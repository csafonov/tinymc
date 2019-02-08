set PATH=D:\Data_D\HSKOST\Tools\MinGW\bin;

rem --wincompat
win_flex  -olex.removetilda_.cpp  removetilda.L
gcc -oremovetilda.exe lex.removetilda_.cpp -static  -lstdc++

pause
