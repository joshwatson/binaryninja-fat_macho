#pragma once

#include "binaryninjaapi.h"
#include "machoTypes.hpp"

using namespace BinaryNinja;

template <typename ARCH>
class FatMachOBinaryView : public BinaryView
{
private:
    Ref<FatMachOBinaryView<ARCH>> m_InternalView;

protected:
    virtual bool Init();
    virtual size_t PerformRead(void* dest, uint64_t offset, size_t len);
    virtual size_t PerformWrite(uint64_t offset, const void* data, size_t len);
    virtual size_t PerformInsert(uint64_t offset, const void* data, size_t len);
    virtual size_t PerformRemove(uint64_t offset, uint64_t len);

    virtual BNModificationStatus PerformGetModification(uint64_t offset);
    virtual bool PerformIsValidOffset(uint64_t offset);
    virtual bool PerformIsOffsetReadable(uint64_t offset);
    virtual bool PerformIsOffsetWritable(uint64_t offset);
    virtual bool PerformIsOffsetExecutable(uint64_t offset);
    virtual bool PerformIsOffsetBackedByFile(uint64_t offset);
    virtual uint64_t PerformGetNextValidOffset(uint64_t offset);
    virtual uint64_t PerformGetStart() const;
    virtual uint64_t PerformGetLength() const;
    virtual uint64_t PerformGetEntryPoint() const;
    virtual bool PerformIsExecutable() const;
    virtual BNEndianness PerformGetDefaultEndianness() const;
    virtual bool PerformIsRelocatable() const;
    virtual size_t PerformGetAddressSize() const;

    virtual bool PerformSave(FileAccessor* file);
    // void PerformDefineRelocation(Architecture* arch, BNRelocationInfo& info, uint64_t target, uint64_t reloc);
    // void PerformDefineRelocation(Architecture* arch, BNRelocationInfo& info, Ref<Symbol> sym, uint64_t reloc);
    // void NotifyDataWritten(uint64_t offset, size_t len);
    // void NotifyDataInserted(uint64_t offset, size_t len);
    // void NotifyDataRemoved(uint64_t offset, uint64_t len);

public:
    FatMachOBinaryView(BNBinaryView *view);
    FatMachOBinaryView(const std::string& typeName, FileMetadata* file, BinaryView* parentView);
    FileMetadata* GetFile() const { return m_file; }
    Ref<BinaryView> GetParentView() const;
    std::string GetTypeName() const;

    // bool IsModified() const;
    // bool IsAnalysisChanged() const;
    // bool IsBackedByDatabase() const;
    // bool CreateDatabase(const std::string& path);
    // bool CreateDatabase(const std::string& path,
    //     const std::function<void(size_t progress, size_t total)>& progressCallback);
    // bool SaveAutoSnapshot();
    // bool SaveAutoSnapshot(const std::function<void(size_t progress, size_t total)>& progressCallback);

    // void BeginUndoActions();
    // void AddUndoAction(UndoAction* action);
    // void CommitUndoActions();

    // bool Undo();
    // bool Redo();

    // std::string GetCurrentView();
    // uint64_t GetCurrentOffset();
    // bool Navigate(const std::string& view, uint64_t offset);

    // size_t Read(void* dest, uint64_t offset, size_t len);
    // DataBuffer ReadBuffer(uint64_t offset, size_t len);

    // size_t Write(uint64_t offset, const void* data, size_t len);
    // size_t WriteBuffer(uint64_t offset, const DataBuffer& data);

    // size_t Insert(uint64_t offset, const void* data, size_t len);
    // size_t InsertBuffer(uint64_t offset, const DataBuffer& data);

    // size_t Remove(uint64_t offset, uint64_t len);

    // BNModificationStatus GetModification(uint64_t offset);
    // std::vector<BNModificationStatus> GetModification(uint64_t offset, size_t len);

    // bool IsValidOffset(uint64_t offset) const;
    // bool IsOffsetReadable(uint64_t offset) const;
    // bool IsOffsetWritable(uint64_t offset) const;
    // bool IsOffsetExecutable(uint64_t offset) const;
    // bool IsOffsetBackedByFile(uint64_t offset) const;
    // bool IsOffsetCodeSemantics(uint64_t offset) const;
    // bool IsOffsetWritableSemantics(uint64_t offset) const;
    // bool IsOffsetExternSemantics(uint64_t offset) const;
    // uint64_t GetNextValidOffset(uint64_t offset) const;

    // uint64_t GetStart() const;
    // uint64_t GetEnd() const;
    // uint64_t GetLength() const;
    // uint64_t GetEntryPoint() const;

    // Ref<Architecture> GetDefaultArchitecture() const;
    // void SetDefaultArchitecture(Architecture* arch);
    // Ref<Platform> GetDefaultPlatform() const;
    // void SetDefaultPlatform(Platform* platform);

    // BNEndianness GetDefaultEndianness() const;
    // bool IsRelocatable() const;
    // size_t GetAddressSize() const;

    // bool IsExecutable() const;

    // bool Save(FileAccessor* file);
    // bool Save(const std::string& path);

    // void DefineRelocation(Architecture* arch, BNRelocationInfo& info, uint64_t target, uint64_t reloc);
    // void DefineRelocation(Architecture* arch, BNRelocationInfo& info, Ref<Symbol> target, uint64_t reloc);
    // std::vector<std::pair<uint64_t, uint64_t>> GetRelocationRanges() const;
    // std::vector<std::pair<uint64_t, uint64_t>> GetRelocationRangesAtAddress(uint64_t addr) const;

    // void RegisterNotification(BinaryDataNotification* notify);
    // void UnregisterNotification(BinaryDataNotification* notify);

    // void AddAnalysisOption(const std::string& name);
    // void AddFunctionForAnalysis(Platform* platform, uint64_t addr);
    // void AddEntryPointForAnalysis(Platform* platform, uint64_t start);
    // void RemoveAnalysisFunction(Function* func);
    // void CreateUserFunction(Platform* platform, uint64_t start);
    // void RemoveUserFunction(Function* func);
    // void UpdateAnalysisAndWait();
    // void UpdateAnalysis();
    // void AbortAnalysis();

    // void DefineDataVariable(uint64_t addr, const Confidence<Ref<Type>>& type);
    // void DefineUserDataVariable(uint64_t addr, const Confidence<Ref<Type>>& type);
    // void UndefineDataVariable(uint64_t addr);
    // void UndefineUserDataVariable(uint64_t addr);

    // std::map<uint64_t, DataVariable> GetDataVariables();
    // bool GetDataVariableAtAddress(uint64_t addr, DataVariable& var);

    // std::vector<Ref<Function>> GetAnalysisFunctionList();
    // bool HasFunctions() const;
    // Ref<Function> GetAnalysisFunction(Platform* platform, uint64_t addr);
    // Ref<Function> GetRecentAnalysisFunctionForAddress(uint64_t addr);
    // std::vector<Ref<Function>> GetAnalysisFunctionsForAddress(uint64_t addr);
    // Ref<Function> GetAnalysisEntryPoint();

    // Ref<BasicBlock> GetRecentBasicBlockForAddress(uint64_t addr);
    // std::vector<Ref<BasicBlock>> GetBasicBlocksForAddress(uint64_t addr);
    // std::vector<Ref<BasicBlock>> GetBasicBlocksStartingAtAddress(uint64_t addr);

    // std::vector<ReferenceSource> GetCodeReferences(uint64_t addr);
    // std::vector<ReferenceSource> GetCodeReferences(uint64_t addr, uint64_t len);

    // Ref<Symbol> GetSymbolByAddress(uint64_t addr, const NameSpace& nameSpace=NameSpace());
    // Ref<Symbol> GetSymbolByRawName(const std::string& name, const NameSpace& nameSpace=NameSpace());
    // std::vector<Ref<Symbol>> GetSymbolsByName(const std::string& name, const NameSpace& nameSpace=NameSpace());
    // std::vector<Ref<Symbol>> GetSymbols(const NameSpace& nameSpace=NameSpace());
    // std::vector<Ref<Symbol>> GetSymbols(uint64_t start, uint64_t len, const NameSpace& nameSpace=NameSpace());
    // std::vector<Ref<Symbol>> GetSymbolsOfType(BNSymbolType type, const NameSpace& nameSpace=NameSpace());
    // std::vector<Ref<Symbol>> GetSymbolsOfType(BNSymbolType type, uint64_t start, uint64_t len, const NameSpace& nameSpace=NameSpace());

    // void DefineAutoSymbol(Ref<Symbol> sym);
    // void DefineAutoSymbolAndVariableOrFunction(Ref<Platform> platform, Ref<Symbol> sym, Ref<Type> type);
    // void UndefineAutoSymbol(Ref<Symbol> sym);

    // void DefineUserSymbol(Ref<Symbol> sym);
    // void UndefineUserSymbol(Ref<Symbol> sym);

    // void DefineImportedFunction(Ref<Symbol> importAddressSym, Ref<Function> func);

    // bool IsNeverBranchPatchAvailable(Architecture* arch, uint64_t addr);
    // bool IsAlwaysBranchPatchAvailable(Architecture* arch, uint64_t addr);
    // bool IsInvertBranchPatchAvailable(Architecture* arch, uint64_t addr);
    // bool IsSkipAndReturnZeroPatchAvailable(Architecture* arch, uint64_t addr);
    // bool IsSkipAndReturnValuePatchAvailable(Architecture* arch, uint64_t addr);
    // bool ConvertToNop(Architecture* arch, uint64_t addr);
    // bool AlwaysBranch(Architecture* arch, uint64_t addr);
    // bool InvertBranch(Architecture* arch, uint64_t addr);
    // bool SkipAndReturnValue(Architecture* arch, uint64_t addr, uint64_t value);
    // size_t GetInstructionLength(Architecture* arch, uint64_t addr);

    // std::vector<BNStringReference> GetStrings();
    // std::vector<BNStringReference> GetStrings(uint64_t start, uint64_t len);

    // Ref<AnalysisCompletionEvent> AddAnalysisCompletionEvent(const std::function<void()>& callback);

    // AnalysisInfo GetAnalysisInfo();
    // BNAnalysisProgress GetAnalysisProgress();
    // Ref<BackgroundTask> GetBackgroundAnalysisTask();

    // uint64_t GetNextFunctionStartAfterAddress(uint64_t addr);
    // uint64_t GetNextBasicBlockStartAfterAddress(uint64_t addr);
    // uint64_t GetNextDataAfterAddress(uint64_t addr);
    // uint64_t GetNextDataVariableAfterAddress(uint64_t addr);
    // uint64_t GetPreviousFunctionStartBeforeAddress(uint64_t addr);
    // uint64_t GetPreviousBasicBlockStartBeforeAddress(uint64_t addr);
    // uint64_t GetPreviousBasicBlockEndBeforeAddress(uint64_t addr);
    // uint64_t GetPreviousDataBeforeAddress(uint64_t addr);
    // uint64_t GetPreviousDataVariableBeforeAddress(uint64_t addr);

    // LinearDisassemblyPosition GetLinearDisassemblyPositionForAddress(uint64_t addr, DisassemblySettings* settings);
    // std::vector<LinearDisassemblyLine> GetPreviousLinearDisassemblyLines(LinearDisassemblyPosition& pos,
    //     DisassemblySettings* settings);
    // std::vector<LinearDisassemblyLine> GetNextLinearDisassemblyLines(LinearDisassemblyPosition& pos,
    //     DisassemblySettings* settings);

    // bool ParseTypeString(const std::string& text, QualifiedNameAndType& result, std::string& errors);

    // std::map<QualifiedName, Ref<Type>> GetTypes();
    // Ref<Type> GetTypeByName(const QualifiedName& name);
    // Ref<Type> GetTypeById(const std::string& id);
    // std::string GetTypeId(const QualifiedName& name);
    // QualifiedName GetTypeNameById(const std::string& id);
    // bool IsTypeAutoDefined(const QualifiedName& name);
    // QualifiedName DefineType(const std::string& id, const QualifiedName& defaultName, Ref<Type> type);
    // void DefineUserType(const QualifiedName& name, Ref<Type> type);
    // void UndefineType(const std::string& id);
    // void UndefineUserType(const QualifiedName& name);
    // void RenameType(const QualifiedName& oldName, const QualifiedName& newName);

    // void RegisterPlatformTypes(Platform* platform);

    // bool FindNextData(uint64_t start, const DataBuffer& data, uint64_t& result, BNFindFlag flags = NoFindFlags);

    // void Reanalyze();

    // void ShowPlainTextReport(const std::string& title, const std::string& contents);
    // void ShowMarkdownReport(const std::string& title, const std::string& contents, const std::string& plainText);
    // void ShowHTMLReport(const std::string& title, const std::string& contents, const std::string& plainText);
    // void ShowGraphReport(const std::string& title, FlowGraph* graph);
    // bool GetAddressInput(uint64_t& result, const std::string& prompt, const std::string& title);
    // bool GetAddressInput(uint64_t& result, const std::string& prompt, const std::string& title,
    //     uint64_t currentAddress);

    // void AddAutoSegment(uint64_t start, uint64_t length, uint64_t dataOffset, uint64_t dataLength, uint32_t flags);
    // void RemoveAutoSegment(uint64_t start, uint64_t length);
    // void AddUserSegment(uint64_t start, uint64_t length, uint64_t dataOffset, uint64_t dataLength, uint32_t flags);
    // void RemoveUserSegment(uint64_t start, uint64_t length);
    // std::vector<Ref<Segment>> GetSegments();
    // Ref<Segment> GetSegmentAt(uint64_t addr);
    // bool GetAddressForDataOffset(uint64_t offset, uint64_t& addr);

    // void AddAutoSection(const std::string& name, uint64_t start, uint64_t length,
    //     BNSectionSemantics semantics = DefaultSectionSemantics, const std::string& type = "",
    //     uint64_t align = 1, uint64_t entrySize = 0, const std::string& linkedSection = "",
    //     const std::string& infoSection = "", uint64_t infoData = 0);
    // void RemoveAutoSection(const std::string& name);
    // void AddUserSection(const std::string& name, uint64_t start, uint64_t length,
    //     BNSectionSemantics semantics = DefaultSectionSemantics, const std::string& type = "",
    //     uint64_t align = 1, uint64_t entrySize = 0, const std::string& linkedSection = "",
    //     const std::string& infoSection = "", uint64_t infoData = 0);
    // void RemoveUserSection(const std::string& name);
    // std::vector<Ref<Section>> GetSections();
    // std::vector<Ref<Section>> GetSectionsAt(uint64_t addr);
    // Ref<Section> GetSectionByName(const std::string& name);

    // std::vector<std::string> GetUniqueSectionNames(const std::vector<std::string>& names);

    // std::vector<BNAddressRange> GetAllocatedRanges();

    // void StoreMetadata(const std::string& key, Ref<Metadata> value);
    // Ref<Metadata> QueryMetadata(const std::string& key);
    // void RemoveMetadata(const std::string& key);
    // std::string GetStringMetadata(const std::string& key);
    // std::vector<uint8_t> GetRawMetadata(const std::string& key);
    // uint64_t GetUIntMetadata(const std::string& key);

    // BNAnalysisParameters GetParametersForAnalysis();
    // void SetParametersForAnalysis(BNAnalysisParameters params);
    // uint64_t GetMaxFunctionSizeForAnalysis();
    // void SetMaxFunctionSizeForAnalysis(uint64_t size);
    // bool GetNewAutoFunctionAnalysisSuppressed();
    // void SetNewAutoFunctionAnalysisSuppressed(bool suppress);

    // std::set<NameSpace> GetNameSpaces() const;
    // static NameSpace GetInternalNameSpace();
    // static NameSpace GetExternalNameSpace();
    ~FatMachOBinaryView();
};