;;
; Provides Kernel entry point.
;
; @module ModularOS Kernel
; @submodule Entry Point
;
%include 'Multiboot.inc'

EXTERN KERNEL_TEXT
EXTERN KERNEL_BSS
EXTERN KERNEL_END

MB_FLAGS        equ  MB_PAGE_ALIGN | MB_MEMORY_INFO | MB_AOUT_KLUDGE; | MB_VIDEO_MODE
MB_CHECKSUM     equ -(MB_HEADER_MAGIC + MB_FLAGS)
SCREEN_WIDTH    equ 320
SCREEN_HEIGHT   equ 240
SCREEN_DEPTH    equ 32

;;
; Multiboot Header
;
BITS 32
SECTION .multiboot
GLOBAL multiboot_header
ALIGN 4
multiboot_header:
    dd MB_HEADER_MAGIC
    dd MB_FLAGS
    dd MB_CHECKSUM
    dd multiboot_header
    dd KERNEL_TEXT
    dd KERNEL_BSS
    dd KERNEL_END
    dd main
    dd MB_GRAPHIC_MODE
    dd SCREEN_WIDTH
    dd SCREEN_HEIGHT
    dd SCREEN_DEPTH

;;
; Kernel Main
;
BITS 32
SECTION .text
GLOBAL main
EXTERN KernelMain
main: 
    cli                                           ; Disable Interrupts
    mov esp, kernel_stack_top                     ; Point to kernel stack area
    push ebx                                      ; Pass multiboot_info structure
    push eax                                      ; Pass multiboot bootloader magic field
    push kernel_private_memory_start              ; Pass pointer to private kernel memory
    call KernelMain                               ; Execute kernel main (found in kernel.c)
hang:
    hlt
    jmp hang

;;
; Low-level functions
;
BITS 32
SECTION .machine
GLOBAL gdt_flush                                   ; C `extern void gdt_flush(void *);`
GLOBAL load_page_directory
GLOBAL enable_paging
gdt_flush:
    mov eax, [esp + 4]
    lgdt [eax]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:gdt_flush_ret
gdt_flush_ret:
    ret
load_page_directory:
    push ebp
    mov ebp, esp
    mov eax, esp
    mov cr3, eax
    mov esp, ebp
    pop ebp
    ret
enable_paging:
    push ebp
    mov ebp, esp
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    mov esp, ebp
    pop ebp
    ret

;;
; Low-level cpu exposing functions
;
BITS 32
SECTION .cpu
GLOBAL cpu_read_cr0
GLOBAL cpu_write_cr0
GLOBAL cpu_read_cr3
GLOBAL cpu_write_cr3
GLOBAL cpu_gdt_flush
cpu_read_cr0:
    mov eax, cr0
    retn
cpu_write_cr0:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    mov cr0,  eax
    pop ebp
    retn
cpu_read_cr3:
    mov eax, cr3
    retn
cpu_write_cr3:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]
    mov cr3, eax
    pop ebp
    retn
extern gdtEntries            ; Says that '_gp' is in another file
cpu_gdt_flush:
    lgdt [gdtEntries]        ; Load the GDT with our '_gp' which is a special pointer
    mov ax, 0x10            ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:cpu_gdt_flush_ret   ; 0x08 is the offset to our code segment: Far jump!
cpu_gdt_flush_ret:
    ret

;;
; Data
;
BITS 32
SECTION .bss
kernel_stack_bottom:
    resb 8192                                     ; Reserve 8KB for kernel stack
kernel_stack_top:
kernel_private_memory_start:
    resb 8192                                     ; Reserve 8KB for PrivateKernelMemory
kernel_private_memory_end:
