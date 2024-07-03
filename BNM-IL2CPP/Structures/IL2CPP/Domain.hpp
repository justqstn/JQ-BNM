#pragma once

#include "../../ExportCall.hpp"
#include "Assembly.hpp"

namespace IL2CPP
{
    struct Domain
    {
    public:
        Domain()
        {
            IL2CPP::ExportCall::GetDomain();
        }

        // Returns assembly by the name
        IL2CPP::Assembly *Assembly(const char *name)
        {
            return (IL2CPP::Assembly *)(IL2CPP::ExportCall::GetAssemblyFromDomain((void *)this, name));
        }

        // а тут мы кароч представим КУЧУ крутых методов чтобы ну там ээээ ну ээээ найти КЛАСС
    };
}
