
#ifndef FIXED_FIXED_HPP_INCLUDED
#define FIXED_FIXED_HPP_INCLUDED

// Copyright Joel Riendeau        2008
//           Jean-Philippe Gravel 2008
//           Jean-Olivier Racine  2008
//
// Distributed under the New BSD License. 
// (See accompanying file NewBSDLicense.txt or copy at 
// http://www.opensource.org/licenses/bsd-license.php)

#include "integer_types.hpp"
#include "boost\mpl\if.hpp"

template <sint8_t Magnitude, uint8_t Fractional>
class Q
{
public:
    Q() : m_Comp(0) {}
    template <sint8_t M, uint8_t F>
    explicit Q(const Q<M,F>& val)
    {
        m_Comp = (Fractional > F) ?
                    static_cast<MagnType>(val.m_Comp << (Fractional - F)) :
                    static_cast<MagnType>(val.m_Comp >> (F - Fractional)) ;
    }
    template <typename T>
	Q(T val) : m_Magn(static_cast<MagnType>(val)), m_Frac(0) {}

	Q(float val)
    {
        m_Comp = static_cast<MagnType>(val * (1 << Fractional));
    }

	Q(double val)
    {
        m_Comp = static_cast<MagnType>(val * (1 << Fractional));
    }

    template <typename T>
    operator T() const
    {
        return static_cast<T>(m_Magn);
    }

    operator float() const
    {   
        float result = static_cast<float>(m_Comp);
        ((FloatFormat*)&result)->exponent -= Fractional;
        return (0 == m_Comp) ? 0.0f : result;
    }

    template <sint8_t M, uint8_t F>
    bool operator==(const Q<M,F>& val) const
    {
        return (m_Magn == val.m_Magn) && (m_Frac == val.m_Frac);
    }
    bool operator!=(const Q& val) const {return m_Comp != val.m_Comp;}
    bool operator< (const Q& val) const {return m_Comp <  val.m_Comp;}
    bool operator<=(const Q& val) const {return m_Comp <= val.m_Comp;}
    bool operator> (const Q& val) const {return m_Comp >  val.m_Comp;}
    bool operator>=(const Q& val) const {return m_Comp >= val.m_Comp;}

    Q operator+ (const Q& val) const {Q res; res.m_Comp = m_Comp + val.m_Comp; return res;}
    Q operator+=(const Q& val)       {m_Comp += val.m_Comp; return *this;}
    Q operator- (const Q& val) const {Q res; res.m_Comp = m_Comp - val.m_Comp; return res;}
    Q operator-=(const Q& val)       {m_Comp -= val.m_Comp; return *this;}
    Q operator* (const Q& val) const
    {
        Q res;
        res.m_Comp = (static_cast<MultiplyType>(m_Comp) *
                      static_cast<MultiplyType>(val.m_Comp)) >> Fractional;
        return res;
    }
    Q operator*=(const Q& val)
    {
        m_Comp =  (static_cast<MultiplyType>(m_Comp) *
                   static_cast<MultiplyType>(val.m_Comp)) >> Fractional;
        return *this;
    }
    Q operator/(const Q& val) const
    {
        Q res;
        if (val.m_Comp == 0) res.m_Comp = ~val.m_Comp;
        res.m_Comp = ((static_cast<MultiplyType>(m_Comp) << Fractional) / val.m_Comp) >> Fractional;
        return res;
    }
    Q operator/=(const Q& val)
    {
        if (val.m_Comp == 0)
            m_Comp = ~val.m_Comp;
        else
            m_Comp = ((static_cast<MultiplyType>(m_Comp) << Fractional) / val.m_Comp) >> Fractional;
        return *this;
    }

    // A template to select the smallest integer type for a given amount of bits
    template <uint8_t Bits, bool Signed> struct FixedInteger
    {
        typedef typename boost::mpl::if_c<(Bits <= 8 && Signed),   sint8_t
              , typename boost::mpl::if_c<(Bits <= 8 && !Signed),  uint8_t
              , typename boost::mpl::if_c<(Bits <= 16 && Signed),  sint16_t
              , typename boost::mpl::if_c<(Bits <= 16 && !Signed), uint16_t
              , typename boost::mpl::if_c<(Bits <= 32 && Signed),  sint32_t
              , typename boost::mpl::if_c<(Bits <= 32 && !Signed), uint32_t
              , typename boost::mpl::if_c<(Bits <= 64 && Signed),  sint64_t
              , typename boost::mpl::if_c<(Bits <= 64 && !Signed), uint64_t
              , void>::type >::type >::type >::type >::type >::type >::type >::type type;
    };

    enum
    {
        NBits = (Magnitude < 0 ? -Magnitude : Magnitude) + Fractional,
        NBits_Magn = (Magnitude < 0 ? -Magnitude : Magnitude),
        NBits_Frac = Fractional
    };

    typedef typename FixedInteger<NBits,   (Magnitude < 0)>::type MagnType;
    typedef typename FixedInteger<NBits,   false>::type           FracType;
    typedef typename FixedInteger<NBits*2, (Magnitude < 0)>::type MultiplyType;
    typedef typename FixedInteger<(NBits > sizeof(float) ? NBits : sizeof(float)), false>::type FloatCastType;

    FracType Frac() {return m_Frac;}

    union
    {
        struct
        {
            FracType m_Frac : NBits_Frac;
            MagnType m_Magn : NBits_Magn;
        };
        MagnType m_Comp;
    };

private:
    typedef union FloatFormat
    {
        struct
        {
            uint32_t mantissa : 23;
            uint32_t exponent : 8;
            uint32_t sign : 1;
        };
        uint32_t full;
    } FloatFormat;
};

template <sint8_t Magnitude, uint8_t Fractional>
Q<Magnitude, Fractional> sqrt(const Q<Magnitude, Fractional>& val)
{
    //if (Magnitude < 0)
    //    return MAX_VAL
    Q<Magnitude, Fractional>::MultiplyType temp = val.m_Comp << Fractional;
    Q<Magnitude, Fractional>::InternalType root = 0, test;
    for (Sint8 i = Q<Magnitude, Fractional>::NBits - 1; i >= 0; i--)
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

#endif