#pragma once

#include "string.h"
#include "object.h"

namespace
{
    uintptr_t ArrayOffset = 0;
    // Gets offset of C-Array in IL2CPP::Array by comparing value of first element.
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
        // Creates new array instance with given class and length @return Pointer to array
        static IL2CPP::Array *New(IL2CPP::Class *Class, int length);
        // @return Array length
        int Length();
        IL2CPP::Object *Object();
        // @return Array type
        IL2CPP::Type *ElementType();
        // @return Array type size
        int ElementSize();

        // @return C-array of elements
        template <typename T>
        T *Elements()
        {
            IL2CPP::Object *str = (IL2CPP::Object *)IL2CPP::String::New("v");
            IL2CPP::Object *char_array = str->Method("ToCharArray", 0).Invoke<IL2CPP::Object *>();
            uint64_t offset = GetArrayOffset((void *)char_array, 118);
            uint64_t addr = (uint64_t)this + offset;
            return (T *)addr;
        }

        // @return Element by index
        template <typename T>
        T Get(int index)
        {
            return this->Elements<T>()[index];
        }

        // @return Sets element by index
        template <typename T>
        void Set(int index, T value)
        {
            this->Elements<T>()[index] = value;
        }
    };
}