#include <ubermock/registrar.hpp>

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

    NUberMock::TMockRegistrar registrar(Quaternary, TCheck::Check, 6);
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

    NUberMock::TSimpleMockRegistrar registrar(Quaternary, TCheck::Check, 8);
    BOOST_REQUIRE_EQUAL(Quaternary(0, 2, 2, 2), 4);
    BOOST_REQUIRE_EQUAL(Quaternary(3, 2, 1, -1), 8);
}

