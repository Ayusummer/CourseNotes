#include"assistFunction.h"
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<iomanip>
using namespace std;

constexpr auto token_size = 12;

// 关键字字符数组
const char* keyword[5] = { "while","if","else","switch","case" };
// C语言自己的单词符号及内码值
const char* table[14] = { "while", "if","else","switch","case","标识符", "常数",
                            "+", "-", "*", "<=或<或==", "=", ";" };


// 初始化token数组
void init_token(char* token) {
    for (int i = 0; i < token_size; i++)
        *(token + i) = NULL;
}


// 输入代码
void input_code(char* code) {
    cout << "请输入程序段，回车换行，输入$完成输入" << endl;
    char ch;
    int i;
    for (i = 0; cin.get(ch) && ch != '$'; i++) {
        *(code + i) = ch;
    }
    *(code + i) = '$';
}

// 判断词根类型
int judge_token(char* code, char* token, int* order) {
    init_token(token);
    int token_num = 0;

    // 忽略空格
    while (*(code + *order) == ' ')
        (*order)++;

    // 判断是否为数字
    if (*(code + *order) >= '0' && *(code + *order) <= '9') {
        while (*(code + *order) >= '0' && *(code + *order) <= '9' || *(code + *order) == '.') {
            *(token + token_num) = *(code + *order);
            token_num++; (*order)++;
        }
        return 7;
    }

    // 判断是否为标识符或变量名
    else if ((*(code + *order) >= 'a' && *(code + *order) <= 'z')
        || (*(code + *order) >= 'A' && *(code + *order) <= 'Z')) {
        while ((*(code + *order) >= '0' && *(code + *order) <= '9')
            || (*(code + *order) >= 'a' && *(code + *order) <= 'z')
            || (*(code + *order) >= 'A' && *(code + *order) <= 'Z')
            || *(code + *order) == '_') {
            *(token + token_num) = *(code + *order);
            token_num++;
            (*order)++;
        }
        *(token + token_num++) = '\0';
        for (int i = 0; i < 5; i++) {
            if (!strcmp(token, keyword[i]))
                //    cout << token << keyword[i] << strcmp(token, keyword[i]) << endl;
                return i + 1;
        }
        return 6;
    }

    // 判断是否为其他运算符
    else {
        *(token + token_num++) = *(code + (*order));
        switch (*(code + (*order)++)) {
        case '+':
            if (*(code + (*order)) == '+') {
                *(token + token_num++) = *(code + (*order)++);
                return 8;  // +
            }
        case '-':
            if (*(code + (*order)) == '-') {
                *(token + token_num++) = *(code + (*order)++);
                return 9;  // - 
            }
        case '*': return 10;  // *
        case '<':
            if (*(code + (*order)) == '=') {
                *(token + token_num++) = *(code + (*order)++);
            }
            return 11;
        case '=':
            if (*(code + (*order)) == '=') {
                *(token + token_num++) = *(code + (*order)++);
                return 11;
            }
            return 12;
        case ';': return 13;
        case '\n': init_token(token); return -2;
        default:  return -1;
        }
    }
}



void judge(char* code) {
    int order = 0, row = 1;
    int symbol;
    char token[token_size];
    cout << "\n\n\n\n\n词法分析结果如下:" << endl;
    do {
        symbol = judge_token(code, token, &order);
        switch (symbol) {
        case -1:          // 返回未识别字符所在行数
            cout << "第" << row << "行出现未识别字符" << endl;
            break;
        case -2:          // 读到了回车键，进行换行，行数加一
            row++;
            break;
        default:
            cout << setw(2) << symbol << "  "
                << setw(5) << table[symbol - 1] << "  "
                << setw(5) << token << endl;
        }
    } while (*(code + order) != '$');
}
