/*
mex -g getwndprocess.c user32.lib
*/
#include "mex.h"
#include <windows.h>
void mexFunction(int nlhs, mxArray *plhs[], 
				 int nrhs, const mxArray *prhs[])
{    
double *dPtr;
HANDLE hWnd;
HANDLE hProcess_copy;
DWORD h_Other_id;

	if (nlhs >1 || nrhs != 1)
	{
		mexErrMsgTxt("Correct syntax: hProcess_copy = getwndprocess( hWnd )\n");
	}


	hWnd = (HANDLE)(long)*mxGetPr( prhs[0] ) ;
	GetWindowThreadProcessId(hWnd,&h_Other_id);
	hProcess_copy = OpenProcess(PROCESS_ALL_ACCESS,FALSE,h_Other_id);

	plhs[0] = mxCreateDoubleMatrix( 1 , 1 , mxREAL ) ; 
	dPtr = mxGetPr( plhs[0] ) ;
	dPtr[0]=(long)hProcess_copy;
}