#pragma once

#include "../../ExportCall.hpp"
#include "Assembly.hpp"

namespace IL2CPP
{
    class Domain
    {
    public:
        Domain()
        {
            this->handle = IL2CPP::ExportCall::GetDomain();
        }

        void *Address()
        {
            return this->handle;
        }

        // Returns assembly by the name
        IL2CPP::Assembly Assembly(const char *name)
        {
            return IL2CPP::Assembly(IL2CPP::ExportCall::GetAssemblyFromDomain(this->handle, name));
        }

        // а тут мы кароч представим КУЧУ крутых методов чтобы ну там ээээ ну ээээ найти КЛАСС

    private:
        void *handle;
    };
}
