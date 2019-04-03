# Overview
BSA files are the resource archive files used by some Bethesda Softworks games (Morrowind, Oblivion, Skyrim, Fallout 3 and Fallout New Vegas for example).  
BSA, ESM, ESP and ESS format are IFF (Interchange File Format) variants.

# File Structure

| Name | Type / Size | Info |
| --- | --- | --- |
| header | [Header](#header) (36 bytes) | See specification |
| folderRecords | [Folder Record](#folder-record) (folderCount * 16 bytes) | See specification |
| fileRecordBlocks | [File Record blocks](#file-record-blocks) | See specification |
| fileNameBlock | [File Name block](file-name-block) | See specification |
| files | | |

## Header

## Folder Record

## File Record blocks

## File Name block

# References
* [uesp.net : Tes3Mod BSA File Format](https://en.uesp.net/wiki/Tes3Mod:BSA_File_Format)
* [uesp.net : Tes4Mod BSA File Format](https://en.uesp.net/wiki/Tes4Mod:BSA_File_Format)
* [uesp.net : Tes5Mod Archive File Format](https://en.uesp.net/wiki/Tes5Mod:Archive_File_Format)
