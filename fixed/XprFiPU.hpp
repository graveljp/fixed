#ifndef __XPR_FIPU_HPP__
#define __XPR_FIPU_HPP__

#include "promote_traits.hpp"

template<typename T1, typename T2>
struct Mult
{
    typedef typename promote_traits<T1, T2>::promote_type value_type;

    static value_type apply(const T1& roLeft, const T2& roRight)
    {
        value_type res;
        // ????
        return res;
    }
};

template<typename T>
struct Mult<T,T>
{
    typedef T value_type;

    static value_type apply(const T& roLeft, const T& roRight)
    {
        value_type res;
        res.m_Comp = (static_cast<T::MultiplyType>(roLeft.m_Comp) *
                      static_cast<T::MultiplyType>(roRight.m_Comp)) >> T::Fractional;
        return res;
    }
};

template<typename T1, typename T2>
struct Div
{
    typedef typename promote_traits<T1, T2>::promote_type value_type;

    static value_type apply(const T1& roLeft, const T2& roRight)
    {
        value_type res;
        // ????
        return res;
    }
};

template<typename T>
struct Div<T,T>
{
    typedef T value_type;

    static value_type apply(const T& roLeft, const T& roRight)
    {
        Q res;
        BOOST_ASSERT(roRight.m_Comp != 0);
        if (roRight.m_Comp == 0)
            res.m_Comp = BitMask<NBits>::value;
        else
            res.m_Comp = ((static_cast<T::MultiplyType>(roLeft.m_Comp) << T::Fractional) / roRight.m_Comp) >> T::Fractional;
        return res;
    }
};

template<typename T1, typename T2>
struct Add
{
    typedef typename promote_traits<T1, T2>::promote_type value_type;

    static value_type apply(const T1& roLeft, const T2& roRight)
    {
        Q res;
        // ????
        return res;
    }
};

template<typename T>
struct Add<T,T>
{
    typedef T value_type;

    static value_type apply(const T& roLeft, const T& roRight)
    {
        value_type res;
        res.m_Comp = roLeft.m_Comp + roRight.m_Comp;
        return res;
    }
};

template<typename T1, typename T2>
struct Sub
{
    typedef typename promote_traits<T1, T2>::promote_type value_type;

    static value_type apply(const T1& roLeft, const T2& roRight)
    {
        Q res;
        // ????
        return res;
    }
};

template<typename T>
struct Sub<T,T>
{
    typedef T value_type;

    static value_type apply(const T& roLeft, const T& roRight)
    {
        value_type res;
        res.m_Comp = roLeft.m_Comp - roRight.m_Comp;
        return res;
    }
};

template<typename E1, typename E2>
BinXpr<Mult<typename E1::value_type, typename E2::value_type>, E1, E2> operator*(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return BinXpr<Mult<typename E1::value_type, typename E2::value_type>, E1, E2>(roLeft(), roRight());
}

template<typename E1, typename E2>
BinXpr<Div<typename E1::value_type, typename E2::value_type>, E1, E2> operator/(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return BinXpr<Div<typename E1::value_type, typename E2::value_type>, E1, E2>(roLeft(), roRight());
}

template<typename E1, typename E2>
BinXpr<Add<typename E1::value_type, typename E2::value_type>, E1, E2> operator+(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return BinXpr<Add<typename E1::value_type, typename E2::value_type>, E1, E2>(roLeft(), roRight());
}

template<typename E1, typename E2>
BinXpr<Sub<typename E1::value_type, typename E2::value_type>, E1, E2> operator-(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return BinXpr<Sub<typename E1::value_type, typename E2::value_type>, E1, E2>(roLeft(), roRight());
}


template<typename E1, typename E2>
bool operator==(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() == roRight().value();
}

template<typename E1, typename E2>
bool operator!=(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() != roRight().value();
}

template<typename E1, typename E2>
bool operator< (const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() < roRight().value();
}

template<typename E1, typename E2>
bool operator<=(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() <= roRight().value();
}

template<typename E1, typename E2>
bool operator> (const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() > roRight().value();
}

template<typename E1, typename E2>
bool operator>=(const QXpr<E1>& roLeft, const QXpr<E2>& roRight)
{
    return roLeft().value() >= roRight().value();
}




#endif //__XPR_FIPU_HPP__