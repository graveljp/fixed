
#ifndef FIXED_INTEGER_TYPES_HPP_INCLUDED
#define FIXED_INTEGER_TYPES_HPP_INCLUDED

// Copyright Joel Riendeau        2008
//           Jean-Philippe Gravel 2008
//           Jean-Olivier Racine  2008
//
// Distributed under the New BSD License. 
// (See accompanying file NewBSDLicense.txt or copy at 
// http://www.opensource.org/licenses/bsd-license.php)

#include "boost/config.hpp"

#if defined (BOOST_MSVC)

    typedef unsigned char uint8_t;
    typedef char sint8_t;
    typedef unsigned short uint16_t;
    typedef short sint16_t;
    typedef unsigned long uint32_t;
    typedef long sint32_t;
    typedef unsigned long long uint64_t;
    typedef long long sint64_t;

#else
// Integer types for compiler not yet defined
#   error "Unsupported compiler"

#endif

#endif