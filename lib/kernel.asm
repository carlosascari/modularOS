;;
; Provides Kernel entry point.
;
; @module ModularOS Kernel
; @submodule Entry Point
;
bits 32
section .text
	align 4
	dd 0x1BADB002					; Multiboot Magic Number (v1)
	dd 0x00 						; Multiboot Flags
	dd - (0x1BADB002 + 0x00)		; Multiboot Checksum

global main
extern kmain
main: 
	cli								; Disable Interrupts
	call kmain						; Execute kernel main (found in kernel.c)
	hlt								; Hang
