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

#include <range/isrange.hpp>

#include <reinvented-wheels/enableif.hpp>

#include "call.hpp"
#include "mockhandler.hpp"
#include "mocks.hpp"

namespace NUberMock
{
    template <class TResult, class TResultGenerator, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        NRange::TIsRange<TResultGenerator>::Value_, TResult>::TType_
        GetResult(TResultGenerator& resultGenerator, const TArgs&)
    {
        const TResult& result = resultGenerator.Front();
        resultGenerator.Pop();
        return result;
    }

    template <class TResult, class TResultGenerator, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !NRange::TIsRange<TResultGenerator>::Value_, TResult>::TType_
        GetResult(TResultGenerator& resultGenerator, const TArgs& args)
    {
        return Call<TResult, false>(resultGenerator, args);
    }

    template <class TFunc, class TCheck, class TResultGenerator>
    struct IGeneratingMock: IMock<TFunc>
    {
        typedef IMock<TFunc> TBase;
        typedef typename TBase::TArgs_ TArgs_;
        typedef typename TBase::TResult_ TResult_;

        const TCheck Check_;
        TResultGenerator ResultGenerator_;

        inline IGeneratingMock(TCheck check, TResultGenerator resultGenerator)
            : Check_(check)
            , ResultGenerator_(resultGenerator)
        {
        }

        virtual TResult_ GetResult(const TArgs_& args)
        {
            return NUberMock::GetResult<TResult_>(ResultGenerator_, args);
        }
    };

    template <class TCheck, class TResultGenerator, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        NRange::TIsRange<TResultGenerator>::Value_, bool>::TType_
        CheckResultGenerator(TCheck check,
            const TResultGenerator& resultGenerator, const TArgs& args)
    {
        return !resultGenerator.IsEmpty()
            && Call<bool, false>(check, args);
    }

    template <class TCheck, class TResultGenerator, class TArgs>
    static inline typename NReinventedWheels::TEnableIf<
        !NRange::TIsRange<TResultGenerator>::Value_, bool>::TType_
        CheckResultGenerator(TCheck check,
            const TResultGenerator& resultGenerator, const TArgs& args)
    {
        return Call<bool, false>(check, args);
    }

    template <class TFunc, class TCheck, class TResultGenerator,
        bool UseBacktrace>
    struct TMock: IGeneratingMock<TFunc, TCheck, TResultGenerator>
    {
        typedef IGeneratingMock<TFunc, TCheck, TResultGenerator> TBase;
        inline TMock(TCheck check, TResultGenerator resultGenerator)
            : TBase(check, resultGenerator)
        {
        }

        virtual bool Check(const NBacktrace::TBacktrace& backtrace,
            const typename TBase::TArgs_& args) const
        {
            return CheckResultGenerator(this->Check_, this->ResultGenerator_,
                args.template Prepend<const NBacktrace::TBacktrace&>(backtrace)
            );
        }
    };

    template <class TFunc, class TCheck, class TResultGenerator>
    struct TMock<TFunc, TCheck, TResultGenerator, false>:
        IGeneratingMock<TFunc, TCheck, TResultGenerator>
    {
        typedef IGeneratingMock<TFunc, TCheck, TResultGenerator> TBase;
        inline TMock(TCheck check, TResultGenerator resultGenerator)
            : TBase(check, resultGenerator)
        {
        }

        virtual bool Check(const NBacktrace::TBacktrace&,
            const typename TBase::TArgs_& args) const
        {
            return CheckResultGenerator(this->Check_, this->ResultGenerator_,
                args);
        }
    };

    template <class TFunc, bool UseBacktrace, class TCheck,
        class TResultGenerator>
    static inline IMock<TFunc>* CreateCheck(TCheck check,
        TResultGenerator resultGenerator)
    {
        return new TMock<TFunc, TCheck, TResultGenerator, UseBacktrace>(
            check, resultGenerator);
    }

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
        template <class TFunc, class TCheck, class TResultGenerator>
        inline TMockRegistrar(TFunc func, TCheck check,
            TResultGenerator resultGenerator)
            : TRegistrarBase(new TCleaner<TFunc>(TMockStorage<TFunc>::AddMock(
                func, CreateCheck<TFunc, true>(check, resultGenerator))))
        {
        }
    };

    struct TSimpleMockRegistrar: TRegistrarBase
    {
        template <class TFunc, class TCheck, class TResultGenerator>
        inline TSimpleMockRegistrar(TFunc func, TCheck check,
            TResultGenerator resultGenerator)
            : TRegistrarBase(new TCleaner<TFunc>(TMockStorage<TFunc>::AddMock(
                func, CreateCheck<TFunc, false>(check, resultGenerator))))
        {
        }
    };
}

#endif

