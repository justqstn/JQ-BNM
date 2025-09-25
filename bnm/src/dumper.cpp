#include <format>
#include <filesystem>
#include <fstream>

#include "../include/dumper.h"
#include "../include/domain.h"
#include "../include/defines.h"

namespace IL2CPP
{
    Dumper::Dumper(const DumperParameters &Parameters)
    {
        this->m_Parameters = Parameters;
    }

    void Dumper::Dump(const std::string &Filename)
    {
        std::filesystem::path path(std::format("{}\\{}.cs", std::filesystem::current_path().string(), Filename));
        std::ofstream stream(path);
        size_t index = 0;
        for (auto it : IL2CPP::Domain::Assemblies())
        {
            LOG(std::format("Dumping {}...", it->Image()->Name()));
            stream << it->Image()->ToString(this->m_Parameters, index++);
        }
        LOG("Successfully dumped!");
        LOG(std::format("Path to dump: {}", path.string()));
        stream.close();
    }
}