#ifndef UNIT_TEST_UTILITIES_HPP_INCLUDED
#define UNIT_TEST_UTILITIES_HPP_INCLUDED

#include <string>

class Utilities
{
public:
    template<typename Q>
    static bool checkResult( const Q& result );

    template<typename Q>
    static bool checkTypeStr( const Q& result, const std::string& reference );

private:
    class Impl;
};


#endif // UNIT_TEST_UTILITIES_HPP_INCLUDED
