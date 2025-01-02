#pragma once

#include <Windows.h>

namespace IL2CPP
{
    namespace Exports
    {
        static HMODULE GameAssembly{nullptr};
        static void *m_IL2CPP_DOMAIN_GET{nullptr};
        static void *m_IL2CPP_ASSEMBLY_GET_FROM_DOMAIN{nullptr};
        static void *m_IL2CPP_ASSEMBLY_GET_IMAGE{nullptr};
        static void *m_IL2CPP_IMAGE_GET_NAME{nullptr};
        static void *m_IL2CPP_OBJECT_NEW{nullptr};
        static void *m_IL2CPP_CLASS_FROM_NAME{nullptr};
        static void *m_IL2CPP_METHOD_FROM_NAME{nullptr};
        static void *m_IL2CPP_FIELD_FROM_NAME{nullptr};
        static void *m_IL2CPP_FIELD_STATIC_GET_VALUE{nullptr};
        static void *m_IL2CPP_FIELD_GET_NAME{nullptr};
        static void *m_IL2CPP_FIELD_GET_FLAGS{nullptr};
        static void *m_IL2CPP_FIELD_GET_OFFSET{nullptr};
        static void *m_IL2CPP_OBJECT_GET_CLASS{nullptr};
        static void *m_IL2CPP_CLASS_GET_NAME{nullptr};
        static void *m_IL2CPP_METHOD_GET_FLAGS{nullptr};
        static void *m_IL2CPP_METHOD_GET_NAME{nullptr};
        static void *m_IL2CPP_RUNTIME_CLASS_INIT{nullptr};
        static void *m_IL2CPP_STRING_NEW{nullptr};
        static void *m_IL2CPP_STRING_CHARS{nullptr};
        static void *m_IL2CPP_STRING_LENGTH{nullptr};
        static void *m_IL2CPP_ARRAY_NEW{nullptr};
        static void *m_IL2CPP_ARRAY_LENGTH{nullptr};
        static void *m_IL2CPP_CLASS_ENUM_BASETYPE{nullptr};
        static void *m_IL2CPP_TYPE_GET_TYPE{nullptr};
        static void *m_IL2CPP_CLASS_ARRAY_ELEMENT_SIZE{nullptr};
        static void *m_IL2CPP_CLASS_FROM_TYPE{nullptr};
        static void *m_IL2CPP_TYPE_FROM_CLASS{nullptr};
        static void *m_IL2CPP_CLASS_NESTED_CLASSES{nullptr};
        static void *m_IL2CPP_ALLOC{nullptr};
        static void *m_IL2CPP_FIELD_STATIC_SET_VALUE{nullptr};
        static void *m_IL2CPP_TYPE_GET_OBJECT{nullptr};
        static void *m_IL2CPP_CLASS_FROM_SYSTEM_TYPE{nullptr};
        static void *m_IL2CPP_METHOD_IS_INFLATED{nullptr};
        static void *m_IL2CPP_VALUE_BOX{nullptr};
        static void *m_IL2CPP_METHOD_IS_INSTANCE{nullptr};
        static void *m_IL2CPP_FIELD_GET_PARENT{nullptr};
        static void *m_IL2CPP_METHOD_GET_CLASS{nullptr};
        static void *m_IL2CPP_CLASS_GET_METHODS{nullptr};
        static void *m_IL2CPP_CLASS_GET_FIELDS{nullptr};
        static void *m_IL2CPP_METHOD_GET_PARAM_COUNT{nullptr};
        static void *m_IL2CPP_METHOD_GET_PARAM_NAME{nullptr};
        static void *m_IL2CPP_METHOD_GET_PARAM_TYPE{nullptr};
        static void *m_IL2CPP_TYPE_GET_NAME{nullptr};
        static void *m_IL2CPP_METHOD_GET_RETURN_TYPE{nullptr};
        static void *m_IL2CPP_FIELD_GET_TYPE{nullptr};
        static void *m_IL2CPP_CLASS_IS_INTERFACE{nullptr};
        static void *m_IL2CPP_CLASS_IS_VALUETYPE{nullptr};
        static void *m_IL2CPP_CLASS_IS_ENUM{nullptr};
        static void *m_IL2CPP_CLASS_IS_INFLATED{nullptr};
        static void *m_IL2CPP_CLASS_GET_NAMESPACE{nullptr};
        static void *m_IL2CPP_DOMAIN_GET_ASSEMBLIES{nullptr};
        static void *m_IL2CPP_IMAGE_GET_CLASS_COUNT{nullptr};
        static void *m_IL2CPP_IMAGE_GET_CLASS{nullptr};
        static void *m_IL2CPP_CLASS_GET_INTERFACES{nullptr};
        static void *m_IL2CPP_METHOD_GET_OBJECT{nullptr};
    }
}