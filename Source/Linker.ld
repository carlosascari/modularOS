OUTPUT_FORMAT(elf32-i386)
ENTRY(main)
SECTIONS
{
	. = 0x100000;
	.text : {
		KERNEL_TEXT = .;
		*(.multiboot);
		*(.text);
		*(.machine);
		. = ALIGN(4096);
	}
	.data : {
		KERNEL_DATA = .;
		*(.data);
		*(.rodata);
		. = ALIGN(4096);
	}
	.bss : {
		KERNEL_BSS = .;
		*(.bss);
		. = ALIGN(4096);
	}
	KERNEL_END = .;
}
