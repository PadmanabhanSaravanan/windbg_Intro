// StackCurruption.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>

int i = 0;

int _tmain(int argc, _TCHAR* argv[])
{

	int a[2] = {0};

	 
	for ( i = 0; i < 5; i++ )
	{
		*(a+i) = i*0x1000;
	}

	for ( i = 0; i < 5; i++ )
	{
		printf ( "%X at %X \n", *(a+i), (a + i));
	}


	return 0;
}

