copy ..\..\..\src\tmcruntime\tmclib\tmcrt_vc.def .\tmcruntime_mingw_w64.def
copy ..\..\..\src\qdlapack_tmcruntime\tmclib\tmcrt_dq.def .\tmcruntime_mingw_qd_w64.def

set PATH="C:\Program Files (x86)\Microsoft Visual Studio 8\VC\bin"
call vcvars32.bat
lib /def:tmcruntime_mingw_w64.def   /out:tmcruntime_mingw_w64.lib /machine:x64
lib /def:tmcruntime_mingw_qd_w64.def   /out:tmcruntime_mingw_qd_w64.lib /machine:x64

pause
