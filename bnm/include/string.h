#pragma once

#include <string>

namespace IL2CPP
{
    struct String
    {
        static IL2CPP::String *New(const char *Content);
        int Length();
        std::string Content();
    };
}