// Copyright Joel Riendeau        2008
//           Jean-Philippe Gravel 2008
//           Jean-Olivier Racine  2008
//
// Distributed under the New BSD License. 
// (See accompanying file NewBSDLicense.txt or copy at 
// http://www.opensource.org/licenses/bsd-license.php)

#ifdef _DEBUG
#define FIXED_DEBUG_MODE
#endif

#include "fixed.hpp"

#include <boost/numeric/ublas/vector.hpp>
#include <fstream>
#include <stdio.h>

#include <boost/mpl/vector.hpp>

int main(int argc, char* argv[])
{
    volatile const float val[] =
    {
        0.125f,
        1.55f,
        1.44f,
        2.1f
    };

    volatile const int ival[] =
    {
        0, 125,
        1, 55,
        1, 44,
        2, 1
    };

    typedef Q<8,8> QType;

    QType a( val[0] );
    QType b( val[1] );
    QType c( val[2] );
    QType d( val[3] );

//     QType a( ival[0], ival[1] );
//     QType b( ival[2], ival[3] );
//     QType c( ival[4], ival[5] );
//     QType d( ival[6], ival[7] );

    QType r = a*(b*c*d*c*d)*(c*c*b);
    //QType r = b*c*d*c*d;
    
    printf("%d\n", r.m_CompFast);
    printf("%f\n", (float)r);


#ifdef FIXED_DEBUG_MODE
    printf("%f\n", r.floatValue);

    float ref = val[0]*(val[1]*val[2]*val[3]*val[2]*val[3])*(val[2]*val[2]*val[1]);
    printf("%f\n", ref);

    printf("%s\n", r.typeStr.c_str());
    printf("%s\n", r.valueStr.c_str());
    printf("%s\n", r.floatStr.c_str());
#endif
    return 0;
}
