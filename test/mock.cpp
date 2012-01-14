#include <cstdio>
#include <cstring>

#include <functional>

#include <registrar.hpp>
#include <ubermock.hpp>

#include "hdr.hpp"

FILE* fopen(const char* path, const char* mode)
{
    return NUberMock::HandleMock(fopen, path, mode);
}

bool checker(const NBacktrace::TBacktrace&, const char* path, const char*)
{
    return !strcmp(path, "abracadabra");
}

int fclose(FILE* fd)
{
    return NUberMock::HandleMock(fclose, fd);
}

struct closeChecker:
    std::binary_function<bool, const NBacktrace::TBacktrace&, FILE*>
{
    const FILE* const Fd;
    inline closeChecker(FILE* fd)
        : Fd(fd)
    {
    }

    bool operator()(const NBacktrace::TBacktrace&, FILE* fd) const
    {
        return fd == Fd;
    }
};

const char* A::f()
{
    return NUberMock::HandleMock(&A::f, this);
}

int A::g(int a, int b) const
{
    return NUberMock::HandleMock(&A::g, this, a, b);
}

bool Afcheck(A*)
{
    return true;
}

bool Agcheck(const A*, int a, int b)
{
    return a == b;
}

int main()
{
    FILE* pf;
    {
        NUberMock::TMockRegistrar guard(fopen, checker, (FILE*)0xff);
        pf = fopen("/tmp/1", "r");
        printf("%p\n", (void*)pf);
        printf("%p\n", (void*)fopen("abracadabra", "r"));
        A a;
        {
            NUberMock::TMockRegistrar guard(fclose, closeChecker(pf), 42);
            printf("%i\n", fclose(pf));
            NUberMock::TSimpleMockRegistrar guard2(&A::f, Afcheck, "mocked A::f");
            puts(a.f());
            NUberMock::TSimpleMockRegistrar guard3(&A::g, Agcheck, 99);
            printf("%i\n", a.g(1,2));
            printf("%i\n", a.g(2,2));
            printf("%i\n", a.g(3,3));
        }
        puts(a.f());
        printf("%i\n", a.g(1,2));
        printf("%i\n", a.g(2,2));
        printf("%i\n", a.g(3,3));
        NUberMock::TSimpleMockRegistrar guard3(fclose, std::bind1st(
            std::equal_to<FILE*>(), pf), 24);
        printf("%i\n", fclose(pf));
    }
    printf("%p\n", (void*)fopen("abracadabra", "r"));
    printf("%i\n", fclose(pf));
}

