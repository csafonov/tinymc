/// \file  tmc_mpi.c
/// Octave/mpi-compatible MPI wrapper for TMC


#include "mpi.h"  // $(MSMPI_INC)

#include <math.h>
#include "mex.h"

#ifndef TMC_MAKEMEX
#define TMCMEX_DLL // must define for TMC
#pragma comment(lib,"msmpi.lib") // $(MSMPI_LIB64)
#endif

#define nrhs	nargin
#define nlhs	nargout

#ifndef TMCMEX_DLL
#include "mexport.h"
#define nrhs	nargin
#define nlhs	nargout

//#include "mex.h"
//#include "mexport.h"
#endif
/*=================================================================
* function numprocs = MPI_Comm_size(COMM);
example function
	COMM = MPI_Comm_Load;
	numprocs= MPI_Comm_size(COMM);
wrapper for
MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
*=================================================================*/
#ifndef TMCMEX_DLL
#define mY	plhs[0]
#define mX1  prhs[0]
#define mX2  prhs[1]

#define MPI_Comm_size_fn 1
#define MPI_Init_fn 2
#define MPI_Finalize_fn 3
#define MPI_Comm_Load_fn 4
#define	MPI_Comm_rank_fn 5
#define	MPI_Send_fn	6
#define	MPI_Recv_fn	7
#endif

#if (TMCMEX_NAME==MPI_Comm_size_fn) || defined(TMCMEX_DLL)
#if !defined(TMCMEX_DLL)
#define mCOMM  prhs[0]
void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray*prhs[] )
#else defined(TMCMEX_DLL)
void tmcMPI_Comm_size(int nargout, int nargin,tmsMatrix *mY, tmsMatrix *mCOMM)
#endif
{
    double * Y_rPtr;
	int      numprocs;
	MPI_Comm COMM;
    /* Check for proper number of arguments */
    if (nrhs != 1)
    {
        mexErrMsgTxt("One input arguments required.");
    }
    if (nlhs != 1) {
        mexErrMsgTxt("One output argument required.");
    }
    
    /* Create a matrix for the return argument */
    TMCMEX_CREATE_DOUBLE_MATRIX(mY,1, 1 , mxREAL );
    Y_rPtr = mxGetPr ( mY  );
	//COMM = (MPI_Comm)mCOMM->value.complx.rData[0];
	COMM = (MPI_Comm) mxGetPr(mCOMM)[0];
	//MPI_Comm_size(COMM, &numprocs);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	Y_rPtr[0] = (double)numprocs;
    return;
}
#endif


#if (TMCMEX_NAME == MPI_Init_fn ) || defined(TMCMEX_DLL)
#if !defined(TMCMEX_DLL)
#define mCOMM  prhs[0]
void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray*prhs[] )
#else
void tmcMPI_Init(int nargout, int nargin, tmsMatrix *mY)
#endif
//////////////////
/**
	INFO = MPI_Init()
*/

{
	double * Y_rPtr;
	int stat;
	/* Check for proper number of arguments */
	if (nrhs > 0)
	{
		mexErrMsgTxt("Zero  input arguments required.");
	}
	if (nlhs != 1) {
		mexErrMsgTxt("MPI_Init:One output argument required.");
	}

	/* Create a matrix for the return argument */
	if (nargout>0)
	{
		stat = MPI_Init(NULL,NULL);
		TMCMEX_CREATE_DOUBLE_MATRIX(mY, 1, 1, mxREAL);
		Y_rPtr = mxGetPr(mY);
		Y_rPtr[0] = (double)stat;
	}
	return;
}
#endif

/**
INFO = MPI_Finalize ()
*/
#if (TMCMEX_NAME ==  MPI_Finalize_fn ) || defined(TMCMEX_DLL)
#if !defined(TMCMEX_DLL)
void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray*prhs[] )
#else
void tmcMPI_Finalize(int nargout, int nargin, tmsMatrix *mY)
#endif
{
	double * Y_rPtr;
	int stat;
	/* Check for proper number of arguments */
	if (nrhs > 0)
	{
		mexErrMsgTxt("Zero  input arguments required.");
	}
	if (nlhs != 1) {
		mexErrMsgTxt("One output argument required.");
	}

	/* Create a matrix for the return argument */
	if (nargout>0)
	{
		stat = MPI_Finalize();
		TMCMEX_CREATE_DOUBLE_MATRIX(mY, 1, 1, mxREAL);
		Y_rPtr = mxGetPr(mY);
		Y_rPtr[0] = (double)stat;
	}
	return;
}
#endif


/**
* COMM = MPI_Comm_Load (DESCRIPTION)
*/
#if (TMCMEX_NAME ==  MPI_Comm_Load_fn ) || defined(TMCMEX_DLL)
#if !defined(TMCMEX_DLL)
#define mD  prhs[0]
void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray*prhs[] )
#else
void tmcMPI_Comm_Load(int nargout, int nargin, tmsMatrix *mY, tmsMatrix *mD)
#endif
{
	double * Y_rPtr;
	/* Check for proper number of arguments */
	if (nrhs > 1)
	{
		mexErrMsgTxt("Zero or one input arguments required.");
	}
	if (nlhs != 1) {
		mexErrMsgTxt("One output argument required.");
	}

	/* Create a matrix for the return argument */
	if (nargout>0)
	{
		TMCMEX_CREATE_DOUBLE_MATRIX(mY, 1, 1, mxREAL);
		Y_rPtr = mxGetPr(mY);
		Y_rPtr[0] = (double)MPI_COMM_WORLD;
	}
	return;
}
#endif


/**
	[RANK INFO] = MPI_Comm_rank (COMM)
*/
#if (TMCMEX_NAME==MPI_Comm_rank_fn) || defined(TMCMEX_DLL)
#if !defined(TMCMEX_DLL)
#define mCOMM  prhs[0]
void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray*prhs[] )
#else defined(TMCMEX_DLL)
void tmcMPI_Comm_rank(int nargout, int nargin,tmsMatrix *mY, tmsMatrix *mCOMM)
#endif
{
	double * Y_rPtr;
	int      numprocs;
	MPI_Comm COMM;
	/* Check for proper number of arguments */
	if (nrhs != 1)
	{
		mexErrMsgTxt("One input arguments required.");
	}
	if (nlhs != 1) {
		mexErrMsgTxt("One output argument required.");
	}

	/* Create a matrix for the return argument */
	TMCMEX_CREATE_DOUBLE_MATRIX(mY, 1, 1, mxREAL);
	Y_rPtr = mxGetPr(mY);
	//COMM = (MPI_Comm)mCOMM->value.complx.rData[0];
	COMM = (MPI_Comm) mxGetPr(mCOMM)[0];
	MPI_Comm_rank(COMM, &numprocs);
	//MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	Y_rPtr[0] = (double)numprocs;
	return;
}
#endif


/**
	\brief INFO = MPI_Send(VALUE,RANKS,TAG,COMM)
	\param X   an matrix to  send
	\param RANKS   a vector with ranks of destination processes
	\param TAG     an integer to identify the message by openmpi
	\param COMM      communicator   returned by MPI_Comm_Load function
*/
#if (TMCMEX_NAME==MPI_Send_fn) || defined(TMCMEX_DLL)
#if !defined(TMCMEX_DLL)
#define mX  prhs[0]
#define mRanks  prhs[1]
#define mTag  prhs[2]
#define mCOMM  prhs[3]
void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray*prhs[] )
#else defined(TMCMEX_DLL)
void tmcMPI_Send(int nargout, int nargin, tmsMatrix *mY, tmsMatrix *mX, tmsMatrix *mRanks,tmsMatrix *mTag, tmsMatrix *mCOMM)
#endif
{
	double * Y_rPtr;
	int      numprocs;
	MPI_Comm COMM;
	int i;
	int stat=0;
	int stat1;
	int dest,tag;
	int MN[3];
	/* Check for proper number of arguments */
	if (nrhs != 4)
	{
		mexErrMsgTxt("4 input arguments required.");
	}
	if (nlhs > 1) {
		mexErrMsgTxt("One output argument required.");
	}
	numprocs = mxGetM(mRanks)*mxGetN(mRanks);
//	tag = (int)mTag->value.complx.rData[0];
//	COMM = (MPI_Comm)mCOMM->value.complx.rData[0];
	tag = (int)mxGetPr(mTag)[0];
	COMM = (MPI_Comm)mxGetPr(mCOMM)[0];

	for (i = 0; i < numprocs; i++) {
		//dest = (int)mRanks->value.complx.rData[i];
		dest = (int)mxGetPr(mRanks)[i];

		//stat1=	MPI_Send(mX, sizeof(*mX) / sizeof(char), MPI_CHAR, dest, tag, COMM);
		//if (stat == 0)
		//	stat = stat1;
		MN[0]=mxGetM(mX);MN[1]=mxGetN(mX);MN[2]=mxIsComplex(mX);
		stat1=	MPI_Send(MN, sizeof(MN) / sizeof(char), MPI_CHAR, dest, tag, COMM);
		if (stat == 0)
			stat = stat1;


		//stat1 = MPI_Send(mX->value.complx.rData, mxGetM(mX)* mxGetN(mX)*sizeof(double) / sizeof(char), MPI_CHAR, dest, tag, COMM);
		stat1 = MPI_Send( mxGetPr(mX), mxGetM(mX)* mxGetN(mX)*sizeof(double) / sizeof(char), MPI_CHAR, dest, tag, COMM);
		if (stat == 0)
			stat = stat1;
		if (mxIsComplex(mX))
		{
			//stat1 = MPI_Send(mX->value.complx.iData, mxGetM(mX)* mxGetN(mX) * sizeof(double) / sizeof(char), MPI_CHAR, dest, tag, COMM);
			stat1 = MPI_Send(mxGetPi(mX), mxGetM(mX)* mxGetN(mX) * sizeof(double) / sizeof(char), MPI_CHAR, dest, tag, COMM);
			if (stat == 0)
				stat = stat1;
		}
	}



	/* Create a matrix for the return argument */
	TMCMEX_CREATE_DOUBLE_MATRIX(mY, 1, 1, mxREAL);
	Y_rPtr = mxGetPr(mY);
		Y_rPtr[0] = (double)stat;
	return;
}
#endif

/**
	[Y, INFO] = MPI_Recv(SOURCE,TAG,COMM)
	\param SOURCE   an integer indicating source process
	\param TAG      an integer to identify the message by openmpi
	\param COMM   communicator  returned by MPI_Comm_Load function
*/
#if (TMCMEX_NAME==MPI_Recv_fn) || defined(TMCMEX_DLL)
#if !defined(TMCMEX_DLL)
#define mStatus		plhs[1]
#define mSrc  prhs[0]
#define mTag	prhs[1]
#define mCOMM	prhs[2]
void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray*prhs[] )
#else defined(TMCMEX_DLL)
void tmcMPI_Recv(int nargout, int nargin, tmsMatrix *mY, tmsMatrix *mStatus,tmsMatrix *mSrc, tmsMatrix *mTag, tmsMatrix *mCOMM)
#endif
{
	double * Y_rPtr;
	MPI_Comm COMM;
	int stat=0, stat1;
	int tag;
	int src;
	//char data[10000];//haard todo
	//tmsMatrix dd;
	int MN[3];

	/* Check for proper number of arguments */
	if (nrhs != 3)
	{
		mexErrMsgTxt("3 input arguments required.");
	}
	if (nlhs > 2) {
		mexErrMsgTxt("2 output argument required.");
	}

	//tag = (int)mTag->value.complx.rData[0];
	//COMM = (MPI_Comm)mCOMM->value.complx.rData[0];
	//src = (int)mSrc->value.complx.rData[0];
	tag = (int)mxGetPr(mTag)[0];
	COMM = (MPI_Comm)mxGetPr(mCOMM)[0];
	src = (int)mxGetPr(mSrc)[0];

	//stat1=MPI_Recv(&dd, sizeof(dd) / sizeof(char), MPI_CHAR, src, tag, COMM, MPI_STATUS_IGNORE);
	stat1=MPI_Recv(MN, sizeof(MN) / sizeof(char), MPI_CHAR, src, tag, COMM, MPI_STATUS_IGNORE);
	if (stat == 0)
		stat = stat1;

	/* Create a matrix for the return argument */
	//TMCMEX_CREATE_DOUBLE_MATRIX(mY, mxGetM((&dd)), mxGetN((&dd)), mxIsComplex((&dd)) ? mxCOMPLEX: mxREAL);
	TMCMEX_CREATE_DOUBLE_MATRIX(mY, MN[0],MN[1], MN[2] ? mxCOMPLEX: mxREAL);
	TMCMEX_CREATE_DOUBLE_MATRIX(mStatus, 1, 1, mxREAL);

	//stat1 = MPI_Recv(mY->value.complx.rData, mxGetM(mY)* mxGetN(mY)*sizeof(double) / sizeof(char), MPI_CHAR, src, tag, COMM, MPI_STATUS_IGNORE);
	stat1 = MPI_Recv(mxGetPr(mY), mxGetM(mY)* mxGetN(mY)*sizeof(double) / sizeof(char), MPI_CHAR, src, tag, COMM, MPI_STATUS_IGNORE);

	if (stat == 0)
		stat = stat1;
	//if (mxIsComplex((&dd)))
	if ( MN[2])
	{
		//stat1 = MPI_Recv(mY->value.complx.iData, mxGetM(mY)* mxGetN(mY) * sizeof(double) / sizeof(char), MPI_CHAR, src, tag, COMM, MPI_STATUS_IGNORE);
		stat1 = MPI_Recv(mxGetPi(mY), mxGetM(mY)* mxGetN(mY) * sizeof(double) / sizeof(char), MPI_CHAR, src, tag, COMM, MPI_STATUS_IGNORE);
		if (stat == 0)
			stat = stat1;
	}
	Y_rPtr = mxGetPr(mStatus);
		Y_rPtr[0] = (double)stat;
	return;
}
#endif
