#ifndef __CALL_HPP_2012_01_26__
#define __CALL_HPP_2012_01_26__

namespace NUberMock
{
    template <class, bool>
    struct TEnableIf;

    template <class TType>
    struct TEnableIf<TType, true>
    {
        typedef TType TType_;
    };

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename TEnableIf<TResult,
        IsMember && TArgs::Arity_ == 1>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return (args.Arg_->*func)();
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename TEnableIf<TResult,
        IsMember && TArgs::Arity_ == 2>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return (args.Arg1_->*func)(args.Arg2_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename TEnableIf<TResult,
        IsMember && TArgs::Arity_ == 3>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return (args.Arg1_->*func)(args.Arg2_, args.Arg3_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename TEnableIf<TResult,
        IsMember && TArgs::Arity_ == 4>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return (args.Arg1_->*func)(args.Arg2_, args.Arg3_, args.Arg4_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename TEnableIf<TResult,
        !IsMember && TArgs::Arity_ == 0>::TType_
        Call(TFunc func, const TArgs&)
    {
        return func();
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename TEnableIf<TResult,
        !IsMember && TArgs::Arity_ == 1>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return func(args.Arg_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename TEnableIf<TResult,
        !IsMember && TArgs::Arity_ == 2>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename TEnableIf<TResult,
        !IsMember && TArgs::Arity_ == 3>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_, args.Arg3_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename TEnableIf<TResult,
        !IsMember && TArgs::Arity_ == 4>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_, args.Arg3_, args.Arg4_);
    }

    template <class TResult, bool IsMember, class TFunc, class TArgs>
    static inline typename TEnableIf<TResult,
        !IsMember && TArgs::Arity_ == 5>::TType_
        Call(TFunc func, const TArgs& args)
    {
        return func(args.Arg1_, args.Arg2_, args.Arg3_, args.Arg4_,
            args.Arg5_);
    }
}

#endif

