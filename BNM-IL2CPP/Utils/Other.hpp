#pragma once

#include <string>
#include <sstream>

namespace BNM
{
    namespace Utils
    {
        std::string ToHex(uint64_t number)
        {
            std::stringstream stream;
            stream << std::hex << number;
            return stream.str();
        }
    }
}