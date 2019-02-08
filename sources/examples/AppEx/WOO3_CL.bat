@rem ============ configuration =================================

rem @set CPUTYPE=x86
@set CPUTYPE=x64

@set TMCLIBLINK=shared
@rem set TMCLIBLINK=static

@rem =============================================


@if "%CPUTYPE%"=="x64" (

echo Building for x64 architecture by mingw-w64
@set OPT64=-m64
@set OUT_EX=w64
rem @set GWIN_BINS=D:\Data_D\HSKOST\Tools\mingw-w64x86_64\mingw64\bin\
@set GWIN_BINS=D:\Data_D\HSKOST\Tools\LLVM\bin\
	

	@if "%TMCLIBLINK%"=="shared" (
	echo shared linking with TMCLIB
	set TMCLIBL=tmcruntime_mingw_w64.lib
	) else	(
	echo static linking with TMCLIB
	set TMCLIBL=tmcruntime_mingw_w64.a
	)
@set INCLUDE=
@set LIBS=..\clang\lib\x64\

) else (

echo Building for x86 architecture by mingw
@set OPT64=
@set OUT_EX=w32
rem @set GWIN_BINS=D:\Data_D\HSKOST\Tools\MinGW\bin\
@set GWIN_BINS=D:\Data_D\HSKOST\Tools\LLVM\bin\

	@if "%TMCLIBLINK%"=="shared" (
	echo shared linking with TMCLIB
	set TMCLIBL=tmcrtvc8_x64.lib 
	) else (
	echo static linking with TMCLIB
	set TMCLIBL=tmcruntime_mingw_w32.a
	)

)

@set PATH=%GWIN_BINS%;%PATH%;
rem @set CC=gcc
@set CC=clang
@set EXEDIR=bin

@rem set MYOPT=-Wformat=0  -ftree-vectorize -unroll-loops --param max-unroll-times=4 -fverbose-asm -Ofast -O3 -D TMCMEX_DLL -D SIMOLIB_EXPORTS -D _TMC_SITARA_ -D _TMC_EMBEDDED_ 
@set MYOPT=%OPT64% -Wformat=0  -ftree-vectorize -unroll-loops --param max-unroll-times=4 -fverbose-asm -Ofast -O3 -D TMCMEX_DLL -D SIMOLIB_EXPORTS  
@rem set MYOPT2=-DTMC_NO_SEH=";"  -DTRY=";"  -DFINALLY=";"  -DENDFINALLY=";"  -DBLG_GCC -DEXTINY0_EXPORTS

@set MYOPT2=-DTMC_NO_SEH=";"  -DTRY=";" -DCATCH=";" -DENDCATCH=";" -DFINALLY=";"  -DENDFINALLY=";"  -DBLG_GCC -DEXTINY0_EXPORTS

@mkdir  .\OutO2
@dir  .\OutC\*.c /B      > OutC_listC2.txt 
@cd   .\OutC\

@rem gcc  %MYOPT% %MYOPT2%  -D UNICODE -I../../../include/  -I./../Stubs/ @..\OutC_listC2.txt ../MexSRC/ExMex1.c ../App_caller/Extiny_caller.c  ./../../../lib/tmcruntime_minigw32.a -lm -o ../%EXEDIR%/Ex1.exe
@rem gcc  %MYOPT% %MYOPT2%  -D UNICODE -I../../../include/  -I./../Stubs/ @..\OutC_listC2.txt ../MexSRC/ExMex1.c ../App_caller/Extiny_caller.c  ./../../../lib/tmcruntime_minigw32.dll -lm -o ../%EXEDIR%/Ex1_.exe
@rem gcc  -m64 %MYOPT% %MYOPT2%  -D UNICODE -I../../../include/  -I./../Stubs/ @..\OutC_listC2.txt ../MexSRC/ExMex1.c ../App_caller/Extiny_caller.c  ./../../../lib/tmcruntime_minigw64.a -lm -o ../%EXEDIR%/Ex1_x64.exe 

rem %CC% -g -D TMCDEBUG %MYOPT% %MYOPT2% -D UNICODE -I../../../include/  -I./../Stubs/ @..\OutC_listC2.txt ../MexSRC/ExMex1.c ../App_caller/Extiny_caller.c  ./../../../lib/%CPUTYPE%/%TMCLIBL% -lm -o ../%EXEDIR%/Ex1_%OUT_EX%_%TMCLIBLINK%.exe
%CC% -L %LIBS% -g  %MYOPT% %MYOPT2% -D UNICODE -I../../../include/  -I./../Stubs/ @..\OutC_listC2.txt ../MexSRC/ExMex1.c ../App_caller/Extiny_caller.c   ../clang/lib/x64/%TMCLIBL%  -o ../%EXEDIR%/Ex1_%OUT_EX%_%TMCLIBLINK%1.exe

cd ..
rem Ex1_
rem Ex1_x64.exe
set PATH=%PATH%;..\..\lib\%CPUTYPE%\;
%EXEDIR%\Ex1_%OUT_EX%_%TMCLIBLINK%1.exe
rem .\bin\Ex1_w32_shared.exe
pause


