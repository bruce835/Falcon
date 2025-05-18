nasm -f macho64 asm/example.asm -o asm/example.o
ld asm/example.o -o example -e _start -macosx_version_min 10.13 -static
./example
