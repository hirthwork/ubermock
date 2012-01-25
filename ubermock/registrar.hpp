/*
 * registrar.hpp            -- mock functions registering routines
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

#ifndef __REGISTRAR_HPP_2011_11_13__
#define __REGISTRAR_HPP_2011_11_13__

#include "mockhandler.hpp"
#include "traits.hpp"

namespace NUberMock
{
    class TCleanerBase {
        TCleanerBase(const TCleanerBase&);
        TCleanerBase& operator = (const TCleanerBase&);

    public:
        const unsigned Id_;

        inline TCleanerBase(unsigned id)
            : Id_(id)
        {
        }

        virtual inline ~TCleanerBase()
        {
        }
    };

    template <class TFunc>
    struct TCleaner: TCleanerBase
    {
        inline TCleaner(unsigned id)
            : TCleanerBase(id)
        {
        }

        virtual inline ~TCleaner()
        {
            TMockStorage<TFunc>::DeleteMock(Id_);
        }
    };

    template <bool UseBacktrace>
    struct TCheckCaller;

    template <>
    struct TCheckCaller<true>
    {
        template <class TCheck>
        static bool Call(const NBacktrace::TBacktrace& backtrace,
            TCheck check)
        {
            return check(backtrace);
        }

        template <class TCheck, class TArg>
        static bool Call(const NBacktrace::TBacktrace& backtrace,
            TCheck check, TArg arg)
        {
            return check(backtrace, arg);
        }

        template <class TCheck, class TArg1, class TArg2>
        static bool Call(const NBacktrace::TBacktrace& backtrace,
            TCheck check, TArg1 arg1, TArg2 arg2)
        {
            return check(backtrace, arg1, arg2);
        }

        template <class TCheck, class TArg1, class TArg2, class TArg3>
        static bool Call(const NBacktrace::TBacktrace& backtrace,
            TCheck check, TArg1 arg1, TArg2 arg2, TArg3 arg3)
        {
            return check(backtrace, arg1, arg2, arg3);
        }

        template <class TCheck, class TArg1, class TArg2, class TArg3,
            class TArg4>
        static bool Call(const NBacktrace::TBacktrace& backtrace,
            TCheck check, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
        {
            return check(backtrace, arg1, arg2, arg3, arg4);
        }
    };

    template <>
    struct TCheckCaller<false>
    {
        template <class TCheck>
        static bool Call(const NBacktrace::TBacktrace&,
            TCheck check)
        {
            return check();
        }

        template <class TCheck, class TArg>
        static bool Call(const NBacktrace::TBacktrace&,
            TCheck check, TArg arg)
        {
            return check(arg);
        }

        template <class TCheck, class TArg1, class TArg2>
        static bool Call(const NBacktrace::TBacktrace&,
            TCheck check, TArg1 arg1, TArg2 arg2)
        {
            return check(arg1, arg2);
        }

        template <class TCheck, class TArg1, class TArg2, class TArg3>
        static bool Call(const NBacktrace::TBacktrace&,
            TCheck check, TArg1 arg1, TArg2 arg2, TArg3 arg3)
        {
            return check(arg1, arg2, arg3);
        }

        template <class TCheck, class TArg1, class TArg2, class TArg3,
            class TArg4>
        static bool Call(const NBacktrace::TBacktrace&,
            TCheck check, TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
        {
            return check(arg1, arg2, arg3, arg4);
        }
    };

    template <class TBase, class TCheck, bool UseBacktrace, class TResult>
    struct TCheckNullaryFunction: TBase
    {
        const TCheck Check_;
        TResult Result_;

        inline TCheckNullaryFunction(TCheck check, TResult result)
            : Check_(check)
            , Result_(result)
        {
        }

        virtual bool Check(const NBacktrace::TBacktrace& backtrace) const
        {
            return TCheckCaller<UseBacktrace>::Call(backtrace, Check_);
        }

        virtual typename TBase::TResult_ GetResult()
        {
            return Result_();
        }
    };

    template <class TBase, class TCheck, bool UseBacktrace, class TResult>
    struct TCheckUnaryFunction: TBase
    {
        const TCheck Check_;
        TResult Result_;

        inline TCheckUnaryFunction(TCheck check, TResult result)
            : Check_(check)
            , Result_(result)
        {
        }

        virtual bool Check(const NBacktrace::TBacktrace& backtrace,
            typename TBase::TArg_ arg) const
        {
            return TCheckCaller<UseBacktrace>::Call(backtrace, Check_, arg);
        }

        virtual typename TBase::TResult_ GetResult(typename TBase::TArg_ arg)
        {
            return Result_(arg);
        }
    };

    template <class TBase, class TCheck, bool UseBacktrace, class TResult>
    struct TCheckBinaryFunction: TBase
    {
        const TCheck Check_;
        TResult Result_;

        inline TCheckBinaryFunction(TCheck check, TResult result)
            : Check_(check)
            , Result_(result)
        {
        }

        virtual bool Check(const NBacktrace::TBacktrace& backtrace,
            typename TBase::TArg1_ arg1, typename TBase::TArg2_ arg2) const
        {
            return TCheckCaller<UseBacktrace>::Call(backtrace, Check_, arg1,
                arg2);
        }

        virtual typename TBase::TResult_ GetResult(typename TBase::TArg1_ arg1,
            typename TBase::TArg2_ arg2)
        {
            return Result_(arg1, arg2);
        }
    };

    template <class TBase, class TCheck, bool UseBacktrace, class TResult>
    struct TCheckTernaryFunction: TBase
    {
        const TCheck Check_;
        TResult Result_;

        inline TCheckTernaryFunction(TCheck check, TResult result)
            : Check_(check)
            , Result_(result)
        {
        }

        virtual bool Check(const NBacktrace::TBacktrace& backtrace,
            typename TBase::TArg1_ arg1, typename TBase::TArg2_ arg2,
            typename TBase::TArg3_ arg3) const
        {
            return TCheckCaller<UseBacktrace>::Call(backtrace, Check_, arg1,
                arg2, arg3);
        }

        virtual typename TBase::TResult_ GetResult(typename TBase::TArg1_ arg1,
            typename TBase::TArg2_ arg2, typename TBase::TArg3_ arg3)
        {
            return Result_(arg1, arg2, arg3);
        }
    };


    template <class TBase, class TCheck, bool UseBacktrace, class TResult>
    struct TCheckQuaternaryFunction: TBase
    {
        const TCheck Check_;
        TResult Result_;

        inline TCheckQuaternaryFunction(TCheck check, TResult result)
            : Check_(check)
            , Result_(result)
        {
        }

        virtual bool Check(const NBacktrace::TBacktrace& backtrace,
            typename TBase::TArg1_ arg1, typename TBase::TArg2_ arg2,
            typename TBase::TArg3_ arg3, typename TBase::TArg4_ arg4) const
        {
            return TCheckCaller<UseBacktrace>::Call(backtrace, Check_, arg1,
                arg2, arg3, arg4);
        }

        virtual typename TBase::TResult_ GetResult(typename TBase::TArg1_ arg1,
            typename TBase::TArg2_ arg2, typename TBase::TArg3_ arg3,
            typename TBase::TArg4_ arg4)
        {
            return Result_(arg1, arg2, arg3, arg4);
        }
    };

    template <unsigned Arity, class TFunc, bool UseBacktrace>
    struct TCheckFactory;

    template <class TFunc, bool UseBacktrace>
    struct TCheckFactory<0, TFunc, UseBacktrace>
    {
        typedef IMock<TFunc> TBase_;
        template <class TCheck, class TResult>
        static TBase_* CreateCheck(TCheck check, TResult result)
        {
            return new TCheckNullaryFunction<TBase_, TCheck, UseBacktrace,
                TResult>(check, result);
        }
    };

    template <class TFunc, bool UseBacktrace>
    struct TCheckFactory<1, TFunc, UseBacktrace>
    {
        typedef IMock<TFunc> TBase_;
        template <class TCheck, class TResult>
        static TBase_* CreateCheck(TCheck check, TResult result)
        {
            return new TCheckUnaryFunction<TBase_, TCheck, UseBacktrace,
                TResult>(check, result);
        }
    };

    template <class TFunc, bool UseBacktrace>
    struct TCheckFactory<2, TFunc, UseBacktrace>
    {
        typedef IMock<TFunc> TBase_;
        template <class TCheck, class TResult>
        static TBase_* CreateCheck(TCheck check, TResult result)
        {
            return new TCheckBinaryFunction<TBase_, TCheck, UseBacktrace,
                TResult>(check, result);
        }
    };

    template <class TFunc, bool UseBacktrace>
    struct TCheckFactory<3, TFunc, UseBacktrace>
    {
        typedef IMock<TFunc> TBase_;
        template <class TCheck, class TResult>
        static TBase_* CreateCheck(TCheck check, TResult result)
        {
            return new TCheckTernaryFunction<TBase_, TCheck, UseBacktrace,
                TResult>(check, result);
        }
    };

    template <class TFunc, bool UseBacktrace>
    struct TCheckFactory<4, TFunc, UseBacktrace>
    {
        typedef IMock<TFunc> TBase_;
        template <class TCheck, class TResult>
        static TBase_* CreateCheck(TCheck check, TResult result)
        {
            return new TCheckQuaternaryFunction<TBase_, TCheck, UseBacktrace,
                TResult>(check, result);
        }
    };

    template <class TFunc, bool UseBacktrace, class TCheck, class TResult>
    IMock<TFunc>* CreateCheck(TCheck check,
        TResult result)
    {
        return TCheckFactory<IMock<TFunc>::Arity_, TFunc,
            UseBacktrace>::CreateCheck(check, result);
    }

    class TRegistrarBase
    {
        const TCleanerBase* Cleaner_;

        TRegistrarBase();
        TRegistrarBase(const TRegistrarBase&);
        TRegistrarBase& operator =(const TRegistrarBase&);

    public:
        inline TRegistrarBase(const TCleanerBase* cleaner)
            : Cleaner_(cleaner)
        {
        }

        inline ~TRegistrarBase()
        {
            if (Cleaner_)
            {
                delete Cleaner_;
            }
        }

        inline void Release()
        {
            if (Cleaner_)
            {
                delete Cleaner_;
                Cleaner_ = 0;
            }
        }
    };

    struct TMockRegistrar: TRegistrarBase
    {
        template <class TFunc, class TCheck, class TResult>
        inline TMockRegistrar(TFunc func, TCheck check, TResult result)
            : TRegistrarBase(new TCleaner<TFunc>(TMockStorage<TFunc>::AddMock(
                func, CreateCheck<TFunc, true>(check, result))))
        {
        }
    };

    struct TSimpleMockRegistrar: TRegistrarBase
    {
        template <class TFunc, class TCheck, class TResult>
        inline TSimpleMockRegistrar(TFunc func, TCheck check, TResult result)
            : TRegistrarBase(new TCleaner<TFunc>(TMockStorage<TFunc>::AddMock(
                func, CreateCheck<TFunc, false>(check, result))))
        {
        }
    };
}

#endif

