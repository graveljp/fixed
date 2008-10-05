#ifndef __SIMPLE_FIPU_HPP__
#define __SIMPLE_FIPU_HPP__

//template <res_type, l_type, r_type>
//res_type operator+ (const l_type& roLeft, const r_type& roRight)
//{
//
//}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag,Fract> operator+ (const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    Q<Mag,Fract> res;
    res.m_Comp = roLeft.m_Comp + roRight.m_Comp;
    return res;
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag,Fract> operator- (const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    Q<Mag,Fract> res;
    res.m_Comp = roLeft.m_Comp - roRight.m_Comp;
    return res;
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag,Fract> operator* (const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    Q<Mag,Fract> res;
    res.m_Comp = (static_cast<Q<Mag,Fract>::MultiplyType>(roLeft.m_Comp) *
                  static_cast<Q<Mag,Fract>::MultiplyType>(roRight.m_Comp)) >> Fract;
    return res;
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag,Fract> operator/(const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    Q<Mag,Fract> res;
    BOOST_ASSERT(roRight.m_Comp != 0);
    if (roRight.m_Comp == 0)
        res.m_Comp = BitMask<Q<Mag,Fract>::NBits>::value;
    else
        res.m_Comp = (static_cast<Q<Mag,Fract>::MultiplyType>(roLeft.m_Comp) << Fract) / roRight.m_Comp;
    return res;
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
    roLeft.m_Comp = (static_cast<Q<Mag,Fract>::MultiplyType>(roLeft.m_Comp) *
                     static_cast<Q<Mag,Fract>::MultiplyType>(roRight.m_Comp)) >> Fract;
    return roLeft;
}

template <sint8_t Mag, uint8_t Fract>
__forceinline Q<Mag, Fract>& operator/=(Q<Mag, Fract>& roLeft, const Q<Mag, Fract>& roRight)
{
    BOOST_ASSERT(roRight.m_Comp != 0);
    if (roRight.m_Comp == 0)
        roLeft.m_Comp = BitMask<Q<Mag,Fract>::NBits>::value;
    else
        roLeft.m_Comp = (static_cast<Q<Mag,Fract>::MultiplyType>(roLeft.m_Comp) << Fract) / roRight.m_Comp;
    return roLeft;
}


#endif //__SIMPLE_FIPU_HPP__