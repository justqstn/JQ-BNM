#pragma once
#include "Class.hpp"

namespace IL2CPP
{
    struct Class;
    struct Type
    {
    public:
        IL2CPP::Class *Class()
        {
            return (IL2CPP::Class *)IL2CPP::ExportCall::ClassFromType((void *)this);
        }

        const char *Name()
        {
            return IL2CPP::ExportCall::TypeGetName((void *)this);
        }
    };
}