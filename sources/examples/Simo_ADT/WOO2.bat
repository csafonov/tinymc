call CfgTmc

set TMCLSP=%TMCC%
rem set OUTC_DIR=.\Simo_ADT_ws\TunerDemo\jni
set OUTC_DIR=.\Simo_AS\app\src\main\jni
copy 	.\OutL\TestO.sym.dat .\Stubs\
%TMCLSP% -c -C   -d -q  -g2  -w TestO  -r .\Stubs\TestO.m -l %OUTC_DIR%\testO2.err.log -@ woo2_rsp2.txt  -o %OUTC_DIR%\ >outC2.txt

pause