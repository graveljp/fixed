#include "UnitTest++.h"
#include "FixedPoint.hpp"

using namespace UnitTest;

namespace
{
	TEST(Construct_Cast)
	{
        Q<8, 8> f0;
        CHECK_EQUAL(static_cast<float>(f0), 0.0f);

        float ft = 3.75f;
		Q<8, 8> f1(ft);
        CHECK_EQUAL(static_cast<float>(f1), ft);

        ft = -3.75f;
		Q<-8, 8> f1n(ft);
        CHECK_EQUAL(static_cast<float>(f1n), ft);

        Q<-8, 8> f2(f1n);
        CHECK_EQUAL(static_cast<float>(f2), ft);

        Uint16 u = 45;
        Q<8, 8> f3(u);
        CHECK_EQUAL(static_cast<Uint16>(f3), u);

        Sint16 s = -33;
        Q<-8, 8> f4(s);
        CHECK_EQUAL(static_cast<Sint16>(f4), s);
        CHECK_EQUAL(static_cast<float>(f4), -33.f);
    }

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