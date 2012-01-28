/*
 * traits.hpp               -- functional traits
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

#ifndef __TRAITS_HPP_2011_11_13__
#define __TRAITS_HPP_2011_11_13__

#include "tuple.hpp"

namespace NBacktrace
{
    struct TBacktrace;
}

namespace NUberMock
{
    template <class TResult, class TArg1 = void, class TArg2 = void,
        class TArg3 = void, class TArg4 = void>
    struct IMockBase
    {
        typedef TResult TResult_;
        typedef TTuple<TArg1, TArg2, TArg3, TArg4> TArgs_;

        virtual inline ~IMockBase()
        {
        }
        virtual bool Check(const NBacktrace::TBacktrace&,
            const TArgs_&) const = 0;
        virtual TResult GetResult(const TArgs_&) = 0;
    };

    template <class TFunc>
    struct IMock;

    template <class TResult>
    struct IMock<TResult (*)()>: IMockBase<TResult>
    {
    };

    template <class TResult, class TArg>
    struct IMock<TResult (*)(TArg)>: IMockBase<TResult, TArg>
    {
    };

    template <class TResult, class TArg1, class TArg2>
    struct IMock<TResult (*)(TArg1, TArg2)>: IMockBase<TResult, TArg1, TArg2>
    {
    };

    template <class TResult, class TArg1, class TArg2, class TArg3>
    struct IMock<TResult (*)(TArg1, TArg2, TArg3)>:
        IMockBase<TResult, TArg1, TArg2, TArg3>
    {
    };

    template <class TResult, class TArg1, class TArg2, class TArg3,
        class TArg4>
    struct IMock<TResult (*)(TArg1, TArg2, TArg3, TArg4)>:
        IMockBase<TResult, TArg1, TArg2, TArg3, TArg4>
    {
    };

    template <class TResult, class TClass>
    struct IMock<TResult (TClass::*)()>: IMockBase<TResult, TClass*>
    {
    };

    template <class TResult, class TClass, class TArg>
    struct IMock<TResult (TClass::*)(TArg)>: IMockBase<TResult, TClass*, TArg>
    {
    };

    template <class TResult, class TClass, class TArg1, class TArg2>
    struct IMock<TResult (TClass::*)(TArg1, TArg2)>:
        IMockBase<TResult, TClass*, TArg1, TArg2>
    {
    };

    template <class TResult, class TClass, class TArg1, class TArg2,
        class TArg3>
    struct IMock<TResult (TClass::*)(TArg1, TArg2, TArg3)>:
        IMockBase<TResult, TClass*, TArg1, TArg2, TArg3>
    {
    };

    template <class TResult, class TClass>
    struct IMock<TResult (TClass::*)() const>:
        IMockBase<TResult, const TClass*>
    {
    };

    template <class TResult, class TClass, class TArg>
    struct IMock<TResult (TClass::*)(TArg) const>:
        IMockBase<TResult, const TClass*, TArg>
    {
    };

    template <class TResult, class TClass, class TArg1, class TArg2>
    struct IMock<TResult (TClass::*)(TArg1, TArg2) const>:
        IMockBase<TResult, const TClass*, TArg1, TArg2>
    {
    };

    template <class TResult, class TClass, class TArg1, class TArg2,
        class TArg3>
    struct IMock<TResult (TClass::*)(TArg1, TArg2, TArg3) const>:
        IMockBase<TResult, const TClass*, TArg1, TArg2, TArg3>
    {
    };
}

#endif

