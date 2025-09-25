#include "../include/class.h"
#include "../include/method.h"
#include "../include/field.h"
#include "../include/object.h"
#include "../include/array.h"
#include "../include/domain.h"
#include "../include/exportcall.h"

namespace IL2CPP
{
    const char *Class::Name()
    {
        return IL2CPP::ExportCall::ClassGetName((void *)this);
    }

    IL2CPP::Object *Class::New()
    {
        return (IL2CPP::Object *)IL2CPP::ExportCall::ObjectNew((void *)this);
    }

    int Class::ElementSize()
    {
        return IL2CPP::ExportCall::ClassArrayElementSize((void *)this);
    }

    bool Class::isEnum()
    {
        return IL2CPP::ExportCall::ClassIsEnum((void *)this);
    }

    bool Class::isInterface()
    {
        return IL2CPP::ExportCall::ClassIsInterface((void *)this);
    }

    bool Class::isValueType()
    {
        return IL2CPP::ExportCall::ClassIsValueType((void *)this);
    }

    bool Class::isStruct()
    {
        return !this->isEnum() && this->isValueType();
    }

    const char *Class::Namespace()
    {
        return IL2CPP::ExportCall::ClassGetNamespace((void *)this);
    }

    const char *Class::Fullname()
    {
        return (std::string(this->Namespace()) + "::" + std::string(this->Name())).c_str();
    }

    IL2CPP::Method Class::Method(const char *Name, int ArgCount)
    {
        return IL2CPP::Method((uintptr_t)IL2CPP::ExportCall::MethodFromName((void *)this, Name, ArgCount));
    }

    IL2CPP::Method Class::Method(const char *Name, std::vector<std::string> ArgTypes)
    {
        IL2CPP::Method result(0, 0);
        std::vector<IL2CPP::Method> methods = this->Methods();

        for (size_t i = 0; i < methods.size(); i++)
        {
            if (strcmp(methods[i].Name(), Name) == 0)
            {
                if (ArgTypes.size() == methods[i].ParametersCount())
                {
                    std::vector<IL2CPP::Parameter> parameters = methods[i].Parameters();
                    if (parameters.size() == ArgTypes.size())
                    {
                        for (size_t k = 0; k < ArgTypes.size(); k++)
                        {
                            bool found = true;
                            if (parameters[k].Type->Name() != ArgTypes[k])
                                found = false;

                            if (found)
                                result = methods[i];
                        }
                    }
                }
            }
        }

        if (result.Handle == 0)
            LOG(std::format("Couldn't find method \"{}\" in \"{}\" with setted parameters.", Name, this->Fullname()));

        return result;
    }

    IL2CPP::Method Class::MethodByIO(const char *Method, int Offset)
    {
        std::vector<IL2CPP::Method> methods = this->Methods();
        for (size_t i = 0; i < methods.size(); i++)
        {
            if (strcmp(methods[i].Name(), Method))
                return methods[i + Offset];
        }

        LOG(std::format("Couldn't find method by IO. Name: {}; Index: {}", Method, Offset));

        return IL2CPP::Method(0, 0);
    }

    IL2CPP::Field Class::FieldByIO(const char *Field, int Offset)
    {
        std::vector<IL2CPP::Field> fields = this->Fields();
        for (size_t i = 0; i < fields.size(); i++)
        {
            if (strcmp(fields[i].Name(), Field))
                return fields[i + Offset];
        }

        LOG(std::format("Couldn't find field by IO. Name: {}; Index: {}", Field, Offset));

        return IL2CPP::Field(0, 0);
    }

    IL2CPP::Field Class::Field(const char *Name)
    {
        return IL2CPP::Field((uintptr_t)IL2CPP::ExportCall::FieldFromName((void *)this, Name));
    }

    std::vector<IL2CPP::Method> Class::Methods()
    {
        std::vector<IL2CPP::Method> result;
        void *iterator = nullptr;
        void *m_handle = IL2CPP::ExportCall::ClassGetMethods((void *)this, &iterator);
        while (m_handle != NULL)
        {
            result.push_back(IL2CPP::Method((uintptr_t)m_handle));
            m_handle = IL2CPP::ExportCall::ClassGetMethods((void *)this, &iterator);
        }

        return result;
    }

    std::vector<IL2CPP::Field> Class::Fields()
    {
        std::vector<IL2CPP::Field> result;
        void *iterator = nullptr;
        void *m_handle = IL2CPP::ExportCall::ClassGetFields((void *)this, &iterator);
        while (m_handle != NULL)
        {
            result.push_back(IL2CPP::Field((uintptr_t)m_handle));
            m_handle = IL2CPP::ExportCall::ClassGetFields((void *)this, &iterator);
        }

        return result;
    }

    IL2CPP::Type *Class::Type()
    {
        return (IL2CPP::Type *)IL2CPP::ExportCall::TypeFromClass((void *)this);
    }

    IL2CPP::Type *Class::BaseType()
    {
        return (IL2CPP::Type *)IL2CPP::ExportCall::ClassEnumBasetype((void *)this);
    }

    IL2CPP::Type *Class::ReflectionType()
    {
        return (IL2CPP::Type *)IL2CPP::ExportCall::TypeGetObject(this->Type());
    }

    std::vector<IL2CPP::Class *> Class::Interfaces()
    {
        std::vector<IL2CPP::Class *> result;
        void *iterator = nullptr;
        void *m_handle = IL2CPP::ExportCall::ClassGetInterfaces((void *)this, &iterator);
        while (m_handle != NULL)
        {
            result.push_back((IL2CPP::Class *)m_handle);
            m_handle = IL2CPP::ExportCall::ClassGetInterfaces((void *)this, &iterator);
        }

        return result;
    }

    std::vector<IL2CPP::Class *> Class::NestedClasses()
    {
        std::vector<IL2CPP::Class *> result;
        void *iterator = nullptr;
        void *m_handle = IL2CPP::ExportCall::ClassNestedClasses((void *)this, &iterator);
        while (m_handle != NULL)
        {
            result.push_back((IL2CPP::Class *)m_handle);
            m_handle = IL2CPP::ExportCall::ClassNestedClasses((void *)this, &iterator);
        }

        return result;
    }

    IL2CPP::Class *Class::Nested(const char *Name)
    {
        std::vector<IL2CPP::Class *> vec{this->NestedClasses()};
        if (vec.size() == 0)
        {
            return (IL2CPP::Class *)nullptr;
        }

        for (auto klass : vec)
        {
            if (strcmp(klass->Name(), Name) == 0)
            {
                return klass;
                break;
            }
        }

        LOG(std::format("Couldn't find nested class \"{}\" in \"{}\"", Name, this->Fullname()));
        return nullptr;
    }

    IL2CPP::Class *Class::Inflate(std::vector<IL2CPP::Class *> Types)
    {
        IL2CPP::Array *types = IL2CPP::Array::New(IL2CPP::Domain::Assembly("mscorlib")->Image()->Class("System.Type"), Types.size());

        for (size_t i = 0; i < Types.size(); i++)
        {
            types->Set(i, Types.at(i)->Type()->Object());
        }

        return (IL2CPP::Class *)(IL2CPP::ExportCall::ClassFromSystemType(this->Type()->Object()->Method("MakeGenericType", 1).Invoke<void *>(types)));
    }

    std::string Class::ToString(const DumperParameters &Parameters, int Index)
    {
        std::string result;

        if (Parameters.ShowIndexes)
            result += std::format("[{}] ", Index);

        if (this->isStruct())
            result += "struct ";
        else if (this->isEnum())
            result += "enum ";
        else if (this->isInterface())
            result += "interface ";
        else
            result += "class ";

        const char *Namespace = this->Namespace();
        if (strlen(Namespace) > 1)
            result += Namespace + std::string(".");
        result += this->Name();

        std::vector<IL2CPP::Class *> interfaces = this->Interfaces();
        int interfaces_count = interfaces.size();
        if (interfaces_count > 0)
        {
            result += " : ";
            size_t index = 0;
            for (auto it : interfaces)
            {
                result += it->Name();
                if (index++ < interfaces_count)
                    result += ", ";
            }
        }

        result += " {\n";

        std::vector<IL2CPP::Field> Fields = this->Fields();
        std::vector<IL2CPP::Method> Methods = this->Methods();

        result += "\n    // Fields:\n";

        size_t index = 0;
        for (auto it : Fields)
        {
            result += "    ";
            if (it.isLiteral())
            {
                const char *type = it.Type()->Name();
                if (strcmp(type, "System.Int32") == 0 || strcmp(type, "System.Int64") == 0)
                {
                    result += std::format("{}\n", it.ToString(Parameters, index, std::to_string(it.GetValue<int64_t>())));
                }
                else if (strcmp(type, "System.Single") == 0)
                {
                    result += std::format("{}\n", it.ToString(Parameters, index, std::to_string(it.GetValue<float>())));
                }
                else if (strcmp(type, "System.String") == 0)
                {
                    result += std::format("{}\n", it.ToString(Parameters, index, it.GetValue<IL2CPP::String *>()->Content()));
                }
                else if (it.Type()->Class()->isEnum())
                {
                    result += std::format("{}\n", it.ToString(Parameters, index, std::to_string(it.GetValue<int>())));
                }
                else
                {
                    result += std::format("{}\n", it.ToString(Parameters, index));
                }
            }
            else
            {
                result += std::format("{}\n", it.ToString(Parameters, index));
            }
            index++;
        }
        result += "\n    // Methods:\n";

        index = 0;
        for (auto it : Methods)
        {
            result += std::format("    {}\n", it.ToString(Parameters, index));
            index++;
        }
        result += "\n}";

        return result;
    }
}