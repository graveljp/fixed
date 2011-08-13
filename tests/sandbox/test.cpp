#ifdef _DEBUG
#define DEBUG_MODE
#endif

#include "fixed.hpp"

Q<8,8> test(const Q<8,8> vec[])
{
    return (vec[0]*(vec[1]*vec[2])*vec[3])*(vec[2]*vec[2]*vec[1]);
};