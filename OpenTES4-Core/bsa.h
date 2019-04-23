#ifndef BSA_H
#define BSA_H

// std includes.
#include <iostream>
#include <vector>

namespace BSA {

class LengthPrefixedString {
public:
    uint8_t length = 0;
    char* string = nullptr;
};

class Header {
public:
    char fileId[4];
    uint32_t version;
    uint32_t offset;
    uint32_t archiveFlags;
    uint32_t folderCount;
    uint32_t fileCount;
    uint32_t totalFolderNameLength;
    uint32_t totalFileNameLength;
    uint32_t fileFlags;
};

class FolderRecord {
public:
    uint64_t nameHash;
    uint32_t count;
    uint32_t offset;
};

class FileRecord {
public:
    uint64_t nameHash;
    uint32_t size;
    uint32_t offset;
};

class FileRecordBlock {
public:
    FileRecordBlock(bool hasName = true, uint32_t blocksCount = 0)
        : hasName(hasName)
        , blocksCount(blocksCount)
    {
    }

    LengthPrefixedString name;
    std::vector<FileRecord> fileRecords;

    const bool hasName;
    const uint32_t blocksCount;
};

class FileNameBlock {
};

class FileBlock {
};

class BSA {
public:
    Header header;
    std::vector<FolderRecord> folderRecords;
    std::vector<FileRecordBlock> fileRecordBlocks;
    FileNameBlock fileNameBlock;

private:
};

std::istream& operator>>(std::istream& is, LengthPrefixedString& string);
std::istream& operator>>(std::istream& is, Header& header);
std::istream& operator>>(std::istream& is, FolderRecord& folderRecord);
std::istream& operator>>(std::istream& is, FileRecord& fileRecord);
std::istream& operator>>(std::istream& is, FileRecordBlock& fileRecordBlock);
std::istream& operator>>(std::istream& is, FileNameBlock& fileNameBlock);
std::istream& operator>>(std::istream& is, FileBlock& fileBlock);
std::istream& operator>>(std::istream& is, BSA& bsa);
}

#endif // BSA_H
