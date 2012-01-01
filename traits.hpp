#ifndef __TRAITS_HPP_2011_11_13__
#define __TRAITS_HPP_2011_11_13__

#include <reinvented-wheels/backtrace.hpp>

namespace NUberMock
{
    struct ICheckNullary
    {
        virtual inline ~ICheckNullary()
        {
        }

        virtual bool Check(const NReinventedWheels::TBacktrace&) const = 0;
    };

    template <class TArg>
    struct ICheckUnary
    {
        virtual inline ~ICheckUnary()
        {
        }

        virtual bool Check(const NReinventedWheels::TBacktrace&,
            TArg) const = 0;
    };

    template <class TArg1, class TArg2>
    struct ICheckBinary
    {
        virtual inline ~ICheckBinary()
        {
        }

        virtual bool Check(const NReinventedWheels::TBacktrace&,
            TArg1, TArg2) const = 0;
    };

    template <class TArg1, class TArg2, class TArg3>
    struct ICheckTernary
    {
        virtual inline ~ICheckTernary()
        {
        }

        virtual bool Check(const NReinventedWheels::TBacktrace&,
            TArg1, TArg2, TArg3) const = 0;
    };

    template <class TFunc>
    struct TFunctionTraits;

    template <class TResult>
    struct TFunctionTraits<TResult (*)()>
    {
        typedef TResult TResult_;
        typedef ICheckNullary TCheck_;
        static const unsigned Arity_ = 0;
    };

    template <class TResult, class TArg>
    struct TFunctionTraits<TResult (*)(TArg)>
    {
        typedef TResult TResult_;
        typedef TArg TArg_;
        typedef ICheckUnary<TArg> TCheck_;
        static const unsigned Arity_ = 1;
    };

    template <class TResult, class TArg1, class TArg2>
    struct TFunctionTraits<TResult (*)(TArg1, TArg2)>
    {
        typedef TResult TResult_;
        typedef TArg1 TArg1_;
        typedef TArg2 TArg2_;
        typedef ICheckBinary<TArg1, TArg2> TCheck_;
        static const unsigned Arity_ = 2;
    };

    template <class TResult, class TArg1, class TArg2, class TArg3>
    struct TFunctionTraits<TResult (*)(TArg1, TArg2, TArg3)>
    {
        typedef TResult TResult_;
        typedef TArg1 TArg1_;
        typedef TArg2 TArg2_;
        typedef TArg3 TArg3_;
        typedef ICheckTernary<TArg1, TArg2, TArg3> TCheck_;
        static const unsigned Arity_ = 3;
    };
}

#endif

