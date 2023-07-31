// CppFromWindbg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
//#include ".\\CppDll\\CppDll.h"

//EVENT g_GoAheadEvent;
/*
DWORD WINAPI MyThreadFunction(LPVOID lpParam);
DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    HINSTANCE hinstLib;
    //MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    // Get a handle to the DLL module.

    hinstLib = LoadLibrary(TEXT("MyPuts.dll"));

    // If the handle is valid, try to get the function address.

    if (hinstLib != NULL)
    {
        //ProcAdd = (MYPROC)GetProcAddress(hinstLib, "myPuts");

        // If the function address is valid, call the function.

        //if (NULL != ProcAdd)
       // {
       //     fRunTimeLinkSuccess = TRUE;
       //     (ProcAdd)();
       // }
        // Free the DLL module.

        fFreeResult = FreeLibrary(hinstLib);
    }

    // If unable to call the DLL function, use an alternative.
    if (!fRunTimeLinkSuccess)
        printf("Message printed from executable\n");

    return 0;

}


#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#define MAX_THREADS 3
#define BUF_SIZE 255


void ErrorHandler(LPTSTR lpszFunction);

// Sample custom data structure for threads to use.
// This is passed by void pointer so it can be any data type
// that can be passed using a single void pointer (LPVOID).
typedef struct MyData {
    int val1;
    int val2;
} MYDATA, * PMYDATA;


int ReadConfigFromReg()
{
    PMYDATA pDataArray[MAX_THREADS];
    DWORD   dwThreadIdArray[MAX_THREADS];
    HANDLE  hThreadArray[MAX_THREADS];

    // Create MAX_THREADS worker threads.

    for (int i = 0; i < MAX_THREADS; i++)
    {
        // Allocate memory for thread data.

        pDataArray[i] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
            sizeof(MYDATA));

        if (pDataArray[i] == NULL)
        {
            // If the array allocation fails, the system is out of memory
            // so there is no point in trying to print an error message.
            // Just terminate execution.
            ExitProcess(2);
        }

        // Generate unique data for each thread to work with.

        pDataArray[i]->val1 = i;
        pDataArray[i]->val2 = i + 100;

        // Create the thread to begin execution on its own.

        hThreadArray[i] = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size  
            MyThreadFunction,       // thread function name
            pDataArray[i],          // argument to thread function 
            0,                      // use default creation flags 
            &dwThreadIdArray[i]);   // returns the thread identifier 


        // Check the return value for success.
        // If CreateThread fails, terminate execution. 
        // This will automatically clean up threads and memory. 

        if (hThreadArray[i] == NULL)
        {
            //ErrorHandler(TEXT("CreateThread"));
            ExitProcess(3);
        }
    } // End of main thread creation loop.

    // Wait until all threads have terminated.

    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

    // Close all thread handles and free memory allocations.

    for (int i = 0; i < MAX_THREADS; i++)
    {
        CloseHandle(hThreadArray[i]);
        if (pDataArray[i] != NULL)
        {
            HeapFree(GetProcessHeap(), 0, pDataArray[i]);
            pDataArray[i] = NULL;    // Ensure address is not reused.
        }
    }

    return 0;
}






void ErrorHandler(LPTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code.

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    // Display the error message.

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    // Free error-handling buffer allocations.

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}



int main()
{
    __asm int 3

    HINSTANCE hinstLib;
    //MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    // Get a handle to the DLL module.

    hinstLib = LoadLibrary(TEXT("cppdll.dll"));
    //CCppDll myDllLocalObject;
    std::cout << "Hello World!\n";
}
*/

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define THREADCOUNT 4 

#define BUFSIZE 4096
#define VARNAME TEXT("MyVariable")

HANDLE ghWriteEvent;
HANDLE ghThreads[THREADCOUNT];

DWORD WINAPI ThreadProc(LPVOID);

void CreateEventsAndThreads(void)
{
    int i;
    DWORD dwThreadID;

    // Create a manual-reset event object. The write thread sets this
    // object to the signaled state when it finishes writing to a 
    // shared buffer. 

    ghWriteEvent = CreateEvent(
        NULL,               // default security attributes
        TRUE,               // manual-reset event
        FALSE,              // initial state is nonsignaled
        TEXT("WriteEvent")  // object name
    );

    if (ghWriteEvent == NULL)
    {
        printf("CreateEvent failed (%d)\n", GetLastError());
        return;
    }

    // Create multiple threads to read from the buffer.

    for (i = 0; i < THREADCOUNT; i++)
    {
        // TODO: More complex scenarios may require use of a parameter
        //   to the thread procedure, such as an event per thread to  
        //   be used for synchronization.
        ghThreads[i] = CreateThread(
            NULL,              // default security
            0,                 // default stack size
            ThreadProc,        // name of the thread function
            NULL,              // no thread parameters
            0,                 // default startup flags
            &dwThreadID);

        if (ghThreads[i] == NULL)
        {
            printf("CreateThread failed (%d)\n", GetLastError());
            return;
        }

        TCHAR threadids[100] = { 0 };

        wsprintf(threadids, _T("%X"), ghThreads);



        SetEnvironmentVariable(VARNAME, threadids);
    }
}

void WriteToBuffer(VOID)
{
    // TODO: Write to the shared buffer.

    printf("Main thread writing to the shared buffer...\n");

    // Set ghWriteEvent to signaled

    if (!SetEvent(ghWriteEvent))
    {
        printf("SetEvent failed (%d)\n", GetLastError());
        return;
    }
}

void CloseEvents()
{
    // Close all event handles (currently, only one global handle).

    CloseHandle(ghWriteEvent);
}

int main(void)
{
    DWORD dwWaitResult;

    // TODO: Create the shared buffer

    // Create events and THREADCOUNT threads to read from the buffer

    CreateEventsAndThreads();

    // At this point, the reader threads have started and are most
    // likely waiting for the global event to be signaled. However, 
    // it is safe to write to the buffer because the event is a 
    // manual-reset event.

   // WriteToBuffer();

    printf("Main thread waiting for threads to exit...\n");

    // The handle for each thread is signaled when the thread is
    // terminated.
    //dwWaitResult = WaitForMultipleObjects(
    //    THREADCOUNT,   // number of handles in array
    //    ghThreads,     // array of thread handles
    //    TRUE,          // wait until all are signaled
    //    INFINITE);


    HINSTANCE hinstLib;
    //MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    // Get a handle to the DLL module.

    hinstLib = LoadLibrary(TEXT("cppdll.dll"));
    //CCppDll myDllLocalObject;
    std::cout << "Hello World!\n";

    //switch (dwWaitResult)
    //{
    //    // All thread objects were signaled
    //case WAIT_OBJECT_0:
    //    printf("All threads ended, cleaning up for application exit...\n");
    //    break;

    //    // An error occurred
    //default:
    //    printf("WaitForMultipleObjects failed (%d)\n", GetLastError());
    //    return 1;
    //}

    // Close the events to clean up

    CloseEvents();

    return 0;
}

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
    // lpParam not used in this example.
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    printf("Thread %d waiting for write event...\n", GetCurrentThreadId());

    dwWaitResult = WaitForSingleObject(
        ghWriteEvent, // event handle
        INFINITE);    // indefinite wait


    HINSTANCE hinstLib;
    //MYPROC ProcAdd;
    BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

    // Get a handle to the DLL module.

    hinstLib = LoadLibrary(TEXT("myPuts.dll"));
    //CCppDll myDllLocalObject;
    std::cout << "Hello World!\n";

    switch (dwWaitResult)
    {
        // Event object was signaled
    case WAIT_OBJECT_0:
        //
        // TODO: Read from the shared buffer
        //
        printf("Thread %d reading from buffer\n",
            GetCurrentThreadId());
        break;

        // An error occurred
    default:
        printf("Wait error (%d)\n", GetLastError());
        return 0;
    }

    // Now that we are done reading the buffer, we could use another
    // event to signal that this thread is no longer reading. This
    // example simply uses the thread handle for synchronization (the
    // handle is signaled when the thread terminates.)

    printf("Thread %d exiting\n", GetCurrentThreadId());
    return 1;
}