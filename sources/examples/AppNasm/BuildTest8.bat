@ECHO ON
set ASME=nasm.exe
%ASME%  -O0    -l .\testO.asm.lst  -o ..\bin\testO.exe   .\TestO.code.asm
pause