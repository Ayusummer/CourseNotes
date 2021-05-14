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
