#include "../include/method.h"
#include "../include/exportcall.h"
#include "../include/defines.h"
#include "../include/domain.h"
#include "../include/type.h"
#include "../include/array.h"

static uintptr_t MethodOffset = 0;
static uintptr_t GetMethodOffset(uintptr_t MethodInfoPtr, uintptr_t MethodPtr)
{
    if (MethodOffset == 0)
    {
        int depth = 512;
        for (int i = 0; i < depth; i++)
        {
            if (*(void **)(MethodInfoPtr + i) == *(void **)(MethodPtr))
            {
                MethodOffset = i;
                return i;
            }
        }

        return 0;
    }
    else
    {
        return MethodOffset;
    }
}

namespace IL2CPP
{
    Method::Method(uintptr_t Handle, uintptr_t ParentInstance)
    {
        this->Handle = Handle;
        this->ParentInstance = ParentInstance;
    }

    const char *Method::Name()
    {
        return IL2CPP::ExportCall::MethodGetName((void *)this->Handle);
    }

    bool Method::isInflated()
    {
        return IL2CPP::ExportCall::MethodIsInflated((void *)this->Handle);
    }

    bool Method::isStatic()
    {
        return !IL2CPP::ExportCall::MethodIsInstance((void *)this->Handle);
    }

    IL2CPP::Object *Method::Object()
    {
        return (IL2CPP::Object *)IL2CPP::ExportCall::MethodGetObject((void *)this->Handle, nullptr);
    }

    IL2CPP::Type *Method::ReturnType()
    {
        return (IL2CPP::Type *)IL2CPP::ExportCall::MethodGetReturnType(this->Handle);
    }

    uintptr_t Method::VA()
    {
        IL2CPP::Class *SR_Module = IL2CPP::Domain::Assembly("mscorlib")->Image()->Class("System.Reflection", "Module");
        IL2CPP::ExportCall::RuntimeClassInit((void *)SR_Module);
        IL2CPP::Object *FilterTypeName_object = SR_Module->Field("FilterTypeName").GetValue<IL2CPP::Object *>();

        uintptr_t FilterTypeName_method = (uintptr_t)FilterTypeName_object + FilterTypeName_object->Class()->Field("method").Offset();
        uintptr_t FilterTypeName_method_ptr = (uintptr_t)FilterTypeName_object + FilterTypeName_object->Class()->Field("method_ptr").Offset();

        uintptr_t offset = GetMethodOffset(FilterTypeName_method, FilterTypeName_method_ptr);
        uintptr_t result = (uintptr_t)(*(void **)((uintptr_t)offset + (uintptr_t)this->Handle));

        return result;
    }

    uint32_t Method::ParametersCount()
    {
        return IL2CPP::ExportCall::MethodGetParamCount((void *)this->Handle);
    }

    std::vector<Parameter> Method::Parameters()
    {
        std::vector<Parameter> result;
        uint32_t parameter_count = this->ParametersCount();

        if (parameter_count == 0)
            return result;

        for (uint32_t i = 0; i < parameter_count; i++)
        {
            Parameter param;

            param.Name = IL2CPP::ExportCall::MethodGetParamName((void *)this->Handle, i);
            param.Type = (IL2CPP::Type *)IL2CPP::ExportCall::MethodGetParamType((void *)this->Handle, i);

            result.push_back(param);
        }

        return result;
    }

    uintptr_t Method::RVA()
    {
        return (uintptr_t)(this->VA()) - (uintptr_t)IL2CPP::Exports::GameAssembly;
    }

    std::string Method::ToString(const DumperParameters &Parameters, int Index = -1)
    {
        std::string result;

        if (Parameters.ShowIndexes)
            result += std::format("[{}] ", Index);

        if (this->isStatic())
            result += "static ";

        result += std::string(this->ReturnType()->Name()) + " " + this->Name() + "(";

        std::vector<Parameter> parameters = this->Parameters();

        size_t parameters_count = parameters.size();

        for (size_t i = 0; i < parameters_count; i++)
        {
            result += std::format("{} {}", parameters[i].Type->Name(), parameters[i].Name);

            if (i != parameters_count - 1)
                result += ", ";
        }

        result += std::format("); // 0x{:x}", this->RVA());

        return result;
    }

    IL2CPP::Method Method::Inflate(std::vector<IL2CPP::Class *> Classes)
    {
        IL2CPP::Array *types = IL2CPP::Array::New(IL2CPP::Domain::Assembly("mscorlib")->Image()->Class("System.Type"), Classes.size());

        for (size_t i = 0; i < Classes.size(); i++)
        {
            types->Set(i, Classes[i]->Type()->Object());
        }

        return IL2CPP::Method(this->Object()->Method("MakeGenericMethod", 1).Invoke<IL2CPP::Object *>(types)->Field("mhandle").GetValue<uintptr_t>());
    }
}