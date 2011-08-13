#ifndef __Q_XPR_HPP_INC__
#define __Q_XPR_HPP_INC__

#include "Policies.h"

#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

template<typename E>
class QXpr
{
public:
    typedef E expression_type;
    typedef E result_type;


    __forceinline expression_type& operator()()
    {
        return *static_cast<expression_type*>(this);
    }
    __forceinline const expression_type& operator()() const
    {
        return *static_cast<const expression_type*>(this);
    }

    template<typename T>
    struct order
    {
        enum { value = 1 };
    };

    template< typename dest_type, int precisionBoost >
    struct AdjustedTypes
    {
        typedef result_type Result;
    };

    template<typename dest_type>
    __forceinline const result_type& value() const
    {
        return *static_cast<const E*>(this);
    }

    template<typename dest_type, int precisionBoost>
    __forceinline const result_type& promotedValue() const
    {
        return *static_cast<const E*>(this);
    }
};

template<typename Op, typename E1, typename E2>
class BinXpr : public QXpr<BinXpr<Op, E1, E2> >
{
public:
    typedef BinXpr<Op,E1,E2> this_type;
    typedef Op op_type;
    typedef E1 E1_type;
    typedef E2 E2_type;

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


    template< typename dest_type, int precisionBoost >
    class AdjustedTypes
    {
    public:
        struct FullTypes
        {
            typedef typename E1::AdjustedTypes<dest_type, precisionBoost>::Result Left;
            typedef typename E2::AdjustedTypes<dest_type, precisionBoost>::Result Right;
            typedef typename Op::NBits<Left, Right> ResultNBits;
            enum { adjustedTypes = false };
        };

        enum {
            maxSize = IntegerSizePolicy<Tag>::maxIntegerSize,

            fullLeftSize = FullTypes::Left::NBits,
            fullRightSize = FullTypes::Right::NBits,
            fullResultSize = FullTypes::ResultNBits::Total,

            leftHeadroom = fullLeftSize - dest_type::NBits,
            rightHeadroom = fullRightSize - dest_type::NBits,
            commonHeadroom = leftHeadroom < rightHeadroom ? leftHeadroom : rightHeadroom,
            
            bitsToShare = precisionBoost/2,
            sharedBits = commonHeadroom < bitsToShare ? commonHeadroom : bitsToShare,

            remainingBits = precisionBoost - sharedBits*2,
            leftBoost = sharedBits + (leftHeadroom > sharedBits ? remainingBits : 0),
            rightBoost = sharedBits + (rightHeadroom > sharedBits ? remainingBits : 0),
        };

        struct BoostedTypes
        {
          typedef typename dest_type::AdjustType<leftBoost>::type Left;
          typedef typename dest_type::AdjustType<rightBoost>::type Right;
          typedef typename Op::NBits<Left, Right> ResultNBits;
          enum { adjustedTypes = true };

          BOOST_STATIC_ASSERT(ResultNBits::Total <= maxSize);
        };

        typedef typename boost::mpl::if_c< fullResultSize <= maxSize, FullTypes, BoostedTypes >::type SelectedTypes;

    public:
        typedef typename SelectedTypes::Left Left;
        typedef typename SelectedTypes::Right Right;
        typedef typename Op::result<Left, Right>::type Result;
        enum { adjustedTypes = SelectedTypes::adjustedTypes};
    };

    template<typename DestType>
    class PromoteResult
    {
    private:
        typedef AdjustedTypes<DestType, 0> baseTypes;
        enum { baseNBits = baseTypes::Result::NBits };

    public:
        enum { precisionBoost = IntegerSizePolicy<Tag>::maxIntegerSize - baseNBits };
        typedef typename AdjustedTypes<DestType, precisionBoost >::Result type;
    };


    template<typename DestType>
    __forceinline typename PromoteResult<DestType>::type
    value() const
    {
        return promotedValue<DestType, PromoteResult<DestType>::precisionBoost>();
    }

    template<typename DestType, int precisionBoost>
    __forceinline typename AdjustedTypes<DestType, precisionBoost>::Result
    promotedValue() const
    {
        typedef AdjustedTypes<DestType, precisionBoost> Adjusted;
        typedef Adjusted::Left LeftType;
        typedef Adjusted::Right RightType;
        enum { nextPrecisionBoost = Adjusted::adjustedTypes ? 0 : precisionBoost };

        return Op::apply( (const LeftType)  m_roLeft.promotedValue<DestType, nextPrecisionBoost>(),
                          (const RightType) m_roRight.promotedValue<DestType, nextPrecisionBoost>() );
    }

private:
    const E1& m_roLeft;
    const E2& m_roRight;
};

#endif //__Q_XPR_HPP_INC__
