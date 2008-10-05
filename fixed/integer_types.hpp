
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

#if defined (BOOST_MSVC) || defined (BOOST_INTEL)
    typedef unsigned char      uint8_t;
    typedef signed   char      sint8_t;
    typedef unsigned short     uint16_t;
    typedef signed   short     sint16_t;
    typedef unsigned long      uint32_t;
    typedef signed   long      sint32_t;
    typedef unsigned long long uint64_t;
    typedef signed   long long sint64_t;
#elif defined (__GNUC__)
	#include <stdint.h>
	typedef int8_t  sint8_t;
	typedef int16_t sint16_t;
	typedef int32_t sint32_t;
	typedef int64_t sint64_t;
#else
// Integer types for compiler not yet defined
#   error "Unsupported compiler"
#endif

#endif
