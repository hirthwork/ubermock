/*
 * call.hpp                 -- function call helpers
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

#ifndef __CALL_HPP_2012_01_26__
#define __CALL_HPP_2012_01_26__

#include <reinvented-wheels/enableif.hpp>

namespace NUberMock
{
    template <class TType>
    struct TIsClass
    {
        typedef char TTwoChars[2];

        template <class T>
        static char Test(void (T::*)());

        template <class>
        static TTwoChars& Test(...);

    public:
        static const bool Value_ = sizeof(Test<TType>(0)) == 1;
    };

    template <class TType, bool = TIsClass<TType>::Value_>
    struct TAddRefIfClass
    {
        typedef TType& TType_;
    };

    template <class TType>
    struct TAddRefIfClass<TType, false>
    {
        typedef TType TType_;
    };

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        IsMember && TArgs::Arity_ == 1, TResult>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return (args.Arg_->*func)();
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        IsMember && TArgs::Arity_ == 2, TResult>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return (args.Arg1_->*func)(args.Arg2_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        IsMember && TArgs::Arity_ == 3, TResult>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return (args.Arg1_->*func)(args.Arg2_, args.Arg3_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        IsMember && TArgs::Arity_ == 4, TResult>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return (args.Arg1_->*func)(args.Arg2_, args.Arg3_, args.Arg4_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !IsMember && TArgs::Arity_ == 0, TResult>::TType_
        Call(typename TAddRefIfClass<TFunc>::TType_ func, const TArgs&)
    {
        return func();
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !IsMember && TArgs::Arity_ == 1, TResult>::TType_
        Call(typename TAddRefIfClass<TFunc>::TType_ func, const TArgs& args)
    {
        return func(args.Arg_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !IsMember && TArgs::Arity_ == 2, TResult>::TType_
        Call(typename TAddRefIfClass<TFunc>::TType_ func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !IsMember && TArgs::Arity_ == 3, TResult>::TType_
        Call(typename TAddRefIfClass<TFunc>::TType_ func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_, args.Arg3_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !IsMember && TArgs::Arity_ == 4, TResult>::TType_
        Call(typename TAddRefIfClass<TFunc>::TType_ func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_, args.Arg3_, args.Arg4_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !IsMember && TArgs::Arity_ == 5, TResult>::TType_
        Call(typename TAddRefIfClass<TFunc>::TType_ func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_, args.Arg3_, args.Arg4_,
            args.Arg5_);
    }
}

#endif

