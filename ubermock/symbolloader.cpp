/*
 * symbolloader.cpp         -- automatic symbol loading routine
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

#include <dlfcn.h>

#include <backtrace/backtrace.hpp>
#include <backtrace/current-frame.hpp>

#include "symbolloader.hpp"

NUberMock::TSymbolLoader::TSymbolLoader()
    : FunctionPointer_(
        dlsym(RTLD_NEXT, NBacktrace::GetCurrentFrame(1).Symbol_))
    , Backtrace_(new NBacktrace::TBacktrace(NBacktrace::GetBacktrace(2)))
{
}

NUberMock::TSymbolLoader::TSymbolLoader(const NUberMock::TSymbolLoader& loader)
    : FunctionPointer_(loader.FunctionPointer_)
    , Backtrace_(new NBacktrace::TBacktrace(*loader.Backtrace_))
{
}

NUberMock::TSymbolLoader::~TSymbolLoader()
{
    delete Backtrace_;
}

const NBacktrace::TBacktrace& NUberMock::TSymbolLoader::GetBacktrace() const
{
    return *Backtrace_;
}

void NUberMock::TSymbolLoader::ConvertFunctionPointer(void* dest) const
{
    reinterpret_cast<void**>(dest)[0] = FunctionPointer_;
}

