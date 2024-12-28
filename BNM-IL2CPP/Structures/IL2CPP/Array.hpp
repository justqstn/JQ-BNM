#pragma once

#include "../../ExportCall.hpp"
#include "../../Offsets.hpp"
#include "Class.hpp"
#include "Object.hpp"
#include "Method.hpp"
#include "String.hpp"
#include <cstdint>
#include <string>

// sex

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
            return this->Object()->Class()->Type()->Class()->BaseType();
        }

        int ElementSize()
        {
            return ((IL2CPP::Class *)(this->ElementType()))->ElementSize();
        }

        template <typename T>
        T *Elements()
        {
            IL2CPP::Object *str = (IL2CPP::Object *)IL2CPP::String::New("v");
            IL2CPP::Object *charArray = str->Method("ToCharArray", 0).Invoke<IL2CPP::Object *>();
            uint64_t offset = IL2CPP::Offsets::offsetOfCharArray((void *)charArray, 118);
            uint64_t addr = (uint64_t)this + offset;
            return (T *)addr;
        }

        template <typename T>
        T Get(int index)
        {
            return this->Elements<T>()[index];
        }

        template <typename T>
        void Set(int index, T value)
        {
            this->Elements<T>()[index] = value;
        }
    };
}