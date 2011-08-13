#ifndef __SIMPLE_FIPU_HPP__
#define __SIMPLE_FIPU_HPP__

#include "promote_traits.hpp"

struct mult_opcode {};
struct div_opcode {};
struct add_opcode {};
struct sub_opcode {};

struct Mult
{
    template<typename T1, typename T2>
    struct NBits
    {
      enum {
        Magnitude = T1::Magnitude  + T2::Magnitude,
        Fractional = T1::Fractional + T2::Fractional,
        Total = Magnitude + Fractional
      };
    };

    template<typename T1, typename T2>
    struct result
    {
        typedef Q< NBits<T1,T2>::Magnitude, 
                   NBits<T1,T2>::Fractional > type;
    };

    template<class T1, class T2>
    __forceinline static typename result<T1, T2>::type apply(const T1& roLeft, const T2& roRight)
    {
      typedef result<T1,T2>::type result_type;
      result_type res;
      res.m_CompFast = static_cast<typename result_type::MagnType>(roLeft.m_CompFast) *
                       static_cast<typename result_type::MagnType>(roRight.m_CompFast);

#ifdef FIXED_DEBUG_MODE
      res.typeStr = "(" + roLeft.typeStr + " * " + roRight.typeStr + ")";
      res.valueStr = "(" + roLeft.valueStr + " * " + roRight.valueStr + " [" + boost::lexical_cast<std::string>(res.m_Magn) + "," + boost::lexical_cast<std::string>(res.m_Frac) + "] )";
      res.floatStr = "(" + roLeft.floatStr + " * " + roRight.floatStr + " [" + boost::lexical_cast<std::string>((float)res) + "] )";
      res.floatValue = roLeft.floatValue * roRight.floatValue;
      res.cumulativeEpsilon = (double)roLeft  * roRight.cumulativeEpsilon +
                              (double)roRight * roLeft.cumulativeEpsilon +
                              roLeft.cumulativeEpsilon * roRight.cumulativeEpsilon;
                              
;
#endif //FIXED_DEBUG_MODE

      return res;
    }
};

struct Div
{
    template<typename T1, typename T2>
    struct instance
    {
        typedef typename promote_traits<T1, T2>::promote_type value_type;

        template<typename OutT>
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

        template<typename OutT>
        __forceinline static OutT apply(const T& roLeft, const T& roRight)
        {
            value_type res;
            BOOST_ASSERT(roRight.m_CompExact != 0);
            if (roRight.m_CompExact == 0)
                res.m_CompFast = BitMask<value_type::NBits>::value;
            else
                res.m_CompFast = static_cast<typename OutT::MagnType>(roLeft.m_CompFast / roRight.m_CompFast);
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

        template<typename OutT>
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

        template<typename OutT>
        __forceinline static value_type apply(const T& roLeft, const T& roRight)
        {
            value_type res;
            res.m_CompFast = roLeft.m_CompFast + roRight.m_CompFast;
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

        template<typename OutT>
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

        template<typename OutT>
        __forceinline static value_type apply(const T& roLeft, const T& roRight)
        {
            value_type res;
            res.m_CompFast = roLeft.m_CompFast - roRight.m_CompFast;
            return res;
        }
    };
};


#endif //__SIMPLE_FIPU_HPP__