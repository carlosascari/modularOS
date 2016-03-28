/**
* Provides Kernel main.
*
* @module ModularOS Kernel
* @submodule Kernel
*/
#ifndef KERNEL_C
#define KERNEL_C

#include "modules/screen.h"

kmain()
{
	Screen.clear();
	Screen.print("modularOS");

	// Ring 0, we can use a pointer to point
	// to video memory directly and modify its contents.
	char * video_memory = (char *) 0xB8000;

	// Starting from top left:
	// zero & even are the characters
	// odds are the color of the character
	video_memory[15] = 0x0C;
	video_memory[17] = 0x0C;
}

#endif