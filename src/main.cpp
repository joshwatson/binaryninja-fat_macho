#include "binaryninjaapi.h"
#include "FatMachOBinaryViewType.hpp"

struct mach_o_x86_64;
struct mach_o_x86;

extern "C"
{
    BINARYNINJAPLUGIN void CorePluginDependencies()
    {
        // Make sure we load after the original mach-o plugin loads
        AddRequiredPluginDependency("platform_mac");
    }

    BINARYNINJAPLUGIN bool CorePluginInit()
    {
        BinaryViewType::Register(new FatMachOBinaryViewType<mach_o_x86_64>());
        BinaryViewType::Register(new FatMachOBinaryViewType<mach_o_x86>());
        return true;
    }
}