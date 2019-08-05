@main_ret_addr@
type T;
@@

T main(...) {
+ main_ret_addr = __builtin_return_address(0);
...
}

@replace_fork@
@@

- fork()
+ tfork()

@add_header_main depends on main_ret_addr@
@@

#include <...>
+ #include "tfork.h"
+
+ void *main_ret_addr;

@add_header_main2 depends on main_ret_addr && !add_header_main@
@@

#include "..."
+ #include "tfork.h"
+
+ void *main_ret_addr;


@add_header depends on replace_fork && !main_ret_addr@
@@

#include <...>
+ #include "tfork.h"

@add_header2 depends on replace_fork && !main_ret_addr && !add_header@
@@

#include "..."
+ #include "tfork.h"

@replace_malloc@
expression E;
@@
- malloc(E)
+ tlsf_malloc(E)

@replace_free@
expression E;
@@
- free(E)
+ tlsf_free(E)

@replace_calloc@
expression E1, E2;
@@
- calloc(E1, E2)
+ tlsf_calloc(E1, E2)

@replace_realloc@
expression E1, E2;
@@
- realloc(E1, E2)
+ tlsf_realloc(E1, E2)

@replace_aligned_alloc@
expression E1, E2;
@@
- aligned_alloc(E1, E2)
+ tfork_aligned_alloc(E1, E2)

@replace_memalign@
expression E1, E2;
@@
- memalign(E1, E2)
+ tfork_memalign(E1, E2)

@replace_posix_memalign@
expression E1, E2, E3;
@@
- posix_memalign(E1, E2, E3)
+ tfork_posix_memalign(E1, E2, E3)

@replace_mallopt@
expression E1, E2;
@@
- mallopt(E1, E2)
+ tfork_mallopt(E1, E2)

@replace_malloc_usable_size@
expression E1;
@@
- memalign(E1)
+ tfork_memalign(E1)


@add_header_malloc depends on replace_malloc || replace_free || replace_calloc || replace_realloc || replace_aligned_alloc || replace_memalign || replace_posix_memalign || replace_mallopt || replace_malloc_usable_size && !replace_fork && !main_ret_addr@
@@
#include <...>
+ #include "tfork.h"

@add_header_malloc2 depends on replace_malloc || replace_free || replace_calloc || replace_realloc || replace_aligned_alloc || replace_memalign || replace_posix_memalign || replace_mallopt || replace_malloc_usable_size && !replace_fork && !main_ret_addr && !add_header_malloc@
@@
#include "..."
+ #include "tfork.h"
