#pragma once

#include <string>

using cpu_type_t = int;
using cpu_subtype_t = int;

#define CPU_ARCH_ABI64	    0x01000000
#define CPU_TYPE_X86		((cpu_type_t) 7)
#define	CPU_TYPE_X86_64		(CPU_TYPE_X86 | CPU_ARCH_ABI64)
#define CPU_TYPE_ARM        ((cpu_type_t) 12)
#define CPU_TYPE_ARM64      (CPU_TYPE_ARM | CPU_ARCH_ABI64)
#define CPU_SUBTYPE_ARM_V7  ((cpu_subtype_t) 9)

struct mach_o_x86_64
{
    static const std::string name;
    static const std::string long_name;
    static const cpu_type_t cputype = CPU_TYPE_X86_64;
};

struct mach_o_x86
{
    static const std::string name;
    static const std::string long_name;
    static const cpu_type_t cputype = CPU_TYPE_X86;
};

struct mach_o_aarch64
{
    static const std::string name;
    static const std::string long_name;
    static const cpu_type_t cputype = CPU_TYPE_ARM64;
};

struct mach_o_armv7
{
    static const std::string name;
    static const std::string long_name;
    static const cpu_type_t cputype = CPU_TYPE_ARM;
    static const cpu_subtype_t cpusubtype = CPU_SUBTYPE_ARM_V7;
};