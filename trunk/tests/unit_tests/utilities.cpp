#include "utilities.h"

#include <boost/test/unit_test.hpp>
#include <stack>
#include <iostream>

namespace
{
    std::string::const_iterator skipWhitespaces( const std::string::const_iterator& current, const std::string::const_iterator& end )
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

    void printMessage( const std::string& message,
        const std::string& reference, const std::string::const_iterator& refPos,
        const std::string& result, const std::string::const_iterator& resultPos)
    {
        std::cout << message << "\n";
        std::cout << "Reference: " << reference << "\n";
        std::cout << "           " << std::string( std::distance(reference.begin(), refPos), ' ' ) << "^\n";
        std::cout << "Result:    " << result << "\n";
        std::cout << "           " << std::string( std::distance(result.begin(), resultPos), ' ' ) << "^\n";
    }

}

bool checkTypeStr(const std::string& reference, const std::string& result)
{
    std::string::const_iterator refIter = reference.begin();
    std::string::const_iterator refEnd = reference.end();

    std::string::const_iterator resultIter = result.begin();
    std::string::const_iterator resultEnd = result.end();

    int refParenthesisLevel = 0;
    int resultParenthesisLevel = 0;

    refIter      = skipWhitespaces( refIter, refEnd );
    resultIter = skipWhitespaces( resultIter, resultEnd );

    while ( refIter != refEnd || resultIter != resultEnd )
    {
        // Both at end
        if ( refIter == refEnd && resultIter == resultEnd )
        {
            if ( refParenthesisLevel > 0 )
            {
                printMessage("Missing closing parenthesis in reference type string:", reference, refIter, result, resultIter);
                return false;
            }

            if ( resultParenthesisLevel > 0 )
            {
                printMessage("Missing closing parenthesis in result type string:", reference, refIter, result, resultIter);
                return false;
            }

            return true;
        }

        // result string terminated prematurely
        else if ( refIter != refEnd && resultIter == resultEnd )
        {
            printMessage("Result type string too short:", reference, refIter, result, resultIter);
            return false;
        }

        // result string too long
        else if ( refIter == refEnd && resultIter != resultEnd )
        {
            // There may still be optional closing parenthesis:
            while ( resultParenthesisLevel > 0 )
            {
                if ( *resultIter != ')' )
                    break;

                --resultParenthesisLevel;
                resultIter = skipWhitespaces( ++resultIter, resultEnd );
            }

            if ( resultIter != resultEnd )
            {
                printMessage("Result type string too long:", reference, refIter, result, resultIter);
                return false;
            }
        }

        // The reference requires a mandatory parenthesis
        else if ( *refIter == '(' )
        {
            if ( *resultIter != '(' )
            {
                printMessage("Expected opening parenthesis in result type string:", reference, refIter, result, resultIter);
                return false;
            }

            ++refParenthesisLevel;
            ++resultParenthesisLevel;

            refIter      = skipWhitespaces( ++refIter, refEnd );
            resultIter = skipWhitespaces( ++resultIter, resultEnd );
        }

        // The reference closes a mandatory parenthesis
        else if ( *refIter == ')' )
        {
            if ( *resultIter != ')' )
            {
                printMessage("Expected closing parenthesis in result type string:", reference, refIter, result, resultIter);
                return false;
            }

            --refParenthesisLevel;
            if ( refParenthesisLevel < 0 )
            {
                printMessage("Unbalanced parenthesis in reference type string:", reference, refIter, result, resultIter);
                return false;
            }

            --resultParenthesisLevel;
            if ( resultParenthesisLevel < 0 )
            {
                printMessage("Unbalanced parenthesis in result type string:", reference, refIter, result, resultIter);
                return false;
            }

            refIter      = skipWhitespaces( ++refIter, refEnd );
            resultIter = skipWhitespaces( ++resultIter, resultEnd );
        }

        // The result string opens an optional parenthesis
        else if ( *resultIter == '(' )
        {
            ++resultParenthesisLevel;

            resultIter = skipWhitespaces( ++resultIter, resultEnd );
        }

        // The result string closes an optional parenthesis
        else if ( *resultIter == ')' )
        {
            --resultParenthesisLevel;

            if ( resultParenthesisLevel < 0 )
            {
                printMessage("Unbalanced parenthesis in result type string:", reference, refIter, result, resultIter);
                return false;
            }

            resultIter = skipWhitespaces( ++resultIter, resultEnd );
        }

        // Finally compare two characters
        else
        {
            if ( *refIter != *resultIter )
            {
                printMessage("String mismatch.", reference, refIter, result, resultIter);
                return false;
            }

            refIter      = skipWhitespaces( ++refIter, refEnd );
            resultIter = skipWhitespaces( ++resultIter, resultEnd );
        }
    }

    return true;
}
