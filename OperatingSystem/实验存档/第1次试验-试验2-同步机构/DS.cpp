#include <windows.h>	// 务必放在第一个编译,否则会因为"byte"的重定义而报错
#include "DS.h"
#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

// 初始化生产者和消费者的数目, 互斥信号量, 缓冲区大小, 待生产产品及其数目
void SM::init() {
	int producer_num, consumer_num;		// 生产者,消费者个数
	cout << "请依次输入生产者和消费者个数：(中间用空格隔开)";
	cin >> producer_num >> consumer_num;

	int size_buffer;					// 缓冲区大小
	cout << "请输入缓冲区大小：";
	cin >> size_buffer;

	cout << "请输入需要生产的产品：";
	cin >> products_required;					// 初始化产品序列
	int num_requiredProduct_temp = 0;
	while (products_required[num_requiredProduct_temp] != '\0')
		num_requiredProduct_temp++;
	num_requiredProduct = num_requiredProduct_temp;
	cout << "待生产产品总数为: " << num_requiredProduct << endl;

	// 初始化互斥信号量
	mutex_consume = 0;
	mutex_produce = size_buffer;


	//产品个数;
	int num_requiredProduct = 0;
	while (products_required[num_requiredProduct] != '\0')
		num_requiredProduct++;

	//创建生产者模拟进程
	for (int i = 0; i < producer_num; i++) {
		PCB* pcb = new PCB;
		pcb->name = "producer" + to_string(i);	// 进程名
		pcb->status = "就绪态";					// 初始状态设为就绪态
		pcb->reason_wait = "";					// 等待原因为空
		pcb->breakPoint = 0;					// 断点为0

		producer.push_back(*pcb);				// 添加到produce数组中
		subscript_unwaitedProducer.addLN(i);	// 加入到未阻塞生产者进程队列
	}

	//创建消费者模拟进程
	for (int i = 0; i < consumer_num; i++) {
		PCB* pcb = new PCB;
		pcb->name = "consumer" + to_string(i);
		pcb->status = "就绪态";					// 初始状态设为就绪态
		pcb->reason_wait = "";					// 等待原因为空
		pcb->breakPoint = 0;					// 断点为0

		consumer.push_back(*pcb);				// 添加到consume数组中
		subscript_unwaitedConsumer.addLN(i);	// 加入到未阻塞消费者进程队列
	}

	cout << "同步机构初始化已完成\n" << endl;
	cout << "当前未阻塞的生产者进程下标队列为: ";
	subscript_unwaitedProducer.showList();
	cout << "当前未阻塞的消费者进程下标队列为: ";
	subscript_unwaitedConsumer.showList();
	cout << endl;
}

// 输出所有模拟进程当前执行情况
void SM::showProcessSituation() {
	cout << setiosflags(ios::left)
		<< setw(10) << "进程名" << "\t"
		<< setw(6) << "状态" << "\t"
		<< setw(18) << "等待原因" << "\t"
		<< setw(16) << "断点" << endl;

	//输出生产者状态
	for (int i = 0; producer.size() >= 0 && i < producer.size(); i++) {
		cout << setiosflags(ios::left)
			<< setw(10) << producer[i].name << "\t"
			<< setw(6) << producer[i].status << "\t"
			<< setw(18) << producer[i].reason_wait << "\t"
			<< setw(16) << breakPoint_string_producer[producer[i].breakPoint] << endl;
	}

	//输出消费者状态
	for (int i = 0; i < consumer.size(); i++) {
		cout << setw(10) << consumer[i].name << "\t"
			<< setw(6) << consumer[i].status << "\t"
			<< setw(18) << consumer[i].reason_wait << "\t"
			<< setw(16) << breakPoint_string_consumer[consumer[i].breakPoint] << endl;
	}

	cout << endl;
}

// 根据断点判断是否有生产者进程还在运行
bool SM::isGoing_producer() {
	for (int i = 0; i < producer.size(); i++) {
		if (producer[i].breakPoint > 0 && producer[i].breakPoint <= 2)
			return true;
	}
	return false;
}


int SM::P(int num_process) {
	// 如果是生产者执行P操作
	if (num_process < producer.size()) {
		cout << "当前生产空间为: " << mutex_produce << " 获取生产锁" << endl;
		mutex_produce--;
		if (mutex_produce < 0) {
			producer[num_process].status = "阻塞态";
			producer[num_process].reason_wait = "缓冲区内无生产空间";
			subscript_unwaitedProducer.deleteByValue(num_process);
		}
		else
			producer[num_process].status = "运行态";
		return(mutex_produce);
	}
	// 如果是消费者执行P操作
	else {
		cout << "当前缓冲区内产品数目为: " << mutex_consume << " ,获取消费锁" << endl;
		mutex_consume--;
		if (mutex_consume < 0) {
			consumer[num_process - producer.size()].status = "阻塞态";
			consumer[num_process - producer.size()].reason_wait = "缓冲区中无产品";
			subscript_unwaitedConsumer.deleteByValue(num_process - producer.size());
		}
		else
			consumer[num_process - producer.size()].status = "运行态";
		return mutex_consume;
	}

}

int SM::V(int num_process) {
	// 如果是生产者执行V操作
	if (num_process < producer.size()) {
		mutex_consume++;
		// 信号量依然<0则表示有消费者在等锁
		if (mutex_consume <= 0) {
			// 若有消费者在等锁
			int num_first_waitBlock_temp = num_first_waitBlock(0);
			if (num_first_waitBlock_temp != -1) {
				consumer[num_first_waitBlock_temp].status = "就绪态";
				consumer[num_first_waitBlock_temp].reason_wait = "";
				// 加入到未阻塞消费者进程队列中
				subscript_unwaitedConsumer
					.addLN(num_first_waitBlock_temp);
			}
			producer[num_process].status = "完成态";

		}

		// 若信号量>0则完成
		else
			producer[num_process].status = "完成态";
		return mutex_consume;
	}
	// 如果是消费者执行V操作
	else {
		mutex_produce++;
		if (mutex_produce <= 0) {
			// 若有生产者在等锁
			int num_first_waitBlock_temp = num_first_waitBlock(1);
			if (num_first_waitBlock_temp != -1) {
				producer[num_first_waitBlock_temp].status = "就绪态";
				producer[num_first_waitBlock_temp].reason_wait = "";
				// 加入到未阻塞生产者进程队列中
				subscript_unwaitedProducer
					.addLN(num_first_waitBlock_temp);
			}
			consumer[num_process - producer.size()].status = "完成态";
		}
		// 唤醒一个生产者进程
		else
			consumer[num_process - producer.size()].status = "完成态";
		return mutex_produce;
	}
}

// 返回队列中第一个等锁的进程的数组下标
int SM::num_first_waitBlock(int producer_or_consumer) {
	int i;	// 循环计数器
	if (producer_or_consumer) {
		for (i = 0; i < producer.size(); i++) {
			if (producer[i].status == "阻塞态") {
				return i;
				break;
			}
			else {}
		}
	}
	else {
		for (i = 0; i < consumer.size(); i++) {
			if (consumer[i].status == "阻塞态") {
				return i;
				break;
			}
			else {}
		}
	}
	return -1;	// 如果没有进程在等锁则返回无意义的下标-1
}

// 生产一份产品
void SM::produce(int subscript_whichProducer) {
	producer[subscript_whichProducer].product_produced = products_required[subscript_requiredProduct];
	cout << "产品 " << products_required[subscript_requiredProduct] << " 生产完成" << endl;
	subscript_requiredProduct++;	// 待生产产品下标+1
}

// 将一个产品放入缓冲区
void SM::put(int subscript_whichProducer) {
	bufferPC.push_back(producer[subscript_whichProducer].product_produced);
	cout << "产品 " << producer[subscript_whichProducer].product_produced
		<< " 已放入缓冲区" << endl;
	producer[subscript_whichProducer].product_produced = '\0';
	product_havePut++;	// 已经放入缓冲区的产品数目+1
}

// 从缓冲区获取一件产品
void SM::GET(int subscript_whichConsumer) {
	consumer[subscript_whichConsumer].product_geted
		= bufferPC[bufferPC.size() - 1];
	bufferPC.pop_back();
	cout << "已获取到产品 "
		<< consumer[subscript_whichConsumer].product_geted << endl;
}

// 消费一件产品
void SM::consume(int subscript_whichConsumer) {
	cout << "消费者已消费产品 "
		<< consumer[subscript_whichConsumer].product_geted << endl;
	consumer[subscript_whichConsumer].product_geted = '\0';
	product_haveConsumed++;		// 已经消费的产品数+1
}

// 空操作指令
void SM::NOP() {}

// 进行生产消费
void SM::runningProduceConsume() {
	// 生成随机数种子,用于决定唤醒哪一个进程
	srand((unsigned)time(NULL));

	while (1) {
		// 通过随机数选择即将运行的进程
		int process_select_random;
		// 如果还有产品需要生产且当前缓冲区中无产品时只投掷没阻塞的生产者骰子
		if (products_required[subscript_requiredProduct] != '\0') {
			cout << "当前仍有尚未完成的产品" << endl;
			if (bufferPC.size() == 0) {
				// 这里需要优化,应该是选择一个正在运行的生产者进程继续执行
				cout << "缓冲区内无产品,选择一个未阻塞的生产者进程执行" << endl;
				process_select_random = rand()
					% subscript_unwaitedProducer.size_list;
			}
			else {
				cout << "当前缓冲区内有产品,随机选取一个未阻塞的进程执行" << endl;
				process_select_random = (rand()
					% (subscript_unwaitedProducer.size_list
						+ subscript_unwaitedConsumer.size_list));
			}
		}
		// 否则生产均已完成,看看有没有放入缓冲区
		else {
			cout << "生产已完成" << endl;
			// 若缓冲区内无产品呢
			if (bufferPC.size() == 0) {
				// 若所有产品尚未放入缓冲区则选择一个未阻塞的生产者进程执行
				if (product_havePut != num_requiredProduct) {
					cout << "尚有产品未放入缓冲区,选择一个未阻塞的生产者进程执行" << endl;
					process_select_random = rand()
						% subscript_unwaitedProducer.size_list;
				}
				// 若所有产品呢均已放入缓冲区则选择一个未阻塞的消费者进程执行
				else {
					cout << "所有产品均已放入缓冲区,选择一个未阻塞的消费者进程执行" << endl;
					process_select_random = (rand()
						% subscript_unwaitedConsumer.size_list)
						+ subscript_unwaitedProducer.size_list;
				}
			}
			else {
				if (product_havePut == num_requiredProduct) {
					cout << "缓冲区内有产品,且所有产品都已经放入缓冲区,"
						"重置所有生产者进程" << endl;
					// 待优化,生产完成了不需要每次都重置生产者进程状态
					resetProducer();
					cout << "此时未阻塞生产者进程下标队列已无意义" << endl;

					// 当消费者消费完所有产品时生产消费结束
					if (products_required[subscript_requiredProduct] == '\0'
						&& product_haveConsumed == num_requiredProduct && !isGoing_producer()) {
						cout << "生产与消费均已结束" << endl;
						break;
					}
					else {
						cout << "并选取一个未阻塞的消费者进程执行" << endl;
						process_select_random = (rand()
							% subscript_unwaitedConsumer.size_list)
							+ subscript_unwaitedProducer.size_list;
					}
				}
				else {
					cout << "当前尚有产品未放入缓冲区,随机选取一个未阻塞的进程执行" << endl;
					process_select_random = (rand()
						% (subscript_unwaitedProducer.size_list
							+ subscript_unwaitedConsumer.size_list));
				}
			}
		}

		// 如果选中了生产者进程且当前有产品仍未放入缓冲区就执行生产者单步
		if (process_select_random < subscript_unwaitedProducer.size_list
			&& product_havePut < num_requiredProduct) {
			cout << subscript_unwaitedProducer
				.getValueBySubscript(process_select_random)
				<< "号生产者被选中执行\n" << endl;
			oneStep_producer(subscript_unwaitedProducer
				.getValueBySubscript(process_select_random));
		}

		// 如果选中了消费者就执行消费者单步
		else if (process_select_random >= subscript_unwaitedProducer.size_list) {
			cout << subscript_unwaitedConsumer
				.getValueBySubscript(process_select_random
					- subscript_unwaitedProducer.size_list)
				<< "号消费者被选中执行\n" << endl;
			oneStep_consumer(subscript_unwaitedConsumer
				.getValueBySubscript(process_select_random
					- subscript_unwaitedProducer.size_list));
		}
		else {
			cout << "本轮随机数为:" << process_select_random << endl;
			cout << "本轮未能唤醒进程" << endl;
		}
		cout << "本轮已放入缓冲区的产品数量为: " << product_havePut
			<< " 已经消费的商品数目为: " << product_haveConsumed
			<< " 目前缓冲区内产品数量为: " << bufferPC.size()
			<< "\n目前未阻塞的生产者进程下标为: ";
		subscript_unwaitedProducer.showList();
		cout << "目前未阻塞的消费者进程下标为: ";
		subscript_unwaitedConsumer.showList();

		showProcessSituation();
		//Sleep(1000);	// 程序延迟1s,模拟延迟
		cout << endl;
	}
}


/* 生产者单步
   根据断点确定接下来该做哪一步了
*/
void SM::oneStep_producer(int subscript_whichProducer) {
	switch (producer[subscript_whichProducer].breakPoint) {
		// 断点为0时获取生产锁
	case 0:
		cout << producer[subscript_whichProducer].name
			<< "已就绪,正在获取生产锁" << endl;
		if (products_required[subscript_requiredProduct] == '\0')
			cout << "当前产品均已生产完成,无需获取生产锁" << endl;
		else {
			P(subscript_whichProducer);
			producer[subscript_whichProducer].breakPoint =
				(producer[subscript_whichProducer].breakPoint + 1) % 3;
		}
		break;
		// 断点为1时执行生产操作
	case 1:
		cout << producer[subscript_whichProducer].name
			<< "正在生产" << endl;
		if (producer[subscript_whichProducer].status != "阻塞态") {
			producer[subscript_whichProducer].status = "运行态";
			produce(subscript_whichProducer);
			producer[subscript_whichProducer].breakPoint =
				(producer[subscript_whichProducer].breakPoint + 1) % 3;
		}
		else {
			cout << "该进程阻塞中,请查看原因" << endl;
		}
		break;
		// 断点为2时执行将产品放入缓冲区并释放消费锁的操作,进程变为就绪态
	case 2:
		cout << producer[subscript_whichProducer].name
			<< "正在将产品放入缓冲区" << endl;
		if (producer[subscript_whichProducer].status != "阻塞态") {
			put(subscript_whichProducer);
			V(subscript_whichProducer);		// 释放一个消费互斥量
			producer[subscript_whichProducer].status = "就绪态";
			producer[subscript_whichProducer].breakPoint =
				(producer[subscript_whichProducer].breakPoint + 1) % 3;
		}
		else {
			cout << "该进程阻塞中,请查看原因" << endl;
		}
		break;
	}
}

void SM::oneStep_consumer(int subscript_whichConsumer) {
	switch (consumer[subscript_whichConsumer].breakPoint) {
		// 断点为0时获取消费锁
	case 0:
		cout << consumer[subscript_whichConsumer].name
			<< "已就绪,正在获取消费锁" << endl;
		P(subscript_whichConsumer + producer.size());
		consumer[subscript_whichConsumer].breakPoint =
			(consumer[subscript_whichConsumer].breakPoint + 1) % 3;
		break;
		// 断点为1时执行从缓冲区取产品操作
	case 1:
		cout << consumer[subscript_whichConsumer].name
			<< "正从缓冲区获取产品" << endl;
		if (consumer[subscript_whichConsumer].status != "阻塞态") {
			consumer[subscript_whichConsumer].status = "运行态";
			GET(subscript_whichConsumer);
			consumer[subscript_whichConsumer].breakPoint =
				(consumer[subscript_whichConsumer].breakPoint + 1) % 3;
		}
		else {
			cout << "该进程阻塞中,请查看原因" << endl;
		}
		break;
		// 断点为2时执行消费操作并释放生产锁,程序变为就绪态
	case 2:
		cout << consumer[subscript_whichConsumer].name
			<< "正在消费之后释放生产锁" << endl;
		if (consumer[subscript_whichConsumer].status != "阻塞态") {
			consume(subscript_whichConsumer);
			V(subscript_whichConsumer + producer.size());		// 释放一个生产互斥量
			consumer[subscript_whichConsumer].status = "就绪态";
			consumer[subscript_whichConsumer].breakPoint =
				(consumer[subscript_whichConsumer].breakPoint + 1) % 3;
		}
		else {
			cout << "该进程阻塞中,请查看原因" << endl;
		}
		break;
	}
}

void SM::resetProducer() {
	for (int i = 0; i < producer.size(); i++) {
		producer[i].status = "就绪态";					// 初始状态设为就绪态
		producer[i].reason_wait = "";					// 等待原因为空
		producer[i].breakPoint = 0;						// 断点为0
	}
	cout << "所有生产者进程已被重置" << endl;

}
