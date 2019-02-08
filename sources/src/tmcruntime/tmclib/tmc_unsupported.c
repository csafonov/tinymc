/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license.
 * 
  *****************************************************************************/
#include "tmc.h"
#include "clapack_types.h"

#include  <math.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h> // ANSI compatibility

#include <stdio.h>

void tmceval(long nout,long ninput,tmsMatrix *ydummy, tmsMatrix *str)
{
// this function is implemented with one output to avoid TMC compilation warnings.
	if (nout>0)
	_tmcCreateMatrix(ydummy,1,1,0);

	_tmcRaiseException(err_unsupported,"main","eval","FATAL: eval(x) is unsupported!!!.",1,str);
}
void tmcssdata(long nout,long ninput,...)
{
	_tmcRaiseException(err_unsupported,"main","ssdata","FATAL: ssdata is unsupported!!!.",0,NULL);
}
void tmcss2tf(long nout,long ninput,...)
{
	_tmcRaiseException(err_unsupported,"main","ss2tf","FATAL: ss2tf is unsupported!!!.",0,NULL);
}
//void tmctfdata(long nout,long ninput,...)
//{
//	_tmcRaiseException(err_unsupported,"main","tfdata","FATAL: tfdata is unsupported!!!.",0,NULL);
//}
void tmctf(long nout,long ninput,...)
{
	_tmcRaiseException(err_unsupported,"main","tf","FATAL: tf is unsupported!!!.",0,NULL);
}
void tmcget(long nout,long ninput, tmsMatrix *y, tmsMatrix *S, tmsMatrix *str)
{
	_tmcRaiseException(err_unsupported,"main","get","FATAL: get(S,'prop') is unsupported!!!.",2,S,str);
}
void tmcexist(long nout,long ninput,tmsMatrix *y,tmsMatrix *x,tmsMatrix *mtype)
{
		fprintf(stdout,"WARN: exist() not suppoted \n");
}
/////////// CONTROL QFD //////////
void tmcisa(long nout,long ninput,tmsMatrix *y, tmsMatrix *x, tmsMatrix *str)
{
	fprintf(stdout,"WARN: isa(): classed not suppoted \n");
	if (nout>0)
	{
			_tmcCreateMatrix(y,1,1,tmcREAL);
			y->m_rData[0]= 0;
	}
}
void tmctfdata(long nout,long ninput, tmsMatrix *num, tmsMatrix *den,tmsMatrix *tsamp, tmsMatrix *sys,tmsMatrix *mopt)
{
	_tmcRaiseException(err_unsupported,"main","tmctfdata","FATAL: tfdata is unsupported!!!.",0,NULL);
}
void tmcfreqresp(long nout,long ninput, tmsMatrix *y, tmsMatrix *sys,tmsMatrix *w)
{
	_tmcRaiseException(err_unsupported,"main","tmcfreqresp","FATAL: freqresp is unsupported!!!.",0,NULL);
}
void tmcfrdata(long nout,long ninput, tmsMatrix *num, tmsMatrix *den,tmsMatrix *tsamp, tmsMatrix *sys,tmsMatrix *mopt)
{
	_tmcRaiseException(err_unsupported,"main","tmcfrdata","FATAL: frdata is unsupported!!!.",0,NULL);

}
void tmcfrdqfd(long nout,long ninput,tmsMatrix *sys,tmsMatrix *L,tmsMatrix *Freqs)
{
	_tmcRaiseException(err_unsupported,"main","tmcfrdqfd","FATAL: frdqfd is unsupported!!!.",0,NULL);
}
void tmctf2ss(long nout,long ninput,...)
{
	_tmcRaiseException(err_unsupported,"main","tmctf2ss","FATAL: tmctf2ss is unsupported!!!.",0,NULL);
}
void tmcss(long nout,long ninput,...)
{
	_tmcRaiseException(err_unsupported,"main","tmcss","FATAL: tmcss is unsupported!!!.",0,NULL);
}
void tmczpkdata(long nout,long ninput,...)
{
	_tmcRaiseException(err_unsupported,"main","tmczpkdata","FATAL: tmczpkdata is unsupported!!!.",0,NULL);
}
void tmczpk(long nout,long ninput,tmsMatrix *y,tmsMatrix *z,tmsMatrix *p,tmsMatrix *k,tmsMatrix *tsamp)
{
	_tmcRaiseException(err_unsupported,"main","tmczpk","FATAL: tmczpk is unsupported!!!.",0,NULL);
}
void tmcfrd(long nout,long ninput,tmsMatrix *y,tmsMatrix *Resp,tmsMatrix *Freqs)
{
	_tmcRaiseException(err_unsupported,"main","tmcfrd","FATAL: tmcfrd is unsupported!!!.",0,NULL);
}
