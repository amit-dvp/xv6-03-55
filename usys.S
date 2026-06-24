// Amit Serebrenikov, ID: 303423255
// usys.S is assembly file that defines the user‑side stubs for every system call.
// These tiny assembly functions load the system‑call number into a
// register and trigger the trap into the kernel
// Here I defined SYSCALLCPS(name) macro that creates
// a user‑space system‑call stub for a syscall whose number is 155.

#include "syscall.h"
#include "traps.h"

// All "standard" SYSCALLS are added by this macro:
#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

// !!!! Adding "new" "SYSCALLfork(fork)" instead of SYSCALL(fork) 
//  without changing syscall.h !!! 1 is SYSCALL number, look in syscall.c
#define SYSCALLFORK(name) \
  .globl name; \
  name: \
    movl $1, %eax; \
    int $T_SYSCALL; \
    ret

// add new SYSCALL :
// This macro creates a user‑space system‑call stub for a syscall whose number is 155.

// in place of add #define SYS_cps    155 in syscall.h:
#define SYSCALLCPS(name) \
  .globl name; \
  name: \
    movl $155, %eax; \
    int $T_SYSCALL; \
    ret





SYSCALLFORK(fork) //instead of SYSCALL(fork) !!!
SYSCALLCPS(cps155)

//SYSCALL(fork)
// For each system call, xv6 expands macro:
//SYSCALL(fork) becames:
//.globl fork
//fork:
//    movl $SYS_fork, %eax   // Load the syscall number for fork into the EAX register.
//    int $T_SYSCALL
//    ret


//%eax is the standard register for passing syscall numbers on x86
//On 32‑bit x86 (the architecture xv6 uses), the convention is:
//%eax holds the system call number
//Other registers (%ebx, %ecx, %edx, etc.) hold syscall arguments


//When a user program calls read(fd, buf, n):
//C code calls the stub read() (from usys.S)

//Stub loads SYS_read into %eax
//Stub executes int $T_SYSCALL
//CPU switches to kernel mode
//Kernel syscall handler reads %eax to know which syscall to run
//Kernel executes sys_read()
//Kernel returns to user mode
//Stub returns to the user program






SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)
