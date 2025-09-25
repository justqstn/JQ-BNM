#include <string>
#include <vector>

#include "../include/image.h"
#include "../include/exports.h"
#include "../include/exportcall.h"

namespace IL2CPP
{
    const char *Image::Name()
    {
        return IL2CPP::ExportCall::ImageGetName((void *)this);
    }

    IL2CPP::Class *Image::Class(const char *Fullname)
    {
        std::string strname(Fullname);
        size_t last_index = strname.find_last_of(".");
        if (last_index > strname.size())
        {
            return (IL2CPP::Class *)(IL2CPP::ExportCall::ClassFromName((void *)this, "", Fullname));
        }
        else
        {
            return (IL2CPP::Class *)(IL2CPP::ExportCall::ClassFromName((void *)this, strname.substr(0, last_index).c_str(), strname.substr(last_index + 1, strname.length()).c_str()));
        }
    }

    IL2CPP::Class *Image::Class(const char *Namespace, const char *Name)
    {
        return (IL2CPP::Class *)(IL2CPP::ExportCall::ClassFromName((void *)this, Namespace, Name));
    }

    unsigned int Image::ClassCount()
    {
        return IL2CPP::ExportCall::ImageGetClassCount((void *)this);
    }

    std::vector<IL2CPP::Class *> Image::Classes()
    {
        std::vector<IL2CPP::Class *> result;
        for (size_t i = 0; i < this->ClassCount(); i++)
        {
            result.push_back((IL2CPP::Class *)(IL2CPP::ExportCall::ImageGetClass((void *)this, i)));
        }

        return result;
    }

    std::string Image::ToString(const DumperParameters &Parameters, int Index)
    {
        std::string result;

        std::vector<IL2CPP::Class *> classes = this->Classes();
        for (size_t i = 0; i < classes.size(); i++)
        {
            if (Parameters.ShowIndexes)
                result += std::format("[{}] ", Index);
            result += std::string("// ") + this->Name() + std::string("\n");
            result += classes[i]->ToString(Parameters, i);
            result += "\n\n";
        }
        return result;
    }
}