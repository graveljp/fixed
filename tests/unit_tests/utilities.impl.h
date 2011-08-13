#include "utilities.h"

#include <boost/test/unit_test.hpp>
#include <stack>
#include <iostream>

template<typename Q>
bool Utilities::checkResult(const Q& result)
{
    const double epsilon = result.cumulativeEpsilon + std::numeric_limits<double>::epsilon();
    const double fixedResult = (double)result;
    const double error = fabs(fixedResult - result.floatValue);

    std::cout << "\n";
    std::cout << "Expression : " << result.floatStr << "\n";
    std::cout << "Expected   : " << result.floatValue << "\n";
    std::cout << "Obtained   : " << fixedResult << "\n";
    std::cout << "Error      : " << error << "\n";
    std::cout << "Tolerance  : " << epsilon << "\n";

    if ( error > epsilon )
    {
        std::cout << "Result out of range.\n";
        std::cout << "Overshoot :" << error - epsilon << "\n";
        return false;
    }

    return true;
}

template<typename Q>
bool Utilities::checkTypeStr(const Q& result, const std::string& referenceStr)
{
    const std::string& resultStr = result.typeStr;

    std::string::const_iterator refIter = referenceStr.begin();
    std::string::const_iterator refEnd = referenceStr.end();

    std::string::const_iterator resultIter = resultStr.begin();
    std::string::const_iterator resultEnd = resultStr.end();

    int refParenthesisLevel = 0;
    int resultParenthesisLevel = 0;

    refIter    = Impl::skipWhitespaces( refIter, refEnd );
    resultIter = Impl::skipWhitespaces( resultIter, resultEnd );

    while ( refIter != refEnd || resultIter != resultEnd )
    {
        // Both at end
        if ( refIter == refEnd && resultIter == resultEnd )
        {
            if ( refParenthesisLevel > 0 )
            {
                Impl::printMessage("Missing closing parenthesis in reference type string:", referenceStr, refIter, resultStr, resultIter);
                return false;
            }

            if ( resultParenthesisLevel > 0 )
            {
                Impl::printMessage("Missing closing parenthesis in result type string:", referenceStr, refIter, resultStr, resultIter);
                return false;
            }

            return true;
        }

        // Result string terminated prematurely
        else if ( refIter != refEnd && resultIter == resultEnd )
        {
            Impl::printMessage("Result type string too short:", referenceStr, refIter, resultStr, resultIter);
            return false;
        }

        // Result string too long
        else if ( refIter == refEnd && resultIter != resultEnd )
        {
            // There may still be optional closing parenthesis:
            while ( resultParenthesisLevel > 0 )
            {
                if ( *resultIter != ')' )
                    break;

                --resultParenthesisLevel;
                resultIter = Impl::skipWhitespaces( ++resultIter, resultEnd );
            }

            if ( resultIter != resultEnd )
            {
                Impl::printMessage("Result type string too long:", referenceStr, refIter, resultStr, resultIter);
                return false;
            }
        }

        // The reference requires a mandatory parenthesis
        else if ( *refIter == '(' )
        {
            if ( *resultIter != '(' )
            {
                Impl::printMessage("Expected opening parenthesis in result type string:", referenceStr, refIter, resultStr, resultIter);
                return false;
            }

            ++refParenthesisLevel;
            ++resultParenthesisLevel;

            refIter    = Impl::skipWhitespaces( ++refIter, refEnd );
            resultIter = Impl::skipWhitespaces( ++resultIter, resultEnd );
        }

        // The reference closes a mandatory parenthesis
        else if ( *refIter == ')' )
        {
            if ( *resultIter != ')' )
            {
                Impl::printMessage("Expected closing parenthesis in result type string:", referenceStr, refIter, resultStr, resultIter);
                return false;
            }

            --refParenthesisLevel;
            if ( refParenthesisLevel < 0 )
            {
                Impl::printMessage("Unbalanced parenthesis in reference type string:", referenceStr, refIter, resultStr, resultIter);
                return false;
            }

            --resultParenthesisLevel;
            if ( resultParenthesisLevel < 0 )
            {
                Impl::printMessage("Unbalanced parenthesis in result type string:", referenceStr, refIter, resultStr, resultIter);
                return false;
            }

            refIter    = Impl::skipWhitespaces( ++refIter, refEnd );
            resultIter = Impl::skipWhitespaces( ++resultIter, resultEnd );
        }

        // The result string opens an optional parenthesis
        else if ( *resultIter == '(' )
        {
            ++resultParenthesisLevel;

            resultIter = Impl::skipWhitespaces( ++resultIter, resultEnd );
        }

        // The result string closes an optional parenthesis
        else if ( *resultIter == ')' )
        {
            --resultParenthesisLevel;

            if ( resultParenthesisLevel < 0 )
            {
                Impl::printMessage("Unbalanced parenthesis in result type string:", referenceStr, refIter, resultStr, resultIter);
                return false;
            }

            resultIter = Impl::skipWhitespaces( ++resultIter, resultEnd );
        }

        // Finally compare two characters
        else
        {
            if ( *refIter != *resultIter )
            {
                Impl::printMessage("String mismatch.", referenceStr, refIter, resultStr, resultIter);
                return false;
            }

            refIter    = Impl::skipWhitespaces( ++refIter, refEnd );
            resultIter = Impl::skipWhitespaces( ++resultIter, resultEnd );
        }
    }

    return true;
}

class Utilities::Impl
{
public:
    static std::string::const_iterator Impl::skipWhitespaces( const std::string::const_iterator& current, const std::string::const_iterator& end )
    {
        std::string::const_iterator iter;
        for ( iter = current; iter != end; ++iter )
        {
            if ( *iter != ' '  &&
                *iter != '\t' &&
                *iter != '\n' &&
                *iter != '\r' )
            {
                break;
            }
        }

        return iter;
    }

    static void Impl::printMessage( const std::string& message,
        const std::string& reference, const std::string::const_iterator& refPos,
        const std::string& result, const std::string::const_iterator& resultPos)
    {
        std::cout << message << "\n";
        std::cout << "reference: " << reference << "\n";
        std::cout << "           " << std::string( std::distance(reference.begin(), refPos), ' ' ) << "^\n";
        std::cout << "result:    " << result << "\n";
        std::cout << "           " << std::string( std::distance(result.begin(), resultPos), ' ' ) << "^\n";
    }

};

