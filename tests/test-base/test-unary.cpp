/*
 * test-unary.cpp           -- unary mocks tests
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

#define BOOST_TEST_MODULE UnaryTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(unary_original_values)
{
    BOOST_REQUIRE_EQUAL(Unary(5), 1);
    BOOST_REQUIRE_EQUAL(TMockApi().Unary(5), 11);
    BOOST_REQUIRE_EQUAL(TMockApi().UnaryConst(5), 21);
}

BOOST_AUTO_TEST_CASE(unary_global)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, int a)
        {
            return a == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(Unary, TCheck::Check,
        NUberMock::MakeRepeatedResult(6));
    BOOST_REQUIRE_EQUAL(Unary(1), 1);
    BOOST_REQUIRE_EQUAL(Unary(5), 6);
}

BOOST_AUTO_TEST_CASE(unary_global_simple)
{
    struct TCheck
    {
        static bool Check(int a)
        {
            return a == 5;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(Unary, TCheck::Check,
        NUberMock::MakeRepeatedResult(8));
    BOOST_REQUIRE_EQUAL(Unary(2), 1);
    BOOST_REQUIRE_EQUAL(Unary(5), 8);
}

BOOST_AUTO_TEST_CASE(unary_member)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, TMockApi*, int a)
        {
            return a == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(&TMockApi::Unary, TCheck::Check,
        NUberMock::MakeRepeatedResult(16));
    BOOST_REQUIRE_EQUAL(TMockApi().Unary(3), 11);
    BOOST_REQUIRE_EQUAL(TMockApi().Unary(5), 16);
}

BOOST_AUTO_TEST_CASE(unary_member_simple)
{
    struct TCheck
    {
        static bool Check(TMockApi*, int a)
        {
            return a == 5;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(&TMockApi::Unary, TCheck::Check,
        NUberMock::MakeRepeatedResult(17));
    BOOST_REQUIRE_EQUAL(TMockApi().Unary(4), 11);
    BOOST_REQUIRE_EQUAL(TMockApi().Unary(5), 17);
}

BOOST_AUTO_TEST_CASE(unary_const_member)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, const TMockApi*, int a)
        {
            return a == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(&TMockApi::UnaryConst, TCheck::Check,
        NUberMock::MakeRepeatedResult(26));
    BOOST_REQUIRE_EQUAL(TMockApi().UnaryConst(6), 21);
    BOOST_REQUIRE_EQUAL(TMockApi().UnaryConst(5), 26);
}

BOOST_AUTO_TEST_CASE(unary_const_member_simple)
{
    struct TCheck
    {
        static bool Check(const TMockApi*, int a)
        {
            return a == 5;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(&TMockApi::UnaryConst,
        TCheck::Check, NUberMock::MakeRepeatedResult(27));
    BOOST_REQUIRE_EQUAL(TMockApi().UnaryConst(7), 21);
    BOOST_REQUIRE_EQUAL(TMockApi().UnaryConst(5), 27);
}

