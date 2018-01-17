// File: tmclsp_marix.cpp
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
#include <string>

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "tmclsp_matrix.h"

std::string tmcPrintMatrix(tmsMatrix *x)
{
	char buff[200];
	double m_Real=0;
	double m_Imag=0;

	std::string res;

	if (x)
	{
		if (_tmcIsChar(x))
		{
			AssignMtoStr(res,x);
		}
		else
		{
			if (x->value.complx.rData)
					m_Real=x->value.complx.rData[0];

			if (_tmcHasIm(x))
			{
				if (x->value.complx.iData)
					m_Imag=x->value.complx.iData[0];
				sprintf(buff,"(%.15e %.15e)",m_Real,m_Imag);
			}
			else
			{
				sprintf(buff,"%.15e",m_Real);
			}
			res.append(buff);
		}
	}
	return res;
}
std::string tmcPrintMatrixType(tmsMatrix *x)
{
	std::string res;

	if (x)
	{
		if (_tmcIsChar(x))
		{
			res="STR";
		}
		else
			if (_tmcHasIm(x))
			{
				res="Z16";
			}
			else
			{
				res="R8";
			}
	}
	else
	{
		res = "(nil)";
	}
	return res;
}

const char* _tmcMat2String(tmsMatrix *src)
{// create char buffer

char *buf;
long n;

	buf = (char*)MYMALLOC(sizeof(char)*(_tmcGetN(src)+1));
	for(n=0;n<_tmcGetN(src);n++)
	{
		buf[n] = (char)src->m_rData[n];
	}
	buf[n]=0;
return buf; // must be free by caller
}
void AssignMtoStr(std::string& str,tmsMatrix *src)
{
	const char *strptr;
			strptr = _tmcMat2String(src);
			str = strptr;
			free((void*)strptr);
}


void tmcScalar(tmsMatrix *dest,double x)
{
	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,1,1,tmcREAL);
	dest->m_rData[0]=x;
}
void tmcComplexScalar(tmsMatrix *dest,double xr,double xi)
{
	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,1,1,tmcCOMPLEX);
	dest->m_rData[0]=xr;
	dest->m_iData[0]=xi;
}

void _tmcSetMatrixEmpty(tmsMatrix *y)
{// HAZARD - matrix not freed
	memset(y,0,sizeof(tmsMatrix));
	memset(&y->m_desc,0,sizeof(struct tag_tmcMatrixDecriptor));
	y->m_desc.m_type=TYPE_NOTHING;
}
void tmcFreeRegister(tmsMatrix *src)
{ // Applied to register  at exit, called before free of local vars
	if (src !=NULL)
	{
		_tmcClearRegister(src);
		free(src); // the only place we destroy register!
	}
}

tmsMatrix * __tmcNewMatrix(void)
{
	tmsMatrix *dest;
	dest=(tmsMatrix *)MYMALLOC(sizeof(tmsMatrix));
	_tmcSetMatrixEmpty(dest);
	return dest;
}

void tmcReallocRegister(tmsMatrix *src)
{
	_tmcClearRegister(src);
}
void _tmcClearRegister(tmsMatrix *x)
{ // free the register before re-usage

long m,n;
long M;
long N;


	if (x==NULL)
	{
		return ; // if register is reference dont clear the source.
	}

	if (x->m_desc.m_modifier & MODIFIER_MASK_NOTCOPY)
	{
		memset(x,0,sizeof(tmsMatrix));
		x->m_desc.m_type = TYPE_NOTHING;
		return ;
	}

 x->m_desc.m_modifier  &= ~MODIFIER_MASK_BOOL;
 M = _tmcGetM(x);
 N = _tmcGetN(x);

	if (x->m_desc.m_type == TYPE_CELL_ARRAY)
	{
		for (m=0;m<M;m++)
		{
			for (n=0;n<N;n++)
			{
				_tmcClearRegister(x->value.m_cells[m+n*M]);
				free(x->value.m_cells[m+n*M]);//xaxa
			}
		}
		x->m_desc.m_type = TYPE_NOTHING;
		if (x->value.m_cells)
			free(x->value.m_cells);
		x->value.m_cells=NULL;
		x->m_desc.m_nRows=0;
		x->m_desc.m_nCols=0;
	return ;
	}

	//if (x->m_desc.m_type == TYPE_STRUCT)
	//{
	//	_tmcClearStruct(x);
	//	return;
	//}




	if (x->m_desc.m_type == TYPE_ITERATOR )
	{
		// Not needed:
		//_tmcClearRegister(*(x->iter_var));
		x->m_desc.m_type = TYPE_NOTHING;
		return;
	}
	// Usual matrix
	if (x->m_desc.m_type == TYPE_MATRIX || x->m_desc.m_type == TYPE_STRING)
	{
		if (x->m_rData)
		free(x->m_rData);
		x->m_rData=NULL;
		if (_tmcHasIm(x))
		{
			free(x->m_iData);
			x->m_iData=NULL;
		}
		x->m_desc.m_type = TYPE_NOTHING;
		x->m_desc.m_nRows=0;
		x->m_desc.m_nCols=0;
	return ;
	}
}

void _tmcCreateCellArray(tmsMatrix *res,long M,long N)
{// memory must be allocated already 
 // Actually used only for MM=0
	res->m_desc.m_nRows=M;
	res->m_desc.m_nCols=N;
	memset(&res->value,0,sizeof(res->value));
	if (M*N)
	{
	res->value.m_cells = (tmsMatrix **)MYMALLOC(M*N*sizeof(tmsMatrix *));
	memset(res->value.m_cells,0,M*N*sizeof(tmsMatrix *));
	}
	res->m_desc.m_type = TYPE_CELL_ARRAY;
	//_tmcClearExtraDims(res);
}
void _tmcCreateMatrix(tmsMatrix *res,long M,long N,short bHasImagine)
{
//long *myEBP;
//
//	__asm
//	{
//		mov myEBP,ebp 
//	}
//	sprintf(dbg_buf,"_tmcCreateMatrix: %x,%s",myEBP[1],dbg_buf2);

	res->m_desc.m_nRows=M;
	res->m_desc.m_nCols=N;
	res->m_desc.m_type= TYPE_MATRIX;

	//res->m_iData =NULL;
	//res->m_rData =NULL;
	//res->value.fields_list = NULL;
	//res->value.m_cells=NULL;
	memset(&res->value,0,sizeof(res->value));
	if (M*N)
	{
//		dbg_counter++;
//		if (dbg_counter==57168 || dbg_counter==57250 || dbg_counter==111198)
//		{
//			dbg_here=1;
//		}
////VANDAL
//	res->m_rData = (double*)my_malloc_dbg(M*N*sizeof(double),dbg_buf,dbg_counter);
//	res->m_rData = (double*)my_malloc_dbg(M*N*sizeof(double),dbg_buf,__LINE__);


	res->m_rData = (double*)MYMALLOC(M*N*sizeof(double));
	memset(res->m_rData,0,M*N*sizeof(double));
	if (bHasImagine)
		{
			res->m_iData = (double*)MYMALLOC(M*N*sizeof(double));
			memset(res->m_iData,0,M*N*sizeof(double));
			res->m_desc.m_modifier |=MODIFIER_MASK_HAS_IM;
		}
		else
		{
			res->m_desc.m_modifier &=~MODIFIER_MASK_HAS_IM;
		}

	}
}
void tmcCreateString(tmsMatrix *matres,const char *str)
{
	// In MATLAB all implicit strings  have no ESC-seq, thus in TMC they contain
	// additional \.
	// In C exist Escape Sequences
	// only sprintf and fprintf functions convert the formats TMC to C
	// e.g. "\\r" ->> "\r"
	tmcReallocRegister(matres);
	_tmcSetString(matres,str);
}
void _tmcSetString(tmsMatrix *y,const char *str)
{
long n;
	long len = strlen(str); // without NULL-termination.
	_tmcCreateMatrix(y,1,len,tmcREAL);
	y->m_desc.m_type = TYPE_STRING;
	for(n=0;n<len;n++)
		y->m_rData[n]=str[n];
}
void tmcCreateMagicColon(tmsMatrix *magcolM)
{
	tmcReallocRegister(magcolM);
	_tmcCreateMatrix(magcolM,0,0,tmcREAL);
	magcolM->m_desc.m_type = TYPE_MAGIC_COLON;
}

