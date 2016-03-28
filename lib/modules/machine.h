/**
* Provides low level access; assembly bindings.
*
* @module ScratchOS Kernel
* @submodule Machine Interface
*/
#ifndef MACHINE_H
#define MACHINE_H

#include "types.h"

typedef struct __Machine
{
    void (*inportb)(WORD);
    void (*outportb)(WORD, BYTE);
} _Machine;

extern _Machine Machine;

static BYTE inportb (WORD);
static void outportb (WORD, BYTE);

#endif
