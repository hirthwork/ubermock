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

namespace NBacktrace
{
    struct TBacktrace;
}

namespace NUberMock
{
    template <class TResult>
    struct TResultBase
    {
        typedef TResult TResult_;
        virtual inline ~TResultBase()
        {
        }
    };

    template <class TResult, class TArg1 = void, class TArg2 = void,
        class TArg3 = void, class TArg4 = void>
    struct IMockBase;

    template <class TResult>
    struct IMockBase<TResult, void, void, void, void>: TResultBase<TResult>
    {
        virtual bool Check(const NBacktrace::TBacktrace&) const = 0;
        virtual TResult GetResult() = 0;
        static const unsigned Arity_ = 0;
    };

    template <class TResult, class TArg>
    struct IMockBase<TResult, TArg, void, void, void>: TResultBase<TResult>
    {
        typedef TArg TArg_;
        virtual bool Check(const NBacktrace::TBacktrace&, TArg) const = 0;
        virtual TResult GetResult(TArg) = 0;
        static const unsigned Arity_ = 1;
    };

    template <class TResult, class TArg1, class TArg2>
    struct IMockBase<TResult, TArg1, TArg2, void, void>: TResultBase<TResult>
    {
        typedef TArg1 TArg1_;
        typedef TArg2 TArg2_;
        virtual bool Check(const NBacktrace::TBacktrace&,
            TArg1, TArg2) const = 0;
        virtual TResult GetResult(TArg1, TArg2) = 0;
        static const unsigned Arity_ = 2;
    };

    template <class TResult, class TArg1, class TArg2, class TArg3>
    struct IMockBase<TResult, TArg1, TArg2, TArg3, void>: TResultBase<TResult>
    {
        typedef TArg1 TArg1_;
        typedef TArg2 TArg2_;
        typedef TArg3 TArg3_;
        virtual bool Check(const NBacktrace::TBacktrace&,
            TArg1, TArg2, TArg3) const = 0;
        virtual TResult GetResult(TArg1, TArg2, TArg3) = 0;
        static const unsigned Arity_ = 3;
    };

    template <class TResult, class TArg1, class TArg2, class TArg3, class TArg4>
    struct IMockBase: TResultBase<TResult>
    {
        typedef TArg1 TArg1_;
        typedef TArg2 TArg2_;
        typedef TArg3 TArg3_;
        typedef TArg4 TArg4_;
        virtual bool Check(const NBacktrace::TBacktrace&,
            TArg1, TArg2, TArg3, TArg4) const = 0;
        virtual TResult GetResult(TArg1, TArg2, TArg3, TArg4) = 0;
        static const unsigned Arity_ = 4;
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

    template <class TResult, class TArg1, class TArg2, class TArg3, class TArg4>
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
    struct IMock<TResult (TClass::*)() const>: IMockBase<TResult, const TClass*>
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

