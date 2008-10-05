#ifndef __SIMPLE_FIPU_HPP__
#define __SIMPLE_FIPU_HPP__

//template <res_type, l_type, r_type>
//res_type operator+ (const l_type& roLeft, const r_type& roRight)
//{
//
//}

template <sint8_t Mag, uint8_t Fract>
Q<Mag,Fract> operator+ (const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    Q<Mag,Fract> res;
    res.m_Comp = roLeft.m_Comp + roRight.m_Comp;
    return res;
}

template <sint8_t Mag, uint8_t Fract>
Q<Mag,Fract> operator- (const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    Q<Mag,Fract> res;
    res.m_Comp = roLeft.m_Comp - roRight.m_Comp;
    return res;
}

template <sint8_t Mag, uint8_t Fract>
Q<Mag,Fract> operator* (const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    Q<Mag,Fract> res;
    res.m_Comp = (static_cast<Q<Mag,Fract>::MultiplyType>(roLeft.m_Comp) *
                  static_cast<Q<Mag,Fract>::MultiplyType>(roRight.m_Comp)) >> Fract;
    return res;
}

template <sint8_t Mag, uint8_t Fract>
Q<Mag,Fract> operator/(const Q<Mag,Fract>& roLeft, const Q<Mag,Fract>& roRight) const
{
    Q<Mag,Fract> res;
    BOOST_ASSERT(val.m_Comp != 0);
    if (val.m_Comp == 0)
        res.m_Comp = BitMask<NBits>::value;
    else
        res.m_Comp = ((static_cast<Q<Mag,Fract>::MultiplyType>(roLeft.m_Comp) << Frac) / roRight.m_Comp) >> Fract;
    return res;
}


#endif //__SIMPLE_FIPU_HPP__