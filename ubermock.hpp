#ifndef __UBERMOCK_HPP_2011_11_13__
#define __UBERMOCK_HPP_2011_11_13__

#include "mockhandler.hpp"
#include "traits.hpp"

namespace NUberMock
{
    template <class TFunc>
    static inline typename TFunctionTraits<TFunc>::TResult_ HandleMock(
        TFunc func)
    {
        return TMockHandler<TFunc>::Handle(func);
    }

    template <class TFunc, class TArg>
    static inline typename TFunctionTraits<TFunc>::TResult_ HandleMock(
        TFunc func, TArg arg)
    {
        return TMockHandler<TFunc>::Handle(func, arg);
    }

    template <class TFunc, class TArg1, class TArg2>
    static inline typename TFunctionTraits<TFunc>::TResult_ HandleMock(
        TFunc func, TArg1 arg1, TArg2 arg2)
    {
        return TMockHandler<TFunc>::Handle(func, arg1, arg2);
    }

    template <class TFunc, class TArg1, class TArg2, class TArg3>
    static inline typename TFunctionTraits<TFunc>::TResult_ HandleMock(
        TFunc func, TArg1 arg1, TArg2 arg2, TArg3 arg3)
    {
        return TMockHandler<TFunc>::Handle(func, arg1, arg2, arg3);
    }

    template <class TFunc, class TArg1, class TArg2, class TArg3, class TArg4>
    static inline typename TFunctionTraits<TFunc>::TResult_ HandleMock(
        TFunc func, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
    {
        return TMockHandler<TFunc>::Handle(func, arg1, arg2, arg3, arg4);
    }
}

#endif

