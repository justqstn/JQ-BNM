#include <cstdint>

#include "../include/array.h"
#include "../include/exportcall.h"

namespace IL2CPP
{
    IL2CPP::Array *Array::New(IL2CPP::Class *Class, int Length)
    {
        return (IL2CPP::Array *)IL2CPP::ExportCall::ArrayNew((void *)Class, Length);
    }

    int Array::Length()
    {
        return IL2CPP::ExportCall::ArrayLength((void *)this);
    }

    IL2CPP::Object *Array::Object()
    {
        return (IL2CPP::Object *)this;
    }

    IL2CPP::Type *Array::ElementType()
    {
        return this->Object()->Class()->Type()->Class()->BaseType();
    }

    int Array::ElementSize()
    {
        return ((IL2CPP::Class *)(this->ElementType()))->ElementSize();
    }
}