cmake_minimum_required(VERSION 2.8)
project (TmcExample_App_caller)

#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/../../../bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#include_directories("${PROJECT_SOURCE_DIR}")

if(DEFINED ENV{<name>}) 
include_directories(C:/MyClaster/MPI/Include)
include_directories(../../Include)
include_directories(./dll/Stubs)
link_directories(../../lib/x64)

set(App_caller_SRCS
 App_caller/App_caller.c
)
set(dll_SRCS
	dll/OutC/filter_.c
	dll/OutC/getcurloop.c
	dll/OutC/TestO.c
	dll/OutC/TestO.globals.c
	dll/OutC/TestO._init_hash_data.c
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
  
##  SET(MY_LINK_FLAGS    "-DEF:tmclib/tmcrt_vc.def")

##  SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MY_COMPILE_FLAGS}" )
  SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${MY_LINK_FLAGS}" )

endif()



add_library(dll_getcurloop SHARED ${dll_SRCS} )
add_executable(SIMO_caller  ${App_caller_SRCS} )



