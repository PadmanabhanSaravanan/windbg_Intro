// HelloWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char string[200] = { 'A',' ','N','o','r','m','a','l',' ','T','a', 'x','i',' ','D','r','i','v','e','r' };
	printf(string);

	__asm int 3;
	return 0;
}

