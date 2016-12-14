#ifndef GDT_H
#define GDT_H

#include "../../Types.h"

typedef struct _GdtEntry {
    UInt16 limitLow;
    UInt16 baseLow;
    UInt8 baseMiddle;
    UInt8 access;
    UInt8 granularity;
    UInt8 baseHigh;
} GdtEntry __attribute__((packed));

typedef struct _GdtPointer {
    UInt16 limit;
    UInt32 base;
} GdtPointer __attribute__((packed));

typedef struct __Gdt {
	GdtPointer pointer;
	GdtEntry entries[3];
	void (*install)();
} _Gdt __attribute__((packed)); 

_Gdt Gdt;
struct _GdtEntry gdtEntries[3];
GdtPointer gdtPointer;

static void Gdt_SetGate(UInt32, UInt32, UInt32, Byte, Byte);
 void Gdt_Install();

extern void cpu_gdt_flush();

#endif
