#ifndef __Q_XPR_HPP_INC__
#define __Q_XPR_HPP_INC__

#include <boost/mpl/if.hpp>
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
        enum { value = 1 };
    };

    template<>
    struct order<Op>
    {
        typedef typename boost::is_same<typename E1::op_type, Op>::type e1_compatible;
        typedef typename boost::is_same<typename E2::op_type, Op>::type e2_compatible;
        enum { value = (e1_compatible::value||E1::template order<Op>::value==1)&&(e2_compatible::value||E2::template order<Op>::value==1) ? E1::template order<Op>::value+E2::template order<Op>::value : 2 };
    };
    
    typedef Op op_type;

    __forceinline explicit BinXpr(const E1& roLeft, const E2& roRight) :
        m_roLeft(roLeft),
        m_roRight(roRight)
    {
    }

    template<int idx>
    struct type_at
    {
        enum { e1_idx = idx<(E1::template order<Op>::value) ? idx : 0 };
        enum { e2_idx = idx>=(E1::template order<Op>::value) ? idx-(E1::template order<Op>::value) : 0 };
        typedef typename E1::template type_at<e1_idx> e1_type;
        typedef typename E2::template type_at<e2_idx> e2_type;
        typedef typename boost::mpl::if_c< (idx<(E1::template order<Op>::value)), typename e1_type::type, typename e2_type::type >::type type;
    };

    template<int first, int last>
    struct type_of
    {
        typedef typename type_of<first,(first+last)/2>::type    left_type;
        typedef typename type_of<(first+last)/2+1, last>::type  right_type;
        
        typedef typename Op::instance<left_type, right_type>::result_type type;
    };
    
    template<int idx>
    struct type_of<idx, idx>
    {
        typedef typename type_at<idx>::type type;
    };

    template<typename dest_type>
    __forceinline dest_type
    value() const
    {
        return eval<dest_type>(boost::mpl::int_<0>(), boost::mpl::int_<order<Op>::value-1>());
    }

    template<typename dest_type, typename first, typename last>
    __forceinline typename type_of<first::value, last::value>::type
    eval(first, last) const
    {
        typedef first                                              left_begin;
        typedef boost::mpl::int_<(first::value + last::value)/2>   left_end;
        typedef boost::mpl::int_<(first::value + last::value)/2+1> right_begin;
        typedef last                                               right_end;

        typedef Op::instance < typename type_of< left_begin::value,  left_end::value  >::type,
                               typename type_of< right_begin::value, right_end::value >::type > OpInstance;

        return OpInstance::apply(eval<dest_type>(left_begin(),  left_end()),
                                 eval<dest_type>(right_begin(), right_end()));
    }
    
    template<typename dest_type, typename idx>
    __forceinline typename type_at<idx::value>::type
    eval(idx, idx) const
    {
        return value_at<dest_type, idx::value, Op>();
    }


    template<typename dest_type, int idx, typename probe_op>
    __forceinline typename type_at<idx>::type
    value_at(typename boost::enable_if_c<order<probe_op>::value!=1 && (idx<(E1::template order<probe_op>::value)), int>::type=0) const
    {
        return m_roLeft.value_at<dest_type, idx, probe_op>();
    }

    template<typename dest_type, int idx, typename probe_op>
    __forceinline typename type_at<idx>::type
    value_at(typename boost::enable_if_c<order<probe_op>::value!=1 && (idx>=(E1::template order<probe_op>::value)), int>::type=0) const
    {
        return m_roRight.value_at<dest_type, idx-(E1::order<probe_op>::value), probe_op>();
    }

    template<typename dest_type, int idx, typename probe_op>
    __forceinline typename type_at<idx>::type
    value_at(typename boost::enable_if_c<order<probe_op>::value==1, int>::type=0) const
    {
        return value<dest_type>();
    }

private:
    const E1& m_roLeft;
    const E2& m_roRight;
};

#endif //__Q_XPR_HPP_INC__
