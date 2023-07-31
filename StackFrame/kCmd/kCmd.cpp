// kCmd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void fun4(int w)
{
	int fun4local1 = 55;
	int fun4local2 = 66;
	int fun4local3 = 77;
	int fun4local4 = 88;
	printf("%d",w);
	fun4local4 = 0;
	fun4local4 = fun4local4 / fun4local4;
}

void __stdcall fun3(int i, int j)
{
	int fun3local1 = 51;
	int fun3local2 = 62;
	int fun3local3 = 73;
	int fun3local4 = 84;
	fun4(i+j);
}

void fun2(int x, int y, int z)
{
	int fun2local1 = 5;
	int fun2local2 = 6;
	int fun2local3 = 7;
	int fun2local4 = 8;
	fun3(x+100,y+z);
}

void fun1(int a, int b, int c, int d)
{
	int fun1local1 = 1;
	int fun1local2 = 2;
	int fun1local3 = 3;
	int fun1local4 = 4;


	fun2(a+10, b+20, c+30+d);
}

int _tmain(int argc, _TCHAR* argv[])
{
	fun1(100,200,300,139);
	return 0;
}

