@set CPUTYPE=x86
@rem set CPUTYPE=x64

@if "%CPUTYPE%"=="x64" (
echo Building for x64 architecture by mingw-w64
@set OPT64=-m64
@set OUT_EX=w64
@set GWIN_BINS=D:\Data_D\HSKOST\Tools\mingw-w64x86_64\mingw64\bin\

) else (
echo Building for x86 architecture by mingw
@set OPT64=
@set OUT_EX=w32
@set GWIN_BINS=D:\Data_D\HSKOST\Tools\MinGW\bin\
)

@set PATH=%GWIN_BINS%;%PATH%;
@set EXEDIR=./bin

set PATH=%PATH%;..\..\lib\%CPUTYPE%;

gdb  .\bin\Ex1_w32_shared.exe < db1.txt > gdb.log.txt 2>&1
pause


