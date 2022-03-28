#include "DS.h"

#include<iostream>
#include<string>
using namespace std;

int main()
{
	VirtualStorage vs;
	vs.initJob();
	vs.initCommand();
	vs.SimulateAddressTranslationANDPageFault();

	system("pause");
	return 0;
}
