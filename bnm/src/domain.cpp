#include <cstdint>

#include "../include/domain.h"
#include "../include/assembly.h"
#include "../include/exportcall.h"
#include "../include/defines.h"
#include "../include/array.h"

namespace IL2CPP
{
    namespace Domain
    {
        uintptr_t Get()
        {
            return IL2CPP::ExportCall::DomainGet();
        }

        std::vector<IL2CPP::Assembly *> Assemblies()
        {
            std::vector<IL2CPP::Assembly *> result;

            IL2CPP::Array *assebmlies = Assembly("mscorlib")->Image()->Class("System.AppDomain")->Method("get_CurrentDomain").Invoke<IL2CPP::Object *>()->Method("GetAssemblies", 0).Invoke<IL2CPP::Array *>();
            for (size_t i = 0; i < assebmlies->Length(); i++)
            {
                result.push_back(assebmlies->Get<IL2CPP::Object *>(i)->Field("_mono_assembly").GetValue<IL2CPP::Assembly *>());
            }

            return result;
        }

        IL2CPP::Assembly *Assembly(const char *Name)
        {
            return IL2CPP::ExportCall::AssemblyGetFromDomain(IL2CPP::ExportCall::DomainGet(), Name);
        }
    }
}