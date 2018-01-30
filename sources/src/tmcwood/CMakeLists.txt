cmake_minimum_required(VERSION 2.8)
project (tmcc)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../../../bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
include_directories("${PROJECT_SOURCE_DIR}")

set(tmcc_SRCS
	tmc_rtl.cpp
	tmc_string_hash.cpp
	tmclsp_rtlgen.cpp
	tmclsp_tree.cpp
	lex.tmclsp_.cpp
	tmc_tree_debug.cpp
	tmclsp_matrix.cpp
	tmcpar_env.cpp
	tmcpar_tree.cpp
	tmcpar_utils.cpp
	TmcLspParser.tab.cpp
	tmc_sym_table.cpp
	tmc_mak_ml.cpp
	tmc_mak_lc.cpp
	tmc_asmgen.cpp
	TmcParParser.tab.cpp
	lex.tmcpar_.cpp
)

  add_definitions(-DBLD_RTL_FEATURE=1)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  add_definitions(-DUNICODE)
endif()



add_executable(tmcc ${tmcc_SRCS})



