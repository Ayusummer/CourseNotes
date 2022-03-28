#include<iostream>
#include<string.h>
#include"head.h"
using namespace std;

int main() {
	printf("******************************\n");
	printf("**时间片轮转法实现处理器调度**\n");
	printf("******************************\n\n\n\n");
	ProcessQueue PQ = ProcessQueue();
	PQ.input_n();			// 输入进程数目
	PQ.create();			// 创建进程队列
	PQ.roundtime();
	system("pause");
	return 0;
}
