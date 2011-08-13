#include "fixed.hpp"
#include "utilities.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(MultiplicationTest)
{
    const Q<8,8> a( 1.50f);
    const Q<8,8> b( 0.89f);
    const Q<8,8> c(10.20f);
    const Q<8,8> d( 0.09f);
    
    {
        Q<8,8> r = a*b;
        BOOST_CHECK( checkTypeStr(
            "( Q8,8 * Q8,8 ) >> 8 [Q8,8]",
            r.typeStr) );
    }

    {
        Q<8,8> r = a*b*c*d;
        BOOST_CHECK( checkTypeStr(
            "( Q8,8 * Q8,8 * Q8,8 * Q8,8 ) >> 24 [Q8,8]",
            r.typeStr) );
    }

    {
        Q<16,16> r = a*b*c*d;
        BOOST_CHECK( checkTypeStr(
            "( Q8,8 * Q8,8 * Q8,8 * Q8,8 ) >> 16 [Q16,16]",
            r.typeStr) );
    }

    {
        Q<8,8> r = a*b*c*d*b*c;
        BOOST_CHECK( checkTypeStr(
            "( "
            "  ( "
            "    ( Q8,8 * Q8,8 * Q8,8 * Q8,8 ) >> 16 [Q16,16]"
            "  ) * Q8,8 * Q8,8"
            ") >> 24 [Q8,8]",
            r.typeStr) );
    }


    {
        Q<8,8> r = (a*b*c)*(b*c*(a*d));
        BOOST_CHECK( checkTypeStr(
            "( "
            "  ( "
            "    ( Q8,8 * Q8,8 * Q8,8 ) >> 8 [Q16,16]"
            "  ) "
            "  * "
            "  ("
            "    ( Q8,8 * Q8,8 * ( Q8,8 * Q8,8 ) ) >> 16 [Q16,16]"
            "  )"
            ") >> 24 [Q8,8]",
            r.typeStr) );
    }

    {
        Q<8,8> r = ( (a*b*c)*(b*c*(a*d)) ) * (c);
        BOOST_CHECK( checkTypeStr(
            "( "
            "  ( "
            "    ( "
            "      ( Q8,8 * Q8,8 * Q8,8 ) >> 12 [Q12,12]"
            "    ) "
            "    * "
            "    ("
            "      ( Q8,8 * Q8,8 * ( Q8,8 * Q8,8 ) ) >> 20 [Q12,12]"
            "    )"
            "  ) "
            "  * "
            "  Q8,8 "
            ") >> 24 [Q8,8]",
            r.typeStr) );
    }
}