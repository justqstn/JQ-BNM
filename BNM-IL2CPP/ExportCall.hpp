#pragma once

#include "Exports.hpp"
#include "Defines.hpp"

namespace IL2CPP
{
    namespace ExportCall
    {
        inline void *GetDomain()
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)()>(Exports::m_IL2CPP_DOMAIN_GET)();
        }

        inline void *GetAssemblyFromDomain(void *handle, const char *name)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *)>(Exports::m_IL2CPP_ASSEMBLY_GET_FROM_DOMAIN)(handle, name);
        }

        inline void *AssemblyGetImage(void *handle)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_ASSEMBLY_GET_IMAGE)(handle);
        }

        inline const char *ImageGetName(void *handle)
        {
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_IMAGE_GET_NAME)(handle);
        }

        inline void *ObjectNew(void *klass)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_OBJECT_NEW)(klass);
        }

        inline void *ClassFromName(void *image, const char *k_namespace, const char *k_name)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *, const char *)>(Exports::m_IL2CPP_CLASS_FROM_NAME)(image, k_namespace, k_name);
        }

        inline void *MethodFromName(void *klass, const char *name, int parameter_count)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *, int)>(Exports::m_IL2CPP_METHOD_FROM_NAME)(klass, name, parameter_count);
        }

        inline void *FieldFromName(void *klass, const char *name)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, const char *)>(Exports::m_IL2CPP_FIELD_FROM_NAME)(klass, name);
        }

        inline uint64_t GetStaticFieldValue(void *field)
        {
            uint64_t value = 0;
            reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::m_IL2CPP_FIELD_STATIC_GET_VALUE)(field, (void *)&value);
            return value;
        }

        inline const char *FieldGetName(void *field)
        {
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_FIELD_GET_NAME)(field);
        }

        inline int FieldGetFlags(void *field)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_FIELD_GET_FLAGS)(field);
        }

        inline int FieldGetOffset(void *field)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_FIELD_GET_OFFSET)(field);
        }

        inline void *ObjectGetClass(void *object)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_OBJECT_GET_CLASS)(object);
        }

        inline const char *ClassGetName(void *klass)
        {
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_GET_NAME)(klass);
        }

        inline int MethodGetFlags(void *method, void *implflag = nullptr)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::m_IL2CPP_METHOD_GET_FLAGS)(method, implflag);
        }

        inline const char *MethodGetName(void *method)
        {
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_METHOD_GET_NAME)(method);
        }

        inline void RuntimeClassInit(void *klass)
        {
            reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_RUNTIME_CLASS_INIT)(klass);
        }

        inline void *StringNew(const char *content)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(const char *)>(Exports::m_IL2CPP_STRING_NEW)(content);
        }

        inline LPCWCH StringChars(void *instance)
        {
            return reinterpret_cast<LPCWCH(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_STRING_CHARS)(instance);
        }

        inline int StringLength(void *instance)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_STRING_LENGTH)(instance);
        }

        inline void *ArrayNew(void *klass, int length)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, int)>(Exports::m_IL2CPP_ARRAY_NEW)(klass, length);
        }

        inline int ArrayLength(void *instance)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_ARRAY_LENGTH)(instance);
        }

        inline void *ClassEnumBasetype(void *klass)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_ENUM_BASETYPE)(klass);
        }

        // erm what the sigma
        inline int TypeGetType(void *basetype)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_TYPE_GET_TYPE)(basetype);
        }

        inline int ClassArrayElementSize(void *klass)
        {
            return reinterpret_cast<int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_ARRAY_ELEMENT_SIZE)(klass);
        }

        inline void *ClassFromType(void *type)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_FROM_TYPE)(type);
        }

        inline void *TypeFromClass(void *klass)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_TYPE_FROM_CLASS)(klass);
        }

        inline void *ClassNestedClasses(void *klass, void **iterator)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void **)>(Exports::m_IL2CPP_CLASS_NESTED_CLASSES)(klass, iterator);
        }

        inline void *Alloc(size_t size)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(size_t)>(Exports::m_IL2CPP_ALLOC)(size);
        }

        inline void FieldStaticSetValue(void *field, void *value)
        {
            return reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::m_IL2CPP_FIELD_STATIC_SET_VALUE)(field, value);
        }

        inline void *TypeGetObject(void *type)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_TYPE_GET_OBJECT)(type);
        }

        inline void *ClassFromSystemType(void *runtimetype)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_FROM_SYSTEM_TYPE)(runtimetype);
        }

        inline bool MethodIsInflated(void *method)
        {
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_METHOD_IS_INFLATED)(method);
        }

        inline void *ValueBox(void *value, void *klass)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::m_IL2CPP_VALUE_BOX)(value, klass);
        }

        inline bool MethodIsInstance(void *method)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_METHOD_IS_INSTANCE)(method);
        }

        inline void *FieldGetParent(void *field)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_FIELD_GET_PARENT)(field);
        }

        inline void *MethodGetClass(void *method)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_METHOD_GET_CLASS)(method);
        }

        inline void *ClassGetMethods(void *klass, void **iterator)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void **)>(Exports::m_IL2CPP_CLASS_GET_METHODS)(klass, iterator);
        }

        inline void *ClassGetFields(void *klass, void **iterator)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void **)>(Exports::m_IL2CPP_CLASS_GET_FIELDS)(klass, iterator);
        }

        inline uint8_t MethodGetParamCount(void *method)
        {
            return reinterpret_cast<uint8_t(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_METHOD_GET_PARAM_COUNT)(method);
        }

        inline void *MethodGetParamType(void *method, uint32_t index)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, uint32_t)>(Exports::m_IL2CPP_METHOD_GET_PARAM_TYPE)(method, index);
        }

        inline const char *MethodGetParamName(void *method, uint32_t index)
        {
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *, uint32_t)>(Exports::m_IL2CPP_METHOD_GET_PARAM_NAME)(method, index);
        }

        inline const char *TypeGetName(void *type)
        {
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_TYPE_GET_NAME)(type);
        }

        inline void *MethodGetReturnType(void *method)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_METHOD_GET_RETURN_TYPE)(method);
        }

        inline void *FieldGetType(void *field)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_FIELD_GET_TYPE)(field);
        }

        inline bool ClassIsInterface(void *klass)
        {
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_IS_INTERFACE)(klass);
        }

        inline bool ClassIsEnum(void *klass)
        {
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_IS_ENUM)(klass);
        }

        inline bool ClassIsInflated(void *klass)
        {
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_IS_INFLATED)(klass);
        }

        inline bool ClassIsValueType(void *klass)
        {
            return reinterpret_cast<bool(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_IS_VALUETYPE)(klass);
        }

        inline const char *ClassGetNamespace(void *klass)
        {
            return reinterpret_cast<const char *(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_CLASS_GET_NAMESPACE)(klass);
        }

        inline void *DomainGetAssemblies(void *domain, void **iterator)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void **)>(Exports::m_IL2CPP_DOMAIN_GET_ASSEMBLIES)(domain, iterator);
        }

        inline unsigned int ImageGetClassCount(void *image)
        {
            return reinterpret_cast<unsigned int(IL2CPP_CALLING_CONVENTION)(void *)>(Exports::m_IL2CPP_IMAGE_GET_CLASS_COUNT)(image);
        }

        inline void *ImageGetClass(void *image, unsigned int index)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, unsigned int)>(Exports::m_IL2CPP_IMAGE_GET_CLASS)(image, index);
        }

        inline void *ClassGetInterfaces(void *klass, void **iterator)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void **)>(Exports::m_IL2CPP_CLASS_GET_INTERFACES)(klass, iterator);
        }

        inline void *MethodGetObject(void *method, void *hi)
        {
            return reinterpret_cast<void *(IL2CPP_CALLING_CONVENTION)(void *, void *)>(Exports::m_IL2CPP_IMAGE_GET_CLASS)(method, hi);
        }
    }
}