#pragma once

#include "class.h"
#include "dumper.h"

namespace IL2CPP
{
    struct Class;
    struct Image
    {
        // @return Image name
        const char *Name();
        // Gets class by fullname (namespace + name) @return Pointer to Class
        IL2CPP::Class *Class(const char *Fullname);
        // Gets class by namespace and name @return Pointer to Class
        IL2CPP::Class *Class(const char *Namespace, const char *Name);
        // @return Class count
        unsigned int ClassCount();
        // @return Vector of classes
        std::vector<IL2CPP::Class *> Classes();
        std::string ToString(const DumperParameters &Parameters = {}, int Index = -1);
        // Gets class by IndexOffset @return Pointer to Class
        IL2CPP::Class *ClassByIO(const char *Field, int Offset);
    };
}