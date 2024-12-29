#pragma once

#include "../../ExportCall.hpp"
#include "../../Offsets.hpp"
#include "Type.hpp"
#include <initializer_list>
#include <any>
#include <string>
#include "../../Utils/Other.hpp"
#include "../../Utils/MemPattern.hpp"

namespace IL2CPP
{
    struct Type;
    struct Parameter
    {
        IL2CPP::Type *type;
        const char *name;

        std::string ToString()
        {
            return this->type->Name() + std::string(" ") + this->name;
        }
    };

    class Method
    {
    public:
        template <typename T>
        Method(T handle)
        {
            this->instance = (void *)handle;
            this->object_instance = nullptr;
        }

        template <typename T, typename T2>
        Method(T handle, T2 object)
        {
            this->instance = (void *)handle;
            this->object_instance = (void *)object;
        }

        template <typename T>
        operator T()
        {
            return (T)this->instance;
        }

        void SetObjectInstance(void *instance)
        {
            this->object_instance = instance;
        }

        uint32_t ParametersCount()
        {
            return IL2CPP::ExportCall::MethodGetParamCount(this->instance);
        }

        std::vector<Parameter> Parameters()
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

        IL2CPP::Type *ReturnType()
        {
            return (IL2CPP::Type *)IL2CPP::ExportCall::MethodGetReturnType(this->instance);
        }

        std::string ToString(bool show_offset = true, bool show_pattern = false, int pattern_length = 16)
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

            if (show_offset)
                result += "// 0x" + BNM::Utils::ToHex(this->RVA()) + "; ";

            if (show_pattern)
                result += "// " + BNM::Utils::BytesToPattern(BNM::Utils::BytesFromAddress((uint64_t)this->instance, pattern_length));
            return result;
        }

        enum class Attributes
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

        const char *Name()
        {
            return IL2CPP::ExportCall::MethodGetName(this->instance);
        }

        // Returns Value Address of method - it's RVA (offset)+maindll address.
        uint64_t VA()
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
                LOG_ERROR("Couldn't find the VA of method " + std::string(this->Name()) + "(). You can try increase \"depth\" value in IL2CPPResolver2.0/Structures/IL2CPP/Method.hpp/Method::offsetOf or kys.");
                return 0;
            }

            uint64_t result = (uint64_t)(*(void **)((uint64_t)offset + (uint64_t)this->instance));
            return result;
        }

        // Returns Relative Value Address of method - it's VA-maindll address.
        uint64_t RVA()
        {
            return (uint64_t)(this->VA()) - (uint64_t)IL2CPP::Exports::GameAssembly;
        }

        bool isInflated()
        {
            return IL2CPP::ExportCall::MethodIsInflated(this->instance);
        }

        bool isStatic()
        {
            return !IL2CPP::ExportCall::MethodIsInstance(this->instance);
        }

        template <typename T, typename... Args>
        T Invoke(Args... args)
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

        void *instance;
        void *object_instance;
    };
}