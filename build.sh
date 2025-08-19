#!/bin/bash
set -e

BUILD_DIR=build
ISO_DIR=isodir
KERNEL_BIN=kernel.bin
GRUB_CFG=grub.cfg
ISO_NAME=asphodel.iso

echo "building asphodel kernel..."

mkdir -p $BUILD_DIR

echo "compiling boot.asm..."
nasm -f elf32 boot/boot.asm -o $BUILD_DIR/boot.o

echo "compiling kernel..."
gcc -m32 -ffreestanding -c kernel/kernelMain.c -o build/kernelMain.o
gcc -m32 -ffreestanding -c kernel/io.c -o build/io.o

echo "linking object files..."
ld -m elf_i386 -T linker.ld -z noexecstack -nostdlib -o $BUILD_DIR/$KERNEL_BIN $BUILD_DIR/boot.o $BUILD_DIR/kernelMain.o $BUILD_DIR/io.o

echo "writing grub.cfg..."
mkdir -p $ISO_DIR/boot/grub
cp $BUILD_DIR/$KERNEL_BIN $ISO_DIR/boot

cat > $ISO_DIR/boot/grub/$GRUB_CFG << EOF
set timeout=0
set default=0

menuentry "Asphodel" {
    multiboot2 /boot/$KERNEL_BIN
    boot
}
EOF

echo "building iso..."
grub-mkrescue -o $BUILD_DIR/$ISO_NAME $ISO_DIR


echo "asphodel build successful"
echo "iso created at $BUILD_DIR/$ISO_NAME"
echo ""

echo "running kernel..."
qemu-system-x86_64 -cdrom $BUILD_DIR/$ISO_NAME

echo "finished."

rm -rf build
rm -rf isodir