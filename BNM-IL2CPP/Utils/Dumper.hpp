#include <string>
#include <filesystem>
#include <fstream>
#include "../Structures/IL2CPP.hpp"

namespace BNM
{
    namespace Utils
    {
        // Runtime dumper.
        void Dump(std::string filename = "dump", bool show_offsets = true, bool show_patterns = true, int patterns_length = 16)
        {
            std::filesystem::path path(std::filesystem::current_path().string() + "\\" + filename + ".cs");
            std::ofstream stream(path);
            for (auto it : IL2CPP::Domain().Assemblies())
            {
                LOG_DEBUG(std::string("Dumping ") += it->Image()->Name());
                stream << it->Image()->ToString(show_offsets, show_patterns, patterns_length);
            }
            LOG_DEBUG("Successfully dumped!");
            LOG_DEBUG("Path to dump: " + path.string());
            stream.close();
        }
    }
}