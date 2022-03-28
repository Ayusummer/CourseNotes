#include "head.h"
#include<iostream>
#include<string.h>
using namespace std;

// 构造函数,用于创建节点
node::node(string na, int ro, int ru, int ne, int co, int st){
	name = na;
	roundtime = ro;
	runnedtime = ru;
	needtime = ne;
	count = co;
	state = st;
	next = NULL;		//链指针 
}

// 空构造函数,用于创建空链表
ProcessQueue::ProcessQueue(){
	ready = NULL;				// 队首结点指针为空
	run = NULL;					// 正在运行的结点指针为空
	endP = NULL;				// 已经运行完成的结点指针为空
	tail = NULL;				// 队尾结点指针为空
	int n = 0;					// 进程数目为零
}


// 输入创建进程数目
void ProcessQueue::input_n() {
	cout << "输入创建进程数目:";
	cin >> n;
}

// 插入一个进程结点
void ProcessQueue::insert(PCB p){
	PCB* pp = new PCB(p);
	if (tail == NULL) {	// 若队尾结点为空则说明此时链表为空
		// 首尾都应当为当前插入结点
		ready = pp;
		tail = pp;
	}
	else if (tail != NULL) {	// 若队尾结点不为空
		// 则队尾结点next指针指向当前插入结点并更新队尾指针
		tail->next = pp;
		tail = pp;
	}
}

/*输出就绪进程队列*/
void ProcessQueue::show(){
	PCB* p = ready;	//p指向头指针   
	if (ready != NULL)
		printf("进程名  已运行时间  还需时间  计数器  时间片  状态\n");
	while (p != NULL) {
		cout << p->name <<"          "<< p->runnedtime << "        " << p->needtime 
			 << "        " << p->count << "        " << p->roundtime << "        " 
			<< p->state << "        " << endl;
		p = p->next;
	}
}


void ProcessQueue::create() {
	int i, time;
	string name;
	cout << "请输入进程名和要求运行的时间:" << endl;
	cout << "注:每一组进程名和要求运行的时间用空格隔开" << endl;
	cout << "输入完一组进程后请回车" << endl;
	for (i = 0; i < n; i++) {
		cin >> name >> time;			//键盘输入进程名及要运行时间    
		//p = (PCB*)malloc(sizeof(PCB));	//创建新的空间       
		PCB p = node(name, 1, 0, time, 0, 'R');
		//已运行时间开始为0   
		//还需要的时间为总时间        
		//计数器初值为0   
		//进程初始状态为ready   
		//时间片论时间为1   
		//预处理结点与队列断开，若没有运行完成，则插入到队尾；否则就视为删除   
		insert(p);
	}
	printf("\n\n");
	printf("**************************************************\n");
	printf("**                   进程信息                   **\n");
	printf("**************************************************\n");
	show();
}

/*出队*/
PCB* ProcessQueue::del()
{
	PCB* p = ready;
	ready = ready->next;
	if (ready == NULL)
		tail = NULL;
	p->next = NULL;
	return p;
}

/*时间片轮转法算法*/
void ProcessQueue::roundtime(){
	PCB* tial = NULL;
	int k = 1;					//记录运行次数  
	while (ready != NULL) {
		run = del();
		run->state = 'Y';
		run->runnedtime = run->runnedtime + 1;
		run->needtime = run->needtime - 1;
		run->count = run->count + 1;
		if (run->needtime == 0) {		/*运行完时将其变为完成态，插入完成队列*/
			printf("\n\n\n********第%d次运行结果*******\n", k);
			cout << "进程" << run->name << "已完成!" << endl;
			endP = run;
			endP->state = 'E';
		}
		else if (run->count == run->roundtime) {			/*如果时间片到*/
			printf("\n********第%d次运行结果*******\n", k);
			run->count = 0;									/*记数器置零*/
			run->state = 'R';								/*将进程插入到就绪队列中等待轮转*/
			insert(PCB(run->name, run->roundtime, run->runnedtime, run->needtime, run->count, run->state));
		}
		k++;
		show();
	}
}
