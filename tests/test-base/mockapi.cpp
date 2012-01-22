#include "mockapi.hpp"

int Nullary()
{
    return 0;
}

int Unary(int)
{
    return 1;
}

int Binary(int, int)
{
    return 2;
}

int Ternary(int, int, int)
{
    return 3;
}

int Quaternary(int, int, int, int)
{
    return 4;
}

TMockApi::TMockApi(int state)
    : State_(state)
{
}

int TMockApi::Nullary()
{
    return 10;
}

int TMockApi::Unary(int)
{
    return 11;
}

int TMockApi::Binary(int, int)
{
    return 12;
}

int TMockApi::Ternary(int, int, int)
{
    return 13;
}

int TMockApi::NullaryConst() const
{
    return 20;
}

int TMockApi::UnaryConst(int) const
{
    return 21;
}

int TMockApi::BinaryConst(int, int) const
{
    return 22;
}

int TMockApi::TernaryConst(int, int, int) const
{
    return 23;
}

