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
            GetMocks().push_front(mock);
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

    struct TFunctionCaller
    {
        template <class TFunc, class TArg>
        static inline typename TFunctionTraits<TFunc>::TResult_ Call(TFunc func,
            const TArg& arg)
        {
            return func(arg);
        }

        template <class TFunc, class TArg1, class TArg2>
        static inline typename TFunctionTraits<TFunc>::TResult_ Call(TFunc func,
            const TArg1& arg1, const TArg2& arg2)
        {
            return func(arg1, arg2);
        }

        template <class TFunc, class TArg1, class TArg2, class TArg3>
        static inline typename TFunctionTraits<TFunc>::TResult_ Call(TFunc func,
            const TArg1& arg1, const TArg2& arg2, const TArg3& arg3)
        {
            return func(arg1, arg2, arg3);
        }

        template <class TFunc, class TArg1, class TArg2, class TArg3,
            class TArg4>
        static inline typename TFunctionTraits<TFunc>::TResult_ Call(TFunc func,
            const TArg1& arg1, const TArg2& arg2, const TArg3& arg3,
            const TArg4& arg4)
        {
            return func(arg1, arg2, arg3, arg4);
        }
    };

    struct TMemberFunctionCaller
    {
        template <class TFunc, class TClass>
        static inline typename TFunctionTraits<TFunc>::TResult_ Call(TFunc func,
            TClass* pthis)
        {
            return (pthis->*func)();
        }

        template <class TFunc, class TClass, class TArg>
        static inline typename TFunctionTraits<TFunc>::TResult_ Call(TFunc func,
            TClass* pthis, const TArg& arg)
        {
            return (pthis->*func)(arg);
        }

        template <class TFunc, class TClass, class TArg1, class TArg2>
        static inline typename TFunctionTraits<TFunc>::TResult_ Call(TFunc func,
            TClass* pthis, const TArg1& arg1, const TArg2& arg2)
        {
            return (pthis->*func)(arg1, arg2);
        }

        template <class TFunc, class TClass, class TArg1, class TArg2,
            class TArg3>
        static inline typename TFunctionTraits<TFunc>::TResult_ Call(TFunc func,
            TClass* pthis, const TArg1& arg1, const TArg2& arg2,
            const TArg3& arg3)
        {
            return (pthis->*func)(arg1, arg2, arg3);
        }
    };

    template <class TFunc>
    static typename TFunctionTraits<TFunc>::TResult_ CheckAndHandle(
        TFunc func, const TSymbolLoader& loader)
    {
        typedef typename TMockStorage<TFunc>::TMocks_ TMocks_;
        const TMocks_& mocks = TMockStorage<TFunc>::GetMocks();
        for (typename TMocks_::const_iterator iter = mocks.begin(),
            end = mocks.end(); iter != end; ++iter)
        {
            if (iter->Func_ == func
                && iter->Check_->Check(loader.GetBacktrace()))
            {
                return iter->Result_;
            }
        }
        return TFunc(loader)();
    }

    template <class TCaller, class TFunc, class TArg>
    static typename TFunctionTraits<TFunc>::TResult_ CheckAndHandle(
        TFunc func, const TArg& arg, const TSymbolLoader& loader)
    {
        typedef typename TMockStorage<TFunc>::TMocks_ TMocks_;
        const TMocks_& mocks = TMockStorage<TFunc>::GetMocks();
        for (typename TMocks_::const_iterator iter = mocks.begin(),
            end = mocks.end(); iter != end; ++iter)
        {
            if (iter->Func_ == func
                && iter->Check_->Check(loader.GetBacktrace(), arg))
            {
                return iter->Result_;
            }
        }
        return TCaller::Call(TFunc(loader), arg);
    }

    template <class TCaller, class TFunc, class TArg1, class TArg2>
    static typename TFunctionTraits<TFunc>::TResult_ CheckAndHandle(
        TFunc func, const TArg1& arg1, const TArg2& arg2,
        const TSymbolLoader& loader)
    {
        typedef typename TMockStorage<TFunc>::TMocks_ TMocks_;
        const TMocks_& mocks = TMockStorage<TFunc>::GetMocks();
        for (typename TMocks_::const_iterator iter = mocks.begin(),
            end = mocks.end(); iter != end; ++iter)
        {
            if (iter->Func_ == func
                && iter->Check_->Check(loader.GetBacktrace(), arg1, arg2))
            {
                return iter->Result_;
            }
        }
        return TCaller::Call(TFunc(loader), arg1, arg2);
    }

    template <class TCaller, class TFunc, class TArg1, class TArg2, class TArg3>
    static typename TFunctionTraits<TFunc>::TResult_ CheckAndHandle(
        TFunc func, const TArg1& arg1, const TArg2& arg2, const TArg3& arg3,
        const TSymbolLoader& loader)
    {
        typedef typename TMockStorage<TFunc>::TMocks_ TMocks_;
        const TMocks_& mocks = TMockStorage<TFunc>::GetMocks();
        for (typename TMocks_::const_iterator iter = mocks.begin(),
            end = mocks.end(); iter != end; ++iter)
        {
            if (iter->Func_ == func
                && iter->Check_->Check(loader.GetBacktrace(), arg1, arg2, arg3))
            {
                return iter->Result_;
            }
        }
        return TCaller::Call(TFunc(loader), arg1, arg2, arg3);
    }

    template <class TCaller, class TFunc, class TArg1, class TArg2, class TArg3,
        class TArg4>
    static typename TFunctionTraits<TFunc>::TResult_ CheckAndHandle(
        TFunc func, const TArg1& arg1, const TArg2& arg2, const TArg3& arg3,
        const TArg4& arg4, const TSymbolLoader& loader)
    {
        typedef typename TMockStorage<TFunc>::TMocks_ TMocks_;
        const TMocks_& mocks = TMockStorage<TFunc>::GetMocks();
        for (typename TMocks_::const_iterator iter = mocks.begin(),
            end = mocks.end(); iter != end; ++iter)
        {
            if (iter->Func_ == func
                && iter->Check_->Check(loader.GetBacktrace(), arg1, arg2, arg3,
                    arg4))
            {
                return iter->Result_;
            }
        }
        return TCaller::Call(TFunc(loader), arg1, arg2, arg3, arg4);
    }

    template <class TFunc>
    struct TMockHandler;

    template <class TResult>
    struct TMockHandler<TResult (*)()>
    {
        typedef TResult (*TFunc_)();
        static inline TResult Handle(TFunc_ func, const TSymbolLoader& loader)
        {
            return CheckAndHandle(func, loader);
        }
    };

    template <class TResult, class TArg>
    struct TMockHandler<TResult (*)(TArg)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TArg& arg,
            const TSymbolLoader& loader)
        {
            return CheckAndHandle<TFunctionCaller>(func, arg, loader);
        }
    };

    template <class TResult, class TArg1, class TArg2>
    struct TMockHandler<TResult (*)(TArg1, TArg2)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TArg1& arg1,
            const TArg2& arg2, const TSymbolLoader& loader)
        {
            return CheckAndHandle<TFunctionCaller>(func, arg1, arg2, loader);
        }
    };

    template <class TResult, class TArg1, class TArg2, class TArg3>
    struct TMockHandler<TResult (*)(TArg1, TArg2, TArg3)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TArg1& arg1,
            const TArg2& arg2, const TArg3& arg3, const TSymbolLoader& loader)
        {
            return CheckAndHandle<TFunctionCaller>(func, arg1, arg2, arg3,
                loader);
        }
    };

    template <class TResult, class TArg1, class TArg2, class TArg3, class TArg4>
    struct TMockHandler<TResult (*)(TArg1, TArg2, TArg3, TArg4)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TArg1& arg1,
            const TArg2& arg2, const TArg3& arg3, const TArg4& arg4,
            const TSymbolLoader& loader)
        {
            return CheckAndHandle<TFunctionCaller>(func, arg1, arg2, arg3, arg4,
                loader);
        }
    };

    template <class TResult, class TClass>
    struct TMockHandler<TResult (TClass::*)()>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, TClass* pthis,
            const TSymbolLoader& loader)
        {
            return CheckAndHandle<TMemberFunctionCaller>(func, pthis, loader);
        }
    };

    template <class TResult, class TClass, class TArg>
    struct TMockHandler<TResult (TClass::*)(TArg)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, TClass* pthis,
            const TArg& arg, const TSymbolLoader& loader)
        {
            return CheckAndHandle<TMemberFunctionCaller>(func, pthis, arg,
                loader);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, TClass* pthis,
            const TArg1& arg1, const TArg2& arg2, const TSymbolLoader& loader)
        {
            return CheckAndHandle<TMemberFunctionCaller>(func, pthis, arg1,
                arg2, loader);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2,
        class TArg3>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2, TArg3)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, TClass* pthis,
            const TArg1& arg1, const TArg2& arg2, const TArg3& arg3,
            const TSymbolLoader& loader)
        {
            return CheckAndHandle<TMemberFunctionCaller>(func, pthis, arg1,
                arg2, arg3, loader);
        }
    };

    template <class TResult, class TClass>
    struct TMockHandler<TResult (TClass::*)() const>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TClass* pthis,
            const TSymbolLoader& loader)
        {
            return CheckAndHandle<TMemberFunctionCaller>(func, pthis, loader);
        }
    };

    template <class TResult, class TClass, class TArg>
    struct TMockHandler<TResult (TClass::*)(TArg) const>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TClass* pthis,
            const TArg& arg, const TSymbolLoader& loader)
        {
            return CheckAndHandle<TMemberFunctionCaller>(func, pthis, arg,
                loader);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2) const>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TClass* pthis,
            const TArg1& arg1, const TArg2& arg2, const TSymbolLoader& loader)
        {
            return CheckAndHandle<TMemberFunctionCaller>(func, pthis, arg1,
                arg2, loader);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2,
        class TArg3>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2, TArg3) const>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TClass* pthis,
            const TArg1& arg1, const TArg2& arg2, const TArg3& arg3,
            const TSymbolLoader& loader)
        {
            return CheckAndHandle<TMemberFunctionCaller>(func, pthis, arg1,
                arg2, arg3, loader);
        }
    };
}

#endif

