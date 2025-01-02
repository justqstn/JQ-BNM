#pragma once

// Debug function
#define LOG_DEBUG

// Error function
#define LOG_ERROR

#ifdef _WIN64
#define IL2CPP_CALLING_CONVENTION __fastcall *
#elif _WIN32
#define IL2CPP_CALLING_CONVENTION __cdecl *
#endif

#define MAIN_MODULE "GameAssembly.dll"
#define IL2CPP_DOMAIN_GET "il2cpp_domain_get"
#define IL2CPP_ASSEMBLY_GET_FROM_DOMAIN "il2cpp_domain_assembly_open"
#define IL2CPP_ASSEMBLY_GET_IMAGE "il2cpp_assembly_get_image"
#define IL2CPP_IMAGE_GET_NAME "il2cpp_image_get_name"
#define IL2CPP_OBJECT_NEW "il2cpp_object_new"
#define IL2CPP_CLASS_FROM_NAME "il2cpp_class_from_name"
#define IL2CPP_METHOD_FROM_NAME "il2cpp_class_get_method_from_name"
#define IL2CPP_FIELD_FROM_NAME "il2cpp_class_get_field_from_name"
#define IL2CPP_FIELD_STATIC_GET_VALUE "il2cpp_field_static_get_value"
#define IL2CPP_FIELD_GET_NAME "il2cpp_field_get_name"
#define IL2CPP_FIELD_GET_FLAGS "il2cpp_field_get_flags"
#define IL2CPP_FIELD_GET_OFFSET "il2cpp_field_get_offset"
#define IL2CPP_OBJECT_GET_CLASS "il2cpp_object_get_class"
#define IL2CPP_CLASS_GET_NAME "il2cpp_class_get_name"
#define IL2CPP_METHOD_GET_FLAGS "il2cpp_method_get_flags"
#define IL2CPP_METHOD_GET_NAME "il2cpp_method_get_name"
#define IL2CPP_RUNTIME_CLASS_INIT "il2cpp_runtime_class_init"
#define IL2CPP_STRING_NEW "il2cpp_string_new"
#define IL2CPP_STRING_CHARS "il2cpp_string_chars"
#define IL2CPP_STRING_LENGTH "il2cpp_string_length"
#define IL2CPP_ARRAY_NEW "il2cpp_array_new"
#define IL2CPP_ARRAY_LENGTH "il2cpp_array_length"
#define IL2CPP_CLASS_ENUM_BASETYPE "il2cpp_class_enum_basetype"
#define IL2CPP_TYPE_GET_TYPE "il2cpp_type_get_type"
#define IL2CPP_CLASS_ARRAY_ELEMENT_SIZE "il2cpp_class_array_element_size"
#define IL2CPP_CLASS_FROM_TYPE "il2cpp_class_from_type"
#define IL2CPP_TYPE_FROM_CLASS "il2cpp_class_get_type"
#define IL2CPP_CLASS_NESTED_CLASSES "il2cpp_class_get_nested_types"
#define IL2CPP_ALLOC "il2cpp_alloc"
#define IL2CPP_FIELD_STATIC_SET_VALUE "il2cpp_field_static_set_value"
#define IL2CPP_TYPE_GET_OBJECT "il2cpp_type_get_object"
#define IL2CPP_CLASS_FROM_SYSTEM_TYPE "il2cpp_class_from_system_type"
#define IL2CPP_METHOD_IS_INFLATED "il2cpp_method_is_inflated"
#define IL2CPP_VALUE_BOX "il2cpp_value_box"
#define IL2CPP_METHOD_IS_INSTANCE "il2cpp_method_is_instance"
#define IL2CPP_FIELD_GET_PARENT "il2cpp_field_get_parent"
#define IL2CPP_METHOD_GET_CLASS "il2cpp_method_get_class"
#define IL2CPP_CLASS_GET_METHODS "il2cpp_class_get_methods"
#define IL2CPP_CLASS_GET_FIELDS "il2cpp_class_get_fields"
#define IL2CPP_METHOD_GET_PARAM_COUNT "il2cpp_method_get_param_count"
#define IL2CPP_METHOD_GET_PARAM_NAME "il2cpp_method_get_param_name"
#define IL2CPP_METHOD_GET_PARAM_TYPE "il2cpp_method_get_param"
#define IL2CPP_TYPE_GET_NAME "il2cpp_type_get_name"
#define IL2CPP_METHOD_GET_RETURN_TYPE "il2cpp_method_get_return_type"
#define IL2CPP_FIELD_GET_TYPE "il2cpp_field_get_type"
#define IL2CPP_CLASS_IS_VALUETYPE "il2cpp_class_is_valuetype"
#define IL2CPP_CLASS_IS_INTERFACE "il2cpp_class_is_interface"
#define IL2CPP_CLASS_IS_ENUM "il2cpp_class_is_enum"
#define IL2CPP_CLASS_IS_INFLATED "il2cpp_class_is_inflated"
#define IL2CPP_CLASS_GET_NAMESPACE "il2cpp_class_get_namespace"
// #define IL2CPP_DOMAIN_GET_ASSEMBLIES "a62a4a_wasting_your_life"
#define IL2CPP_IMAGE_GET_CLASS_COUNT "il2cpp_image_get_class_count"
#define IL2CPP_IMAGE_GET_CLASS "il2cpp_image_get_class"
#define IL2CPP_CLASS_GET_INTERFACES "il2cpp_class_get_interfaces"
#define IL2CPP_METHOD_GET_OBJECT "il2cpp_method_get_object"