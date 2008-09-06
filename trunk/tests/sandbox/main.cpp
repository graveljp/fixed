
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
    a = 45.045f;
    b = 33.2334f;

    c = a * b;

    float res = c;

    return 0;
}