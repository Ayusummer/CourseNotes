#include "DS.h"

#include<iostream>

int main()
{
	VirtualStorage vs;
	vs.initJob();
	vs.initCommand();
	vs.SimulateAddressTranslationANDPageFault();

	system("pause");
	return 0;
}
