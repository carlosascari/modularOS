#!/bin/bash

#
# Compile Kernel entry point
#
echo "Compiling Kernel.s (Boot)"
nasm -f elf32 ${SOURCE_FOLDER}/Kernel.s -o ${BUILD_FOLDER}/Kernel_S -I ${SOURCE_FOLDER}/

if [ "$?" = "1" ]; then
	echo "Failed to compile kernel boot entry point (Kernel.s): " 1>&2
	exit 1
fi

#
# Compile Kernel Main
#
echo "Compiling Kernel.c (Main)"
gcc -m32 -c ${SOURCE_FOLDER}/Kernel.c -o ${BUILD_FOLDER}/Kernel_C -ffreestanding -w -std=c99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector

if [ "$?" = "1" ]; then
	echo "Failed to compile kernel main (Kernel.c) " 1>&2
	exit 1
fi

#
# Compile Kernel Modules
#
for module in "${MODULES[@]}"
do :
	echo Compiling module: $module
	gcc -m32 -c ${MODULES_FOLDER}/${module}/$module.c -o ${BUILD_FOLDER}/$module -ffreestanding -w -std=c99 -nostdlib -nostdinc -fno-builtin -fno-stack-protector

	if [ "$?" = "1" ]; then
		echo "Failed to compile module: "$module 1>&2
		exit 1
	fi
done

#
# Create new array with modules folder appened to each module
#
MODULES_PATH=( "${MODULES[@]/#/${BUILD_FOLDER}/}" )

#
# Linker
#
ld -m elf_i386 -T ${SOURCE_FOLDER}/Linker.ld -o ${BUILD_FOLDER}/Kernel.bin ${BUILD_FOLDER}/Kernel_S ${BUILD_FOLDER}/Kernel_C ${MODULES_PATH[*]}

if [ "$?" = "1" ]; then
	echo "There was an error during linking" 1>&2
	exit 1
fi

echo "Kernel compiled succesfully!"
