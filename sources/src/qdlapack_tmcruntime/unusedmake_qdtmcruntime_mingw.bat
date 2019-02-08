@rem ============ configuration =================================


rem set CPUTYPE=x86
set CPUTYPE=x64
rem set CPUTYPE=ARM
rem set OPT_QD=-D USE_QDMATH

@rem =============================================
setlocal enabledelayedexpansion
@if "%CPUTYPE%"=="ARM" (
echo Building for ARM

set NDK="D:\Data_D\HSKOST\Tools\android-ndk-r10d"
set SYSROOT="!NDK!\platforms\android-8\arch-arm"
set TCHAIN="!NDK!\toolchains\arm-linux-androideabi-4.8\prebuilt\windows-x86_64"

set CC=!TCHAIN!\bin\arm-linux-androideabi-gcc --sysroot=!SYSROOT!
set AR=!TCHAIN!\bin\arm-linux-androideabi-ar 
set RANLIB=!TCHAIN!\bin\arm-linux-androideabi-ranlib 
set NDK_PLATFORM_LIB=!TCHAIN!\lib\gcc\arm-linux-androideabi\4.8\

rem set MEPATH=D:\Data_D\HSKOST\TMC\Pure\BuildLibAndroid
set ABI_CFLAGS=-march=armv7-a -mfloat-abi=softfp -mfpu=vfpv3-d16


set OPT64=
set OUT_EX=armv7
) else (

set CC=gcc
set AR=ar
set RANLIB=ranlib.exe

if "%CPUTYPE%"=="x64" (
echo Building for x64 architecture by mingw-w64
set OPT64=-m64
set OUT_EX=w64
@set GWIN_BINS=D:\Data_D\HSKOST\Tools\mingw-w64x86_64\mingw64\bin\
) else (
  
echo Building for x86 architecture by mingw
set OPT64=
set OUT_EX=w32
@set GWIN_BINS=D:\Data_D\HSKOST\Tools\MinGW\bin\
       )
)
pause


@set PATH=%GWIN_BINS%

set MYOPT=%OPT_QD% %OPT64% -Wformat=0 -g -lm -DMSDOS  -D STATIC_LIB_MLAPACK    -D _TMC_SITARA_ -D _TMC_EMBEDDED_ -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    
@rem set MYOPT2=-DMSDOS  -D STATIC_LIB_MLAPACK    -D _TMC_SITARA_ -D _TMC_EMBEDDED_ -D _TMC_ANDROID_ -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    
set MYOPT2=%OPT_QD% %OPT64% -DMSDOS  -D STATIC_LIB_MLAPACK     -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    

@if "%CPUTYPE%"=="ARM" (
set MYOPT2=%MYOPT2% -D _TMC_EMBEDDED_ -D _TMC_SITARA_ -D _TMC_ANDROID_
) else ( 
echo t
)

rem goto LAPACK

	mkdir  .\OutO
	del    .\OutO\*.o

:TMCLIB
	mkdir  .\OutO
	cd ./tmclib 
 	%CC% -c    %MYOPT2%  @TMCLIB_LIST.TXT 
	move *.o ../OutO
cd ..

pause



:FDLIBM
	mkdir   .\OutO
	cd ./fdlibm 
	%CC% -c    %MYOPT%  @FDLIB_LIST.TXT 
	move *.o ../OutO
cd ..
pause

:LAPACK
	mkdir   .\OutO
	cd ./lapack_lib/SRC/ 
	%CC% -c    %MYOPT%  -DNO_BLAS_WRAP     @LAPACK_LIB_LIST.txt >> ..\..\lst.txt
	move *.o ../../OutO
cd ..
cd ..

pause

:BLAS
	mkdir  .\OutO
	cd ./lapack_lib/SRC_BLAS/
	%CC% -c    %MYOPT%  -DNO_BLAS_WRAP     @LAPACK_BLAS_LIST.txt 
	move *.o ../../OutO
cd ..
cd ..
pause
:F2C
	mkdir   .\OutO
	cd ./lapack_lib/SRC_F2C/ 
	%CC% -c    %MYOPT%  -DMSDOS -DUSE_CLOCK -DNO_ONEXIT -DNO_BLAS_WRAP    @LAPACK_F2C_LIST.txt
	move *.o ../../OutO
cd ..
cd ..
pause
:FFTLIB
	mkdir   .\OutO
	cd ./fftlib/ 
	%CC%  -c    %MYOPT%  @fftlib_list.txt  
	move *.o ../OutO
 cd ..
 pause

:MLAPACK
	mkdir  .\OutO
	cd ./lapack_lib/ 
	%CC% -c    %MYOPT%   -D __cdecl=   MyFunc.c
	move *.o ../OutO
cd ..
pause


:TMCLIBAR

@rem 	find ./OutO  -maxdepth 1   -type f -iname *.o    > OutO_list.txt 
	%AR% rs tmcruntime.a  @OutO_list.txt 
	%RANLIB% tmcruntime.a
	move  tmcruntime.a  ../../lib/tmcruntime_mingw%OUT_EX%.a
:TMCLIBDLL
	gcc  -m64 -mdll -static  -lstdc++    -o ../../lib/tmcruntime_mingw%OUT_EX%.dll ./tmclib/tmcrt_vc.def    ../../lib/tmcruntime_mingw%OUT_EX%.a -lm



pause
