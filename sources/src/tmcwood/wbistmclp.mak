##PATH="C:\Program%Files\GnuWin32\bin"
PATH="D:\Data_D\HSKOST\Tools\bison_flex\"

all: lex.tmclsp_.cpp TmcLspParser.tab.cpp TmcLspParser.tab.hpp lex.tmcpar_.cpp TmcParParser.tab.cpp TmcParParser.tab.hpp


TmcLspParser.tab.cpp TmcLspParser.tab.hpp: TmcLspParser.y
	win_bison -o TmcLspParser.tab.cpp -d -v TmcLspParser.y

lex.tmclsp_.cpp: TmcLspLexer.l TmcLspParser.tab.hpp
	win_flex -olex.tmclsp_.cpp  TmcLspLexer.l

#tmc_kw.h  
#tmc_kw.h : tmc_kw.gperf
#	gperf --output-file tmc_kw.h  -t -C -D -G -L C++ -Z octave_kw_hash  tmc_kw.gperf

TmcParParser.tab.cpp TmcParParser.tab.hpp: TmcParParser.y
	win_bison -o TmcParParser.tab.cpp -d -v TmcParParser.y

lex.tmcpar_.cpp: TmcParLexer.l TmcParParser.tab.hpp
	win_flex -olex.tmcpar_.cpp  TmcParLexer.l
