#include "UnitTest++.h"
#include "fixed.hpp"

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

        uint16_t u = 45;
        Q<8, 8> f3(u);
        CHECK_EQUAL(static_cast<uint16_t>(f3), u);

        sint16_t s = -33;
        Q<-8, 8> f4(s);
        CHECK_EQUAL(static_cast<sint16_t>(f4), s);
        CHECK_EQUAL(static_cast<float>(f4), -33.f);
    }
}