#ifndef __SIMPLE_FIPU_HPP__
#define __SIMPLE_FIPU_HPP__

#include "promote_traits.hpp"

struct mult_opcode {};
struct div_opcode {};
struct add_opcode {};
struct sub_opcode {};

struct Mult
{
    template<class T1, class T2>
    struct instance
    {
        typedef Q<T1::Magnitude  + T2::Magnitude, 
                  T1::Fractional + T2::Fractional> result_type;

        __forceinline static result_type apply(const T1& roLeft, const T2& roRight)
        {
            result_type res;
            res.m_Comp = static_cast<typename result_type::MagnType>(roLeft.m_Comp) *
                         static_cast<typename result_type::MagnType>(roRight.m_Comp);
            return res;
        }
    };
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
            BOOST_ASSERT(roRight.m_Comp != 0);
            if (roRight.m_Comp == 0)
                res.m_Comp = BitMask<value_type::NBits>::value;
            else
                res.m_Comp = static_cast<typename OutT::MagnType>(roLeft.m_Comp / roRight.m_Comp);
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
            res.m_Comp = roLeft.m_Comp + roRight.m_Comp;
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
            res.m_Comp = roLeft.m_Comp - roRight.m_Comp;
            return res;
        }
    };
};


#endif //__SIMPLE_FIPU_HPP__