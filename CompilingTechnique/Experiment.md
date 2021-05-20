<!--
 * @Author: your name
 * @Date: 2021-04-02 15:27:49
 * @LastEditTime: 2021-05-14 10:47:16
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