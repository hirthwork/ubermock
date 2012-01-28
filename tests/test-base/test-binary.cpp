/*
 * test-binary.cpp          -- binary mocks tests
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
#include <range/range.hpp>

#include "mockapi.hpp"

#define BOOST_TEST_MODULE BinaryTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(binary_original_values)
{
    BOOST_REQUIRE_EQUAL(Binary(2, 3), 2);
    BOOST_REQUIRE_EQUAL(TMockApi().Binary(2, 3), 12);
    BOOST_REQUIRE_EQUAL(TMockApi().BinaryConst(2, 3), 22);
}

BOOST_AUTO_TEST_CASE(binary_global)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, int a, int b)
        {
            return a + b == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(Binary, TCheck::Check,
        NRange::SingleValue(6));
    BOOST_REQUIRE_EQUAL(Binary(2, 2), 2);
    BOOST_REQUIRE_EQUAL(Binary(2, 3), 6);
}

BOOST_AUTO_TEST_CASE(binary_global_simple)
{
    struct TCheck
    {
        static bool Check(int a, int b)
        {
            return a + b == 5;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(Binary, TCheck::Check,
        NRange::SingleValue(8));
    BOOST_REQUIRE_EQUAL(Binary(2, 4), 2);
    BOOST_REQUIRE_EQUAL(Binary(3, 2), 8);
}

BOOST_AUTO_TEST_CASE(binary_member)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, TMockApi*, int a,
            int b)
        {
            return a + b == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(&TMockApi::Binary, TCheck::Check,
        NRange::SingleValue(16));
    BOOST_REQUIRE_EQUAL(TMockApi().Binary(3, 0), 12);
    BOOST_REQUIRE_EQUAL(TMockApi().Binary(1, 4), 16);
}

BOOST_AUTO_TEST_CASE(binary_member_simple)
{
    struct TCheck
    {
        static bool Check(TMockApi*, int a, int b)
        {
            return a + b == 5;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(&TMockApi::Binary, TCheck::Check,
        NRange::SingleValue(17));
    BOOST_REQUIRE_EQUAL(TMockApi().Binary(3, 3), 12);
    BOOST_REQUIRE_EQUAL(TMockApi().Binary(5, 0), 17);
}

BOOST_AUTO_TEST_CASE(binary_const_member)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, const TMockApi*,
            int a, int b)
        {
            return a + b == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(&TMockApi::BinaryConst, TCheck::Check,
        NRange::SingleValue(26));
    BOOST_REQUIRE_EQUAL(TMockApi().BinaryConst(6, 0), 22);
    BOOST_REQUIRE_EQUAL(TMockApi().BinaryConst(0, 5), 26);
}

BOOST_AUTO_TEST_CASE(binary_const_member_simple)
{
    struct TCheck
    {
        static bool Check(const TMockApi*, int a, int b)
        {
            return a + b == 5;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(&TMockApi::BinaryConst,
        TCheck::Check, NRange::SingleValue(27));
    BOOST_REQUIRE_EQUAL(TMockApi().BinaryConst(7, -1), 22);
    BOOST_REQUIRE_EQUAL(TMockApi().BinaryConst(6, -1), 27);
}

