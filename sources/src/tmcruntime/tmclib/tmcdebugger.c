/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license.
 * 
  *****************************************************************************/
// tmcdebugger.c

// Windows-specific code
#ifndef _TMC_EMBEDDED_
#include <windows.h>



#include "tmc.h"
#include "clapack_types.h"

#include  <math.h>
#include <stdlib.h>
#include <string.h>

#include <STDARG.H> // ANSI compatibility

#include <stdio.h>
#include <malloc.h>

#include "tmc.h"


//#ifndef TMCDBG_CLI // this symbol defined in the debugger
static char *s_module = "tmcdebugger.c";

TMC_DBG_STACK TmcDebugStack;
struct CTmcDbgCommonBlock *pTmcDbgCommonBlock;

long tmcdbgCommonMemCreate(LPCWSTR MapName, DWORD MapSize);
long tmcdbgCommonMemClose();
HANDLE g_hMapFile;
LPVOID g_pMemory;

void tmcdbgPushStackVar(const char *fncname,short nVars,tmsMatrix* var1,const char *varname1,...)
{
tmsMatrix *x;
const char* xn;
va_list marker;
short n;
short bOk=0;
	
		TmcDebugStack.stack[TmcDebugStack.sp].etype=TMC_DBG_ESTACK_FUNC;
		TmcDebugStack.stack[TmcDebugStack.sp].vaddr=(void*)&x;
		TmcDebugStack.stack[TmcDebugStack.sp].varname=fncname;
		TmcDebugStack.sp++;


	n=0;
	va_start( marker, nVars );     // Initialize variable arguments. 
	while (n<nVars)
	{
		x  = va_arg( marker,  tmsMatrix * );
		xn = va_arg( marker,  const char* );
		TmcDebugStack.stack[TmcDebugStack.sp].etype=TMC_DBG_ESTACK_VAR;
		TmcDebugStack.stack[TmcDebugStack.sp].vaddr=x;
		TmcDebugStack.stack[TmcDebugStack.sp].varname=xn;
		TmcDebugStack.sp++;
		n++;
	}
	va_end( marker );              // Reset variable arguments.      

}

void tmcdbgPopStackVar(short nVars)
{
	TmcDebugStack.sp = TmcDebugStack.sp-nVars-1;

}

void tmcdbgOpenDebugger(void)
{
	TmcDebugStack.bp=0;
	TmcDebugStack.sp=0;

  g_hMapFile=NULL;
  g_pMemory=NULL;
pTmcDbgCommonBlock=NULL;

	if (tmcdbgCommonMemCreate(L"tmcdebug.bin",sizeof(struct CTmcDbgCommonBlock)) <0)
	{
		return; // can open map
	}
	pTmcDbgCommonBlock = (struct CTmcDbgCommonBlock*)g_pMemory;
	pTmcDbgCommonBlock->stack_addr = & TmcDebugStack ;
	pTmcDbgCommonBlock->psymbol_table = GetSymbolTableAddr();
}
void tmcdbgCloseDebugger(void)
{
	tmcdbgCommonMemClose();
}
////////// data inteconnection /////////


long tmcdbgCommonMemCreate(LPCWSTR MapName, DWORD MapSize)
// create mapping
{
	if (g_hMapFile !=NULL)
	{
		return -1;
	}
	g_hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,PAGE_READWRITE,0,MapSize,MapName);
	if (g_hMapFile ==NULL)
	{
		return -2;
	}
	if ( GetLastError() == ERROR_ALREADY_EXISTS )
	{
		tmcdbgCommonMemClose();
		return -3;
	}
	g_pMemory = MapViewOfFile(g_hMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	if (g_pMemory ==NULL )
	{
		tmcdbgCommonMemClose();
		return -4;
	}
	return 0;
}
long tmcdbgCommonMemClose()
// close last file mapping
{
	if (g_hMapFile ==NULL)
	{
		return 0;
	}
	if (g_pMemory != NULL)
	{
		if (!UnmapViewOfFile( g_pMemory) )
		{
			g_hMapFile = NULL;
			g_pMemory  = NULL;
			return -2;
		}
	}
	CloseHandle(g_hMapFile); // delete file mapping

	g_hMapFile = NULL;
	g_pMemory  = NULL;
	return 0;
}

//#else
//// client API /////////
HANDLE g_hClientMapFile;
long tmcdbgCommonMemConnect(void** ptr)
// connect to mapping
{
	DWORD myerrcode;

	g_hClientMapFile = OpenFileMapping(FILE_MAP_READ /* |FILE_MAP_WRITE */,FALSE,L"tmcdebug.bin");
	if (g_hClientMapFile ==NULL)
	{
		return -2;
	}

	*ptr = MapViewOfFile(g_hClientMapFile,FILE_MAP_READ,0,0,0);
	if (*ptr ==NULL )
	{
		myerrcode = GetLastError();

		CloseHandle(g_hClientMapFile); // delete file mapping
		g_hClientMapFile=NULL;
		return myerrcode;
	}
	return 0;
}
long tmcdbgCommonMemDisconnect( void)
{
		CloseHandle(g_hClientMapFile); // delete file mapping
		g_hClientMapFile=NULL;
		return 0;
}
/////////////////////
#endif
//#endif
