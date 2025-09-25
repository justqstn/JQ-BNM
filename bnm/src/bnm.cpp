#include <cstdint>
#include <vector>
#include <format>
#include <Windows.h>
#include <thread>
#include <psapi.h>
#include <thread>
#include <sstream>

#include "../include/bnm.h"
#include "../include/domain.h"
#include "../include/defines.h"
#include "../include/exports.h"
#include "../include/exportcall.h"
#include "../include/dumper.h"

MODULEINFO GetModuleInfo(const char *szModule)
{
    MODULEINFO modinfo = {0};
    HMODULE hModule = GetModuleHandleA(szModule);
    if (hModule == 0)
        return modinfo;
    GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
    return modinfo;
}

uintptr_t GetExport(const std::string &Name)
{
    uintptr_t result = GetProcAddress(IL2CPP::Exports::GameAssembly, Name.c_str());
    DEBUG(std::format("Export {}: 0x{:x}", Name, result));
    return result;
}

namespace IL2CPP
{
    void Initialize()
    {
        Exports::GameAssembly = GetModuleHandleA(MAIN_MODULE);
        MODULEINFO dll_modinfo = GetModuleInfo(MAIN_MODULE);

        Exports::AssemblyGetImage = GetExport(IL2CPP_ASSEMBLY_GET_IMAGE);
        Exports::DomainGet = GetExport(IL2CPP_DOMAIN_GET);
        Exports::AssemblyGetFromDomain = GetExport(IL2CPP_ASSEMBLY_GET_FROM_DOMAIN);
        Exports::ImageGetName = GetExport(IL2CPP_IMAGE_GET_NAME);
        Exports::ImageGetClass = GetExport(IL2CPP_IMAGE_GET_CLASS);
        Exports::ImageGetClassCount = GetExport(IL2CPP_IMAGE_GET_CLASS_COUNT);
        Exports::ClassFromName = GetExport(IL2CPP_CLASS_FROM_NAME);
        Exports::ObjectNew = GetExport(IL2CPP_OBJECT_NEW);
        Exports::ClassGetName = GetExport(IL2CPP_CLASS_GET_NAME);
        Exports::ObjectGetClass = GetExport(IL2CPP_OBJECT_GET_CLASS);
        Exports::ClassIsEnum = GetExport(IL2CPP_CLASS_IS_ENUM);
        Exports::ClassIsInterface = GetExport(IL2CPP_CLASS_IS_INTERFACE);
        Exports::ClassIsInflated = GetExport(IL2CPP_CLASS_IS_INFLATED);
        Exports::ClassIsValueType = GetExport(IL2CPP_CLASS_IS_VALUETYPE);
        Exports::ClassGetNamespace = GetExport(IL2CPP_CLASS_GET_NAMESPACE);
        Exports::MethodFromName = GetExport(IL2CPP_METHOD_FROM_NAME);
        Exports::FieldFromName = GetExport(IL2CPP_FIELD_FROM_NAME);
        Exports::ClassGetMethods = GetExport(IL2CPP_CLASS_GET_METHODS);
        Exports::ClassGetFields = GetExport(IL2CPP_CLASS_GET_FIELDS);
        Exports::ClassArrayElementSize = GetExport(IL2CPP_CLASS_ARRAY_ELEMENT_SIZE);
        Exports::TypeFromClass = GetExport(IL2CPP_TYPE_FROM_CLASS);
        Exports::TypeGetObject = GetExport(IL2CPP_TYPE_GET_OBJECT);
        Exports::ClassEnumBasetype = GetExport(IL2CPP_CLASS_ENUM_BASETYPE);
        Exports::MethodGetName = GetExport(IL2CPP_METHOD_GET_NAME);
        Exports::MethodIsInflated = GetExport(IL2CPP_METHOD_IS_INFLATED);
        Exports::MethodIsInstance = GetExport(IL2CPP_METHOD_IS_INSTANCE);
        Exports::MethodGetFlags = GetExport(IL2CPP_METHOD_GET_FLAGS);
        Exports::MethodGetObject = GetExport(IL2CPP_METHOD_GET_OBJECT);
        Exports::FieldGetFlags = GetExport(IL2CPP_FIELD_GET_FLAGS);
        Exports::FieldGetName = GetExport(IL2CPP_FIELD_GET_NAME);
        Exports::FieldGetOffset = GetExport(IL2CPP_FIELD_GET_OFFSET);
        Exports::FieldGetType = GetExport(IL2CPP_FIELD_GET_TYPE);
        Exports::ClassFromType = GetExport(IL2CPP_CLASS_FROM_TYPE);
        Exports::TypeGetName = GetExport(IL2CPP_TYPE_GET_NAME);
        Exports::RuntimeClassInit = GetExport(IL2CPP_RUNTIME_CLASS_INIT);
        Exports::GetStaticFieldValue = GetExport(IL2CPP_FIELD_STATIC_GET_VALUE);
        Exports::SetStaticFieldValue = GetExport(IL2CPP_FIELD_STATIC_SET_VALUE);
        Exports::MethodGetParamCount = GetExport(IL2CPP_METHOD_GET_PARAM_COUNT);
        Exports::MethodGetParamName = GetExport(IL2CPP_METHOD_GET_PARAM_NAME);
        Exports::MethodGetParamType = GetExport(IL2CPP_METHOD_GET_PARAM_TYPE);
        Exports::ClassGetInterfaces = GetExport(IL2CPP_CLASS_GET_INTERFACES);
        Exports::ClassNestedClasses = GetExport(IL2CPP_CLASS_NESTED_CLASSES);
        Exports::StringNew = GetExport(IL2CPP_STRING_NEW);
        Exports::StringChars = GetExport(IL2CPP_STRING_CHARS);
        Exports::StringLength = GetExport(IL2CPP_STRING_LENGTH);
        Exports::ArrayNew = GetExport(IL2CPP_ARRAY_NEW);
        Exports::ArrayLength = GetExport(IL2CPP_ARRAY_LENGTH);
        Exports::ClassFromSystemType = GetExport(IL2CPP_CLASS_FROM_SYSTEM_TYPE);
        Exports::MethodGetReturnType = GetExport(IL2CPP_METHOD_GET_RETURN_TYPE);
        Exports::ClassGetInstanceSize = GetExport(IL2CPP_CLASS_GET_INSTANCE_SIZE);

        LOG("BNM: Successfully loaded.");

        IL2CPP::Assembly *asmMscorlib = IL2CPP::Domain::Assembly("mscorlib");

        LOG(std::format("mscorlib: 0x{:x}", (uintptr_t)asmMscorlib));

        IL2CPP::Image *imgMscorlib = asmMscorlib->Image();

        LOG(std::format("mscorlib image: 0x{:x}", (uintptr_t)imgMscorlib));

        LOG(imgMscorlib->Name());

        IL2CPP::Assembly *asmAssemblyCSharp = IL2CPP::Domain::Assembly("Assembly-CSharp");
        LOG(std::format("assembly-chsarp: 0x{:x}", (uintptr_t)asmAssemblyCSharp));

        IL2CPP::Image *imgAssemblyCSharp = asmAssemblyCSharp->Image();
        LOG(std::format("assembly-chsarp image: 0x{:x}", (uintptr_t)imgAssemblyCSharp));

        IL2CPP::Class *PixelTime = imgAssemblyCSharp->Class("PixelTime");

        LOG(std::format("PixelTime: 0x{:x}", (uintptr_t)PixelTime));

        IL2CPP::Class *Int32Class = imgMscorlib->Class("System.Int32");

        LOG(std::format("System.Int32: 0x{:x}", (uintptr_t)Int32Class));

        IL2CPP::Object *Int32Object = Int32Class->New();

        LOG(std::format("System.Int32 instance: 0x{:x}", (uintptr_t)Int32Object));

        size_t PixelTime_methods_count = PixelTime->Methods().size();
        size_t PixelTime_fields_count = PixelTime->Fields().size();

        LOG(std::format("{} methods; {} fields", PixelTime_methods_count, PixelTime_fields_count));

        //  0x22ba390

        IL2CPP::Method PixelTime_Update = PixelTime->Method("Update");

        LOG(std::format("PixelTime::Update MethodInfo: 0x{:x}", PixelTime_Update.Handle));

        LOG(std::format("PixelTime::Update Method RVA: 0x{:x} | 0x22ba390", PixelTime_Update.RVA()));

        PixelTime_Update.Invoke<void>();
        IL2CPP::String *str = IL2CPP::String::New("IL2CPP String");
        LOG(str->Content());

        IL2CPP::Array *arr = IL2CPP::Array::New(imgMscorlib->Class("System.String"), 1);
        LOG(std::format("Array: {}", (uintptr_t)arr));
        arr->Set(0, IL2CPP::String::New("sex!!!"));
        LOG(arr->Get<IL2CPP::String *>(0)->Content());

        LOG(PixelTime->ToString());

        IL2CPP::Array *int_arr = IL2CPP::Array::New(imgMscorlib->Class("System.Int32"), 2);

        int_arr->Set(0, IL2CPP::Object::Box("System.Int32", 1488));
        LOG(std::to_string(int_arr->Get<IL2CPP::Object *>(0)->Field("m_value").GetValue<int>()));

        /*
    DumperParameters parameters;
    parameters.ShowIndexes = true;
    Dumper dumper(parameters);
    dumper.Dump();
    */

        /*
        std::vector<IL2CPP::Assembly *> assemblies = IL2CPP::Domain::Assemblies();

        LOG(std::format("assemblies count: {}", assemblies.size()));
        */
    }
}