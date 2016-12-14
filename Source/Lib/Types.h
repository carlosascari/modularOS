/**
* Provides type definitions.
*
* @module ModularOS Kernel
* @submodule Type Definitions
*/
#ifndef TYPES_H
#define TYPES_H

#define PACKED __attribute__((packed))

#define Null (void * 0);

typedef int Boolean;
#define true (0x1)
#define false (0x0)
#define True true
#define False false

typedef signed char Int8;
typedef unsigned char UInt8;
typedef unsigned char Byte;

typedef signed short Int16;
typedef unsigned short UInt16;
typedef unsigned short Word;

typedef signed int Int;
typedef signed int Int32;
typedef unsigned int UInt;
typedef unsigned int UInt32;
typedef unsigned int Dword;

typedef signed long long Int64;
typedef unsigned long long UInt64;
typedef unsigned long long Qword;

typedef char * String;

typedef void * Pointer;

typedef	unsigned int PhysicalAddress;
typedef	unsigned int VirtualAddress;

#endif
