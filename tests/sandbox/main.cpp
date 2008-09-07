
// Copyright Joel Riendeau        2008
//           Jean-Philippe Gravel 2008
//           Jean-Olivier Racine  2008
//
// Distributed under the New BSD License. 
// (See accompanying file NewBSDLicense.txt or copy at 
// http://www.opensource.org/licenses/bsd-license.php)

#include "fixed.hpp"

int main(int argc, char* argv[])
{
    Q<16,16> a, b, c;
    Q<10,10> d;
    a = 45.125f;
    d = 45.125f;
    bool eq = (a == d);

    unsigned int x = 0xf0001234;
    unsigned short y = 0x1234;
    bool t = (y == (unsigned short)x);

    float res = c;

    return 0;
}