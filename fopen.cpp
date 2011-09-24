#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

FILE* fopen(const char* path, const char* mode)
{
    if (!strcmp(path, "abracadabra"))
    {
        return (FILE*)0xface8d;
    }
    else
    {
        typedef FILE* (*symbol)(const char*, const char*);
        symbol sym = reinterpret_cast<symbol>(dlsym(RTLD_NEXT, "fopen"));
        return sym(path, mode);
    }
}

