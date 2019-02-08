/*
mex -g readprocessmem.c user32.lib
*/
#include "mex.h"
#include <windows.h>
char buffer[10000];
void mexFunction(int nlhs, mxArray *plhs[], 
				 int nrhs, const mxArray *prhs[])
{    
double *dPtr;
HANDLE hProcess_copy;
DWORD h_Other_id;
void *lpBaseAddress;
long len;
DWORD stat;
DWORD NumberOfBytesRead;
int k;

	if (nlhs >1 || nrhs != 3)
	{
		mexErrMsgTxt("Correct syntax: buff = readprocessmem( hProcess_copy,Addr,Len )\n");
	}


	hProcess_copy = (HANDLE)(long)*mxGetPr( prhs[0] ) ;
	lpBaseAddress = (void *)(long)*mxGetPr( prhs[1] ) ;
	len = (void *)(long)*mxGetPr( prhs[2] ) ;
	if (len>=10000)
	{
		mexErrMsgTxt("must be Len < 10000 )\n");
	}

	stat=ReadProcessMemory(hProcess_copy,lpBaseAddress,buffer,len,&NumberOfBytesRead);
	if (NumberOfBytesRead != len)
	{
		mexErrMsgTxt("cant read memory \n");
	}

	plhs[0] = mxCreateDoubleMatrix( 1 , NumberOfBytesRead , mxREAL ) ; 
	dPtr = mxGetPr( plhs[0] ) ;
	for (k=0;k<NumberOfBytesRead;k++)
	{
			dPtr[k] = (long)buffer[k];
	}
}