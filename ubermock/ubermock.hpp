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
#include "symbolloader.hpp"
#include "traits.hpp"

namespace NUberMock
{
    template <class TFunc>
    static inline typename IMock<TFunc>::TResult_ HandleMock(
        TFunc func, const TSymbolLoader& loader = TSymbolLoader())
    {
        return TMockHandler<TFunc>::Handle(func, loader);
    }

    template <class TFunc, class TArg>
    static inline typename IMock<TFunc>::TResult_ HandleMock(
        TFunc func, TArg arg, const TSymbolLoader& loader = TSymbolLoader())
    {
        return TMockHandler<TFunc>::Handle(func, arg, loader);
    }

    template <class TFunc, class TArg1, class TArg2>
    static inline typename IMock<TFunc>::TResult_ HandleMock(
        TFunc func, TArg1 arg1, TArg2 arg2,
        const TSymbolLoader& loader = TSymbolLoader())
    {
        return TMockHandler<TFunc>::Handle(func, arg1, arg2, loader);
    }

    template <class TFunc, class TArg1, class TArg2, class TArg3>
    static inline typename IMock<TFunc>::TResult_ HandleMock(
        TFunc func, TArg1 arg1, TArg2 arg2, TArg3 arg3,
        const TSymbolLoader& loader = TSymbolLoader())
    {
        return TMockHandler<TFunc>::Handle(func, arg1, arg2, arg3, loader);
    }

    template <class TFunc, class TArg1, class TArg2, class TArg3, class TArg4>
    static inline typename IMock<TFunc>::TResult_ HandleMock(
        TFunc func, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4,
        const TSymbolLoader& loader = TSymbolLoader())
    {
        return TMockHandler<TFunc>::Handle(func, arg1, arg2, arg3, arg4,
            loader);
    }

    template <class TResult>
    class TRepeatedResult
    {
        const TResult Result_;

    public:
        inline TRepeatedResult(const TResult& result)
            : Result_(result)
        {
        }

        const TResult& operator () () const
        {
            return Result_;
        }

        template <class TArg>
        const TResult& operator () (TArg) const
        {
            return Result_;
        }

        template <class TArg1, class TArg2>
        const TResult& operator () (TArg1, TArg2) const
        {
            return Result_;
        }

        template <class TArg1, class TArg2, class TArg3>
        const TResult& operator () (TArg1, TArg2, TArg3) const
        {
            return Result_;
        }

        template <class TArg1, class TArg2, class TArg3, class TArg4>
        const TResult& operator () (TArg1, TArg2, TArg3, TArg4) const
        {
            return Result_;
        }
    };

    template <class TResult>
    TRepeatedResult<TResult> MakeRepeatedResult(TResult result)
    {
        return TRepeatedResult<TResult>(result);
    }
}

#endif

