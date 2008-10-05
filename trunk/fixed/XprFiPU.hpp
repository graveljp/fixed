#ifndef __XPR_FIPU_HPP__
#define __XPR_FIPU_HPP__

#include "promote_traits.hpp"

struct mult_opcode {};
struct div_opcode {};
struct add_opcode {};
struct sub_opcode {};

struct Mult
{
    template<typename T1, typename T2>
    struct instance
    {
        typedef typename promote_traits<T1, T2>::promote_type value_type;

        __forceinline static value_type apply(const T1& roLeft, const T2& roRight)
        {
            value_type res;
            // ????
            return res;
        }
    };

    template<typename T>
    struct instance<T,T>
    {
        typedef T value_type;

        __forceinline static value_type apply(const T& roLeft, const T& roRight)
        {
            value_type res;
            res.m_Comp = static_cast<typename T::MagnType>((static_cast<typename T::MultiplyType>(roLeft.m_Comp) *
                                                            static_cast<typename T::MultiplyType>(roRight.m_Comp)) >> T::Fractional);
            return res;
        }
    };
};

struct Div
{
    template<typename T1, typename T2>
    struct instance
    {
        typedef typename promote_traits<T1, T2>::promote_type value_type;

        __forceinline static value_type apply(const T1& roLeft, const T2& roRight)
        {
            value_type res;
            // ????
            return res;
        }
    };

    template<typename T>
    struct instance<T,T>
    {
        typedef T value_type;

        __forceinline static value_type apply(const T& roLeft, const T& roRight)
        {
            value_type res;
            BOOST_ASSERT(roRight.m_Comp != 0);
            if (roRight.m_Comp == 0)
                res.m_Comp = BitMask<value_type::NBits>::value;
            else
                res.m_Comp = (static_cast<typename T::MultiplyType>(roLeft.m_Comp) << T::Fractional) / roRight.m_Comp;
            return res;
        }
    };
};

struct Add
{
    template<typename T1, typename T2>
    struct instance
    {
        typedef typename promote_traits<T1, T2>::promote_type value_type;

        __forceinline static value_type apply(const T1& roLeft, const T2& roRight)
        {
            vale_type res;
            // ????
            return res;
        }
    };

    template<typename T>
    struct instance<T,T>
    {
        typedef T value_type;

        __forceinline static value_type apply(const T& roLeft, const T& roRight)
        {
            value_type res;
            res.m_Comp = roLeft.m_Comp + roRight.m_Comp;
            return res;
        }
    };
};

struct Sub
{
    template<typename T1, typename T2>
    struct instance
    {
        typedef typename promote_traits<T1, T2>::promote_type value_type;

        __forceinline static value_type apply(const T1& roLeft, const T2& roRight)
        {
            value_type res;
            // ????
            return res;
        }
    };

    template<typename T>
    struct instance<T,T>
    {
        typedef T value_type;

        __forceinline static value_type apply(const T& roLeft, const T& roRight)
        {
            value_type res;
            res.m_Comp = roLeft.m_Comp - roRight.m_Comp;
            return res;
        }
    };
};



template<typename E1, typename E2>
__forceinline BinXpr<Mult, E1, E2> operator*(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return BinXpr<Mult, E1, E2>(roLeft(), roRight());
}

template<typename E1, typename E2>
__forceinline BinXpr<Div, E1, E2> operator/(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return BinXpr<Div, E1, E2>(roLeft(), roRight());
}

template<typename E1, typename E2>
__forceinline BinXpr<Add, E1, E2> operator+(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return BinXpr<Add, E1, E2>(roLeft(), roRight());
}

template<typename E1, typename E2>
__forceinline BinXpr<Sub, E1, E2> operator-(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return BinXpr<Sub, E1, E2>(roLeft(), roRight());
}


template<typename E1, typename E2>
__forceinline bool operator==(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() == roRight().value();
}

template<typename E1, typename E2>
__forceinline bool operator!=(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() != roRight().value();
}

template<typename E1, typename E2>
__forceinline bool operator< (const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() < roRight().value();
}

template<typename E1, typename E2>
__forceinline bool operator<=(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() <= roRight().value();
}

template<typename E1, typename E2>
__forceinline bool operator> (const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() > roRight().value();
}

template<typename E1, typename E2>
__forceinline bool operator>=(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() >= roRight().value();
}


template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag, Fract>& operator+=(Q<Mag, Fract>& roLeft, const Q<Mag, Fract>& roRight)
{
    roLeft.m_Comp += roRight.m_Comp;
    return roLeft;
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag, Fract>& operator-=(Q<Mag, Fract>& roLeft, const Q<Mag, Fract>& roRight)
{
    roLeft.m_Comp -= roRight.m_Comp;
    return roLeft;
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag, Fract>& operator*=(Q<Mag, Fract>& roLeft, const Q<Mag, Fract>& roRight)
{
    roLeft.m_Comp = (static_cast<Q<Mag, Fract>::MultiplyType>(roLeft.m_Comp) *
                     static_cast<Q<Mag, Fract>::MultiplyType>(roRight.m_Comp)) >> Fract;
    return roLeft;
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag, Fract>& operator/=(Q<Mag, Fract>& roLeft, const Q<Mag, Fract>& roRight)
{
    BOOST_ASSERT(roRight.m_Comp != 0);
    if (roRight.m_Comp == 0)
        roLeft.m_Comp = BitMask<Q<Mag, Fract>::NBits>::value;
    else
        roLeft.m_Comp = (static_cast<Q<Mag, Fract>::MultiplyType>(roLeft.m_Comp) << Fract) / roRight.m_Comp;
    return roLeft;
}


template<sint8_t Mag, uint8_t Fract>
template<typename E>
__forceinline Q<Mag, Fract>& Q<Mag, Fract>::operator=(const QXpr<E>& roRight)
{
    *this = roRight().value();
    return *this;
}

template<sint8_t Mag, uint8_t Fract, typename E>
__forceinline Q<Mag, Fract>& operator+=(Q<Mag, Fract>& roLeft, const QXpr<E>& roRight)
{
    roLeft += roRight().value();
    return roLeft;
}

template<sint8_t Mag, uint8_t Fract, typename E>
__forceinline Q<Mag, Fract>& operator-=(Q<Mag, Fract>& roLeft, const QXpr<E>& roRight)
{
    roLeft -= roRight().value();
    return roLeft;
}

template<sint8_t Mag, uint8_t Fract, typename E>
__forceinline Q<Mag, Fract>& operator*=(Q<Mag, Fract>& roLeft, const QXpr<E>& roRight)
{
    roLeft *= roRight().value();
    return roLeft;
}

template<sint8_t Mag, uint8_t Fract, typename E>
__forceinline Q<Mag, Fract>& operator/=(Q<Mag, Fract>& roLeft, const QXpr<E>& roRight)
{
    roLeft /= roRight().value();
    return roLeft;
}


#endif //__XPR_FIPU_HPP__
