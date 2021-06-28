#include<iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <cstring>
using namespace std;

/*常量定义*/
constexpr auto sy_if = 0, sy_then = 1, sy_else = 2, sy_while = 3;
constexpr auto sy_begin = 4, sy_do = 5, sy_end = 6;
constexpr auto a = 7;		// 转化的时候注意到与库文件有类似的地方
constexpr auto semicolon = 8;
constexpr auto e = 9;
constexpr auto jinghao = 10;
constexpr auto S = 11;
constexpr auto L = 12;
constexpr auto tempsy = 15;
constexpr auto EA = 18;
constexpr auto E0 = 19;
constexpr auto jiafa = 34;
constexpr auto times = 36;
constexpr auto becomes = 38;
constexpr auto op_and = 39, op_or = 40, op_not = 41;
constexpr auto rop = 42;
constexpr auto lparent = 48, rparent = 49;
constexpr auto ident = 56;
constexpr auto intconst = 57;

// 编译程序中涉及到的变量及数据结构说明如下：
char ch = '\0';		// 从字符缓冲区读取当前字符
int counter = 0;	// 词法分析结果缓冲区计数器
static char spelling[10] = { "" };		// 存放识别的字
static char line[81] = { "" };			// 一行字符缓冲区，最多 80 个字符
char* pline;	// 字符缓冲区指针
static char ntab1[100][10];				// 变量名表，共 100 项，每项长度 10

/*保留字表的结构，用来与输入缓冲区中的单词进行匹配*/
struct rwords {
	char sp[10];
	int sy;
};
/* 保留字表初始化，大小为 10*/
rwords reswords[10] = {
	{"if",sy_if},
	{"do",sy_do},
	{"else",sy_else},
	{"while",sy_while},
	{"then",sy_then},
	{"begin",sy_begin},
	{"end",sy_end},
	{"and",op_and},
	{"or",op_or},
	{"not",op_not}
};

struct aa {
	int sy1;	// 存放单词的种别编码
	int pos;	// 存放单词自身的值
};
aa buf[1000];	// 词法分析结果缓冲区

int nlength = 0;	// 词法分析中记录单词的长度
int tt1 = 0;		// 变量名表指针
FILE* cfile;		// 源程序文件, #~为结束符
int lnum = 0;		// 源程序行数记数

/************* 从文件读一行到缓冲区 *************/
void readline() {
	char ch1;
	pline = line;
	ch1 = getc(cfile);
	while (ch1 != '\n' && !feof(cfile)) {
		*pline = ch1;
		pline++;
		ch1 = getc(cfile);
	}
	*pline = '\0';
	pline = line;
}

/************* 从缓冲区读取一个字符 *********************/
void readch() {
	if (ch == '\0') {
		readline();
		lnum++;
	}
	ch = *pline;
	pline++;
}

/**********************  变量匹配，查找变量名表  *******************/
int find(char spel[]) {
	int ss1 = 0;
	int ii = 0;
	while ((ss1 == 0) && (ii < nlength)) {
		if (!strcmp(spel, ntab1[ii]))
			ss1 = 1;	// 查找，匹配
		ii++;
	}
	if (ss1 == 1)
		return ii - 1;	// 查找到
	else
		return -1;		// 没查找到
}

/*************** 标识符和保留字的识别 ******************/
void identifier() {
	int iii = 0, j, k;
	int ss = 0;
	k = 0;
	do {
		spelling[k] = ch;
		k++;
		readch();
	} while (((ch >= 'a') && (ch <= 'z')) || ((ch >= '0') && (ch <= '9')));
	pline--;
	spelling[k] = '\0';
	while ((ss == 0) && (iii < 10)) {
		if (!strcmp(spelling, reswords[iii].sp)) ss = 1;	// 保留字匹配
		iii++;
	}
	if (ss == 1) {
		buf[counter].sy1 = reswords[iii - 1].sy;	// 是保留字
	}
	else {
		buf[counter].sy1 = ident;	// 是标识符，变量名
		j = find(spelling);
		/* 没有在变量名表中则添加 */
		if (j == -1) {
			buf[counter].pos = tt1;		// tt1 是变量名表指针
			strcpy_s(ntab1[tt1], strlen(spelling) + 1, spelling);
			tt1++;
			nlength++;
		}
		else buf[counter].pos = j;		// 获得变量名自身的值
	}
	counter++;
	for (k = 0; k < 10; k++) {
		char temp = '\0';
		spelling[k] = ' '; /* 清空单词符号缓冲区 */
	}
}

/*********************** 数字识别 **********************/
void number() {
	int ivalue = 0;
	int digit;
	do {
		digit = ch - '0';
		ivalue = ivalue * 10 + digit; /* 数字字符转换为十进制整常数 */
		readch();
	} while ((ch >= '0') && (ch <= '9'));
	buf[counter].sy1 = intconst;	// 整常数单词符号二元式
	buf[counter].pos = ivalue;
	counter++;
	pline--;
}

/**************  显示词法分析结果：单词符号二元式  ****************/
void disp1() {
	int temp1 = 0;
	printf("\n*********  词法分析结果  ************************\n");
	for (temp1 = 0; temp1 < counter; temp1++) {
		printf("%d\t%d\n", buf[temp1].sy1, buf[temp1].pos);
		// if(temp1==20)
		// {
		// printf("Press any key to continue.......\n");
		//     //system("stty -icanon");
		// getchar();
		// }
	}
	//system("stty -icanon");
	//getchar();
	cout << "\n" << endl;
}

/*****************  打印变量名表  *************************/
void disp3() {
	int tttt;
	printf("\n\n 程序总共 %d 行，产生了 %d 个二元式！ \n", lnum, counter);
	//system("stty -icanon");
	//getchar();
	cout << "\n" << endl;
	printf("\n**************  变量名表  *********************\n");
	for (tttt = 0; tttt < tt1; tttt++)
		printf("%d\t%s\n", tttt, ntab1[tttt]);
	//system("stty -icanon");
	//getchar();
	cout << "\n" << endl;
}

/****************** 扫描主函数 **************************/
void scan() {
	//int i;
	/*’  ’ 是源程序结束符号 */
	while (ch != '#') {
		switch (ch) {
		case ' ':
			break;
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z': /* 保留字和标识符中的字母只能是小写字母 */
			identifier(); /* 识别保留字和标识符 */
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			number(); /* 识别整常数 */
			break;
		case '<':
			readch();
			if (ch == '=') {
				buf[counter].pos = 0; /* 识别 ’<=’*/
			}
			else {
				if (ch == '>') buf[counter].pos = 4; /* 识别 ’<>’*/
				else {
					buf[counter].pos = 1; /* 识别 ’<’*/
					pline--;
				}
			}
			buf[counter].sy1 = rop; /* 识别关系运算符 */
			counter++;
			break;
		case '>':
			readch();
			if (ch == '=') {
				buf[counter].pos = 2; /* 识别 ’>=’*/
			}
			else {
				buf[counter].pos = 3; /* 识别 ’>’*/
				pline--;
			}
			buf[counter].sy1 = rop; /* 识别关系运算符 */
			counter++;
			break;
		case '(':
			buf[counter].sy1 = lparent; /* 识别 ’(’*/
			counter++;
			break;
		case ')':
			buf[counter].sy1 = rparent; /* 识别 ’)’*/
			counter++;
			break;
		case '#':
			buf[counter].sy1 = jinghao; /* 识别 ’#’*/
			counter++;
			break;
		case '+':
			buf[counter].sy1 = jiafa; /* 识别 ’+’*/
			counter++;
			break;
		case '*':
			buf[counter].sy1 = times; /* 识别 ’*’*/
			counter++;
			break;
		case ':':
			readch();
			if (ch == '=')
				buf[counter].sy1 = becomes; /* 识别 ’:=’*/
			counter++;
			break;
		case '=':
			buf[counter].sy1 = rop;
			buf[counter].pos = 5; /* 识别 ’=’ ，关系算符 */
			counter++;
			break;
		case ';':
			buf[counter].sy1 = semicolon; /* 识别 ’ ； ’*/
			counter++;
			break;
		}
		readch();
	}
	buf[counter].sy1 = -1; /* 不可识别的符号 */
}


int main(int argc, const char* argv[]) {
	errno_t ccfile;
	ccfile = fopen_s(&cfile, "pas.dat", "r"); /* 打开 C 语言源文件 */
	readch(); /* 从源文件读一个字符 */
	scan(); /* 词法分析 */
	disp1(); /* 打印词法分析结果 */
	disp3(); /* 打印词法分析变量名表 */
	printf("\n 程序运行结束！ \n");
	//system("stty -icanon");
	//getchar();
	cout << endl << endl;
	return 0;
}
