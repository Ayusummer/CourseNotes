#pragma once
// 有头结点的双向循环列表
#include<iostream>
using namespace std;

template <class T>
class List;	// 前向引用,用于声明友元

// 结点类
template <class T>
class ListNode {
	T valueLN;
public:
	ListNode<T>* nextLN;
	ListNode<T>* priorLN;
	ListNode() {			// 空构造函数,用于创建头结点
		valueLN = NULL;
		nextLN = NULL;
		priorLN = NULL;
	}

	ListNode(T valueT) {		// 含参构造函数,用于创建普通结点
		valueLN = valueT;
		nextLN = NULL;
		priorLN = NULL;
	}
	T getValueLN() {		// 获取结点数据值
		return valueLN;
	}
	~ListNode() {}

	friend class List<T>;
};

// 链表类
template <class T>
class List {
public:
	ListNode<T> headLN;
	int size_list;	// 链表长度
	List() {		// 空构造函数,用于创建空链表
		headLN = ListNode<T>();
		headLN.nextLN = &headLN;
		headLN.priorLN = &headLN;
	}

	// 加入一个结点
	void addLN(T valueLN) {
		ListNode<T>* LN = new ListNode<T>(valueLN);
		LN->priorLN = headLN.priorLN;
		LN->nextLN = &headLN;
		headLN.priorLN->nextLN = LN;
		headLN.priorLN = LN;
		size_list++;	// 每加入一个节点,链表长度+1
	}
	// 删除第一个值为valueLN的节点
	void deleteByValue(T valueLN) {
		ListNode<T>* i = headLN.nextLN;
		while (i != &headLN) {
			while (i->getValueLN() != valueLN) {
				cout << i->getValueLN() << "!=" << valueLN << endl;
				i = i->nextLN;
			}
			break;
		}
		if (i != &headLN) {
			cout << "找到了" << endl;
			i->priorLN->nextLN = i->nextLN;
			i->nextLN->priorLN = i->priorLN;
			i->~ListNode();
			size_list--;
		}
	}

	// 显示列表所有元素
	void showList() {
		ListNode<T>* i = headLN.nextLN;
		while (i != headLN.priorLN) {
			cout << i->getValueLN() << " ";
			i = i->nextLN;
		}
		cout << i->getValueLN() << endl;
	}

	// 根据类似于数组下标的形式取出value
	T getValueBySubscript(int subscript) {
		ListNode<T>* i = &headLN;
		int k = -1;
		while (k < subscript) {
			i = i->nextLN;
			k++;
		}
		return i->getValueLN();
	}
};
