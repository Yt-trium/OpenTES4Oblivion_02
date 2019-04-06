# Overview
BSA files are the resource archive files used by some Bethesda Softworks games (Morrowind, Oblivion, Skyrim, Fallout 3 and Fallout New Vegas for example).  
BSA, ESM, ESP and ESS format are IFF (Interchange File Format) variants.  
This documentation focus on The Elder Scrolls IV Oblivion versions.

# File Structure

| Name | Type / Size | Info |
| --- | --- | --- |
| header | [Header](#header) (36 bytes) | [See specification](#header) |
| folderRecords | [Folder Record](#folder-record) (folderCount * 16 bytes) | [See specification](#folder-record) |
| fileRecordBlocks | [File Record blocks](#file-record-blocks) | [See specification](#file-record-blocks) |
| fileNameBlock | [File Name block](#file-name-block) | [See specification](#file-name-block) |
| files | | |

## Header

| Name | Type / Size | Info |
| --- | --- | --- |
| fileId | char[4] | Value: "BSA\x00" |
| version | uint32 | 103 (0x67) for Oblivion <br> 104 (0x68)  for Skyrim <br> 105 (0x69) for Skyrim SE |
| offset | uint32 | Offset of beginning of folder records. All headers are the same size, this value is 36 (0x24)|
| archiveFlags | uint32 | Flags for archive, [see specification](#archive-flags) |
| folderCount | uint32 | Number of folders |
| fileCount | uint32 | Number of files |
| totalFolderNameLength | uint32 | Length of all folder names, including \0's but not including the prefixed length byte |
| totalFileNameLength | uint32 | Length of all file names, including \0's |
| fileFlags | uint32 | Flags for file type, [see specification](#file-flags) |

### Archive Flags
| Bit | Description |
| --- | --- |
| 0x01**¹** | Has names for directories |
| 0x02**¹** | Has names for files |
| 0x04 | Files are by default compressed |
| 0x08**²** | Retain Directory Names |
| 0x10**²** | Retain File Names |
| 0x20**²** | Retain File Name Offsets |
| 0x40 | Xbox360 archive |
| 0x80**²** | Unknown |
| 0x100**¹** | Unknown |
| 0x200**¹** | Unknown |
| 0x400**¹** | Unknown |

* **¹** Bit is set in all official BSA files.
* **²** Bit has no effect on the file structure. Probably just instructions for the game.

### File Flags

| Bit | Description |
| --- | --- |
| 0x01 | Meshes |
| 0x02 | Textures |
| 0x04 | Menus |
| 0x08 | Sounds |
| 0x10 | Voices |
| 0x20 | Shaders |
| 0x40 | Trees |
| 0x80 | Fonts |
| 0x100 | Miscellaneous |

## Folder Record

| Name | Type / Size | Info |
| --- | --- | --- |
| nameHash | uint64 | Hash of the folder name |
| count | uint32 | Number of files in folder |
| offset | uint32 | Offset to file records for this folder : Offset to name of this folder + totalFileNameLength |

## File Record blocks

If archiveFlags bit 0x01 is set

| Name | Type / Size | Info |
| --- | --- | --- |
| name | length-prefixed (1 byte) and null-terminated string |  Name of the folder |
| fileRecords | [File Record](#file-record) | *count* number of file record specified in folder record, [see specification](#file-record)  |

If not

| Name | Type / Size | Info |
| --- | --- | --- |
| fileRecords | [File Record](#file-record) | *count* number of file record specified in folder record, [see specification](#file-record)  |

### File Record

| Name | Type / Size | Info |
| --- | --- | --- |
| nameHash | uint64 | Hash of the file name |
| size | uint32 | If bit 0x40000000 is set and files are default compressed, this file is not compressed <br> If bit 0x40000000 is set and files are default not compressed, this file is compressed |
| offset | uint32 | Offset to file raw data |

## File Name block

# References
* [uesp.net : Tes3Mod BSA File Format](https://en.uesp.net/wiki/Tes3Mod:BSA_File_Format)
* [uesp.net : Tes4Mod BSA File Format](https://en.uesp.net/wiki/Tes4Mod:BSA_File_Format)
* [uesp.net : Tes5Mod Archive File Format](https://en.uesp.net/wiki/Tes5Mod:Archive_File_Format)
