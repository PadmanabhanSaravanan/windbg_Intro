#pragma once
/*++

Copyright (c) 2020  SourceLens Consulting Private Limited - Australia
Module Name:

    Issues.c

Abstract:

    This file will create different types of hangs and crashes.
    This should be used only for educational purpose.
    Any delibrate attempt to introduce such issues in production drivers is illegal and
    this samples should not be used for such purpose.

Environment:

    Kernel mode only.

--*/


void SimpleCrash();
void StackCorruption();
void StackOverflow();
void PoolCorruption();


//hangs
void KernelHang();
void SystemSlowness();
//application slowness, 
//application hang
void KernelModeHighCpu();
void KernelModeMemoryLeak();



//CPU
//Memory

void EresourceLocksHang();
void SpinlockDeadlock();
void WaitingForIrp();

//Irql
//eresource
//Alpc calls
//Process leak
//Thread leak

//Slow disk with disk filter
//Suspend processand alpc

