/*
mex -g findwnd.c user32.lib
*/
#include "mex.h"
#include <windows.h>
void mexFunction(int nlhs, mxArray *plhs[], 
				 int nrhs, const mxArray *prhs[])
{    
double *dPtr;
HANDLE hWnd;
char *Name  ;

	if (nlhs >1 || nrhs != 1)
	{
		mexErrMsgTxt("Correct syntax: hWnd = findwnd( title )\n");
	}
	if( mxIsChar( prhs[0] ) == 0 )
	{
		mexErrMsgTxt( "Parameter 1 must be character string" ) ;
	}
	if( mxIsEmpty( prhs[0] ) )
	{
		mexErrMsgTxt( "Parameter 1 must be non-empty character string" ) ;
	}
	Name = mxArrayToString( prhs[0] ) ;




	hWnd=FindWindow(NULL,Name);
	plhs[0] = mxCreateDoubleMatrix( 1 , 1 , mxREAL ) ; 
	dPtr = mxGetPr( plhs[0] ) ;
	dPtr[0]=(long)hWnd;

	mxFree( Name ) ;
}