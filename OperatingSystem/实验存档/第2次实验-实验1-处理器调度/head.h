#pragma once
#include<iostream>
#include<string.h>
using namespace std;

// 进程结点
typedef struct node {
	string name;			//进程名 
	int roundtime;			//轮转时间片          
	int runnedtime;			//已运行时间    
	int needtime;			//还需运行时间    
	int count;				//计数器    
	char state;				//进程状态    
	struct node* next;		//链指针 
	
	// 构造函数,用于创建节点
	node(string na, int ro, int ru, int ne, int co, int st);
}PCB;

// 进程队列,没有头结点的单向非循环列表
class ProcessQueue {
public:
	PCB* ready;				// 队首结点指针
	PCB* run;				// 正在运行的结点指针
	PCB* endP;				// 已经运行完成的结点指针
	PCB* tail;				// 队尾结点指针
	int n;					// 进程数目

	ProcessQueue();			// 空构造函数,用于创建空链表
	void input_n();			// 输入进程数目n
	void insert(PCB p);		// 插入一个进程结点
	void create();			// 初始化进程队列
	void show();			// 输出就绪进程队列
	PCB* del();				// 出队
	void roundtime();		// 时间片轮转法算法
};
