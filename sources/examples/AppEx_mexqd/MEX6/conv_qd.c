//! MEX: r=conv_qd(P)
//! MATLAB 6 (32 bit):
//!  mex   -output conv_qd  conv_qd.c  tmcruntime_mingw_qd_w32.lib tmcruntime_mingw_w32.lib
//! MATLAB 7 (64 bit):
//!  mex   -output conv_qd.mexw64  conv_qd.c  tmcruntime_mingw_qd_w64.lib tmcruntime_mingw_w64.lib


#include "tmcmexutils.c" 
#include <windows.h>

//#pragma comment(lib,"tmcruntime_mingw_qd_w64.lib")
void  tmcconv_qd(long nout,long ninput, tmsMatrix *C, tmsMatrix *A, tmsMatrix *B);

#define mC plhs[0]
#define mA prhs[0]
#define mB prhs[1]

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
tmsMatrix *C=tmcNewMatrix();
tmsMatrix *A=tmcNewMatrixFromCdouble(mxGetM(mA),mxGetN(mA),mxGetPr(mA),mxGetPi(mA));
tmsMatrix *B=tmcNewMatrixFromCdouble(mxGetM(mB),mxGetN(mB),mxGetPr(mB),mxGetPi(mB));
//_asm int 4 
		tmcconv_qd(1,2,C,A,B);
		CreatemxArrayFromTmcMatrix(&mC,C);

		tmcFreeLocalVar(B);
		tmcFreeLocalVar(A);
		tmcFreeLocalVar(C);
}
