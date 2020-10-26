call CfgTmc

echo Symbol table generation from m-files (1st pass)
mkdir .\OutL
mkdir .\OutC

type .\Stubs\external_fnc.sym.dat > .\OutL\external_fnc.sym.dat

set MATLSPGEN=%TMCC%

rem -P: generate lsp-output
%MATLSPGEN%  -P -L -w testm  -r ./Stubs/testm1.m -h ..\..\src\tmcruntime\tmclib/ -l ./OutL/testO.lsp.txt -@ woo1_rsp.txt  -o ./OutL/ >>out.txt

pause
