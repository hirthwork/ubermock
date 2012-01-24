/*
 * mockapi.cpp              -- implemenation of test functions to be mocked
 *
 * Copyright (C) 2012 Dmitry Potapov <potapov.d@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

void NullaryVoid()
{
    TGlobalState::Get() = 5;
}

void UnaryVoid(int& a)
{
    a = 5;
}

void BinaryVoid(int& a, int& b)
{
    a = b = 5;
}

void TernaryVoid(int& a, int& b, int& c)
{
    a = b = c = 5;
}

void QuaternaryVoid(int& a, int& b, int& c, int& d)
{
    a = b = c = d = 5;
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

