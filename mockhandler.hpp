/*
 * mockhandler.hpp          -- mock functions handling routines
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

#ifndef __MOCKHANDLER_HPP_2011_11_13__
#define __MOCKHANDLER_HPP_2011_11_13__

#include <list>

#include <backtrace/backtrace.hpp>

#include "symbolloader.hpp"
#include "traits.hpp"

namespace NUberMock
{
    template <class TFunc>
    class TMockStorage
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

    public:
        typedef std::list<TMock_> TMocks_;

    private:
        TMocks_ Mocks_;

        inline TMockStorage()
        {
        }

        TMockStorage(const TMockStorage&);
        TMockStorage& operator =(const TMockStorage&);

        ~TMockStorage()
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
            static TMockStorage mockHandlerBase;
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
    struct TMockHandler<TResult (*)()>
    {
        typedef TResult (*TFunc_)();
        static TResult Handle(TFunc_ func)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace))
                {
                    return iter->Result_;
                }
            }
            return TFunc_(TSymbolLoader())();
        }
    };

    template <class TResult, class TArg>
    struct TMockHandler<TResult (*)(TArg)>
    {
        typedef TResult (*TFunc_)(TArg);
        static TResult Handle(TFunc_ func, const TArg& arg)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, arg))
                {
                    return iter->Result_;
                }
            }
            return TFunc_(TSymbolLoader())(arg);
        }
    };

    template <class TResult, class TArg1, class TArg2>
    struct TMockHandler<TResult (*)(TArg1, TArg2)>
    {
        typedef TResult (*TFunc_)(TArg1, TArg2);
        static TResult Handle(TFunc_ func, const TArg1& arg1, const TArg2& arg2)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, arg1, arg2))
                {
                    return iter->Result_;
                }
            }
            return TFunc_(TSymbolLoader())(arg1, arg2);
        }
    };

    template <class TResult, class TArg1, class TArg2, class TArg3>
    struct TMockHandler<TResult (*)(TArg1, TArg2, TArg3)>
    {
        typedef TResult (*TFunc_)(TArg1, TArg2, TArg3);
        static TResult Handle(TFunc_ func, const TArg1& arg1, const TArg2& arg2,
            const TArg3& arg3)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, arg1, arg2, arg3))
                {
                    return iter->Result_;
                }
            }
            return TFunc_(TSymbolLoader())(arg1, arg2, arg3);
        }
    };

    template <class TResult, class TArg1, class TArg2, class TArg3, class TArg4>
    struct TMockHandler<TResult (*)(TArg1, TArg2, TArg3, TArg4)>
    {
        typedef TResult (*TFunc_)(TArg1, TArg2, TArg3, TArg4);
        static TResult Handle(TFunc_ func, const TArg1& arg1, const TArg2& arg2,
            const TArg3& arg3, const TArg4& arg4)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, arg1, arg2, arg3, arg4))
                {
                    return iter->Result_;
                }
            }
            return TFunc_(TSymbolLoader())(arg1, arg2, arg3, arg4);
        }
    };

    template <class TResult, class TClass>
    struct TMockHandler<TResult (TClass::*)()>
    {
        typedef TResult (TClass::* TFunc_)();
        static TResult Handle(TFunc_ func, TClass* pthis)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, pthis))
                {
                    return iter->Result_;
                }
            }
            return (pthis->*TFunc_(TSymbolLoader()))();
        }
    };

    template <class TResult, class TClass, class TArg>
    struct TMockHandler<TResult (TClass::*)(TArg)>
    {
        typedef TResult (TClass::* TFunc_)(TArg);
        static TResult Handle(TFunc_ func, TClass* pthis, const TArg& arg)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, pthis, arg))
                {
                    return iter->Result_;
                }
            }
            return (pthis->*TFunc_(TSymbolLoader()))(arg);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2)>
    {
        typedef TResult (TClass::* TFunc_)(TArg1, TArg2);
        static TResult Handle(TFunc_ func, TClass* pthis,
            const TArg1& arg1, const TArg2& arg2)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, pthis, arg1, arg2))
                {
                    return iter->Result_;
                }
            }
            return (pthis->*TFunc_(TSymbolLoader()))(arg1, arg2);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2,
        class TArg3>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2, TArg3)>
    {
        typedef TResult (TClass::* TFunc_)(TArg1, TArg2, TArg3);
        static TResult Handle(TFunc_ func, TClass* pthis,
            const TArg1& arg1, const TArg2& arg2, const TArg3& arg3)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, pthis, arg1, arg2, arg3))
                {
                    return iter->Result_;
                }
            }
            return (pthis->*TFunc_(TSymbolLoader()))(arg1, arg2, arg3);
        }
    };

    template <class TResult, class TClass>
    struct TMockHandler<TResult (TClass::*)() const>
    {
        typedef TResult (TClass::* TFunc_)() const;
        static TResult Handle(TFunc_ func, const TClass* pthis)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, pthis))
                {
                    return iter->Result_;
                }
            }
            return (pthis->*TFunc_(TSymbolLoader()))();
        }
    };

    template <class TResult, class TClass, class TArg>
    struct TMockHandler<TResult (TClass::*)(TArg) const>
    {
        typedef TResult (TClass::* TFunc_)(TArg) const;
        static TResult Handle(TFunc_ func, const TClass* pthis, const TArg& arg)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, pthis, arg))
                {
                    return iter->Result_;
                }
            }
            return (pthis->*TFunc_(TSymbolLoader()))(arg);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2) const>
    {
        typedef TResult (TClass::* TFunc_)(TArg1, TArg2) const;
        static TResult Handle(TFunc_ func, const TClass* pthis,
            const TArg1& arg1, const TArg2& arg2)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, pthis, arg1, arg2))
                {
                    return iter->Result_;
                }
            }
            return (pthis->*TFunc_(TSymbolLoader()))(arg1, arg2);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2,
        class TArg3>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2, TArg3) const>
    {
        typedef TResult (TClass::* TFunc_)(TArg1, TArg2, TArg3) const;
        static TResult Handle(TFunc_ func, const TClass* pthis,
            const TArg1& arg1, const TArg2& arg2, const TArg3& arg3)
        {
            const NBacktrace::TBacktrace& backtrace =
                NBacktrace::GetBacktrace(3);
            typedef typename TMockStorage<TFunc_>::TMocks_ TMocks_;
            const TMocks_& mocks = TMockStorage<TFunc_>::GetMocks();
            for (typename TMocks_::const_iterator iter = mocks.begin(),
                end = mocks.end(); iter != end; ++iter)
            {
                if (iter->Func_ == func
                    && iter->Check_->Check(backtrace, pthis, arg1, arg2, arg3))
                {
                    return iter->Result_;
                }
            }
            return (pthis->*TFunc_(TSymbolLoader()))(arg1, arg2, arg3);
        }
    };
}

#endif

