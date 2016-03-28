/**
* Provides Screen module.
*
* @module ModularOS Kernel
* @submodule Screen
*/
#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"
#include "string.h"
#include "machine.h"

typedef struct __Screen
{
	void (*clear)();
	void (*clearLine)(uint8, uint8);
	void (*updateCursor)();
	void (*scrollUp)(uint8);
	void (*newLineCheck)();
	void (*printch)(char);
	void (*print) (string);
} _Screen; 

extern _Screen Screen;

static void clear();
static void clearLine(uint8, uint8);
static void updateCursor();
static void scrollUp(uint8);
static void newLineCheck();
static void printch(char);
static void print (string);

#endif
