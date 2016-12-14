/**
* Provides Kernel main
*
* @module ModularOS Kernel
* @submodule Kernel
*/
#ifndef KERNEL_C
#define KERNEL_C

#include "Multiboot.h"
#include "VBE.h"
#include "Lib/Lib.h"
#include "Lib/Modules/PrivateKernelMemory/PrivateKernelMemory.h"
#include "Lib/Modules/Gdt/Gdt.h"
#include "Lib/Modules/Console/Console.h"

#include "KDebug.h"

/**
* Kernel Main (called from Kernel.s)
*
* @param privateKernelMemory {Pointer}
* @param multibootMagic {Dword}
* @param multibootInfo {MultibootInformation}
*/
KernelMain(Pointer privateKernelMemory, Dword multibootMagic, MultibootInformation * multibootInfo) {
	// Gdt_Install(); // Crashes

	// Need to initilize in order to instanciate modules
	PrivateKernelMemory.initialize(privateKernelMemory);

	_Console * console;
	VbeInfoBlock * vbeInfoBlock;
	VbeModeInfoBlock * vbeModeInfoBlock;

	// console->clear(console);
	// Halt();

	if (multibootMagic != MB_BOOTLOADER_MAGIC) {
		console = Console(80, 25, 2);
		KDebugFatalNotMultiboot(console);
		Halt();
	} else if (!(multibootInfo->flags & MB_HAS_MEMORY_MAP)) {
		console = Console(80, 25, 2);
		KDebugFatalNoMemoryMap(console);
		Halt();
	}

	if (multibootInfo->flags & MB_HAS_VIDEO_INFO) {
		console = Console(80, 25, 2); // Should be pixel console (WIP)
		console->clear(console);
		console->print(console, "modularOS\n");

		// color :)
		char * videoMemory = (char *) 0xB8000;
		videoMemory[15] = 0xFC;
		videoMemory[17] = 0xFC;

		console->print(console, "VGA/VESA Graphic Mode\n");
	} else {
		console = Console(80, 25, 2);
		console->clear(console);
		console->print(console, "modularOS\n");
		console->print(console, "EGA Text Mode\n\n");
	}

	KDebugPrintMultibootInformation(console, multibootInfo);

	if (multibootInfo->flags & MB_HAS_VIDEO_INFO) {
		vbeInfoBlock = multibootInfo->vbeControlInfo;
		vbeModeInfoBlock = multibootInfo->vbeModeInfo;
		if (multibootInfo->vbeMode == 3) {
			KDebugPrintVbeInfo(console, vbeInfoBlock);
			KDebugPrintVbeModeInfo(console, vbeModeInfoBlock);
		} else {
			KDebugFatalUnsupportedVbe(console);
		}
	}

	Halt();
}

#endif
