#include "DS.h"

#include <iostream>
#include<iomanip>
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>  
using namespace std;

void VirtualStorage::initJob() {
	ifstream inFile("page.csv", ios::in);
	string lineStr;
	vector<vector<int>> intArray;
	while (getline(inFile, lineStr)) {
		// 存成二维表结构  
		stringstream ss(lineStr);
		string str;
		vector<int> lineArray;
		// 按照逗号分隔  
		while (getline(ss, str, ','))
			lineArray.push_back(stoi(str));
		intArray.push_back(lineArray);
	}
	inFile.close();
	job[0].setValue(intArray[0][0], intArray[0][1], intArray[0][2], intArray[0][3], intArray[0][4]);
	job[1].setValue(intArray[1][0], intArray[1][1], intArray[1][2], intArray[1][3], intArray[1][4]);
	job[2].setValue(intArray[2][0], intArray[2][1], intArray[2][2], intArray[2][3], intArray[2][4]);
	job[3].setValue(intArray[3][0], intArray[3][1], intArray[3][2], intArray[3][3], intArray[3][4]);
	job[4].setValue(intArray[4][0], intArray[4][1], intArray[4][2], intArray[4][3], intArray[4][4]);
	job[5].setValue(intArray[5][0], intArray[5][1], intArray[5][2], intArray[5][3], intArray[5][4]);
	job[6].setValue(intArray[6][0], intArray[6][1], intArray[6][2], intArray[6][3], intArray[6][4]);
}

void VirtualStorage::initCommand() {
	ifstream inFile("InstructionsSequence_simple.csv", ios::in);
	string lineStr;
	vector<vector<int>> intArray;
	while (getline(inFile, lineStr)) {
		// 存成二维表结构  
		stringstream ss(lineStr);
		string str;
		vector<int> lineArray;
		// 按照逗号分隔  
		while (getline(ss, str, ','))
			lineArray.push_back(stoi(str));
		intArray.push_back(lineArray);
	}
	inFile.close();
	command[0].setValue(intArray[0][0], intArray[0][1], intArray[0][2], intArray[0][3]);
	command[1].setValue(intArray[1][0], intArray[1][1], intArray[1][2], intArray[1][3]);
	command[2].setValue(intArray[2][0], intArray[2][1], intArray[2][2], intArray[2][3]);
	command[3].setValue(intArray[3][0], intArray[3][1], intArray[3][2], intArray[3][3]);
	command[4].setValue(intArray[4][0], intArray[4][1], intArray[4][2], intArray[4][3]);
	command[5].setValue(intArray[5][0], intArray[5][1], intArray[5][2], intArray[5][3]);
}

void VirtualStorage::SimulateAddressTranslationANDPageFault() {
	for (int i = 0; i < 6; i++) {
		if (job[command[i].num_page_operand_front].flag_load == true) {
			cout << "第" << i + 1 << "条指令:\n  操作数1的页号为: " << command[i].num_page_operand_front
				<< " 绝对地址为：" << setw(4) << getAbsoluteAddressOfFrontOperand(i) << endl;
			job[command[i].num_page_operand_front].setChangeFlag(1);
		}
		else {
			cout << "第" << i + 1 << "条指令:\n  操作数1产生了缺页中断,该页号为: " << command[i].num_page_operand_front
				<< " 当前置换页数组下标为 " << k << " 调出页面页号为: " << job[P[k]].num_page
				<< "\n    将所需页面调入主存置换掉该页并改变置换页下标 ";
			job[P[k]].setLoadFlag(0);	// 将待置换页"调出"主存
			job[command[i].num_page_operand_front].setLoadFlag(1);	// 将该页"调入"主存
			P[k] = command[i].num_page_operand_front;				// 修改当前已经装入主存的页号数组
			k = (k + 1) % 4;			// 修改初始时要置换的页面的数组下标
			showP();
		}
		if (job[command[i].num_page_operand_back].flag_load == true) {
			cout << "  操作数2的页号为: " << command[i].num_page_operand_back
				<< " 绝对地址为：" << getAbsoluteAddressOfbacktOperand(i) << endl;
			job[command[i].num_page_operand_front].setChangeFlag(1);
		}
		else {
			cout << setw(33) << "  操作数2产生了缺页中断,操作数2的页号为: " << command[i].num_page_operand_back
				<< " 当前待置换页数组下标为 " << k << " 调出页面页号为: " << job[P[k]].num_page
				<< "\n    将所需页面调入主存置换掉该页并改变置换页下标 ";
			job[P[k]].setLoadFlag(0);	// 将待置换页"调出"主存
			job[command[i].num_page_operand_back].setLoadFlag(1);	// 将该页"调入"主存
			P[k] = command[i].num_page_operand_back;				// 修改当前已经装入主存的页号数组
			k = (k + 1) % 4;			// 修改初始时要置换的页面的数组下标
			showP();
		}
		cout << "第" << i + 1 << "条指令执行完毕\n  ";
		showP();
		cout << endl;
	}
}


int VirtualStorage::getAbsoluteAddressOfFrontOperand(int i)
{
	return job[command[i].num_page_operand_front].num_block * 128 + command[i].number_unit_operand_front;
}

int VirtualStorage::getAbsoluteAddressOfbacktOperand(int i)
{
	return job[command[i].num_page_operand_back].num_block * 128 + command[i].number_unit_operand_back;
}

void VirtualStorage::showP() {
	cout << "目前在主存中的页号为:" << P[0] << " " << P[1] << " " << P[2] << " " << P[3] << endl;
}

void Page::setValue(int num_page, bool flag_load, int num_block, bool flag_change, int location_disk) {
	this->num_page = num_page;
	this->flag_load = flag_load;
	this->num_block = num_block;
	this->flag_change = flag_change;
	this->location_disk = location_disk;
}

void Page::setChangeFlag(bool flag_change) {
	this->flag_change = flag_change;
}

void Page::setLoadFlag(bool flag_load) {
	this->flag_load = flag_load;
}

void Command::setValue(int num_page_operand_front, int number_unit_operand_front,
	int num_page_operand_back, int number_unit_operand_back) {
	this->num_page_operand_front = num_page_operand_front;
	this->number_unit_operand_front = number_unit_operand_front;
	this->num_page_operand_back = num_page_operand_back;
	this->number_unit_operand_back = number_unit_operand_back;
}
