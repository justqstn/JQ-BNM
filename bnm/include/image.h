#pragma once

#include "class.h"
#include "dumper.h"

namespace IL2CPP
{
    struct Class;
    struct Image
    {
        const char *Name();
        IL2CPP::Class *Class(const char *Fullname);
        IL2CPP::Class *Class(const char *Namespace, const char *Name);
        unsigned int ClassCount();
        std::vector<IL2CPP::Class *> Classes();
        std::string ToString(const DumperParameters &Parameters = {}, int Index = -1);
    };
}