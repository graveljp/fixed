#ifndef FIXED_POINT_HPP
#define FIXED_POINT_HPP

#include "Types.hpp"
#include "boost\mpl\if.hpp"

template <Sint8 Magnitude, Uint8 Fractional>
class Q
{
public:
    Q()                   : m_Comp(0) {}
    Q(const Q& val)       : m_Comp(val.m_Comp) {}
    template <typename T>
	Q(T val)              : m_Magn(static_cast<InternalType>(val)), m_Frac(0) {}

	Q(float val)
    {
        m_Comp = static_cast<InternalType>(val * (1 << Fractional));
    }

	Q(double val)
    {
        m_Comp = static_cast<InternalType>(val * (1 << Fractional));
    }

    template <typename T>
    inline operator T() const
    {
        return static_cast<T>(m_Magn);
    }

    inline operator float() const
    {   
        if (0 == m_Comp)
            return 0.0f;
        float result = static_cast<float>(m_Comp);
        ((FloatFormat*)&result)->exponent -= Fractional;
        return result;
    }

    inline bool operator==(Q val) const {return m_Comp == val.m_Comp;}
    inline bool operator!=(Q val) const {return m_Comp != val.m_Comp;}
    inline bool operator< (Q val) const {return m_Comp <  val.m_Comp;}
    inline bool operator<=(Q val) const {return m_Comp <= val.m_Comp;}
    inline bool operator> (Q val) const {return m_Comp >  val.m_Comp;}
    inline bool operator>=(Q val) const {return m_Comp >= val.m_Comp;}

    inline Q operator+ (Q val) const {Q res; res.m_Comp = m_Comp + val.m_Comp; return res;}
    inline Q operator+=(Q val)       {m_Comp += val.m_Comp; return *this;}
    inline Q operator- (Q val) const {Q res; res.m_Comp = m_Comp - val.m_Comp; return res;}
    inline Q operator-=(Q val)       {m_Comp -= val.m_Comp; return *this;}
    inline Q operator* (Q val) const
    {
        Q res;
        res.m_Comp = (static_cast<MultiplyType>(m_Comp) *
                      static_cast<MultiplyType>(val.m_Comp)) >> Fractional;
        return res;
    }
    inline Q operator*=(Q val)
    {
        m_Comp =  (static_cast<MultiplyType>(m_Comp) *
                   static_cast<MultiplyType>(val.m_Comp)) >> Fractional;
        return *this;
    }
    inline Q operator/(Q val) const
    {
        Q res;
        if (val.m_Comp == 0) res.m_Comp = ~val.m_Comp;
        res.m_Comp = ((static_cast<MultiplyType>(m_Comp) << Fractional) / val.m_Comp) >> Fractional;
        return res;
    }
    inline Q operator/=(Q val)
    {
        if (val.m_Comp == 0)
            m_Comp = ~val.m_Comp;
        else
            m_Comp = ((static_cast<MultiplyType>(m_Comp) << Fractional) / val.m_Comp) >> Fractional;
        return *this;
    }

    // A template to select the smallest integer type for a given amount of bits
    template <Uint8 Bits, bool Signed> struct FixedInteger
    {
        typedef typename boost::mpl::if_c<(Bits <= 8 && Signed), Sint8
              , typename boost::mpl::if_c<(Bits <= 8 && !Signed), Uint8
              , typename boost::mpl::if_c<(Bits <= 16 && Signed), Sint16
              , typename boost::mpl::if_c<(Bits <= 16 && !Signed), Uint16
              , typename boost::mpl::if_c<(Bits <= 32 && Signed), Sint32
              , typename boost::mpl::if_c<(Bits <= 32 && !Signed), Uint32
              , typename boost::mpl::if_c<(Bits <= 64 && Signed), Sint64
              , typename boost::mpl::if_c<(Bits <= 64 && !Signed), Uint64
              , void>::type >::type >::type >::type >::type >::type >::type >::type type;
    };

    enum
    {
        NBits = (Magnitude < 0 ? -Magnitude : Magnitude) + Fractional,
        NBits_Magn = (Magnitude < 0 ? -Magnitude : Magnitude),
        NBits_Frac = Fractional
    };

    typedef typename FixedInteger<NBits,   (Magnitude < 0)>::type InternalType;
    typedef typename FixedInteger<NBits*2, (Magnitude < 0)>::type MultiplyType;
    typedef typename FixedInteger<(NBits > sizeof(float) ? NBits : sizeof(float)), false>::type FloatCastType;

    inline InternalType Frac() {return m_Frac;}

    union
    {
        struct
        {
            InternalType m_Frac : NBits_Frac;
            InternalType m_Magn : NBits_Magn;
        };
        InternalType m_Comp;
    };

private:
    typedef union FloatFormat
    {
        struct
        {
            Uint32 mantissa : 23;
            Uint32 exponent : 8;
            Uint32 sign : 1;
        };
        Uint32 full;
    } FloatFormat;
};

template <Sint8 Magnitude, Uint8 Fractional>
inline Q<Magnitude, Fractional> sqrt(const Q<Magnitude, Fractional>& val)
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

template <Sint8 Magnitude, Uint8 Fractional>
inline Q<Magnitude, Fractional> floor(const Q<Magnitude, Fractional>& val)
{
    Q<Magnitude, Fractional> ret = val;
    ret.m_Frac = 0;
    return ret;
}

template <Sint8 Magnitude, Uint8 Fractional>
inline Q<Magnitude, Fractional> ceil(const Q<Magnitude, Fractional>& val)
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