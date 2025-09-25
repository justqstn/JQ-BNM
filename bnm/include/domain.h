#pragma once

#include <vector>
#include <cstdint>
#include "assembly.h"

namespace IL2CPP
{
    struct Assembly;
    namespace Domain
    {
        uintptr_t Get();
        std::vector<IL2CPP::Assembly *> Assemblies();
        IL2CPP::Assembly *Assembly(const char *Name);
    }
}