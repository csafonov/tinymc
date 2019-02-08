cd D:\Data_D\HSKOST\TMC\rel_github\tmc_src-1.11\sources\src\tmcruntime\
path=%PATH%;D:\Data_D\HSKOST\Tools\cmake-3.7.1-win64-x64\bin;
rem cmake -H. -B../../../rt_build_x86 -G "Visual Studio 8 2005"
cmake -H. -B../../../rt_build_64 -G "Visual Studio 15 2017 Win64"
cmake --build ../../../rt_build_64
pause