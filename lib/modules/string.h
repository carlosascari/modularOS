/**
* Provides String utilities.
*
* @module ModularOS Kernel
* @submodule String Utilities
*/
#ifndef STRING_H
#define STRING_H

#include "types.h"

typedef struct __String
{
    uint16 (*length)(string);
} _String;

extern _String String;

static uint16 length(string);

#endif
