PATH=C:\BCC55\Bin

make -f btmclib.mak.txt > btmclib_bld.lst

move *.obj .\DebugBcc55\
move *.lib .\DebugBcc55\

pause
