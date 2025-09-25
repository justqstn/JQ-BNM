#pragma once

#include <string>

namespace IL2CPP
{
    struct String
    {
        // Creates new string @return Pointer to String
        static IL2CPP::String *New(const char *Content);
        // @return String length
        int Length();
        // @return Content of string
        std::string Content();
    };
}