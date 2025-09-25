#pragma once

#include <cstdint>
#include <format>
#include "type.h"
#include "exportcall.h"
#include "dumper.h"

namespace IL2CPP
{

    class Field
    {
    public:
        enum class Attributes
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

        Field(uintptr_t Handle, uintptr_t ParentInstance = 0);

        const char *Name();
        IL2CPP::Type *Type();
        int Flags();
        bool isStatic();
        bool isLiteral();
        int Offset();
        std::string ToString(const DumperParameters &Parameters = {}, int Index = -1, const std::string &FieldValue = "");

        template <typename T>
        T GetValue()
        {
            if (this->isStatic())
            {
                if (this->ParentInstance != 0)
                {
                    LOG(std::format("Trying getting static field \"{}\" of IL2CPP::Object instance, use IL2CPP::Class instead.", this->Name()));
                    return T(0);
                }
                return (T)(IL2CPP::ExportCall::GetStaticFieldValue((void *)this->Handle));
            }
            else
            {
                if (this->ParentInstance == 0)
                {
                    LOG(std::format("Trying getting static field \"{}\" of IL2CPP::Class instance, use IL2CPP::Object instead.", this->Name()));
                }
                return *(T *)((uintptr_t)this->ParentInstance + (uintptr_t)this->Offset());
            }
        }

        template <typename T>
        void SetValue(T value)
        {
            if (this->isStatic())
            {
                if (this->ParentInstance != 0)
                {
                    LOG(std::format("Trying setting static field \"{}\" of IL2CPP::Object instance, use IL2CPP::Class instead.", this->Name()));
                    return;
                }
                IL2CPP::ExportCall::SetStaticFieldValue((void *)this->Handle, (void *)value);
                return;
            }
            else
            {
                if (this->ParentInstance == 0)
                {
                    LOG(std::format("Trying setting static field \"{}\" of IL2CPP::Class instance, use IL2CPP::Object instead.", this->Name()));
                    return;
                }
                *(T *)((uintptr_t)this->ParentInstance + (uintptr_t)this->Offset()) = value;
                return;
            }
        }

        uintptr_t Handle;
        uintptr_t ParentInstance;
    };
}