/**
* Provides functions to print out specific structures for debugging
*
* @module ModularOS Kernel
* @submodule KDebug
*/
#ifndef KERNEL_DEBUG_H
#define KERNEL_DEBUG_H

#include "Multiboot.h"
#include "VBE.h"
#include "Lib/Types.h"
#include "Lib/Modules/Console/Console.h"

KDebugPrintMultibootInformation(Pointer consolePointer, MultibootInformation * multibootInfo) {
	_Console * console = (_Console *) consolePointer;
	// Detect RAM memory
	if (CHECK_BIT(multibootInfo->flags, 0)) {
		console->print(console, " LOW Memory Addr:");
		console->printNumber(console, multibootInfo->memLower, true);
		console->print(console, "\n");
		console->print(console, "HIGH Memory Addr:");
		console->printNumber(console, multibootInfo->memUpper, true);
		console->print(console, "\n");
	}
	if (CHECK_BIT(multibootInfo->flags, 2)) {
		console->print(console, "         cmdline:");
		console->print(console, multibootInfo->cmdline);
		console->print(console, "\n");
	}
	if (CHECK_BIT(multibootInfo->flags, 6)) {
		console->print(console, "  mmapByteLength: ");
		console->printNumber(console, multibootInfo->mmapLength * 1024, false);
		console->print(console, "\n");
		console->print(console, "     mmapAddress: ");
		console->printNumber(console, multibootInfo->mmapAddress, true);
		console->print(console, "\n");
		Pointer mmapIterator = multibootInfo->mmapAddress;
		MultibootMmapEntry * mmapEntry;
		while (mmapIterator < multibootInfo->mmapAddress + multibootInfo->mmapLength) {
			mmapEntry = mmapIterator;
			console->print(console, "       mmapEntry:");
			console->print(console, " size: ");
			console->printNumber(console, mmapEntry->size, false);
			console->print(console, " addr: ");
			console->printNumber(console, mmapEntry->address, true);
			console->print(console, " length: ");
			console->printNumber(console, mmapEntry->length, false);
			console->print(console, " type: ");
			console->printNumber(console, mmapEntry->type, true);
			console->print(console, "\n");
			mmapIterator = mmapIterator + mmapEntry->size + sizeof(mmapEntry->size);
		}
	}
	if (CHECK_BIT(multibootInfo->flags, 11)) {
		console->print(console, "  vbeControlInfo:");
		console->printNumber(console, multibootInfo->vbeControlInfo, true);
		console->print(console, "\n");
		console->print(console, "     vbeModeInfo:");
		console->printNumber(console, multibootInfo->vbeModeInfo, true);
		console->print(console, "\n");
		console->print(console, "     vbeMode:");
		console->printNumber(console, multibootInfo->vbeMode, true);
		console->print(console, "\n");
		console->print(console, "     vbeInterfaceSegment:");
		console->printNumber(console, multibootInfo->vbeInterfaceSegment, true);
		console->print(console, "\n");
		console->print(console, "     vbeInterfaceOffset:");
		console->printNumber(console, multibootInfo->vbeInterfaceOffset, true);
		console->print(console, "\n");
		console->print(console, "     vbeInterfaceLength:");
		console->printNumber(console, multibootInfo->vbeInterfaceLength, true);
		console->print(console, "\n");
	}
}

KDebugPrintVbeInfo(Pointer consolePointer, VbeInfoBlock * vbeInfoBlock) {
	_Console * console = (_Console *) consolePointer;
	console->print(console, "     vbeSignature:");
	console->printCharacter(console, vbeInfoBlock->vbeSignature[0]);
	console->printCharacter(console, vbeInfoBlock->vbeSignature[1]);
	console->printCharacter(console, vbeInfoBlock->vbeSignature[2]);
	console->printCharacter(console, vbeInfoBlock->vbeSignature[3]);
	console->printCharacter(console, '\n');
}

KDebugPrintVbeModeInfo(Pointer consolePointer, VbeModeInfoBlock * vbeModeInfoBlock) {
	_Console * console = (_Console *) consolePointer;
	console->print(console, "     physbase:");
	console->printNumber(console, vbeModeInfoBlock->physbase, true);
	console->print(console, "\n");
	console->print(console, " vbeModeInfoBlock:");
	console->printNumber(console, vbeModeInfoBlock->attributes, true);
	console->print(console, "\n");
}

/*
* Fatalities
*/

KDebugFatalNotMultiboot(Pointer consolePointer) {
	_Console * console = (_Console *) consolePointer;
	console->clear(console);
	console->print(console, "FATAL - OS only boots from a multiboot compliant bootloader!\n");
}

KDebugFatalUnsupportedVbe(Pointer consolePointer) {
	_Console * console = (_Console *) consolePointer;
	console->print(console, "FATAL - Unsupported VBE Mode!\n");
}

KDebugFatalNoMemoryMap(Pointer consolePointer) {
	_Console * console = (_Console *) consolePointer;
	console->print(console, "FATAL - No memory map!\n");
}

#endif
