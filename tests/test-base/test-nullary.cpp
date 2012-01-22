/*
 * test-nullary.cpp         -- nullary mocks tests
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

#include "mockapi.hpp"

#define BOOST_TEST_MODULE NullaryTest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(nullary_original_values)
{
    BOOST_REQUIRE_EQUAL(Nullary(), 0);
    BOOST_REQUIRE_EQUAL(TMockApi().Nullary(), 10);
    BOOST_REQUIRE_EQUAL(TMockApi().NullaryConst(), 20);
}

struct TGlobalState
{
    static int& Get()
    {
        static int i;
        return i;
    }
};

BOOST_AUTO_TEST_CASE(nullary_global)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&)
        {
            return TGlobalState::Get() == 5;
        }
    };

    {
        TGlobalState::Get() = 0;
        NUberMock::TMockRegistrar registrar(Nullary, TCheck::Check, 6);
        BOOST_REQUIRE_EQUAL(Nullary(), 0);
        TGlobalState::Get() = 5;
        BOOST_REQUIRE_EQUAL(Nullary(), 6);
    }
    BOOST_REQUIRE_EQUAL(Nullary(), 0);
    NUberMock::TMockRegistrar registrar(Nullary, TCheck::Check, 7);
    TGlobalState::Get() = 4;
    BOOST_REQUIRE_EQUAL(Nullary(), 0);
    TGlobalState::Get() = 5;
    BOOST_REQUIRE_EQUAL(Nullary(), 7);
}

BOOST_AUTO_TEST_CASE(nullary_global_simple)
{
    struct TCheck
    {
        static bool Check()
        {
            return TGlobalState::Get() == 6;
        }
    };

    {
        TGlobalState::Get() = 0;
        NUberMock::TSimpleMockRegistrar registrar(Nullary, TCheck::Check, 8);
        BOOST_REQUIRE_EQUAL(Nullary(), 0);
        TGlobalState::Get() = 6;
        BOOST_REQUIRE_EQUAL(Nullary(), 8);
    }
    BOOST_REQUIRE_EQUAL(Nullary(), 0);
    NUberMock::TSimpleMockRegistrar registrar(Nullary, TCheck::Check, 9);
    TGlobalState::Get() = 5;
    BOOST_REQUIRE_EQUAL(Nullary(), 0);
    TGlobalState::Get() = 6;
    BOOST_REQUIRE_EQUAL(Nullary(), 9);
    registrar.Release();
    BOOST_REQUIRE_EQUAL(Nullary(), 0);
}

BOOST_AUTO_TEST_CASE(nullary_member)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, TMockApi* pthis)
        {
            return pthis->State_ == 7;
        }
    };

    NUberMock::TMockRegistrar registrar(&TMockApi::Nullary, TCheck::Check, 16);
    BOOST_REQUIRE_EQUAL(TMockApi().Nullary(), 10);
    BOOST_REQUIRE_EQUAL(TMockApi(7).Nullary(), 16);
}

BOOST_AUTO_TEST_CASE(nullary_member_simple)
{
    struct TCheck
    {
        static bool Check(TMockApi* pthis)
        {
            return pthis->State_ == 8;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(&TMockApi::Nullary, TCheck::Check,
        17);
    BOOST_REQUIRE_EQUAL(TMockApi().Nullary(), 10);
    BOOST_REQUIRE_EQUAL(TMockApi(8).Nullary(), 17);
}

BOOST_AUTO_TEST_CASE(nullary_const_member)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, const TMockApi* pthis)
        {
            return pthis->State_ == 9;
        }
    };

    NUberMock::TMockRegistrar registrar(&TMockApi::NullaryConst, TCheck::Check,
        26);
    BOOST_REQUIRE_EQUAL(TMockApi().NullaryConst(), 20);
    BOOST_REQUIRE_EQUAL(TMockApi(9).NullaryConst(), 26);
}

BOOST_AUTO_TEST_CASE(nullary_const_member_simple)
{
    struct TCheck
    {
        static bool Check(const TMockApi* pthis)
        {
            return pthis->State_ == 10;
        }
    };

    NUberMock::TSimpleMockRegistrar registrar(&TMockApi::NullaryConst,
        TCheck::Check, 27);
    BOOST_REQUIRE_EQUAL(TMockApi().NullaryConst(), 20);
    BOOST_REQUIRE_EQUAL(TMockApi(10).NullaryConst(), 27);
}

