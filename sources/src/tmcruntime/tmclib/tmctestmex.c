//! File: tmctestmex.c
//! Part of TMC run-time. Copyright (C) 2009-2016 Shmuel Safonov.  
//! A template for calling tmc-functions from a MEX
#include "mex.h"
#include "tmc_lib.h"

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
	
    MN = (mxGetM(msOpt) * mxGetN(msOpt)) + 1;
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
	long M= mxGetM(mx);
	long N= mxGetN(mx);
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



void tmcinv(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
//////////////////////////// tmcinv ///////////////////////////////////
        //_asm int 4
#ifdef MEX_FILE_NAME_tmcinv
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
        tmcinv(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// acos /////////////

           //_asm int 4
#ifdef MEX_FILE_NAME_tmcacos
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
        tmcacos(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// asin /////////////

           //_asm int 4
#ifdef MEX_FILE_NAME_tmcasin
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
        tmcasin(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// sin /////////////

           //_asm int 4
#ifdef MEX_FILE_NAME_tmcsin
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
        tmcsin(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// cos /////////////

           //_asm int 4
#ifdef MEX_FILE_NAME_tmccos
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
        tmccos(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
///////////////////////////////////////// 
//////////////////////// tan /////////////

           //_asm int 4
#ifdef MEX_FILE_NAME_tmctan
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
//_asm int 4 
		tmctan(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// exp /////////////

           //_asm int 4
#ifdef MEX_FILE_NAME_tmcexp
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
//_asm int 4 
		tmcexp(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// sqrt /////////////

           //_asm int 4
#ifdef MEX_FILE_NAME_tmcsqrt
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
//_asm int 4 
		tmcsqrt(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// log10 /////////////

           //_asm int 4
#ifdef MEX_FILE_NAME_tmclog10
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
//_asm int 4 
		tmclog10(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// atan /////////////
           //_asm int 4
#ifdef MEX_FILE_NAME_tmcatan
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
//_asm int 4 
		tmcatan(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// log /////////////
           //_asm int 4
#ifdef MEX_FILE_NAME_tmclog
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
//_asm int 4 
		tmclog(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// sign /////////////
           //_asm int 4
#ifdef MEX_FILE_NAME_tmcsign
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
//_asm int 4 
		tmcsign(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// roots /////////////
           //_asm int 4
#ifdef MEX_FILE_NAME_tmcroots
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
//_asm int 4 
		tmcroots(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif


//////////////////////// deconv /////////////
#ifdef MEX_FILE_NAME_tmcdeconv
void tmcdeconv(long nout,long ninput, tmsMatrix *q, tmsMatrix *r, tmsMatrix *v,tmsMatrix *u);
#define mQ plhs[0]
#define mR plhs[1]

#define mV prhs[0]
#define mU prhs[1]


tmsMatrix *q=tmcNewMatrix();
tmsMatrix *r=tmcNewMatrix();

tmsMatrix *v=tmcNewMatrixFromCdouble(mxGetM(mV),mxGetN(mV),mxGetPr(mV),mxGetPi(mV));
tmsMatrix *u=tmcNewMatrixFromCdouble(mxGetM(mU),mxGetN(mU),mxGetPr(mU),mxGetPi(mU));

//_asm int 4 
		tmcdeconv(nlhs,nrhs,q,r,v,u);
		CreatemxArrayFromTmcMatrix(&mQ,q);
		CreatemxArrayFromTmcMatrix(&mR,r);

		tmcFreeLocalVar(u);
		tmcFreeLocalVar(v);
		tmcFreeLocalVar(r);
		tmcFreeLocalVar(q);

#endif
//////////////////////// tmcDivScalar /////////////
#ifdef MEX_FILE_NAME_tmcDivScalar
void tmcDivScalar(tmsMatrix *divres,tmsMatrix *a,tmsMatrix *b);
#define mdivres plhs[0]

#define ma prhs[0]
#define mb prhs[1]


tmsMatrix *divres=tmcNewMatrix();

tmsMatrix *a=tmcNewMatrixFromCdouble(mxGetM(ma),mxGetN(ma),mxGetPr(ma),mxGetPi(ma));
tmsMatrix *b=tmcNewMatrixFromCdouble(mxGetM(mb),mxGetN(mb),mxGetPr(mb),mxGetPi(mb));

//_asm int 4 
		tmcDivScalar(divres,a,b);
		CreatemxArrayFromTmcMatrix(&mdivres,divres);

		tmcFreeLocalVar(b);
		tmcFreeLocalVar(a);
		tmcFreeLocalVar(divres);
#endif
//////////////////////// tmcatan2 /////////////
#ifdef MEX_FILE_NAME_tmcatan2
void tmcatan2(long nout,long ninput, tmsMatrix *y,tmsMatrix *xY,tmsMatrix *xX);

#define my plhs[0]

#define ma prhs[0]
#define mb prhs[1]


tmsMatrix *y=tmcNewMatrix();

tmsMatrix *a=tmcNewMatrixFromCdouble(mxGetM(ma),mxGetN(ma),mxGetPr(ma),mxGetPi(ma));
tmsMatrix *b=tmcNewMatrixFromCdouble(mxGetM(mb),mxGetN(mb),mxGetPr(mb),mxGetPi(mb));

//_asm int 4 
		tmcatan2(1,2,y,a,b);
		CreatemxArrayFromTmcMatrix(&my,y);

		tmcFreeLocalVar(b);
		tmcFreeLocalVar(a);
		tmcFreeLocalVar(y);
#endif
//////////////////////// tmclogspace /////////////
#ifdef MEX_FILE_NAME_tmclogspace
void tmclogspace(long nout,long ninput, tmsMatrix *y, tmsMatrix *x1, tmsMatrix *x2,tmsMatrix *nP);

#define my plhs[0]

#define mx1 prhs[0]
#define mx2 prhs[1]
#define mnP prhs[2]


tmsMatrix *y=tmcNewMatrix();

tmsMatrix *x1=tmcNewMatrixFromCdouble(mxGetM(mx1),mxGetN(mx1),mxGetPr(mx1),mxGetPi(mx1));
tmsMatrix *x2=tmcNewMatrixFromCdouble(mxGetM(mx2),mxGetN(mx2),mxGetPr(mx2),mxGetPi(mx2));
tmsMatrix *nP=tmcNewMatrixFromCdouble(mxGetM(mnP),mxGetN(mnP),mxGetPr(mnP),mxGetPi(mnP));

//_asm int 4 
		tmclogspace(1,3,y,x1,x2,nP);
		CreatemxArrayFromTmcMatrix(&my,y);

		tmcFreeLocalVar(nP);
		tmcFreeLocalVar(x2);
		tmcFreeLocalVar(x1);
		tmcFreeLocalVar(y);
#endif
//////////////////////// tmclinspace /////////////
#ifdef MEX_FILE_NAME_tmclinspace
void tmclinspace(long nout,long ninput, tmsMatrix *y, tmsMatrix *x1, tmsMatrix *x2,tmsMatrix *nP);

#define my plhs[0]

#define mx1 prhs[0]
#define mx2 prhs[1]
#define mnP prhs[2]


tmsMatrix *y=tmcNewMatrix();

tmsMatrix *x1=tmcNewMatrixFromCdouble(mxGetM(mx1),mxGetN(mx1),mxGetPr(mx1),mxGetPi(mx1));
tmsMatrix *x2=tmcNewMatrixFromCdouble(mxGetM(mx2),mxGetN(mx2),mxGetPr(mx2),mxGetPi(mx2));
tmsMatrix *nP=tmcNewMatrixFromCdouble(mxGetM(mnP),mxGetN(mnP),mxGetPr(mnP),mxGetPi(mnP));

//_asm int 4 
		tmclinspace(1,3,y,x1,x2,nP);
		CreatemxArrayFromTmcMatrix(&my,y);

		tmcFreeLocalVar(nP);
		tmcFreeLocalVar(x2);
		tmcFreeLocalVar(x1);
		tmcFreeLocalVar(y);
#endif
//////////////////////// tmcinterp1 /////////////
#ifdef MEX_FILE_NAME_tmcinterp1
void tmcinterp1(long nout,long ninput, tmsMatrix *yi, tmsMatrix *x, tmsMatrix *y, tmsMatrix *xi,
			tmsMatrix *typeinter,tmsMatrix *typeextr);

#define myi plhs[0]

#define mx prhs[0]
#define my prhs[1]
#define mxi prhs[2]


tmsMatrix *yi=tmcNewMatrix();

tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
tmsMatrix *y=tmcNewMatrixFromCdouble(mxGetM(my),mxGetN(my),mxGetPr(my),mxGetPi(my));
tmsMatrix *xi=tmcNewMatrixFromCdouble(mxGetM(mxi),mxGetN(mxi),mxGetPr(mxi),mxGetPi(mxi));

//_asm int 4 
		tmcinterp1(1,3,yi,x,y,xi,NULL,NULL);
		CreatemxArrayFromTmcMatrix(&myi,yi);

		tmcFreeLocalVar(xi);
		tmcFreeLocalVar(y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(yi);
#endif
//////////////////////// tmcpolyval /////////////
#ifdef MEX_FILE_NAME_tmcpolyval
void tmcpolyval(long nout,long ninput,tmsMatrix *y,tmsMatrix *p,tmsMatrix *x);

#define my plhs[0]

#define mp prhs[0]
#define mx prhs[1]


tmsMatrix *y=tmcNewMatrix();

tmsMatrix *p=tmcNewMatrixFromCdouble(mxGetM(mp),mxGetN(mp),mxGetPr(mp),mxGetPi(mp));
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));

//_asm int 4 
		tmcpolyval(1,2,y,p,x);
		CreatemxArrayFromTmcMatrix(&my,y);

		tmcFreeLocalVar(x);
		tmcFreeLocalVar(p);
		tmcFreeLocalVar(y);
#endif
//////////////////////// tmcconv /////////////
#ifdef MEX_FILE_NAME_tmcconv
void tmcconv(long nout,long ninput, tmsMatrix *C, tmsMatrix *A, tmsMatrix *B);

#define mC plhs[0]

#define mA prhs[0]
#define mB prhs[1]


tmsMatrix *C=tmcNewMatrix();

tmsMatrix *A=tmcNewMatrixFromCdouble(mxGetM(mA),mxGetN(mA),mxGetPr(mA),mxGetPi(mA));
tmsMatrix *B=tmcNewMatrixFromCdouble(mxGetM(mB),mxGetN(mB),mxGetPr(mB),mxGetPi(mB));

//_asm int 4 
		tmcconv(1,2,C,A,B);
		CreatemxArrayFromTmcMatrix(&mC,C);

		tmcFreeLocalVar(B);
		tmcFreeLocalVar(A);
		tmcFreeLocalVar(C);
#endif

//////////////////////// tmcfind /////////////
#ifdef MEX_FILE_NAME_tmcfind
void tmcfind(long nout,long ninput, tmsMatrix *I,tmsMatrix *J,tmsMatrix *V, tmsMatrix *x,tmsMatrix *Opt,tmsMatrix *sOpt);

#define mI plhs[0]
#define mJ plhs[1]
#define mV plhs[2]

#define mx prhs[0]
#define mOpt prhs[1]
#define msOpt prhs[2]

#define nout	nlhs
#define ninput	nrhs

tmsMatrix *I=tmcNewMatrix();
tmsMatrix *J=tmcNewMatrix();
tmsMatrix *V=tmcNewMatrix();

tmsMatrix *x=tmcNewMatrixFromMxLogical(mx);
tmsMatrix *Opt=NULL;

	
tmsMatrix *sOpt=NULL;

if (nrhs>1)
	Opt = tmcNewMatrixFromCdouble(mxGetM(mOpt),mxGetN(mOpt),mxGetPr(mOpt),mxGetPi(mOpt));
if (nrhs>2)
	sOpt = tmcNewMatrixFromMxString(msOpt);

//_asm int 4 
		tmcfind(nout,ninput,I,J,V,x,Opt,sOpt);
		CreatemxArrayFromTmcMatrix(&mI,I);
if (nlhs>1)
		CreatemxArrayFromTmcMatrix(&mJ,J);
if (nlhs>2)
		CreatemxArrayFromTmcMatrix(&mV,V);

if (nrhs>2)
	tmcFreeLocalVar(sOpt);

if (nrhs>1)
	tmcFreeLocalVar(Opt);

		tmcFreeLocalVar(x);
		tmcFreeLocalVar(V);
		tmcFreeLocalVar(J);
		tmcFreeLocalVar(I);
#endif
		
//////////////////////// tmccond /////////////
#ifdef MEX_FILE_NAME_tmccond
void tmccond(long nout,long ninput, tmsMatrix *y, tmsMatrix *x, tmsMatrix *p);

#define my plhs[0]

#define mx prhs[0]
#define mp prhs[1]

#define nout	nlhs
#define ninput	nrhs

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *p=NULL;

tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
if (nrhs>1)
 if (mxIsChar(mp))
	 p = tmcNewMatrixFromMxString(mp);
 else
	 p = tmcNewMatrixFromCdouble(mxGetM(mp),mxGetN(mp),mxGetPr(mp),mxGetPi(mp));

//_asm int 4 
		tmccond(nlhs,nrhs,y,x,p);
		CreatemxArrayFromTmcMatrix(&my,y);

if (nrhs>1)
		tmcFreeLocalVar(p);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
//////////////////////// tmcsort /////////////
#ifdef MEX_FILE_NAME_tmcsort
void tmcsort(long nout,long ninput, tmsMatrix *y1,tmsMatrix *y2,tmsMatrix *x,tmsMatrix *c);

#define my1 plhs[0]
#define my2 plhs[1]

#define mx prhs[0]
#define mc prhs[1]

#define nout	nlhs
#define ninput	nrhs

tmsMatrix *y1=tmcNewMatrix();
tmsMatrix *y2=tmcNewMatrix();

tmsMatrix *c=NULL;

tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
if (nrhs>1)
	 c = tmcNewMatrixFromMxString(mc);

//_asm int 4 
		tmcsort(nlhs,nrhs,y1,y2,x,c);
		CreatemxArrayFromTmcMatrix(&my1,y1);
if (nlhs>1)
		CreatemxArrayFromTmcMatrix(&my2,y2);

if (nrhs>1)
		tmcFreeLocalVar(c);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y2);
		tmcFreeLocalVar(y1);
#endif
/////////////////////////////// tmceps /////////////////////
           //_asm int 4
#ifdef MEX_FILE_NAME_tmceps
#define my plhs[0]
#define mx prhs[0]
long k;
double *ptr,*pti;
tmsMatrix *x=NULL;

tmsMatrix *y=tmcNewMatrix();
if (nrhs>0)
 x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));


//_asm int 4 
		tmceps(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
if (nrhs>1)
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
#endif
}

