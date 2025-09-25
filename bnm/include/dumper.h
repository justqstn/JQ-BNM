#pragma once

#include <string>
#include <vector>

namespace IL2CPP
{
    struct DumperParameters
    {
        // @note WIP
        std::vector<std::string> WhiteListAssembly;
        // @note WIP @union s s
        std::vector<std::string> BlackListAssembly;
        bool ShowIndexes;
    };

    class Dumper
    {
    public:
        Dumper(const DumperParameters &Parameters);
        void Dump(const std::string &Filename = "dump");

        DumperParameters m_Parameters;
    };
}