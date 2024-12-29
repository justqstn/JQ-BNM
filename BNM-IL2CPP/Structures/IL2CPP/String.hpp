#pragma once

#include "../../ExportCall.hpp"
#include <string>
#include <stringapiset.h>
#include <list>
#include <vector>

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
            std::string content(static_cast<size_t>(length) * 3 + 1, '\0');
            WideCharToMultiByte(CP_UTF8, 0, IL2CPP::ExportCall::StringChars((void *)this), length, &content[0], static_cast<int>(content.size()), 0, 0);

            std::vector<char> bytes(content.begin(), content.end());
            bytes.push_back('\0');

            std::list<char> chars;

            for (byte byte : bytes)
            {
                if (byte)
                {
                    chars.push_back(byte);
                }
            }

            std::string clean(chars.begin(), chars.end());

            return clean;
        }
    };
}