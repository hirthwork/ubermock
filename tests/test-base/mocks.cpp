#include <ubermock/ubermock.hpp>

#include "mockapi.hpp"

int Nullary()
{
    return NUberMock::HandleMock(Nullary);
}

int Unary(int a)
{
    return NUberMock::HandleMock(Unary, a);
}

int Binary(int a, int b)
{
    return NUberMock::HandleMock(Binary, a, b);
}

int Ternary(int a, int b, int c)
{
    return NUberMock::HandleMock(Ternary, a, b, c);
}

int Quaternary(int a, int b, int c, int d)
{
    return NUberMock::HandleMock(Quaternary, a, b, c, d);
}

int TMockApi::Nullary()
{
    return NUberMock::HandleMock(&TMockApi::Nullary, this);
}

int TMockApi::Unary(int a)
{
    return NUberMock::HandleMock(&TMockApi::Unary, this, a);
}

int TMockApi::Binary(int a, int b)
{
    return NUberMock::HandleMock(&TMockApi::Binary, this, a, b);
}

int TMockApi::Ternary(int a, int b, int c)
{
    return NUberMock::HandleMock(&TMockApi::Ternary, this, a, b, c);
}

int TMockApi::NullaryConst() const
{
    return NUberMock::HandleMock(&TMockApi::NullaryConst, this);
}

int TMockApi::UnaryConst(int a) const
{
    return NUberMock::HandleMock(&TMockApi::UnaryConst, this, a);
}

int TMockApi::BinaryConst(int a, int b) const
{
    return NUberMock::HandleMock(&TMockApi::BinaryConst, this, a, b);
}

int TMockApi::TernaryConst(int a, int b, int c) const
{
    return NUberMock::HandleMock(&TMockApi::TernaryConst, this, a, b, c);
}

