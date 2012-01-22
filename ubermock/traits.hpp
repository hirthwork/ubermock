/*
 * traits.hpp               -- functional traits
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

#ifndef __TRAITS_HPP_2011_11_13__
#define __TRAITS_HPP_2011_11_13__

namespace NBacktrace
{
    struct TBacktrace;
}

namespace NUberMock
{
    template <class TArg1, class TArg2>
    struct ICheckBinaryFunction
    {
        virtual inline ~ICheckBinaryFunction()
        {
        }

        virtual bool Check(const NBacktrace::TBacktrace&,
            TArg1, TArg2) const = 0;
    };

    template <class TArg1, class TArg2, class TArg3>
    struct ICheckTernaryFunction
    {
        virtual inline ~ICheckTernaryFunction()
        {
        }

        virtual bool Check(const NBacktrace::TBacktrace&,
            TArg1, TArg2, TArg3) const = 0;
    };

    template <class TArg1, class TArg2, class TArg3, class TArg4>
    struct ICheckQuaternaryFunction
    {
        virtual inline ~ICheckQuaternaryFunction()
        {
        }

        virtual bool Check(const NBacktrace::TBacktrace&,
            TArg1, TArg2, TArg3, TArg4) const = 0;
    };

    struct TCheck {
        virtual inline ~TCheck()
        {
        }
    };

    template <class TFunc>
    struct TFunctionTraits;

    template <class TResult>
    struct TFunctionTraits<TResult (*)()>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            virtual bool Check(const NBacktrace::TBacktrace&) const = 0;
        };

        static const unsigned Arity_ = 0;
    };

    template <class TResult, class TArg>
    struct TFunctionTraits<TResult (*)(TArg)>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef TArg TArg_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                TArg_) const = 0;
        };

        static const unsigned Arity_ = 1;
    };

    template <class TResult, class TArg1, class TArg2>
    struct TFunctionTraits<TResult (*)(TArg1, TArg2)>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef TArg1 TArg1_;
            typedef TArg2 TArg2_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                TArg1, TArg2) const = 0;
        };

        static const unsigned Arity_ = 2;
    };

    template <class TResult, class TArg1, class TArg2, class TArg3>
    struct TFunctionTraits<TResult (*)(TArg1, TArg2, TArg3)>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef TArg1 TArg1_;
            typedef TArg2 TArg2_;
            typedef TArg3 TArg3_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                TArg1, TArg2, TArg3) const = 0;
        };

        static const unsigned Arity_ = 3;
    };

    template <class TResult, class TArg1, class TArg2, class TArg3, class TArg4>
    struct TFunctionTraits<TResult (*)(TArg1, TArg2, TArg3, TArg4)>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef TArg1 TArg1_;
            typedef TArg2 TArg2_;
            typedef TArg3 TArg3_;
            typedef TArg4 TArg4_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                TArg1, TArg2, TArg3, TArg4) const = 0;
        };

        static const unsigned Arity_ = 4;
    };

    template <class TResult, class TClass>
    struct TFunctionTraits<TResult (TClass::*)()>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef TClass* TArg_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                TClass*) const = 0;
        };

        static const unsigned Arity_ = 1;
    };

    template <class TResult, class TClass, class TArg>
    struct TFunctionTraits<TResult (TClass::*)(TArg)>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef TClass* TArg1_;
            typedef TArg TArg2_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                TClass*, TArg) const = 0;
        };

        static const unsigned Arity_ = 2;
    };

    template <class TResult, class TClass, class TArg1, class TArg2>
    struct TFunctionTraits<TResult (TClass::*)(TArg1, TArg2)>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef TClass* TArg1_;
            typedef TArg1 TArg2_;
            typedef TArg2 TArg3_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                TClass*, TArg1, TArg2) const = 0;
        };

        static const unsigned Arity_ = 3;
    };

    template <class TResult, class TClass, class TArg1, class TArg2,
        class TArg3>
    struct TFunctionTraits<TResult (TClass::*)(TArg1, TArg2, TArg3)>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef TClass* TArg1_;
            typedef TArg1 TArg2_;
            typedef TArg2 TArg3_;
            typedef TArg3 TArg4_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                TClass*, TArg1, TArg2, TArg3) const = 0;
        };

        static const unsigned Arity_ = 4;
    };

    template <class TResult, class TClass>
    struct TFunctionTraits<TResult (TClass::*)() const>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef const TClass* TArg_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                const TClass*) const = 0;
        };

        static const unsigned Arity_ = 1;
    };

    template <class TResult, class TClass, class TArg>
    struct TFunctionTraits<TResult (TClass::*)(TArg) const>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef const TClass* TArg1_;
            typedef TArg TArg2_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                const TClass*, TArg) const = 0;
        };

        static const unsigned Arity_ = 2;
    };

    template <class TResult, class TClass, class TArg1, class TArg2>
    struct TFunctionTraits<TResult (TClass::*)(TArg1, TArg2) const>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef const TClass* TArg1_;
            typedef TArg1 TArg2_;
            typedef TArg2 TArg3_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                const TClass*, TArg1, TArg2) const = 0;
        };

        static const unsigned Arity_ = 3;
    };

    template <class TResult, class TClass, class TArg1, class TArg2,
        class TArg3>
    struct TFunctionTraits<TResult (TClass::*)(TArg1, TArg2, TArg3) const>
    {
        typedef TResult TResult_;

        struct TCheck_ : TCheck
        {
            typedef const TClass* TArg1_;
            typedef TArg1 TArg2_;
            typedef TArg2 TArg3_;
            typedef TArg3 TArg4_;
            virtual bool Check(const NBacktrace::TBacktrace&,
                const TClass*, TArg1, TArg2, TArg3) const = 0;
        };

        static const unsigned Arity_ = 4;
    };
}

#endif

