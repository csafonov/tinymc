cmake_minimum_required(VERSION 2.8)
project (ReadJsonDLL)

set(TMCLIB_SRC_DIR ${CMAKE_SOURCE_DIR}/../../src/tmcruntime)
## set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/Bin)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
include_directories("${PROJECT_SOURCE_DIR}")

include_directories("../../src/tmcruntime/tmclib")
include_directories("Stubs")

include ( "SrcList.cmake" )
include (${CMAKE_SOURCE_DIR}/JsonParser/JsonParser.cmake)
include (${TMCLIB_SRC_DIR}/Lapack_lib/Lapack_lib_src.cmake)
# include (${TMCLIB_SRC_DIR}/fdlibm/fdlibm_src.cmake)
include (${TMCLIB_SRC_DIR}/fftlib/fftlib_src.cmake)

set(tmclib_SRCS
 ${TMCLIB_SRC_DIR}/tmclib/cmatrix.c
 ${TMCLIB_SRC_DIR}/tmclib/tmcmstruct.c
 ${TMCLIB_SRC_DIR}/tmclib/tmcmath.c
 ${TMCLIB_SRC_DIR}/tmclib/graphic_stubs.c
 ${TMCLIB_SRC_DIR}/tmclib/lapackutils.c
 ${TMCLIB_SRC_DIR}/tmclib/tmc_unsupported.c
 ${TMCLIB_SRC_DIR}/tmclib/tmccell.c
 ${TMCLIB_SRC_DIR}/tmclib/tmcexcpt.c 
	${TMCLIB_SRC_DIR}/tmclib/tmclib.c
	${TMCLIB_SRC_DIR}/tmclib/tmcstringhash.c
	${TMCLIB_SRC_DIR}/tmclib/tmcio.c
	${TMCLIB_SRC_DIR}/tmclib/tmcdebugger.c
${TMCLIB_SRC_DIR}/tmclib/tmc.h
${TMCLIB_SRC_DIR}/tmclib/cmatrix.h
${TMCLIB_SRC_DIR}/tmclib/tmcstringhash.h
${TMCLIB_SRC_DIR}/tmclib/tmc.h
${TMCLIB_SRC_DIR}/tmclib/clapack.h
${TMCLIB_SRC_DIR}/tmclib/clapack_types.h
${TMCLIB_SRC_DIR}/tmclib/f2c.h
${TMCLIB_SRC_DIR}/tmclib/mex.h
${TMCLIB_SRC_DIR}/tmclib/mex2tmc.h
)



set (MLAPACK_SRCS
${TMCLIB_SRC_DIR}/lapack_lib/MyFunc.c
)
set (Main_SRCS
Stubs/main.c
##Stubs/ReadJsonDLL.c
##Stubs/ReadJsonDLL.def
##tmclib/tmcrt_vc.def
)
if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  add_definitions(-DUNICODE)
  add_definitions(-DMSDOS)
  add_definitions(-D_TMCRTVC6_)
  add_definitions(-DWIN32)
  add_definitions(-D_WINDOWS)
  add_definitions(-DTMCRTVC6_EXPORTS)

  add_definitions(-DNO_BLAS_WRAP)
  
  add_definitions(-DTMCMEX_DLL)
  
  
 ## SET(MY_LINK_FLAGS    "-DEF:Stubs/ReadJsonDLL.def")
##  SET(MY_LINK_FLAGS    "-DEF:tmclib/tmcrt_vc.def")

##  SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MY_COMPILE_FLAGS}" )
  SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${MY_LINK_FLAGS}" )

endif()


add_executable(ReadJson  ${Main_SRCS} ${APP_SRCS} ${JsonParser_SRCS} ${MLAPACK_SRCS} ${tmclib_SRCS} ${FDLIBM_SRCS} ${LAPACK_SRCS} ${BLAS_SRCS} ${F2C_SRCS} ${FFTLIB_SRCS} )

source_group("Main"    FILES ${Main_SRCS})
source_group("APP_C"    FILES ${APP_SRCS})
source_group("JsonParser"    FILES ${JsonParser_SRCS})
source_group("MLAPACK"        FILES ${MLAPACK_SRCS})
source_group("tmclib"        FILES ${tmclib_SRCS})
source_group("FDLIBM"        FILES ${FDLIBM_SRCS})
source_group("LAPACK"        FILES ${LAPACK_SRCS})
source_group("BLAS"        FILES ${BLAS_SRCS})
source_group("F2C"        FILES ${F2C_SRCS})
source_group("FFTLIB"        FILES ${FFTLIB_SRCS})



