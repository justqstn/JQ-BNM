#pragma once

#include "../../ExportCall.hpp"
#include "Method.hpp"
#include "Field.hpp"
#include <vector>
#include <algorithm>

namespace IL2CPP
{
    class Class
    {
    public:
        Class(void *address)
        {
            this->handle = address;
        }

        const char *Name()
        {
            return IL2CPP::ExportCall::ClassGetName(this->handle);
        }

        void *Address()
        {
            return this->handle;
        }

        // Return method of class by the name and parameter count
        IL2CPP::Method Method(const char *name, int parameter_count = -1)
        {
            return IL2CPP::Method(IL2CPP::ExportCall::MethodFromName(this->handle, name, parameter_count));
        }

        // Return field of class by the name
        IL2CPP::Field Field(const char *name)
        {
            return IL2CPP::Field(IL2CPP::ExportCall::FieldFromName(this->handle, name));
        }

        // Returns size of erm what the sigma
        int ElementSize()
        {
            return IL2CPP::ExportCall::ClassArrayElementSize(this->handle);
        }

        void *Type()
        {
            return IL2CPP::ExportCall::TypeFromClass(this->handle);
        }

        void *BaseType()
        {
            return IL2CPP::ExportCall::ClassEnumBasetype(this->handle);
        }

        std::vector<IL2CPP::Class> NestedClasses()
        {
            std::vector<IL2CPP::Class> arr;
            void *iterator = nullptr;
            void *m_handle = IL2CPP::ExportCall::ClassNestedClasses(this->handle, &iterator);
            while (m_handle != NULL)
            {
                arr.push_back(IL2CPP::Class(m_handle));
                m_handle = IL2CPP::ExportCall::ClassNestedClasses(this->handle, &iterator);
            }

            return arr;
        }

        IL2CPP::Class Nested(const char *name)
        {
            std::vector<IL2CPP::Class> vec{this->NestedClasses()};
            if (vec.size() == 0)
            {
                return IL2CPP::Class(nullptr);
            }

            for (auto klass : vec)
            {
                if (strcmp(klass.Name(), name) == 0)
                {
                    return klass;
                    break;
                }
            }
        }

    private:
        void *handle;
    };

    class Object
    {
    public:
        Object(void *address)
        {
            this->handle = address;
        }

        // Returns class of object.
        IL2CPP::Class Class()
        {
            return IL2CPP::ExportCall::ObjectGetClass(this->handle);
        }

        static IL2CPP::Object New(void *klass)
        {
            return IL2CPP::Object(IL2CPP::ExportCall::ObjectNew(klass));
        }

        static IL2CPP::Object New(IL2CPP::Class klass)
        {
            return IL2CPP::Object(IL2CPP::ExportCall::ObjectNew(klass.Address()));
        }

        IL2CPP::Field Field(const char *name)
        {
            return IL2CPP::Field(IL2CPP::ExportCall::FieldFromName(this->Class().Address(), name), this->handle);
        }

    private:
        void *handle;
    };

    class Type
    {
    public:
        Type(void *address)
        {
            this->handle = address;
        }

        void *Address()
        {
            return this->handle;
        }

        IL2CPP::Class Class()
        {
            return IL2CPP::Class(IL2CPP::ExportCall::ClassFromType(this->handle));
        }

    private:
        void *handle;
    };
}