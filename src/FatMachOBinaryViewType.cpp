#include "FatMachOBinaryViewType.hpp"

struct mach_o_x86_64
{
    static const std::string name;
    static const std::string long_name;
    static const cpu_type_t cputype = CPU_TYPE_X86_64;
};

const std::string mach_o_x86_64::name = "Fat Mach-O x86_64";
const std::string mach_o_x86_64::long_name = "Fat Mach-O x86_64";

struct mach_o_x86
{
    static const std::string name;
    static const std::string long_name;
    static const cpu_type_t cputype = CPU_TYPE_X86;
};

const std::string mach_o_x86::name = "Fat Mach-O x86";
const std::string mach_o_x86::long_name = "Fat Mach-O x86";

template <typename ARCH>
FatMachOBinaryViewType<ARCH>::FatMachOBinaryViewType() :
    BinaryViewType(ARCH::name, ARCH::long_name) { }

Ref<BinaryView> NewParentBinaryView(DataBuffer& data)
{
    Ref<FileMetadata> file_metadata = new FileMetadata();
    BNBinaryView* view = BNCreateBinaryDataViewFromBuffer(file_metadata->GetObject(), data.GetBufferObject());
    LogDebug("view = %p", view);
    return new BinaryView(view);
}

template <typename ARCH>
BinaryView* FatMachOBinaryViewType<ARCH>::Create(BinaryView* data)
{
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

    auto types = GetViewTypes();

    LogDebug("Looking for Mach-O BinaryViewType");
    for (auto &t : types)
    {
        LogDebug("%s", t->GetName().c_str());
        if (t->GetName().compare("Mach-O") == 0)
        {
            auto length = arch.offset + arch.size;
            length += arch.align - (length % arch.align);
            DataBuffer fat_data = data->ReadBuffer(arch.offset, length);
            auto parent = NewParentBinaryView(fat_data);
            BNBinaryView *view = BNCreateBinaryViewOfType(t->GetObject(), parent->GetObject());
            if (!view)
            {
                return nullptr;
            }
            return new BinaryView(view);
        }
    }

    return nullptr;
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