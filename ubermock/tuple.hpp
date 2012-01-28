/*
 * tuple.hpp                -- heterogeneous tuples construction set
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

#ifndef __TUPLE_HPP_2012_01_26__
#define __TUPLE_HPP_2012_01_26__

namespace NUberMock
{
    template <class TArg1 = void, class TArg2 = void, class TArg3 = void,
        class TArg4 = void, class TArg5 = void>
    struct TTuple
    {
        TArg1 Arg1_;
        TArg2 Arg2_;
        TArg3 Arg3_;
        TArg4 Arg4_;
        TArg5 Arg5_;
        static const unsigned Arity_ = 5;

        inline TTuple(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4,
            TArg5 arg5)
            : Arg1_(arg1)
            , Arg2_(arg2)
            , Arg3_(arg3)
            , Arg4_(arg4)
            , Arg5_(arg5)
        {
        }
    };

    template <class TArg1, class TArg2, class TArg3, class TArg4>
    struct TTuple<TArg1, TArg2, TArg3, TArg4, void>
    {
        TArg1 Arg1_;
        TArg2 Arg2_;
        TArg3 Arg3_;
        TArg4 Arg4_;
        static const unsigned Arity_ = 4;

        inline TTuple(TArg1 arg1, TArg2 arg2, TArg3 arg3, TArg4 arg4)
            : Arg1_(arg1)
            , Arg2_(arg2)
            , Arg3_(arg3)
            , Arg4_(arg4)
        {
        }

        template <class TArg>
        inline TTuple<TArg, TArg1, TArg2, TArg3, TArg4> Prepend(TArg arg) const
        {
            return TTuple<TArg, TArg1, TArg2, TArg3, TArg4>(arg, Arg1_, Arg2_,
                Arg3_, Arg4_);
        }
    };

    template <class TArg1, class TArg2, class TArg3>
    struct TTuple<TArg1, TArg2, TArg3, void, void>
    {
        TArg1 Arg1_;
        TArg2 Arg2_;
        TArg3 Arg3_;
        static const unsigned Arity_ = 3;

        inline TTuple(TArg1 arg1, TArg2 arg2, TArg3 arg3)
            : Arg1_(arg1)
            , Arg2_(arg2)
            , Arg3_(arg3)
        {
        }

        template <class TArg>
        inline TTuple<TArg, TArg1, TArg2, TArg3> Prepend(TArg arg) const
        {
            return TTuple<TArg, TArg1, TArg2, TArg3>(arg, Arg1_, Arg2_, Arg3_);
        }
    };

    template <class TArg1, class TArg2>
    struct TTuple<TArg1, TArg2, void, void, void>
    {
        TArg1 Arg1_;
        TArg2 Arg2_;
        static const unsigned Arity_ = 2;

        inline TTuple(TArg1 arg1, TArg2 arg2)
            : Arg1_(arg1)
            , Arg2_(arg2)
        {
        }

        template <class TArg>
        inline TTuple<TArg, TArg1, TArg2> Prepend(TArg arg) const
        {
            return TTuple<TArg, TArg1, TArg2>(arg, Arg1_, Arg2_);
        }
    };

    template <class TArg>
    struct TTuple<TArg, void, void, void, void>
    {
        TArg Arg_;
        static const unsigned Arity_ = 1;

        inline explicit TTuple(TArg arg)
            : Arg_(arg)
        {
        }

        template <class TNewArg>
        inline TTuple<TNewArg, TArg> Prepend(TNewArg arg) const
        {
            return TTuple<TNewArg, TArg>(arg, Arg_);
        }
    };

    template <>
    struct TTuple<void, void, void, void, void>
    {
        static const unsigned Arity_ = 0;

        template <class TArg>
        inline TTuple<TArg> Prepend(TArg arg) const
        {
            return TTuple<TArg>(arg);
        }
    };
}

#endif

