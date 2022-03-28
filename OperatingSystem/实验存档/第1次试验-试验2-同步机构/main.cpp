#include"DS.h"

int main() {
	SM sm;
	sm.init();					// 初始化同步机构
	sm.showProcessSituation();	// 输出状态
	sm.runningProduceConsume();	// 进行生产和消费

	system("pause");
	return 0;
}
