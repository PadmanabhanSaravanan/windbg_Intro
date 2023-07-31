// HeapCurruption.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>


int _tmain(int argc, _TCHAR* argv[])
{
	char*ptr1 = (char*)malloc(4);
	char*ptr2 = (char*)malloc(4);
	char*ptr3 = (char*)malloc(4);

	for ( int i = 0; i < 200; i++ )
	{
		*(ptr2-i) = 0;
	}


	free ( ptr1 );
	free ( ptr2 );
	free ( ptr3 );

	return 0;
}

