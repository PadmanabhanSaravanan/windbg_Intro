#include "stdafx.h"


#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

CRITICAL_SECTION CriticalSection1; //pink
CRITICAL_SECTION CriticalSection2; //blue



DWORD WINAPI MyThreadFunction1(LPVOID lpParameter)
{

	// Request ownership of the critical section.
	EnterCriticalSection(&CriticalSection1); //pink
	Sleep(5000);
	EnterCriticalSection(&CriticalSection2); //blue

	// Access the shared resource.

	// Release ownership of the critical section.
	LeaveCriticalSection(&CriticalSection1);
	EnterCriticalSection(&CriticalSection2);

	return 1;
}


DWORD WINAPI MyThreadFunction2(LPVOID lpParameter)
{

	// Request ownership of the critical section.
	EnterCriticalSection(&CriticalSection2); //blue
	Sleep(5000);
	EnterCriticalSection(&CriticalSection1); //pink

	// Access the shared resource.

	// Release ownership of the critical section.
	LeaveCriticalSection(&CriticalSection2);
	EnterCriticalSection(&CriticalSection1);

	return 1;
}



int _tmain()
{

	DWORD   dwThreadIdArray[2];
	HANDLE  hThreadArray[2];

	// Create MAX_THREADS worker threads.


	InitializeCriticalSectionAndSpinCount(
		&CriticalSection1,
		0
	);

	InitializeCriticalSectionAndSpinCount(
		&CriticalSection2,
		0
	);



	// Create the thread to begin execution on its own.

	hThreadArray[0] = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		MyThreadFunction1,       // thread function name
		0,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdArray[0]);   // returns the thread identifier 

	hThreadArray[1] = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		MyThreadFunction2,       // thread function name
		0,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdArray[1]);   // returns the thread identifier 


	// Check the return value for success.
	// If CreateThread fails, terminate execution. 
	// This will automatically clean up threads and memory. 


	// Wait until all threads have terminated.

	WaitForMultipleObjects(2, hThreadArray, TRUE, INFINITE);


	return 0;
}






