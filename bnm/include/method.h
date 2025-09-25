#pragma once

#include <cstdint>
#include <format>
#include <vector>

#include "type.h"
#include "defines.h"
#include "dumper.h"

namespace IL2CPP
{
    struct Parameter
    {
        const char *Name;
        IL2CPP::Type *Type;
    };

    class Method
    {
    public:
        Method(uintptr_t Handle, uintptr_t ParentInstance = 0);

        enum class Attributes
        {
            MemberAccessMask = 0x0007,
            PrivateScope = 0x0000,
            Private = 0x0001,
            FamilyAndAssembly = 0x0002,
            Assembly = 0x0003,
            Family = 0x0004,
            FamilyOrAssembly = 0x0005,
            Public = 0x0006,
            Static = 0x0010,
            Final = 0x0020,
            Virtual = 0x0040,
            HideBySig = 0x0080,
            CheckAccessOnOverride = 0x0200,
            VtableLayoutMask = 0x0100,
            ReuseSlot = 0x0000,
            NewSlot = 0x0100,
            Abstract = 0x0400,
            SpecialName = 0x0800,
            PinvokeImpl = 0x2000,
            UnmanagedExport = 0x0008,
            RTSpecialName = 0x1000,
            ReservedMask = 0xd000,
            HasSecurity = 0x4000,
            RequireSecObject = 0x8000
        };

        // @return Method return type
        IL2CPP::Type *ReturnType();
        // @return Method name
        const char *Name();
        // @return Naive method address (Virutal Address)
        uintptr_t VA();
        // @return Native method offset (Relative Virtual Address)
        uintptr_t RVA();
        // Checks is it inflated method
        bool isInflated();
        // Checks is it static method
        bool isStatic();
        // @return Method object
        IL2CPP::Object *Object();
        // @note WIP
        std::vector<IL2CPP::Class *> Generics();
        // Creates generic method @return Method object
        IL2CPP::Method Inflate(std::vector<IL2CPP::Class *> classes);
        // @return Parameters count
        uint32_t ParametersCount();
        // @return Vector of parameters
        std::vector<Parameter> Parameters();
        std::string ToString(const DumperParameters &Parameters = {}, int Index = -1);

        // Invokes method with given parameters
        template <typename T, typename... TArgs>
        T Invoke(TArgs... Args)
        {
            if (this->isStatic())
            {
                if (this->ParentInstance != 0)
                {
                    LOG(std::format("Couldn't invoke static method \"{}\": the method was received from IL2CPP::Object, not IL2CPP::Class.", this->Name()));
                    return (T)0;
                }

                if (this->isInflated())
                    return ((T (*)(TArgs..., void *))(this->VA()))(Args..., (void *)this->Handle);

                return ((T (*)(TArgs...))(this->VA()))(Args...);
            }
            else
            {
                if (this->ParentInstance == 0)
                {
                    LOG(std::format("Couldn't invoke non-static method \"{}\": the method was received from IL2CPP::Class, not IL2CPP::Object.", this->Name()));
                    return (T)0;
                }

                if (this->isInflated())
                    return ((T (*)(void *, TArgs..., void *))(this->VA()))((void *)this->ParentInstance, Args..., (void *)this->Handle);

                return ((T (*)(void *, TArgs...))(this->VA()))((void *)this->ParentInstance, Args...);
            }
        }

        // Invokes method with given parameters
        template <typename T, typename... TArgs>
        T operator()(TArgs... Args)
        {
            if (this->isStatic())
            {
                if (this->ParentInstance != 0)
                {
                    LOG(std::format("Couldn't invoke static method \"{}\": the method was received from IL2CPP::Object, not IL2CPP::Class.", this->Name()));
                    return (T)0;
                }

                if (this->isInflated())
                    return ((T (*)(TArgs..., void *))(this->VA()))(Args..., (void *)this->Handle);

                return ((T (*)(TArgs...))(this->VA()))(Args...);
            }
            else
            {
                if (this->ParentInstance == 0)
                {
                    LOG(std::format("Couldn't invoke non-static method \"{}\": the method was received from IL2CPP::Class, not IL2CPP::Object.", this->Name()));
                    return (T)0;
                }

                if (this->isInflated())
                    return ((T (*)(void *, TArgs..., void *))(this->VA()))((void *)this->ParentInstance, Args..., (void *)this->Handle);

                return ((T (*)(void *, TArgs...))(this->VA()))((void *)this->ParentInstance, Args...);
            }
        }

        // Pointer to Field
        uintptr_t Handle;
        // Pointer to Object (zero if it's static)
        uintptr_t ParentInstance;
    };

}