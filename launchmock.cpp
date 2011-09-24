#include <dlfcn.h>
#include <reinvented-wheels/backtrace.hpp>
#include "launch.hpp"

int TLaunch::GetValue(int i) const {
    if (i == 5)
    {
        return i << 2;
    }
    else
    {
        typedef int (*symbol)(const TLaunch*, int i);
        symbol sym = reinterpret_cast<symbol>(dlsym(RTLD_NEXT,
            NReinventedWheels::GetCurrentFrame().Symbol_.c_str()));
        return sym(this, i);
    }
}

