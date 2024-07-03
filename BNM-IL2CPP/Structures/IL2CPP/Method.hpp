#pragma once

#include "../../ExportCall.hpp"

namespace IL2CPP
{
    struct Method
    {
    public:
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
            return IL2CPP::ExportCall::MethodGetName((void *)this);
        }

        // Returns Virtual Address of method - it's RVA (offset)+maindll address.
        uint64_t VA()
        {
            // hello im from sigma department
            void *SR_Module = IL2CPP::ExportCall::ClassFromName(IL2CPP::ExportCall::AssemblyGetImage(IL2CPP::ExportCall::GetAssemblyFromDomain(IL2CPP::ExportCall::GetDomain(), "mscorlib")), "System.Reflection", "Module");
            IL2CPP::ExportCall::RuntimeClassInit(SR_Module);
            void *FilterTypeName_obj = IL2CPP::ExportCall::GetStaticFieldValue(IL2CPP::ExportCall::FieldFromName(SR_Module, "FilterTypeName"));
            void *FilterTypeName_klass = IL2CPP::ExportCall::ObjectGetClass(FilterTypeName_obj);
            int method_offset = IL2CPP::ExportCall::FieldGetOffset(IL2CPP::ExportCall::FieldFromName(FilterTypeName_klass, "method"));
            int method_ptr_offset = IL2CPP::ExportCall::FieldGetOffset(IL2CPP::ExportCall::FieldFromName(FilterTypeName_klass, "method_ptr"));
            void *FilterTypeName_method = (void *)((uint64_t)FilterTypeName_obj + method_offset);
            void *FilterTypeName_method_ptr = (void *)((uint64_t)FilterTypeName_obj + method_ptr_offset);

            uint64_t offset = Method::offsetOf((uint64_t)FilterTypeName_method, (uint64_t)FilterTypeName_method_ptr);
            if (offset)
            {
                LOG_ERROR("Couldn't find the VA of method " + std::string(this->Name()) + "(). You can try increase \"depth\" value in IL2CPPResolver2.0/Structures/IL2CPP/Method.hpp/Method::offsetOf or kys.");
                return 0;
            }
            uint64_t result = (uint64_t)(*(void **)((uint64_t)offset + (uint64_t)this));
            return result;
        }

        // Returns Relative Virtual Address of method - it's VA-maindll address.
        uint64_t RVA()
        {
            return (uint64_t)(this->VA()) - (uint64_t)IL2CPP::Exports::GameAssembly;
        }

    private:
        static uint64_t offsetOf(uint64_t start_ptr, uint64_t equal_ptr)
        {
            int depth = 512;
            for (int i = 0; i < depth; i++)
            {
                if (*(void **)(start_ptr + i) == *(void **)(equal_ptr))
                {
                    return i;
                }
            }

            return 0;
        }
    };
}