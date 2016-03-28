#include "machine.h"

_Machine Machine = {
    .inportb = inportb,
    .outportb = outportb
};

/**
* @method inportb
* @param _port
*/
BYTE inportb (WORD _port)
{
	BYTE rv;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
	return rv;
}

/**
* @method outportb
* @param _port
* @param _data
*/
void outportb (WORD _port, BYTE _data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
