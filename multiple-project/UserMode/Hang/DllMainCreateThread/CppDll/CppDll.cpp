// CppDll.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "CppDll.h"
#include <tchar.h>
#include <Objbase.h>
#include "ReadConfig.h"

CCppDll myDllGlobalObject;
// This is an example of an exported variable
CPPDLL_API int nCppDll=0;

// This is an example of an exported function.
CPPDLL_API int fnCppDll(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
CCppDll::CCppDll()
{
    __asm int 3
    ReadConfigFromReg();

    return;
}
