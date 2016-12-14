#!/bin/bash

#
# Copy compiled kernel to iso `boot/` folder
#
cp ${BUILD_FOLDER}/Kernel.bin ${SOURCE_FOLDER}/ISO/boot/Kernel.bin

#
# Create ISO with GRUB as the bootloader
#
grub-mkrescue -o ${BUILD_FOLDER}/${ISO_FILENAME} ${SOURCE_FOLDER}/ISO/

if [ "$?" = "1" ]; then
	echo "There was an error while building the ISO." 1>&2
	exit 1
fi

#
# Cleanup
#
rm -f ${SOURCE_FOLDER}/ISO/boot/Kernel.bin

echo "ISO created!"
