/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license.
 * 
  *****************************************************************************/

#ifndef  _TMC_EMBEDDED_
#include <windows.h>
#endif

#include "tmc.h"
#include "clapack_types.h"



#include  <math.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h> // ANSI compatibility

#include <stdio.h>
#ifndef  _TMC_EMBEDDED_
#include <malloc.h>

#define EXCEPTION_TMC_USER_ERROR	0xE0000001
#define EXCEPTION_TMC_LIB_ERROR		0xE0000002

#endif
	
//Legal values for expression in except()
//#define EXCEPTION_EXECUTE_HANDLER       1
//#define EXCEPTION_CONTINUE_SEARCH       0
//#define EXCEPTION_CONTINUE_EXECUTION    -1

char ExceptMessageBuf[4096];

static char *s_module="tmcexcpt.c";

long _tmcDumpErrors;

void _tmcRaiseException(long errcode,const char *module_name,const char *func_name,const char *errmsg,long numargin,tmsMatrix *x,...)
{
va_list marker;
long ind;
tmsMatrix *M;
//   DWORD e_infos[1];
#ifndef  _TMC_EMBEDDED_
ULONG_PTR e_infos[1];//x64
#endif

   if (_tmcDumpErrors)
   {
    fprintf(stderr,"*** Run-time exception: %s\nin module %s,function %s ***\n",errmsg,module_name,func_name);
	if (numargin > 0)
	{
		fprintf(stderr,"*************** Operands dump: ****************\n");
		va_start( marker, x );     // Initialize variable arguments. 
		ind=0;M =x;
		while (ind<numargin)
		{
			fprintf(stderr,"Matrix addr=%llx\n",(unsigned __int64)(void*)M);
			tmcDisplayMat(M,1);
			fprintf(stderr,"*******************************\n");
			M = va_arg( marker,  tmsMatrix * );
			ind++;
		}
		va_end( marker );              // Reset variable arguments.      
	}
   }
	//RaiseException(( ((errcode & 0x0FFFFFFF )) | 0xE0000000 ),0,0,NULL);
		sprintf(ExceptMessageBuf,"*** Run-time exception:\n %s\nin module %s,function %s ***\n",errmsg,module_name,func_name);
#ifndef  _TMC_EMBEDDED_
		e_infos[0] = (ULONG_PTR)&ExceptMessageBuf[0];

		RaiseException(EXCEPTION_TMC_LIB_ERROR,0,1,&e_infos[0]);
#else
		// TMC_HAZARD_TODO : no exception handling for embedded systems
#endif
	
}


#ifndef  _TMC_EMBEDDED_
long _tmcUnhandledExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
// exception filter function for TMCLIB
char *ptrStr;

	if (ExceptionInfo->ExceptionRecord->ExceptionCode==EXCEPTION_TMC_USER_ERROR ||
		ExceptionInfo->ExceptionRecord->ExceptionCode==EXCEPTION_TMC_LIB_ERROR)
	{
		ptrStr = (char*)ExceptionInfo->ExceptionRecord->ExceptionInformation[0];
				fprintf(stderr,"\nerror at ADDR=%llx:\n %s\n",
					(unsigned __int64)(void*)ExceptionInfo->ExceptionRecord->ExceptionAddress,ptrStr);
	}
	else
	{
				fprintf(stderr,"\nEXCEPTION=%x,\nADDR=%llx,\n", ExceptionInfo->ExceptionRecord->ExceptionCode,
					(unsigned __int64)(void*)ExceptionInfo->ExceptionRecord->ExceptionAddress);
	}

return EXCEPTION_EXECUTE_HANDLER;
}
#endif

void _tmcInstallUnhandledExceptionFilter(void)
// installed TMC specific UnhandledExceptionFilter
{
#ifndef  _TMC_EMBEDDED_
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)_tmcUnhandledExceptionFilter);
#endif
}
void _tmcUninstallUnhandledExceptionFilter(void)
// reset   UnhandledExceptionFilter to windows default
{
#ifndef  _TMC_EMBEDDED_
	SetUnhandledExceptionFilter(NULL);
#endif
}



void tmcSyntaxError(const char *msg)
// run-time error
{
			_tmcRaiseException(err_bad_index,s_module,"FATAL:SyntaxError",msg,0,NULL);
}

extern void javatmcSignalError(char *ExceptMessageBuf);

void tmcerror(long nout,long ninput,tmsMatrix *ydummy, tmsMatrix *msg_string)
{
long len,k;
//   DWORD e_infos[1];
#ifndef  _TMC_EMBEDDED_
ULONG_PTR e_infos[1];//x64
#endif

// this function is implemented with one output to avoid TMC compilation warnings.
	if (nout>0)
	_tmcCreateMatrix(ydummy,1,1,0);

	if (_tmcIsEmptyMatrix(msg_string)==0)
	{
		len = tmcNumElem(msg_string);
		for (k=0;k<len;k++)
		{
			ExceptMessageBuf[k]=(char)msg_string->value.complx.rData[k];
		}
		ExceptMessageBuf[k]='\0';
#ifndef  _TMC_EMBEDDED_ // TMC_HAZARD: no error() support for embedded systems so far
		e_infos[0] = (ULONG_PTR)&ExceptMessageBuf[0];
		RaiseException(EXCEPTION_TMC_USER_ERROR,0,1,&e_infos[0]);
#else
		javatmcSignalError(ExceptMessageBuf);// platform-specific function. No internal try-catch handling !
#endif
	}
	else
		ExceptMessageBuf[0]='\0';

	
}
void tmclasterr(long nout,long ninput,tmsMatrix *msg_string_out, tmsMatrix *msg_string)
{
	int len,k;
	int m;

	if (nout>0)
	{
	len =(long)strlen( ExceptMessageBuf);//x64
	if (len==0)
		m=0;
	else
		m=1;

	_tmcCreateMatrix(msg_string_out,m,len,tmcREAL);
	msg_string_out->m_desc.m_type = TYPE_STRING;
	for (k=0;k<len;k++)
		msg_string_out->value.complx.rData[k] = (double)ExceptMessageBuf[k];
	}

	if (ninput>0)
	{
		//restriction:  only clear lasterr is supported
		ExceptMessageBuf[0]='\0';
	}

}
void tmcwarning(long nout,long ninput, tmsMatrix *msg_string,tmsMatrix *msg_string2)
{
//HSKOST:restrict: so far unsupported, ignored 
}
