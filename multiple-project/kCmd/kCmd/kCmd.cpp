// kCmd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void fun4(int w)
{
	printf("%d",w);
	__asm int 3;
}

void fun3(int i, int j)
{
	fun4(i+j);
}

void fun2(int x, int y, int z)
{
	fun3(x+100,y+z);
}

void fun1(int a, int b, int c, int d)
{
	fun2(a+10, b+20, c+30+d);
}

int _tmain(int argc, _TCHAR* argv[])
{
	fun1(100,200,300,139);
	return 0;
}

