#include <stdio.h>
#include <tchar.h>

int testVar = 1000;

void MyTestFunc(const char* p, int a)
{
	printf(p);
	printf(" % d", a);
}

int _tmain(int argc, _TCHAR* argv[])
{
	const char* p = "hello world";
	int initi = 123;
	MyTestFunc(p, initi);

	testVar = 2000;
	MyTestFunc(p, initi);

	int a = 0;
	int b = 0;

	int c = a / b;

	return 0;
}



