// CppDll.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "CppDll.h"
#include <tchar.h>
#include <Objbase.h>
#include "ReadConfig.h"
#include <stdio.h>
#define THREADCOUNT 4 

HANDLE ghWriteEvent;
HANDLE *ghThreads;

CCppDll myDllGlobalObject;
// This is an example of an exported variable
CPPDLL_API int nCppDll=0;

// This is an example of an exported function.
CPPDLL_API int fnCppDll(void)
{
    return 0;
}
#define BUFSIZE 4096
#define VARNAME TEXT("MyVariable")
// This is the constructor of a class that has been exported.
CCppDll::CCppDll()
{
    //__asm int 3
    //ReadConfigFromReg();

    ghWriteEvent = OpenEvent(EVENT_ALL_ACCESS, 0, TEXT("WriteEvent"));

    if (!SetEvent(ghWriteEvent))
    {
        //printf("SetEvent failed (%d)\n", GetLastError());
        return;
    }

    LPTSTR pszOldVal = (LPTSTR)malloc(BUFSIZE * sizeof(TCHAR));

    GetEnvironmentVariable(VARNAME, pszOldVal, BUFSIZE);

    TCHAR threadids[100] = { 0 };

    swscanf_s(pszOldVal, _T("%X"), &ghThreads,1);

    WaitForMultipleObjects(
        THREADCOUNT,   // number of handles in array
        ghThreads,     // array of thread handles
        TRUE,          // wait until all are signaled
        INFINITE);



    return;
}
