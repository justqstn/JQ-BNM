#pragma once

#include "../../ExportCall.hpp"
#include "../../Offsets.hpp"
#include "Method.hpp"
#include "Field.hpp"
#include "Object.hpp"
#include "Type.hpp"
#include "String.hpp"
#include <vector>
#include <algorithm>

namespace IL2CPP
{
    struct Object;
    struct Type;
    struct Class
    {
    public:
        const char *Name()
        {
            return IL2CPP::ExportCall::ClassGetName((void *)this);
        }

        IL2CPP::Object *New()
        {
            return (IL2CPP::Object *)IL2CPP::ExportCall::ObjectNew((void *)this);
        }
        // Return method of class by the name and parameter count
        IL2CPP::Method Method(const char *name, int parameter_count = -1)
        {
            return IL2CPP::Method(IL2CPP::ExportCall::MethodFromName((void *)this, name, parameter_count));
        }

        // Return field of class by the name
        IL2CPP::Field Field(const char *name)
        {
            return IL2CPP::Field(IL2CPP::ExportCall::FieldFromName((void *)this, name));
        }

        // Returns size of erm what the sigma
        int ElementSize()
        {
            return IL2CPP::ExportCall::ClassArrayElementSize((void *)this);
        }

        IL2CPP::Type *Type()
        {
            return (IL2CPP::Type *)IL2CPP::ExportCall::TypeFromClass((void *)this);
        }

        IL2CPP::Type *BaseType()
        {
            return (IL2CPP::Type *)IL2CPP::ExportCall::ClassEnumBasetype((void *)this);
        }

        bool isEnum()
        {
            return IL2CPP::ExportCall::ClassIsEnum((void *)this);
        }

        bool isInterface()
        {
            return IL2CPP::ExportCall::ClassIsInterface((void *)this);
        }

        bool isValueType()
        {
            return IL2CPP::ExportCall::ClassIsValueType((void *)this);
        }

        bool isStruct()
        {
            return !this->isEnum() && this->isValueType();
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

        std::vector<IL2CPP::Method> Methods()
        {
            std::vector<IL2CPP::Method> arr;
            void *iterator = nullptr;
            void *m_handle = IL2CPP::ExportCall::ClassGetMethods((void *)this, &iterator);
            while (m_handle != NULL)
            {
                arr.push_back(IL2CPP::Method(m_handle));
                m_handle = IL2CPP::ExportCall::ClassGetMethods((void *)this, &iterator);
            }

            return arr;
        }

        std::vector<IL2CPP::Field> Fields()
        {
            std::vector<IL2CPP::Field> arr;
            void *iterator = nullptr;
            void *m_handle = IL2CPP::ExportCall::ClassGetFields((void *)this, &iterator);
            while (m_handle != NULL)
            {
                arr.push_back(IL2CPP::Field(m_handle));
                m_handle = IL2CPP::ExportCall::ClassGetFields((void *)this, &iterator);
            }

            return arr;
        }

        const char *Namespace()
        {
            return IL2CPP::ExportCall::ClassGetNamespace((void *)this);
        }

        std::string ToString(bool show_offsets = true, bool show_patterns = false, int patterns_length = 16)
        {
            std::string result;
            LOG_DEBUG("1");
            if (this->isStruct())
                result += "struct ";
            else if (this->isEnum())
                result += "enum ";
            else if (this->isInterface())
                result += "interface ";
            else
                result += "class ";

            const char *Namespace = this->Namespace();
            result += this->Name();

            result += " {\n";

            std::vector<IL2CPP::Field> Fields = this->Fields();
            std::vector<IL2CPP::Method> Methods = this->Methods();

            result += "\n    // Fields:\n";

            for (auto it : Fields)
            {
                result += "    ";
                if (it.isStatic() && it.isLiteral())
                {
                    const char *type = it.Type()->Name();
                    if (strcmp(type, "System.Int32") == 0 || strcmp(type, "System.Int64") == 0)
                    {
                        result += it.ToString(std::to_string(it.GetValue<int64_t>()), show_offsets, show_patterns, patterns_length) + "\n";
                    }
                    else if (strcmp(type, "System.Single") == 0)
                    {
                        result += it.ToString(std::to_string(it.GetValue<float>()), show_offsets, show_patterns, patterns_length) + "\n";
                    }
                    else if (strcmp(type, "System.String") == 0)
                    {
                        result += it.ToString('"' + it.GetValue<IL2CPP::String *>()->Content() + '"', show_offsets, show_patterns, patterns_length) + "\n";
                    }
                    else
                    {
                        result += it.ToString(show_offsets, show_patterns, patterns_length) + "\n";
                    }
                }
                else if (it.Type()->Class()->isEnum())
                {
                    result += it.ToString(std::to_string(it.GetValue<int>()), show_offsets, show_patterns, patterns_length) + "\n";
                }
                else
                {
                    result += it.ToString(show_offsets, show_patterns, patterns_length) + "\n";
                }
            }

            result += "\n    // Methods:\n";
            for (auto it : Methods)
            {
                result += "    " + it.ToString(show_offsets, show_patterns, patterns_length) + "\n";
            }
            result += "\n}";
            return result;
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

        IL2CPP::Type *ReflectionType()
        {
            return (IL2CPP::Type *)IL2CPP::ExportCall::TypeGetObject(this->Type());
        }

        // Returns generic instance of generic class with given parameters
        IL2CPP::Class *Inflate(std::vector<IL2CPP::Class *> types)
        {
            void *il2cpp_array_types = IL2CPP::ExportCall::ArrayNew(IL2CPP::ExportCall::ClassFromName(IL2CPP::ExportCall::AssemblyGetImage(IL2CPP::ExportCall::GetAssemblyFromDomain(IL2CPP::ExportCall::GetDomain(), "mscorlib")), "System", "Type"), types.size());
            void *str = IL2CPP::ExportCall::StringNew("v");
            void *(*toCharArray)(void *) = (void *(*)(void *))((((IL2CPP::Method *)(IL2CPP::ExportCall::MethodFromName(IL2CPP::ExportCall::ClassFromName(IL2CPP::ExportCall::AssemblyGetImage(IL2CPP::ExportCall::GetAssemblyFromDomain(IL2CPP::ExportCall::GetDomain(), "mscorlib")), "System", "String"), "ToCharArray", 0)))->VA()));
            void *charArray = toCharArray(str);
            uint64_t offset = IL2CPP::Offsets::offsetOfCharArray(charArray, 118);
            void *array_elements = (void *)((uint64_t)il2cpp_array_types + offset);
            for (int i = 0; i < types.size(); i++)
            {
                *(void **)((uint64_t)array_elements + i * sizeof(void *)) = IL2CPP::ExportCall::TypeGetObject((types.at(i))->Type());
            }
            IL2CPP::Method *MakeGenericType_method = ((IL2CPP::Class *)(IL2CPP::ExportCall::ObjectGetClass(IL2CPP::ExportCall::TypeGetObject(this->Type()))))->Method("MakeGenericType", 1);
            void *(*MakeGenericType)(void *, void *) = (void *(*)(void *, void *))((void *)(MakeGenericType_method->VA()));
            return (IL2CPP::Class *)(IL2CPP::ExportCall::ClassFromSystemType(MakeGenericType((IL2CPP::ExportCall::TypeGetObject(this->Type())), il2cpp_array_types)));
        }
    };
}