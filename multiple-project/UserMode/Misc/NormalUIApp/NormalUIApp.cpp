// NormalUIApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>

int main()
{
    std::cout << "Hello World!\n";
    MessageBox(0, _T("console message box"), _T("This is UI"), 0);
}
