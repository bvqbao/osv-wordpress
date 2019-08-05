#ifndef TFORK_H
#define TFORK_H

#include <setjmp.h>
#include <unistd.h>
#include <sched.h>

#define TFORK_SYSCALL_NUM           500
#define EXECVE_SYSCALL_NUM          501
#define WAITPID_SYSCALL_NUM         502

/* This should be declared somewhere else, probably in the C file conatining
 * main(), and within main should be initialized as follows:
 * main_ret_addr = __builtin_return_address(0)
 */
extern void *main_ret_addr;

static inline int tfork(void) {
    jmp_buf envx;

    /* setjmp returns 0 when called first (parent). When the child jumps back
     * here, it retruns 1 */
    int setjmp_ret = setjmp(envx);
    if(!setjmp_ret)
        return syscall(TFORK_SYSCALL_NUM, &envx, main_ret_addr);

    /* let the parent run first in case the child call tfork again (I'm not
     * 100% sure we are thread safe */
    sched_yield();
    return 0;
}

static inline int tfork_execve(const char *pathname, char *const argv[],
        char *const envp[]) {
    return syscall(EXECVE_SYSCALL_NUM, pathname, argv, envp);
}

static inline int tfork_waitpid(long tid, int *status, int option) {
    return syscall(WAITPID_SYSCALL_NUM, tid, status, option);
}

#endif /* ifndef TFORK_H */
