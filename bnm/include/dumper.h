#pragma once

#include <string>
#include <vector>

namespace IL2CPP
{
    struct DumperParameters
    {
        std::vector<std::string> WhiteListAssembly;
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