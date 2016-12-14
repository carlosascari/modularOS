#include "Gdt.h"

_Gdt Gdt = {
    .install = Gdt_Install
};

// Setup a descriptor in the Global Descriptor Table 
void Gdt_SetGate(UInt32 index, UInt32 base, UInt32 limit, Byte access, Byte granularity) {
    // Setup the descriptor base address
    gdtEntries[index].baseLow = (base & 0xFFFF);
    gdtEntries[index].baseMiddle = (base >> 16) & 0xFF;
    gdtEntries[index].baseHigh = (base >> 24) & 0xFF;
    // Setup the descriptor limits 
    gdtEntries[index].limitLow = (limit & 0xFFFF);
    gdtEntries[index].granularity = ((limit >> 16) & 0x0F);
    // Finally, set up the granularity and access flags 
    gdtEntries[index].granularity |= (granularity & 0xF0);
    gdtEntries[index].access = access;
}

void Gdt_Install() {
	// Setup the GDT pointer and limit
	gdtPointer.limit = (8 * 3) - 1;
	gdtPointer.base = gdtEntries;

    // NULL descriptor
    Gdt_SetGate(0, 0, 0, 0, 0);

    /* Code Segment
    * The base address is 0, the limit is 4GBytes, it uses 4KByte granularity,
    * uses 32-bit opcodes.
    */
    Gdt_SetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* Data Segment
    * The base address is 0, the limit is 4GBytes, it uses 4KByte granularity,
    * uses 32-bit opcodes.
    */
    Gdt_SetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Flush out the old GDT and install the new changes
    cpu_gdt_flush();
}
