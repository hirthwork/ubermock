/*
 * test-ternary.cpp         -- ternary mocks tests
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

#include <ubermock/registrar.hpp>
#include <ubermock/ubermock.hpp>

#include "mockapi.hpp"

#define BOOST_TEST_MODULE TernaryTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ternary_original_values)
{
    BOOST_REQUIRE_EQUAL(Ternary(2, 3, 0), 3);
    BOOST_REQUIRE_EQUAL(TMockApi().Ternary(2, 3, 0), 13);
    BOOST_REQUIRE_EQUAL(TMockApi().TernaryConst(2, 3, 0), 23);
}

BOOST_AUTO_TEST_CASE(ternary_global)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, int a, int b, int c)
        {
            return a + b + c == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(Ternary, TCheck::Check,
        NUberMock::MakeRepeatedResult(6));
    BOOST_REQUIRE_EQUAL(Ternary(2, 2, 0), 3);
    BOOST_REQUIRE_EQUAL(Ternary(2, 3, 0), 6);
}

BOOST_AUTO_TEST_CASE(ternary_global_simple)
{
    struct TCheck
    {
        static bool Check(int a, int b, int c)
        {
            return a + b + c == 5;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(Ternary, TCheck::Check,
        NUberMock::MakeRepeatedResult(8));
    BOOST_REQUIRE_EQUAL(Ternary(2, 3, 1), 3);
    BOOST_REQUIRE_EQUAL(Ternary(3, 1, 1), 8);
}

BOOST_AUTO_TEST_CASE(ternary_member)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, TMockApi*, int a,
            int b, int c)
        {
            return a + b + c == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(&TMockApi::Ternary, TCheck::Check,
        NUberMock::MakeRepeatedResult(16));
    BOOST_REQUIRE_EQUAL(TMockApi().Ternary(2, 0, 1), 13);
    BOOST_REQUIRE_EQUAL(TMockApi().Ternary(3, 3, -1), 16);
}

BOOST_AUTO_TEST_CASE(ternary_member_simple)
{
    struct TCheck
    {
        static bool Check(TMockApi*, int a, int b, int c)
        {
            return a + b + c == 5;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(&TMockApi::Ternary,
        TCheck::Check, NUberMock::MakeRepeatedResult(17));
    BOOST_REQUIRE_EQUAL(TMockApi().Ternary(3, 3, 3), 13);
    BOOST_REQUIRE_EQUAL(TMockApi().Ternary(2, 2, 1), 17);
}

BOOST_AUTO_TEST_CASE(ternary_const_member)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, const TMockApi*,
            int a, int b, int c)
        {
            return a + b + c == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(&TMockApi::TernaryConst, TCheck::Check,
        NUberMock::MakeRepeatedResult(26));
    BOOST_REQUIRE_EQUAL(TMockApi().TernaryConst(3, 0, 3), 23);
    BOOST_REQUIRE_EQUAL(TMockApi().TernaryConst(-1, -1, 7), 26);
}

BOOST_AUTO_TEST_CASE(ternary_const_member_simple)
{
    struct TCheck
    {
        static bool Check(const TMockApi*, int a, int b, int c)
        {
            return a + b + c == 5;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(&TMockApi::TernaryConst,
        TCheck::Check, NUberMock::MakeRepeatedResult(27));
    BOOST_REQUIRE_EQUAL(TMockApi().TernaryConst(6, -1, 1), 23);
    BOOST_REQUIRE_EQUAL(TMockApi().TernaryConst(6, -1, 0), 27);
}

