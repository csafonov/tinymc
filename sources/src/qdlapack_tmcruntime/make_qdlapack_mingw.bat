rem ------------------------- Building tmclib calling qdlapack ----------
@rem ============ configuration =================================
set CPUTYPE=%1

rem set CPUTYPE=x86
rem set CPUTYPE=x64
rem set CPUTYPE=ARM
set OPT_QD=-D USE_QDMATH
@rem =============================================
setlocal enabledelayedexpansion
@if "%CPUTYPE%"=="arm" (
echo Building for arm

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
rem @set GWIN_BINS=D:\Data_D\HSKOST\Tools\mingw-w64x86_64\mingw64\bin\
@set GWIN_BINS=D:\Data_D\HSKOST\Tools\msys2\mingw64\bin\
) else (
  
echo Building for x86 architecture by mingw
set OPT64=
set OUT_EX=w32
@set GWIN_BINS=D:\Data_D\HSKOST\Tools\MinGW\bin\
       )
)
pause

set OBJ_DIR=OutO_%OUT_EX%
set OBJLIB_DIR=OutO2_%OUT_EX%

@set PATH=%GWIN_BINS%

set MYOPT=%OPT_QD% %OPT64% -Wformat=0 -g -lm -DMSDOS  -D STATIC_LIB_MLAPACK    -D _TMC_SITARA_ -D _TMC_EMBEDDED_ -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    
@rem set MYOPT2=-DMSDOS  -D STATIC_LIB_MLAPACK    -D _TMC_SITARA_ -D _TMC_EMBEDDED_ -D _TMC_ANDROID_ -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    
set MYOPT2= %OPT_QD% %OPT64% -DMSDOS  -D STATIC_LIB_MLAPACK     -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    

@if "%CPUTYPE%"=="arm" (
set MYOPT2=%MYOPT2% -D _TMC_EMBEDDED_ -D _TMC_SITARA_ -D _TMC_ANDROID_
) else ( 
echo t
)

rem ------------------- QD configuration -------------------------------
set OPT_QD=-D USE_QDMATH
set PREC_EX=_qd_
@set PATH=%GWIN_BINS%;%PATH%;

set MYOPT=%OPT_QD% %OPT64% -Wformat=0 -g -lm -DMSDOS  -D STATIC_LIB_MLAPACK    -D _TMC_SITARA_ -D _TMC_EMBEDDED_ -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    
@rem set MYOPT2=-DMSDOS  -D STATIC_LIB_MLAPACK    -D _TMC_SITARA_ -D _TMC_EMBEDDED_ -D _TMC_ANDROID_ -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    
@rem set MYOPT2=-DVANDAL %OPT_QD% %OPT64% -DMSDOS  -D STATIC_LIB_MLAPACK     -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    
set MYOPT2=  %OPT_QD% %OPT64% -DMSDOS  -D STATIC_LIB_MLAPACK     -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    

rem goto :QDLAPACKDLL
rem goto :MLAPACK
rem goto TMCLIB

:LAPACK
	mkdir   .\%OBJ_DIR%
	cd ./lapack_lib/SRC/ 
	%CC% -c    %MYOPT%  -DNO_BLAS_WRAP     @LAPACK_LIB_LIST.txt >> ..\..\lst.txt
	move *.o ../../%OBJ_DIR%
cd ..
cd ..

:BLAS
	mkdir  .\%OBJ_DIR%
	cd ./lapack_lib/SRC_BLAS/
	%CC% -c    %MYOPT%  -DNO_BLAS_WRAP     @LAPACK_BLAS_LIST.txt >> ..\..\lst.txt
	move *.o ../../%OBJ_DIR%
cd ..
cd ..
rem pause

:F2C
	mkdir   .\%OBJ_DIR%
	cd ./lapack_lib/SRC_F2C/ 
	%CC% -c    %MYOPT%  -DMSDOS -DUSE_CLOCK -DNO_ONEXIT -DNO_BLAS_WRAP    @LAPACK_F2C_LIST.txt >> ..\..\lst.txt
	move *.o ../../%OBJ_DIR%
cd ..
cd ..
rem pause

:FFTLIB
	mkdir   .\%OBJ_DIR%
	cd ./fftlib/ 
	%CC%  -c    %MYOPT%  @fftlib_list.txt  
	move *.o ../%OBJ_DIR%
 cd ..
rem  pause

:MLAPACK
	mkdir  .\%OBJ_DIR%
	cd ./lapack_lib/ 
	%CC% -c    %MYOPT%   -D __cdecl=   MyFunc.c    ./LAMCH/qdlamch.c ./SRC/dlamch.c
	move *.o ../%OBJ_DIR%
cd ..
rem pause

:QDLAPACKDLL
	mkdir  .\%OBJLIB_DIR%
	cd .\%OBJ_DIR%
	%AR% rs ../%OBJLIB_DIR%/qdlapack%PREC_EX%%OUT_EX%.a  @..\OutO_list.txt 
	%RANLIB% ../%OBJLIB_DIR%/qdlapack%PREC_EX%%OUT_EX%.a
	rem move  tmcruntime.a  ../../lib/%CPUTYPE%/tmcruntime_minig%OUT_EX%.a
	cd ..
	%CC%  %OPT64%  -mdll   -lstdc++    -o ../../lib/%CPUTYPE%/lapack%PREC_EX%%OUT_EX%.dll    ./tmclib/qdmlapack.def ./%OBJLIB_DIR%/qdlapack%PREC_EX%%OUT_EX%.a -lquadmath -lm

rem pause

:TMCLIB
	mkdir  .\%OBJLIB_DIR%
	cd ./tmclib 
 	%CC% -c    %MYOPT2%  lapackutils_qd.c tmcmath_qd.c
	move *.o ../%OBJLIB_DIR%
cd ..

:TMCLIBDLL
	cd .\%OBJLIB_DIR%
	%AR% rs ..\%OBJLIB_DIR%\tmcrt%PREC_EX%%OUT_EX%.a  @..\OutO2_list.txt 
	%RANLIB% ..\%OBJLIB_DIR%\tmcrt%PREC_EX%%OUT_EX%.a
	cd ..
	%CC%  %OPT64%  -mdll   -lstdc++    -o ../../lib/%CPUTYPE%/tmcruntime_mingw%PREC_EX%%OUT_EX%.dll ./tmclib/tmcrt_dq.def  ./%OBJLIB_DIR%/tmcrt%PREC_EX%%OUT_EX%.a   ../../lib/%CPUTYPE%/lapack%PREC_EX%%OUT_EX%.dll -lquadmath  ../../lib/%CPUTYPE%/tmcruntime_mingw_%OUT_EX%.dll -lm
@ECHO  ------------- DONE --------------
pause




