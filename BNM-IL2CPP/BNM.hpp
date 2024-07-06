// Exports, defines

// Structures
#include "Structures/IL2CPP/Domain.hpp"
#include "Structures/IL2CPP/String.hpp"
#include "Structures/IL2CPP/Array.hpp"

#include <Windows.h>
#include <memoryapi.h>

#include <string>
#include <unordered_map>

namespace IL2CPP
{
    void *ResolveExport(const char *m_Name)
    {
        return GetProcAddress(Exports::GameAssembly, m_Name);
    }

    // Initializing
    void Initialize()
    {
        Exports::GameAssembly = GetModuleHandleA(MAIN_MODULE);

        std::unordered_map<std::string, void **>
            ExportMap = {
                {IL2CPP_DOMAIN_GET, &Exports::m_IL2CPP_DOMAIN_GET},
                {IL2CPP_ASSEMBLY_GET_FROM_DOMAIN, &Exports::m_IL2CPP_ASSEMBLY_GET_FROM_DOMAIN},
                {IL2CPP_ASSEMBLY_GET_IMAGE, &Exports::m_IL2CPP_ASSEMBLY_GET_IMAGE},
                {IL2CPP_IMAGE_GET_NAME, &Exports::m_IL2CPP_IMAGE_GET_NAME},
                {IL2CPP_CLASS_FROM_NAME, &Exports::m_IL2CPP_CLASS_FROM_NAME},
                {IL2CPP_OBJECT_NEW, &Exports::m_IL2CPP_OBJECT_NEW},
                {IL2CPP_METHOD_FROM_NAME, &Exports::m_IL2CPP_METHOD_FROM_NAME},
                {IL2CPP_FIELD_FROM_NAME, &Exports::m_IL2CPP_FIELD_FROM_NAME},
                {IL2CPP_FIELD_STATIC_GET_VALUE, &Exports::m_IL2CPP_FIELD_STATIC_GET_VALUE},
                {IL2CPP_FIELD_GET_NAME, &Exports::m_IL2CPP_FIELD_GET_NAME},
                {IL2CPP_FIELD_GET_FLAGS, &Exports::m_IL2CPP_FIELD_GET_FLAGS},
                {IL2CPP_OBJECT_GET_CLASS, &Exports::m_IL2CPP_OBJECT_GET_CLASS},
                {IL2CPP_FIELD_GET_OFFSET, &Exports::m_IL2CPP_FIELD_GET_OFFSET},
                {IL2CPP_CLASS_GET_NAME, &Exports::m_IL2CPP_CLASS_GET_NAME},
                {IL2CPP_METHOD_GET_FLAGS, &Exports::m_IL2CPP_METHOD_GET_FLAGS},
                {IL2CPP_METHOD_GET_NAME, &Exports::m_IL2CPP_METHOD_GET_NAME},
                {IL2CPP_RUNTIME_CLASS_INIT, &Exports::m_IL2CPP_RUNTIME_CLASS_INIT},
                {IL2CPP_STRING_NEW, &Exports::m_IL2CPP_STRING_NEW},
                {IL2CPP_STRING_CHARS, &Exports::m_IL2CPP_STRING_CHARS},
                {IL2CPP_STRING_LENGTH, &Exports::m_IL2CPP_STRING_LENGTH},
                {IL2CPP_ARRAY_NEW, &Exports::m_IL2CPP_ARRAY_NEW},
                {IL2CPP_ARRAY_LENGTH, &Exports::m_IL2CPP_ARRAY_LENGTH},
                {IL2CPP_CLASS_ENUM_BASETYPE, &Exports::m_IL2CPP_CLASS_ENUM_BASETYPE},
                {IL2CPP_TYPE_GET_TYPE, &Exports::m_IL2CPP_TYPE_GET_TYPE},
                {IL2CPP_CLASS_ARRAY_ELEMENT_SIZE, &Exports::m_IL2CPP_CLASS_ARRAY_ELEMENT_SIZE},
                {IL2CPP_TYPE_FROM_CLASS, &Exports::m_IL2CPP_TYPE_FROM_CLASS},
                {IL2CPP_CLASS_FROM_TYPE, &Exports::m_IL2CPP_CLASS_FROM_TYPE},
                {IL2CPP_CLASS_NESTED_CLASSES, &Exports::m_IL2CPP_CLASS_NESTED_CLASSES},
                {IL2CPP_ALLOC, &Exports::m_IL2CPP_ALLOC},
                {IL2CPP_TYPE_GET_OBJECT, &Exports::m_IL2CPP_TYPE_GET_OBJECT},
                {IL2CPP_FIELD_STATIC_SET_VALUE, &Exports::m_IL2CPP_FIELD_STATIC_SET_VALUE},
                {IL2CPP_CLASS_FROM_SYSTEM_TYPE, &Exports::m_IL2CPP_CLASS_FROM_SYSTEM_TYPE},
            };
        for (auto &p : ExportMap)
        {
            *p.second = ResolveExport(p.first.c_str());
        }
    };
}