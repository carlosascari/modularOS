#include "screen.h"

_Screen Screen = {
    .clear = clear,
    .clearLine = clearLine,
    .updateCursor = updateCursor,
    .scrollUp = scrollUp,
    .newLineCheck = newLineCheck,
    .printch = printch,
    .print = print
};

/**
* @private
* @property cursorX
*/
int cursorX = 0;

/**
* @private
* @property cursorY
*/
int cursorY = 0;

/**
* @final
* @private
* @property SCREEN_WIDTH
*/
const uint8 SCREEN_WIDTH = 80;

/**
* @final
* @private
* @property SCREEN_HEIGHT
*/
const uint8 SCREEN_HEIGHT = 25;

/**
* @final
* @private
* @property SCREEN_DEPTH
*/
const uint8 SCREEN_DEPTH = 2;

/**
* @method clearLine
* @param from
* @param to
*/
void clearLine(uint8 from, uint8 to)
{
    uint16 i = SCREEN_WIDTH * from * SCREEN_DEPTH;
    string vidmem = (string) 0xb8000;
    for(i; i < (SCREEN_WIDTH * (to + 1) * SCREEN_DEPTH); i++)
    {
        vidmem[i] = 0x0;
    }
}

/**
* @method updateCursor
*/
void updateCursor()
{
    unsigned temp;

    temp = cursorY * SCREEN_WIDTH + cursorX;    // Position = (y * width) +  x

    Machine.outportb(0x3D4, 14);                        // CRT Control Register: Select Cursor Location
    Machine.outportb(0x3D5, temp >> 8);                 // Send the high byte across the bus
    Machine.outportb(0x3D4, 15);                        // CRT Control Register: Select Send Low byte
    Machine.outportb(0x3D5, temp);                      // Send the Low byte of the cursor location
}

/**
* @method clear
*/
void clear()
{
    clearLine(0, SCREEN_HEIGHT-1);
    cursorX = 0;
    cursorY = 0;
    updateCursor();
}

/**
* @method scrollUp
* @param lineNumber
*/
void scrollUp(uint8 lineNumber)
{
    string vidmem = (string)0xb8000;
    uint16 i = 0;
    for (i; i < SCREEN_WIDTH * (SCREEN_HEIGHT-1) * SCREEN_DEPTH; i++)
    {
        vidmem[i] = vidmem[i+SCREEN_WIDTH*SCREEN_DEPTH*lineNumber];
    }

    clearLine(SCREEN_HEIGHT-1-lineNumber,SCREEN_HEIGHT-1);

    if((cursorY - lineNumber) < 0 ) 
    {
        cursorY = 0;
        cursorX = 0;
    } 
    else 
    {
        cursorY -= lineNumber;
    }

    updateCursor();
}

/**
* @method newLineCheck
*/
void newLineCheck()
{
    if(cursorY >=SCREEN_HEIGHT-1)
    {
        scrollUp(1);
    }
}

/**
* @method printch
* @param c
*/
void printch(char c)
{
    string vidmem = (string) 0xb8000;     

    switch(c)
    {   
        case (0x08):
            if (cursorX > 0) 
            {
                cursorX--;									
                vidmem[(cursorY * SCREEN_WIDTH + cursorX) * SCREEN_DEPTH] = 0x00;
            }
	        break;
        case (0x09):    
            cursorX = (cursorX + 8) & ~(8 - 1);
            break;
        case ('\r'):
            cursorX = 0;
            break;
        case ('\n'):
            cursorX = 0;
            cursorY++;
            break;
        default:
            vidmem [((cursorY * SCREEN_WIDTH + cursorX)) * SCREEN_DEPTH] = c;
            vidmem [((cursorY * SCREEN_WIDTH + cursorX)) * SCREEN_DEPTH + 1] = 0x0F;
            cursorX++; 
            break;
    }

    if(cursorX >= SCREEN_WIDTH)                                                                   
    {
        cursorX = 0;                                                                
        cursorY++;                                                                    
    }
    newLineCheck();
    updateCursor();
}

/**
* @method printch
* @param ch
*/
void print(string ch)
{
    uint16 i = 0;
    for(i; i < String.length(ch); i++)
    {
        printch(ch[i]);
    }
}
