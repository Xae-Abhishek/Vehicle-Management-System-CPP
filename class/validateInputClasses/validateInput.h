#ifndef VALIDATE_INPUT
#define VALIDATE_INPUT
#include <cstdint>
#include <iostream>
#include <sstream>
#include <limits>

namespace ValidateInputNamespace
{
    template<typename t>
    bool takeAndCheckNumberInput( t& addressOfNumber )
    {
        std::string       validate;
        std::getline(std::cin,validate);
        std::stringstream ss(validate);
        
        if ( !( ss>> addressOfNumber ) || !( ss.eof() ) ) {
            return false;
        }
        return true;
    }
    
    inline bool takeAndCheckStringInput(std::string &addressOfString)
    {
        std::cin>>addressOfString;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        bool falseInputFlag = true;

        for ( char c : addressOfString ){
            if ( !isdigit(c) ) {
                falseInputFlag = false;
            }
        }
        if ( addressOfString.empty() ) {
            falseInputFlag = true;
        }
        return falseInputFlag;
    }
}
#endif