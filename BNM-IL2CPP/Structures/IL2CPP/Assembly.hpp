#pragma once

#include "Image.hpp"
#include "../../ExportCall.hpp"

namespace IL2CPP
{
    class Assembly
    {
    public:
        Assembly(void *address)
        {
            this->handle = address;
        }

        // Returns image of assembly. By image you can get all needed things.
        IL2CPP::Image Image()
        {
            return IL2CPP::Image(IL2CPP::ExportCall::AssemblyGetImage(this->handle));
        }

        void *Address()
        {
            return this->handle;
        }

    private:
        void *handle;
    };
}