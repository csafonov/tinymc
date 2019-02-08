//! MEX: r=roots_qd(P)
//! MATLAB 6 (32 bit):
//!  mex   -output roots_qd  roots_qd.c tmcruntime_mingw_qd_w32.lib tmcruntime_mingw_w32.lib
//! MATLAB 7 (64 bit):
//!  mex   -output roots_qd.mexw64  roots_qd.c  tmcruntime_mingw_qd_w64.lib tmcruntime_mingw_w64.lib

#include "tmcmexutils.c" 
#include <windows.h>

//#pragma comment(lib,"tmcruntime_mingw_qd_w64.lib")

void  tmcroots_qd(long nout,long ninput,tmsMatrix *r,tmsMatrix *p);
//void tmcroots_qd(long nout,long ninput,tmsMatrix *r,tmsMatrix *p);



void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
//#ifdef MEX_FILE_NAME_tmcroots
#define my plhs[0]
#define mx prhs[0]
//long k;
//double *ptr,*pti;

tmsMatrix *y=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrixFromCdouble(mxGetM(mx),mxGetN(mx),mxGetPr(mx),mxGetPi(mx));
//_asm int 4 
		tmcroots_qd(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
//#endif
}
