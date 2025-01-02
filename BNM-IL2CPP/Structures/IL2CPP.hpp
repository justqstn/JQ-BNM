#pragma once

#include <string>
#include <stringapiset.h>
#include <list>
#include <vector>
#include <string>

// #include "../Utils/EasyPattern.hpp" craze sucks my dick
#include "../Utils/Other.hpp"
#include "../ExportCall.hpp"
#include "../Offsets.hpp"
#include "../Defines.hpp"

namespace IL2CPP
{
    struct Domain;
    struct Assembly;
    struct Image;
    struct Type;
    struct Class;
    struct Object;
    struct Parameter;
    class Method;
    class Field;
    struct Array;
    struct String;

    /*
   IL2CPP::Domain definition
   */

    struct Domain
    {
    public:
        Domain();
        IL2CPP::Assembly *Assembly(const char *name);
        IL2CPP::Object *Object();
        std::vector<IL2CPP::Assembly *> Assemblies();
    };

    /*
   IL2CPP::Assembly definition
   */

    struct Assembly
    {
    public:
        IL2CPP::Image *Image();
    };

    /*
   IL2CPP::Image definition
   */

    struct Image
    {
    public:
        const char *Name();
        IL2CPP::Class *Class(const char *_fullname);
        IL2CPP::Class *Class(const char *k_namespace, const char *k_name);
        unsigned int ClassCount();
        std::vector<IL2CPP::Class *> Classes();
        std::string ToString(bool show_offsets = true, bool show_patterns = false, int patterns_length = 16);
    };

    /*
   IL2CPP::Type definition
   */

    struct Type
    {
    public:
        IL2CPP::Class *Class();
        const char *Name();
        IL2CPP::Object *Object();
    };

    /*
   IL2CPP::Class definition
   */

    struct Class
    {
    public:
        const char *Name();
        IL2CPP::Object *New();
        IL2CPP::Method Method(const char *name, int parameter_count = -1);
        IL2CPP::Method Method(const char *name, std::vector<std::string> arg_types);
        IL2CPP::Field Field(const char *name);
        int ElementSize();
        IL2CPP::Type *Type();
        IL2CPP::Type *BaseType();
        bool isEnum();
        bool isInterface();
        bool isValueType();
        bool isStruct();
        std::vector<IL2CPP::Class *> Interfaces();
        std::vector<IL2CPP::Class *> NestedClasses();
        std::vector<IL2CPP::Method> Methods();
        std::vector<IL2CPP::Field> Fields();
        const char *Namespace();
        std::string ToString(bool show_offsets = true, bool show_patterns = false, int patterns_length = 16);
        IL2CPP::Class *Nested(const char *name);
        IL2CPP::Type *ReflectionType();
        IL2CPP::Class *Inflate(std::vector<IL2CPP::Class *> types);
    };

    /*
   IL2CPP::Object definition
   */

    struct Object
    {
    public:
        IL2CPP::Class *Class();
        static IL2CPP::Object *New(IL2CPP::Class *klass);
        IL2CPP::Method Method(const char *name, int parameter_count = -1);
        IL2CPP::Method Method(const char *name, std::vector<std::string> arg_types);
        IL2CPP::Field Field(const char *name);
    };

    struct Parameter
    {
        IL2CPP::Type *type;
        const char *name;

        std::string ToString();
    };

    /*
   IL2CPP::Method definition
   */

    class Method
    {
    public:
        template <typename T>
        Method(T handle);

        template <typename T, typename T2>
        Method(T handle, T2 object);

        template <typename T>
        operator T();

        uint32_t ParametersCount();
        std::vector<Parameter> Parameters();
        IL2CPP::Type *ReturnType();
        std::string ToString(bool show_offset = true, bool show_pattern = false, int pattern_length = 16);
        enum class Attributes;
        const char *Name();
        uint64_t VA();
        uint64_t RVA();
        bool isInflated();
        bool isStatic();
        IL2CPP::Object *Object();
        std::vector<IL2CPP::Class *> Generics();
        IL2CPP::Method Inflate(std::vector<IL2CPP::Class *> classes);

        template <typename T, typename... Args>
        T Invoke(Args... args);

        void *instance;
        void *object_instance;
    };

    /*
    IL2CPP::Field definition
    */

    class Field
    {
    public:
        template <typename T>
        Field(T handle);

        template <typename T, typename T2>
        Field(T handle, T2 object);

        template <typename T>
        operator T();

        enum class Attributes;
        int Flags();
        bool isStatic();
        bool isLiteral();
        int Offset();

        template <typename T>
        T GetValue();

        template <typename T>
        void SetValue(T value);

        const char *Name();
        IL2CPP::Type *Type();
        std::string ToString(bool show_offset = true);
        std::string ToString(std::string val, bool show_offset = true);

        void *instance;
        void *object_instance;
    };

    /*
    IL2CPP::Array definition
    */

    struct Array
    {
    public:
        static IL2CPP::Array *New(IL2CPP::Class *klass, int length);
        int Length();
        IL2CPP::Object *Object();
        IL2CPP::Type *ElementType();
        int ElementSize();

        template <typename T>
        T *Elements();

        template <typename T>
        T Get(int index);

        template <typename T>
        void Set(int index, T value);
    };

    /*
    IL2CPP::String definition
    */

    struct String
    {
    public:
        static IL2CPP::String *New(const char *content);
        int Length();
        std::string Content();
    };

    /*
    IL2CPP::Domain implementation
    */

    // Returns main domain of application.
    Domain::Domain()
    {
        IL2CPP::ExportCall::GetDomain();
    }

    // Returns assembly by the name.
    IL2CPP::Assembly *Domain::Assembly(const char *name)
    {
        return (IL2CPP::Assembly *)(IL2CPP::ExportCall::GetAssemblyFromDomain((void *)this, name));
    }

    // Returns domain's object.
    IL2CPP::Object *Domain::Object()
    {
        return IL2CPP::Domain().Assembly("mscorlib")->Image()->Class("System.AppDomain")->Method("get_CurrentDomain").Invoke<IL2CPP::Object *>();
    }

    // Returns vector of all assemblies.
    std::vector<IL2CPP::Assembly *> Domain::Assemblies()
    {
        std::vector<IL2CPP::Assembly *> arr;

        IL2CPP::Array *il2cpp_arr = this->Object()->Method("GetAssemblies", 0).Invoke<IL2CPP::Array *>();
        LOG_DEBUG("Found " + std::to_string(il2cpp_arr->Length()) + " assemblies.");
        for (size_t i = 0; i < il2cpp_arr->Length(); i++)
        {
            arr.push_back(il2cpp_arr->Get<IL2CPP::Object *>(i)->Field("_mono_assembly").GetValue<IL2CPP::Assembly *>());
        }

        return arr;
    }

    /*
    IL2CPP::Assembly implementation
    */

    // Returns image of assembly.
    IL2CPP::Image *Assembly::Image()
    {
        return (IL2CPP::Image *)(IL2CPP::ExportCall::AssemblyGetImage((void *)this));
    }

    /*
    IL2CPP::Image implementation
    */

    // Returns name of image.
    const char *Image::Name()
    {
        return IL2CPP::ExportCall::ImageGetName((void *)this);
    }

    // Returns class of assembly by the name. @param _fullname format of name: NAMESPACE.NAME
    IL2CPP::Class *Image::Class(const char *_fullname)
    {
        std::string fullname = _fullname;
        size_t lastindex = fullname.find_last_of(".");
        if (lastindex > fullname.size())
        {
            return (IL2CPP::Class *)(IL2CPP::ExportCall::ClassFromName((void *)this, "", _fullname));
        }
        else
        {
            return (IL2CPP::Class *)(IL2CPP::ExportCall::ClassFromName((void *)this, fullname.substr(0, lastindex).c_str(), fullname.substr(lastindex + 1, fullname.length()).c_str()));
        }
    }

    // Return class of assembly by the namespace and name.
    IL2CPP::Class *Image::Class(const char *k_namespace, const char *k_name)
    {
        return (IL2CPP::Class *)(IL2CPP::ExportCall::ClassFromName((void *)this, k_namespace, k_name));
    }

    // Returns count of classes of image.
    unsigned int Image::ClassCount()
    {
        return IL2CPP::ExportCall::ImageGetClassCount((void *)this);
    }

    // Returns vector of classes.
    std::vector<IL2CPP::Class *> Image::Classes()
    {
        std::vector<IL2CPP::Class *> result;
        for (size_t i = 0; i < this->ClassCount(); i++)
        {
            result.push_back((IL2CPP::Class *)(IL2CPP::ExportCall::ImageGetClass((void *)this, i)));
        }

        return result;
    }

    // Returns dumpe dimage in dumped format.
    std::string Image::ToString(bool show_offsets, bool show_patterns, int patterns_length)
    {
        std::string result;
        std::vector<IL2CPP::Class *> classes = this->Classes();
        for (size_t i = 0; i < classes.size(); i++)
        {
            result += std::string("// ") + this->Name() + std::string("\n");
            result += classes[i]->ToString(show_offsets, show_patterns, patterns_length);
            result += "\n";
        }
        return result;
    }

    /*
    IL2CPP::Type implementation
    */

    // Returns class of type.
    IL2CPP::Class *Type::Class()
    {
        return (IL2CPP::Class *)IL2CPP::ExportCall::ClassFromType((void *)this);
    }

    // Returns name of type.
    const char *Type::Name()
    {
        return IL2CPP::ExportCall::TypeGetName((void *)this);
    }

    // Returns object of type.
    IL2CPP::Object *Type::Object()
    {
        return (IL2CPP::Object *)IL2CPP::ExportCall::TypeGetObject((void *)this);
    }

    /*
    IL2CPP::Class implementation
    */

    // Returns name of class.
    const char *Class::Name()
    {
        return IL2CPP::ExportCall::ClassGetName((void *)this);
    }

    // Creates new instance of class.
    IL2CPP::Object *Class::New()
    {
        return (IL2CPP::Object *)IL2CPP::ExportCall::ObjectNew((void *)this);
    }
    // Returns method of class by the name and parameter count. @note You can't invoke non-static method without IL2CPP::Object instance.
    IL2CPP::Method Class::Method(const char *name, int parameter_count)
    {
        return IL2CPP::Method(IL2CPP::ExportCall::MethodFromName((void *)this, name, parameter_count));
    }

    // Returns method of class by the name and vector of arguments names. @note You can't invoke non-static method without IL2CPP::Object instance.
    IL2CPP::Method Class::Method(const char *name, std::vector<std::string> arg_types)
    {
        IL2CPP::Method result(nullptr, nullptr);
        std::vector<IL2CPP::Method> methods = this->Methods();

        for (size_t i = 0; i < methods.size(); i++)
        {
            if (strcmp(methods[i].Name(), name) == 0)
            {
                if (arg_types.size() == methods[i].ParametersCount())
                {
                    std::vector<IL2CPP::Parameter> parameters = methods[i].Parameters();
                    if (parameters.size() == arg_types.size())
                    {
                        for (size_t k = 0; k < arg_types.size(); k++)
                        {
                            bool found = true;
                            if (parameters[k].type->Name() != arg_types[k])
                                found = false;

                            if (found)
                                result = methods[i];
                        }
                    }
                }
            }
        }

        if (result.instance == nullptr)
            LOG_ERROR("Error: couldn't find method " + std::string(name) + " with given parameters.");

        return result;
    }

    // Returns field by the name. @note You can't get value of non-static field without IL2CPP::Object instance.
    IL2CPP::Field Class::Field(const char *name)
    {
        return IL2CPP::Field(IL2CPP::ExportCall::FieldFromName((void *)this, name));
    }

    // Returns size of erm what the sigma.
    int Class::ElementSize()
    {
        return IL2CPP::ExportCall::ClassArrayElementSize((void *)this);
    }

    // Returns type of class.
    IL2CPP::Type *Class::Type()
    {
        return (IL2CPP::Type *)IL2CPP::ExportCall::TypeFromClass((void *)this);
    }

    // Return base type of class.
    IL2CPP::Type *Class::BaseType()
    {
        return (IL2CPP::Type *)IL2CPP::ExportCall::ClassEnumBasetype((void *)this);
    }

    // Checks if it's enum.
    bool Class::isEnum()
    {
        return IL2CPP::ExportCall::ClassIsEnum((void *)this);
    }

    // Checks if it's interface.
    bool Class::isInterface()
    {
        return IL2CPP::ExportCall::ClassIsInterface((void *)this);
    }

    // Checks if it's value type.
    bool Class::isValueType()
    {
        return IL2CPP::ExportCall::ClassIsValueType((void *)this);
    }

    // Checks if it's struct.
    bool Class::isStruct()
    {
        return !this->isEnum() && this->isValueType();
    }

    // Returns interfaces of class.
    std::vector<IL2CPP::Class *> Class::Interfaces()
    {
        std::vector<IL2CPP::Class *> arr;
        void *iterator = nullptr;
        void *m_handle = IL2CPP::ExportCall::ClassGetInterfaces((void *)this, &iterator);
        while (m_handle != NULL)
        {
            arr.push_back((IL2CPP::Class *)m_handle);
            m_handle = IL2CPP::ExportCall::ClassGetInterfaces((void *)this, &iterator);
        }

        return arr;
    }

    // Returns nested classes of class.
    std::vector<IL2CPP::Class *> Class::NestedClasses()
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

    // Returns methods of class.
    std::vector<IL2CPP::Method> Class::Methods()
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

    // Returns fields of class.
    std::vector<IL2CPP::Field> Class::Fields()
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

    // Returns namespace of class.
    const char *Class::Namespace()
    {
        return IL2CPP::ExportCall::ClassGetNamespace((void *)this);
    }

    // Returns class in dumped format.
    std::string Class::ToString(bool show_offsets, bool show_patterns, int patterns_length)
    {
        std::string result;
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

        for (auto it : Fields)
        {
            result += "    ";
            if (it.isLiteral())
            {
                const char *type = it.Type()->Name();
                if (strcmp(type, "System.Int32") == 0 || strcmp(type, "System.Int64") == 0)
                {
                    result += it.ToString(std::to_string(it.GetValue<int64_t>()), show_offsets) + "\n";
                }
                else if (strcmp(type, "System.Single") == 0)
                {
                    result += it.ToString(std::to_string(it.GetValue<float>()), show_offsets) + "\n";
                }
                else if (strcmp(type, "System.String") == 0)
                {
                    result += it.ToString('"' + it.GetValue<IL2CPP::String *>()->Content() + '"', show_offsets) + "\n";
                }
                else if (it.Type()->Class()->isEnum())
                {
                    result += it.ToString(std::to_string(it.GetValue<int>()), show_offsets) + "\n";
                }
                else
                {
                    result += it.ToString(show_offsets) + "\n";
                }
            }
            else
            {
                result += it.ToString(show_offsets) + "\n";
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

    // Returns nested class of the class by name.
    IL2CPP::Class *Class::Nested(const char *name)
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

    // Returns reflection type of class.
    IL2CPP::Type *Class::ReflectionType()
    {
        return (IL2CPP::Type *)IL2CPP::ExportCall::TypeGetObject(this->Type());
    }

    // Returns generic instance of generic class with given parameters.
    IL2CPP::Class *Class::Inflate(std::vector<IL2CPP::Class *> types)
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

    /*
    IL2CPP::Object implementation
    */

    // Returns class of object.
    IL2CPP::Class *Object::Class()
    {
        return (IL2CPP::Class *)IL2CPP::ExportCall::ObjectGetClass((void *)this);
    }

    IL2CPP::Object *Object::New(IL2CPP::Class *klass)
    {
        return (IL2CPP::Object *)IL2CPP::ExportCall::ObjectNew((void *)klass);
    }

    // Return method of object instance  by the name and parameter count
    IL2CPP::Method Object::Method(const char *name, int parameter_count)
    {
        return IL2CPP::Method(IL2CPP::ExportCall::MethodFromName((void *)this->Class(), name, parameter_count), this);
    }

    IL2CPP::Method Object::Method(const char *name, std::vector<std::string> arg_types)
    {
        IL2CPP::Method result(nullptr, this);
        std::vector<IL2CPP::Method> methods = this->Class()->Methods();

        for (size_t i = 0; i < methods.size(); i++)
        {
            if (strcmp(methods[i].Name(), name) == 0)
            {
                if (arg_types.size() == methods[i].ParametersCount())
                {
                    std::vector<IL2CPP::Parameter> parameters = methods[i].Parameters();
                    if (parameters.size() == arg_types.size())
                    {
                        for (size_t k = 0; k < arg_types.size(); k++)
                        {
                            bool found = true;
                            if (parameters[k].type->Name() != arg_types[k])
                                found = false;

                            if (found)
                                result = methods[i];
                        }
                    }
                }
            }
        }

        if (result.instance == nullptr)
            LOG_ERROR("Error: couldn't find method " + std::string(name) + " with given parameters.");

        return result;
    }

    // Return field of object instance by the name
    IL2CPP::Field Object::Field(const char *name)
    {
        return IL2CPP::Field(IL2CPP::ExportCall::FieldFromName((void *)this->Class(), name), this);
    }

    /*
    IL2CPP::Parameter implementation
    */

    // Returns parameter in dumped format.
    std::string Parameter::ToString()
    {
        return this->type->Name() + std::string(" ") + this->name;
    }

    /*
    IL2CPP::Method implementation
    */

    template <typename T>
    Method::Method(T handle)
    {
        this->instance = (void *)handle;
        this->object_instance = nullptr;
    }

    template <typename T, typename T2>
    Method::Method(T handle, T2 object)
    {
        this->instance = (void *)handle;
        this->object_instance = (void *)object;
    }

    template <typename T>
    Method::operator T()
    {
        return (T)this->instance;
    }

    // Returns count of methods's parameters.
    uint32_t Method::ParametersCount()
    {
        return IL2CPP::ExportCall::MethodGetParamCount(this->instance);
    }

    // Returns parameters of method.
    std::vector<Parameter> Method::Parameters()
    {
        std::vector<Parameter> result;
        uint32_t parameter_count = this->ParametersCount();

        if (parameter_count == 0)
            return result;

        for (uint32_t i = 0; i < parameter_count; i++)
        {
            Parameter param;

            param.name = IL2CPP::ExportCall::MethodGetParamName(this->instance, i);
            param.type = (IL2CPP::Type *)IL2CPP::ExportCall::MethodGetParamType(this->instance, i);

            result.push_back(param);
        }

        return result;
    }

    // Returns return type of method.
    IL2CPP::Type *Method::ReturnType()
    {
        return (IL2CPP::Type *)IL2CPP::ExportCall::MethodGetReturnType(this->instance);
    }

    // Returns method in dumped format.
    std::string Method::ToString(bool show_offset, bool show_pattern, int pattern_length)
    {
        std::string result;

        if (this->isStatic())
            result += "static ";

        result += std::string(this->ReturnType()->Name()) + " " + this->Name() + "(";

        std::vector<Parameter> parameters = this->Parameters();

        int paramcount = parameters.size();

        int index = 0;
        for (auto it : parameters)
        {
            result += it.ToString();

            if (index++ != paramcount - 1)
                result += ", ";
        }
        result += "); ";
        uint64_t address = this->VA();
        if (show_offset && address)
            result += "// 0x" + BNM::Utils::NumberToHex(this->RVA()) + "; ";

#ifdef PATTERNS
        if (show_pattern && address != 0)
        {
            if (address >= (uint64_t)IL2CPP::Exports::GameAssembly)
            {
                result += "// " + BNM::Utils::Pattern(address, pattern_length).ToString();
            }
        }
#endif

        return result;
    }

    // Attributes of methods.
    enum class Method::Attributes
    {
        MemberAccessMask = 0x0007,
        PrivateScope = 0x0000,
        Private = 0x0001,
        FamilyAndAssembly = 0x0002,
        Assembly = 0x0003,
        Family = 0x0004,
        FamilyOrAssembly = 0x0005,
        Public = 0x0006,
        Static = 0x0010,
        Final = 0x0020,
        Virtual = 0x0040,
        HideBySig = 0x0080,
        CheckAccessOnOverride = 0x0200,
        VtableLayoutMask = 0x0100,
        ReuseSlot = 0x0000,
        NewSlot = 0x0100,
        Abstract = 0x0400,
        SpecialName = 0x0800,
        PinvokeImpl = 0x2000,
        UnmanagedExport = 0x0008,
        RTSpecialName = 0x1000,
        ReservedMask = 0xd000,
        HasSecurity = 0x4000,
        RequireSecObject = 0x8000
    };

    // Returns name of method.
    const char *Method::Name()
    {
        return IL2CPP::ExportCall::MethodGetName(this->instance);
    }

    // Returns VA of method.
    uint64_t Method::VA()
    {
        // hello im from sigma department
        void *SR_Module = IL2CPP::ExportCall::ClassFromName(IL2CPP::ExportCall::AssemblyGetImage(IL2CPP::ExportCall::GetAssemblyFromDomain(IL2CPP::ExportCall::GetDomain(), "mscorlib")), "System.Reflection", "Module");
        IL2CPP::ExportCall::RuntimeClassInit(SR_Module);

        void *FilterTypeName_obj = (void *)IL2CPP::ExportCall::GetStaticFieldValue(IL2CPP::ExportCall::FieldFromName(SR_Module, "FilterTypeName"));
        void *FilterTypeName_klass = IL2CPP::ExportCall::ObjectGetClass(FilterTypeName_obj);

        int method_offset = IL2CPP::ExportCall::FieldGetOffset(IL2CPP::ExportCall::FieldFromName(FilterTypeName_klass, "method"));
        int method_ptr_offset = IL2CPP::ExportCall::FieldGetOffset(IL2CPP::ExportCall::FieldFromName(FilterTypeName_klass, "method_ptr"));

        void *FilterTypeName_method = (void *)((uint64_t)FilterTypeName_obj + method_offset);
        void *FilterTypeName_method_ptr = (void *)((uint64_t)FilterTypeName_obj + method_ptr_offset);

        uint64_t offset = IL2CPP::Offsets::offsetOfMethod((uint64_t)FilterTypeName_method, (uint64_t)FilterTypeName_method_ptr);
        if (offset)
        {
            LOG_ERROR("Error: couldn't find the VA of method " + std::string(this->Name()) + ".");
            return 0;
        }

        uint64_t result = (uint64_t)(*(void **)((uint64_t)offset + (uint64_t)this->instance));
        return result;
    }

    // Returns RVA of method.
    uint64_t Method::RVA()
    {
        return (uint64_t)(this->VA()) - (uint64_t)IL2CPP::Exports::GameAssembly;
    }

    // Checks if method is inflated.
    bool Method::isInflated()
    {
        return IL2CPP::ExportCall::MethodIsInflated(this->instance);
    }

    // Checks if method is static
    bool Method::isStatic()
    {
        return !IL2CPP::ExportCall::MethodIsInstance(this->instance);
    }

    // Returns object of method. @note UNTESTED
    IL2CPP::Object *Method::Object()
    {
        return (IL2CPP::Object *)IL2CPP::ExportCall::MethodGetObject(this->instance, nullptr);
    }

    // Returns generics parameters of method. @note UNTESTED
    std::vector<IL2CPP::Class *> Method::Generics()
    {
        std::vector<IL2CPP::Class *> result;
        if (!this->isInflated())
            return result;
        IL2CPP::Array *arr = this->Object()->Method("GetGenericArguments").Invoke<IL2CPP::Array *>();
        for (size_t i = 0; i < arr->Length(); i++)
        {
            result.push_back(arr->Get<IL2CPP::Object *>(i)->Class());
        }

        return result;
    }

    // Returns generic instance of generic method with given parameters. @note UNTESTED
    IL2CPP::Method Method::Inflate(std::vector<IL2CPP::Class *> classes)
    {
        if (this->Generics().size() != classes.size())
        {
            LOG_ERROR("Error: couldn't inflate method " + std::string(this->Name()) + " - incorrect count of classes.");
        }

        IL2CPP::Array *arr = IL2CPP::Array::New(IL2CPP::Domain().Assembly("mscorlib")->Image()->Class("System.Type"), classes.size());
        for (size_t i = 0; i < arr->Length(); i++)
        {
            arr->Set(0, classes[i]->Type()->Object());
        }

        return IL2CPP::Method(this->Object()->Method("MakeGenericMethod", 1).Invoke<IL2CPP::Object *>(arr)->Field("mhandle").GetValue<void *>());
    }

    // Invokes method with given parameters. @todo Handle the cases with inflated methods.
    template <typename T, typename... Args>
    T Method::Invoke(Args... args)
    {
        if (this->isStatic())
        {

            if (this->object_instance != nullptr)
            {
                LOG_ERROR(std::string("Error: Couldn't invoke static method \"") + this->Name() + std::string("\" from IL2CPP::Object."));
                return (T)0;
            }
            return ((T(*)(Args...))(this->VA()))(args...);
        }
        else
        {
            if (this->object_instance == nullptr)
            {
                LOG_ERROR(std::string("Error: Couldn't invoke non-static method \"") + this->Name() + std::string("\"from IL2CPP::Class instance, use IL2CPP::Object instance instead."));
                return (T)0;
            }
            return ((T(*)(void *, Args...))(this->VA()))(this->object_instance, args...);
        }
    }

    template <typename T>
    Field::Field(T handle)
    {
        this->instance = (void *)handle;
        this->object_instance = nullptr;
    }

    template <typename T, typename T2>
    Field::Field(T handle, T2 object)
    {
        this->instance = (void *)handle;
        this->object_instance = (void *)object;
    }

    template <typename T>
    Field::operator T()
    {
        return (T)this->instance;
    }

    // Attributes of fields.
    enum class Field::Attributes
    {
        FieldAccessMask = 0x0007,
        PrivateScope = 0x0000,
        Private = 0x0001,
        FamilyAndAssembly = 0x0002,
        Assembly = 0x0003,
        Family = 0x0004,
        FamilyOrAssembly = 0x0005,
        Public = 0x0006,
        Static = 0x0010,
        InitOnly = 0x0020,
        Literal = 0x0040,
        NotSerialized = 0x0080,
        SpecialName = 0x0200,
        PinvokeImpl = 0x2000,
        ReservedMask = 0x9500,
        RTSpecialName = 0x0400,
        HasFieldMarshal = 0x1000,
        HasDefault = 0x8000,
        HasFieldRVA = 0x0100
    };

    // Returns flags of field.
    int Field::Flags()
    {
        return IL2CPP::ExportCall::FieldGetFlags(this->instance);
    }

    // Checks if field is static.
    bool Field::isStatic()
    {
        return (this->Flags() & (int)IL2CPP::Field::Attributes::Static) != 0;
    }

    // Checks if field is literal.
    bool Field::isLiteral()
    {
        return (this->Flags() & (int)IL2CPP::Field::Attributes::Literal) != 0;
    }

    // Returns offset of field.
    int Field::Offset()
    {
        return IL2CPP::ExportCall::FieldGetOffset(this->instance);
    }

    // Returns value of field.
    template <typename T>
    T Field::GetValue()
    {
        if (this->isStatic())
        {
            if (this->object_instance != nullptr)
            {
                LOG_ERROR("Error: Trying getting static field " + std::string(this->Name()) + " of IL2CPP::Object instance, use IL2CPP::Class instead.");
                return T(0);
            }
            return (T)(IL2CPP::ExportCall::GetStaticFieldValue(this->instance));
        }
        else
        {
            if (this->object_instance == nullptr)
            {
                LOG_ERROR("Error: Trying getting non-static field " + std::string(this->Name()) + " of IL2CPP::Class instance, use IL2CPP::Object instead.");
            }
            return *(T *)((uint64_t)this->object_instance + (uint64_t)this->Offset());
        }
    }

    // Sets value of field.
    template <typename T>
    void Field::SetValue(T value)
    {
        if (this->isStatic())
        {
            if (this->object_instance != nullptr)
            {
                LOG_ERROR("Error: Trying setting static field " + std::string(this->Name()) + " of IL2CPP::Object instance, use IL2CPP::Class instead.");
                return;
            }
            IL2CPP::ExportCall::FieldStaticSetValue(this->instance, (void *)value);
            return;
        }
        else
        {
            if (this->object_instance == nullptr)
            {
                LOG_ERROR("Error: Trying setting non-static field " + std::string(this->Name()) + " of IL2CPP::Class instance, use IL2CPP::Object instead.");
                return;
            }
            *(T *)((uint64_t)this->object_instance + (uint64_t)this->Offset()) = value;
            return;
        }
    }

    // Returns name of field.
    const char *Field::Name()
    {
        return IL2CPP::ExportCall::FieldGetName(this->instance);
    }

    // Returns type of field.
    IL2CPP::Type *Field::Type()
    {
        return (IL2CPP::Type *)IL2CPP::ExportCall::FieldGetType(this->instance);
    }

    // Returns field in dumped format.
    std::string Field::ToString(bool show_offset)
    {
        std::string result;
        if (this->isStatic())
            result += "static ";

        result += std::string(this->Type()->Name()) + " " + std::string(this->Name()) + ";";

        if (show_offset)
            result += " // 0x" + BNM::Utils::NumberToHex(this->Offset()) + "; ";

        return result;
    }

    // Returns field in dumped format. @param val if you know value of field use it.
    std::string Field::ToString(std::string val, bool show_offset)
    {
        std::string result;

        if (this->isStatic())
            result += "static ";

        result += std::string(this->Type()->Name()) + " " + this->Name();
        result += " = " + val;

        if (show_offset)
            result += "// 0x" + BNM::Utils::NumberToHex(this->Offset()) + "; ";
        return result;
    }

    /*
    IL2CPP::Array definition
    */

    // Creates new instance of array.
    IL2CPP::Array *Array::New(IL2CPP::Class *klass, int length)
    {
        return (IL2CPP::Array *)IL2CPP::ExportCall::ArrayNew((void *)klass, length);
    }

    // Returns length of array.
    int Array::Length()
    {
        return IL2CPP::ExportCall::ArrayLength((void *)this);
    }

    // Returns object of array.
    IL2CPP::Object *Array::Object()
    {
        return (IL2CPP::Object *)this;
    }

    // Returns type of array.
    IL2CPP::Type *Array::ElementType()
    {
        return this->Object()->Class()->Type()->Class()->BaseType();
    }

    // Returns size of element.
    int Array::ElementSize()
    {
        return ((IL2CPP::Class *)(this->ElementType()))->ElementSize();
    }

    // Returns array of elements.
    template <typename T>
    T *Array::Elements()
    {
        IL2CPP::Object *str = (IL2CPP::Object *)IL2CPP::String::New("v");
        IL2CPP::Object *charArray = str->Method("ToCharArray", 0).Invoke<IL2CPP::Object *>();
        uint64_t offset = IL2CPP::Offsets::offsetOfCharArray((void *)charArray, 118);
        uint64_t addr = (uint64_t)this + offset;
        return (T *)addr;
    }

    // Returns value by index.
    template <typename T>
    T Array::Get(int index)
    {
        return this->Elements<T>()[index];
    }

    // Sets value by index.
    template <typename T>
    void Array::Set(int index, T value)
    {
        this->Elements<T>()[index] = value;
    }

    /*
   IL2CPP::String definition
   */

    // Creates new string instance.
    IL2CPP::String *String::New(const char *content)
    {
        return (IL2CPP::String *)IL2CPP::ExportCall::StringNew(content);
    }

    // Returns length of string.
    int String::Length()
    {
        return IL2CPP::ExportCall::StringLength((void *)this);
    }

    // Returns data of string.
    std::string String::Content()
    {
        if ((void *)this == nullptr)
            return std::string("null");
        int length = this->Length();
        std::string content(static_cast<size_t>(length) * 3 + 1, '\0');
        WideCharToMultiByte(CP_UTF8, 0, IL2CPP::ExportCall::StringChars((void *)this), length, &content[0], static_cast<int>(content.size()), 0, 0);

        std::vector<char> bytes(content.begin(), content.end());
        bytes.push_back('\0');

        std::list<char> chars;

        for (byte byte : bytes)
        {
            if (byte)
            {
                chars.push_back(byte);
            }
        }

        std::string clean(chars.begin(), chars.end());

        return clean;
    }
}