#include <iostream>
#include "stdafx.h"

int a = 0xFFFFFFF;

int _tmain(int argc, _TCHAR* argv[])
{
	//int a[10] = { 0 };
	//a[1100] = 100; //index out of bound

	int* ptr = 0;
	*ptr = 100;

	//int a[10] = {0};
	//a[-111111] = 100;
	
	//for (int i = 0; i < 1111111; i++)
	//{
	//	a[-i] = 100;
	//	if (i == 11111111)
	//		printf("value of i = %d", i);
	//}
	//int ptr1 = 0;
	//ptr1 = (int)&a;
	//__asm call ptr1

	//__asm mov eax,0ax

	//char *p = "hello world"
	//printf(p);
	return 0;
}
