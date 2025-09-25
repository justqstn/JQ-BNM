#pragma once

#include <vector>
#include <cstdint>
#include "assembly.h"

namespace IL2CPP
{
    struct Assembly;
    namespace Domain
    {
        // @return Address of AppDomain
        uintptr_t Get();
        // @return Vector of assemblies
        std::vector<IL2CPP::Assembly *> Assemblies();
        // @return Assembly by name
        IL2CPP::Assembly *Assembly(const char *Name);
    }
}