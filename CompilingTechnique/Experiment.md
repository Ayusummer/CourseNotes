<!--
 * @Author: your name
 * @Date: 2021-04-02 15:27:49
 * @LastEditTime: 2021-05-25 11:42:06
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\CompilingTechnique\Experiment.md
-->
# 实验1 手工实现词法分析器


## 实验要求
- `34`:上机实验内容:词法分析器手工实现(参考教材状态转换图)
   
  ---
- `12`:
  - 一、题目
    - 编制C语言子集的词法分析程序
  - 二、目的
    - 通过设计、编制、调试一个具体的词法分析程序，加深对词法分析原理的理解，并掌握在对程序设计语言源程序进行扫描过程中将其分解为各类单词的词法分析方法。
  - 三、要求
    - 1.根据具体情况，由同学们自己选取C语言的一个适当大小的子集，如课本表2.1（常量要求为有符号整数）；在上机前一定要制出相应的表。  
    ![20210402223437](http:cdn.ayusummer233.top/img/20210402223437.png) 
    - 2.程序功能
      - 输入：字符串。
      - 输出：二元式（种别编码，单词自身）构成的序列。
      - 举例：
        - 输入：a=$;#
        - 输出：
          ```
          （6，a）
          （12，=）
          FOUND ERROR
          （13，;）
          ```
    - 3.实验时间： 4学时。
    - 4.检查时间：第7周抽查。
  - 四、步骤
    - 1.定义单词表
    - 2.完善词法分析器程序
      - （1）定义变量、函数
      - （2）增加程序的输入、输出
    - 3.程序验证
    ---
> 通知有所差异,不过最终都是参考课本的`2.1`与`2.2`节

----
## 设计流程
- C语言子集的单词符号及内码值
  ![20210514102959](http:cdn.ayusummer233.top/img/20210514102959.png)
  - 采用了教材表2.1的C语言子集,用此部分手工实现词法分析器已经具有代表性了,再扩充也不过是对已写代码的仿写与重复加工
- 在设计的状态转换图中，首先剔除多余的空白符，其次，将保留字作为一类特殊的标识符来处理，也即对保留字不专设对应的状态转换图，当转换图识别出一个标识符时就去查对上表的前五项，确定它是否为一个保留字。当然，也可以专设一个保留字表来进行处理(个人实际实现的程序中使用的就是另外的保留字表以减少查询判断时间)。 下就是对应上表这个简单词法分析的状态转换图:
  ![20210514103411](http:cdn.ayusummer233.top/img/20210514103411.png)
- 实际实现中使用的数组及函数如下:
  ```C++
  // 关键字字符数组
  const char* keyword[5] = { "while","if","else","switch","case" };
  // C语言自己的单词符号及内码值
  const char* table[14] = { "while", "if","else","switch","case","标识符", "常数",
                "+", "-", "*", "<=或<或==", "=", ";" };
  void init_token(char* token);    // 初始化token数组
  void input_code(char* code);    // 输入代码
  int judge_token(char* code, char* token, int* order);    // 判断词根类型
  void judge(char* code);            // 词法分析
  ```
  - `token` : 字符数组，存放构成单词符号的字符串
- 确定好C语言子集并绘制好状态转换图之后程序的关键逻辑(判断词根类型)对照状态转换图写即可
- 程序主体部分的逻辑为:
  - `获取输入测试代码` -> `初始化相关变量` -> `判断词根类型` -> `有解释地输出词根判断结果`

## 附录一:源代码

---
### `assistFunction.h`
```C++
void init_token(char* token);    // 初始化token数组
void input_code(char* code);    // 输入代码
int judge_token(char* code, char* token, int* order);    // 判断词根类型
void judge(char* code);            // 词法分析
```

  ---
### `assistFunction.cpp`
```C++
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

```

---
### `analyse.cpp`
```C++
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include"assistFunction.h"
using namespace std;
constexpr auto code_size = 100;

int main() {
    char code[code_size];
    input_code(code);
    judge(code);

    system("pause");
    return 0;
}
```


----
# 实验2-LL(1)分析法

---
## 一、题目
- 编制LL(1)语法分析程序

---
## 二、目的
- 通过设计、编制、调试一个典型的语法分析程序，能识别由加+、乘*、括号（）、操作数所组成的算术表达式，

---
## 三、要求
- 编程实现LL(1)语法分析程序，对满足条件的输入文法能够自动的生成该文法的语法分析程序并执行分析过程，输出所采用的产生式。
- LL(1)语法分析程序有以下功能
  - 自动构建FIRST集
  - 自动构建FOLLOW集
  - 自动构建预测分析表
  - 执行分析程序分析输入串
  - 输出所采用的产生式

----
## 四、设计流程

---
### 数据结构
```cpp
// 产生式结构体
struct Production {
    char left; // 左部符号
    vector<char> rigths;  // 右部符号串
};

// 文法结构体 
struct Grammar {
    int num;  // 产生式数量
    vector<char> T;   // 终结符集
    vector<char> N;   // 非终结符集
    vector<Production> prods;  //产生式集
} grammar;

// FIRST集和FOLLOW集
map<char, set<char> > first;
map<char, set<char> > follow;

// 分析栈
stack<char> ST;

// 待分析串
string str;

// 预测分析表
vector<char> M[50][50];
```

----
### 构建FIRST集和FOLLOW集

---
#### 求单个文法符号的FIRST集
- 若 $X∈V_r$, 则 $FIRST(X) = {X}$。
- 若 $X∈V_N$, 且有产生式 $X → a...$, 其中 $\alpha∈V_T$, 则把 $\alpha$ 加入到 $FIRST(X)$ 中;  
  若有产生式 $X → ε$, 则 ε 也加人到 $FIRST(X)$ 中;
- 若有产生式 $X → Y...$ 且 $Y ∈ V_N$, 则把 $FIRST(Y)$ 中的所有非 ε 元素加入到 $FIRST(X)$ 中;
- 若有产生式 $X → Y_1Y_2...Y_K$, 如果对某个 i, $FIRST(Y_1), FIRST(Y_2), ..., FIRST(Y_{i-1})$都含有 ε,即 $Y_1Y_2...Y_{i-1}$ 经过若干操作可推导出 $ε$, 则把 $FIRST(Y_i)$ 中的所有非 ε 元素加入到 $FIRST(X)$ 中;  
  若所有 $FIRST(Y_i)$ 均含有 $ε$, 其中 $i=1, 2, ..., k$,则把 ε 加入到 $FIRST(X)$ 中;

根据上述方法,可以为文法G的任何文法符号串 $\alpha$ 构造集合 $FIRST(\alpha)$;

---
#### 求一串文法符号的FIRST集

要求 $FIRST(\alpha)$, 先将 $\alpha$ 的第一个文法符号的 $FIRST$ 集加入到加入到 $FIRST(\alpha)$, 若当前符号的 $FIRST$ 集含空, 则继续将下一个文法符号的 $FIRST$ 加入到 $FIRST(\alpha)$ 中, 直至末尾;

---
#### 求非终结符的FOLLOW集
- 为了构造文法 $G$ 的每个非终结符号 $A$ 的 $FOLLOW(A)$, 可以连续使用下面的规则, 直到每个集合不再增大为止:
  - 对文法开始符号 $S$, 置 $ 于 $FOLLOW(S)$ 中
  - 若有产生式 $A → \alpha B \beta$, 则把 $FIRST(β)$ 中的所有非 $ε$  元素加入到 $FOLLOW(B)$ 中
  - 若有产生式 $A → \alpha B$, 或有产生式 $A → \alpha B \beta$, 但是 $ε∈FIRST(\beta)$, 则把 $FOLLOW(A)$ 中的所有元素加人到 $FOLLOW(B)$ 中。


---
### 构建预测分析表
$for(文法G的每一个产生式A→a)$ {  
&nbsp;&nbsp;&nbsp;&nbsp; $for(每个终结符号 a∈FIRST(a) ) 把 A → a 放入表项M[A,a]中;$    
&nbsp;&nbsp;&nbsp;&nbsp; $if( E∈FIRST(a) )$     
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;
$for (每个 b∈FOLLOW(A) )把 A → a 放入表项 M[A,b] 中;$    
&nbsp;&nbsp;&nbsp;&nbsp; }$;$    
$for(所有无定义的表项M[A,a] )标上错误标志;$



----
### 分析程序
$do${
&nbsp;&nbsp;&nbsp;&nbsp; $令x是栈顶文法符号,a是ip所指向的输入符号;$     
&nbsp;&nbsp;&nbsp;&nbsp; $if(x是终结符号或\$)$    
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; $if(X == a)$ {$从栈顶弹出X; ip前移一个位置$}            
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; $else$ $error();$      
&nbsp;&nbsp;&nbsp;&nbsp; $else$ 
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;  $// x是非终结符号$          
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; $if( M[X,a] = X → Y_1Y_2...Y_K)${      
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; 
$从栈顶弹出X;$        
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; 
$依次把Y_K, Y_{K-1}, ..., Y_2, Y_1 压入栈;$ 
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; 
$// Y_1 在栈顶$        
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; 
$输出产生式 X → Y_1Y_2...Y_k;$                
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; }$;$          
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; $else$ $error ();$        
} $while (X != \$)$
&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp; 
$//栈非空,分析继续$




----
## 五、总结
- 通过本次实验,基本掌握了LL(1)语法分析程序的编写;
- 进一步提升了个人 C++ 编程水平

<div STYLE="page-break-after: always;"></div>


## 附录1 : 程序运行结果
![20210525114203](http:cdn.ayusummer233.top/img/20210525114203.png)


<div STYLE="page-break-after: always;"></div>

----
## 附录2 : 源代码

---
### `assistFunction.h`
```C++
#pragma once
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <stack>
using namespace std;

// 产生式结构体
struct Production {
	char left;				// 左部符号
	vector<char> rigths;	// 右部符号串
};

// 文法结构体
struct Grammar {
	int num;				// 产生式数量
	vector<char> T;			// 终结符
	vector<char> N;			// 非终结符
	vector<Production> prods;  //产生式
} grammar;


// 判断ch是否是终结符
int isInT(char ch);

// 判断ch是否是非终结符
int isInN(char ch);

// 求(T U N)的FIRST集
void getFirstSet();

// 产找alpha串的FIRST集， 保存到FS集合中
void getFirstByAlphaSet(vector<char>& alpha, set<char>& FS);

// 求非终结符的FOLLOW集
void getFollowSet();

// 把生成式插入到预测分析表对应的项中
void insertTOForecastAnalysisTable(char A, char a, Production& P);

// 取出预测分析表对应的项中的产生式
void getFromForecastAnalysisTable(char A, char a, vector<char>& s);

// 构建预测分析表
void productForecastAnalysisTable();

// 读入并初始化语法
void initGrammar();

// 分析程序
void process();

```

  ---
### `assistFUnction.cpp`
```C++
#include"assistFunction.h"
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <stack>
using namespace std;

// FIRST集和FOLLOW集 
map<char, set<char> > first;
map<char, set<char> > follow;

// 分析栈
stack<char> ST;

// 待分析串
string str;

// 预测分析表
vector<char> M[50][50];

// 判断ch是否是终结符
int isInT(char ch) {
	for (int i = 0; i < grammar.T.size(); i++) {
		if (grammar.T[i] == ch) {
			return i + 1;
		}
	}
	return 0;
}


// 判断ch是否是非终结符
int isInN(char ch)
{
	for (int i = 0; i < grammar.N.size(); i++) {
		if (grammar.N[i] == ch) {
			return i + 1;
		}
	}
	return 0;
}


// 求(T U N)的FIRST集
void getFirstSet()
{
	/* 终结符的FIRST集是其本身 */
	for (int i = 0; i < grammar.T.size(); i++) {
		char X = grammar.T[i];
		set<char> tmp;
		tmp.insert(X);
		first[X] = tmp;
	}
	/* 当非终结符的FIRST集发生变化时循环 */
	bool change = true;
	while (change) {
		change = false;
		/* 枚举每个产生式 */
		for (int i = 0; i < grammar.prods.size(); i++) {
			Production& P = grammar.prods[i];
			char X = P.left;
			set<char>& FX = first[X];
			/* 如果右部第一个符号是空或者是终结符，则加入到左部的FIRST集中 */
			if (isInT(P.rigths[0]) || P.rigths[0] == '&') {
				/* 查找是否FIRST集是否已经存在该符号 */
				auto it = FX.find(P.rigths[0]);
				/* 不存在 */
				if (it == FX.end()) {
					change = true; // 标注FIRST集发生变化，循环继续
					FX.insert(P.rigths[0]);
				}
			}
			else {
				/* 当前符号是非终结符，且当前符号可以推出空，则还需判断下一个符号 */
				bool next = true;
				/* 待判断符号的下标 */
				int idx = 0;
				while (next && idx < P.rigths.size()) {
					next = false;
					char Y = P.rigths[idx];
					set<char>& FY = first[Y];
					for (auto it = FY.begin(); it != FY.end(); it++) {
						/* 把当前符号的FIRST集中非空元素加入到左部符号的FIRST集中 */
						if (*it != '&') {
							auto itt = FX.find(*it);
							if (itt == FX.end()) {
								change = true;
								FX.insert(*it);
							}
						}
					}
					/* 当前符号的FIRST集中有空, 标记next为真，idx下标+1 */
					auto it = FY.find('&');
					if (it != FY.end()) {
						next = true;
						idx = idx + 1;
					}
				}

			}
		}
	}
	printf("FIRST:\n");
	for (int i = 0; i < grammar.N.size(); i++) {
		char X = grammar.N[i];
		printf("%c: ", X);
		for (auto it = first[X].begin(); it != first[X].end(); it++) {
			printf("%c ", *it);
		}
		printf("\n");
	}
}


// 产找alpha串的FIRST集， 保存到FS集合中
void getFirstByAlphaSet(vector<char>& alpha, set<char>& FS)
{
	/* 当前符号是非终结符，若当前符号可以推出空，则还需判断下一个符号 */
	bool next = true;
	int idx = 0;
	while (idx < alpha.size() && next) {
		next = false;
		/* 当前符号是终结符或空，加入到FIRST集中 */
		if (isInT(alpha[idx]) || alpha[idx] == '&') {
			/* 判断是否已经在FIRST集中 */
			auto itt = FS.find(alpha[idx]);
			if (itt == FS.end()) {
				FS.insert(alpha[idx]);
			}
		}
		else {
			char B = alpha[idx];
			set<char>& FB = first[B];
			for (auto it = first[B].begin(); it != first[B].end(); it++) {
				/* 当前符号FIRST集包含空，标记next为真，并跳过当前循环 */
				if (*it == '&') {
					next = true;
					continue;
				}
				/* 把非空元素加入到FIRST集中 */
				auto itt = FS.find(*it);
				if (itt == FS.end()) {
					FS.insert(*it);
				}
			}
		}
		idx = idx + 1;
	}
	/* 如果到达产生式右部末尾next还为真，说明alpha可以推空，将空加入到FIRST集中 */
	if (next) {
		FS.insert('&');
	}
}

// 求非终结符的FOLLOW集
void getFollowSet()
{
	/* 初始化终结符的FOLLOW集为空集 */
	for (int i = 0; i < grammar.N.size(); i++) {
		char B = grammar.N[i];
		follow[B] = set<char>();
	}
	/* 将$加入到文法的开始符号的FOLLOW集中 */
	char S = grammar.N[0];
	follow[S].insert('$');

	bool change = true;
	while (change) {
		change = false;
		/* 枚举每个产生式 */
		for (int i = 0; i < grammar.prods.size(); i++) {
			Production& P = grammar.prods[i];
			for (int j = 0; j < P.rigths.size(); j++) {
				char B = P.rigths[j];
				/* 当前符号是非终结符 */
				if (isInN(B)) {
					set<char>& FB = follow[B];
					set<char> FS;
					/* alpha是从当前符号下一个符号开始的符号串 */
					vector<char> alpha(P.rigths.begin() + j + 1, P.rigths.end());
					/* 求alpha的FIRST集，即FS */
					getFirstByAlphaSet(alpha, FS);
					/* 将alpha的FIRST集中所有非空元素加入到当前符号的FOLLOW集中 */
					for (auto it = FS.begin(); it != FS.end(); it++) {
						if (*it == '&') {
							continue;
						}
						auto itt = FB.find(*it);
						if (itt == FB.end()) {
							change = true;
							FB.insert(*it);
						}
					}
					/* 如果alpha能推空，或者当前符号是产生式右部末尾，则将文法左部符号的FOLLOW集加入到当前符号的FOLLOW集中 */
					auto itt = FS.find('&');
					if (itt != FS.end() || (j + 1) >= P.rigths.size()) {
						char A = P.left;    // A为左部符号
						for (auto it = follow[A].begin(); it != follow[A].end(); it++) {
							auto itt = FB.find(*it);
							if (itt == FB.end()) {
								change = true;
								FB.insert(*it);
							}
						}
					}
				}
			}
		}
	}

	printf("FOLLOW:\n");
	for (int i = 0; i < grammar.N.size(); i++) {
		char X = grammar.N[i];
		printf("%c: ", X);
		for (auto it = follow[X].begin(); it != follow[X].end(); it++) {
			printf("%c ", *it);
		}
		printf("\n");
	}
}

// 把生成式插入到预测分析表对应的项中
void insertTOForecastAnalysisTable(char A, char a, Production& P)
{
	/* 根据A和a找到对应表项 */
	int i = isInN(A) - 1;
	int j = isInT(a) - 1;
	/* 把P.left->P.rights插入*/
	M[i][j].push_back(P.left);
	M[i][j].push_back('-');
	M[i][j].push_back('>');
	for (auto it = P.rigths.begin(); it != P.rigths.end(); it++) {
		M[i][j].push_back(*it);
	}
}

// 取出预测分析表对应的项中的产生式
void getFromForecastAnalysisTable(char A, char a, vector<char>& s)
{
	/* 根据A和a找到对应表项 */
	int i = isInN(A) - 1;
	int j = isInT(a) - 1;
	/* 取出 */
	s.assign(M[i][j].begin(), M[i][j].end());
}

// 构建预测分析表
void productForecastAnalysisTable() {
	/* 枚举所有产生式 */
	for (int i = 0; i < grammar.prods.size(); i++) {
		/* 假设P为 A->alpha */
		Production& P = grammar.prods[i];
		set<char> FS;
		/* 对每个 a in FIRST(alpha) 把 A->alpha放入M[A, a]中 */
		getFirstByAlphaSet(P.rigths, FS);
		for (auto it = FS.begin(); it != FS.end(); it++) {
			insertTOForecastAnalysisTable(P.left, *it, P);
		}
		/* 如果alpha能推空，则把每个b in FOLLOW(A) 把 A->alpha放入M[A, b]中*/
		auto itt = FS.find('&');
		if (itt != FS.end()) {
			for (auto it = follow[P.left].begin(); it != follow[P.left].end(); it++) {
				insertTOForecastAnalysisTable(P.left, *it, P);
			}
		}
	}
	/* 输出预测分析表 */
	printf("forecast analysis table:\n");
	printf("\t");
	for (int i = 0; i < grammar.T.size(); i++) {
		printf("%c\t\t", grammar.T[i]);
	}
	printf("\n");
	for (int i = 0; i < grammar.N.size(); i++) {
		printf("%c\t", grammar.N[i]);
		for (int j = 0; j < grammar.T.size(); j++) {
			for (auto k = M[i][j].begin(); k != M[i][j].end(); k++) {
				printf("%c", *k);
			}
			printf("\t\t");
		}
		printf("\n");
	}
}

// 读入并初始化语法
void initGrammar() {
	printf("Please enter the num of production:\n");
	cin >> grammar.num;
	string s;
	printf("Please enter the production:\n");
	for (int i = 0; i < grammar.num; i++) {
		cin >> s;
		Production tmp;
		tmp.left = s[0];
		for (int j = 3; j < s.size(); j++) {
			tmp.rigths.push_back(s[j]);
		}
		grammar.prods.push_back(tmp);
	}
	printf("Please enter the non-terminators(end with #):\n");
	char ch;
	cin >> ch;
	while (ch != '#') {
		grammar.N.push_back(ch);
		cin >> ch;
	}
	printf("Please enter the terminators(end with #):\n");
	cin >> ch;
	while (ch != '#') {
		grammar.T.push_back(ch);
		cin >> ch;
	}
	/* 把$当作终结符 */
	grammar.T.push_back('$');
	/* 求FIRST集和FOLLOW集 */
	getFirstSet();
	getFollowSet();

	/* 生成预测分析表 */
	productForecastAnalysisTable();

	/* 读入待分析串并初始化分析栈 */
	printf("Please enter the String to be analyzed:\n");
	cin >> str;
	str += '$';
	ST.push('$');
	ST.push(grammar.N[0]);
}

// 分析程序
void process()
{
	/* 指向当前字符 */
	int ip = 0;
	/* 栈顶符号X， 和当前输入符号a */
	char X, a;
	printf("The answer:\n");
	do {
		X = ST.top();
		a = str[ip];
		/* 如果是终结符或者$ */
		if (isInT(X)) {
			/* 如果栈顶符号和当前符号匹配，出栈，指针前移 */
			if (X == a) {
				ST.pop();
				ip = ip + 1;
			}
			else { /* 不匹配报错 */
				printf("error1\n");
			}
		}
		else {    //非终结符
			vector<char> s;
			/* 取出对应预测分析表的项 */
			getFromForecastAnalysisTable(X, a, s);
			/* 预测分析表项中有元素 */
			if (!s.empty()) {
				/* 弹栈并将右部符号串逆序入栈 */
				ST.pop();
				for (int i = s.size() - 1; i >= 3; i--) {
					if (s[i] != '&') { // 为空时不入栈
						ST.push(s[i]);
					}
				}
				/* 输出产生式 */
				for (int i = 0; i < s.size(); i++) {
					printf("%c", s[i]);
				}
				printf("\n");
			}
			else { // 空，报错
				printf("error2\n");
			}
		}
	} while (X != '$');
}

```

<div STYLE="page-break-after: always;"></div>

---
### `主程序.cpp`
```C++
#include"assistFunction.h"

int main() {
	initGrammar();
	process();
	return 0;
}
```