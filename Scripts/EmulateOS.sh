#!/bin/bash

if [ ${QEMU_EMULATE} = "kernel" ]; then
	#
	# Emulate Kernel directly
	#
	qemu-system-x86_64 -kernel ${BUILD_FOLDER}/Kernel.bin
else 
	#
	# Emulate with boot ISO
	#
	qemu-system-x86_64 -cdrom ${BUILD_FOLDER}/${ISO_FILENAME}
fi

if [ "$?" = "1" ]; then
	echo "There was an error emulating ${QEMU_EMULATE}." 1>&2 
	exit 1
fi
