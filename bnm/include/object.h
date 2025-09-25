#pragma once

#include <format>

#include "defines.h"
#include "class.h"
#include "domain.h"

namespace IL2CPP
{
    class Method;
    class Field;
    struct Type;
    struct Class;
    struct Object
    {
        IL2CPP::Class *Class();
        IL2CPP::Object *New(IL2CPP::Class *Class);
        IL2CPP::Method Method(const char *Name, int ArgCount = -1);
        IL2CPP::Method Method(const char *Name, std::vector<std::string> ArgTypes);
        IL2CPP::Method MethodByIO(const char *Method, int Offset);
        IL2CPP::Field Field(const char *Name);
        IL2CPP::Field FieldByIO(const char *Field, int Offset);
        template <typename T>
        static IL2CPP::Object *Box(const char *PrimitiveType, const T &Value)
        {
            IL2CPP::Class *primitive_class = IL2CPP::Domain::Assembly("mscorlib")->Image()->Class(PrimitiveType);
            IL2CPP::Object *result = primitive_class->New();
            IL2CPP::Field value = result->Field("m_value");
            if (value.Handle == 0)
            {
                value = result->Field("__pointer");
                if (value.Handle == 0)
                {
                    LOG(std::format("Couldn't box {}, seems like it's not a primitive!", primitive_class->Fullname()));
                    return nullptr;
                }
            }

            value.SetValue(Value);

            return result;
        }
    };
}