#ifndef VBE_H
#define VBE_H

#include "Lib/Types.h"

typedef struct _VbeInfoBlock {
   char vbeSignature[4];   // == "VESA"
   Word vbeVersion;        // == 0x0300 for VBE 3.0
   Word OemStringPtr[2];   // isa vbeFarPtr
   Byte Capabilities[4];
   Word VideoModePtr[2];   // isa vbeFarPtr
   Word TotalMemory;       // as # of 64KB blocks
   // Byte  OemData[256] 
} VbeInfoBlock __attribute__((packed));
 
typedef struct _VbeModeInfoBlock {
  Word attributes;
  Byte winA; 
  Byte winB;
  Word granularity;
  Word winsize;
  Word segmentA;
  Word segmentB;
  unsigned long int VBE_FAR;
  Word pitch; // bytes per scanline
  Word Xres;
  Word Yres;
  Byte Xchar, Ychar, planes, bpp, banks;
  Byte memory_model, bank_size, image_pages;
  Byte reserved0;
  Byte red_mask, red_position;
  Byte green_mask, green_position;
  Byte blue_mask, blue_position;
  Byte rsv_mask, rsv_position;
  Byte directcolor_attributes;
  UInt32 physbase;  // your LFB (Linear Framebuffer) address ;)
  UInt32 reserved1;
  Word reserved2;
} VbeModeInfoBlock __attribute__((packed));


// Another version?
typedef struct MODE_INFO {
  Word ModeAttributes;
  Byte  WinAAttributes;
  Byte  WinBAttributes;
  Word WinGranularity;
  Word WinSize;
  Word WinASegment;
  Word WinBSegment;
  unsigned long WinFuncPtr;
  Word BytesPerScanLine;
  Word XResolution;
  Word YResolution;
  Byte  XCharSize;
  Byte  YCharSize;
  Byte  NumberOfPlanes;
  Byte  BitsPerPixel;
  Byte  NumberOfBanks;
  Byte  MemoryModel;
  Byte  BankSize;
  Byte  NumberOfImagePages;
  Byte  Reserved_page;
  Byte  RedMaskSize;
  Byte  RedMaskPos;
  Byte  GreenMaskSize;
  Byte  GreenMaskPos;
  Byte  BlueMaskSize;
  Byte  BlueMaskPos;
  Byte  ReservedMaskSize;
  Byte  ReservedMaskPos;
  Byte  DirectColorModeInfo;
  unsigned long  PhysBasePtr;
  unsigned long  OffScreenMemOffset;
  Word OffScreenMemSize;
  Byte  Reserved[206];
} MODE_INFO;

#endif
