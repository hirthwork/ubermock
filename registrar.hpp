#include "mockhandler.hpp"
#include "traits.hpp"

namespace NUberMock
{
    struct TCleanerBase {
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
            TMockHandler<TFunc>::DeleteMock(Id_);
        }
    };

    template <bool UseBacktrace>
    struct TCheckCaller;

    template <>
    struct TCheckCaller<true>
    {
        template <class TCheck>
        static bool Call(const NReinventedWheels::TBacktrace& backtrace,
            TCheck check)
        {
            return check(backtrace);
        }

        template <class TCheck, class TArg>
        static bool Call(const NReinventedWheels::TBacktrace& backtrace,
            TCheck check, TArg arg)
        {
            return check(backtrace, arg);
        }

        template <class TCheck, class TArg1, class TArg2>
        static bool Call(const NReinventedWheels::TBacktrace& backtrace,
            TCheck check, TArg1 arg1, TArg2 arg2)
        {
            return check(backtrace, arg1, arg2);
        }

        template <class TCheck, class TArg1, class TArg2, class TArg3>
        static bool Call(const NReinventedWheels::TBacktrace& backtrace,
            TCheck check, TArg1 arg1, TArg2 arg2, TArg3 arg3)
        {
            return check(backtrace, arg1, arg2, arg3);
        }
    };

    template <>
    struct TCheckCaller<false>
    {
        template <class TCheck>
        static bool Call(const NReinventedWheels::TBacktrace&,
            TCheck check)
        {
            return check();
        }

        template <class TCheck, class TArg>
        static bool Call(const NReinventedWheels::TBacktrace&,
            TCheck check, TArg arg)
        {
            return check(arg);
        }

        template <class TCheck, class TArg1, class TArg2>
        static bool Call(const NReinventedWheels::TBacktrace&,
            TCheck check, TArg1 arg1, TArg2 arg2)
        {
            return check(arg1, arg2);
        }

        template <class TCheck, class TArg1, class TArg2, class TArg3>
        static bool Call(const NReinventedWheels::TBacktrace&,
            TCheck check, TArg1 arg1, TArg2 arg2, TArg3 arg3)
        {
            return check(arg1, arg2, arg3);
        }
    };

    template <class TCheck, bool UseBacktrace>
    struct TCheckNullary: ICheckNullary
    {
        const TCheck Check_;
        inline TCheckNullary(TCheck check)
            : Check_(check)
        {
        }

        virtual bool Check(const NReinventedWheels::TBacktrace& backtrace) const
        {
            return TCheckCaller<UseBacktrace>::Call(backtrace, Check_);
        }
    };

    template <class TCheck, bool UseBacktrace, class TArg>
    struct TCheckUnary: ICheckUnary<TArg>
    {
        const TCheck Check_;
        inline TCheckUnary(TCheck check)
            : Check_(check)
        {
        }

        virtual bool Check(const NReinventedWheels::TBacktrace& backtrace,
            TArg arg) const
        {
            return TCheckCaller<UseBacktrace>::Call(backtrace, Check_, arg);
        }
    };

    template <class TCheck, bool UseBacktrace, class TArg1, class TArg2>
    struct TCheckBinary: ICheckBinary<TArg1, TArg2>
    {
        const TCheck Check_;
        inline TCheckBinary(TCheck check)
            : Check_(check)
        {
        }

        virtual bool Check(const NReinventedWheels::TBacktrace& backtrace,
            TArg1 arg1, TArg2 arg2) const
        {
            return TCheckCaller<UseBacktrace>::Call(backtrace, Check_, arg1,
                arg2);
        }
    };

    template <class TCheck, bool UseBacktrace, class TArg1, class TArg2,
        class TArg3>
    struct TCheckTernary: ICheckTernary<TArg1, TArg2, TArg3>
    {
        const TCheck Check_;
        inline TCheckTernary(TCheck check)
            : Check_(check)
        {
        }

        virtual bool Check(const NReinventedWheels::TBacktrace& backtrace,
            TArg1 arg1, TArg2 arg2, TArg3 arg3) const
        {
            return TCheckCaller<UseBacktrace>::Call(backtrace, Check_, arg1,
                arg2, arg3);
        }
    };

    template <unsigned Arity, class TFunc, bool UseBacktrace>
    struct TCheckFactory;

    template <class TFunc, bool UseBacktrace>
    struct TCheckFactory<0, TFunc, UseBacktrace>
    {
        template <class TCheck>
        static ICheckNullary* CreateCheck(TCheck check)
        {
            return new TCheckNullary<TCheck, UseBacktrace>(check);
        }
    };

    template <class TFunc, bool UseBacktrace>
    struct TCheckFactory<1, TFunc, UseBacktrace>
    {
        typedef typename TFunctionTraits<TFunc>::TArg_ TArg_;
        template <class TCheck>
        static ICheckUnary<TArg_>* CreateCheck(TCheck check)
        {
            return new TCheckUnary<TCheck, UseBacktrace, TArg_>(check);
        }
    };

    template <class TFunc, bool UseBacktrace>
    struct TCheckFactory<2, TFunc, UseBacktrace>
    {
        typedef typename TFunctionTraits<TFunc>::TArg1_ TArg1_;
        typedef typename TFunctionTraits<TFunc>::TArg2_ TArg2_;
        template <class TCheck>
        static ICheckBinary<TArg1_, TArg2_>* CreateCheck(TCheck check)
        {
            return new TCheckBinary<TCheck, UseBacktrace, TArg1_, TArg2_>(
                check);
        }
    };

    template <class TFunc, bool UseBacktrace>
    struct TCheckFactory<3, TFunc, UseBacktrace>
    {
        typedef typename TFunctionTraits<TFunc>::TArg1_ TArg1_;
        typedef typename TFunctionTraits<TFunc>::TArg2_ TArg2_;
        typedef typename TFunctionTraits<TFunc>::TArg3_ TArg3_;
        template <class TCheck>
        static ICheckTernary<TArg1_, TArg2_, TArg3_>* CreateCheck(TCheck check)
        {
            return new TCheckTernary<TCheck, UseBacktrace, TArg1_, TArg2_,
                TArg3_>(check);
        }
    };

    template <class TFunc, bool UseBacktrace, class TCheck>
    typename TFunctionTraits<TFunc>::TCheck_* CreateCheck(TCheck check)
    {
        return TCheckFactory<TFunctionTraits<TFunc>::Arity_, TFunc,
            UseBacktrace>::CreateCheck(check);
    }

    class TMockRegistrar
    {
        const TCleanerBase* Cleaner_;

        TMockRegistrar();
        TMockRegistrar(const TMockRegistrar&);
        TMockRegistrar& operator =(const TMockRegistrar&);

    public:
        template <class TFunc, class TCheck>
        inline TMockRegistrar(TFunc func, TCheck check,
            typename TFunctionTraits<TFunc>::TResult_ result)
            : Cleaner_(new TCleaner<TFunc>(TMockHandler<TFunc>::AddMock(func,
                CreateCheck<TFunc, true>(check), result)))
        {
        }

        inline ~TMockRegistrar()
        {
            delete Cleaner_;
        }
    };

    class TSimpleMockRegistrar
    {
        const TCleanerBase* Cleaner_;

        TSimpleMockRegistrar();
        TSimpleMockRegistrar(const TMockRegistrar&);
        TSimpleMockRegistrar& operator =(const TMockRegistrar&);

    public:
        template <class TFunc, class TCheck>
        inline TSimpleMockRegistrar(TFunc func, TCheck check,
            typename TFunctionTraits<TFunc>::TResult_ result)
            : Cleaner_(new TCleaner<TFunc>(TMockHandler<TFunc>::AddMock(func,
                CreateCheck<TFunc, false>(check), result)))
        {
        }

        inline ~TSimpleMockRegistrar()
        {
            delete Cleaner_;
        }
    };
}

