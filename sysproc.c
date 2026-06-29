
//
// The stages of system call ps : 
//  1. cps155 is a C function wrapper, declared in user.h
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
//
// sysproc.c implements process‑management system calls,
// meaning the functions that user programs invoke to
// interact with processes.
// These functions all begin with the prefix sys_
// and are called by the system‑call dispatcher in syscall.c.



#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


// sys_cps155() is the kernel‑side system call handler.
// It is the function that the syscall dispatcher (syscall()) 
// calls when the user program invokes the system call.

int
sys_cps155(void)
{
	return cps155(); // calls the REAL kernel function
}

