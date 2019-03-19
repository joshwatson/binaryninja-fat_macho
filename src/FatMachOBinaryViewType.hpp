#pragma once

#include "binaryninjaapi.h"
#include "machoTypes.hpp"

using namespace BinaryNinja;

template <typename ARCH>
class FatMachOBinaryViewType: public BinaryViewType
{
public:
    FatMachOBinaryViewType();
    virtual BinaryView* Create(BinaryView* data);
    virtual bool IsTypeValidForData(BinaryView* data);
};