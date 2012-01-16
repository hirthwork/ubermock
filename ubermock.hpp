/*
 * ubermock.hpp             -- basic mock handling routines
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

