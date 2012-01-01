#ifndef __MOCKHANDLER_HPP_2011_11_13__
#define __MOCKHANDLER_HPP_2011_11_13__

#include <dlfcn.h>

#include <list>

#include <reinvented-wheels/backtrace.hpp>

#include "traits.hpp"

namespace NUberMock
{
    template <class TFunc>
    struct TMockHandlerBase
    {
        typedef TFunc TFunc_;
        typedef typename TFunctionTraits<TFunc_>::TCheck_ TCheck_;
        typedef typename TFunctionTraits<TFunc_>::TResult_ TResult_;
        struct TMock_ {
            const unsigned Id_;
            const TFunc_ Func_;
            const TCheck_* Check_;
            const TResult_ Result_;
        };
        typedef std::list<TMock_> TMocks_;
        TMocks_ Mocks_;

        inline TMockHandlerBase()
        {
        }

        TMockHandlerBase(const TMockHandlerBase&);
        TMockHandlerBase& operator =(const TMockHandlerBase&);

        ~TMockHandlerBase()
        {
            for (typename TMocks_::iterator iter = Mocks_.begin(),
                end = Mocks_.end(); iter != end; ++iter)
            {
                delete iter->Check_;
            }
        }

        static inline unsigned GetId()
        {
            static unsigned id;
            return id++;
        }

    public:
        static inline TMocks_& GetMocks()
        {
            static TMockHandlerBase mockHandlerBase;
            return mockHandlerBase.Mocks_;
        }

        static inline unsigned AddMock(TFunc_ func, const TCheck_* check,
            TResult_ result)
        {
            TMock_ mock = {GetId(), func, check, result};
            GetMocks().push_back(mock);
            return mock.Id_;
        }

        static void DeleteMock(unsigned id)
        {
            TMocks_& mocks = GetMocks();
            for (typename TMocks_::iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Id_ == id) {
                    delete iter->Check_;
                    mocks.erase(iter);
                    break;
                }
            }
        }
    };

    template <class TFunc>
    struct TMockHandler;

    template <class TResult>
    struct TMockHandler<TResult (*)()>: TMockHandlerBase<TResult (*)()>
    {
        typedef TResult (*TFunc_)();
        static TResult Handle(TFunc_ func)
        {
            const NReinventedWheels::TBacktrace& backtrace =
                NReinventedWheels::GetBacktrace(3);
            typedef typename TMockHandlerBase<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockHandlerBase<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func && iter->Check_->Check(backtrace))
                {
                    return iter->Result_;
                }
            }
            TResult (*symbol)();
            *reinterpret_cast<void**>(&symbol) = dlsym(RTLD_NEXT,
                NReinventedWheels::GetCurrentFrame(2).Symbol_);
            return symbol();
        }
    };

    template <class TResult, class TArg>
    struct TMockHandler<TResult (*)(TArg)>: TMockHandlerBase<TResult (*)(TArg)>
    {
        typedef TResult (*TFunc_)(TArg);
        static TResult Handle(TFunc_ func, const TArg& arg)
        {
            const NReinventedWheels::TBacktrace& backtrace =
                NReinventedWheels::GetBacktrace(3);
            typedef typename TMockHandlerBase<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockHandlerBase<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func && iter->Check_->Check(backtrace, arg))
                {
                    return iter->Result_;
                }
            }
            TResult (*symbol)(TArg);
            *reinterpret_cast<void**>(&symbol) = dlsym(RTLD_NEXT,
                NReinventedWheels::GetCurrentFrame(2).Symbol_);
            return symbol(arg);
        }
    };

    template <class TResult, class TArg1, class TArg2>
    struct TMockHandler<TResult (*)(TArg1, TArg2)>:
        TMockHandlerBase<TResult (*)(TArg1, TArg2)>
    {
        typedef TResult (*TFunc_)(TArg1, TArg2);
        static TResult Handle(TFunc_ func, const TArg1& arg1, const TArg2& arg2)
        {
            const NReinventedWheels::TBacktrace& backtrace =
                NReinventedWheels::GetBacktrace(3);
            typedef typename TMockHandlerBase<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockHandlerBase<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, arg1, arg2))
                {
                    return iter->Result_;
                }
            }
            TResult (*symbol)(TArg1, TArg2);
            *reinterpret_cast<void**>(&symbol) = dlsym(RTLD_NEXT,
                NReinventedWheels::GetCurrentFrame(2).Symbol_);
            return symbol(arg1, arg2);
        }
    };

    template <class TResult, class TArg1, class TArg2, class TArg3>
    struct TMockHandler<TResult (*)(TArg1, TArg2, TArg3)>:
        TMockHandlerBase<TResult (*)(TArg1, TArg2, TArg3)>
    {
        typedef TResult (*TFunc_)(TArg1, TArg2, TArg3);
        static TResult Handle(TFunc_ func, const TArg1& arg1, const TArg2& arg2,
            const TArg3& arg3)
        {
            const NReinventedWheels::TBacktrace& backtrace =
                NReinventedWheels::GetBacktrace(3);
            typedef typename TMockHandlerBase<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockHandlerBase<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, arg1, arg2, arg3))
                {
                    return iter->Result_;
                }
            }
            TResult (*symbol)(TArg1, TArg2, TArg3);
            *reinterpret_cast<void**>(&symbol) = dlsym(RTLD_NEXT,
                NReinventedWheels::GetCurrentFrame(2).Symbol_);
            return symbol(arg1, arg2, arg3);
        }
    };
}

#endif

