#!/bin/bash
SOURCE_FOLDER='lib'
ISO_FOLDER='modularOS'
MODULES_FOLDER='modules' 
MODULES=(					# NOTE: Add here in a new line your own kernel module filename and place in lib/modules folder.
	machine 
	string 
	screen
)

mkdir -p ${MODULES_FOLDER}

# Clean up existing modules and compiled kernel copies
rm -f ${MODULES_FOLDER}/*
rm -f kernel.bin
rm -f iso/${ISO_FOLDER}/boot/kernel.bin

# Compile Kernel entry point
echo "Compiling kernel entry point (multiboot)"
nasm -f elf32 ${SOURCE_FOLDER}/kernel.asm -o ${MODULES_FOLDER}/kernel_asm

# Compile Kernel Main
echo Compiling kernel main
gcc -m32 -c ${SOURCE_FOLDER}/kernel.c -o ${MODULES_FOLDER}/kernel_c -ffreestanding -w

# Compile Modules 
for module in "${MODULES[@]}"
do :
   echo Compiling module: $module
   gcc -m32 -c ${SOURCE_FOLDER}/${MODULES_FOLDER}/$module.c -o ${MODULES_FOLDER}/$module -ffreestanding -w
done

# Create new array with modules folder appened to each module
MODULES_PATH=( "${MODULES[@]/#/${MODULES_FOLDER}/}" )

# Link kernel and modules
ld -m elf_i386 -T ${SOURCE_FOLDER}/link.ld -o kernel.bin ${MODULES_FOLDER}/kernel_asm ${MODULES_FOLDER}/kernel_c ${MODULES_PATH[*]}

echo Done!

## ISO

# Copy compiled kernel to iso `boot/` folder
cp kernel.bin iso/${ISO_FOLDER}/boot/kernel.bin

# Create ISO with GRUB as the bootloader
grub-mkrescue -o iso/modularOS.iso iso/${ISO_FOLDER}/

# Run Emulator

## Emulate Kernel 
# qemu-system-x86_64 -kernel kernel.bin

# Emulate ISO
qemu-system-x86_64 -cdrom iso/modularOS.iso
