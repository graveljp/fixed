#include <boost/test/unit_test.hpp>
#include "fixed.hpp"

BOOST_AUTO_TEST_CASE(ComparisonTest)
{
    Q<8, 8> f0(13);
    Q<8, 8> f1(28);
    Q<8, 8> f2(1);
    Q<8, 8> f3(f0);

    BOOST_CHECK(f0 == f3);
    BOOST_CHECK(f0 < f1);
    BOOST_CHECK(f0 > f2);
    BOOST_CHECK(f0 >= f3);
    BOOST_CHECK(f0 <= f3);
    BOOST_CHECK(f0 != f1);

    Q<-8, 8> f0n(13);
    Q<-8, 8> f1n(-28);
    Q<-8, 8> f2n(-1);
    Q<-8, 8> f3n(f0n);

    BOOST_CHECK(f0n == f3n);
    BOOST_CHECK(f0n > f1n);
    BOOST_CHECK(f2n < f0n);
    BOOST_CHECK(f0n >= f3n);
    BOOST_CHECK(f0n <= f3n);
    BOOST_CHECK(f1n != f2n);
}