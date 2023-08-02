// StackOverflow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

void MyBadFun()
{
	int a[1000] = { 0 };
	MyBadFun();
	return;
}


int _tmain(int argc, _TCHAR* argv[])
{
	MyBadFun();
	return 0;
}

