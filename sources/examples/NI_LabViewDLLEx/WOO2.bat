call CfgTmc

set TMCLSP=%TMCC%

copy 	.\OutL\TestO.sym.dat .\Stubs\
%TMCLSP% -c -C   -d -q  -g2  -w TestO  -r .\Stubs\TestO.m -l .\OutC\testO2.err.log -@ woo2_rsp2.txt  -o .\OutC\ >outC2.txt

pause