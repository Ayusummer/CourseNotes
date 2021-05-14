#pragma once


void init_token(char* token);	// 初始化token数组
void input_code(char* code);	// 输入代码
int judge_token(char* code, char* token, int* order);	// 判断词根类型
void judge(char* code);			// 词法分析
