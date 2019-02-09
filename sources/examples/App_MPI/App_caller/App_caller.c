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
// for x64
#ifdef WIN_x64
#ifdef _DEBUG
//#pragma comment(lib,"tmcrtvc8_x64.lib")
#pragma comment(lib,".\\x64\\debug\\dll_getcurloop.lib")
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
#else // not MSVC
#define EXT_LINKAGE
#endif


//#include "tmc_lib.h"
#include "mpi.h" 
#include <stdio.h>
#pragma comment(lib,"msmpi.lib")

//EXT_LINKAGE void tmcTestO(int nargout, int nargin,tmsMatrix *y,tmsMatrix *x);
//extern EXT_LINKAGE const struct CInit_funcs_table Init_funcs_table ;
/*EXT_LINKAGE*/ void __stdcall calccurrentctrl(double *PropGain,double *IntGain,long *FreqLen,double *FreqHz,
							   double *OL_Mag,double *OL_Ph,double *CL_Mag,double *CL_Ph,
							   long *RespLen,double *RespTime,double *Resp,long MaxFreqLen,long MaxTimeLen,double R,double L,double Ts,double Ovs);


void usectime_init(void);
long usectime(void);

///////////////////////// UTILITIES ///////////////
#if defined(WIN32) & defined(_MSC_VER)

//extern __int64 g_MemCnt;
//extern __int64 g_MemN;
//extern __int64 g_MemUsed;
//extern double *g_MemHe[1000];
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
//   hWnd=CreateWindow(
//  L"edit",  // pointer to registered class name
//  L"tmcdebug", // pointer to window name
 // WS_DISABLED,        // window style
 // 0,                // horizontal position of window
 // 0,                // vertical position of window
 // 1,           // window width
 // 1,          // window height
 // NULL,      // handle to parent or owner window
//  0,          // handle to menu or child-window identifier
 // NULL,     // handle to application instance
 // NULL        // pointer to window-creation data
//);
//tmcdbgOpenDebugger();

//#endif


GlobalMemoryStatus(&mems);


hProcessId=GetCurrentProcessId();
#endif



/////////////////
//tmcInitLib(&Init_funcs_table);
}
void FinDll()
{
//tmcFreeLib();
//////////////
#if defined(WIN32) & defined(_MSC_VER)
//fprintf(stdout,"Mem=%I64d,N=%I64d,MU=%I64d,Time=%f \n",g_MemCnt,g_MemN,g_MemUsed,0);

GlobalMemoryStatus(&memf);
printf("MEM DELTA=%I64d\n",mems.dwAvailPhys-memf.dwAvailPhys);
//_CrtCheckMemory( );
#ifdef _DEBUG_MEMORY
 _CrtDumpMemoryLeaks( );

SET_CRT_DEBUG_FIELD( _CRTDBG_LEAK_CHECK_DF );
#endif
#ifdef _DEBUG
//DestroyWindow(hWnd);
//tmcdbgCloseDebugger();
#endif
#endif

//////////////
return ;
}


 void javatmcSignalError(char *ExceptMessageBuf)
{
// Application specific handle is here

}
#define MaxFreqLen 1000
#define MaxTimeLen  60
 struct Cdata
 {
	double R ;
	double  L  ;
	double  Ts ;
	double  Ovs ;
 };
 struct CdataRes
 {
	 double  PropGain;
	 double  IntGain;
	 long  RespLen;
 };

int  main(int argc, char *argv[])
{
long t1,t2;
////////////
   double      FreqHz[MaxFreqLen];
   double      OL_Mag [MaxFreqLen];
   double      OL_Ph [MaxFreqLen];
   double      CL_Mag[MaxFreqLen];
   double      CL_Ph [MaxFreqLen];
   double     RespTime[MaxTimeLen];
   double     Resp [MaxTimeLen];

double  PropGain, IntGain;
long RespLen, FreqLen;
double R, L,Ts,Ovs;
/// MPI
char processor_name[MPI_MAX_PROCESSOR_NAME];
int done = 0, n, myid, numprocs, i;
int  namelen;
char outfilename[256];
struct Cdata data;
struct CdataRes datares[1000] ;
///////////////////////
InitDll();

usectime_init();
t1=usectime();


MPI_Init(  &argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
MPI_Comm_rank(MPI_COMM_WORLD, &myid);
MPI_Get_processor_name(processor_name, &namelen);

sprintf(outfilename,"r%d.txt", myid);
FILE *f = fopen(outfilename,"w");

fprintf(stdout, "Process %d of %d is on %s\n",
	myid, numprocs, processor_name);
fflush(stdout);

fprintf(f, "Process %d of %d is on %s\n",
	myid, numprocs, processor_name);
fflush(f);


	//tmcTestO(1, 1,y,x);
R  =0.2;
L = 2e-3;
Ts = 50e-6;
Ovs =   1+ 0.01*15;

if (myid==0)
{
	/** MPI_Bcast(
		void* data,
		int count,
		MPI_Datatype datatype,
		int root,
		MPI_Comm communicator) */


	int i;
	for (i = 0; i < numprocs; i++) {
		if (i != myid) {

			data.L = L;// *i;
			data.Ovs =  Ovs;//i *
			data.R =  R;//i *
			data.Ts = Ts;

			MPI_Send(&data, sizeof(data)/sizeof(char), MPI_CHAR, i, 0, MPI_COMM_WORLD);
		}
	}
 
}
else
{
	MPI_Recv(&data, sizeof(data) / sizeof(char), MPI_CHAR, 0, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	R = data.R;
	L = data.L;
	Ovs = data.Ovs;
}

fprintf(f, "R=%f,L=%f,Ovs=%f\n",R,L,Ovs );
fflush(f);

calccurrentctrl(&PropGain,&IntGain,&FreqLen,FreqHz,
							   OL_Mag,OL_Ph,CL_Mag,CL_Ph,
							   &RespLen,RespTime,Resp,MaxFreqLen,MaxTimeLen, R, L,Ts,Ovs);

fprintf(f, "My: Kp=%f,Ki=%f \n", PropGain, IntGain);
fflush(f);

if (myid == 0)
{
	int i;
	for (i = 0; i < numprocs; i++) {
		if (i != myid) {

			//data.L = L * i;
			//data.Ovs = i * Ovs;
			//data.R = i * R;
			//data.Ts = Ts;
			MPI_Recv(&datares[i], sizeof(datares[0]) / sizeof(char), MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (datares[i].RespLen > 0)
				fprintf(f, "node %d:Kp=%f,Ki=%f \n", i, datares[i].PropGain, datares[i].IntGain);
			else
				fprintf(f, "node %d:solution not found \n",i);
			fflush(f);

		}
	}

}
else
{
	datares[0].IntGain = IntGain;
	datares[0].PropGain = PropGain;
	datares[0].RespLen = RespLen;
	MPI_Send(&datares[0], sizeof(datares[0]) / sizeof(char), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
}

t2=usectime();


#if defined(WIN32) & defined(_MSC_VER)
//fprintf(stdout,"Mem=%I64d,N=%I64d,MU=%I64d,Time=%f \n",g_MemCnt,g_MemN,g_MemUsed,1e-6f*((long)(t2-t1)));
#endif

FinDll();
#if defined(WIN32) & defined(_MSC_VER)
GlobalMemoryStatus(&memf);
printf("MEM DELTA=%I64d\n",mems.dwAvailPhys-memf.dwAvailPhys);
#endif

MPI_Finalize();
fclose(f);
return 0;
}
