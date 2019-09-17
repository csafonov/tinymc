cmake_minimum_required(VERSION 2.8)
project (TMCDebugger)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/Setup)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../../../bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
include_directories("${PROJECT_SOURCE_DIR}")

include_directories("../DLL_SRC/tmclib")
#include_directories("Stubs")

#include ( "SrcList.cmake" )
#include ( "MatTermMexList.cmake" )
##  include ( "MexLibList.cmake" )
#include ("Lapack_lib/Lapack_lib_src.cmake")
#include ("fdlibm/fdlibm_src.cmake")
#include ("fftlib/fftlib_src.cmake")


set(tmclib_SRCS
 ../DLL_SRC/tmclib/cmatrix.c
 ../DLL_SRC/tmclib/tmcmstruct.c
# ../DLL_SRC/tmclib/tmcmath.c
 ../DLL_SRC/tmclib/graphic_stubs.c
# ../DLL_SRC/tmclib/lapackutils.c
# ../DLL_SRC/tmclib/tmc_unsupported.c
 ../DLL_SRC/tmclib/tmccell.c
 ../DLL_SRC/tmclib/tmcexcpt.c 
	../DLL_SRC/tmclib/tmclib.c
	../DLL_SRC/tmclib/tmcstringhash.c
	../DLL_SRC/tmclib/tmcio.c
	../DLL_SRC/tmclib/tmcdebugger.c
../DLL_SRC/tmclib/tmc.h
../DLL_SRC/tmclib/cmatrix.h
../DLL_SRC/tmclib/tmcstringhash.h
../DLL_SRC/tmclib/tmc.h
../DLL_SRC/tmclib/clapack.h
../DLL_SRC/tmclib/clapack_types.h
../DLL_SRC/tmclib/f2c.h
../DLL_SRC/tmclib/mex.h
../DLL_SRC/tmclib/mex2tmc.h
)

set (TMCDBG_SRCS
SplitWnd.cpp
SplitWnd.h
StdAfx.cpp
tmcdbgW.cpp
tmcdbgW.h
tmcdbgWDlg.cpp
tmcdbgWDlg.h
tmcdbg_w.c
tmcdbgW.rc
)
if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  add_definitions(-DUNICODE)
#  add_definitions(-DMSDOS)
  add_definitions(-D_TMCRTVC6_)
  add_definitions(-DWIN32)
  add_definitions(-D_WINDOWS)
  add_definitions(-DTMCRTVC6_EXPORTS)

  add_definitions(-DNO_BLAS_WRAP)
  
  add_definitions(-DTMCMEX_DLL)
  add_definitions(-DTMCDBG_CLI)
  #add_definitions(-MT)
  add_definitions(-DTMC_NO_SEH)

  add_definitions(-D_AFXDLL)
  set(CMAKE_MFC_FLAG 1)

#  SET(MY_LINK_FLAGS    "-DEF:Stubs/Conductor_ServerDLL.def")
##  SET(MY_LINK_FLAGS    "-DEF:tmclib/tmcrt_vc.def")

##  SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MY_COMPILE_FLAGS}" )
set (MY_LINK_FLAGS "-SUBSYSTEM:WINDOWS")

  SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${MY_LINK_FLAGS}" )

endif()


# ${SIMOLib_SRCS} - temporary excluded
add_executable(TMCDebugger  ${TMCDBG_SRCS} ${tmclib_SRCS}  )

source_group("TMCDBG"        FILES ${TMCDBG_SRCS})
source_group("tmclib"        FILES ${tmclib_SRCS})



