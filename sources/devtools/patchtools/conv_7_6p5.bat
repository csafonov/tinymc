set DST_RR=%2
set SRC_RR=%1


set SUBDIRR=SIMOMex
set SRC_DIR=%SRC_RR%\%SUBDIRR%
set DST_DIR=%DST_RR%\%SUBDIRR%
for /R %SRC_DIR% %%G in (*.m) do removetilda.exe   %SRC_DIR%\%%~nG.m   > %DST_DIR%\%%~nG.m  


pause

