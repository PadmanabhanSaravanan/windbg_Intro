/*++

Copyright (c) 1997  Microsoft Corporation

Module Name:

    SIOCTL.H

Abstract:


    Defines the IOCTL codes that will be used by this driver.  The IOCTL code
    contains a command identifier, plus other information about the device,
    the type of access with which the file must have been opened,
    and the type of buffering.

Environment:

    Kernel mode only.

--*/

//
// Device type           -- in the "User Defined" range."
//
#define SIOCTL_TYPE 40000
//
// The IOCTL function codes from 0x800 to 0xFFF are for customer use.
//
#define IOCTL_SIOCTL_METHOD_IN_DIRECT \
    CTL_CODE( SIOCTL_TYPE, 0x900, METHOD_IN_DIRECT, FILE_ANY_ACCESS  )

#define IOCTL_SIOCTL_METHOD_OUT_DIRECT \
    CTL_CODE( SIOCTL_TYPE, 0x901, METHOD_OUT_DIRECT , FILE_ANY_ACCESS  )

#define IOCTL_SIOCTL_METHOD_BUFFERED \
    CTL_CODE( SIOCTL_TYPE, 0x902, METHOD_BUFFERED, FILE_ANY_ACCESS  )

#define IOCTL_SIOCTL_METHOD_NEITHER \
    CTL_CODE( SIOCTL_TYPE, 0x903, METHOD_NEITHER , FILE_ANY_ACCESS  )


//void SimpleCrash();
#define IOCTL_SIOCTL_SIMPLE_CRASH \
    CTL_CODE( SIOCTL_TYPE, 0x904, METHOD_BUFFERED, FILE_ANY_ACCESS  )


//void StackCorruption();
#define IOCTL_SIOCTL_STACK_CORRUPTION \
    CTL_CODE( SIOCTL_TYPE, 0x905, METHOD_BUFFERED, FILE_ANY_ACCESS  )

//void StackOverflow();
#define IOCTL_SIOCTL_STACK_OVERFLOW \
    CTL_CODE( SIOCTL_TYPE, 0x906, METHOD_BUFFERED, FILE_ANY_ACCESS  )


//void PoolCorruption();
#define IOCTL_SIOCTL_POOL_CURRUPTION \
    CTL_CODE( SIOCTL_TYPE, 0x907, METHOD_BUFFERED, FILE_ANY_ACCESS  )


//void KernelHang();
#define IOCTL_SIOCTL_KERNEL_HANG \
    CTL_CODE( SIOCTL_TYPE, 0x908, METHOD_BUFFERED, FILE_ANY_ACCESS  )

//void SystemSlowness();
#define IOCTL_SIOCTL_SYSTEM_SLOWNESS \
    CTL_CODE( SIOCTL_TYPE, 0x909, METHOD_BUFFERED, FILE_ANY_ACCESS  )

//void KernelModeHighCpu();
#define IOCTL_SIOCTL_KERNEMODE_HIGHCPU \
    CTL_CODE( SIOCTL_TYPE, 0x90A, METHOD_BUFFERED, FILE_ANY_ACCESS  )


//void KernelModeMemoryLeak();
#define IOCTL_SIOCTL_KERNELMODE_MEMORYLEAK \
    CTL_CODE( SIOCTL_TYPE, 0x90B, METHOD_BUFFERED, FILE_ANY_ACCESS  )

//void EresourceLocksHang();
#define IOCTL_SIOCTL_ERESOURCE_LOCKS_HANG \
    CTL_CODE( SIOCTL_TYPE, 0x90C, METHOD_BUFFERED, FILE_ANY_ACCESS  )

//void SpinlockDeadlock();
#define IOCTL_SIOCTL_SPINLOCK_DEADLOCK \
    CTL_CODE( SIOCTL_TYPE, 0x90D, METHOD_BUFFERED, FILE_ANY_ACCESS  )

//void WaitingForIrp();
#define IOCTL_SIOCTL_PENDING_IRP \
    CTL_CODE( SIOCTL_TYPE, 0x90E, METHOD_BUFFERED, FILE_ANY_ACCESS  )




#define DRIVER_FUNC_INSTALL     0x01
#define DRIVER_FUNC_REMOVE      0x02

#define DRIVER_NAME       "SIoctl"

