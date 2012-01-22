#include <ubermock/registrar.hpp>

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

    NUberMock::TMockRegistrar registrar(Ternary, TCheck::Check, 6);
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

    NUberMock::TSimpleMockRegistrar registrar(Ternary, TCheck::Check, 8);
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

    NUberMock::TMockRegistrar registrar(&TMockApi::Ternary, TCheck::Check, 16);
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

    NUberMock::TSimpleMockRegistrar registrar(&TMockApi::Ternary, TCheck::Check,
        17);
    BOOST_REQUIRE_EQUAL(TMockApi().Ternary(3, 3, 3), 13);
    BOOST_REQUIRE_EQUAL(TMockApi().Ternary(2, 2, 1), 17);
}

BOOST_AUTO_TEST_CASE(ternary_const_member)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, const TMockApi*, int a,
            int b, int c)
        {
            return a + b + c == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(&TMockApi::TernaryConst, TCheck::Check,
        26);
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
        TCheck::Check, 27);
    BOOST_REQUIRE_EQUAL(TMockApi().TernaryConst(6, -1, 1), 23);
    BOOST_REQUIRE_EQUAL(TMockApi().TernaryConst(6, -1, 0), 27);
}

