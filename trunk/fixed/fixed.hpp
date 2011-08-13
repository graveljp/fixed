
#ifndef FIXED_FIXED_HPP_INCLUDED
#define FIXED_FIXED_HPP_INCLUDED

// Copyright Joel Riendeau        2008
//           Jean-Philippe Gravel 2008
//           Jean-Olivier Racine  2008
//
// Distributed under the New BSD License. 
// (See accompanying file NewBSDLicense.txt or copy at 
// http://www.opensource.org/licenses/bsd-license.php)

#define USING_XPR_OPTIMIZER 1

#include "integer_types.hpp"
#include "QXpr.hpp"

#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>
#include <boost/assert.hpp>

#ifdef DEBUG_MODE
#include <boost/lexical_cast.hpp>
#endif //DEBUG_MODE

// A template to select the smallest integer type for a given amount of bits
template <uint8_t Bits, bool Signed> struct FixedInteger
{
    typedef typename boost::mpl::if_c<(Bits <= 8 && Signed),   sint32_t
          , typename boost::mpl::if_c<(Bits <= 8 && !Signed),  uint32_t
          , typename boost::mpl::if_c<(Bits <= 16 && Signed),  sint32_t
          , typename boost::mpl::if_c<(Bits <= 16 && !Signed), uint32_t
          , typename boost::mpl::if_c<(Bits <= 32 && Signed),  sint32_t
          , typename boost::mpl::if_c<(Bits <= 32 && !Signed), uint32_t
          , typename boost::mpl::if_c<(Bits <= 64 && Signed),  sint64_t
          , typename boost::mpl::if_c<(Bits <= 64 && !Signed), uint64_t
          , void>::type >::type >::type >::type >::type >::type >::type >::type type;
};

template<uint8_t Bits> struct BitMask
{
    typedef typename FixedInteger<Bits, false>::type type;
    static const type value = static_cast<type>(-1) >> (sizeof(type)*8-Bits);
};


template <sint8_t Mag, uint8_t Fract>
class Q : public QXpr<Q<Mag, Fract> >
{
public:
    enum
    {
        Magnitude = Mag,
        Fractional = Fract,
        NBits_Magn = (Magnitude < 0 ? -Magnitude : Magnitude),
        NBits_Frac = Fractional,
        NBits = NBits_Magn + NBits_Frac
    };

    typedef Q<Magnitude, Fractional> this_type;
    typedef this_type result_type;
    typedef void op_type;
    
    template<typename T>
    struct order
    {
        enum { value = 1 };
    };

    template< typename dest_type, int precisionBoost >
    struct AdjustedTypes
    {
        typedef this_type Result;
    };
    
    typedef typename FixedInteger<NBits,   (Magnitude < 0)>::type MagnType;
    typedef typename FixedInteger<NBits,   false>::type           FracType;
    typedef typename FixedInteger<NBits*2, (Magnitude < 0)>::type MultiplyType;
    typedef typename FixedInteger<(NBits > sizeof(float) ? NBits : sizeof(float)), false>::type FloatCastType;


    template<int bitAdjustment>
    struct AdjustType
    {
      enum { magnBoost = bitAdjustment * Magnitude / NBits };
      enum { fracBoost = bitAdjustment * Fractional / NBits };
      typedef Q<Magnitude + magnBoost, Fractional + fracBoost> type;
    };


    __forceinline Q() :
        m_Magn(),
        m_Frac()
    {
#ifdef DEBUG_MODE
      debugStr = "Q" + boost::lexical_cast<std::string>(Magnitude) + "," + boost::lexical_cast<std::string>(Fractional) + "";
#endif //DEBUG_MODE
    }

    __forceinline Q(const Q& val) :
#ifdef DEBUG_MODE
          debugStr(val.debugStr),
#endif //DEBUG_MODE
          m_CompFast(val.m_CompFast & BitMask<NBits>::value )
    {
    }

    __forceinline Q(int iMagn, int iFrac) :
        m_Magn(iMagn),
        m_Frac(iFrac)
    {
#ifdef DEBUG_MODE
        debugStr = "Q" + boost::lexical_cast<std::string>(Magnitude) + "," + boost::lexical_cast<std::string>(Fractional) + "";
#endif //DEBUG_MODE
    }

    template<typename E>
    Q(const QXpr<E>& roRight)
    {
        *this = roRight().value<this_type>();
    }

    template <typename T>
    __forceinline Q( const T& val, typename boost::enable_if<boost::is_integral<T>, int >::type dummy = 0 )
    {
        m_Magn = static_cast<MagnType>(val);
        m_Frac = 0;

#ifdef DEBUG_MODE
        debugStr = "Q" + boost::lexical_cast<std::string>(Magnitude) + "," + boost::lexical_cast<std::string>(Fractional) + "";
#endif //DEBUG_MODE
    }
    
    template <typename T>
    __forceinline Q( const T& val, typename boost::enable_if<boost::is_float<T>, int >::type dummy = 0 )
    {
        m_CompFast = static_cast<MagnType>(val * (1 << Fractional)) & BitMask<NBits>::value;

#ifdef DEBUG_MODE
        debugStr = "Q" + boost::lexical_cast<std::string>(Magnitude) + "," + boost::lexical_cast<std::string>(Fractional) + "";
#endif //DEBUG_MODE
    }

    template <sint8_t M, uint8_t F>
    __forceinline Q( const Q<M,F>& val )
    {
        *this = val;
    }

    template <sint8_t M, uint8_t F>
    __forceinline typename boost::enable_if_c<(Fractional>F), this_type& >::type
    operator=( const Q<M,F>& val )
    {
        enum { shift = Fractional - F };
        m_CompFast = static_cast<MagnType>(val.m_CompFast << shift) & BitMask<NBits>::value;

#ifdef DEBUG_MODE
        debugStr = "(" + val.debugStr + " << " + boost::lexical_cast<std::string>(shift) + " [Q" + boost::lexical_cast<std::string>(Magnitude) + "," + boost::lexical_cast<std::string>(Fractional) + "] )";
#endif //DEBUG_MODE
        return *this;
    }

    template <sint8_t M, uint8_t F>
    __forceinline typename boost::enable_if_c<(Fractional<F), this_type& >::type
    operator=( const Q<M,F>&  val )
    {
        enum { shift = F - Fractional };

        m_CompFast = static_cast<MagnType>(val.m_CompExact >> shift) & BitMask<NBits>::value;
        
#ifdef DEBUG_MODE
        debugStr = "(" + val.debugStr + " >> " + boost::lexical_cast<std::string>(shift) + " [Q" + boost::lexical_cast<std::string>(Magnitude) + "," + boost::lexical_cast<std::string>(Fractional) + "] )";
#endif //DEBUG_MODE
        return *this;
    }


    template<typename E>
    __forceinline Q& operator=(const QXpr<E>& roRight);


    template<typename dest_type>
    __forceinline const result_type& value() const
    {
      return *this;
    }

    template<typename dest_type, int precisionBoost>
    __forceinline const result_type& promotedValue() const
    {
      return *this;
    }


    template<typename t>
    __forceinline operator t() const
    {
        return static_cast<t>(m_Magn);
    }

    __forceinline operator float() const
    {   
        float result = static_cast<float>(m_CompExact);
        ((FloatFormat*)&result)->exponent -= Fractional;
        return (0 == m_CompExact) ? 0.0f : result;
    }

    template <sint8_t M, uint8_t F>
    __forceinline bool operator==(const Q<M,F>& val) const
    {
        return (m_Magn == val.m_Magn) && (m_Frac == val.m_Frac);
    }
    __forceinline bool operator==(const Q& val) const {return m_CompExact == val.m_CompExact;}
    __forceinline bool operator!=(const Q& val) const {return m_CompExact != val.m_CompExact;}
    __forceinline bool operator< (const Q& val) const {return m_CompExact <  val.m_CompExact;}
    __forceinline bool operator<=(const Q& val) const {return m_CompExact <= val.m_CompExact;}
    __forceinline bool operator> (const Q& val) const {return m_CompExact >  val.m_CompExact;}
    __forceinline bool operator>=(const Q& val) const {return m_CompExact >= val.m_CompExact;}


    __forceinline FracType Frac() {return m_Frac;}

    union
    {
        struct
        {
            FracType m_Frac : NBits_Frac;
            MagnType m_Magn : NBits_Magn;
        };
        struct
        {
            MagnType m_CompExact: NBits;
        };
        MagnType m_CompFast;
    };

#ifdef DEBUG_MODE
    std::string debugStr;
#endif //DEBUG_MODE

private:
    union FloatFormat
    {
        struct
        {
            uint32_t mantissa : 23;
            uint32_t exponent : 8;
            uint32_t sign : 1;
        };
        uint32_t full;
    };
};

template <sint8_t Magnitude, uint8_t Fractional>
Q<Magnitude, Fractional> sqrt(const Q<Magnitude, Fractional>& val)
{
    //if (Magnitude < 0)
    //    return MAX_VAL
    typename Q<Magnitude, Fractional>::MultiplyType temp = val.m_CompExact << Fractional;
    typename Q<Magnitude, Fractional>::InternalType root = 0, test;
    for (sint8_t i= Q<Magnitude, Fractional>::NBits - 1; i >= 0; i--)
    {
        test = root + (1 << i);
        if (temp >= test << i)
        {   temp -= test << i;
            root |= 2 << i;
        }
    }
    return root >> 1;
}

template <sint8_t Magnitude, uint8_t Fractional>
Q<Magnitude, Fractional> floor(const Q<Magnitude, Fractional>& val)
{
    Q<Magnitude, Fractional> ret = val;
    ret.m_Frac = 0;
    return ret;
}

template <sint8_t Magnitude, uint8_t Fractional>
Q<Magnitude, Fractional> ceil(const Q<Magnitude, Fractional>& val)
{
    Q<Magnitude, Fractional> ret = val;
    if (0 != ret.m_Frac)
        ++ret.m_Magn;
    ret.m_Frac = 0;
    return ret;
}

    /*
    fixed pow(fixed fixedPower);
    fixed log10(void);
    fixed log(void);
    fixed exp(void);
    fixed cos(void);
    fixed sin(void);
    fixed tan(void);*/

#include "SimpleFiPU.hpp"

#if USING_XPR_OPTIMIZER
#include "XprOptimizer.hpp"
#else
#include "SimpleOptimizer.hpp"
#endif

#endif
