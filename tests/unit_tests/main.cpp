#include "UnitTest++.h"
#include "stdio.h"

int main(int argc, char const * argv[])
{
    int testsFailed = UnitTest::RunAllTests();
    if (testsFailed != 0)
    {
        
    }
    return testsFailed;
}