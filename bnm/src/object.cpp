#include "../include/object.h"
#include "../include/exportcall.h"
#include "../include/defines.h"

namespace IL2CPP
{
    IL2CPP::Class *Object::Class()
    {
        return (IL2CPP::Class *)IL2CPP::ExportCall::ObjectGetClass((void *)this);
    }

    IL2CPP::Object *Object::New(IL2CPP::Class *Class)
    {
        return (IL2CPP::Object *)IL2CPP::ExportCall::ObjectNew((void *)Class);
    }

    IL2CPP::Method Object::Method(const char *Name, int ArgCount)
    {
        return IL2CPP::Method(IL2CPP::ExportCall::MethodFromName((void *)this->Class(), Name, ArgCount), (uintptr_t)this);
    }

    IL2CPP::Method Object::Method(const char *Name, std::vector<std::string> ArgTypes)
    {
        IL2CPP::Method result(0, this);
        std::vector<IL2CPP::Method> methods = this->Class()->Methods();

        for (size_t i = 0; i < methods.size(); i++)
        {
            if (strcmp(methods[i].Name(), Name) == 0)
            {
                if (ArgTypes.size() == methods[i].ParametersCount())
                {
                    std::vector<IL2CPP::Parameter> parameters = methods[i].Parameters();
                    if (parameters.size() == ArgTypes.size())
                    {
                        for (size_t k = 0; k < ArgTypes.size(); k++)
                        {
                            bool found = true;
                            if (parameters[k].Type->Name() != ArgTypes[k])
                                found = false;

                            if (found)
                                result.Handle = methods[i].Handle;
                        }
                    }
                }
            }
        }

        if (result.Handle == 0)
            LOG(std::format("Couldn't find method \"{}\" in \"{}\" with setted parameters.", Name, this->Class()->Fullname()));

        return result;
    }

    IL2CPP::Field Object::Field(const char *Name)
    {
        return IL2CPP::Field(IL2CPP::ExportCall::FieldFromName((void *)this->Class(), Name), (uintptr_t)this);
    }
}