# Build tmccoGPL
# Shmuel Safonov (C) 2015, GPL licence

# -Wall -Wextra 
BINDIR=../../bin

all:	lex.tmclsp_.cpp TmcLspParser.tab.cpp TmcLspParser.tab.hpp TmcParParser.tab.cpp TmcParParser.tab.hpp lex.tmcpar_.cpp *.cpp *.h
	gcc  -g -D LINUX_GPL -D UNICODE -O0  -D BLD_RTL_FEATURE=1 -masm=intel -D GCC_BUILD=1 -o  $(BINDIR)/tmccoD.out  tmc_asmgen.cpp tmc_rtl.cpp tmc_string_hash.cpp  tmclsp_rtlgen.cpp tmclsp_tree.cpp tmc_mak_lc.cpp    lex.tmclsp_.cpp tmc_tree_debug.cpp tmclsp_matrix.cpp  tmcpar_env.cpp tmcpar_tree.cpp tmcpar_utils.cpp  TmcLspParser.tab.cpp tmc_sym_table.cpp  tmc_mak_ml.cpp TmcParParser.tab.cpp lex.tmcpar_.cpp -static  -lstdc++
	gcc   -D LINUX_GPL -D UNICODE -O0  -D BLD_RTL_FEATURE=1 -masm=intel -D GCC_BUILD=1 -o    $(BINDIR)/tmcco.out  tmc_asmgen.cpp tmc_rtl.cpp tmc_string_hash.cpp  tmclsp_rtlgen.cpp tmclsp_tree.cpp tmc_mak_lc.cpp    lex.tmclsp_.cpp tmc_tree_debug.cpp tmclsp_matrix.cpp  tmcpar_env.cpp tmcpar_tree.cpp tmcpar_utils.cpp  TmcLspParser.tab.cpp tmc_sym_table.cpp  tmc_mak_ml.cpp TmcParParser.tab.cpp lex.tmcpar_.cpp -static  -lstdc++


TmcParParser.tab.cpp TmcParParser.tab.hpp: TmcParParser.Y
	bison -o TmcParParser.tab.cpp -d -v TmcParParser.Y

lex.tmcpar_.cpp: TmcParLexer.L TmcParParser.tab.hpp
	flex -olex.tmcpar_.cpp  TmcParLexer.L


TmcLspParser.tab.cpp TmcLspParser.tab.hpp: TmcLspParser.Y
	bison -o TmcLspParser.tab.cpp -d -v TmcLspParser.Y

lex.tmclsp_.cpp: TmcLspLexer.L TmcLspParser.tab.hpp
	flex -olex.tmclsp_.cpp  TmcLspLexer.L

#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1 tmcpar_env.cpp   -static  -lstdc++
#
#
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1  tmc_sym_table.cpp  -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1 tmc_asmgen.cpp  -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1 tmc_rtl.cpp  -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1 tmc_string_hash.cpp  -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1  tmclsp_rtlgen.cpp  -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1 tmclsp_tree.cpp  -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1  tmc_mak_lc.cpp   -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1   lex.tmclsp_.cpp   -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1  tmc_tree_debug.cpp   -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1 tmclsp_matrix.cpp   -static  -lstdc++
#   	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1 tmcpar_env.cpp   -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1 tmcpar_tree.cpp   -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1 tmcpar_utils.cpp  -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1 tmc_sym_table.cpp  -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1  tmc_mak_ml.cpp  -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1  TmcLspParser.tab.cpp  -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1  TmcParParser.tab.cpp  -static  -lstdc++
#	gcc -D UNICODE -D LINUX_GPL  -D BLD_RTL_FEATURE=1  -masm=intel  -c -D GCC_BUILD=1  lex.tmcpar_.cpp  -static  -lstdc++
       
