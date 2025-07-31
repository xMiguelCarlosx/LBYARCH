nasm -f win64 labgroup7ASM.asm
gcc -c labgroup7C.c -o labgroup7C.obj -m64
gcc labgroup7ASM.obj labgroup7C.obj -o labgroup7C.exe -m64
labgroup7C.exe
