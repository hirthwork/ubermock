#include <ubermock/registrar.hpp>

#include "mockapi.hpp"

#define BOOST_TEST_MODULE BinaryTest
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

    NUberMock::TMockRegistrar registrar(Unary, TCheck::Check, 6);
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

    NUberMock::TSimpleMockRegistrar registrar(Unary, TCheck::Check, 8);
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

    NUberMock::TMockRegistrar registrar(&TMockApi::Unary, TCheck::Check, 16);
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
        17);
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
        26);
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
        TCheck::Check, 27);
    BOOST_REQUIRE_EQUAL(TMockApi().UnaryConst(7), 21);
    BOOST_REQUIRE_EQUAL(TMockApi().UnaryConst(5), 27);
}

