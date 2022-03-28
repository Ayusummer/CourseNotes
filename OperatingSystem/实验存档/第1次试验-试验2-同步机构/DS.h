#pragma once
#include<string>
using namespace std;
#include <vector>
#include"list.h"
constexpr auto MAX = 50;	// 最大产品数;

// 进程控制块类型
struct PCB {
	string name;			// 进程名
	string status;			// 进程状态：就绪态, 运行态, 阻塞态, 完成态
	string reason_wait;		// 等待原因
	int  breakPoint;		// 断点信息，使用int类型变量来判断运行到的位置

	char product_produced;	// 生产出来的产品
	char product_geted;		// 从缓冲区中取出来的产品
};


// 本次专用同步机构类
class SM {
public:
	vector <PCB> consumer;		// 消费者数组
	vector <PCB> producer;		// 生产者数组
	vector <char> bufferPC;		// 生产消费缓冲区数组

	char products_required[MAX];        // 需要生产的产品
	int subscript_requiredProduct = 0;  // 待生产的products数组下标
	int num_requiredProduct;			// 需要生产的产品总数

	// 生产者断点含义数组
	string breakPoint_string_producer[3] = { "已就绪", "已获取生产锁", "产品已生产" };
	// 消费者断点含义数组
	string breakPoint_string_consumer[3] = { "已就绪", "已获取消费锁", "已获取待消费产品" };

	/* 访问互斥信号量
	num_product表示缓冲区中的产品数, block_produce表示缓冲区空闲数，二者相加为缓冲区大小*/
	int mutex_consume, mutex_produce;
	// 当前已经放入缓冲区的产品数目
	int	product_havePut;
	// 当前已经消费的产品数目
	int product_haveConsumed;
	// 当前没有阻塞的生产者进程下标,随SM初始化而初始化
	List<int> subscript_unwaitedProducer;
	// 当前没有阻塞的消费者进程下标,随SM初始化而初始化
	List<int> subscript_unwaitedConsumer;



	// 初始化生产者和消费者的数目, 互斥信号量, 缓冲区大小, 待生产产品及其数目
	void init();
	void showProcessSituation();	// 输出所有模拟进程当前情况
	bool isGoing_producer();		// 判断是否有生产者进程还在运行
	int P(int num_process);			// P操作原语
	int V(int num_process);			// V操作原语
	int num_first_waitBlock(int producer_or_consumer);	// 返回队列中第一个等锁的进程
	void produce(int subscript_whichProducer);	// 生产一份产品
	void put(int subscript_whichProducer);		// 将当前生产的产品放入缓冲区
	void GET(int subscript_whichConsumer);						// 从缓冲区获取一件产品
	void consume(int subscript_whichConsumer);		// 消费一件产品
	void NOP();						// 空操作指令
	void runningProduceConsume();	// 进行生产消费
	void oneStep_producer(int subscript_whichProducer);	// 生产者单步
	void oneStep_consumer(int subscript_whichConsumer);	// 消费者单步
	void resetProducer();	// 重置所有生产者进程以及未阻塞生产者进程下标队列
};
