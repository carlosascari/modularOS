/**
* Provides general purpose functions to aid Kernel development
*
* @module ModularOS Kernel
* @submodule Lib
*/
#ifndef LIB_H
#define LIB_H

#include "Types.h"

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

extern Halt() {
	for (;;);
}

extern UInt StringLength(String source) {
    UInt i = 1;
    while(source[i++]);
    return --i;
}

extern void CopyMemory(Pointer destination, Pointer source, UInt length) {
	String stringDestination = (String) destination;
	String stringSource = (String) source;

	for (int i = 0; i < length; i++) {
		stringDestination[i] = stringSource[i];
	}
}

extern void FillMemory(Pointer destination, char character, UInt length) {
	String stringDestination = (String) destination;

	for (int i = 0; i < length; i++) {
		stringDestination[i] = character;
	}
}

extern void ReverseString(char s[]) {
	Int i, j;
	char c;

	for (i = 0, j = StringLength(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

extern void IntToString(Int n, char s[]) {
	int i, sign;

	if ((sign = n) < 0) {/* record sign */
		n = -n;          /* make n positive */
	}

	i = 0;

	do {       /* generate digits in reverse order */
		s[i++] = n % 10 + '0';   /* get next digit */
	} while ((n /= 10) > 0);     /* delete it */
	
	if (sign < 0) {
		s[i++] = '-';
	}
	
	s[i] = '\0';

	ReverseString(s);
}

static char HEX_CHARSET [] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' ,'A', 'B', 'C', 'D', 'E', 'F' };
extern Int UIntToHexString(UInt integer, String buffer) {
    Int length = 0, i = 0;
   
    do {
        buffer[length] = HEX_CHARSET[integer & 0xF];
        length++;
        integer >>= 4;
    } while(integer != 0);

    //since we get the digits in the wrong order reverse the digits in the buffer
    for(; i < length / 2; i++) {
        buffer[i] ^= buffer[length - i - 1];
        buffer[length-i-1] ^= buffer[i];
        buffer[i] ^= buffer[length - i - 1];
    }

    buffer[length] = '\0';
    return length;
}


/**
* Paging
* @ref http://www.osdever.net/tutorials/view/implementing-basic-paging
*/
extern UInt cpu_read_cr0();
extern void cpu_write_cr0(UInt);
extern UInt cpu_read_cr3();
extern void cpu_write_cr3(UInt);

/**
* gdt
*/

#endif