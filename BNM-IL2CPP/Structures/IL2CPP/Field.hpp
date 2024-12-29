#pragma once

#include "../../Defines.hpp"
#include "../../ExportCall.hpp"
#include "Type.hpp"

namespace IL2CPP
{
    struct Type;
    class Field
    {
    public:
        template <typename T>
        Field(T handle)
        {
            this->instance = (void *)handle;
            this->object_instance = nullptr;
        }

        template <typename T, typename T2>
        Field(T handle, T2 object)
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
            return IL2CPP::ExportCall::FieldGetFlags(this->instance);
        }
        bool isStatic()
        {
            return (this->Flags() & (int)IL2CPP::Field::Attributes::Static) != 0;
        }

        bool isLiteral()
        {
            return (this->Flags() & (int)IL2CPP::Field::Attributes::Static) != 0;
        }

        int Offset()
        {
            return IL2CPP::ExportCall::FieldGetOffset(this->instance);
        }

        template <typename T>
        // Returns value of  field. If field is non-static you need to pass instance parameter
        T GetValue()
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

        template <typename T>
        // Sets value of field. If field non-static you need to pass instance parameter
        void SetValue(T value)
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

        const char *Name()
        {
            return IL2CPP::ExportCall::FieldGetName(this->instance);
        }

        IL2CPP::Type *Type()
        {
            return (IL2CPP::Type *)IL2CPP::ExportCall::FieldGetType(this->instance);
        }

        std::string ToString(bool show_offset = true, bool show_pattern = false, int pattern_length = 16)
        {
            std::string result;
            if (this->isStatic())
                result += "static ";

            result += std::string(this->Type()->Name()) + " " + this->Name();

            if (show_offset)
                result += "// 0x" + BNM::Utils::ToHex(this->Offset()) + "; ";

            if (show_pattern)
                result += "// " + BNM::Utils::BytesToPattern(BNM::Utils::BytesFromAddress((uint64_t)this->instance, pattern_length));

            return result;
        }

        std::string ToString(std::string val, bool show_offset = true, bool show_pattern = false, int pattern_length = 16)
        {
            std::string result;

            if (this->isStatic())
                result += "static ";

            result += std::string(this->Type()->Name()) + " " + this->Name();
            result += " = " + val;

            if (show_offset)
                result += "// 0x" + BNM::Utils::ToHex(this->Offset()) + "; ";

            if (show_pattern)
                result += "// " + BNM::Utils::BytesToPattern(BNM::Utils::BytesFromAddress((uint64_t)this->instance, pattern_length));

            return result;
        }

    private:
        void *instance;
        void *object_instance;
    };
}