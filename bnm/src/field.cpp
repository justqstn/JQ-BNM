#include "../include/field.h"
#include "../include/type.h"
#include "../include/exportcall.h"
#include <string>

namespace IL2CPP
{
    Field::Field(uintptr_t Handle, uintptr_t ParentInstance)
    {
        this->Handle = Handle;
        this->ParentInstance = ParentInstance;
    }

    const char *Field::Name()
    {
        return IL2CPP::ExportCall::FieldGetName((void *)this->Handle);
    }

    IL2CPP::Type *Field::Type()
    {
        return (IL2CPP::Type *)IL2CPP::ExportCall::FieldGetType((void *)this->Handle);
    }

    int Field::Flags()
    {
        return IL2CPP::ExportCall::FieldGetFlags((void *)this->Handle);
    }

    bool Field::isStatic()
    {
        return (this->Flags() & (int)IL2CPP::Field::Attributes::Static) != 0;
    }

    bool Field::isLiteral()
    {
        return (this->Flags() & (int)IL2CPP::Field::Attributes::Literal) != 0;
    }

    int Field::Offset()
    {
        return IL2CPP::ExportCall::FieldGetOffset((void *)this->Handle);
    }

    std::string Field::ToString(const DumperParameters &Parameters, int Index, const std::string &FieldValue)
    {
        return std::format("{}{}{} {}{}; // 0x{:x}",
                           Parameters.ShowIndexes ? std::format("[{}] ", Index) : "",
                           this->isStatic() ? "static " : "",
                           this->Type()->Name(),
                           this->Name(),
                           FieldValue != "" ? " = " + FieldValue : "",
                           this->Offset());
    }
}