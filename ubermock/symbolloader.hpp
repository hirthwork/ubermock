/*
 * symbolloader.hpp         -- automatic function pointer converting
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

#ifndef __SYMBOL_LOADER_2012_01_16__
#define __SYMBOL_LOADER_2012_01_16__

namespace NBacktrace
{
    struct TBacktrace;
}

namespace NUberMock
{
    class TSymbolLoader
    {
        void* const FunctionPointer_;
        const NBacktrace::TBacktrace* const Backtrace_;

        TSymbolLoader& operator = (const TSymbolLoader&);

        // hack used to get rid of strict-aliasing warning
        void ConvertFunctionPointer(void** dest) const;

    public:
        TSymbolLoader();
        TSymbolLoader(const TSymbolLoader& loader);
        ~TSymbolLoader();

        const NBacktrace::TBacktrace& GetBacktrace() const;

        template <class TFunc>
        inline operator TFunc() const
        {
            TFunc function = 0;
            ConvertFunctionPointer(reinterpret_cast<void**>(&function));
            return function;
        }
    };
}

#endif

