#include "PortIO.h"

_PortIO PortIO = {
    .outByte = outByte,
    .inByte = inByte
};

Byte inByte(Word port) {
	Byte rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port));
	return rv;
}

void outByte(Word port, Byte data) {
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}
