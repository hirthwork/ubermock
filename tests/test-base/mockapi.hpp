#ifndef __MOCKAPI_HPP_2012_01_22__
#define __MOCKAPI_HPP_2012_01_22__

extern int Nullary();
extern int Unary(int);
extern int Binary(int, int);
extern int Ternary(int, int, int);
extern int Quaternary(int, int, int, int);

struct TMockApi
{
    int State_;
    TMockApi(int state = 0);
    int Nullary();
    int Unary(int);
    int Binary(int, int);
    int Ternary(int, int, int);
    int NullaryConst() const;
    int UnaryConst(int) const;
    int BinaryConst(int, int) const;
    int TernaryConst(int, int, int) const;
};

#endif

