#ifndef __CALL_HPP_2012_01_26__
#define __CALL_HPP_2012_01_26__

#include <reinvented-wheels/enableif.hpp>

namespace NUberMock
{
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
        Call(TFunc func, const TArgs&)
    {
        return func();
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !IsMember && TArgs::Arity_ == 1, TResult>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return func(args.Arg_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !IsMember && TArgs::Arity_ == 2, TResult>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !IsMember && TArgs::Arity_ == 3, TResult>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_, args.Arg3_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !IsMember && TArgs::Arity_ == 4, TResult>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_, args.Arg3_, args.Arg4_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !IsMember && TArgs::Arity_ == 5, TResult>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_, args.Arg3_, args.Arg4_,
            args.Arg5_);
    }
}

#endif

