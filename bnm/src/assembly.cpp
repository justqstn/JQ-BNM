#include "../include/assembly.h"
#include "../include/exportcall.h"
namespace IL2CPP
{
    IL2CPP::Image *Assembly::Image()
    {
        return IL2CPP::ExportCall::AssemblyGetImage((void *)this);
    }
}