
#include "stdafx.h"

int testVar = 1000;

void MyTestFunc(char* p, int a)
{
	printf(p);
	printf(" % d", a);
}

int _tmain(int argc, _TCHAR* argv[])
{
	char* p = "hello world";
	int initi = 123;
	MyTestFunc(p, initi);

	testVar = 2000;
	MyTestFunc(p, initi);

	return 0;
}



