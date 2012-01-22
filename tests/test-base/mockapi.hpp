/*
 * mockapi.hpp              -- declaration of test functions to be mocked
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

#ifndef __MOCKAPI_HPP_2012_01_22__
#define __MOCKAPI_HPP_2012_01_22__

extern int Nullary();
extern int Unary(int);
extern int Binary(int, int);
extern int Ternary(int, int, int);
extern int Quaternary(int, int, int, int);

struct TMockApi
{
    int State_;
    TMockApi(int state = 0);
    int Nullary();
    int Unary(int);
    int Binary(int, int);
    int Ternary(int, int, int);
    int NullaryConst() const;
    int UnaryConst(int) const;
    int BinaryConst(int, int) const;
    int TernaryConst(int, int, int) const;
};

#endif

