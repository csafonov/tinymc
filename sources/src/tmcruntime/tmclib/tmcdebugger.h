/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 File may be used in the generated application
  *****************************************************************************/
// tmcdebugger.h
#ifndef _tmcdebugger_h_
#define _tmcdebugger_h_

#define TMC_DBG_PUSH_STACK_VAR  tmcdbgPushStackVar
#define TMC_DBG_POP_STACK_VAR	tmcdbgPopStackVar


#define TMC_DBG_MAX_STACKIZE 100000

enum ETmcDbgStackEntries
{
	TMC_DBG_ESTACK_VAR     = 0, // TMC_VAR
	TMC_DBG_ESTACK_FUNC    = 1 // TMC_FUNC
};

typedef	tmsMatrix*			TMC_VAR_ADDR;
//typedef	(void (*)(long,...))  TMC_FUNC_ADDR;
typedef long tmcindex;
typedef const char* TMC_VARNAME;

struct CTmcDbgEntry
{
	enum ETmcDbgStackEntries etype;
	TMC_VAR_ADDR			 vaddr;
	TMC_VARNAME				 varname;
};

typedef 
	struct CTmcDbgStack
	{
		tmcindex sp; // stack pointer
		tmcindex bp; // stack frame
		struct CTmcDbgEntry stack[TMC_DBG_MAX_STACKIZE];
	} TMC_DBG_STACK;

struct CTmcDbgCommonBlock
{
	struct CTmcDbgStack *stack_addr;
	bucket   **psymbol_table;
};


void tmcdbgPushStackVar(const char *fncname,short nVars,tmsMatrix* var1,const char *varname1,...);
void tmcdbgPopStackVar(short nVars);
void tmcdbgOpenDebugger(void);
void tmcdbgCloseDebugger(void);

long tmcdbgCommonMemConnect(void** ptr);
long tmcdbgCommonMemDisconnect( void);

#endif
