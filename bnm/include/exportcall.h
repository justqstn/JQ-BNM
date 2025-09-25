#pragma once

#include <format>

#include "../include/exports.h"
#include "../include/defines.h"

#define DEBUG_EXPORTS
#ifdef DEBUG_EXPORTS
#define CHECK_IS_NULL_EXPORT(Name, Export)                 \
    if (Export == 0)                                       \
    {                                                      \
        LOG(std::format("Export \"{}\" is null. ", Name)); \
    }
#else
#define CHECK_IS_NULL_EXPORT(Name, Export)
#endif

namespace IL2CPP
{
    namespace ExportCall
    {
        inline void *DomainGet()
        {
            CHECK_IS_NULL_EXPORT("DomainGet", Exports::DomainGet);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)()>(Exports::DomainGet)();
        }

        inline void *AssemblyGetFromDomain(void *Handle, const char *Name)
        {
            CHECK_IS_NULL_EXPORT("AssemblyGetFromDomain", Exports::AssemblyGetFromDomain);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *)>(Exports::AssemblyGetFromDomain)(Handle, Name);
        }

        inline void *AssemblyGetImage(void *Handle)
        {
            CHECK_IS_NULL_EXPORT("AssemblyGetImage", Exports::AssemblyGetImage);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::AssemblyGetImage)(Handle);
        }

        inline void *GetAllAssemblies(void *Domain, void **Iterator)
        {
            CHECK_IS_NULL_EXPORT("GetAllAssemblies", Exports::GetAllAssemblies);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void **)>(Exports::GetAllAssemblies)(Domain, Iterator);
        }

        inline const char *ImageGetName(void *Handle)
        {
            CHECK_IS_NULL_EXPORT("ImageGetName", Exports::ImageGetName);
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ImageGetName)(Handle);
        }

        inline unsigned int ImageGetClassCount(void *Image)
        {
            CHECK_IS_NULL_EXPORT("ImageGetClassCount", Exports::ImageGetClassCount);
            return reinterpret_cast<unsigned int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ImageGetClassCount)(Image);
        }

        inline void *ImageGetClass(void *Image, unsigned int Index)
        {
            CHECK_IS_NULL_EXPORT("ImageGetClass", Exports::ImageGetClass);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, unsigned int)>(Exports::ImageGetClass)(Image, Index);
        }

        inline void *ClassFromName(void *Image, const char *Namespace, const char *Name)
        {
            CHECK_IS_NULL_EXPORT("ClassFromName", Exports::ClassFromName);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *, const char *)>(Exports::ClassFromName)(Image, Namespace, Name);
        }

        inline void *ObjectNew(void *Class)
        {
            CHECK_IS_NULL_EXPORT("ObjectNew", Exports::ObjectNew);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ObjectNew)(Class);
        }

        inline const char *ClassGetName(void *Class)
        {
            CHECK_IS_NULL_EXPORT("ClassGetName", Exports::ClassGetName);
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ClassGetName)(Class);
        }

        inline void *ObjectGetClass(void *Object)
        {
            CHECK_IS_NULL_EXPORT("ObjectGetClass", Exports::ObjectGetClass);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ObjectGetClass)(Object);
        }

        inline bool ClassIsInterface(void *Class)
        {
            CHECK_IS_NULL_EXPORT("ClassIsInterface", Exports::ClassIsInterface);
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ClassIsInterface)(Class);
        }

        inline bool ClassIsEnum(void *Class)
        {
            CHECK_IS_NULL_EXPORT("ClassIsEnum", Exports::ClassIsEnum);
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ClassIsEnum)(Class);
        }

        inline bool ClassIsInflated(void *Class)
        {
            CHECK_IS_NULL_EXPORT("ClassIsInflated", Exports::ClassIsInflated);
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ClassIsInflated)(Class);
        }

        inline bool ClassIsValueType(void *Class)
        {
            CHECK_IS_NULL_EXPORT("ClassIsValueType", Exports::ClassIsValueType);
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ClassIsValueType)(Class);
        }

        inline const char *ClassGetNamespace(void *Class)
        {
            CHECK_IS_NULL_EXPORT("ClassGetNamespace", Exports::ClassGetNamespace);
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ClassGetNamespace)(Class);
        }

        inline void *MethodFromName(void *Class, const char *Name, int ArgCount)
        {
            CHECK_IS_NULL_EXPORT("MethodFromName", Exports::MethodFromName);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *, int)>(Exports::MethodFromName)(Class, Name, ArgCount);
        }

        inline void *FieldFromName(void *Class, const char *Name)
        {
            CHECK_IS_NULL_EXPORT("FieldFromName", Exports::FieldFromName);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *)>(Exports::FieldFromName)(Class, Name);
        }

        inline void *ClassGetMethods(void *Class, void **Iterator)
        {
            CHECK_IS_NULL_EXPORT("ClassGetMethods", Exports::ClassGetMethods);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void **)>(Exports::ClassGetMethods)(Class, Iterator);
        }

        inline void *ClassGetFields(void *Class, void **Iterator)
        {
            CHECK_IS_NULL_EXPORT("ClassGetFields", Exports::ClassGetFields);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void **)>(Exports::ClassGetFields)(Class, Iterator);
        }

        inline int ClassArrayElementSize(void *Class)
        {
            CHECK_IS_NULL_EXPORT("ClassArrayElementSize", Exports::ClassArrayElementSize);
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ClassArrayElementSize)(Class);
        }

        inline void *TypeFromClass(void *Class)
        {
            CHECK_IS_NULL_EXPORT("ClassEnumBasetype", Exports::TypeFromClass);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::TypeFromClass)(Class);
        }

        inline void *ClassEnumBasetype(void *Class)
        {
            CHECK_IS_NULL_EXPORT("ClassEnumBasetype", Exports::ClassEnumBasetype);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ClassEnumBasetype)(Class);
        }

        inline void *TypeGetObject(void *Type)
        {
            CHECK_IS_NULL_EXPORT("TypeGetObject", Exports::TypeGetObject);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::TypeGetObject)(Type);
        }

        inline int MethodGetFlags(void *Method, void *ImplFlag = nullptr)
        {
            CHECK_IS_NULL_EXPORT("MethodGetFlags", Exports::MethodGetFlags);
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::MethodGetFlags)(Method, ImplFlag);
        }

        inline const char *MethodGetName(void *Method)
        {
            CHECK_IS_NULL_EXPORT("MethodGetName", Exports::MethodGetName);
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::MethodGetName)(Method);
        }

        inline void *MethodGetObject(void *Method, void *__p1)
        {
            CHECK_IS_NULL_EXPORT("MethodGetObject", Exports::MethodGetObject);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::MethodGetObject)(Method, __p1);
        }

        inline bool MethodIsInflated(void *Method)
        {
            CHECK_IS_NULL_EXPORT("MethodIsInflated", Exports::MethodIsInflated);
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::MethodIsInflated)(Method);
        }

        inline bool MethodIsInstance(void *Method)
        {
            CHECK_IS_NULL_EXPORT("MethodIsInstance", Exports::MethodIsInstance);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::MethodIsInstance)(Method);
        }

        inline const char *FieldGetName(void *Field)
        {
            CHECK_IS_NULL_EXPORT("FieldGetName", Exports::FieldGetName);
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::FieldGetName)(Field);
        }

        inline int FieldGetFlags(void *Field)
        {
            CHECK_IS_NULL_EXPORT("FieldGetFlags", Exports::FieldGetFlags);
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::FieldGetFlags)(Field);
        }

        inline int FieldGetOffset(void *Field)
        {
            CHECK_IS_NULL_EXPORT("FieldGetOffset", Exports::FieldGetOffset);
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::FieldGetOffset)(Field);
        }

        inline void *FieldGetType(void *Field)
        {
            CHECK_IS_NULL_EXPORT("FieldGetType", Exports::FieldGetType);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::FieldGetType)(Field);
        }

        inline void *ClassFromType(void *Type)
        {
            CHECK_IS_NULL_EXPORT("ClassFromType", Exports::ClassFromType);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ClassFromType)(Type);
        }

        inline const char *TypeGetName(void *Type)
        {
            CHECK_IS_NULL_EXPORT("TypeGetName", Exports::TypeGetName);
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::TypeGetName)(Type);
        }

        inline void RuntimeClassInit(void *Class)
        {
            CHECK_IS_NULL_EXPORT("RuntimeClassInit", Exports::RuntimeClassInit);
            reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::RuntimeClassInit)(Class);
        }

        inline uintptr_t GetStaticFieldValue(void *Field)
        {
            CHECK_IS_NULL_EXPORT("GetStaticFieldValue", Exports::GetStaticFieldValue);
            uintptr_t value = 0;
            reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::GetStaticFieldValue)(Field, (void *)&value);
            return value;
        }

        inline void SetStaticFieldValue(void *Field, void *Value)
        {
            CHECK_IS_NULL_EXPORT("SetStaticFieldValue", Exports::SetStaticFieldValue);
            return reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::SetStaticFieldValue)(Field, Value);
        }

        inline void *ThreadAttach(void *Domain)
        {
            CHECK_IS_NULL_EXPORT("ThreadAttach", Exports::ThreadAttach);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ThreadAttach)(Domain);
        }

        inline void *ClassGetInterfaces(void *Class, void **Iterator)
        {
            CHECK_IS_NULL_EXPORT("ClassGetInterfaces", Exports::ClassGetInterfaces);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void **)>(Exports::ClassGetInterfaces)(Class, Iterator);
        }

        inline uint8_t MethodGetParamCount(void *Method)
        {
            CHECK_IS_NULL_EXPORT("MethodGetParamCount", Exports::MethodGetParamCount);
            return reinterpret_cast<uint8_t(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::MethodGetParamCount)(Method);
        }

        inline void *MethodGetParamType(void *Method, uint32_t Index)
        {
            CHECK_IS_NULL_EXPORT("MethodGetParamType", Exports::MethodGetParamType);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, uint32_t)>(Exports::MethodGetParamType)(Method, Index);
        }

        inline const char *MethodGetParamName(void *Method, uint32_t Index)
        {
            CHECK_IS_NULL_EXPORT("MethodGetParamName", Exports::MethodGetParamName);
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *, uint32_t)>(Exports::MethodGetParamName)(Method, Index);
        }

        inline void *ClassNestedClasses(void *Class, void **Iterator)
        {
            CHECK_IS_NULL_EXPORT("ClassNestedClasses", Exports::ClassNestedClasses);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void **)>(Exports::ClassNestedClasses)(Class, Iterator);
        }

        inline void *StringNew(const char *Content)
        {
            CHECK_IS_NULL_EXPORT("StringNew", Exports::StringNew);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(const char *)>(Exports::StringNew)(Content);
        }

        inline LPCWCH StringChars(void *String)
        {
            CHECK_IS_NULL_EXPORT("StringChars", Exports::StringChars);
            return reinterpret_cast<LPCWCH(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::StringChars)(String);
        }

        inline int StringLength(void *String)
        {
            CHECK_IS_NULL_EXPORT("StringLength", Exports::StringLength);
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::StringLength)(String);
        }

        inline void *ArrayNew(void *Class, int Length)
        {
            CHECK_IS_NULL_EXPORT("ArrayNew", Exports::ArrayNew);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, int)>(Exports::ArrayNew)(Class, Length);
        }

        inline int ArrayLength(void *Array)
        {
            CHECK_IS_NULL_EXPORT("ArrayLength", Exports::ArrayLength);
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ArrayLength)(Array);
        }

        inline void *ClassFromSystemType(void *RuntimeType)
        {
            CHECK_IS_NULL_EXPORT("ClassFromSystemType", Exports::ClassFromSystemType);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ClassFromSystemType)(RuntimeType);
        }

        inline void *MethodGetReturnType(void *Method)
        {
            CHECK_IS_NULL_EXPORT("MethodGetReturnType", Exports::MethodGetReturnType);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::MethodGetReturnType)(Method);
        }

        inline int ClassGetInstanceSize(void *Class)
        {
            CHECK_IS_NULL_EXPORT("ClassGetInstanceSize", Exports::ClassGetInstanceSize);
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ClassGetInstanceSize)(Class);
        }

        /*
        inline void *ObjectValueBox(void *Object, void **Instance)
        {
            CHECK_IS_NULL_EXPORT("ObjectValueBox", Exports::ObjectValueBox);
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::ObjectValueBox)(Object, Instance);
        }
        */
    }
}