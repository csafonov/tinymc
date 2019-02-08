copy ..\..\..\src\tmcruntime\tmclib\tmcrt_vc.def .\tmcruntime_mingw_w32.def
copy ..\..\..\src\qdlapack_tmcruntime\tmclib\tmcrt_dq.def .\tmcruntime_mingw_qd_w32.def

set PATH="C:\Program Files (x86)\Microsoft Visual Studio 8\VC\bin"
call vcvars32.bat
lib /def:tmcruntime_mingw_w32.def   /out:tmcruntime_mingw_w32.lib /machine:x86
lib /def:tmcruntime_mingw_qd_w32.def   /out:tmcruntime_mingw_qd_w32.lib /machine:x86

pause
