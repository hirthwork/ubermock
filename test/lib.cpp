#include "hdr.hpp"

const char* A::f()
{
    return "original A::f";
}

int A::g(int a, int b) const
{
    return a + b;
}

