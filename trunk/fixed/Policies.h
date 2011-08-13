#ifndef __POLICIES_HPP_INC__
#define __POLICIES_HPP_INC__


class Tag
{
};

template<typename T>
class OptimizationPolicy
{
public:
    enum { optimizeForSpeed = true };
};

#define OPTIMIZE_FOR_PRECISION                     \
class OptimizationPolicy<Tag>                      \
{                                                  \
public:                                            \
    enum { optimizeForSpeed = false };             \
};


template<typename T>
class IntegerSizePolicy
{
public:
    enum { maxIntegerSize = 64 };
};

#endif //__POLICIES_HPP_INC__
