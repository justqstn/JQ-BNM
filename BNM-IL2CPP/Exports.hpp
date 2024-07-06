#pragma once

#include <Windows.h>

namespace IL2CPP
{
    namespace Exports
    {
        HMODULE GameAssembly{nullptr};
        void *m_IL2CPP_DOMAIN_GET{nullptr};
        void *m_IL2CPP_ASSEMBLY_GET_FROM_DOMAIN{nullptr};
        void *m_IL2CPP_ASSEMBLY_GET_IMAGE{nullptr};
        void *m_IL2CPP_IMAGE_GET_NAME{nullptr};
        void *m_IL2CPP_OBJECT_NEW{nullptr};
        void *m_IL2CPP_CLASS_FROM_NAME{nullptr};
        void *m_IL2CPP_METHOD_FROM_NAME{nullptr};
        void *m_IL2CPP_FIELD_FROM_NAME{nullptr};
        void *m_IL2CPP_FIELD_STATIC_GET_VALUE{nullptr};
        void *m_IL2CPP_FIELD_GET_NAME{nullptr};
        void *m_IL2CPP_FIELD_GET_FLAGS{nullptr};
        void *m_IL2CPP_FIELD_GET_OFFSET{nullptr};
        void *m_IL2CPP_OBJECT_GET_CLASS{nullptr};
        void *m_IL2CPP_CLASS_GET_NAME{nullptr};
        void *m_IL2CPP_METHOD_GET_FLAGS{nullptr};
        void *m_IL2CPP_METHOD_GET_NAME{nullptr};
        void *m_IL2CPP_RUNTIME_CLASS_INIT{nullptr};
        void *m_IL2CPP_STRING_NEW{nullptr};
        void *m_IL2CPP_STRING_CHARS{nullptr};
        void *m_IL2CPP_STRING_LENGTH{nullptr};
        void *m_IL2CPP_ARRAY_NEW{nullptr};
        void *m_IL2CPP_ARRAY_LENGTH{nullptr};
        void *m_IL2CPP_CLASS_ENUM_BASETYPE{nullptr};
        void *m_IL2CPP_TYPE_GET_TYPE{nullptr};
        void *m_IL2CPP_CLASS_ARRAY_ELEMENT_SIZE{nullptr};
        void *m_IL2CPP_CLASS_FROM_TYPE{nullptr};
        void *m_IL2CPP_TYPE_FROM_CLASS{nullptr};
        void *m_IL2CPP_CLASS_NESTED_CLASSES{nullptr};
        void *m_IL2CPP_ALLOC{nullptr};
        void *m_IL2CPP_FIELD_STATIC_SET_VALUE{nullptr};
        void *m_IL2CPP_TYPE_GET_OBJECT{nullptr};
        void *m_IL2CPP_CLASS_FROM_SYSTEM_TYPE{nullptr};
    }
}