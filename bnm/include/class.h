#pragma once
#include <vector>
#include <string>
#include <format>

#include "object.h"
#include "method.h"
#include "field.h"
#include "domain.h"
#include "defines.h"

namespace IL2CPP
{
    class Method;
    class Field;
    struct Type;
    struct Object;
    struct Class
    {
        const char *Name();
        IL2CPP::Object *New();
        IL2CPP::Method Method(const char *Name, int ArgCount = -1);
        IL2CPP::Method Method(const char *Name, std::vector<std::string> ArgTypes);
        IL2CPP::Field Field(const char *Name);
        int ElementSize();
        IL2CPP::Type *Type();
        IL2CPP::Type *BaseType();
        IL2CPP::Type *ReflectionType();
        bool isEnum();
        bool isInterface();
        bool isValueType();
        bool isStruct();
        std::vector<IL2CPP::Class *> Interfaces();
        std::vector<IL2CPP::Class *> NestedClasses();
        std::vector<IL2CPP::Method> Methods();
        std::vector<IL2CPP::Field> Fields();
        const char *Namespace();
        const char *Fullname();
        IL2CPP::Class *Nested(const char *Name);
        IL2CPP::Class *Inflate(std::vector<IL2CPP::Class *> Types);
        std::string ToString(const DumperParameters &Parameters = {}, int Index = -1);
        template <typename T>
        IL2CPP::Object *Box(T Value)
        {
            IL2CPP::Object *result = this->New();
            IL2CPP::Field value = result->Field("m_value");
            if (value.Handle == 0)
            {
                value = result->Field("__pointer");
                if (value.Handle == 0)
                {
                    LOG(std::format("Couldn't box {}, seems like it's not a primitive!", this->Fullname()));
                    return nullptr;
                }
            }

            value.SetValue(Value);

            return result;
        }
    };
}