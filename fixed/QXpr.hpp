#ifndef __Q_XPR_HPP_INC__
#define __Q_XPR_HPP_INC__

template<typename E>
struct QXpr
{
    typedef E expression_type;

    expression_type& operator()()
    {
        return *static_cast<expression_type*>(this);
    }
    const expression_type& operator()() const
    {
        return *static_cast<const expression_type*>(this);
    }
};

template<typename Op, typename E1, typename E2>
class BinXpr : public QXpr<BinXpr<Op, E1, E2> >
{
public:
    typedef typename Op::value_type value_type;

    explicit BinXpr(const E1& roLeft, const E2& roRight) :
        m_roLeft(roLeft),
        m_roRight(roRight)
    {
    }

    value_type value() const
    {
        return Op::apply(m_roLeft.value(), m_roRight.value());
    }

private:
    const E1& m_roLeft;
    const E2& m_roRight;
};

#endif //__Q_XPR_HPP_INC__
