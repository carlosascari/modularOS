#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "Lib/Types.h"

#define MB_SEARCH 8192
#define MB_HEADER_MAGIC 0x1BADB002
#define MB_BOOTLOADER_MAGIC 0x2BADB002
#define MB_UNSUPPORTED 0x0000fffc
#define MB_MOD_ALIGN 0x00001000
#define MB_INFO_ALIGN 0x00000004
#define MB_PAGE_ALIGN 0x00000001
#define MB_MEMORY_INFO 0x00000002
#define MB_VIDEO_MODE 0x00000004
#define MB_AOUT_KLUDGE 0x00010000

/*
*  Flags to be set in the 'flags' member of the multiboot info structure.
*/
#define MB_HAS_MEMORY 0x00000001
#define MB_HAS_BOOT_DEVICE 0x00000002
#define MB_HAS_CMDLINE 0x00000004
#define MB_HAS_MODS 0x00000008
// Next two are mutually exclusive
#define MB_HAS_AOUT_SYMS 0x00000010
#define MB_HAS_ELF_SHDR 0x00000020
#define MB_HAS_MEMORY_MAP 0x00000040
#define MB_HAS_DRIVE_INFO 0x00000080
#define MB_HAS_CONFIG_TABLE 0x00000100
#define MB_HAS_BOOT_LOADER_NAME 0x00000200
#define MB_HAS_APM_TABLE 0x00000400
#define MB_HAS_VIDEO_INFO 0x00000800

typedef struct _MultibootHeader {
  // Must be MB_MAGIC - see above.
  UInt32 magic;
  // Feature flags
  UInt32 flags;
  // The above fields plus this one must equal 0 mod 2^32.
  UInt32 checksum;
  // These are only valid if MB_AOUT_KLUDGE is set.
  UInt32 headerAddress;
  UInt32 loadAddress;
  UInt32 loadEndAddress;
  UInt32 bssEndAddress;
  UInt32 entryAddress;
  // These are only valid if MB_VIDEO_MODE is set.
  UInt32 modeType;
  UInt32 width;
  UInt32 height;
  UInt32 depth;
} MultibootHeader __attribute__ ((packed));

typedef struct _MultibootInfo {
  // Multiboot info version number
  UInt32 flags;
  // Available memory from BIOS
  UInt32 memLower;
  UInt32 memUpper;
  // "root" partition
  UInt32 bootDevice;
  // Kernel command line
  UInt32 cmdline;
  // Boot-Module list
  UInt32 modsCount;
  UInt32 modsAddress;
  UInt32 syms[4];
  // Memory Mapping buffer 
  UInt32 mmapLength;
  UInt32 mmapAddress;
  // Drive Info buffer 
  UInt32 drivesLength;
  UInt32 drivesAddress;
  // ROM configuration table 
  UInt32 configTable;
  // Boot Loader Name 
  UInt32 bootLoaderName;
  // APM table 
  UInt32 apmTable;
  // Video 
  UInt32 vbeControlInfo;
  UInt32 vbeModeInfo;
  UInt16 vbeMode;
  UInt16 vbeInterfaceSegment;
  UInt16 vbeInterfaceOffset;
  UInt16 vbeInterfaceLength;
} MultibootInformation __attribute__ ((packed));

#define MULTIBOOT_MEMORY_AVAILABLE 1
#define MULTIBOOT_MEMORY_RESERVED 2

typedef struct _MultibootMmapEntry {
  UInt32 size;
  UInt64 address;
  UInt64 length;
  UInt32 type;
} MultibootMmapEntry __attribute__ ((packed));

#endif
