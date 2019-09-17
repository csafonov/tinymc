call CfgTmc
set FFN=.\MatSRC\getfrdRL.m

%TMCC% -d -c -C  -h .\Stubs\TestO.sym.dat    -g2     -f %FFN%  -l .\OutC\TestOx.err.log  -o .\OutC\ > TestOx.txt

rem -S    -q
pause


