// Copyright Joel Riendeau        2008
//           Jean-Philippe Gravel 2008
//           Jean-Olivier Racine  2008
//
// Distributed under the New BSD License. 
// (See accompanying file NewBSDLicense.txt or copy at 
// http://www.opensource.org/licenses/bsd-license.php)

#ifdef _DEBUG
#define DEBUG_MODE
#endif

#include "fixed.hpp"

#include <boost/numeric/ublas/vector.hpp>
#include <fstream>
#include <stdio.h>

#include <boost/mpl/vector.hpp>

// Call the test function from another compilation unit to prevent the
// optimizer from optimizing out the whole code
Q<8,8> test(const Q<8,8> vec[]);

int main(int argc, char* argv[])
{/*
    std::ifstream f("D:\\Dev\\fixed\\fixed\\input.txt");
    int val1a, val1b, val2a, val2b, val3a, val3b, val4a, val4b;
    f >> val1a >> val1b >> val2a >> val2b >> val3a >> val3b >> val4a >> val4b;
    
    Q<8,8> a(val1a, val1b);
    Q<8,8> b(val2a, val2b);
    Q<8,8> c(val3a, val3b);
    Q<8,8> d(val4a, val4b);
    */

    Q<8,8> fixedVec[4] =
    {
        Q<8,8>(5, 125),
        Q<8,8>(4, 55),
        Q<8,8>(1, 44),
        Q<8,8>(2, 1)
    };

    Q<8,8> r = test(fixedVec);

#ifdef DEBUG_MODE
    printf("%s\n", r.debugStr.c_str());
#endif

    float rf = r;
    //float rf = (float)(val1a*val1b*val2a*val2b);


//    printf("%d %d %d %d",b1, b2, b3, b4);
//    printf("%f, %f, %f, %f", (float)a, (float)b, (float)c, (float)d);
    printf("%f\n", rf);

    return 0;
}
