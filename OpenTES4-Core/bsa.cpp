#include "bsa.h"

#include <bitset>

std::istream& BSA::operator>>(std::istream& is, LengthPrefixedString& string)
{
    is.read(reinterpret_cast<char*>(&string.length),
        sizeof(string.length));

    string.string = new char[string.length];

    is.read(string.string, string.length);

    return is;
}

std::istream& BSA::operator>>(std::istream& is, Header& header)
{
    is.read(reinterpret_cast<char*>(&header.fileId),
        sizeof(header.fileId));
    is.read(reinterpret_cast<char*>(&header.version),
        sizeof(header.version));
    is.read(reinterpret_cast<char*>(&header.offset),
        sizeof(header.offset));
    is.read(reinterpret_cast<char*>(&header.archiveFlags),
        sizeof(header.archiveFlags));
    is.read(reinterpret_cast<char*>(&header.folderCount),
        sizeof(header.folderCount));
    is.read(reinterpret_cast<char*>(&header.fileCount),
        sizeof(header.fileCount));
    is.read(reinterpret_cast<char*>(&header.totalFolderNameLength),
        sizeof(header.totalFolderNameLength));
    is.read(reinterpret_cast<char*>(&header.totalFileNameLength),
        sizeof(header.totalFileNameLength));
    is.read(reinterpret_cast<char*>(&header.fileFlags),
        sizeof(header.fileFlags));

    return is;
}

std::istream& BSA::operator>>(std::istream& is, FolderRecord& folderRecord)
{
    is.read(reinterpret_cast<char*>(&folderRecord.nameHash),
        sizeof(folderRecord.nameHash));
    is.read(reinterpret_cast<char*>(&folderRecord.count),
        sizeof(folderRecord.count));
    is.read(reinterpret_cast<char*>(&folderRecord.offset),
        sizeof(folderRecord.offset));

    return is;
}

std::istream& BSA::operator>>(std::istream& is, FileRecord& fileRecord)
{
    is.read(reinterpret_cast<char*>(&fileRecord.nameHash),
        sizeof(fileRecord.nameHash));
    is.read(reinterpret_cast<char*>(&fileRecord.size),
        sizeof(fileRecord.size));
    is.read(reinterpret_cast<char*>(&fileRecord.offset),
        sizeof(fileRecord.offset));

    return is;
}

std::istream& BSA::operator>>(std::istream& is, FileRecordBlock& fileRecordBlock)
{
    if (fileRecordBlock.hasName)
        is >> fileRecordBlock.name;

    fileRecordBlock.fileRecords.reserve(fileRecordBlock.blocksCount);

    for (uint32_t i = 0; i < fileRecordBlock.blocksCount; ++i) {
        FileRecord fr;
        is >> fr;
        fileRecordBlock.fileRecords.push_back(fr);
    }

    fileRecordBlock.fileRecords.shrink_to_fit();

    return is;
}

std::istream& BSA::operator>>(std::istream& is, FileNameBlock& fileNameBlock)
{
    return is;
}

std::istream& BSA::operator>>(std::istream& is, FileBlock& fileBlock)
{
    return is;
}

std::istream& BSA::operator>>(std::istream& is, BSA& bsa)
{
    is >> bsa.header;

    bsa.folderRecords.reserve(bsa.header.folderCount);

    for (uint32_t i = 0; i < bsa.header.folderCount; ++i) {
        FolderRecord fr;
        is >> fr;
        bsa.folderRecords.push_back(fr);
    }

    bsa.folderRecords.shrink_to_fit();

    std::bitset<32> archiveFlags(bsa.header.archiveFlags);

    bsa.fileRecordBlocks.reserve(bsa.header.folderCount);

    for (uint32_t i = 0; i < bsa.header.folderCount; ++i) {
        FileRecordBlock frb(archiveFlags.test(0), bsa.folderRecords.at(i).count);
        is >> frb;
        bsa.fileRecordBlocks.push_back(frb);
    }

    bsa.fileRecordBlocks.shrink_to_fit();

    return is;
}
