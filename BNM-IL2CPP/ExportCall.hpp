#pragma once

#include "Exports.hpp"
#include "Defines.hpp"

namespace IL2CPP
{
    namespace ExportCall
    {
        void *GetDomain()
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)()>(Exports::m_IL2CPP_DOMAIN_GET)();
        }

        void *GetAssemblyFromDomain(void *handle, const char *name)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *)>(Exports::m_IL2CPP_ASSEMBLY_GET_FROM_DOMAIN)(handle, name);
        }

        void *AssemblyGetImage(void *handle)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_ASSEMBLY_GET_IMAGE)(handle);
        }

        const char *ImageGetName(void *handle)
        {
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_IMAGE_GET_NAME)(handle);
        }

        void *ObjectNew(void *klass)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_OBJECT_NEW)(klass);
        }

        void *ClassFromName(void *image, const char *k_namespace, const char *k_name)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *, const char *)>(Exports::m_IL2CPP_CLASS_FROM_NAME)(image, k_namespace, k_name);
        }

        void *MethodFromName(void *klass, const char *name, int parameter_count)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *, int)>(Exports::m_IL2CPP_METHOD_FROM_NAME)(klass, name, parameter_count);
        }

        void *FieldFromName(void *klass, const char *name)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *)>(Exports::m_IL2CPP_FIELD_FROM_NAME)(klass, name);
        }

        void *GetStaticFieldValue(void *field)
        {
            void *value = nullptr;
            reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::m_IL2CPP_FIELD_STATIC_GET_VALUE)(field, &value);
            return value;
        }

        const char *FieldGetName(void *field)
        {
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_FIELD_GET_NAME)(field);
        }

        int FieldGetFlags(void *field)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_FIELD_GET_FLAGS)(field);
        }

        int FieldGetOffset(void *field)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_FIELD_GET_OFFSET)(field);
        }

        void *ObjectGetClass(void *object)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_OBJECT_GET_CLASS)(object);
        }

        const char *ClassGetName(void *klass)
        {
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_GET_NAME)(klass);
        }

        int MethodGetFlags(void *method, void *implflag = nullptr)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::m_IL2CPP_METHOD_GET_FLAGS)(method, implflag);
        }

        const char *MethodGetName(void *method)
        {
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_METHOD_GET_NAME)(method);
        }

        void RuntimeClassInit(void *klass)
        {
            reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_RUNTIME_CLASS_INIT)(klass);
        }

        void *StringNew(const char *content)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(const char *)>(Exports::m_IL2CPP_STRING_NEW)(content);
        }

        LPCWCH StringChars(void *instance)
        {
            return reinterpret_cast<LPCWCH(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_STRING_CHARS)(instance);
        }

        int StringLength(void *instance)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_STRING_LENGTH)(instance);
        }

        void *ArrayNew(void *klass, int length)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, int)>(Exports::m_IL2CPP_ARRAY_NEW)(klass, length);
        }

        int ArrayLength(void *instance)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_ARRAY_LENGTH)(instance);
        }

        void *ClassEnumBasetype(void *klass)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_ENUM_BASETYPE)(klass);
        }

        // erm what the sigma
        int TypeGetType(void *basetype)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_TYPE_GET_TYPE)(basetype);
        }

        int ClassArrayElementSize(void *klass)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_ARRAY_ELEMENT_SIZE)(klass);
        }

        void *ClassFromType(void *type)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_FROM_TYPE)(type);
        }

        void *TypeFromClass(void *klass)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_TYPE_FROM_CLASS)(klass);
        }

        void *ClassNestedClasses(void *klass, void **iterator)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void **)>(Exports::m_IL2CPP_CLASS_NESTED_CLASSES)(klass, iterator);
        }

        void *Alloc(size_t size)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(size_t)>(Exports::m_IL2CPP_ALLOC)(size);
        }

        void FieldStaticSetValue(void *field, void *value)
        {
            return reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::m_IL2CPP_FIELD_STATIC_SET_VALUE)(field, value);
        }

        void *TypeGetObject(void *type)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_TYPE_GET_OBJECT)(type);
        }

        void* ClassFromSystemType(void* runtimetype) {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_FROM_SYSTEM_TYPE)(runtimetype);
        }
    }
}