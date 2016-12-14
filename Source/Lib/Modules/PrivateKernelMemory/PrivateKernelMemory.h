#ifndef PRIVATE_KERNEL_MEMORY_H
#define PRIVATE_KERNEL_MEMORY_H

#include "../../Types.h"

#define PKM_MEMORY_SIZE 8192

static struct __PrivateKernelMemoryHeader {
	Pointer dataPointer;
	Pointer freePointer;
	UInt availableMemory;
	UInt count;
} __attribute__((packed));

static struct __PrivateKernelMemoryHeader * header;

typedef struct __PrivateKernelMemory {
	Pointer location;
	void (*initialize)(Pointer);
	Pointer (*new)(Pointer);
} _PrivateKernelMemory;

extern _PrivateKernelMemory PrivateKernelMemory;

static void initialize(Pointer location);
static Pointer new(Pointer structure);
static Pointer AllocateMemory(UInt size);

#endif
