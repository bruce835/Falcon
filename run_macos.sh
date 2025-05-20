nasm -f macho64 asm/main.asm -o asm/main.o
ld asm/main.o -o main -e _start -macosx_version_min 10.13 -static
./main
