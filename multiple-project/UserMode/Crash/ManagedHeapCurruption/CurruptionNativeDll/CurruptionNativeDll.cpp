// CurruptionNativeDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CurruptionNativeDll.h"
#include <stdio.h>


// This is an example of an exported variable
CURRUPTIONNATIVEDLL_API int nCurruptionNativeDll=0;

// This is an example of an exported function.
CURRUPTIONNATIVEDLL_API int fnCurruptionNativeDll(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see CurruptionNativeDll.h for the class definition
CCurruptionNativeDll::CCurruptionNativeDll()
{
	return;
}

extern "C"
{
	__declspec(dllexport) VOID InitBuffer(BYTE* ptr, INT size)
	{
		printf ("from dll \n");
		Sleep(2000);
		for(int i=0; i<25500000; i=i+1000)
		{
			printf ("from dll loop %d \n", i);
			memset(&ptr[i],i,1000);
		}
		Sleep(20000);
	}
}
