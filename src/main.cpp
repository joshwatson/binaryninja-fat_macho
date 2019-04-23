#include "binaryninjaapi.h"
#include "FatMachOBinaryViewType.hpp"
#include "machoTypes.hpp"

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
        BinaryViewType::Register(new FatMachOBinaryViewType<mach_o_aarch64>());
        BinaryViewType::Register(new FatMachOBinaryViewType<mach_o_armv7>());
        return true;
    }
}