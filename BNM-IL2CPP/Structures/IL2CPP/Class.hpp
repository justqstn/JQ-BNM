#pragma once

#include "../../ExportCall.hpp"
#include "Method.hpp"
#include "Field.hpp"
#include <vector>
#include <algorithm>

namespace IL2CPP
{
    struct Class
    {
    public:
        const char *Name()
        {
            return IL2CPP::ExportCall::ClassGetName((void *)this);
        }

        // Return method of class by the name and parameter count
        IL2CPP::Method *Method(const char *name, int parameter_count = -1)
        {
            return (IL2CPP::Method *)IL2CPP::ExportCall::MethodFromName((void *)this, name, parameter_count);
        }

        // Return field of class by the name
        IL2CPP::Field *Field(const char *name)
        {
            return (IL2CPP::Field *)(IL2CPP::ExportCall::FieldFromName((void *)this, name));
        }

        // Returns size of erm what the sigma
        int ElementSize()
        {
            return IL2CPP::ExportCall::ClassArrayElementSize((void *)this);
        }

        void *Type()
        {
            return IL2CPP::ExportCall::TypeFromClass((void *)this);
        }

        void *BaseType()
        {
            return IL2CPP::ExportCall::ClassEnumBasetype((void *)this);
        }

        std::vector<IL2CPP::Class *> NestedClasses()
        {
            std::vector<IL2CPP::Class *> arr;
            void *iterator = nullptr;
            void *m_handle = IL2CPP::ExportCall::ClassNestedClasses((void *)this, &iterator);
            while (m_handle != NULL)
            {
                arr.push_back((IL2CPP::Class *)m_handle);
                m_handle = IL2CPP::ExportCall::ClassNestedClasses((void *)this, &iterator);
            }

            return arr;
        }

        IL2CPP::Class *Nested(const char *name)
        {
            std::vector<IL2CPP::Class *> vec{this->NestedClasses()};
            if (vec.size() == 0)
            {
                return (IL2CPP::Class *)nullptr;
            }

            for (auto klass : vec)
            {
                if (strcmp(klass->Name(), name) == 0)
                {
                    return klass;
                    break;
                }
            }
        }
    };

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

        IL2CPP::Field *Field(const char *name)
        {
            return (IL2CPP::Field *)(IL2CPP::ExportCall::FieldFromName((void *)(this->Class()), name));
        }
    };

    struct Type
    {
    public:
        IL2CPP::Class *Class()
        {
            return (IL2CPP::Class *)IL2CPP::ExportCall::ClassFromType((void *)this);
        }
    };
}