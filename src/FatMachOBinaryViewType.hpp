#pragma once

#include "binaryninjaapi.h"

using namespace BinaryNinja;

using cpu_type_t = int;
using cpu_subtype_t = int;

#define CPU_ARCH_ABI64	    0x01000000
#define CPU_TYPE_X86		((cpu_type_t) 7)
#define	CPU_TYPE_X86_64		(CPU_TYPE_X86 | CPU_ARCH_ABI64)

template <typename ARCH>
class FatMachOBinaryViewType: public BinaryViewType
{
public:
    FatMachOBinaryViewType();
    virtual BinaryView* Create(BinaryView* data);
    virtual bool IsTypeValidForData(BinaryView* data);
};

struct fat_header
{
    uint32_t magic;
    uint32_t nfat_arch;
};

struct fat_arch
{
    cpu_type_t cputype;
    cpu_subtype_t cpusubtype;
    uint32_t offset;
    uint32_t size;
    uint32_t align;
};