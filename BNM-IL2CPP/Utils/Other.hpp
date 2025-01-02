#pragma once

#include <string>
#include <sstream>
#include <psapi.h>

namespace BNM
{
    namespace Utils
    {
        std::string NumberToHex(uint64_t number)
        {
            std::stringstream stream;
            stream << std::hex << number;

            return stream.str();
        }

        std::string ByteToHex(uint64_t number)
        {
            std::stringstream stream;
            if (number < 16)
                stream << "0";
            stream << std::hex << number;

            return stream.str();
        }

        MODULEINFO GetModuleInfo(const char *szModule)
        {
            MODULEINFO modinfo = {0};
            HMODULE hModule = GetModuleHandleA(szModule);
            if (hModule == 0)
                return modinfo;
            GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
            return modinfo;
        }
    }
}