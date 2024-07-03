#pragma once

#include "Image.hpp"
#include "../../ExportCall.hpp"

namespace IL2CPP
{
    struct Assembly
    {
    public:
        // Returns image of assembly. By image you can get all needed things.
        IL2CPP::Image *Image()
        {
            return (IL2CPP::Image *)(IL2CPP::ExportCall::AssemblyGetImage((void *)this));
        }
    };
}