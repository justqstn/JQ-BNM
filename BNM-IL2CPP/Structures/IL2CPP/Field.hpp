#pragma once

#include "../../Defines.hpp"
#include "../../ExportCall.hpp"

namespace IL2CPP
{
    struct Field
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

        // erm what the sigma
        int Flags()
        {
            return IL2CPP::ExportCall::FieldGetFlags((void *)this);
        }
        bool isStatic()
        {
            return (this->Flags() & (int)IL2CPP::Field::Attributes::Static) != 0;
        }

        int Offset()
        {
            return IL2CPP::ExportCall::FieldGetOffset((void *)this);
        }

        template <typename T>
        // Returns value of  field. If field is non-static you need to pass instance parameter
        T GetValue(void *instance = nullptr)
        {
            if (this->isStatic())
            {
                if (instance == nullptr)
                {
                    return (T)IL2CPP::ExportCall::GetStaticFieldValue((void *)this);
                }
                else
                {
                    LOG_ERROR("Error: trying getting static field " + std::string(this->Name()) + " of instance, returning nullptr.");
                    return NULL;
                }
            }
            else if (instance == nullptr)
            {
                LOG_ERROR("Error: trying getting non-static field " + std::string(this->Name()) + " without instance, returning nullptr.");
                return nullptr;
            }
            else
            {
                return *(T *)((uint64_t)instance + (uint64_t)this->Offset());
            }
        }

        template <typename T>
        // Sets value of field. If field non-static you need to pass instance parameter
        void SetValue(T value, void *instance = nullptr)
        {
            if (this->isStatic())
            {
                if (instance == nullptr)
                {
                    (T) IL2CPP::ExportCall::FieldStaticSetValue((void *)this, (void *)value);
                    return;
                }
                else
                {
                    LOG_ERROR("Error: trying setting static field " + std::string(this->Name()) + " of instancer.");
                    return;
                }
            }
            else if (instance == nullptr)
            {
                LOG_ERROR("Error: trying setting non-static field " + std::string(this->Name()) + " without instance.");
                return;
            }
            else
            {
                *(T *)((uint64_t)instance + (uint64_t)this->Offset()) = value;
                return;
            }
        }

        const char *Name()
        {
            return IL2CPP::ExportCall::FieldGetName((void *)this);
        }
    };
}