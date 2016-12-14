#ifndef CONSOLE_H
#define CONSOLE_H

#include "../../Types.h"
#include "../PrivateKernelMemory/PrivateKernelMemory.h"

typedef struct __Console {
	void (*clear)(struct __Console *);
	void (*print)(struct __Console *, String);
	void (*printCharacter)(struct __Console *, char);
	void (*printNumber)(struct __Console *, Int, Boolean);
	UInt width;
	UInt height;
	UInt depth;
	UInt scrollX;
	UInt scrollY;
	UInt cursorX;
	UInt cursorY;
} _Console;

extern _Console ConsoleInstance;

static Word * VideoFrameBuffer = (Word *) 0xb8000;

static void clear(struct __Console *);
static void print(struct __Console *, String);
static void printCharacter(struct __Console *, char);
static void printNumber(struct __Console *, Int, Boolean);
static void updateCursor(struct __Console *);

static enum VGA_COLOR {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

#endif
