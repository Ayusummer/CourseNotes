#pragma once

// 页表格式
struct Page {
	int num_page;		// 页号
	bool flag_load;		// 标志
	int num_block;		// 主存块号
	bool flag_change;	// 修改标志
	int location_disk;	// 在磁盘上的位置

	void setValue(int num_page, bool flag_load, int num_block, bool flag_change, int location_disk);
	void setChangeFlag(bool flag_change);
	void setLoadFlag(bool flag_load);
};

//	指令序列
struct Command {
	int num_page_operand_front;		// 第一个操作数的页号
	int number_unit_operand_front;	// 第一个操作数的单元号 
	int num_page_operand_back;		// 第二个操作数的页号
	int number_unit_operand_back;	// 第二个操作数的单元号

	void setValue(int num_page_operand_front, int number_unit_operand_front,
		int num_page_operand_back, int number_unit_operand_back);
};

// 题目中的虚拟存储管理专用类
class VirtualStorage {
public:
	Page job[7];			// 题目中的7页作业
	Command command[6];		// 题目中的6行双操作数指令
	int P[4] = { 0,1,2,3 };	// 已经装入主存的页号数组
	int k = 0;				// 初始时要置换的页面的数组下标
	void initJob();			// 按照题目要求初始化当前页表
	void initCommand();		// 按照题目要求初始化指令序列
	void SimulateAddressTranslationANDPageFault();	// 模拟地址转换和缺页中断及处理
	int	getAbsoluteAddressOfFrontOperand(int i);	// 获取指令第1个操作数的绝对地址
	int	getAbsoluteAddressOfbacktOperand(int i);	// 获取指令第2个操作数的绝对地址
	void showP();			// 显示当前装入主存的页号

};
