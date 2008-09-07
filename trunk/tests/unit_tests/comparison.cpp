#include "UnitTest++.h"
#include "fixed.hpp"

using namespace UnitTest;

namespace
{
    TEST(Comparison)
    {
        Q<8, 8> f0(13);
        Q<8, 8> f1(28);
        Q<8, 8> f2(1);
        Q<8, 8> f3(f0);

        CHECK(f0 == f3);
        CHECK(f0 < f1);
        CHECK(f0 > f2);
        CHECK(f0 >= f3);
        CHECK(f0 <= f3);
        CHECK(f0 != f1);

        Q<-8, 8> f0n(13);
        Q<-8, 8> f1n(-28);
        Q<-8, 8> f2n(-1);
        Q<-8, 8> f3n(f0n);

        CHECK(f0n == f3n);
        CHECK(f0n > f1n);
        CHECK(f2n < f0n);
        CHECK(f0n >= f3n);
        CHECK(f0n <= f3n);
        CHECK(f1n != f2n);
    }
}