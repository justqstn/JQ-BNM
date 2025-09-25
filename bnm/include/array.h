#pragma once

#include "string.h"
#include "object.h"

namespace
{
    uintptr_t ArrayOffset = 0;
    uintptr_t GetArrayOffset(void *StartPtr, int16_t Value)
    {
        if (ArrayOffset == 0)
        {
            int depth = 512;
            for (int i = 0; i < depth; i++)
            {
                if ((uint16_t)(*((char *)((void *)((uintptr_t)StartPtr + i)))) == Value)
                {
                    ArrayOffset = i;
                    return i;
                }
            }
            return 0;
        }
        else
            return ArrayOffset;
    }
}

namespace IL2CPP
{
    struct Array
    {
    public:
        static IL2CPP::Array *New(IL2CPP::Class *Class, int length);
        int Length();
        IL2CPP::Object *Object();
        IL2CPP::Type *ElementType();
        int ElementSize();

        template <typename T>
        T *Elements()
        {
            IL2CPP::Object *str = (IL2CPP::Object *)IL2CPP::String::New("v");
            IL2CPP::Object *char_array = str->Method("ToCharArray", 0).Invoke<IL2CPP::Object *>();
            uint64_t offset = GetArrayOffset((void *)char_array, 118);
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