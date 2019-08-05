#ifndef TFORK_H
#define TFORK_H

#include <setjmp.h>
#include <unistd.h>
#include <sched.h>

#define TFORK_SYSCALL_NUM   500

/* This should be declared somewhere else, probably in the C file conatining
 * main(), and within main should be initialized as follows:
 * main_ret_addr = __builtin_return_address(0)
 */
extern void *main_ret_addr;

/* For reference, the standard content of a jmp_buf is:
 * jmp_buf.__jb[0]: rbx
 * jmp_buf.__jb[1]: rbp
 * jmp_buf.__jb[2]: r12
 * jmp_buf.__jb[3]: r13
 * jmp_buf.__jb[4]: r14
 * jmp_buf.__jb[5]: r15
 * jmp_buf.__jb[6]: rsp
 * jmp_buf.__jb[7]: rip
 */

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

/* tfork allocation: these function declaration with weak attribute and no
default implementation will make that the symbol is resolved by the dynamic
linker at runtime */
#if 0
extern void * __attribute__((weak)) tfork_malloc (size_t);
extern void * __attribute__((weak)) tfork_calloc (size_t, size_t);
extern void * __attribute__((weak)) tfork_realloc (void *, size_t);
extern void __attribute__((weak)) tfork_free (void *);
extern void * __attribute__((weak)) tfork_aligned_alloc(size_t alignment, size_t size);
#endif

extern void * __attribute__((weak)) tlsf_malloc (size_t);
extern void * __attribute__((weak)) tlsf_calloc (size_t, size_t);
extern void * __attribute__((weak)) tlsf_realloc (void *, size_t);
extern void __attribute__((weak)) tlsf_free (void *);

#endif /* ifndef TFORK_H */
