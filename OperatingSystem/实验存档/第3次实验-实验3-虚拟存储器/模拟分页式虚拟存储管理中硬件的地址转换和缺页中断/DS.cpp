#include "DS.h"

#include <iostream>
#include<iomanip>
using namespace std;

void VirtualStorage::initJob() {
	job[0].num_page = 0; job[0].flag = true; job[0].num_block = 5; job[0].location_disk = 011;
	job[1].num_page = 1; job[1].flag = true; job[1].num_block = 8; job[1].location_disk = 012;
	job[2].num_page = 2; job[2].flag = true; job[2].num_block = 9; job[2].location_disk = 013;
	job[3].num_page = 3; job[3].flag = true; job[3].num_block = 1; job[3].location_disk = 021;
	job[4].num_page = 4; job[4].flag = false; job[4].num_block = 0; job[4].location_disk = 022;
	job[5].num_page = 5; job[5].flag = false; job[5].num_block = 0; job[5].location_disk = 023;
	job[6].num_page = 6; job[6].flag = false; job[6].num_block = 0; job[6].location_disk = 121;
}

void VirtualStorage::initCommand() {
	command[0].num_page_operand_front = 0; command[0].number_unit_operand_front = 70;
	command[0].num_page_operand_back = 4; command[0].number_unit_operand_back = 53;
	command[1].num_page_operand_front = 1; command[1].number_unit_operand_front = 50;
	command[1].num_page_operand_back = 5; command[1].number_unit_operand_back = 23;
	command[2].num_page_operand_front = 2; command[2].number_unit_operand_front = 15;
	command[2].num_page_operand_back = 1; command[2].number_unit_operand_back = 73;
	command[3].num_page_operand_front = 3; command[3].number_unit_operand_front = 21;
	command[3].num_page_operand_back = 2; command[3].number_unit_operand_back = 78;
	command[4].num_page_operand_front = 0; command[4].number_unit_operand_front = 56;
	command[4].num_page_operand_back = 4; command[4].number_unit_operand_back = 1;
	command[5].num_page_operand_front = 6; command[5].number_unit_operand_front = 40;
	command[5].num_page_operand_back = 6; command[5].number_unit_operand_back = 84;
}

void VirtualStorage::SimulateAddressTranslationANDPageFault() {
	for (int i = 0; i < 6; i++) {
		if (job[command[i].num_page_operand_front].flag == true) {
			cout << "第" << i + 1 << "条指令: 操作数1的页号为: " << command[i].num_page_operand_front
				<< " 绝对地址为：" << setw(4) << getAbsoluteAddressOfFrontOperand(i) << "  ";
		}
		else {
			cout << setw(45) << " * " << command[i].num_page_operand_front << "  ";
		}
		if (job[command[i].num_page_operand_back].flag == true) {
			cout << "操作数2的页号为: " << command[i].num_page_operand_back
				<< " 绝对地址为：" << getAbsoluteAddressOfbacktOperand(i) << endl;
		}
		else {
			cout << setw(33) << " * " << command[i].num_page_operand_back << endl;
		}
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
