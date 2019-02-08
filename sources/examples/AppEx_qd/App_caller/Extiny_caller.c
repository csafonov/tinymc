// For linux 
// LGPL Lisence

#if  defined(TMCDEBUG)
#include <windows.h>
DWORD hProcessId;
MEMORYSTATUS mems,memf;
HANDLE hWnd;
#endif

#if defined(WIN32) & defined(_MSC_VER)
#include <windows.h>


#define EXT_LINKAGE __declspec(dllimport)
#if _MSC_VER < 1800
// for x64
#ifdef WIN_x64
#ifdef _DEBUG
#pragma comment(lib,"tmcrtvc8d_x64.lib")
#pragma comment(lib,"..\\bin\\x64\\SIMOD.lib")
#else
#pragma comment(lib,"tmcrtvc8_x64.lib")
#pragma comment(lib,"..\\bin\\x64\\SIMOR.lib")
#endif

#else // x86

#ifdef _DEBUG
#pragma comment(lib,"tmcrtvc8d.lib")
#pragma comment(lib,"..\\bin\\SIMOD.lib")
#else
#pragma comment(lib,"tmcrtvc8.lib")
#pragma comment(lib,"..\\bin\\SIMOR.lib")
#endif

#endif
#endif

#else // not MSVC
#define EXT_LINKAGE
#endif



#include "tmc_lib.h"
#include <stdio.h>


EXT_LINKAGE void tmcTestO(int nargout, int nargin,tmsMatrix *y,tmsMatrix *x);
extern EXT_LINKAGE const struct CInit_funcs_table Init_funcs_table ;

void usectime_init(void);
long usectime(void);

///////////////////////// UTILITIES ///////////////
#if defined(WIN32) & defined(_MSC_VER)

extern __int64 g_MemCnt;
extern __int64 g_MemN;
extern __int64 g_MemUsed;
extern double *g_MemHe[1000];
//__int64 g_MemCnt;
//__int64 g_MemN;

extern LARGE_INTEGER time_start ;	
DWORD hProcessId;
MEMORYSTATUS mems,memf;
	HANDLE hWnd;

//#ifdef _MANAGED
//#pragma managed(push, off)
//#endif

LARGE_INTEGER time_start ;	
void usectime_init(void)
{
	QueryPerformanceCounter( &time_start) ;
}

long usectime(void)
{
	double out ;
	LARGE_INTEGER time,freq,dt ;	

	QueryPerformanceFrequency( &freq ) ;
	QueryPerformanceCounter( &time) ;
	dt.QuadPart = time.QuadPart-time_start.QuadPart;
	out = ((double)dt.QuadPart)/(double)(freq.QuadPart*1e-6f) ;
	return (long)out;
}


#else
void usectime_init(void)
{
}

long usectime(void)
{
	double out=0 ;
	return (long)out;
}
#endif
//////////////////////////////////////////


void InitDll()
{
/////////////////
#if (defined(WIN32) & defined(_MSC_VER)) || defined(TMCDEBUG)
// Send all reports to STDOUT
#ifdef _DEBUG_MEMORY
   _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
   _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
   _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
   _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );
#endif
// Set the debug-heap flag so that freed blocks are kept on the
   // linked list, to catch any inadvertent use of freed memory
//   SET_CRT_DEBUG_FIELD( _CRTDBG_DELAY_FREE_MEM_DF );
//#ifdef _DEBUG
   hWnd=CreateWindow(
  L"edit",  // pointer to registered class name
  L"tmcdebug", // pointer to window name
  WS_DISABLED,        // window style
  0,                // horizontal position of window
  0,                // vertical position of window
  1,           // window width
  1,          // window height
  NULL,      // handle to parent or owner window
  0,          // handle to menu or child-window identifier
  NULL,     // handle to application instance
  NULL        // pointer to window-creation data
);
tmcdbgOpenDebugger();

//#endif


GlobalMemoryStatus(&mems);


hProcessId=GetCurrentProcessId();
#endif



/////////////////
tmcInitLib(&Init_funcs_table);
}
void FinDll()
{
tmcFreeLib();
//////////////
#if defined(WIN32) & defined(_MSC_VER)
fprintf(stdout,"Mem=%I64d,N=%I64d,MU=%I64d,Time=%f \n",g_MemCnt,g_MemN,g_MemUsed,0);

GlobalMemoryStatus(&memf);
printf("MEM DELTA=%d\n",mems.dwAvailPhys-memf.dwAvailPhys);
//_CrtCheckMemory( );
#ifdef _DEBUG_MEMORY
 _CrtDumpMemoryLeaks( );

SET_CRT_DEBUG_FIELD( _CRTDBG_LEAK_CHECK_DF );
#endif
#ifdef _DEBUG
DestroyWindow(hWnd);
tmcdbgCloseDebugger();
#endif
#endif

//////////////
return ;
}


 void javatmcSignalError(char *ExceptMessageBuf)
{
// Application specific handle is here

}

void  main(void)
{

tmsMatrix *x;
tmsMatrix *y;
tmsMatrix *z;
tmsMatrix *yy;

tmsMatrix *a;
tmsMatrix *b;
long t1,t2;

/////////////
#if defined(WIN32) & defined(_MSC_VER)
HANDLE hWnd=CreateWindow(
  L"edit",  // pointer to registered class name
  L"tmcdebug", // pointer to window name
  WS_DISABLED,        // window style
  0,                // horizontal position of window
  0,                // vertical position of window
  1,           // window width
  1,          // window height
  NULL,      // handle to parent or owner window
  0,          // handle to menu or child-window identifier
  NULL,     // handle to application instance
  NULL        // pointer to window-creation data
);
#endif

////////////
InitDll();

x = tmcNewMatrix();
y = tmcNewMatrix();
z = tmcNewMatrix();
yy = tmcNewMatrix();

a = tmcNewMatrix();
b = tmcNewMatrix();

tmcScalar(a,0);
tmcScalar(b,3);

tmcScalar(x,100);

usectime_init();
t1=usectime();

//for (kk=0;kk<1000;kk++)
//{
//tmctestM(2, 4,x,y,z,yy,a,b);
//tmctestM(1, 2,x,a,b);
	tmcTestO(1, 1,y,x);

//	*nErrCode =(long) x->value.complx.rData[0];

//}

t2=usectime();


tmcDisplayMat(x,1);
tmcDisplayMat(y,1);
//tmcDisplayMat(a,1);
//tmcDisplayMat(b,1);

//fp=fopen("debugout.mat","wb");
//	Store2MatFile(fp ,"x" , x->m_rData , x->m_desc.m_nRows , x->m_desc.m_nCols);
//	StoreComplex2MatFile(fp ,"y" , y->m_rData ,y->m_iData, y->m_desc.m_nRows , y->m_desc.m_nCols);
//fclose(fp);

tmcFreeLocalVar(x);
tmcFreeLocalVar(y);
tmcFreeLocalVar(z);
tmcFreeLocalVar(yy);
tmcFreeLocalVar(a);
tmcFreeLocalVar(b);

#if defined(WIN32) & defined(_MSC_VER)
fprintf(stdout,"Mem=%I64d,N=%I64d,MU=%I64d,Time=%f \n",g_MemCnt,g_MemN,g_MemUsed,1e-6f*((long)(t2-t1)));
#endif

FinDll();
#if defined(WIN32) & defined(_MSC_VER)
GlobalMemoryStatus(&memf);
printf("MEM DELTA=%d\n",mems.dwAvailPhys-memf.dwAvailPhys);
#endif

}
