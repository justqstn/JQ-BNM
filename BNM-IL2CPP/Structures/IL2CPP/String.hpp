#pragma once

#include "../../ExportCall.hpp"
#include <string>
#include <stringapiset.h>

namespace IL2CPP
{
    struct String
    {
    public:
        static IL2CPP::String *New(const char *content)
        {
            return (IL2CPP::String *)IL2CPP::ExportCall::StringNew(content);
        }

        int Length()
        {
            return IL2CPP::ExportCall::StringLength((void *)this);
        }

        std::string Content()
        {
            int length = this->Length();
            std::string result(static_cast<size_t>(length) * 3 + 1, '\0');
            WideCharToMultiByte(CP_UTF8, 0, IL2CPP::ExportCall::StringChars((void *)this), length, &result[0], static_cast<int>(result.size()), 0, 0);
            return result;
        }
    };
}