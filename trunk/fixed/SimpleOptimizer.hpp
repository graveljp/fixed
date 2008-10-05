#ifndef __SIMPLE_OPTIMIZER_HPP__
#define __SIMPLE_OPTIMIZER_HPP__

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag,Fract> operator+ (const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    return Add::instance<Q<Mag,Fract>,Q<Mag,Fract> >::apply(roLeft, roRight);
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag,Fract> operator- (const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    return Sub::instance<Q<Mag,Fract>,Q<Mag,Fract> >::apply(roLeft, roRight);
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag,Fract> operator* (const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    return Mult::instance<Q<Mag,Fract>,Q<Mag,Fract> >::apply(roLeft, roRight);
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag,Fract> operator/(const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    return Div::instance<Q<Mag,Fract>,Q<Mag,Fract> >::apply(roLeft, roRight);
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


#endif//__SIMPLE_OPTIMIZER_HPP__
