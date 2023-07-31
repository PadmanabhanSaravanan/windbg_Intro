/*++

Copyright (c) 1990-98  Microsoft Corporation All Rights Reserved

Module Name:

    testapp.c

Abstract:

Environment:

    Win32 console multi-threaded application

--*/
#include <windows.h>
#include <winioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strsafe.h>
#include <sys\sioctl.h>
#include <conio.h>


BOOLEAN
ManageDriver(
    _In_ LPCTSTR  DriverName,
    _In_ LPCTSTR  ServiceName,
    _In_ USHORT   Function
    );

BOOLEAN
SetupDriverName(
    _Inout_updates_bytes_all_(BufferLength) PCHAR DriverLocation,
    _In_ ULONG BufferLength
    );

char OutputBuffer[100];
char InputBuffer[100];

int g_controlCodeForIssue;

BOOL SetControlCodeFromCmdLineArgs(ULONG argc, PCHAR argv[]);

BOOL SetControlCodeFromCmdLineArgs(ULONG argc, PCHAR argv[])
{
    UNREFERENCED_PARAMETER(argc);

    if (argc != 2)
    {
        printf("This program takes exactly one arg. Check the code for details");
    }
    
    if (0 == strcmp("test", argv[1]))
    {
        printf("test success");
    }



// void SimpleCrash();
// #define IOCTL_SIOCTL_SIMPLE_CRASH \
// CTL_CODE( SIOCTL_TYPE, 0x904, METHOD_BUFFERED, FILE_ANY_ACCESS  )

    if (0 == _stricmp("SimpleCrash", argv[1]))
    {
        g_controlCodeForIssue = IOCTL_SIOCTL_SIMPLE_CRASH;
    }


//void StackCorruption();
//#define IOCTL_SIOCTL_STACK_CORRUPTION \
//    CTL_CODE( SIOCTL_TYPE, 0x905, METHOD_BUFFERED, FILE_ANY_ACCESS  )

    if (0 == _stricmp("StackCorruption", argv[1]))
    {
        g_controlCodeForIssue = IOCTL_SIOCTL_STACK_CORRUPTION;
    }

//void StackOverflow();
//#define IOCTL_SIOCTL_STACK_OVERFLOW \
//    CTL_CODE( SIOCTL_TYPE, 0x906, METHOD_BUFFERED, FILE_ANY_ACCESS  )

    if (0 == _stricmp("StackOverflow", argv[1]))
    {
        g_controlCodeForIssue = IOCTL_SIOCTL_STACK_OVERFLOW;
    }

//void PoolCorruption();
//#define IOCTL_SIOCTL_POOL_CURRUPTION \
 //   CTL_CODE( SIOCTL_TYPE, 0x907, METHOD_BUFFERED, FILE_ANY_ACCESS  )

    if (0 == _stricmp("PoolCorruption", argv[1]))
    {
        g_controlCodeForIssue = IOCTL_SIOCTL_POOL_CURRUPTION;
    }


//void KernelHang();
//#define IOCTL_SIOCTL_KERNEL_HANG \
//    CTL_CODE( SIOCTL_TYPE, 0x908, METHOD_BUFFERED, FILE_ANY_ACCESS  )

    if (0 == _stricmp("KernelHang", argv[1]))
    {
        g_controlCodeForIssue = IOCTL_SIOCTL_KERNEL_HANG;
    }

//void SystemSlowness();
//#define IOCTL_SIOCTL_SYSTEM_SLOWNESS \
 //   CTL_CODE( SIOCTL_TYPE, 0x909, METHOD_BUFFERED, FILE_ANY_ACCESS  )

    if (0 == _stricmp("SystemSlowness", argv[1]))
    {
        g_controlCodeForIssue = IOCTL_SIOCTL_SYSTEM_SLOWNESS;
    }

//void KernelModeHighCpu();
//#define IOCTL_SIOCTL_KERNEMODE_HIGHCPU \
 //   CTL_CODE( SIOCTL_TYPE, 0x90A, METHOD_BUFFERED, FILE_ANY_ACCESS  )

    if (0 == _stricmp("KernelModeHighCpu", argv[1]))
    {
        g_controlCodeForIssue = IOCTL_SIOCTL_KERNEMODE_HIGHCPU;
    }


//void KernelModeMemoryLeak();
//#define IOCTL_SIOCTL_KERNELMODE_MEMORYLEAK \
 //   CTL_CODE( SIOCTL_TYPE, 0x90B, METHOD_BUFFERED, FILE_ANY_ACCESS  )

    if (0 == _stricmp("KernelModeMemoryLeak", argv[1]))
    {
        g_controlCodeForIssue = IOCTL_SIOCTL_KERNELMODE_MEMORYLEAK;
    }

//void EresourceLocksHang();
//#define IOCTL_SIOCTL_ERESOURCE_LOCKS_HANG \
//    CTL_CODE( SIOCTL_TYPE, 0x90C, METHOD_BUFFERED, FILE_ANY_ACCESS  )

    if (0 == _stricmp("EresourceLocksHang", argv[1]))
    {
        g_controlCodeForIssue = IOCTL_SIOCTL_ERESOURCE_LOCKS_HANG;
    }

//void SpinlockDeadlock();
//#define IOCTL_SIOCTL_SPINLOCK_DEADLOCK \
//   CTL_CODE( SIOCTL_TYPE, 0x90D, METHOD_BUFFERED, FILE_ANY_ACCESS  )

    if (0 == _stricmp("SpinlockDeadlock", argv[1]))
    {
        g_controlCodeForIssue = IOCTL_SIOCTL_SPINLOCK_DEADLOCK;
    }

//void WaitingForIrp();
//#define IOCTL_SIOCTL_PENDING_IRP \
 //   CTL_CODE( SIOCTL_TYPE, 0x90E, METHOD_BUFFERED, FILE_ANY_ACCESS  )

    if (0 == _stricmp("WaitingForIrp", argv[1]))
    {
        g_controlCodeForIssue = IOCTL_SIOCTL_PENDING_IRP;
    }








    return 1;
}

VOID __cdecl
main(
    _In_ ULONG argc,
    _In_reads_(argc) PCHAR argv[]
    )
{
    HANDLE hDevice;
    BOOL bRc;
    ULONG bytesReturned;
    DWORD errNum = 0;
    TCHAR driverLocation[MAX_PATH];

    //UNREFERENCED_PARAMETER(argc);
    //UNREFERENCED_PARAMETER(argv);

    SetControlCodeFromCmdLineArgs(argc, argv);

    //
    // open the device
    //

    if ((hDevice = CreateFile( "\\\\.\\IoctlTest",
                            GENERIC_READ | GENERIC_WRITE,
                            0,
                            NULL,
                            CREATE_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL)) == INVALID_HANDLE_VALUE) {

        errNum = GetLastError();

        if (errNum != ERROR_FILE_NOT_FOUND) {

            printf("CreateFile failed : %d\n", errNum);

            return ;
        }

        //
        // The driver is not started yet so let us the install the driver.
        // First setup full path to driver name.
        //

        if (!SetupDriverName(driverLocation, sizeof(driverLocation))) {

            return ;
        }

        if (!ManageDriver(DRIVER_NAME,
                          driverLocation,
                          DRIVER_FUNC_INSTALL
                          )) {

            printf("Unable to install driver.\n");

            //
            // Error - remove driver.
            //

            ManageDriver(DRIVER_NAME,
                         driverLocation,
                         DRIVER_FUNC_REMOVE
                         );

            return;
        }

        hDevice = CreateFile( "\\\\.\\IoctlTest",
                            GENERIC_READ | GENERIC_WRITE,
                            0,
                            NULL,
                            CREATE_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);

        if ( hDevice == INVALID_HANDLE_VALUE ){
            printf ( "Error: CreatFile Failed : %d\n", GetLastError());
            return;
        }

    }

    //
    // Printing Input & Output buffer pointers and size
    //

    printf("InputBuffer Pointer = %p, BufLength = %Iu\n", InputBuffer,
                        sizeof(InputBuffer));
    printf("OutputBuffer Pointer = %p BufLength = %Iu\n", OutputBuffer,
                                sizeof(OutputBuffer));
    //
    // Performing METHOD_BUFFERED
    //

    StringCbCopy(InputBuffer, sizeof(InputBuffer),
        "This String is from User Application; using METHOD_BUFFERED");

    printf("\nCalling DeviceIoControl METHOD_BUFFERED:\n");

    memset(OutputBuffer, 0, sizeof(OutputBuffer));

    bRc = DeviceIoControl ( hDevice,
                            (DWORD) g_controlCodeForIssue,
                            &InputBuffer,
                            (DWORD) strlen ( InputBuffer )+1,
                            &OutputBuffer,
                            sizeof( OutputBuffer),
                            &bytesReturned,
                            NULL
                            );

    if ( !bRc )
    {
        printf ( "Error in DeviceIoControl : %d", GetLastError());
        return;

    }
    printf("    OutBuffer (%d): %s\n", bytesReturned, OutputBuffer);
    _getch();
    //
    // Performing METHOD_NEITHER
    //

    //

    //printf("\nCalling DeviceIoControl METHOD_NEITHER\n");

    //StringCbCopy(InputBuffer, sizeof(InputBuffer),
    //           "This String is from User Application; using METHOD_NEITHER");
    //memset(OutputBuffer, 0, sizeof(OutputBuffer));

    //bRc = DeviceIoControl ( hDevice,
    //                        (DWORD) IOCTL_SIOCTL_METHOD_NEITHER,
    //                        &InputBuffer,
    //                        (DWORD) strlen ( InputBuffer )+1,
    //                        &OutputBuffer,
    //                        sizeof( OutputBuffer),
    //                        &bytesReturned,
    //                        NULL
    //                        );

    //if ( !bRc )
    //{
    //    printf ( "Error in DeviceIoControl : %d\n", GetLastError());
    //    return;

    //}

    //printf("    OutBuffer (%d): %s\n", bytesReturned, OutputBuffer);

    ////
    //// Performing METHOD_IN_DIRECT
    ////

    //printf("\nCalling DeviceIoControl METHOD_IN_DIRECT\n");

    //StringCbCopy(InputBuffer, sizeof(InputBuffer),
    //           "This String is from User Application; using METHOD_IN_DIRECT");
    //StringCbCopy(OutputBuffer, sizeof(OutputBuffer),
    //           "This String is from User Application in OutBuffer; using METHOD_IN_DIRECT");

    //bRc = DeviceIoControl ( hDevice,
    //                        (DWORD) IOCTL_SIOCTL_METHOD_IN_DIRECT,
    //                        &InputBuffer,
    //                        (DWORD) strlen ( InputBuffer )+1,
    //                        &OutputBuffer,
    //                        sizeof( OutputBuffer),
    //                        &bytesReturned,
    //                        NULL
    //                        );

    //if ( !bRc )
    //{
    //    printf ( "Error in DeviceIoControl : %d", GetLastError());
    //    return;
    //}

    //printf("    Number of bytes transfered from OutBuffer: %d\n",
    //                                bytesReturned);

    ////
    //// Performing METHOD_OUT_DIRECT
    ////

    //printf("\nCalling DeviceIoControl METHOD_OUT_DIRECT\n");
    //StringCbCopy(InputBuffer, sizeof(InputBuffer),
    //           "This String is from User Application; using METHOD_OUT_DIRECT");
    //memset(OutputBuffer, 0, sizeof(OutputBuffer));
    //bRc = DeviceIoControl ( hDevice,
    //                        (DWORD) IOCTL_SIOCTL_METHOD_OUT_DIRECT,
    //                        &InputBuffer,
    //                        (DWORD) strlen ( InputBuffer )+1,
    //                        &OutputBuffer,
    //                        sizeof( OutputBuffer),
    //                        &bytesReturned,
    //                        NULL
    //                        );

    //if ( !bRc )
    //{
    //    printf ( "Error in DeviceIoControl : %d", GetLastError());
    //    return;
    //}

    //printf("    OutBuffer (%d): %s\n", bytesReturned, OutputBuffer);

    CloseHandle ( hDevice );

    //
    // Unload the driver.  Ignore any errors.
    //

    ManageDriver(DRIVER_NAME,
                 driverLocation,
                 DRIVER_FUNC_REMOVE
                 );


    //
    // close the handle to the device.
    //

}


