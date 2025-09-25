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
        // @return Class name
        const char *Name();
        // Allocates nwe class instance @return Pointer to object
        IL2CPP::Object *New();
        // Gets method by name and arguments count  @return Method
        IL2CPP::Method Method(const char *Name, int ArgCount = -1);
        // Gets method by name and arguments names  @return Method
        IL2CPP::Method Method(const char *Name, std::vector<std::string> ArgTypes);
        // Gets method by IndexOffset  @return Method
        IL2CPP::Method MethodByIO(const char *Method, int Offset);
        // Gets field by name @return Field
        IL2CPP::Field Field(const char *Name);
        // Gets field by IndexOffset  @return Field
        IL2CPP::Field FieldByIO(const char *Field, int Offset);
        // @return Class size
        int ElementSize();
        // @return Class type
        IL2CPP::Type *Type();
        // @return Class base type
        IL2CPP::Type *BaseType();
        // @return Class reflection type
        IL2CPP::Type *ReflectionType();
        // Checks is it enum
        bool isEnum();
        // Checks is it interface
        bool isInterface();
        // Checks is it ValueType
        bool isValueType();
        // Checks is it struct
        bool isStruct();
        // @return Vector of interfaces
        std::vector<IL2CPP::Class *> Interfaces();
        // @return Vector of nested classes
        std::vector<IL2CPP::Class *> NestedClasses();
        // @return Vector of methods
        std::vector<IL2CPP::Method> Methods();
        // @return Vector of fields
        std::vector<IL2CPP::Field> Fields();
        // @return Class namespace
        const char *Namespace();
        // @return Class namespace + name (namespace::name)
        const char *Fullname();
        // @return Nested class by name
        IL2CPP::Class *Nested(const char *Name);
        // Creates generic instance by given types @return Pointer to generic class
        IL2CPP::Class *Inflate(std::vector<IL2CPP::Class *> Types);
        std::string ToString(const DumperParameters &Parameters = {}, int Index = -1);

        // Boxes primitive value and wrap it into IL2CPP::Object* @return Pointer to object
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