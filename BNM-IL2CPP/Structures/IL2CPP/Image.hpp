#pragma once

#include "Class.hpp"
#include "../../ExportCall.hpp"
#include <string>
#include <vector>

namespace IL2CPP
{
    class Image
    {
    public:
        Image(void *address)
        {
            this->handle = address;
        }
        const char *Name()
        {
            return IL2CPP::ExportCall::ImageGetName(this->handle);
        }

        // Returns class of assembly by the name. Name format: NAMESPACE.NAME
        IL2CPP::Class Class(const char *_fullname)
        {
            std::string fullname = _fullname;
            size_t lastindex = fullname.find_last_of(".");
            if (lastindex > fullname.size())
            {
                return IL2CPP::Class(IL2CPP::ExportCall::ClassFromName(this->handle, "", _fullname));
            }
            else
            {
                return IL2CPP::Class(IL2CPP::ExportCall::ClassFromName(this->handle, fullname.substr(0, lastindex).c_str(), fullname.substr(lastindex + 1, fullname.length()).c_str()));
            }
        }

        // Return class of assembly by the namespace and name.
        IL2CPP::Class Class(const char *k_namespace, const char *k_name)
        {
            return IL2CPP::Class(IL2CPP::ExportCall::ClassFromName(this->handle, k_namespace, k_name));
        }

    private:
        void *handle;
    };
}