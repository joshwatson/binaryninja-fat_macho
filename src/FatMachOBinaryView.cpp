#include "FatMachOBinaryView.hpp"
#include <exception>

template <typename ARCH>
FatMachOBinaryView<ARCH>::FatMachOBinaryView(BNBinaryView *view) : 
    BinaryView(view), m_InternalView(nullptr) { 
        LogInfo("In empty constructor");
    }

template <typename ARCH>
FatMachOBinaryView<ARCH>::FatMachOBinaryView(const std::string& typeName, FileMetadata* file, BinaryView* parentView) :
    BinaryView(typeName, file, parentView)
{
    LogInfo("FatMacOBinaryView(%p, %p, %p)", &typeName, file, parentView);
    auto machoType = BinaryViewType::GetByName("Mach-O");
    if (machoType->m_object == nullptr)
    {
        throw std::runtime_error("machoType is null");
    }

    m_InternalView = reinterpret_cast<FatMachOBinaryView<ARCH>*>(machoType->Create(parentView));
    if (static_cast<BinaryView*>(m_InternalView) == nullptr)
    {
        throw std::runtime_error("m_InternalView is null");
    }

    LogInfo("After create");

    m_object = m_InternalView->m_object;
    uint64_t isInlined = ((uint64_t)*(void**)m_object+0x18);
    bool *isInlined_ = (bool*)isInlined;
    *isInlined_ = true;
    uint64_t str = (uint64_t)isInlined + 0x10; //(uint64_t)m_object + 0x28;
    const char **str_ = (const char**)str;
    *str_ = ARCH::long_name.c_str();
    //*str = (uint64_t)(ARCH::long_name.c_str());
    LogInfo("%s %d", str, *(bool*)isInlined);
    // BNNewViewReference(m_object);
}

template <typename ARCH>
bool FatMachOBinaryView<ARCH>::Init()
{
    LogInfo("In Init");
    // if (!m_InternalView->Init())
    // {
    //     return false;
    // }

    // BNSetDefaultArchitecture(GetObject(), m_InternalView->GetDefaultArchitecture()->GetObject());
    // BNSetDefaultPlatform(GetObject(), m_InternalView->GetDefaultPlatform()->GetObject());

    // for (auto& segment : m_InternalView->GetSegments())
    // {
    //     BNAddAutoSegment(GetObject(), segment->GetStart(), segment->GetLength(), segment->GetDataOffset(), segment->GetDataLength(), segment->GetFlags());
    // }

    // for (auto& section : m_InternalView->GetSections())
    // {
    //     BNAddAutoSection(
    //         m_object, section->GetName().c_str(), section->GetStart(),
    //         section->GetLength(), section->GetSemantics(), section->GetType().c_str(),
    //         section->GetAlignment(), section->GetEntrySize(), section->GetLinkedSection().c_str(),
    //         section->GetInfoSection().c_str(), section->GetInfoData()
    //     );
    // }

    // auto entryPointFunction = m_InternalView->GetAnalysisEntryPoint();

    // LogInfo("Internal View Entry Point: %X", entryPointFunction->GetStart());

    // BNAddEntryPointForAnalysis(m_object, GetDefaultPlatform()->GetObject(), entryPointFunction->GetStart());

    // LogInfo("After SetDefaultArchitecture for %s", typeid(ARCH).name());

    return true;
}

template <typename ARCH>
size_t FatMachOBinaryView<ARCH>::PerformRead(void* dest, uint64_t offset, size_t len)
{
    return m_InternalView->PerformRead(dest, offset, len);
}

template <typename ARCH>
size_t FatMachOBinaryView<ARCH>::PerformWrite(uint64_t offset, const void* data, size_t len)
{
    return m_InternalView->PerformWrite(offset, data, len);
}

template <typename ARCH>
size_t FatMachOBinaryView<ARCH>::PerformInsert(uint64_t offset, const void* data, size_t len)
{
    return m_InternalView->PerformInsert(offset, data, len);
}

template <typename ARCH>
size_t FatMachOBinaryView<ARCH>::PerformRemove(uint64_t offset, uint64_t len)
{
    return m_InternalView->PerformRemove(offset, len);
}

template <typename ARCH>
BNModificationStatus FatMachOBinaryView<ARCH>::PerformGetModification(uint64_t offset)
{
    return m_InternalView->PerformGetModification(offset);
}

template <typename ARCH>
bool FatMachOBinaryView<ARCH>::PerformIsValidOffset(uint64_t offset)
{
    return m_InternalView->PerformIsValidOffset(offset);
}

template <typename ARCH>
bool FatMachOBinaryView<ARCH>::PerformIsOffsetReadable(uint64_t offset)
{
    return m_InternalView->PerformIsOffsetReadable(offset);
}

template <typename ARCH>
bool FatMachOBinaryView<ARCH>::PerformIsOffsetWritable(uint64_t offset)
{
    return m_InternalView->PerformIsOffsetWritable(offset);
}

template <typename ARCH>
bool FatMachOBinaryView<ARCH>::PerformIsOffsetExecutable(uint64_t offset)
{
    return m_InternalView->PerformIsOffsetExecutable(offset);
}

template <typename ARCH>
bool FatMachOBinaryView<ARCH>::PerformIsOffsetBackedByFile(uint64_t offset)
{
    return m_InternalView->PerformIsOffsetBackedByFile(offset);
}

template <typename ARCH>
uint64_t FatMachOBinaryView<ARCH>::PerformGetNextValidOffset(uint64_t offset)
{
    return m_InternalView->PerformGetNextValidOffset(offset);
}

template <typename ARCH>
uint64_t FatMachOBinaryView<ARCH>::PerformGetStart() const
{
    return m_InternalView->PerformGetStart();
}

template <typename ARCH>
uint64_t FatMachOBinaryView<ARCH>::PerformGetLength() const
{
    return m_InternalView->PerformGetLength();
}

template <typename ARCH>
uint64_t FatMachOBinaryView<ARCH>::PerformGetEntryPoint() const
{
    return m_InternalView->PerformGetEntryPoint();
}

template <typename ARCH>
bool FatMachOBinaryView<ARCH>::PerformIsExecutable() const
{
    return m_InternalView->PerformIsExecutable();
}

template <typename ARCH>
BNEndianness FatMachOBinaryView<ARCH>::PerformGetDefaultEndianness() const
{
    return m_InternalView->PerformGetDefaultEndianness();
}

template <typename ARCH>
bool FatMachOBinaryView<ARCH>::PerformIsRelocatable() const
{
    return m_InternalView->PerformIsRelocatable();
}

template <typename ARCH>
size_t FatMachOBinaryView<ARCH>::PerformGetAddressSize() const
{
    return m_InternalView->PerformGetAddressSize();
}

template <typename ARCH>
bool FatMachOBinaryView<ARCH>::PerformSave(FileAccessor* file)
{
    return m_InternalView->PerformSave(file);
}

template <typename ARCH>
std::string FatMachOBinaryView<ARCH>::GetTypeName() const
{
    return std::string(ARCH::long_name);
}

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::PerformDefineRelocation(Architecture* arch, BNRelocationInfo& info, Ref<Symbol> sym, uint64_t reloc)
// {
//     reinterpret_cast<FatMachOBinaryView<ARCH>*>(m_InternalView)->PerformDefineRelocation(arch, info, sym, reloc);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::NotifyDataWritten(uint64_t offset, size_t len)
// {
//     reinterpret_cast<FatMachOBinaryView<ARCH>*>(m_InternalView)->NotifyDataWritten(offset, len);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::NotifyDataInserted(uint64_t offset, size_t len)
// {
//     m_InternalView->NotifyDataInserted(offset, len);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::NotifyDataRemoved(uint64_t offset, uint64_t len)
// {
//     reinterpret_cast<FatMachOBinaryView<ARCH>*>(m_InternalView)->NotifyDataRemoved(offset, len);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsModified() const
// {
// 	return m_InternalView->IsModified();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsAnalysisChanged() const
// {
//     return m_InternalView->IsAnalysisChanged();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsBackedByDatabase() const
// {
//     return m_InternalView->IsBackedByDatabase();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::CreateDatabase(const std::string& path)
// {
// 	return m_InternalView->CreateDatabase(path);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::CreateDatabase(const std::string& path,
//     const std::function<void(size_t progress, size_t total)>& progressCallback)
// {
//     return m_InternalView->CreateDatabase(path, progressCallback);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::SaveAutoSnapshot()
// {
// 	return m_InternalView->SaveAutoSnapshot();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::SaveAutoSnapshot(const std::function<void(size_t progress, size_t total)>& progressCallback)
// {
//     return m_InternalView->SaveAutoSnapshot(progressCallback);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::BeginUndoActions()
// {
// 	m_InternalView->BeginUndoActions();
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::AddUndoAction(UndoAction* action)
// {
// 	m_InternalView->AddUndoAction(action);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::CommitUndoActions()
// {
// 	m_InternalView->CommitUndoActions();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::Undo()
// {
// 	return m_InternalView->Undo();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::Redo()
// {
// 	return m_InternalView->Redo();
// }

// template <typename ARCH>
// std::string FatMachOBinaryView<ARCH>::GetCurrentView()
// {
// 	return m_InternalView->GetCurrentView();
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetCurrentOffset()
// {
// 	return m_InternalView->GetCurrentOffset();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::Navigate(const std::string& view, uint64_t offset)
// {
// 	return m_InternalView->Navigate(view, offset);
// }

// template <typename ARCH>
// size_t FatMachOBinaryView<ARCH>::Read(void* dest, uint64_t offset, size_t len)
// {
// 	return m_InternalView->Read(dest, offset, len);
// }

// template <typename ARCH>
// DataBuffer FatMachOBinaryView<ARCH>::ReadBuffer(uint64_t offset, size_t len)
// {
// 	return m_InternalView->ReadBuffer(offset, len);
// }

// template <typename ARCH>
// size_t FatMachOBinaryView<ARCH>::Write(uint64_t offset, const void* data, size_t len)
// {
// 	return m_InternalView->Write(offset, data, len);
// }

// template <typename ARCH>
// size_t FatMachOBinaryView<ARCH>::WriteBuffer(uint64_t offset, const DataBuffer& data)
// {
// 	return m_InternalView->WriteBuffer(offset, data);
// }

// template <typename ARCH>
// size_t FatMachOBinaryView<ARCH>::Insert(uint64_t offset, const void* data, size_t len)
// {
// 	return m_InternalView->Insert(offset, data, len);
// }

// template <typename ARCH>
// size_t FatMachOBinaryView<ARCH>::InsertBuffer(uint64_t offset, const DataBuffer& data)
// {
// 	return m_InternalView->InsertBuffer(offset, data);
// }

// template <typename ARCH>
// size_t FatMachOBinaryView<ARCH>::Remove(uint64_t offset, uint64_t len)
// {
// 	return m_InternalView->Remove(offset, len);
// }

// template <typename ARCH>
// BNModificationStatus FatMachOBinaryView<ARCH>::GetModification(uint64_t offset)
// {
// 	return m_InternalView->GetModification(offset);
// }

// template <typename ARCH>
// std::vector<BNModificationStatus> FatMachOBinaryView<ARCH>::GetModification(uint64_t offset, size_t len)
// {
// 	return m_InternalView->GetModification(offset, len);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsValidOffset(uint64_t offset) const
// {
// 	return m_InternalView->IsValidOffset(offset);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsOffsetReadable(uint64_t offset) const
// {
// 	return m_InternalView->IsOffsetReadable(offset);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsOffsetWritable(uint64_t offset) const
// {
// 	return m_InternalView->IsOffsetWritable(offset);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsOffsetExecutable(uint64_t offset) const
// {
// 	return m_InternalView->IsOffsetExecutable(offset);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsOffsetBackedByFile(uint64_t offset) const
// {
// 	return m_InternalView->IsOffsetBackedByFile(offset);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsOffsetCodeSemantics(uint64_t offset) const
// {
// 	return m_InternalView->IsOffsetCodeSemantics(offset);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsOffsetWritableSemantics(uint64_t offset) const
// {
// 	return m_InternalView->IsOffsetWritableSemantics(offset);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsOffsetExternSemantics(uint64_t offset) const
// {
// 	return m_InternalView->IsOffsetExternSemantics(offset);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetNextValidOffset(uint64_t offset) const
// {
// 	return m_InternalView->GetNextValidOffset(offset);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetStart() const
// {
// 	return m_InternalView->GetStart();
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetEnd() const
// {
// 	return m_InternalView->GetEnd();
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetLength() const
// {
// 	return m_InternalView->GetLength();
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetEntryPoint() const
// {
// 	return m_InternalView->GetEntryPoint();
// }

// template <typename ARCH>
// Ref<Architecture> FatMachOBinaryView<ARCH>::GetDefaultArchitecture() const
// {
// 	LogInfo("GetDefaultArchitecture");
// return m_InternalView->GetDefaultArchitecture();
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::SetDefaultArchitecture(Architecture* arch)
// {
// 	m_InternalView->SetDefaultArchitecture(arch);
// }

// template <typename ARCH>
// Ref<Platform> FatMachOBinaryView<ARCH>::GetDefaultPlatform() const
// {
// 	return m_InternalView->GetDefaultPlatform();
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::SetDefaultPlatform(Platform* platform)
// {
// 	m_InternalView->SetDefaultPlatform(platform);
// }

// template <typename ARCH>
// BNEndianness FatMachOBinaryView<ARCH>::GetDefaultEndianness() const
// {
// 	return m_InternalView->GetDefaultEndianness();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsRelocatable() const
// {
// 	return m_InternalView->IsRelocatable();
// }

// template <typename ARCH>
// size_t FatMachOBinaryView<ARCH>::GetAddressSize() const
// {
// 	return m_InternalView->GetAddressSize();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsExecutable() const
// {
// 	return m_InternalView->IsExecutable();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::Save(FileAccessor* file)
// {
// 	return m_InternalView->Save(file);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::Save(const std::string& path)
// {
// 	return m_InternalView->Save(path);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::DefineRelocation(Architecture* arch, BNRelocationInfo& info, uint64_t target, uint64_t reloc)
// {
// 	m_InternalView->DefineRelocation(arch, info, target, reloc);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::DefineRelocation(Architecture* arch, BNRelocationInfo& info, Ref<Symbol> target, uint64_t reloc)
// {
// 	m_InternalView->DefineRelocation(arch, info, target, reloc);
// }

// template <typename ARCH>
// std::vector<std::pair<uint64_t, uint64_t>> FatMachOBinaryView<ARCH>::GetRelocationRanges() const
// {
// 	return m_InternalView->GetRelocationRanges();
// }

// template <typename ARCH>
// std::vector<std::pair<uint64_t, uint64_t>> FatMachOBinaryView<ARCH>::GetRelocationRangesAtAddress(uint64_t addr) const
// {
// 	return m_InternalView->GetRelocationRangesAtAddress(addr);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::RegisterNotification(BinaryDataNotification* notify)
// {
// 	m_InternalView->RegisterNotification(notify);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::UnregisterNotification(BinaryDataNotification* notify)
// {
// 	m_InternalView->UnregisterNotification(notify);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::AddAnalysisOption(const std::string& name)
// {
// 	m_InternalView->AddAnalysisOption(name);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::AddFunctionForAnalysis(Platform* platform, uint64_t addr)
// {
// 	m_InternalView->AddFunctionForAnalysis(platform, addr);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::AddEntryPointForAnalysis(Platform* platform, uint64_t start)
// {
// 	m_InternalView->AddEntryPointForAnalysis(platform, start);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::RemoveAnalysisFunction(Function* func)
// {
// 	m_InternalView->RemoveAnalysisFunction(func);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::CreateUserFunction(Platform* platform, uint64_t start)
// {
// 	m_InternalView->CreateUserFunction(platform, start);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::RemoveUserFunction(Function* func)
// {
// 	m_InternalView->RemoveUserFunction(func);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::UpdateAnalysisAndWait()
// {
// 	m_InternalView->UpdateAnalysisAndWait();
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::UpdateAnalysis()
// {
// 	m_InternalView->UpdateAnalysis();
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::AbortAnalysis()
// {
// 	return m_InternalView->AbortAnalysis();
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::DefineDataVariable(uint64_t addr, const Confidence<Ref<Type>>& type)
// {
// 	return m_InternalView->DefineDataVariable(addr, type);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::DefineUserDataVariable(uint64_t addr, const Confidence<Ref<Type>>& type)
// {
// 	return m_InternalView->DefineUserDataVariable(addr, type);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::UndefineDataVariable(uint64_t addr)
// {
// 	return m_InternalView->UndefineDataVariable(addr);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::UndefineUserDataVariable(uint64_t addr)
// {
// 	return m_InternalView->UndefineUserDataVariable(addr);
// }

// template <typename ARCH>
// std::map<uint64_t, DataVariable> FatMachOBinaryView<ARCH>::GetDataVariables()
// {
// 	return m_InternalView->GetDataVariables();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::GetDataVariableAtAddress(uint64_t addr, DataVariable& var)
// {
// 	return m_InternalView->GetDataVariableAtAddress(addr,var);
// }

// template <typename ARCH>
// std::vector<Ref<Function>> FatMachOBinaryView<ARCH>::GetAnalysisFunctionList()
// {
// 	return m_InternalView->GetAnalysisFunctionList();
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::HasFunctions() const
// {
// 	return m_InternalView->HasFunctions();
// }

// template <typename ARCH>
// Ref<Function> FatMachOBinaryView<ARCH>::GetAnalysisFunction(Platform* platform, uint64_t addr)
// {
// 	return m_InternalView->GetAnalysisFunction(platform, addr);
// }

// template <typename ARCH>
// Ref<Function> FatMachOBinaryView<ARCH>::GetRecentAnalysisFunctionForAddress(uint64_t addr)
// {
// 	return m_InternalView->GetRecentAnalysisFunctionForAddress(addr);
// }

// template <typename ARCH>
// std::vector<Ref<Function>> FatMachOBinaryView<ARCH>::GetAnalysisFunctionsForAddress(uint64_t addr)
// {
// 	return m_InternalView->GetAnalysisFunctionsForAddress(addr);
// }

// template <typename ARCH>
// Ref<Function> FatMachOBinaryView<ARCH>::GetAnalysisEntryPoint()
// {
// 	return m_InternalView->GetAnalysisEntryPoint();
// }

// template <typename ARCH>
// Ref<BasicBlock> FatMachOBinaryView<ARCH>::GetRecentBasicBlockForAddress(uint64_t addr)
// {
// 	return m_InternalView->GetRecentBasicBlockForAddress(addr);
// }

// template <typename ARCH>
// std::vector<Ref<BasicBlock>> FatMachOBinaryView<ARCH>::GetBasicBlocksForAddress(uint64_t addr)
// {
// 	return m_InternalView->GetBasicBlocksForAddress(addr);
// }

// template <typename ARCH>
// std::vector<Ref<BasicBlock>> FatMachOBinaryView<ARCH>::GetBasicBlocksStartingAtAddress(uint64_t addr)
// {
// 	return m_InternalView->GetBasicBlocksStartingAtAddress(addr);
// }

// template <typename ARCH>
// std::vector<ReferenceSource> FatMachOBinaryView<ARCH>::GetCodeReferences(uint64_t addr)
// {
// 	return m_InternalView->GetCodeReferences(addr);
// }

// template <typename ARCH>
// std::vector<ReferenceSource> FatMachOBinaryView<ARCH>::GetCodeReferences(uint64_t addr, uint64_t len)
// {
// 	return m_InternalView->GetCodeReferences(addr, len);
// }

// template <typename ARCH>
// Ref<Symbol> FatMachOBinaryView<ARCH>::GetSymbolByAddress(uint64_t addr, const NameSpace& nameSpace)
// {
//     return m_InternalView->GetSymbolByAddress(addr, nameSpace);
// }

// template <typename ARCH>
// Ref<Symbol> FatMachOBinaryView<ARCH>::GetSymbolByRawName(const std::string& name, const NameSpace& nameSpace)
// {
//     return m_InternalView->GetSymbolByRawName(name, nameSpace);
// }

// template <typename ARCH>
// std::vector<Ref<Symbol>> FatMachOBinaryView<ARCH>::GetSymbolsByName(const std::string& name, const NameSpace& nameSpace)
// {
//     return m_InternalView->GetSymbolsByName(name, nameSpace);
// }

// template <typename ARCH>
// std::vector<Ref<Symbol>> FatMachOBinaryView<ARCH>::GetSymbols(const NameSpace& nameSpace)
// {
//     return m_InternalView->GetSymbols(nameSpace);
// }

// template <typename ARCH>
// std::vector<Ref<Symbol>> FatMachOBinaryView<ARCH>::GetSymbols(uint64_t start, uint64_t len, const NameSpace& nameSpace)
// {
//     return m_InternalView->GetSymbols(start, len, nameSpace);
// }

// template <typename ARCH>
// std::vector<Ref<Symbol>> FatMachOBinaryView<ARCH>::GetSymbolsOfType(BNSymbolType type, const NameSpace& nameSpace)
// {
//     return m_InternalView->GetSymbolsOfType(type, nameSpace);
// }

// template <typename ARCH>
// std::vector<Ref<Symbol>> FatMachOBinaryView<ARCH>::GetSymbolsOfType(BNSymbolType type, uint64_t start, uint64_t len, const NameSpace& nameSpace)
// {
//     return m_InternalView->GetSymbolsOfType(type, start, len, nameSpace);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::DefineAutoSymbol(Ref<Symbol> sym)
// {
// 	return m_InternalView->DefineAutoSymbol(sym);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::DefineAutoSymbolAndVariableOrFunction(Ref<Platform> platform, Ref<Symbol> sym, Ref<Type> type)
// {
// 	return m_InternalView->DefineAutoSymbolAndVariableOrFunction(platform, sym, type);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::UndefineAutoSymbol(Ref<Symbol> sym)
// {
// 	return m_InternalView->UndefineAutoSymbol(sym);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::DefineUserSymbol(Ref<Symbol> sym)
// {
// 	return m_InternalView->DefineUserSymbol(sym);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::UndefineUserSymbol(Ref<Symbol> sym)
// {
// 	return m_InternalView->UndefineUserSymbol(sym);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::DefineImportedFunction(Ref<Symbol> importAddressSym, Ref<Function> func)
// {
// 	return m_InternalView->DefineImportedFunction(importAddressSym, func);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsNeverBranchPatchAvailable(Architecture* arch, uint64_t addr)
// {
// 	return m_InternalView->IsNeverBranchPatchAvailable(arch, addr);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsAlwaysBranchPatchAvailable(Architecture* arch, uint64_t addr)
// {
// 	return m_InternalView->IsAlwaysBranchPatchAvailable(arch, addr);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsInvertBranchPatchAvailable(Architecture* arch, uint64_t addr)
// {
// 	return m_InternalView->IsInvertBranchPatchAvailable(arch, addr);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsSkipAndReturnZeroPatchAvailable(Architecture* arch, uint64_t addr)
// {
// 	return m_InternalView->IsSkipAndReturnZeroPatchAvailable(arch, addr);
// }

// template <typename ARCH>
// bool IsSkipAndReturnValuePatchAvailable(Architecture* arch, uint64_t addr);

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::ConvertToNop(Architecture* arch, uint64_t addr)
// {
// 	return m_InternalView->ConvertToNop(arch, addr);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::AlwaysBranch(Architecture* arch, uint64_t addr)
// {
// 	return m_InternalView->AlwaysBranch(arch, addr);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::InvertBranch(Architecture* arch, uint64_t addr)
// {
// 	return m_InternalView->InvertBranch(arch, addr);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::SkipAndReturnValue(Architecture* arch, uint64_t addr, uint64_t value)
// {
//     return m_InternalView->SkipAndReturnValue(arch, addr, value);
// }

// template <typename ARCH>
// size_t FatMachOBinaryView<ARCH>::GetInstructionLength(Architecture* arch, uint64_t addr)
// {
//     return m_InternalView->GetInstructionLength(arch, addr);
// }

// template <typename ARCH>
// std::vector<BNStringReference> FatMachOBinaryView<ARCH>::GetStrings()
// {
// 	return m_InternalView->GetStrings();
// }

// template <typename ARCH>
// std::vector<BNStringReference> FatMachOBinaryView<ARCH>::GetStrings(uint64_t start, uint64_t len)
// {
// 	return m_InternalView->GetStrings(start, len);
// }

// template <typename ARCH>
// Ref<AnalysisCompletionEvent> FatMachOBinaryView<ARCH>::AddAnalysisCompletionEvent(const std::function<void()>& callback)
// {
//     return m_InternalView->AddAnalysisCompletionEvent(callback);
// }

// template <typename ARCH>
// AnalysisInfo FatMachOBinaryView<ARCH>::GetAnalysisInfo()
// {
// 	return m_InternalView->GetAnalysisInfo();
// }

// template <typename ARCH>
// BNAnalysisProgress FatMachOBinaryView<ARCH>::GetAnalysisProgress()
// {
// 	return m_InternalView->GetAnalysisProgress();
// }

// template <typename ARCH>
// Ref<BackgroundTask> FatMachOBinaryView<ARCH>::GetBackgroundAnalysisTask()
// {
// 	return m_InternalView->GetBackgroundAnalysisTask();
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetNextFunctionStartAfterAddress(uint64_t addr)
// {
// 	return m_InternalView->GetNextFunctionStartAfterAddress(addr);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetNextBasicBlockStartAfterAddress(uint64_t addr)
// {
// 	return m_InternalView->GetNextBasicBlockStartAfterAddress(addr);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetNextDataAfterAddress(uint64_t addr)
// {
// 	return m_InternalView->GetNextDataAfterAddress(addr);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetNextDataVariableAfterAddress(uint64_t addr)
// {
// 	return m_InternalView->GetNextDataVariableAfterAddress(addr);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetPreviousFunctionStartBeforeAddress(uint64_t addr)
// {
// 	return m_InternalView->GetPreviousFunctionStartBeforeAddress(addr);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetPreviousBasicBlockStartBeforeAddress(uint64_t addr)
// {
// 	return m_InternalView->GetPreviousBasicBlockStartBeforeAddress(addr);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetPreviousBasicBlockEndBeforeAddress(uint64_t addr)
// {
// 	return m_InternalView->GetPreviousBasicBlockEndBeforeAddress(addr);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetPreviousDataBeforeAddress(uint64_t addr)
// {
// 	return m_InternalView->GetPreviousDataBeforeAddress(addr);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetPreviousDataVariableBeforeAddress(uint64_t addr)
// {
// 	return m_InternalView->GetPreviousDataVariableBeforeAddress(addr);
// }

// template <typename ARCH>
// LinearDisassemblyPosition FatMachOBinaryView<ARCH>::GetLinearDisassemblyPositionForAddress(uint64_t addr, DisassemblySettings* settings)
// {
// 	return m_InternalView->GetLinearDisassemblyPositionForAddress(addr, settings);
// }

// template <typename ARCH>
// std::vector<LinearDisassemblyLine> FatMachOBinaryView<ARCH>::GetPreviousLinearDisassemblyLines(LinearDisassemblyPosition& pos,
//     DisassemblySettings* settings)
// {
// 	return m_InternalView->GetPreviousLinearDisassemblyLines(pos, settings);
// }

// template <typename ARCH>
// std::vector<LinearDisassemblyLine> FatMachOBinaryView<ARCH>::GetNextLinearDisassemblyLines(LinearDisassemblyPosition& pos,
//     DisassemblySettings* settings)
// {
// 	return m_InternalView->GetNextLinearDisassemblyLines(pos, settings);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::ParseTypeString(const std::string& text, QualifiedNameAndType& result, std::string& errors)
// {
// 	return m_InternalView->ParseTypeString(text, result, errors);
// }

// template <typename ARCH>
// std::map<QualifiedName, Ref<Type>> FatMachOBinaryView<ARCH>::GetTypes()
// {
// 	return m_InternalView->GetTypes();
// }

// template <typename ARCH>
// Ref<Type> FatMachOBinaryView<ARCH>::GetTypeByName(const QualifiedName& name)
// {
// 	return m_InternalView->GetTypeByName(name);
// }

// template <typename ARCH>
// Ref<Type> FatMachOBinaryView<ARCH>::GetTypeById(const std::string& id)
// {
// 	return m_InternalView->GetTypeById(id);
// }

// template <typename ARCH>
// std::string FatMachOBinaryView<ARCH>::GetTypeId(const QualifiedName& name)
// {
// 	return m_InternalView->GetTypeId(name);
// }

// template <typename ARCH>
// QualifiedName FatMachOBinaryView<ARCH>::GetTypeNameById(const std::string& id)
// {
// 	return m_InternalView->GetTypeNameById(id);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::IsTypeAutoDefined(const QualifiedName& name)
// {
// 	return m_InternalView->IsTypeAutoDefined(name);
// }

// template <typename ARCH>
// QualifiedName FatMachOBinaryView<ARCH>::DefineType(const std::string& id, const QualifiedName& defaultName, Ref<Type> type)
// {
//     return m_InternalView->DefineType(id, defaultName, type);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::DefineUserType(const QualifiedName& name, Ref<Type> type)
// {
// 	return m_InternalView->DefineUserType(name, type);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::UndefineType(const std::string& id)
// {
// 	return m_InternalView->UndefineType(id);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::UndefineUserType(const QualifiedName& name)
// {
// 	return m_InternalView->UndefineUserType(name);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::RenameType(const QualifiedName& oldName, const QualifiedName& newName)
// {
// 	return m_InternalView->RenameType(oldName, newName);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::RegisterPlatformTypes(Platform* platform)
// {
// 	return m_InternalView->RegisterPlatformTypes(platform);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::FindNextData(uint64_t start, const DataBuffer& data, uint64_t& result, BNFindFlag flags)
// {
// 	return m_InternalView->FindNextData(start, data, result, flags);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::Reanalyze()
// {
// 	return m_InternalView->Reanalyze();
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::ShowPlainTextReport(const std::string& title, const std::string& contents)
// {
// 	return m_InternalView->ShowPlainTextReport(title, contents);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::ShowMarkdownReport(const std::string& title, const std::string& contents, const std::string& plainText)
// {
// 	return m_InternalView->ShowMarkdownReport(title, contents, plainText);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::ShowHTMLReport(const std::string& title, const std::string& contents, const std::string& plainText)
// {
// 	return m_InternalView->ShowHTMLReport(title, contents, plainText);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::ShowGraphReport(const std::string& title, FlowGraph* graph)
// {
// 	return m_InternalView->ShowGraphReport(title, graph);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::GetAddressInput(uint64_t& result, const std::string& prompt, const std::string& title)
// {
// 	return m_InternalView->GetAddressInput(result, prompt, title);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::GetAddressInput(uint64_t& result, const std::string& prompt, const std::string& title,
//     uint64_t currentAddress)
// {
// 	return m_InternalView->GetAddressInput(result, prompt, title, currentAddress);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::AddAutoSegment(uint64_t start, uint64_t length, uint64_t dataOffset, uint64_t dataLength, uint32_t flags)
// {
// 	return m_InternalView->AddAutoSegment(start, length, dataOffset, dataLength, flags);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::RemoveAutoSegment(uint64_t start, uint64_t length)
// {
// 	return m_InternalView->RemoveAutoSegment(start, length);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::AddUserSegment(uint64_t start, uint64_t length, uint64_t dataOffset, uint64_t dataLength, uint32_t flags)
// {
// 	return m_InternalView->AddUserSegment(start, length, dataOffset, dataLength, flags);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::RemoveUserSegment(uint64_t start, uint64_t length)
// {
// 	return m_InternalView->RemoveUserSegment(start, length);
// }

// template <typename ARCH>
// std::vector<Ref<Segment>> FatMachOBinaryView<ARCH>::GetSegments()
// {
// 	return m_InternalView->GetSegments();
// }

// template <typename ARCH>
// Ref<Segment> FatMachOBinaryView<ARCH>::GetSegmentAt(uint64_t addr)
// {
// 	return m_InternalView->GetSegmentAt(addr);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::GetAddressForDataOffset(uint64_t offset, uint64_t& addr)
// {
// 	return m_InternalView->GetAddressForDataOffset(offset, addr);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::AddAutoSection(const std::string& name, uint64_t start, uint64_t length,
//     BNSectionSemantics semantics, const std::string& type,
//     uint64_t align, uint64_t entrySize, const std::string& linkedSection,
//     const std::string& infoSection, uint64_t infoData)
// {
// 	return m_InternalView->AddAutoSection(name, start, length,
//     semantics, type, align, entrySize, linkedSection, infoSection, infoData);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::RemoveAutoSection(const std::string& name)
// {
// 	return m_InternalView->RemoveAutoSection(name);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::AddUserSection(const std::string& name, uint64_t start, uint64_t length,
//     BNSectionSemantics semantics, const std::string& type,
//     uint64_t align, uint64_t entrySize, const std::string& linkedSection,
//     const std::string& infoSection, uint64_t infoData)
// {
// 	return m_InternalView->AddUserSection(name, start, length,
//     semantics, type, align, entrySize, linkedSection, infoSection, infoData);
// }
//     template <typename ARCH>
// void FatMachOBinaryView<ARCH>::RemoveUserSection(const std::string& name)
// {
// 	return m_InternalView->RemoveUserSection(name);
// }

// template <typename ARCH>
// std::vector<Ref<Section>> FatMachOBinaryView<ARCH>::GetSections()
// {
// 	return m_InternalView->GetSections();
// }

// template <typename ARCH>
// std::vector<Ref<Section>> FatMachOBinaryView<ARCH>::GetSectionsAt(uint64_t addr)
// {
// 	return m_InternalView->GetSectionsAt(addr);
// }

// template <typename ARCH>
// Ref<Section> FatMachOBinaryView<ARCH>::GetSectionByName(const std::string& name)
// {
// 	return m_InternalView->GetSectionByName(name);
// }

// template <typename ARCH>
// std::vector<std::string> FatMachOBinaryView<ARCH>::GetUniqueSectionNames(const std::vector<std::string>& names)
// {
// 	return m_InternalView->GetUniqueSectionNames(names);
// }

// template <typename ARCH>
// std::vector<BNAddressRange> FatMachOBinaryView<ARCH>::GetAllocatedRanges()
// {
// 	return m_InternalView->GetAllocatedRanges();
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::StoreMetadata(const std::string& key, Ref<Metadata> value)
// {
// 	return m_InternalView->StoreMetadata(key, value);
// }

// template <typename ARCH>
// Ref<Metadata> FatMachOBinaryView<ARCH>::QueryMetadata(const std::string& key)
// {
// 	return m_InternalView->QueryMetadata(key);
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::RemoveMetadata(const std::string& key)
// {
// 	return m_InternalView->RemoveMetadata(key);
// }

// template <typename ARCH>
// std::string FatMachOBinaryView<ARCH>::GetStringMetadata(const std::string& key)
// {
// 	return m_InternalView->GetStringMetadata(key);
// }

// template <typename ARCH>
// std::vector<uint8_t> FatMachOBinaryView<ARCH>::GetRawMetadata(const std::string& key)
// {
// 	return m_InternalView->GetRawMetadata(key);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetUIntMetadata(const std::string& key)
// {
// 	return m_InternalView->GetUIntMetadata(key);
// }

// template <typename ARCH>
// BNAnalysisParameters FatMachOBinaryView<ARCH>::GetParametersForAnalysis()
// {
// 	return m_InternalView->GetParametersForAnalysis();
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::SetParametersForAnalysis(BNAnalysisParameters params)
// {
// 	return m_InternalView->SetParametersForAnalysis(params);
// }

// template <typename ARCH>
// uint64_t FatMachOBinaryView<ARCH>::GetMaxFunctionSizeForAnalysis()
// {
// 	return m_InternalView->GetMaxFunctionSizeForAnalysis();
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::SetMaxFunctionSizeForAnalysis(uint64_t size)
// {
// 	return m_InternalView->SetMaxFunctionSizeForAnalysis(size);
// }

// template <typename ARCH>
// bool FatMachOBinaryView<ARCH>::GetNewAutoFunctionAnalysisSuppressed()
// {
// 	return m_InternalView->GetNewAutoFunctionAnalysisSuppressed();
// }

// template <typename ARCH>
// void FatMachOBinaryView<ARCH>::SetNewAutoFunctionAnalysisSuppressed(bool suppress)
// {
// 	m_InternalView->SetNewAutoFunctionAnalysisSuppressed(suppress);
// }

template <typename ARCH>
FatMachOBinaryView<ARCH>::~FatMachOBinaryView() {}

template class FatMachOBinaryView<mach_o_x86_64>;
template class FatMachOBinaryView<mach_o_x86>;
template class FatMachOBinaryView<mach_o_aarch64>;
template class FatMachOBinaryView<mach_o_armv7>;
template class FatMachOBinaryView<mach_o_ppc>;