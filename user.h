// Amit Serebrenikov, ID: 303423255
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
// user.h defines the user‑space interface to the operating system —
// it declares all system calls and user‑library functions
// that user programs are allowed to use
// For example it defines C function wrapper of cps155


struct stat;
struct rtcdate;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int cps155(void); // Amit Add function prototype to system calls

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
