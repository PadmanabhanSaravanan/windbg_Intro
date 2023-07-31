// kCmd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

typedef struct 
{
	int a;
	char b;
	float c;
	int d;
} MY_STRUCT, *PMYSTRUCT;

int _tmain(int argc, _TCHAR* argv[])
{	
	MY_STRUCT myStr;

	myStr.a = 1;
	myStr.b = 10;
	myStr.c = 100.001;
	myStr.d = 1000;


	PMYSTRUCT pmyStr = &myStr;

	__asm int 3;
	return 0;
}

