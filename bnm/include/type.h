#pragma once

#include "class.h"
#include "object.h"

namespace IL2CPP
{
    struct Class;
    struct Object;
    struct Type
    {
        IL2CPP::Class *Class();
        const char *Name();
        IL2CPP::Object *Object();
    };
}