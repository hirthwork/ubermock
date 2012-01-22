#include <ubermock/registrar.hpp>

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

    NUberMock::TMockRegistrar registrar(Binary, TCheck::Check, 6);
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

    NUberMock::TSimpleMockRegistrar registrar(Binary, TCheck::Check, 8);
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

    NUberMock::TMockRegistrar registrar(&TMockApi::Binary, TCheck::Check, 16);
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
        17);
    BOOST_REQUIRE_EQUAL(TMockApi().Binary(3, 3), 12);
    BOOST_REQUIRE_EQUAL(TMockApi().Binary(5, 0), 17);
}

BOOST_AUTO_TEST_CASE(binary_const_member)
{
    struct TCheck
    {
        static bool Check(const NBacktrace::TBacktrace&, const TMockApi*, int a,
            int b)
        {
            return a + b == 5;
        }
    };

    NUberMock::TMockRegistrar registrar(&TMockApi::BinaryConst, TCheck::Check,
        26);
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
        TCheck::Check, 27);
    BOOST_REQUIRE_EQUAL(TMockApi().BinaryConst(7, -1), 22);
    BOOST_REQUIRE_EQUAL(TMockApi().BinaryConst(6, -1), 27);
}

