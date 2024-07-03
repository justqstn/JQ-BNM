#pragma once

#include "../../ExportCall.hpp"
#include "Class.hpp"
#include "Method.hpp"
#include <cstdint>
#include <string>

namespace IL2CPP
{
    class Array
    {
    public:
        Array(void *address)
        {
            this->handle = address;
        }

        static IL2CPP::Array New(IL2CPP::Class klass, int length)
        {
            return IL2CPP::ExportCall::ArrayNew(klass.Address(), length);
        }

        /*template<typename T>
        T Type() {

        }*/

        int Length()
        {
            return IL2CPP::ExportCall::ArrayLength(this->handle);
        }

        IL2CPP::Object Object()
        {
            return IL2CPP::Object(this->handle);
        }

        IL2CPP::Type ElementType()
        {
            return IL2CPP::Type(IL2CPP::Type(this->Object().Class().Type()).Class().BaseType());
        }

        int ElementSize()
        {
            return IL2CPP::Class(this->ElementType().Address()).ElementSize();
        }

        void *Elements()
        {
            void *str = IL2CPP::ExportCall::StringNew("v");
            void *(*toCharArray)(void *) = (void *(*)(void *))((IL2CPP::Method(IL2CPP::ExportCall::MethodFromName(IL2CPP::ExportCall::ClassFromName(IL2CPP::ExportCall::AssemblyGetImage(IL2CPP::ExportCall::GetAssemblyFromDomain(IL2CPP::ExportCall::GetDomain(), "mscorlib")), "System", "String"), "ToCharArray", 0)).VA()));
            void *charArray = toCharArray(str);
            uint64_t offset = IL2CPP::Array::offsetOf(charArray, 118);

            uint64_t addr = (uint64_t)this->handle + offset;
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

        void *Address()
        {
            return this->handle;
        }

    private:
        void *handle;

        static uint64_t offsetOf(void *start_ptr, int16_t value)
        {
            int depth = 512;
            for (int i = 0; i < depth; i++)
            {
                if ((uint16_t)(*((char *)((void *)((uint64_t)start_ptr + i)))) == value)
                {
                    return i;
                }
            }

            return 0;
        }
    };
}