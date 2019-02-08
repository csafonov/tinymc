//! MEX: r=roots_d(P)
//!  mex   -output roots_d  tmcroots_d.c


#include "tmcmexutils.c" 
#include <windows.h>

//#pragma comment(lib,"tmcruntime_mingw_qd_w64.lib")



HANDLE hDll;
HANDLE hDll2;
void  (*tmcroots)(long nout,long ninput,tmsMatrix *r,tmsMatrix *p);
//void tmcroots(long nout,long ninput,tmsMatrix *r,tmsMatrix *p);

BOOL WINAPI DllMain(
  HINSTANCE hinstDLL,  // handle to DLL module
  DWORD fdwReason,     // reason for calling function
  LPVOID lpvReserved   // reserved
)
{
	switch( fdwReason )
	{
	case DLL_PROCESS_ATTACH :
	hDll = LoadLibrary("tmcruntime_mingw_w64.dll");//LoadLibrary("tmcruntime_mingw_qd_w64.dll");
	if (hDll)
	{
		printf("tmcruntime_mingw_qd_w64 loaded Ok\n");
		tmcroots = ( void (*)(long nout,long ninput,tmsMatrix *r,tmsMatrix *p))GetProcAddress(hDll, "tmcroots");
		if (tmcroots)
		{
			printf("tmcroots  Ok\n");
		}
	}

	hDll2 = hDll;//LoadLibrary("tmcruntime_mingw_w64.dll");
	if (hDll2)
	{
		printf("tmcruntime_mingw_w64 loaded Ok\n");
		__tmcNewMatrix = ( tmsMatrix* (*)(void))GetProcAddress(hDll2, "__tmcNewMatrix");
		if (__tmcNewMatrix)
		{
			printf("__tmcNewMatrix  Ok\n");
		}
		tmcCreateString = ( void (*)(tmsMatrix *matres,const char *str))GetProcAddress(hDll2, "tmcCreateString");
		if (tmcCreateString)
		{
			printf("tmcCreateString  Ok\n");
		}
		tmcFreeLocalVar = ( void (*)(tmsMatrix *src))GetProcAddress(hDll2, "tmcFreeLocalVar");
		if (tmcFreeLocalVar)
		{
			printf("tmcFreeLocalVar  Ok\n");
		}
		_tmcCreateMatrix = ( void (*)(tmsMatrix *res,long M,long N,short bHasImagine))GetProcAddress(hDll2, "_tmcCreateMatrix");
		if (_tmcCreateMatrix)
		{
			printf("_tmcCreateMatrix  Ok\n");
		}


	}

		break ;
	case DLL_THREAD_ATTACH  :
		break ;
	case DLL_THREAD_DETACH  :
		break ;
	case DLL_PROCESS_DETACH :
		if (hDll) 
		{
			FreeLibrary(hDll);
			hDll=0;tmcroots=0;
		}
		if (hDll2) 
		{
			FreeLibrary(hDll2);
			hDll2=0;
		}

			
		break ;
	}

	return 1;
}

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
		tmcroots(nlhs,nrhs,y,x);
		CreatemxArrayFromTmcMatrix(&my,y);
		tmcFreeLocalVar(x);
		tmcFreeLocalVar(y);
//#endif
}
