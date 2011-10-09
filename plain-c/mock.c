#define _GNU_SOURCE
#include <dlfcn.h>
#include <execinfo.h>
int puts(const char* s)
{
    int (*func)(const char*);
    void* bt[10];
    int size = backtrace(bt, 10);
    backtrace_symbols_fd(bt, size, 0);
    *(void**)(&func) = dlsym(RTLD_NEXT, "puts");
    if (func) {
        func(s);
    }
    return 0;
}
