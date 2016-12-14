#include "Console.h"
#include "../PortIO/PortIO.h"

_Console ConsoleInstance;

Word vgaEntry(char letter, Byte fg, Byte bg) {
	Word c16 = letter;
	Word color16 = (fg | bg << 4);
	return c16 | color16 << 8;
}

void updateCursor(struct __Console * this) {
	UInt position = (this->cursorY * this->width) + this->cursorX;
	PortIO.outByte(0x3D4, 14);               // CRT Control Register: Select Cursor Location
	PortIO.outByte(0x3D5, position >> 8);    // Send the high byte across the bus
	PortIO.outByte(0x3D4, 15);               // CRT Control Register: Select Send Low byte
	PortIO.outByte(0x3D5, position);         // Send the Low byte of the cursor location
}

// DOES NOT WORK
void scrollUp(struct __Console * this, UInt lineNumber) {
    for (UInt i = 0; i < this->width * (this->height - 1); i++) {
        VideoFrameBuffer[i] = VideoFrameBuffer[this->width * lineNumber + i];
    }

    clearLine(this->height - 1 - lineNumber, this->height - 1);

    if (this->cursorY - lineNumber < 0 ) {
        this->cursorY = 0;
        this->cursorX = 0;
    } else {
        this->cursorY -= lineNumber;
    }

    updateCursor(this);
}

void clearLine(struct __Console * this, UInt from, UInt to) {
	for(UInt i = this->width * from; i < this->width * (to + 1); i++) {
		VideoFrameBuffer[i] = vgaEntry(' ', 0, 15);
	}
}

void clear(struct __Console * this) {
	clearLine(this, 0, this->height - 1);
	this->cursorX = 0;
	this->cursorY = 0;
	updateCursor(this);
}

void printCharacter(struct __Console * this, char character) {
	switch(character) {
		case (0x08):
			if (this->cursorX > 0) {
				this->cursorX--;
				VideoFrameBuffer[(this->cursorY * this->width + this->cursorX)] = vgaEntry(' ', 0, 15);
			}
			break;
		case (0x09):    
			this->cursorX = (this->cursorX + 8) & ~(8 - 1);
			break;
		case ('\r'):
			this->cursorX = 0;
			break;
		case ('\n'):
			this->cursorX = 0;
			this->cursorY++;
			break;
		default:
			VideoFrameBuffer[this->cursorY * this->width + this->cursorX] = vgaEntry(character, 0, 15);
			this->cursorX++;
			break;
	}

	if (this->cursorX >= this->width) {
		this->cursorX = 0;
		this->cursorY++;
	}

	if(this->cursorY >= this->width - 1) {
		scrollUp(this, 1);
	}

	updateCursor(this);
}

char buffer[255];
void printNumber(struct __Console * this, Int number, Boolean asHex) {
	FillMemory(buffer, 0x00, 255);
    if (asHex) {
        UIntToHexString(number, buffer);
        print(this, buffer);
    } else {
        IntToString(number, buffer);
        print(this, buffer);
    }
}

void print(struct __Console * this, String string) {
    for(UInt i = 0; i < StringLength(string); i++) {
        printCharacter(this, string[i]);
    }
}

_Console * Console(UInt width, UInt height, UInt depth) {
	_Console * this = PrivateKernelMemory.new(&ConsoleInstance);
	this->clear = clear;
	this->print = print;
	this->printCharacter = printCharacter;
	this->printNumber = printNumber;
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->scrollX = 0;
	this->scrollY = 0;
	this->cursorX = 0;
	this->cursorY = 0;
	return this;
}
