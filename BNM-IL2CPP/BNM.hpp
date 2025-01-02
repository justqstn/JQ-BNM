// Exports, defines

// Structures
#include "Structures/IL2CPP.hpp"
#include "Structures/UnityEngine.hpp"

#include "Defines.hpp"

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
                {IL2CPP_METHOD_IS_INSTANCE, &Exports::m_IL2CPP_METHOD_IS_INSTANCE},
                {IL2CPP_FIELD_GET_PARENT, &Exports::m_IL2CPP_FIELD_GET_PARENT},
                {IL2CPP_METHOD_GET_CLASS, &Exports::m_IL2CPP_METHOD_GET_CLASS},
                {IL2CPP_CLASS_GET_METHODS, &Exports::m_IL2CPP_CLASS_GET_METHODS},
                {IL2CPP_CLASS_GET_FIELDS, &Exports::m_IL2CPP_CLASS_GET_FIELDS},
                {IL2CPP_METHOD_GET_PARAM_COUNT, &Exports::m_IL2CPP_METHOD_GET_PARAM_COUNT},
                {IL2CPP_METHOD_GET_PARAM_TYPE, &Exports::m_IL2CPP_METHOD_GET_PARAM_TYPE},
                {IL2CPP_METHOD_GET_PARAM_NAME, &Exports::m_IL2CPP_METHOD_GET_PARAM_NAME},
                {IL2CPP_TYPE_GET_NAME, &Exports::m_IL2CPP_TYPE_GET_NAME},
                {IL2CPP_METHOD_GET_RETURN_TYPE, &Exports::m_IL2CPP_METHOD_GET_RETURN_TYPE},
                {IL2CPP_FIELD_GET_TYPE, &Exports::m_IL2CPP_FIELD_GET_TYPE},
                {IL2CPP_CLASS_IS_INTERFACE, &Exports::m_IL2CPP_CLASS_IS_INTERFACE},
                {IL2CPP_CLASS_IS_VALUETYPE, &Exports::m_IL2CPP_CLASS_IS_VALUETYPE},
                {IL2CPP_CLASS_IS_ENUM, &Exports::m_IL2CPP_CLASS_IS_ENUM},
                {IL2CPP_CLASS_IS_INFLATED, &Exports::m_IL2CPP_CLASS_IS_INFLATED},
                {IL2CPP_CLASS_GET_NAMESPACE, &Exports::m_IL2CPP_CLASS_GET_NAMESPACE},
                //{IL2CPP_DOMAIN_GET_ASSEMBLIES, &Exports::m_IL2CPP_DOMAIN_GET_ASSEMBLIES},
                {IL2CPP_IMAGE_GET_CLASS_COUNT, &Exports::m_IL2CPP_IMAGE_GET_CLASS_COUNT},
                {IL2CPP_IMAGE_GET_CLASS, &Exports::m_IL2CPP_IMAGE_GET_CLASS},
                {IL2CPP_CLASS_GET_INTERFACES, &Exports::m_IL2CPP_CLASS_GET_INTERFACES},
                {IL2CPP_METHOD_GET_OBJECT, &Exports::m_IL2CPP_METHOD_GET_OBJECT}};

        for (auto &p : ExportMap)
        {
            *p.second = ResolveExport(p.first.c_str());
            if ((uint64_t)*p.second == 0)
                LOG_ERROR(p.first + " is not found!");
        }
    };
}