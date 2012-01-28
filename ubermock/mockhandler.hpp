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

#include "call.hpp"
#include "mocks.hpp"
#include "symbolloader.hpp"

namespace NUberMock
{
    template <class TFunc>
    class TMockStorage
    {
        struct TMock_ {
            const unsigned Id_;
            const TFunc Func_;
            IMock<TFunc>* const Check_;
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
            static TMockStorage mockStorage;
            return mockStorage.Mocks_;
        }

        static inline unsigned AddMock(TFunc func,
            IMock<TFunc>* check)
        {
            TMock_ mock = {GetId(), func, check};
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

    template <bool IsMember, class TFunc, class TArgs>
    static typename IMock<TFunc>::TResult_ GetValue(TFunc func,
        const TArgs& args, const TSymbolLoader& loader)
    {
        typedef typename TMockStorage<TFunc>::TMocks_ TMocks_;
        const TMocks_& mocks = TMockStorage<TFunc>::GetMocks();
        for (typename TMocks_::const_iterator iter = mocks.begin(),
            end = mocks.end(); iter != end; ++iter)
        {
            if (iter->Func_ == func
                && iter->Check_->Check(loader.GetBacktrace(), args))
            {
                return iter->Check_->GetResult(args);
            }
        }
        return Call<typename IMock<TFunc>::TResult_, IsMember>(TFunc(loader),
            args);
    }

    template <class TFunc>
    struct TMockHandler;

    template <class TResult>
    struct TMockHandler<TResult (*)()>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<false>(func, TArgs(), loader);
        }
    };

    template <class TResult, class TArg>
    struct TMockHandler<TResult (*)(TArg)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, TArg arg,
            const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<false>(func, TArgs(arg), loader);
        }
    };

    template <class TResult, class TArg1, class TArg2>
    struct TMockHandler<TResult (*)(TArg1, TArg2)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, TArg1 arg1, TArg2 arg2,
            const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<false>(func, TArgs(arg1, arg2), loader);
        }
    };

    template <class TResult, class TArg1, class TArg2, class TArg3>
    struct TMockHandler<TResult (*)(TArg1, TArg2, TArg3)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, TArg1 arg1, TArg2 arg2,
            TArg3 arg3, const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<false>(func, TArgs(arg1, arg2, arg3), loader);
        }
    };

    template <class TResult, class TArg1, class TArg2, class TArg3,
        class TArg4>
    struct TMockHandler<TResult (*)(TArg1, TArg2, TArg3, TArg4)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, TArg1 arg1, TArg2 arg2,
            TArg3 arg3, TArg4 arg4, const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<false>(func, TArgs(arg1, arg2, arg3, arg4),
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
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<true>(func, TArgs(pthis), loader);
        }
    };

    template <class TResult, class TClass, class TArg>
    struct TMockHandler<TResult (TClass::*)(TArg)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, TClass* pthis, TArg arg,
            const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<true>(func, TArgs(pthis, arg), loader);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, TClass* pthis, TArg1 arg1,
            TArg2 arg2, const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<true>(func, TArgs(pthis, arg1, arg2), loader);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2,
        class TArg3>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2, TArg3)>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, TClass* pthis, TArg1 arg1,
            TArg2 arg2, TArg3 arg3, const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<true>(func, TArgs(pthis, arg1, arg2, arg3),
                loader);
        }
    };

    template <class TResult, class TClass>
    struct TMockHandler<TResult (TClass::*)() const>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TClass* pthis,
            const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<true>(func, TArgs(pthis), loader);
        }
    };

    template <class TResult, class TClass, class TArg>
    struct TMockHandler<TResult (TClass::*)(TArg) const>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TClass* pthis, TArg arg,
            const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<true>(func, TArgs(pthis, arg), loader);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2) const>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TClass* pthis,
            TArg1 arg1, TArg2 arg2, const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<true>(func, TArgs(pthis, arg1, arg2), loader);
        }
    };

    template <class TResult, class TClass, class TArg1, class TArg2,
        class TArg3>
    struct TMockHandler<TResult (TClass::*)(TArg1, TArg2, TArg3) const>
    {
        template <class TFunc>
        static inline TResult Handle(TFunc func, const TClass* pthis,
            TArg1 arg1, TArg2 arg2, TArg3 arg3, const TSymbolLoader& loader)
        {
            typedef typename IMock<TFunc>::TArgs_ TArgs;
            return GetValue<true>(func, TArgs(pthis, arg1, arg2, arg3),
                loader);
        }
    };
}

#endif

