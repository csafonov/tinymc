call CfgTmc

set TMCLSP=%TMCC%

rem From m-code:
copy 	.\OutL\testm.sym.dat .\Stubs\
%TMCLSP% -c -C   -d -q  -g2  -w testm  -r .\Stubs\testm1.m -l .\OutC\testO2.err.log -@ woo2_rsp2.txt  -o .\OutC\ >outC2.txt

rem From LSP files:
rem %TMCLSP% -S -c -C   -d -q  -g2  -w TestO  -r .\OutL\TestO.lsp -l .\OutC\testO2.err.log -@ woo2_rspL.txt  -o .\OutC\ >outC2.txt



pause