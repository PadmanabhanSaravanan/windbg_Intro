// OstrichOnStage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h> 
#include <excpt.h>

int main()
{
    __try
    {
        std::cout << "Hello World!\n";

        int* ptr = 0;

        std::cout << "We are happy so far. But still long way to go.\n";

        *ptr = 100;

        std::cout << "Yes we did it.\n";
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        exit(1);
    }
}

