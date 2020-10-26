win_bison -o JsonRead.tab.c  -d -v JsonRead.y
win_flex   -olex.JsonRead_lin.c JsonRead.l  
pause
