#pragma once

#include <cstdint>
#include <Windows.h>

namespace IL2CPP
{
    namespace Exports
    {
        extern HMODULE GameAssembly;
        extern uintptr_t GetAllAssemblies;
        extern uintptr_t AssemblyGetFromDomain;
        extern uintptr_t DomainGet;
        extern uintptr_t AssemblyGetImage;
        extern uintptr_t ImageGetName;
        extern uintptr_t ImageGetClass;
        extern uintptr_t ImageGetClassCount;
        extern uintptr_t ClassFromName;
        extern uintptr_t ObjectNew;
        extern uintptr_t ClassGetName;
        extern uintptr_t ObjectGetClass;
        extern uintptr_t ClassIsInterface;
        extern uintptr_t ClassIsEnum;
        extern uintptr_t ClassIsInflated;
        extern uintptr_t ClassIsValueType;
        extern uintptr_t ClassGetNamespace;
        extern uintptr_t MethodFromName;
        extern uintptr_t FieldFromName;
        extern uintptr_t ClassGetMethods;
        extern uintptr_t ClassGetFields;
        extern uintptr_t ClassArrayElementSize;
        extern uintptr_t TypeFromClass;
        extern uintptr_t ClassEnumBasetype;
        extern uintptr_t TypeGetObject;
        extern uintptr_t MethodGetName;
        extern uintptr_t MethodGetFlags;
        extern uintptr_t MethodIsInstance;
        extern uintptr_t MethodIsInflated;
        extern uintptr_t MethodGetObject;
        extern uintptr_t FieldGetName;
        extern uintptr_t FieldGetOffset;
        extern uintptr_t FieldGetFlags;
        extern uintptr_t FieldGetType;
        extern uintptr_t ClassFromType;
        extern uintptr_t TypeGetName;
        extern uintptr_t RuntimeClassInit;
        extern uintptr_t GetStaticFieldValue;
        extern uintptr_t SetStaticFieldValue;
        extern uintptr_t ThreadAttach;
        extern uintptr_t ClassGetInterfaces;
        extern uintptr_t MethodGetParamCount;
        extern uintptr_t MethodGetParamType;
        extern uintptr_t MethodGetParamName;
        extern uintptr_t ClassNestedClasses;
        extern uintptr_t StringNew;
        extern uintptr_t StringLength;
        extern uintptr_t StringChars;
        extern uintptr_t ArrayNew;
        extern uintptr_t ArrayLength;
        extern uintptr_t ClassFromSystemType;
        extern uintptr_t MethodGetReturnType;
        extern uintptr_t ObjectValueBox;
        extern uintptr_t ClassGetInstanceSize;
    }
}