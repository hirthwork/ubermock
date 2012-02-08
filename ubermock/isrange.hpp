#ifndef __ISRANGE_HPP_2012_02_08__
#define __ISRANGE_HPP_2012_02_08__

namespace NUberMock
{
    template <class TRange>
    class TIsRange
    {
        typedef char TTwoChars[2];

        template <class T>
        static char Test(bool (T::*)() = &T::IsEmpty, void (T::*)() = &T::Pop,
            int [sizeof(((T*)0)->Front()) ? 1 : -1] = 0);

        template <class>
        static TTwoChars& Test(...);

    public:
        static const bool Value_ = sizeof(Test<TRange>(0, 0, 0)) == 1;
    };
}

#endif

