#ifndef __Q_XPR_HPP_INC__
#define __Q_XPR_HPP_INC__

#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/at.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

template<typename E>
struct QXpr
{
    typedef E expression_type;

    __forceinline expression_type& operator()()
    {
        return *static_cast<expression_type*>(this);
    }
    __forceinline const expression_type& operator()() const
    {
        return *static_cast<const expression_type*>(this);
    }
};

template<typename Op, typename E1, typename E2>
class BinXpr : public QXpr<BinXpr<Op, E1, E2> >
{
public:
    template<typename T>
    struct order
    {
        static const int value = 1;
    };

    template<>
    struct order<Op>
    {
        typedef typename boost::is_same<typename E1::op_type, Op>::type e1_compatible;
        typedef typename boost::is_same<typename E2::op_type, Op>::type e2_compatible;
        static const int value = (e1_compatible::value||E1::template order<Op>::value==1)&&(e2_compatible::value||E2::template order<Op>::value==1) ? E1::template order<Op>::value+E2::template order<Op>::value : 2;
    };
    
    typedef Op op_type;
    typedef typename Op::instance<typename E1::value_type, typename E2::value_type>::value_type value_type;

    __forceinline explicit BinXpr(const E1& roLeft, const E2& roRight) :
        m_roLeft(roLeft),
        m_roRight(roRight)
    {
    }

    template<int idx>
    struct type_at
    {
        static const int e1_idx = idx<(E1::template order<Op>::value) ? idx : 0;
        static const int e2_idx = idx>=(E1::template order<Op>::value) ? idx-(E1::template order<Op>::value) : 0;
        typedef typename E1::template type_at<e1_idx> e1_type;
        typedef typename E2::template type_at<e2_idx> e2_type;
        typedef typename boost::mpl::if_c< (idx<(E1::template order<Op>::value)), typename e1_type::type, typename e2_type::type >::type type;
    };

    template<int first, int last>
    struct type_of
    {
        typedef typename Op::instance<typename type_of<first,(first+last)/2>::type, typename type_of<(first+last)/2+1, last>::type>::value_type type;
    };
    
    template<int idx>
    struct type_of<idx, idx>
    {
        typedef typename type_at<idx>::type type;
    };

    __forceinline typename type_of<0, order<Op>::value-1>::type
    value() const
    {
        return eval(boost::mpl::int_<0>(), boost::mpl::int_<order<Op>::value-1>());
    }

    template<typename first, typename last>
    __forceinline typename type_of<first::value, last::value>::type
    eval(first, last) const
    {
        return Op::instance<typename type_of<(first::value), ((first::value)+(last::value))/2>::type,
                            typename type_of<((first::value)+(last::value))/2+1, (last::value)>::type >
               ::apply(eval(first(), boost::mpl::int_<((first::value)+(last::value))/2>()),
                       eval(boost::mpl::int_<((first::value)+(last::value))/2+1>(), last()));
    }
    
    template<typename idx>
    __forceinline typename type_at<idx::value>::type
    eval(idx, idx) const
    {
        return value_at<idx::value, Op>();
    }


    template<int idx, typename probe_op>
    __forceinline typename type_at<idx>::type
    value_at(typename boost::enable_if_c<order<probe_op>::value!=1 && (idx<(E1::template order<probe_op>::value)), int>::type=0) const
    {
        return m_roLeft.value_at<idx, probe_op>();
    }

    template<int idx, typename probe_op>
    __forceinline typename type_at<idx>::type
    value_at(typename boost::enable_if_c<order<probe_op>::value!=1 && (idx>=(E1::template order<probe_op>::value)), int>::type=0) const
    {
        return m_roRight.value_at<idx-(E1::order<probe_op>::value), probe_op>();
    }

    template<int idx, typename probe_op>
    __forceinline typename type_at<idx>::type
    value_at(typename boost::enable_if_c<order<probe_op>::value==1, int>::type=0) const
    {
        return value();
    }

private:
    const E1& m_roLeft;
    const E2& m_roRight;
};

#endif //__Q_XPR_HPP_INC__
