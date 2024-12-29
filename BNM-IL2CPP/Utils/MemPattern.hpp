#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <sstream>
#include <psapi.h>
#include "../Exports.hpp"
#include "../Defines.hpp"

namespace BNM
{
    namespace Utils
    {
        MODULEINFO GetModuleInfo(const char *szModule)
        {
            MODULEINFO modinfo = {0};
            HMODULE hModule = GetModuleHandleA(szModule);
            if (hModule == 0)
                return modinfo;
            GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
            return modinfo;
        }

        std::vector<unsigned char> PatternToBytes(const std::string &pattern, const std::string &delimiter = " ")
        {
            std::vector<unsigned char> bytes;
            size_t pos = 0;
            std::string token;
            std::string input = pattern; // Копируем строку, так как она изменяется

            while ((pos = input.find(delimiter)) != std::string::npos)
            {
                token = input.substr(0, pos);
                if (token == "??")
                {
                    bytes.push_back(0xFF); // Используем 0xFF как wildcard
                }
                else
                {
                    bytes.push_back(static_cast<unsigned char>(std::stoul(token, nullptr, 16)));
                }
                input.erase(0, pos + delimiter.length());
            }

            // Обработка последнего токена
            if (input == "??")
            {
                bytes.push_back(0xFF);
            }
            else
            {
                bytes.push_back(static_cast<unsigned char>(std::stoul(input, nullptr, 16)));
            }

            return bytes;
        }

        std::string BytesToPattern(std::vector<unsigned char> bytes)
        {
            std::string result;
            for (auto it : bytes)
            {
                std::stringstream stream;
                if (it < 16)
                    stream << "0";
                stream << std::hex << (short)it;
                result += stream.str() + " ";
            }
            return result;
        }

        uint64_t ScanPattern(std::string str, uint64_t start = 0)
        {
            uint64_t result = 0;
            std::vector<unsigned char> bytes = PatternToBytes(str);
            MODULEINFO info = GetModuleInfo(MAIN_MODULE);
            uint64_t end = (uint64_t)IL2CPP::Exports::GameAssembly + info.SizeOfImage;

            for (uint64_t current = (uint64_t)IL2CPP::Exports::GameAssembly + start; current < end; current++)
            {
                bool found = true;
                for (size_t i = 0; i < bytes.size(); i++)
                {
                    unsigned char byte = *(unsigned char *)(current + i);
                    if (bytes[i] != 0xFF && bytes[i] != byte)
                    {
                        found = false;
                        break;
                    }
                }
                if (found)
                {
                    LOG_DEBUG("Pattern found at: " + std::to_string(current));
                    return current;
                }
            }

            LOG_DEBUG("Pattern not found.");
            return result;
        }

        std::vector<unsigned char> BytesFromAddress(uint64_t address, int length)
        {
            std::vector<unsigned char> result;
            for (int i = 0; i < length; i++)
            {
                result.push_back(*(unsigned char *)(address + i));
            }
            return result;
        }
    }
}