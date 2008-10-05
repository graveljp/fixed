#ifndef __XPR_OPTIMIZER_HPP__
#define __XPR_OPTIMIZER_HPP__

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
    roLeft = Add::instance<Q<Mag,Fract>,Q<Mag,Fract> >::apply(roLeft, roRight);
    return roLeft;
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag, Fract>& operator-=(Q<Mag, Fract>& roLeft, const Q<Mag, Fract>& roRight)
{
    roLeft = Sub::instance<Q<Mag,Fract>,Q<Mag,Fract> >::apply(roLeft, roRight);
    return roLeft;
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag, Fract>& operator*=(Q<Mag, Fract>& roLeft, const Q<Mag, Fract>& roRight)
{
    roLeft = Mult::instance<Q<Mag,Fract>,Q<Mag,Fract> >::apply(roLeft, roRight);
    return roLeft;
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag, Fract>& operator/=(Q<Mag, Fract>& roLeft, const Q<Mag, Fract>& roRight)
{
    roLeft = Div::instance<Q<Mag,Fract>,Q<Mag,Fract> >::apply(roLeft, roRight);
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


#endif //__XPR_OPTIMIZER_HPP__
