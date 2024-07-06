#pragma once

#include "../../ExportCall.hpp"
#include "../../Offsets.hpp"
#include "Class.hpp"
#include "Method.hpp"
#include <cstdint>
#include <string>

namespace IL2CPP
{
    struct Array
    {
    public:
        static IL2CPP::Array *New(IL2CPP::Class *klass, int length)
        {
            return (IL2CPP::Array *)IL2CPP::ExportCall::ArrayNew((void *)klass, length);
        }

        /*template<typename T>
        T Type() {

        }*/

        int Length()
        {
            return IL2CPP::ExportCall::ArrayLength((void *)this);
        }

        IL2CPP::Object *Object()
        {
            return (IL2CPP::Object *)this;
        }

        IL2CPP::Type *ElementType()
        {
            return (IL2CPP::Type *)(((IL2CPP::Type *)(this->Object()->Class()->Type()))->Class()->BaseType());
        }

        int ElementSize()
        {
            return ((IL2CPP::Class *)(this->ElementType()))->ElementSize();
        }

        void *Elements()
        {
            void *str = IL2CPP::ExportCall::StringNew("v");
            void *(*toCharArray)(void *) = (void *(*)(void *))((((IL2CPP::Method *)(IL2CPP::ExportCall::MethodFromName(IL2CPP::ExportCall::ClassFromName(IL2CPP::ExportCall::AssemblyGetImage(IL2CPP::ExportCall::GetAssemblyFromDomain(IL2CPP::ExportCall::GetDomain(), "mscorlib")), "System", "String"), "ToCharArray", 0)))->VA()));
            void *charArray = toCharArray(str);
            uint64_t offset = IL2CPP::Offsets::offsetOfCharArray(charArray, 118);

            uint64_t addr = (uint64_t)this + offset;
            return (void *)addr;
        }

        template <typename T>
        T Get(int index)
        {
            return *(T *)((uint64_t)this->Elements() + index * this->ElementSize());
        }

        template <typename T>
        void Set(int index, T value)
        {
            *(T *)((uint64_t)this->Elements() + index * this->ElementSize()) = value;
        }
    };
}