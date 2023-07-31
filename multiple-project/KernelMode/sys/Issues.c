/*++

Copyright (c) 2020  SourceLens Consulting Private Limited - Australia
Module Name:

    Issues.c

Abstract:

    This file will create different types of hangs and crashes.
    This should be used only for educational purpose.
    Any delibrate attempt to introduce such issues in production drivers is illegal and 
    this samples or part of it should not be used with any such malicious intent.

Environment:

    Kernel mode only.

--*/

#include <wdm.h>

ERESOURCE er1, er2;

KSPIN_LOCK    g_SpinLock1;
KIRQL         g_OldIrql1;
KSPIN_LOCK    g_SpinLock2;
KIRQL         g_OldIrql2;

KEVENT g_eventNoOneSets;


VOID
KernelThreadFunc1(
    _In_ PVOID Context
);


VOID
KernelThreadFunc2(
    _In_ PVOID Context
);

VOID
KernelThreadFunc3(
    _In_ PVOID Context
);

VOID
KernelThreadFunc4(
    _In_ PVOID Context
);

VOID
KernelThreadFunc5(
    _In_ PVOID Context
)
{
    UNREFERENCED_PARAMETER(Context);
    while (1);
}

void SimpleCrash()
{
    int* ptr = 0;
    *ptr = 100;
}
void StackCorruption()
{
    int a = 0xDEADC0DE;
    int* ptr = &a;
    for (int c = 0; c < 10; c++)
    {
        *(ptr + c) = c;
    }
}

void StackOverflow()
{
    int array[3000] = { 0 };
    //UNREFERENCED_PARAMETER(array);
    if(array[1]==array[0])
    StackOverflow();
}

void PoolCorruption()
{
    int* ptr = ExAllocatePoolWithTag(NonPagedPool, 10, 'neLS');
    int* ptr1 = ExAllocatePoolWithTag(NonPagedPool, 10, 'neLS');
    int* ptr2 = ExAllocatePoolWithTag(NonPagedPool, 10, 'neLS');
    for (int c = 0; c < 100; c++)
    {
        *(ptr1 + c) = c;
    }
    ExFreePoolWithTag(ptr, 'neLS');
    ExFreePoolWithTag(ptr1, 'neLS');
    ExFreePoolWithTag(ptr2, 'neLS');
}




//hangs
void KernelHang()
{
    NTSTATUS            status = STATUS_SUCCESS;
    HANDLE              threadHandle;

    while (1)
    {

        status = PsCreateSystemThread(&threadHandle,
            (ACCESS_MASK)0,
            NULL,
            (HANDLE)0,
            NULL,
            KernelThreadFunc3,
            NULL);

        if (!NT_SUCCESS(status))
        {
            //kd print and bail out.
            return;
        }
    }

}
void SystemSlowness()
{

}
//application slowness, 
//application hang
void KernelModeHighCpu()
{
	NTSTATUS            status = STATUS_SUCCESS;
	HANDLE              threadHandle;



	status = PsCreateSystemThread(&threadHandle,
		(ACCESS_MASK)0,
		NULL,
		(HANDLE)0,
		NULL,
		KernelThreadFunc5,
		NULL);

	if (!NT_SUCCESS(status))
	{
		//kd print and bail out.
		return;
	}

}


void KernelModeMemoryLeak()
{

    while (1)
    {
        ExAllocatePoolWithTag(NonPagedPool, 10, 'neLS');
    }


}



//CPU
//Memory


void EresourceLocksHang()
{
    //From cancel safe IRP queue 

    NTSTATUS            status = STATUS_SUCCESS;
    HANDLE              threadHandle;

    ExInitializeResourceLite(
        &er1
    );
    ExInitializeResourceLite(
        &er2
    );

    //status = PsCreateSystemThread(&threadHandle,
    //    (ACCESS_MASK)0,
    //    NULL,
    //    (HANDLE)0,
    //    NULL,
    //    KernelThreadFunc1,
    //    NULL);

    //if (!NT_SUCCESS(status))
    //{
    //    //kd print and bail out.
    //    return ;
    //}


    //status = PsCreateSystemThread(&threadHandle,
    //    (ACCESS_MASK)0,
    //    NULL,
    //    (HANDLE)0,
    //    NULL,
    //    KernelThreadFunc2,
    //    NULL);

    //if (!NT_SUCCESS(status))
    //{
    //    //kd print and bail out.
    //    return;
    //}


    status = PsCreateSystemThread(&threadHandle,
        (ACCESS_MASK)0,
        NULL,
        (HANDLE)0,
        NULL,
        KernelThreadFunc3,
        NULL);

    if (!NT_SUCCESS(status))
    {
        //kd print and bail out.
        return;
    }


    status = PsCreateSystemThread(&threadHandle,
        (ACCESS_MASK)0,
        NULL,
        (HANDLE)0,
        NULL,
        KernelThreadFunc4,
        NULL);

    if (!NT_SUCCESS(status))
    {
        //kd print and bail out.
        return;
    }


    //
// Convert the Thread object handle into a pointer to the Thread object
// itself. Then close the handle.
//

	/*ObReferenceObjectByHandle(threadHandle,
		THREAD_ALL_ACCESS,
		NULL,
		KernelMode,
		&devExtension->ThreadObject,
		NULL);*/

   // ZwClose(threadHandle);

}

VOID
KernelThreadFunc1(
    _In_ PVOID Context
)
/*++

Routine Description:

    Bad thread func1
Arguments:

    Context     -- pointer to the device object

--*/
{
    UNREFERENCED_PARAMETER(Context);
    ExAcquireResourceSharedLite(&er1, TRUE);
}


VOID
KernelThreadFunc2(
    _In_ PVOID Context
)
/*++

Routine Description:

    Bad thread func1
Arguments:

    Context     -- pointer to the device object

--*/
{
    UNREFERENCED_PARAMETER(Context);
    ExAcquireResourceSharedLite(&er2, TRUE);
}


VOID
KernelThreadFunc3(
    _In_ PVOID Context
)
/*++

Routine Description:

    Bad thread func1
Arguments:

    Context     -- pointer to the device object

--*/
{
    LARGE_INTEGER   timeToWait;
    UNREFERENCED_PARAMETER(Context);
    ExAcquireResourceExclusiveLite(&er1, TRUE);
 
    timeToWait.QuadPart = -50000000;   // 10sec
    KeDelayExecutionThread(KernelMode, FALSE, &timeToWait);

    ExAcquireResourceExclusiveLite(&er2, TRUE);
}


VOID
KernelThreadFunc4(
    _In_ PVOID Context
)
/*++

Routine Description:

    Bad thread func1
Arguments:

    Context     -- pointer to the device object

--*/
{
    LARGE_INTEGER   timeToWait;
    UNREFERENCED_PARAMETER(Context);
    ExAcquireResourceExclusiveLite(&er2, TRUE);

    timeToWait.QuadPart = -50000000;   // 10sec
    KeDelayExecutionThread(KernelMode, FALSE, &timeToWait);
    ExAcquireResourceExclusiveLite(&er1, TRUE);
}



void SpinlockDeadlock()
{

    KeAcquireSpinLock(&g_SpinLock1, &g_OldIrql1);

    KeAcquireSpinLock(&g_SpinLock1, &g_OldIrql1);


    KeReleaseSpinLock(&g_SpinLock1, g_OldIrql1);

    KeReleaseSpinLock(&g_SpinLock1, g_OldIrql1);

}
void WaitingForIrp()
{
    KeInitializeEvent(&g_eventNoOneSets, SynchronizationEvent,
        FALSE);
    KeWaitForSingleObject(
        &g_eventNoOneSets,
        Executive,
        KernelMode,
        FALSE,
        NULL
    );
}
