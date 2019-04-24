#include "FatMachOBinaryViewType.hpp"

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

template <typename ARCH>
FatMachOBinaryViewType<ARCH>::FatMachOBinaryViewType() :
    BinaryViewType(ARCH::name, ARCH::long_name) { }

Ref<BinaryView> NewParentBinaryView(BinaryView* originalParent, DataBuffer& data)
{
    // Ref<FileMetadata> file_metadata = new FileMetadata();
    BNBinaryView* view = BNCreateBinaryDataViewFromBuffer(originalParent->GetFile()->GetObject(), data.GetBufferObject());
    LogDebug("view = %p", view);
    return new BinaryView(view);
}

template <typename ARCH>
BinaryView* FatMachOBinaryViewType<ARCH>::Create(BinaryView* data)
{
    LogInfo("BVT Create");
    LogDebug("Read header");
    // Look for a fat_arch structure that matches our type
    fat_header header;
    data->Read(&header, 0, sizeof(header));

    header.magic = __builtin_bswap32(header.magic);
    header.nfat_arch = __builtin_bswap32(header.nfat_arch);

    LogDebug("header.magic = %016x", header.magic);
    LogDebug("arch.nfat_arch = %16x", header.nfat_arch);
    fat_arch arch;
    for (unsigned long i = 0; i < header.nfat_arch; i++)
    {
        LogDebug("Reading arch %d", i);
        data->Read(&arch, sizeof(header) + sizeof(arch) * i, sizeof(arch));
        
        // fix the endianness. This looks so dirty
        arch.size = __builtin_bswap32(arch.size);
        arch.offset = __builtin_bswap32(arch.offset);
        arch.cputype = __builtin_bswap32(arch.cputype);
        arch.cpusubtype = __builtin_bswap32(arch.cpusubtype);
        arch.align = __builtin_bswap32(arch.align);

        LogDebug("arch.cputype %08x", arch.cputype);

        if (arch.cputype == ARCH::cputype)
        {
            break;
        }
    }

    if (arch.cputype != ARCH::cputype)
    {
        LogDebug("Couldn't find arch");
        // couldn't find it
        return nullptr;
    }

    auto length = arch.offset + arch.size;
    length += arch.align - (length % arch.align);
    DataBuffer fat_data = data->ReadBuffer(arch.offset, length);
    auto parent = NewParentBinaryView(data, fat_data);
    BNBinaryView* child = BNCreateBinaryViewOfType(BinaryViewType::GetByName("Mach-O")->GetObject(), parent->GetObject());
    return new BinaryView(child);
}

template <typename ARCH>
bool FatMachOBinaryViewType<ARCH>::IsTypeValidForData(BinaryView* data)
{
    LogDebug("Read header");
    // Look for a fat_arch structure that matches our type
    fat_header header;
    data->Read(&header, 0, sizeof(header));

    header.magic = __builtin_bswap32(header.magic);
    header.nfat_arch = __builtin_bswap32(header.nfat_arch);

    if (header.magic != 0xcafebabe)
    {
        return false;
    }

    LogDebug("header.magic = %016x", header.magic);
    LogDebug("arch.nfat_arch = %16x", header.nfat_arch);
    fat_arch arch;
    for (unsigned long i = 0; i < header.nfat_arch; i++)
    {
        LogDebug("Reading arch %d", i);
        data->Read(&arch, sizeof(header) + sizeof(arch) * i, sizeof(arch));
        
        // fix the endianness. This looks so dirty
        arch.size = __builtin_bswap32(arch.size);
        arch.offset = __builtin_bswap32(arch.offset);
        arch.cputype = __builtin_bswap32(arch.cputype);
        arch.cpusubtype = __builtin_bswap32(arch.cpusubtype);
        arch.align = __builtin_bswap32(arch.align);

        LogDebug("arch.cputype %08x", arch.cputype);

        if (arch.cputype == ARCH::cputype)
        {
            break;
        }
    }

    return arch.cputype == ARCH::cputype;
}

template class FatMachOBinaryViewType<mach_o_x86_64>;
template class FatMachOBinaryViewType<mach_o_x86>;
template class FatMachOBinaryViewType<mach_o_aarch64>;
template class FatMachOBinaryViewType<mach_o_armv7>;
template class FatMachOBinaryViewType<mach_o_ppc>;