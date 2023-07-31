 // UserModeStackTrace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>


int _tmain(int argc, _TCHAR* argv[])
{
	char*ptr1 = (char*)malloc(4);

	__asm int 3

	return 0;
}


