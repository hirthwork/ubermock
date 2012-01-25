/*
 * test-quaternary.cpp      -- quaternary mocks tests
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

#define BOOST_TEST_MODULE QuaternaryTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(quaternary_original_values)
{
    BOOST_REQUIRE_EQUAL(Quaternary(2, 1, 1, 1), 4);
}

BOOST_AUTO_TEST_CASE(quaternary_global)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, int a, int b, int c,
            int d)
        {
            return a + b + c + d == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(Quaternary, TCheck::Check,
        NUberMock::MakeRepeatedResult(6));
    BOOST_REQUIRE_EQUAL(Quaternary(1, 1, 1, 1), 4);
    BOOST_REQUIRE_EQUAL(Quaternary(2, 1, 1, 1), 6);
}

BOOST_AUTO_TEST_CASE(quaternary_global_simple)
{
    struct TCheck
    {
        static bool Check(int a, int b, int c, int d)
        {
            return a + b + c + d == 5;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(Quaternary, TCheck::Check,
        NUberMock::MakeRepeatedResult(8));
    BOOST_REQUIRE_EQUAL(Quaternary(0, 2, 2, 2), 4);
    BOOST_REQUIRE_EQUAL(Quaternary(3, 2, 1, -1), 8);
}

