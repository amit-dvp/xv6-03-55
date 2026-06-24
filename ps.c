// Amit Serebrenikov, ID: 303423255

// ps.c is user‑level program that prints the list of running processes.
// It is the xv6 equivalent of the Unix ps command.
// It does not manage processes itself — instead, it calls a system call cps155
//
// The stages of system call ps: 
//  1. cps155 here is a C function wrapper, declared in user.h
//        - this is not the real implementation.
//        - the actual implementation is generated in usys.S.
//  2. The cps155 assembly stub defined in usys.S actually perfroms TRAP into the kernell:
//        - Loads system call number into register %eax on x86
//        - Executes the trap instruction (int $64)
//              int $T_SYSCALL is the x86 software interrupt instruction 
//              forces the CPU to trap into the kernel so a system call can be handled.
//              T_SYSCALL is defined as : #define T_SYSCALL 64
//        - Switch to kernel mode 
// 3. The trap handler sees that the trap number is T_SYSCALL and calls syscall();
//        - The handler that sees trap number 64 is 
//          inside the function trap() in trap.c
// 4. Syscall dispatcher table in syscall.c inside syscall(): 
//        - reads the syscall number
//        - looks in loo up tabler 
//        - calls the kernel implementation in sysproc.c . 
// 5. sysproc.c - kernell implementation 
//        - extracts arguments and calls the real kernel function.
// 6. proc.c - actual kernell logic
//        - this is where the real work happens
//        - this function has full access to process table.
// defs.h is the master header file for the xv6 kernel.
// It contains function prototypes for every kernel function, 
// so that all .c files inside the kernel can call each other.
 
// If the kernel function is named cps155() in proc.c, then the system call 
// that reaches it must be named sys_cps155() in sysproc.c, 
// and the user‑level wrapper must be named cps155() in user.h and usys.S



#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

extern int cps155();

int
main(int argc, char *argv[])
{
  cps155();
  exit();
}
