// DoubleFree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <stdlib.h>


int _tmain(int argc, _TCHAR* argv[])
{
	char*ptr1 = (char*)malloc(4);

	if ( ptr1 !=0 )
	{
		free ( ptr1 );
	}


	if ( ptr1 !=0 )
	{
		free ( ptr1 );
	}

	return 0;
}


