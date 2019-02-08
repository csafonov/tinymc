call TmcSetEnv.bat

type .\Stubs\external_fnc.sym.dat > .\OutL\external_fnc.sym.dat
%MATLSPGEN%  -S -L   -w TestO  -r .\Stubs\TestO.m -h ..\..\include/ -l .\OutL\testO.lsp.txt -@ WOO1_rsp.txt  -o .\OutL\ >>out.txt
copy 	.\OutL\TestO.sym.dat .\Stubs\
pause