#pragma once

#include "../../Defines.hpp"
#include "../../ExportCall.hpp"

namespace IL2CPP
{
    class Field
    {
    public:
        Field(void *address, void *_instance = nullptr)
        {
            this->handle = address;
            this->instance = _instance;
        }

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
            return IL2CPP::ExportCall::FieldGetFlags(this->handle);
        }
        bool isStatic()
        {
            return (this->Flags() & (int)IL2CPP::Field::Attributes::Static) != 0;
        }

        int Offset()
        {
            return IL2CPP::ExportCall::FieldGetOffset(this->handle);
        }

        void *Address()
        {
            return this->handle;
        }

        template <typename T>
        // Returns value of static field. After getting value cast it to needed type. If field non-static you'll get nullptr;
        T Value()
        {
            if (this->isStatic())
            {
                if (this->instance == nullptr)
                {
                    return (T)IL2CPP::ExportCall::GetStaticFieldValue(this->handle);
                }
                else
                {
                    LOG_ERROR("Error: trying getting static field " + std::string(this->Name()) + " of instance, returning nullptr.");
                    return NULL;
                }
            }
            else
            {
                return *(T *)((uint64_t)this->instance + (uint64_t)this->Offset());
            }
        }

        const char *Name()
        {
            return IL2CPP::ExportCall::FieldGetName(this->handle);
        }

    private:
        void *handle;
        void *instance;
    };
}