#include <cstdio>
#include <cstring>

#include <functional>

#include <registrar.hpp>
#include <ubermock.hpp>

FILE* fopen(const char* path, const char* mode)
{
    return NUberMock::HandleMock(fopen, path, mode);
}

bool checker(const NReinventedWheels::TBacktrace&, const char* path, const char*)
{
    return !strcmp(path, "abracadabra");
}

int fclose(FILE* fd)
{
    return NUberMock::HandleMock(fclose, fd);
}

struct closeChecker:
    std::binary_function<bool, const NReinventedWheels::TBacktrace&, FILE*>
{
    const FILE* const Fd;
    inline closeChecker(FILE* fd)
        : Fd(fd)
    {
    }

    bool operator()(const NReinventedWheels::TBacktrace&, FILE* fd) const
    {
        return fd == Fd;
    }
};

int main()
{
    FILE* pf;
    {
        NUberMock::TMockRegistrar guard(fopen, checker, (FILE*)0xff);
        pf = fopen("/tmp/1", "r");
        printf("%p\n", (void*)pf);
        printf("%p\n", (void*)fopen("abracadabra", "r"));
        {
            NUberMock::TMockRegistrar guard2(fclose, closeChecker(pf), 42);
            printf("%i\n", fclose(pf));
        }
        NUberMock::TSimpleMockRegistrar guard3(fclose, std::bind1st(
            std::equal_to<FILE*>(), pf), 24);
        printf("%i\n", fclose(pf));
    }
    printf("%p\n", (void*)fopen("abracadabra", "r"));
    printf("%i\n", fclose(pf));
}

