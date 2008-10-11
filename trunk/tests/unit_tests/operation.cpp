#include <boost/test/unit_test.hpp>
#include "fixed.hpp"

#include <conio.h>

BOOST_AUTO_TEST_CASE(OperationTest)
{
	Q<8, 8> f0 = 2.03125f;
	Q<8, 8> f1 = 4.015625f;
	Q<8, 8> r0 = f0 + f1;
	BOOST_CHECK_EQUAL(static_cast<float>(r0), 6.046875f);

	_getch();
}