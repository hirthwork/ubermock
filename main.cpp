#include <stdio.h>
#include "launch.hpp"

int main()
{
    for (int i = 4; i <= 6; ++i)
    {
        printf("\tvalue(%d) = %i\n", i, TLaunch().GetValue(i));
    }
    printf("\tabracadabra handle = %p\n", fopen("abracadabra", "r"));
    printf("\tsomething handle = %p\n", fopen("something", "r"));
}

