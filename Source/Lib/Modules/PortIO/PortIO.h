#ifndef PORT_IO_H
#define PORT_IO_H

#include "../../Types.h"

typedef struct __PortIO {
	Byte (*inByte)(Word port);
	void (*outByte)(Word port, Byte data);
} _PortIO;

extern _PortIO PortIO;

static Byte inByte(Word port);
static void outByte(Word port, Byte data);

#endif
