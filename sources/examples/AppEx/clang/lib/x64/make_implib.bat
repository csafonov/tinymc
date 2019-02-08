rem set PATH=D:\Data_D\HSKOST\Tools\BCC101\bin
set PATH="C:\Program Files (x86)\Microsoft Visual Studio 8\VC\bin"
set TMCLIBS_PATH=D:\Data_D\HSKOST\TMC\rel_sourceforge\tmc_src-1.10\lib\x64\

rem implib -aa tmcruntime_mingw_w64.lib %TMCLIBS_PATH%tmcruntime_mingw_w64.dll
call vcvars32.bat
copy D:\Data_D\HSKOST\TMC\rel_sourceforge\tmc_src-1.10\src\tmcruntime\tmclib\tmcrt_vc.def tmcruntime_mingw_w64.def
lib /def:tmcruntime_mingw_w64.def   /out:tmcruntime_mingw_w64.lib /machine:x64
pause
