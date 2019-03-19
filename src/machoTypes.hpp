#pragma once

#include <string>

using cpu_type_t = int;
using cpu_subtype_t = int;

#define CPU_ARCH_ABI64	    0x01000000
#define CPU_TYPE_X86		((cpu_type_t) 7)
#define	CPU_TYPE_X86_64		(CPU_TYPE_X86 | CPU_ARCH_ABI64)

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