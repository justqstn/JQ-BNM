#pragma once
#include "../../ExportCall.hpp"
#include "Method.hpp"
#include "Field.hpp"
#include "Class.hpp"

namespace IL2CPP
{
    struct Class;
    struct Object
    {
    public:
        // Returns class of object.
        IL2CPP::Class *Class()
        {
            return (IL2CPP::Class *)IL2CPP::ExportCall::ObjectGetClass((void *)this);
        }

        static IL2CPP::Object *New(IL2CPP::Class *klass)
        {
            return (IL2CPP::Object *)IL2CPP::ExportCall::ObjectNew((void *)klass);
        }

        // Return method of object instance  by the name and parameter count
        IL2CPP::Method Method(const char *name, int parameter_count = -1)
        {
            return IL2CPP::Method(IL2CPP::ExportCall::MethodFromName((void *)this->Class(), name, parameter_count), this);
        }

        // Return field of object instance by the name
        IL2CPP::Field Field(const char *name)
        {
            return IL2CPP::Field(IL2CPP::ExportCall::FieldFromName((void *)this->Class(), name), this);
        }

        /*IL2CPP::Object *Box()
        {
            return (IL2CPP::Object *)(IL2CPP::ExportCall::ValueBox((void *)this, (void *)this->Class()->Type()));
        }*/
    };
}