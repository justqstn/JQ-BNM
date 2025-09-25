#include "../include/type.h"
#include "../include/exportcall.h"
#include "../include/class.h"
#include "../include/object.h"

namespace IL2CPP
{
    IL2CPP::Class *Type::Class()
    {
        return (IL2CPP::Class *)IL2CPP::ExportCall::ClassFromType((void *)this);
    }

    const char *Type::Name()
    {
        return IL2CPP::ExportCall::TypeGetName((void *)this);
    }

    IL2CPP::Object *Type::Object()
    {
        return (IL2CPP::Object *)IL2CPP::ExportCall::TypeGetObject((void *)this);
    }
}
