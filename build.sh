#!/bin/bash
set -e

echo "building asphodel kernel..."

mkdir -p build

echo "compiling boot.asm..."
nasm -f elf32 boot/boot.asm -o build/boot.o

echo "compiling kernel sources..."
for file in kernel/*.cpp; do
    obj="build/$(basename "${file}" .cpp).o"
    echo "  -> $file -> $obj"
    g++ -m32 -ffreestanding -fno-exceptions -fno-rtti -c "$file" -o "$obj"
done

echo "linking object files..."
ld -m elf_i386 -T linker.ld -z noexecstack -nostdlib -o build/kernel.bin build/*.o

echo "writing grub.cfg..."
mkdir -p isodir/boot/grub
cp build/kernel.bin isodir/boot

cat > isodir/boot/grub/grub.cfg << EOF
set timeout=0
set default=0

menuentry "Asphodel" {
    multiboot2 /boot/kernel.bin
    boot
}
EOF

echo "building iso..."
grub-mkrescue -o build/asphodel.iso isodir

echo "asphodel build successful"
echo "iso created at build/asphodel.iso"
echo ""

echo "running kernel..."
qemu-system-x86_64 -cdrom build/asphodel.iso

echo "finished."

# cleanup (optional: comment out if you want to keep build files)
rm -rf build
rm -rf isodir