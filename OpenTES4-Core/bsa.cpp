#include "bsa.h"
#include <QDebug>
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

std::istream& BSA::operator>>(std::istream& is, FileRecordBlock& fileRecordBlock)
{
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

    for (uint32_t i = 0; i < bsa.header.folderCount; ++i) {
        FolderRecord fr;
        is >> fr;
        bsa.folderRecords.push_back(fr);
    }

    return is;
}
