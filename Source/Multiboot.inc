;;
; Provides Multiboot constants for NASM
;
; @module ModularOS Kernel
; @submodule Multiboot Structure NASM Header
;

;;
; NOTE
;
; 3.2 Machine State (https://www.gnu.org/software/grub/manual/multiboot/multiboot.pdf)
; When the boot loader invokes the 32-bit operating system, the machine must have the following state:
; 
; `EAX` Must contain the magic value `0x2BADB002`; the presence of this value indicates
; to the operating system that it was loaded by a Multiboot-compliant boot loader.
;
; `EBX` Must contain the 32-bit physical address of the Multiboot information structure
; provided by the boot loader (see Section 3.3 [Boot information format], page 8).
;

%ifndef MULTIBOOT_INC
%define MULTIBOOT_INC

MB_SEARCH                   equ 8192
MB_HEADER_MAGIC             equ 0x1BADB002
MB_BOOTLOADER_MAGIC         equ 0x2BADB002
MB_UNSUPPORTED              equ 0x0000fffc
MB_MOD_ALIGN                equ 0x00001000
MB_INFO_ALIGN               equ 0x00000004

; Flags set in the `flags` member of the multiboot header
MB_PAGE_ALIGN               equ 0x00000001
MB_MEMORY_INFO              equ 0x00000002
MB_VIDEO_MODE               equ 0x00000004
MB_AOUT_KLUDGE              equ 0x00010000

; Flags set in `mode_type` member of the multiboot header 
MB_GRAPHIC_MODE             equ 0x00000000
MB_TEXT_MODE                equ 0x00000001

%endif
