#include "PrivateKernelMemory.h"

_PrivateKernelMemory PrivateKernelMemory = {
    .new = new,
    .initialize = initialize
};

void initialize(Pointer location) {
	UInt sizeOfHeader = sizeof(struct __PrivateKernelMemoryHeader);
	PrivateKernelMemory.location = location;
	header = PrivateKernelMemory.location;
	header->dataPointer = (sizeOfHeader + PrivateKernelMemory.location);
	header->freePointer = header->dataPointer;
	header->count = 0;
	header->availableMemory = PKM_MEMORY_SIZE - sizeOfHeader;
}

Pointer AllocateMemory(UInt size) {
	Pointer newMemoryPointer = header->freePointer;
	if (size < header->availableMemory) {
		FillMemory(newMemoryPointer, 0x00, size);
		header->freePointer = newMemoryPointer + size;
		header->count++;
		return newMemoryPointer;
	} else {
		return 0;
	}
}

Pointer new(Pointer structure) {
	UInt structureSize = sizeof(*structure);
	Pointer newMemory = AllocateMemory(structureSize);
	CopyMemory(newMemory, structure, structureSize);
	if (newMemory) {
		return newMemory;
	} else {
		return 0;
	}
}
