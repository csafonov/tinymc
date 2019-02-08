/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license. 
  *****************************************************************************/
//! File: tmcmath_qd.c
//!	Quadriple precision routines (128 bit double)

// Uses clapack interfaces
#ifndef USE_QDMATH
#define USE_QDMATH
#endif


#define tmcconv tmcconv_qd
#define _tmcRealLeftDiv _tmcRealLeftDiv_qd
#define _tmcComplexLeftDiv _tmcComplexLeftDiv_qd



static char *s_module="tmcmath_qd.c";

//#include "f2c.h"
#include "clapack_types.h"

#define min(a,b) ((a) <= (b) ? (a) : (b))
#define max(a,b) ((a) >= (b) ? (a) : (b))


// DLL version    is funcname_
// static version is funcname
#ifndef _BCC55_ // for Borland 5.5 use statics link
#define dgesvd_ dgesvd
#define zgesvd_ zgesvd
#define dgels_ dgels
#define zgels_ zgels
#define zgeevx_ zgeevx
#define dgeevx_ dgeevx
#define dgetrf_ dgetrf
#define zgetrf_ zgetrf
#define	zgeqrf_ zgeqrf
#endif



#include "clapack.h"

#ifndef _BCC55_ // for Borland 5.5 use statics link
#define zfftf_ zfftf
#define zffti_ zffti
#endif



#ifdef _BCC55_ // for Borland 5.5  
int errno;
#endif

#include "tmc.h"

//#undef VANDAL


#ifdef VANDAL
#include <stdio.h>
int quadmath_snprintf (char *s, size_t size, const char *format,...);
char qd_string_buf[2048];
#endif

#define MYMALLOC malloc
#define MYFREE		free

// fft tools
int __cdecl zffti_(integer *n, doublereal *wsave);
int __cdecl zfftf_(integer *n, doublereal *c__, doublereal *wsave);

//#include <stdlib.h>
#ifndef  _TMC_EMBEDDED_
#include <malloc.h>
#endif
#include <string.h>

#ifndef _BCC55_ // for Borland 5.5 use statics link
#ifndef _TMCRTVC6_

#ifdef WIN32
#ifndef NO_LAPACK_DLL
#ifdef _DEBUG
#pragma comment(lib,"mlapackd.lib")
#else
#pragma comment(lib,"mlapack.lib")
#endif
#endif
#endif
#endif
#endif

//////////////////
void tmcconv(long nout,long ninput, tmsMatrix *C, tmsMatrix *A, tmsMatrix *B)
{ // C=conv(A,B)
//TODO
//* Let nA = length(A) and nB = length(B). Then C is the vector of length nA+nB-1 whose kth element is
//* C(k)=Sum_j A(j)B(k+1-j), j=max(1,k+1-nB)..min(k,nA)
long nA,nB,lenC,mC,nC;
long k,jmax,jn,j2;
doublereal rS,iS;

nA = tmcNumElem(A);
nB = tmcNumElem(B);
lenC = nA+nB-1;

	// dims of C go after dims B
	if (_tmcGetM(B)> _tmcGetN(B))
	{
		mC = lenC; nC=1;
	}
	else
	{
		mC= 1; nC = lenC;
	}
		_tmcCreateMatrix(C,mC,nC,_tmcHasIm(A) |_tmcHasIm(B));

		for (k=0;k<lenC;k++)
		{
			rS=0;iS=0;
			jn=max(1,(1+k)+1-nB)-1;// zero based indexes
			jmax=min((k+1),nA)-1;
			j2=(k+1)+1-(jn+1)-1;

			if (_tmcHasIm(C)==0)
			{
				for ( ;jn<=jmax;jn++,j2--)
				{
					rS += (doublereal)A->value.complx.rData[jn]*(doublereal)B->value.complx.rData[j2];
				}
			    C->value.complx.rData[k]=(double)rS;
			}
			else
			{
				if (_tmcHasIm(A) && _tmcHasIm(B))
				{
					for ( ;jn<=jmax;jn++,j2--)
					{
						rS += (doublereal)A->value.complx.rData[jn]*(doublereal)B->value.complx.rData[j2]-
							  (doublereal)A->value.complx.iData[jn]*(doublereal)B->value.complx.iData[j2];
						iS += (doublereal)A->value.complx.rData[jn]*(doublereal)B->value.complx.iData[j2]+
							  (doublereal)A->value.complx.iData[jn]*(doublereal)B->value.complx.rData[j2];
					}
				}
				else if (_tmcHasIm(A)) // only _tmcHasIm(A)
				{
					for ( ;jn<=jmax;jn++,j2--)
					{
						rS += (doublereal)A->value.complx.rData[jn]*(doublereal)B->value.complx.rData[j2];
						iS += (doublereal)A->value.complx.iData[jn]*(doublereal)B->value.complx.rData[j2];
					}
				}
				else // only _tmcHasIm(B)
				{
					for ( ;jn<=jmax;jn++,j2--)
					{
						rS += (doublereal)A->value.complx.rData[jn]*(doublereal)B->value.complx.rData[j2];
						iS += (doublereal)A->value.complx.rData[jn]*(doublereal)B->value.complx.iData[j2];
					}
				}
				C->value.complx.rData[k]=(double)rS;
				C->value.complx.iData[k]=(double)iS;
			}
		}
return;
}
///////////////

void tmcleftdivide_qd(long nout,long ninput, tmsMatrix *X,tmsMatrix *A,tmsMatrix *B)
{// X = A\B
long t;
//	printf("errferfer \n");
//tmcDisplayMat(A,1);
//tmcDisplayMat(B,1);

//	printf("tmcleftdivide_qd %d,%d,%x %x %x\n",nout,ninput,X,A,B);

		if ((_tmcHasIm(A)==0)	&& (_tmcHasIm(B)==0))
		{
			_tmcRealLeftDiv_qd(X,A,B);
		}
		else
	{
			_tmcComplexLeftDiv(X,A,B);
		}


/* 
	if (_tmcIsScalar(A))
	{
		_tmcCreateMatrix(X,_tmcGetM(B),_tmcGetN(B),(short)(_tmcHasIm(A) | _tmcHasIm(B)));
		_tmcDivByScalar(X,B,A,0);
	}
	else if (_tmcIsScalar(B))
	{
		_tmcCreateMatrix(X,_tmcGetM(A),_tmcGetN(A),(short)(_tmcHasIm(A) | _tmcHasIm(B)));
		_tmcDivByScalar(X,A,B,1);
	}
	else
	{
		if ((_tmcHasIm(A)==0)	&& (_tmcHasIm(B)==0))
		{
			_tmcRealLeftDiv(X,A,B);
		}
		else
		{
				_tmcComplexLeftDiv(X,A,B);
		}
	}
*/

}



void _tmcPolyVal_qd(doublecomplex *y, doublecomplex *p, doublecomplex *x, integer N);
/**
	\brief	polyval_qd implemented by QUAD precision calculations
*/
void tmcpolyval_qd(long nout, long ninput, tmsMatrix *y, tmsMatrix *p, tmsMatrix *x)
{

	long M, N, MN;
	long ind;
	long deg;

	doublecomplex *pol;
	doublecomplex parg;
	doublecomplex pval;

	M = _tmcGetM(x);
	N = _tmcGetN(x);
	MN = M*N;
	deg = tmcNumElem(p) - 1;
	pol = MYMALLOC(sizeof(doublecomplex)*(deg + 1));
	for (ind = 0; ind <= deg; ind++)
	{
		pol[ind].r = p->m_rData[ind];
		if (_tmcHasIm(p))
		{
			pol[ind].i = p->m_iData[ind];
		}
		else
			pol[ind].i = 0;
	}

	_tmcClearRegister(y);
	_tmcCreateMatrix(y, M, N, (short)(_tmcHasIm(x) | _tmcHasIm(p)));
	for (ind = 0; ind<MN; ind++)
	{
		parg.r = x->m_rData[ind];
		if (_tmcHasIm(x))
		{
			parg.i = x->m_iData[ind];
		}
		else
		{
			parg.i = 0;
		}
		_tmcPolyVal_qd(&pval, pol, &parg, deg);
		y->m_rData[ind] = pval.r;
		if (_tmcHasIm(y))
		{
			y->m_iData[ind] = pval.i;
		}
	}
	MYFREE(pol);
}

