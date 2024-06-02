#ifndef TO_STRING_H_INCLUDED
#define TO_STRING_H_INCLUDED

#include <sstream>
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
}

#endif // TO_STRING_H_INCLUDED
