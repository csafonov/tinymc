//! File: tmctestmex.c
//! Part of TMC run-time. Copyright (C) 2009-2016 Shmuel Safonov.  
//! A template for calling tmc-functions from a MEX
#include "mex.h"
#include "tmc_libx.h"

/*
tmsMatrix * (*__tmcNewMatrix)(void);
void (*tmcCreateString)(tmsMatrix *matres,const char *str);
void (*tmcFreeLocalVar)(tmsMatrix *src);// free local var at exit
void (*_tmcCreateMatrix)(tmsMatrix *res,long M,long N,short bHasImagine);
*/

tmsMatrix * __tmcNewMatrix(void);
void tmcCreateString(tmsMatrix *matres,const char *str);
void tmcFreeLocalVar(tmsMatrix *src);// free local var at exit
void _tmcCreateMatrix(tmsMatrix *res,long M,long N,short bHasImagine);


#define TMCMEX_CREATE_DOUBLE_MATRIX(y,m,n,tmcTYPE)  (y=mxCreateDoubleMatrix(m,n,tmcTYPE))  
#define TMCMEX_CREATE_CELL_MATRIX(y,m,n)   (y=mxCreateCellMatrix(m,n))
#define TMCMEX_NEW_DOUBLE_MATRIX(y,m,n,tmcTYPE)  (y=mxCreateDoubleMatrix(m,n,tmcTYPE ))  

// output to MATLAB functions
void CreatemxArrayFromTmcMatrix(mxArray **y,tmsMatrix *x)
{
double *ptr,*pti;
long k;

TMCMEX_CREATE_DOUBLE_MATRIX(y[0],_tmcGetM(x),_tmcGetN(x),_tmcHasIm(x) ? mxCOMPLEX:mxREAL);
		ptr=mxGetPr(y[0]);
		pti=mxGetPi(y[0]);

		for (k=0;k<_tmcNumElem(x);k++)
		{
			ptr[k]=x->m_rData[k];
			if (_tmcHasIm(x))
			{
				pti[k]=x->m_iData[k];
			}
		}
// is free by MATLAB
}

// input from MATLAB functions
tmsMatrix * tmcNewMatrixFromCdouble(long M,long N,double *ptr,double *pti)
{
	long k;
	tmsMatrix *x=tmcNewMatrix();
	short HasIm = (pti==NULL ? tmcREAL:tmcCOMPLEX);
    _tmcCreateMatrix(x,M,N,HasIm);

		for (k=0;k<M*N;k++)
		{
			x->m_rData[k] = ptr[k];
			if (HasIm)
			{
				x->m_iData[k] = pti[k];
			}
		}

return x; // must free
}

tmsMatrix * tmcNewMatrixFromMxString(const mxArray *msOpt)
{
//	long k;
	long MN;
	char *input_buf;

	tmsMatrix *x=tmcNewMatrix();

  // Input must be a string
  if (mxIsChar(msOpt) != 1)
    mexErrMsgTxt("Input must be a string.");    
	
    MN = (long)(mxGetM(msOpt) * mxGetN(msOpt)) + 1;
    input_buf = mxCalloc(MN, sizeof(char));

  // Copy the string data from prhs[0] into a C string 
  //   input_buf. If the string array contains several rows, 
  //   they are copied, one column at a time, into one long 
  //   string array. 
  if ( mxGetString(msOpt, input_buf, MN) !=0)
		mexWarnMsgTxt("Not enough space. String is truncated.");

  input_buf[MN-1]=0;//force termination
	tmcCreateString(x,input_buf);



return x; // must free
}


tmsMatrix *tmcNewMatrixFromMxLogical(const mxArray *mx)
{
	long k;
	mxLogical *pl;
	long M= (long)mxGetM(mx);
	long N= (long)mxGetN(mx);
	tmsMatrix *x=tmcNewMatrix();

    // Check to be sure input argument is logical. 
    if (!(mxIsLogical(mx))){
	mexErrMsgTxt("Input must be of type logical.");
    }

   pl = mxGetLogicals(mx);

   _tmcCreateMatrix(x,M,N,tmcREAL);

		for (k=0;k<M*N;k++)
		{
			x->m_rData[k] =(double)(pl[k]);
		}
return x; // must free
}




