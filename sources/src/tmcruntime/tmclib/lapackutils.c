/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license.
 * 
  *****************************************************************************/
// File: lapackutils.c

// Uses clapack interfaces


static char *s_module="algebrautils.c";

//#include "f2c.h"
#include "clapack_types.h"

#define min(a,b) ((a) <= (b) ? (a) : (b))
#define max(a,b) ((a) >= (b) ? (a) : (b))


// DLL version    is funcname_
// static version is funcname
#ifndef _BCC55_ // for Borland 5.5 use statics link
#define dgesvd_ dgesvd
#define zgesvd_ zgesvd
#define dgels_ dgels
#define zgels_ zgels
#define zgeevx_ zgeevx
#define dgeevx_ dgeevx
#define dgetrf_ dgetrf
#define zgetrf_ zgetrf
#endif

#include "clapack.h"

#ifndef _BCC55_ // for Borland 5.5 use statics link
#define zfftf_ zfftf
#define zffti_ zffti
#endif



#ifdef _BCC55_ // for Borland 5.5  
int errno;
#endif

#include "tmc.h"

// fft tools
int __cdecl zffti_(integer *n, doublereal *wsave);
int __cdecl zfftf_(integer *n, doublereal *c__, doublereal *wsave);

//#include <stdlib.h>
#ifndef  _TMC_EMBEDDED_
#include <malloc.h>
#endif
#include <string.h>

#ifndef _BCC55_ // for Borland 5.5 use statics link
#ifndef _TMCRTVC6_

#ifdef WIN32
#ifndef NO_LAPACK_DLL
#ifdef _DEBUG
#pragma comment(lib,"mlapackd.lib")
#else
#pragma comment(lib,"mlapack.lib")
#endif
#endif
#endif
#endif
#endif

#ifdef NO_LAPACK_DLL_xxx
/* Subroutine */ int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, 
	doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
	ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
	integer *info)
	{

		fprintf(stderr,"dgesvd: **** FATAL ****NO LAPACK SUPPORT\n");
		return -1;
	}
/* Subroutine */ int dgels_(char *trans, integer *m, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, 
	doublereal *work, integer *lwork, integer *info)
	{

		fprintf(stderr,"dgels_: **** FATAL ****NO LAPACK SUPPORT\n");
		return -1;
	}

/* Subroutine */ int zgels_(char *trans, integer *m, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *work, integer *lwork, integer *info)
	{
		fprintf(stderr,"zgels_: **** FATAL ****NO LAPACK SUPPORT\n");
		return -1;
	}

/* Subroutine */ int zgeevx_(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, doublecomplex *a, integer *lda, doublecomplex *w, 
	doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, 
	integer *ilo, integer *ihi, doublereal *scale, doublereal *abnrm, 
	doublereal *rconde, doublereal *rcondv, doublecomplex *work, integer * 	
	lwork, doublereal *rwork, integer *info)
	{

		fprintf(stderr,"zgeevx_: **** FATAL ****NO LAPACK SUPPORT\n");
		return -1;
	}



int __cdecl zffti(integer *n, doublereal *wsave)
	{

		fprintf(stderr,"zffti: **** FATAL ****NO FFT SUPPORT\n");
		return -1;
	}

int __cdecl zfftf(integer *n, doublereal *c__, doublereal *wsave)
	{

		fprintf(stderr,"zfftf: **** FATAL ****NO FFT SUPPORT\n");
		return -1;
	}


#endif


#include <math.h>


void _Cdiv(double *Qr,double *Qi,double ar,double ai,double br,double bi);


void _tmcsvd_z(long nout,long ninput,tmsMatrix *U,tmsMatrix *S,tmsMatrix *V,tmsMatrix *X,tmsMatrix *flag)
{
/*  Purpose   
    =======   

    ZGESVD computes the singular value decomposition (SVD) of a complex   
    M-by-N matrix A, optionally computing the left and/or right singular   
    vectors. The SVD is written   

         A = U * SIGMA * conjugate-transpose(V)   

    where SIGMA is an M-by-N matrix which is zero except for its   
    min(m,n) diagonal elements, U is an M-by-M unitary matrix, and   
    V is an N-by-N unitary matrix.  The diagonal elements of SIGMA   
    are the singular values of A; they are real and non-negative, and   
    are returned in descending order.  The first min(m,n) columns of   
    U and V are the left and right singular vectors of A.   

    Note that the routine returns V**H, not V.   

    Arguments   
    =========   

    JOBU    (input) CHARACTER*1   
            Specifies options for computing all or part of the matrix U:   
            = 'A':  all M columns of U are returned in array U:   
            = 'S':  the first min(m,n) columns of U (the left singular   
                    vectors) are returned in the array U;   
            = 'O':  the first min(m,n) columns of U (the left singular   
                    vectors) are overwritten on the array A;   
            = 'N':  no columns of U (no left singular vectors) are   
                    computed.   

    JOBVT   (input) CHARACTER*1   
            Specifies options for computing all or part of the matrix   
            V**H:   
            = 'A':  all N rows of V**H are returned in the array VT;   
            = 'S':  the first min(m,n) rows of V**H (the right singular   
                    vectors) are returned in the array VT;   
            = 'O':  the first min(m,n) rows of V**H (the right singular   
                    vectors) are overwritten on the array A;   
            = 'N':  no rows of V**H (no right singular vectors) are   
                    computed.   

            JOBVT and JOBU cannot both be 'O'.   

    M       (input) INTEGER   
            The number of rows of the input matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the input matrix A.  N >= 0.   

    A       (input/output) COMPLEX*16 array, dimension (LDA,N)   
            On entry, the M-by-N matrix A.   
            On exit,   
            if JOBU = 'O',  A is overwritten with the first min(m,n)   
                            columns of U (the left singular vectors,   
                            stored columnwise);   
            if JOBVT = 'O', A is overwritten with the first min(m,n)   
                            rows of V**H (the right singular vectors,   
                            stored rowwise);   
            if JOBU .ne. 'O' and JOBVT .ne. 'O', the contents of A   
                            are destroyed.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    S       (output) DOUBLE PRECISION array, dimension (min(M,N))   
            The singular values of A, sorted so that S(i) >= S(i+1).   

    U       (output) COMPLEX*16 array, dimension (LDU,UCOL)   
            (LDU,M) if JOBU = 'A' or (LDU,min(M,N)) if JOBU = 'S'.   
            If JOBU = 'A', U contains the M-by-M unitary matrix U;   
            if JOBU = 'S', U contains the first min(m,n) columns of U   
            (the left singular vectors, stored columnwise);   
            if JOBU = 'N' or 'O', U is not referenced.   

    LDU     (input) INTEGER   
            The leading dimension of the array U.  LDU >= 1; if   
            JOBU = 'S' or 'A', LDU >= M.   

    VT      (output) COMPLEX*16 array, dimension (LDVT,N)   
            If JOBVT = 'A', VT contains the N-by-N unitary matrix   
            V**H;   
            if JOBVT = 'S', VT contains the first min(m,n) rows of   
            V**H (the right singular vectors, stored rowwise);   
            if JOBVT = 'N' or 'O', VT is not referenced.   

    LDVT    (input) INTEGER   
            The leading dimension of the array VT.  LDVT >= 1; if   
            JOBVT = 'A', LDVT >= N; if JOBVT = 'S', LDVT >= min(M,N).   

    WORK    (workspace/output) COMPLEX*16 array, dimension (MAX(1,LWORK))   
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.   
            LWORK >=  MAX(1,2*MIN(M,N)+MAX(M,N)).   
            For good performance, LWORK should generally be larger.   

            If LWORK = -1, then a workspace query is assumed; the routine   
            only calculates the optimal size of the WORK array, returns   
            this value as the first entry of the WORK array, and no error   
            message related to LWORK is issued by XERBLA.   

    RWORK   (workspace) DOUBLE PRECISION array, dimension (5*min(M,N))   
            On exit, if INFO > 0, RWORK(1:MIN(M,N)-1) contains the   
            unconverged superdiagonal elements of an upper bidiagonal   
            matrix B whose diagonal is in S (not necessarily sorted).   
            B satisfies A = U * B * VT, so it has the same singular   
            values as A, and singular vectors related by U and VT.   

    INFO    (output) INTEGER   
            = 0:  successful exit.   
            < 0:  if INFO = -i, the i-th argument had an illegal value.   
            > 0:  if ZBDSQR did not converge, INFO specifies how many   
                  superdiagonals of an intermediate bidiagonal form B   
                  did not converge to zero. See the description of RWORK   
                  above for details.   

    =====================================================================   


       Test the input arguments   

       Parameter adjustments */
long k,MN,m,n;
doublereal *s;
doublecomplex *u;
doublecomplex *vt;
integer info;
integer lwork=-1;
doublecomplex *work;
doublereal	*rwork;
tmsMatrix *SigValOut;
doublecomplex OptWork;

int stat=0;
integer M = _tmcGetM(X);
integer N = _tmcGetN(X);// HSKOST_BUG
integer lda  =M;
integer ldu = M;
integer ldvt = N; // ?? BUG


doublecomplex *a = MYMALLOC(sizeof(doublecomplex)*lda*N);
rwork = (doublereal *)MYMALLOC(5*min(M,N) * sizeof(doublereal));



// checked that a has complex part !!!
MN=tmcNumElem(X);
if (_tmcHasIm(X))
	for (k=0;k< MN;k++)
	{
		a[k].r=X->m_rData[k];
		a[k].i=X->m_iData[k];
	}
else // never enters, only for the generity
	for (k=0;k< MN;k++)
	{
		a[k].r=X->m_rData[k];
		a[k].i=0;
	}
s = (doublereal *)MYMALLOC(min(M,N) * sizeof(doublereal));


 if (nout==3)
 {
	_tmcClearRegister(S);
	_tmcClearRegister(U);
	_tmcClearRegister(V);

 _tmcCreateMatrix(S,M,N,tmcREAL );
 	SigValOut=S;

 _tmcCreateMatrix(U,ldu,M,tmcCOMPLEX );
 _tmcCreateMatrix(V,N,N,tmcCOMPLEX );

 u = (doublecomplex *)MYMALLOC(ldu*M * sizeof(doublecomplex));
 vt = (doublecomplex *)MYMALLOC(N*N* sizeof(doublecomplex));

	//LWORK >= MAX(1,3*MIN(M,N)+MAX(M,N),5*MIN(M,N))
    //lwork = max(max(1,3*min(M,N)+max(M,N)),5*min(M,N));
	//work = (doublereal*)MYMALLOC(lwork*sizeof(doublereal));

	stat= zgesvd_("A", "A", &M, &N,a, &lda, s, u,&ldu, vt, &ldvt, &OptWork, &lwork,rwork,&info);

	 lwork = (integer)OptWork.r;
	 work = MYMALLOC(max(1,lwork)*sizeof(doublecomplex));
	
	
	stat= zgesvd_("A", "A", &M, &N,a, &lda, s, u,&ldu, vt, &ldvt, work, &lwork,rwork,&info);
    
	for (k=0;k<ldu*M;k++)
	{
			U->m_rData[k]=u[k].r;
			U->m_iData[k]=u[k].i;
	}
	for (m=0;m<N;m++)
		for (n=0;n<N;n++) // V = vt' (complex)
		{
				V->m_rData[m+N*n]=vt[n+N*m].r;
				V->m_iData[m+N*n]=-vt[n+N*m].i;
		}
	MYFREE(work);
	MYFREE(vt);
	MYFREE(u);

	 for (k=0;k<min(M,N);k++)
	 {
			SigValOut->m_rData[k*M+k]=s[k];
	 }


 }
 if (nout==1)
 {
	 // S = SVD(X) returns a vector containing the singular values.
	 _tmcClearRegister(U);
     _tmcCreateMatrix(U,min(M,N),1,tmcREAL );
	 SigValOut=U;
	 u =0;// (doublereal *)MYMALLOC(ldu * M * sizeof(doublereal));
	 vt =0;// (doublereal *)MYMALLOC(N * N * sizeof(doublereal));
	//LWORK >= MAX(1,3*MIN(M,N)+MAX(M,N),5*MIN(M,N))
    //lwork = max(max(1,3*min(M,N)+max(M,N)),5*min(M,N));
	//work = (doublereal*)MYMALLOC(lwork*sizeof(doublereal));


	 stat= zgesvd_("N", "N", &M, &N,a, &lda, s, u,&ldu, vt, &ldvt, &OptWork, &lwork,rwork,&info);

	 lwork = (integer)OptWork.r;
	 work = MYMALLOC(max(1,lwork)*sizeof(doublecomplex));


	 stat= zgesvd_("N", "N", &M, &N,a, &lda, s, u,&ldu, vt, &ldvt, work, &lwork,rwork,&info);
	 for (k=0;k<min(M,N);k++)
	 {
			SigValOut->m_rData[k]=s[k];
	 }
 	 MYFREE(work);
}
 MYFREE(s);
 MYFREE(rwork);
 MYFREE(a);

}

void tmcsvd(long nout,long ninput,tmsMatrix *U,tmsMatrix *S,tmsMatrix *V,tmsMatrix *X,tmsMatrix *flag)
{// must implement for COMPLEX*16 case. (zgesvd)
/*
*  Purpose
*  =======
*
*  DGESVD computes the singular value decomposition (SVD) of a real
*  M-by-N matrix A, optionally computing the left and/or right singular
*  vectors. The SVD is written
*
*       A = U * SIGMA * transpose(V)
*
*  where SIGMA is an M-by-N matrix which is zero except for its
*  min(m,n) diagonal elements, U is an M-by-M orthogonal matrix, and
*  V is an N-by-N orthogonal matrix.  The diagonal elements of SIGMA
*  are the singular values of A; they are real and non-negative, and
*  are returned in descending order.  The first min(m,n) columns of
*  U and V are the left and right singular vectors of A.
*
*  Note that the routine returns V**T, not V.
*
*  Arguments
*  =========
*
*  JOBU    (input) CHARACTER*1
*          Specifies options for computing all or part of the matrix U:
*          = 'A':  all M columns of U are returned in array U:
*          = 'S':  the first min(m,n) columns of U (the left singular
*                  vectors) are returned in the array U;
*          = 'O':  the first min(m,n) columns of U (the left singular
*                  vectors) are overwritten on the array A;
*          = 'N':  no columns of U (no left singular vectors) are
*                  computed.
*
*  JOBVT   (input) CHARACTER*1
*          Specifies options for computing all or part of the matrix
*          V**T:
*          = 'A':  all N rows of V**T are returned in the array VT;
*          = 'S':  the first min(m,n) rows of V**T (the right singular
*                  vectors) are returned in the array VT;
*          = 'O':  the first min(m,n) rows of V**T (the right singular
*                  vectors) are overwritten on the array A;
*          = 'N':  no rows of V**T (no right singular vectors) are
*                  computed.
*
*          JOBVT and JOBU cannot both be 'O'.
*
*  M       (input) INTEGER
*          The number of rows of the input matrix A.  M >= 0.
*
*  N       (input) INTEGER
*          The number of columns of the input matrix A.  N >= 0.
*
*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
*          On entry, the M-by-N matrix A.
*          On exit,
*          if JOBU = 'O',  A is overwritten with the first min(m,n)
*                          columns of U (the left singular vectors,
*                          stored columnwise);
*          if JOBVT = 'O', A is overwritten with the first min(m,n)
*                          rows of V**T (the right singular vectors,
*                          stored rowwise);
*          if JOBU .ne. 'O' and JOBVT .ne. 'O', the contents of A
*                          are destroyed.
*
*  LDA     (input) INTEGER
*          The leading dimension of the array A.  LDA >= max(1,M).
*
*  S       (output) DOUBLE PRECISION array, dimension (min(M,N))
*          The singular values of A, sorted so that S(i) >= S(i+1).
*
*  U       (output) DOUBLE PRECISION array, dimension (LDU,UCOL)
*          (LDU,M) if JOBU = 'A' or (LDU,min(M,N)) if JOBU = 'S'.
*          If JOBU = 'A', U contains the M-by-M orthogonal matrix U;
*          if JOBU = 'S', U contains the first min(m,n) columns of U
*          (the left singular vectors, stored columnwise);
*          if JOBU = 'N' or 'O', U is not referenced.
*
*  LDU     (input) INTEGER
*          The leading dimension of the array U.  LDU >= 1; if
*          JOBU = 'S' or 'A', LDU >= M.
*
*  VT      (output) DOUBLE PRECISION array, dimension (LDVT,N)
*          If JOBVT = 'A', VT contains the N-by-N orthogonal matrix
*          V**T;
*          if JOBVT = 'S', VT contains the first min(m,n) rows of
*          V**T (the right singular vectors, stored rowwise);
*          if JOBVT = 'N' or 'O', VT is not referenced.
*
*  LDVT    (input) INTEGER
*          The leading dimension of the array VT.  LDVT >= 1; if
*          JOBVT = 'A', LDVT >= N; if JOBVT = 'S', LDVT >= min(M,N).
*
*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK))
*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK;
*          if INFO > 0, WORK(2:MIN(M,N)) contains the unconverged
*          superdiagonal elements of an upper bidiagonal matrix B
*          whose diagonal is in S (not necessarily sorted). B
*          satisfies A = U * B * VT, so it has the same singular values
*          as A, and singular vectors related by U and VT.
*
*  LWORK   (input) INTEGER
*          The dimension of the array WORK.
*          LWORK >= MAX(1,3*MIN(M,N)+MAX(M,N),5*MIN(M,N)).
*          For good performance, LWORK should generally be larger.
*
*          If LWORK = -1, then a workspace query is assumed; the routine
*          only calculates the optimal size of the WORK array, returns
*          this value as the first entry of the WORK array, and no error
*          message related to LWORK is issued by XERBLA.
*
*  INFO    (output) INTEGER
*          = 0:  successful exit.
*          < 0:  if INFO = -i, the i-th argument had an illegal value.
*          > 0:  if DBDSQR did not converge, INFO specifies how many
*                superdiagonals of an intermediate bidiagonal form B
*                did not converge to zero. See the description of WORK
*                above for details.
*
*  =====================================================================

*/
long k;
doublereal *s;
doublereal *u;
doublereal *vt;
integer info;
integer lwork=-1;
doublereal *work;
tmsMatrix *SigValOut;
doublereal OptWork;
doublereal *a;

int stat=0;
integer M;
integer N;
integer lda;
integer ldu ;
integer ldvt;

		if (_tmcHasIm(X))
		{
			_tmcsvd_z(nout,ninput,U,S,V,X,flag);
			return;
		}

M = _tmcGetM(X);
N = _tmcGetN(X);
lda  =M;ldu = M;ldvt = N;

a = MYMALLOC(sizeof(doublereal)*lda*N);
memcpy(a,X->m_rData,sizeof(doublereal)*lda*N);

s = (doublereal *)MYMALLOC(min(M,N) * sizeof(doublereal));


 if (nout==3)
 {
	_tmcClearRegister(S);
	_tmcClearRegister(U);
	_tmcClearRegister(V);

 _tmcCreateMatrix(S,M,N,_tmcHasIm(X) );
 	SigValOut=S;

 _tmcCreateMatrix(U,ldu,M,_tmcHasIm(X) );
 _tmcCreateMatrix(V,N,N,_tmcHasIm(X) );
	u = U->m_rData;
	vt = V->m_rData;
	//LWORK >= MAX(1,3*MIN(M,N)+MAX(M,N),5*MIN(M,N))
    //lwork = max(max(1,3*min(M,N)+max(M,N)),5*min(M,N));
	//work = (doublereal*)MYMALLOC(lwork*sizeof(doublereal));

	stat= dgesvd_("A", "A", &M, &N,a, &lda, s, u,&ldu, vt, &ldvt, &OptWork, &lwork,&info);

	 lwork = (integer)OptWork;
	 work = MYMALLOC(max(1,lwork)*sizeof(doublereal));
	
	
	stat= dgesvd_("A", "A", &M, &N,a, &lda, s, u,&ldu, vt, &ldvt, work, &lwork,&info);
    _tmcTransposeMatrix(V,0);

	 for (k=0;k<min(M,N);k++)
	 {
			SigValOut->m_rData[k*M+k]=s[k];
	 }

 }
 if (nout==1)
 {
	 // S = SVD(X) returns a vector containing the singular values.
	_tmcClearRegister(U);
     _tmcCreateMatrix(U,min(M,N),1,_tmcHasIm(X) );
	 SigValOut=U;
	 u =0;// (doublereal *)MYMALLOC(ldu * M * sizeof(doublereal));
	 vt =0;// (doublereal *)MYMALLOC(N * N * sizeof(doublereal));
	//LWORK >= MAX(1,3*MIN(M,N)+MAX(M,N),5*MIN(M,N))
    //lwork = max(max(1,3*min(M,N)+max(M,N)),5*min(M,N));
	//work = (doublereal*)MYMALLOC(lwork*sizeof(doublereal));


	 stat= dgesvd_("N", "N", &M, &N,a, &lda, s, u,&ldu, vt, &ldvt, &OptWork, &lwork,&info);

	 lwork = (integer)OptWork;
	 work = MYMALLOC(max(1,lwork)*sizeof(doublereal));


	 stat= dgesvd_("N", "N", &M, &N,a, &lda, s, u,&ldu, vt, &ldvt, work, &lwork,&info);
	 for (k=0;k<min(M,N);k++)
	 {
			SigValOut->m_rData[k]=s[k];
	 }
 }
 MYFREE(s);
 MYFREE(a);
 MYFREE(work);
}

void _tmcRealLeftDiv(tmsMatrix *X,tmsMatrix *A,tmsMatrix *B)
{

/*
*  DGELS solves overdetermined or underdetermined real linear systems
*  involving an M-by-N matrix A, or its transpose, using a QR or LQ
*  factorization of A.  It is assumed that A has full rank.
*
*  The following options are provided:
*
*  1. If TRANS = 'N' and m >= n:  find the least squares solution of
*     an overdetermined system, i.e., solve the least squares problem
*                  minimize || B - A*X ||.
*
*  2. If TRANS = 'N' and m < n:  find the minimum norm solution of
*     an underdetermined system A * X = B.
*
*  3. If TRANS = 'T' and m >= n:  find the minimum norm solution of
*     an undetermined system A**T * X = B.
*
*  4. If TRANS = 'T' and m < n:  find the least squares solution of
*     an overdetermined system, i.e., solve the least squares problem
*                  minimize || B - A**T * X ||.
*
*  Several right hand side vectors b and solution vectors x can be
*  handled in a single call; they are stored as the columns of the
*  M-by-NRHS right hand side matrix B and the N-by-NRHS solution
*  matrix X.
*
*  Arguments
*  =========
*
*  TRANS   (input) CHARACTER*1
*          = 'N': the linear system involves A;
*          = 'T': the linear system involves A**T.
*
*  M       (input) INTEGER
*          The number of rows of the matrix A.  M >= 0.
*
*  N       (input) INTEGER
*          The number of columns of the matrix A.  N >= 0.
*
*  NRHS    (input) INTEGER
*          The number of right hand sides, i.e., the number of
*          columns of the matrices B and X. NRHS >=0.
*
*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
*          On entry, the M-by-N matrix A.
*          On exit,
*            if M >= N, A is overwritten by details of its QR
*                       factorization as returned by DGEQRF;
*            if M <  N, A is overwritten by details of its LQ
*                       factorization as returned by DGELQF.
*
*  LDA     (input) INTEGER
*          The leading dimension of the array A.  LDA >= max(1,M).
*
*  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS)
*          On entry, the matrix B of right hand side vectors, stored
*          columnwise; B is M-by-NRHS if TRANS = 'N', or N-by-NRHS
*          if TRANS = 'T'.
*          On exit, if INFO = 0, B is overwritten by the solution
*          vectors, stored columnwise:
*          if TRANS = 'N' and m >= n, rows 1 to n of B contain the least
*          squares solution vectors; the residual sum of squares for the
*          solution in each column is given by the sum of squares of
*          elements N+1 to M in that column;
*          if TRANS = 'N' and m < n, rows 1 to N of B contain the
*          minimum norm solution vectors;
*          if TRANS = 'T' and m >= n, rows 1 to M of B contain the
*          minimum norm solution vectors;
*          if TRANS = 'T' and m < n, rows 1 to M of B contain the
*          least squares solution vectors; the residual sum of squares
*          for the solution in each column is given by the sum of
*          squares of elements M+1 to N in that column.
*
*  LDB     (input) INTEGER
*          The leading dimension of the array B. LDB >= MAX(1,M,N).
*
*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK))
*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
*
*  LWORK   (input) INTEGER
*          The dimension of the array WORK.
*          LWORK >= max( 1, MN + max( MN, NRHS ) ).
*          For optimal performance,
*          LWORK >= max( 1, MN + max( MN, NRHS )*NB ).
*          where MN = min(M,N) and NB is the optimum block size.
*
*          If LWORK = -1, then a workspace query is assumed; the routine
*          only calculates the optimal size of the WORK array, returns
*          this value as the first entry of the WORK array, and no error
*          message related to LWORK is issued by XERBLA.
*
*  INFO    (output) INTEGER
*          = 0:  successful exit
*          < 0:  if INFO = -i, the i-th argument had an illegal value
*          > 0:  if INFO =  i, the i-th diagonal element of the
*                triangular factor of A is zero, so that A does not have
*                full rank; the least squares solution could not be
*                computed.

*/
long m,n;
integer stat;
doublereal OptWork;
doublereal *work;
integer info;
integer lwork=-1;

integer M=_tmcGetM(A);
integer N=_tmcGetN(A);
integer nrhs = _tmcGetN(B);
integer lda = M;
integer ldb = _tmcGetM(B);

doublereal *a = (doublereal *)MYMALLOC(sizeof(doublereal)*lda*N);
doublereal *b = (doublereal *)MYMALLOC(sizeof(doublereal)*ldb*nrhs);


memcpy(a,A->m_rData,sizeof(doublereal)*lda*N);
memcpy(b,B->m_rData,sizeof(doublereal)*ldb*nrhs);

stat = dgels_("N",&M, &N, &nrhs, a, &lda, b, &ldb, 
	&OptWork, &lwork, &info);

	lwork = (integer)OptWork;
	work = MYMALLOC(max(1,lwork)*sizeof(doublereal));

stat = dgels_("N",&M, &N, &nrhs, a, &lda, b, &ldb, 
	work, &lwork, &info);


     _tmcCreateMatrix(X,N,nrhs,(short)(_tmcHasIm(A) | _tmcHasIm(B)));
	 for (m=0;m<N;m++)
		 for (n=0;n<nrhs;n++)
			 X->m_rData[n*N+m]=b[ldb*n+m];

	MYFREE(a);
	MYFREE(b);
	MYFREE(work);
}

void _tmcComplexLeftDiv(tmsMatrix *X,tmsMatrix *A,tmsMatrix *B)
{

/*
*  ZGELS solves overdetermined or underdetermined complex linear systems
*  involving an M-by-N matrix A, or its conjugate-transpose, using a QR
*  or LQ factorization of A.  It is assumed that A has full rank.
*
*  The following options are provided:
*
*  1. If TRANS = 'N' and m >= n:  find the least squares solution of
*     an overdetermined system, i.e., solve the least squares problem
*                  minimize || B - A*X ||.
*
*  2. If TRANS = 'N' and m < n:  find the minimum norm solution of
*     an underdetermined system A * X = B.
*
*  3. If TRANS = 'C' and m >= n:  find the minimum norm solution of
*     an undetermined system A**H * X = B.
*
*  4. If TRANS = 'C' and m < n:  find the least squares solution of
*     an overdetermined system, i.e., solve the least squares problem
*                  minimize || B - A**H * X ||.
*
*  Several right hand side vectors b and solution vectors x can be
*  handled in a single call; they are stored as the columns of the
*  M-by-NRHS right hand side matrix B and the N-by-NRHS solution
*  matrix X.
*
*  Arguments
*  =========
*
*  TRANS   (input) CHARACTER*1
*          = 'N': the linear system involves A;
*          = 'C': the linear system involves A**H.
*
*  M       (input) INTEGER
*          The number of rows of the matrix A.  M >= 0.
*
*  N       (input) INTEGER
*          The number of columns of the matrix A.  N >= 0.
*
*  NRHS    (input) INTEGER
*          The number of right hand sides, i.e., the number of
*          columns of the matrices B and X. NRHS >= 0.
*
*  A       (input/output) COMPLEX*16 array, dimension (LDA,N)
*          On entry, the M-by-N matrix A.
*            if M >= N, A is overwritten by details of its QR
*                       factorization as returned by ZGEQRF;
*            if M <  N, A is overwritten by details of its LQ
*                       factorization as returned by ZGELQF.
*
*  LDA     (input) INTEGER
*          The leading dimension of the array A.  LDA >= max(1,M).
*
*  B       (input/output) COMPLEX*16 array, dimension (LDB,NRHS)
*          On entry, the matrix B of right hand side vectors, stored
*          columnwise; B is M-by-NRHS if TRANS = 'N', or N-by-NRHS
*          if TRANS = 'C'.
*          On exit, if INFO = 0, B is overwritten by the solution
*          vectors, stored columnwise:
*          if TRANS = 'N' and m >= n, rows 1 to n of B contain the least
*          squares solution vectors; the residual sum of squares for the
*          solution in each column is given by the sum of squares of the
*          modulus of elements N+1 to M in that column;
*          if TRANS = 'N' and m < n, rows 1 to N of B contain the
*          minimum norm solution vectors;
*          if TRANS = 'C' and m >= n, rows 1 to M of B contain the
*          minimum norm solution vectors;
*          if TRANS = 'C' and m < n, rows 1 to M of B contain the
*          least squares solution vectors; the residual sum of squares
*          for the solution in each column is given by the sum of
*          squares of the modulus of elements M+1 to N in that column.
*
*  LDB     (input) INTEGER
*          The leading dimension of the array B. LDB >= MAX(1,M,N).
*
*  WORK    (workspace/output) COMPLEX*16 array, dimension (MAX(1,LWORK))
*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
*
*  LWORK   (input) INTEGER
*          The dimension of the array WORK.
*          LWORK >= max( 1, MN + max( MN, NRHS ) ).
*          For optimal performance,
*          LWORK >= max( 1, MN + max( MN, NRHS )*NB ).
*          where MN = min(M,N) and NB is the optimum block size.
*
*          If LWORK = -1, then a workspace query is assumed; the routine
*          only calculates the optimal size of the WORK array, returns
*          this value as the first entry of the WORK array, and no error
*          message related to LWORK is issued by XERBLA.
*
*  INFO    (output) INTEGER
*          = 0:  successful exit
*          < 0:  if INFO = -i, the i-th argument had an illegal value
*          > 0:  if INFO =  i, the i-th diagonal element of the
*                triangular factor of A is zero, so that A does not have
*                full rank; the least squares solution could not be
*                computed.
*/
long m,n;
long k;
integer stat;
doublecomplex OptWork;
doublecomplex *work;
integer info;
integer lwork=-1;

integer M=_tmcGetM(A);
integer N=_tmcGetN(A);
integer nrhs = _tmcGetN(B);
integer lda = M;
integer ldb = _tmcGetM(B);

doublecomplex *a = (doublecomplex *)MYMALLOC(sizeof(doublecomplex)*lda*N);
doublecomplex *b = (doublecomplex *)MYMALLOC(sizeof(doublecomplex)*ldb*nrhs);

for (k=0;k<lda*N;k++)
{
	a[k].r=A->m_rData[k];
}

if (_tmcHasIm(A))
{
	for (k=0;k<lda*N;k++)
	{
		a[k].i=A->m_iData[k];
	}
}
else
{
	for (k=0;k<lda*N;k++)
	{
		a[k].i=0;
	}
}
////
for (k=0;k<ldb*nrhs;k++)
{
	b[k].r=B->m_rData[k];
}
if (_tmcHasIm(B))
{
	for (k=0;k<ldb*nrhs;k++)
	{
		b[k].i=B->m_iData[k];
	}
}
else
{
	for (k=0;k<ldb*nrhs;k++)
	{
		b[k].i=0;
	}
}

//memcpy(a,A->m_rData,sizeof(doublereal)*lda*N);
//memcpy(b,B->m_rData,sizeof(doublereal)*ldb*nrhs);

stat = zgels_("N",&M, &N, &nrhs, a, &lda, b, &ldb, 
	&OptWork, &lwork, &info);

	lwork = (integer)OptWork.r;
	work = MYMALLOC(max(1,lwork)*sizeof(doublecomplex));

stat = zgels_("N",&M, &N, &nrhs, a, &lda, b, &ldb, 
	work, &lwork, &info);


     _tmcCreateMatrix(X,N,nrhs,(short)(_tmcHasIm(A) | _tmcHasIm(B)));
	 for (m=0;m<N;m++)
		 for (n=0;n<nrhs;n++)
		 {
			 X->m_rData[n*N+m]=b[ldb*n+m].r;
			 X->m_iData[n*N+m]=b[ldb*n+m].i;
		 }
	MYFREE(a);
	MYFREE(b);
	MYFREE(work);
}

void _tmceig_r(long nout,long ninput,tmsMatrix *out1,tmsMatrix *out2,tmsMatrix *in1,tmsMatrix *in2,tmsMatrix *in3)
/*
    DGEEVX computes for an N-by-N real nonsymmetric matrix A, the   
    eigenvalues and, optionally, the left and/or right eigenvectors.   

    Optionally also, it computes a balancing transformation to improve   
    the conditioning of the eigenvalues and eigenvectors (ILO, IHI,   
    SCALE, and ABNRM), reciprocal condition numbers for the eigenvalues   
    (RCONDE), and reciprocal condition numbers for the right   
    eigenvectors (RCONDV).   

    The right eigenvector v(j) of A satisfies   
                     A * v(j) = lambda(j) * v(j)   
    where lambda(j) is its eigenvalue.   
    The left eigenvector u(j) of A satisfies   
                  u(j)**H * A = lambda(j) * u(j)**H   
    where u(j)**H denotes the conjugate transpose of u(j).   

    The computed eigenvectors are normalized to have Euclidean norm   
    equal to 1 and largest component real.   

    Balancing a matrix means permuting the rows and columns to make it   
    more nearly upper triangular, and applying a diagonal similarity   
    transformation D * A * D**(-1), where D is a diagonal matrix, to   
    make its rows and columns closer in norm and the condition numbers   
    of its eigenvalues and eigenvectors smaller.  The computed   
    reciprocal condition numbers correspond to the balanced matrix.   
    Permuting rows and columns will not change the condition numbers   
    (in exact arithmetic) but diagonal scaling will.  For further   
    explanation of balancing, see section 4.10.2 of the LAPACK   
    Users' Guide.   

    Arguments   
    =========   

    BALANC  (input) CHARACTER*1   
            Indicates how the input matrix should be diagonally scaled   
            and/or permuted to improve the conditioning of its   
            eigenvalues.   
            = 'N': Do not diagonally scale or permute;   
            = 'P': Perform permutations to make the matrix more nearly   
                   upper triangular. Do not diagonally scale;   
            = 'S': Diagonally scale the matrix, i.e. replace A by   
                   D*A*D**(-1), where D is a diagonal matrix chosen   
                   to make the rows and columns of A more equal in   
                   norm. Do not permute;   
            = 'B': Both diagonally scale and permute A.   

            Computed reciprocal condition numbers will be for the matrix   
            after balancing and/or permuting. Permuting does not change   
            condition numbers (in exact arithmetic), but balancing does.   

    JOBVL   (input) CHARACTER*1   
            = 'N': left eigenvectors of A are not computed;   
            = 'V': left eigenvectors of A are computed.   
            If SENSE = 'E' or 'B', JOBVL must = 'V'.   

    JOBVR   (input) CHARACTER*1   
            = 'N': right eigenvectors of A are not computed;   
            = 'V': right eigenvectors of A are computed.   
            If SENSE = 'E' or 'B', JOBVR must = 'V'.   

    SENSE   (input) CHARACTER*1   
            Determines which reciprocal condition numbers are computed.   
            = 'N': None are computed;   
            = 'E': Computed for eigenvalues only;   
            = 'V': Computed for right eigenvectors only;   
            = 'B': Computed for eigenvalues and right eigenvectors.   

            If SENSE = 'E' or 'B', both left and right eigenvectors   
            must also be computed (JOBVL = 'V' and JOBVR = 'V').   

    N       (input) INTEGER   
            The order of the matrix A. N >= 0.   

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)   
            On entry, the N-by-N matrix A.   
            On exit, A has been overwritten.  If JOBVL = 'V' or   
            JOBVR = 'V', A contains the real Schur form of the balanced   
            version of the input matrix A.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,N).   

    WR      (output) DOUBLE PRECISION array, dimension (N)   
    WI      (output) DOUBLE PRECISION array, dimension (N)   
            WR and WI contain the real and imaginary parts,   
            respectively, of the computed eigenvalues.  Complex   
            conjugate pairs of eigenvalues will appear consecutively   
            with the eigenvalue having the positive imaginary part   
            first.   

    VL      (output) DOUBLE PRECISION array, dimension (LDVL,N)   
            If JOBVL = 'V', the left eigenvectors u(j) are stored one   
            after another in the columns of VL, in the same order   
            as their eigenvalues.   
            If JOBVL = 'N', VL is not referenced.   
            If the j-th eigenvalue is real, then u(j) = VL(:,j),   
            the j-th column of VL.   
            If the j-th and (j+1)-st eigenvalues form a complex   
            conjugate pair, then u(j) = VL(:,j) + i*VL(:,j+1) and   
            u(j+1) = VL(:,j) - i*VL(:,j+1).   

    LDVL    (input) INTEGER   
            The leading dimension of the array VL.  LDVL >= 1; if   
            JOBVL = 'V', LDVL >= N.   

    VR      (output) DOUBLE PRECISION array, dimension (LDVR,N)   
            If JOBVR = 'V', the right eigenvectors v(j) are stored one   
            after another in the columns of VR, in the same order   
            as their eigenvalues.   
            If JOBVR = 'N', VR is not referenced.   
            If the j-th eigenvalue is real, then v(j) = VR(:,j),   
            the j-th column of VR.   
            If the j-th and (j+1)-st eigenvalues form a complex   
            conjugate pair, then v(j) = VR(:,j) + i*VR(:,j+1) and   
            v(j+1) = VR(:,j) - i*VR(:,j+1).   

    LDVR    (input) INTEGER   
            The leading dimension of the array VR.  LDVR >= 1, and if   
            JOBVR = 'V', LDVR >= N.   

    ILO     (output) INTEGER   
    IHI     (output) INTEGER   
            ILO and IHI are integer values determined when A was   
            balanced.  The balanced A(i,j) = 0 if I > J and   
            J = 1,...,ILO-1 or I = IHI+1,...,N.   

    SCALE   (output) DOUBLE PRECISION array, dimension (N)   
            Details of the permutations and scaling factors applied   
            when balancing A.  If P(j) is the index of the row and column   
            interchanged with row and column j, and D(j) is the scaling   
            factor applied to row and column j, then   
            SCALE(J) = P(J),    for J = 1,...,ILO-1   
                     = D(J),    for J = ILO,...,IHI   
                     = P(J)     for J = IHI+1,...,N.   
            The order in which the interchanges are made is N to IHI+1,   
            then 1 to ILO-1.   

    ABNRM   (output) DOUBLE PRECISION   
            The one-norm of the balanced matrix (the maximum   
            of the sum of absolute values of elements of any column).   

    RCONDE  (output) DOUBLE PRECISION array, dimension (N)   
            RCONDE(j) is the reciprocal condition number of the j-th   
            eigenvalue.   

    RCONDV  (output) DOUBLE PRECISION array, dimension (N)   
            RCONDV(j) is the reciprocal condition number of the j-th   
            right eigenvector.   

    WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK))   
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.   If SENSE = 'N' or 'E',   
            LWORK >= max(1,2*N), and if JOBVL = 'V' or JOBVR = 'V',   
            LWORK >= 3*N.  If SENSE = 'V' or 'B', LWORK >= N*(N+6).   
            For good performance, LWORK must generally be larger.   

            If LWORK = -1, then a workspace query is assumed; the routine   
            only calculates the optimal size of the WORK array, returns   
            this value as the first entry of the WORK array, and no error   
            message related to LWORK is issued by XERBLA.   

    IWORK   (workspace) INTEGER array, dimension (2*N-2)   
            If SENSE = 'N' or 'E', not referenced.   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value.   
            > 0:  if INFO = i, the QR algorithm failed to compute all the   
                  eigenvalues, and no eigenvectors or condition numbers   
                  have been computed; elements 1:ILO-1 and i+1:N of WR   
                  and WI contain eigenvalues which have converged.   
*/
{
integer ilo;
integer ihi;
doublereal abnrm;
integer lwork;
integer info;

doublereal OptWork;
doublereal *work;

long MN;
long k;
char *pBalance[2] = {"N","B"};
char indB;
int stat;
integer n;
doublereal *a;
integer lda;
doublereal *wr,*wi;
doublereal *vl;
doublereal *vr;
integer ldvl;
integer ldvr;
doublereal *scale;
doublereal *rconde;
doublereal *rcondv;
integer *iwork;
tmsMatrix *A;
////////

n = _tmcGetM(in1);
a = (doublereal *)MYMALLOC(sizeof(doublereal)*n*n);
lda = n;
wr = (doublereal *)MYMALLOC(sizeof(doublereal)*n);
wi = (doublereal *)MYMALLOC(sizeof(doublereal)*n);

vl = NULL;
vr = NULL;
ldvl =1;
ldvr =1;
scale=(doublereal *)MYMALLOC(sizeof(doublereal)*n);
rconde=(doublereal *)MYMALLOC(sizeof(doublereal)*n);
rcondv=(doublereal *)MYMALLOC(sizeof(doublereal)*n);
iwork=(integer *)MYMALLOC(sizeof(integer)*(2*n-2));
A = in1;

////////
// must be _tmcHasIm(A)==0
	if (ninput==1)
		indB=0;
	else
		indB=1;

MN = _tmcGetM(A)*_tmcGetN(A);

for (k=0;k<MN;k++)
{
	a[k]=A->m_rData[k];
}

lwork=-1;


stat= dgeevx_(pBalance[indB], "N", "N", "N", &n, a, &lda, wr, wi,
	vl, &ldvl, vr, &ldvr, 
	&ilo, &ihi, scale, &abnrm, 
	rconde, rcondv, &OptWork,	
	&lwork,iwork, &info);

	lwork = (integer)OptWork;
	work = MYMALLOC(max(1,lwork)*sizeof(doublereal));

stat= dgeevx_(pBalance[indB], "N", "N", "N", &n, a, &lda, wr,wi,
	vl, &ldvl, vr, &ldvr, 
	&ilo, &ihi, scale, &abnrm, 
	rconde, rcondv, work,	
	&lwork,iwork, &info);


	_tmcClearRegister(out1);
    _tmcCreateMatrix(out1,n,1,tmcCOMPLEX);
	for (k=0;k<n;k++)
	{
		out1->m_rData[k] =  wr[k];
		out1->m_iData[k] =  wi[k];
	}


	MYFREE(work);
	MYFREE(iwork);
	MYFREE(rcondv);
	MYFREE(rconde);
	MYFREE(scale);
	MYFREE(wi);
	MYFREE(wr);
	MYFREE(a);


}

void tmceig(long nout,long ninput,tmsMatrix *out1,tmsMatrix *out2,tmsMatrix *in1,tmsMatrix *in2,tmsMatrix *in3)
{
/*
*  ZGEEVX computes for an N-by-N complex nonsymmetric matrix A, the
*  eigenvalues and, optionally, the left and/or right eigenvectors.
*
*  Optionally also, it computes a balancing transformation to improve
*  the conditioning of the eigenvalues and eigenvectors (ILO, IHI,
*  SCALE, and ABNRM), reciprocal condition numbers for the eigenvalues
*  (RCONDE), and reciprocal condition numbers for the right
*  eigenvectors (RCONDV).
*
*  The right eigenvector v(j) of A satisfies
*                   A * v(j) = lambda(j) * v(j)
*  where lambda(j) is its eigenvalue.
*  The left eigenvector u(j) of A satisfies
*                u(j)**H * A = lambda(j) * u(j)**H
*  where u(j)**H denotes the conjugate transpose of u(j).
*
*  The computed eigenvectors are normalized to have Euclidean norm
*  equal to 1 and largest component real.
*
*  Balancing a matrix means permuting the rows and columns to make it
*  more nearly upper triangular, and applying a diagonal similarity
*  transformation D * A * D**(-1), where D is a diagonal matrix, to
*  make its rows and columns closer in norm and the condition numbers
*  of its eigenvalues and eigenvectors smaller.  The computed
*  reciprocal condition numbers correspond to the balanced matrix.
*  Permuting rows and columns will not change the condition numbers
*  (in exact arithmetic) but diagonal scaling will.  For further
*  explanation of balancing, see section 4.10.2 of the LAPACK
*  Users' Guide.
*
*  Arguments
*  =========
*
*  BALANC  (input) CHARACTER*1
*          Indicates how the input matrix should be diagonally scaled
*          and/or permuted to improve the conditioning of its
*          eigenvalues.
*          = 'N': Do not diagonally scale or permute;
*          = 'P': Perform permutations to make the matrix more nearly
*                 upper triangular. Do not diagonally scale;
*          = 'S': Diagonally scale the matrix, ie. replace A by
*                 D*A*D**(-1), where D is a diagonal matrix chosen
*                 to make the rows and columns of A more equal in
*                 norm. Do not permute;
*          = 'B': Both diagonally scale and permute A.
*
*          Computed reciprocal condition numbers will be for the matrix
*          after balancing and/or permuting. Permuting does not change
*          condition numbers (in exact arithmetic), but balancing does.
*
*  JOBVL   (input) CHARACTER*1
*          = 'N': left eigenvectors of A are not computed;
*          = 'V': left eigenvectors of A are computed.
*          If SENSE = 'E' or 'B', JOBVL must = 'V'.
*
*  JOBVR   (input) CHARACTER*1
*          = 'N': right eigenvectors of A are not computed;
*          = 'V': right eigenvectors of A are computed.
*          If SENSE = 'E' or 'B', JOBVR must = 'V'.
*
*  SENSE   (input) CHARACTER*1
*          Determines which reciprocal condition numbers are computed.
*          = 'N': None are computed;
*          = 'E': Computed for eigenvalues only;
*          = 'V': Computed for right eigenvectors only;
*          = 'B': Computed for eigenvalues and right eigenvectors.
*
*          If SENSE = 'E' or 'B', both left and right eigenvectors
*          must also be computed (JOBVL = 'V' and JOBVR = 'V').
*
*  N       (input) INTEGER
*          The order of the matrix A. N >= 0.
*
*  A       (input/output) COMPLEX*16 array, dimension (LDA,N)
*          On entry, the N-by-N matrix A.
*          On exit, A has been overwritten.  If JOBVL = 'V' or
*          JOBVR = 'V', A contains the Schur form of the balanced
*          version of the matrix A.
*
*  LDA     (input) INTEGER
*          The leading dimension of the array A.  LDA >= max(1,N).
*
*  W       (output) COMPLEX*16 array, dimension (N)
*          W contains the computed eigenvalues.
*
*  VL      (output) COMPLEX*16 array, dimension (LDVL,N)
*          If JOBVL = 'V', the left eigenvectors u(j) are stored one
*          after another in the columns of VL, in the same order
*          as their eigenvalues.
*          If JOBVL = 'N', VL is not referenced.
*          u(j) = VL(:,j), the j-th column of VL.
*
*  LDVL    (input) INTEGER
*          The leading dimension of the array VL.  LDVL >= 1; if
*          JOBVL = 'V', LDVL >= N.
*
*  VR      (output) COMPLEX*16 array, dimension (LDVR,N)
*          If JOBVR = 'V', the right eigenvectors v(j) are stored one
*          after another in the columns of VR, in the same order
*          as their eigenvalues.
*          If JOBVR = 'N', VR is not referenced.
*          v(j) = VR(:,j), the j-th column of VR.
*
*  LDVR    (input) INTEGER
*          The leading dimension of the array VR.  LDVR >= 1; if
*          JOBVR = 'V', LDVR >= N.
*
*  ILO     (output) INTEGER
*  IHI     (output) INTEGER
*          ILO and IHI are integer values determined when A was
*          balanced.  The balanced A(i,j) = 0 if I > J and
*          J = 1,...,ILO-1 or I = IHI+1,...,N.
*
*  SCALE   (output) DOUBLE PRECISION array, dimension (N)
*          Details of the permutations and scaling factors applied
*          when balancing A.  If P(j) is the index of the row and column
*          interchanged with row and column j, and D(j) is the scaling
*          factor applied to row and column j, then
*          SCALE(J) = P(J),    for J = 1,...,ILO-1
*                   = D(J),    for J = ILO,...,IHI
*                   = P(J)     for J = IHI+1,...,N.
*          The order in which the interchanges are made is N to IHI+1,
*          then 1 to ILO-1.
*
*  ABNRM   (output) DOUBLE PRECISION
*          The one-norm of the balanced matrix (the maximum
*          of the sum of absolute values of elements of any column).
*
*  RCONDE  (output) DOUBLE PRECISION array, dimension (N)
*          RCONDE(j) is the reciprocal condition number of the j-th
*          eigenvalue.
*
*  RCONDV  (output) DOUBLE PRECISION array, dimension (N)
*          RCONDV(j) is the reciprocal condition number of the j-th
*          right eigenvector.
*
*  WORK    (workspace/output) COMPLEX*16 array, dimension (MAX(1,LWORK))
*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
*
*  LWORK   (input) INTEGER
*          The dimension of the array WORK.  If SENSE = 'N' or 'E',
*          LWORK >= max(1,2*N), and if SENSE = 'V' or 'B',
*          LWORK >= N*N+2*N.
*          For good performance, LWORK must generally be larger.
*
*          If LWORK = -1, then a workspace query is assumed; the routine
*          only calculates the optimal size of the WORK array, returns
*          this value as the first entry of the WORK array, and no error
*          message related to LWORK is issued by XERBLA.
*
*  RWORK   (workspace) DOUBLE PRECISION array, dimension (2*N)
*
*  INFO    (output) INTEGER
*          = 0:  successful exit
*          < 0:  if INFO = -i, the i-th argument had an illegal value.
*          > 0:  if INFO = i, the QR algorithm failed to compute all the
*                eigenvalues, and no eigenvectors or condition numbers
*                have been computed; elements 1:ILO-1 and i+1:N of W
*                contain eigenvalues which have converged.


*/
integer ilo;
integer ihi;
doublereal abnrm;
integer lwork;
integer info;

doublecomplex OptWork;
doublecomplex *work;

long MN;
long k;
char *pBalance[2] = {"N","B"};
char indB;
int stat;
integer n;
doublecomplex *a;
integer lda;
doublecomplex *w;
doublecomplex *vl;
doublecomplex *vr;
integer ldvl;
integer ldvr;
doublereal *scale;
doublereal *rconde;
doublereal *rcondv;
doublereal *rwork;
tmsMatrix *A;
////////
	if (_tmcHasIm(in1)==0)
	{
		_tmceig_r(nout,ninput,out1,out2,in1,in2,in3);
		return;
	}

n = _tmcGetM(in1);
a = (doublecomplex *)MYMALLOC(sizeof(doublecomplex)*n*n);
lda = n;
w = (doublecomplex *)MYMALLOC(sizeof(doublecomplex)*n);
vl = NULL;
vr = NULL;
ldvl =1;
ldvr =1;
scale=(doublereal *)MYMALLOC(sizeof(doublereal)*n);
rconde=(doublereal *)MYMALLOC(sizeof(doublereal)*n);
rcondv=(doublereal *)MYMALLOC(sizeof(doublereal)*n);
rwork=(doublereal *)MYMALLOC(sizeof(doublereal)*n*2);
A = in1;

////////

	if (ninput==1)
		indB=0;
	else
		indB=1;

MN = _tmcGetM(A)*_tmcGetN(A);

for (k=0;k<MN;k++)
{
	a[k].r=A->m_rData[k];
}

if (_tmcHasIm(A))
{
	for (k=0;k<MN;k++)
	{
		a[k].i=A->m_iData[k];
	}
}
else
{
	for (k=0;k<MN;k++)
	{
		a[k].i=0;
	}
}


lwork=-1;
stat= zgeevx_(pBalance[indB], "N", "N", "N", &n, a, &lda, w, 
	vl, &ldvl, vr, &ldvr, 
	&ilo, &ihi, scale, &abnrm, 
	rconde, rcondv, &OptWork,	
	&lwork,rwork, &info);

	lwork = (integer)OptWork.r;
	work = MYMALLOC(max(1,lwork)*sizeof(doublecomplex));

stat= zgeevx_(pBalance[indB], "N", "N", "N", &n, a, &lda, w, 
	vl, &ldvl, vr, &ldvr, 
	&ilo, &ihi, scale, &abnrm, 
	rconde, rcondv, work,	
	&lwork,rwork, &info);

	_tmcClearRegister(out1);
    _tmcCreateMatrix(out1,n,1,1);
	for (k=0;k<n;k++)
	{
		out1->m_rData[k] =  w[k].r;
		out1->m_iData[k] =  w[k].i;
	}

	MYFREE(a);
	MYFREE(w);
	MYFREE(scale);
	MYFREE(rconde);
	MYFREE(rcondv);
	MYFREE(rwork);
	MYFREE(work);

}



void tmcfft(long nout,long ninput,tmsMatrix *out,tmsMatrix *in)
{
// HAZARD: only for one dimention
	long k;
	long MN = tmcNumElem(in);
	integer n= MN;
	doublereal *wsave = MYMALLOC(sizeof(doublereal)*(4*n+15)*2*2);
	doublereal *c = MYMALLOC(sizeof(doublereal)*n*2*2);

	memset(c,0,sizeof(doublereal)*n*2);
	memset(wsave,0,sizeof(doublereal)*(4*n+15)*2);
	for (k=0;k<MN;k++)
	{
		c[k*2]=in->m_rData[k];
	}

	if (_tmcHasIm(in))
	for (k=0;k<MN;k++)
	{
		c[k*2+1]=in->m_iData[k];
	}
	else
	for (k=0;k<MN;k++)
	{
		c[k*2+1]=0;
	}


	zffti_(&n, &wsave[0]);
	zfftf_(&n, &c[0], &wsave[0]);

	_tmcClearRegister(out);
    _tmcCreateMatrix(out,_tmcGetM(in),_tmcGetN(in),1);
	for (k=0;k<MN;k++)
	{
		out->m_rData[k] =  c[k*2];
		out->m_iData[k] =  c[k*2+1];
	}

	MYFREE(c);
	MYFREE(wsave);

}



void _tmcPolyVal(doublecomplex *y, doublecomplex *p,doublecomplex *x,integer N)
{// evaluate y = p(x), N=deg(p)

	short k;
	doublecomplex a;
	doublecomplex res;


	a.r = p[0].r;
	a.i = p[0].i;

	for (k=1;k<=N;k++)
	{ // a_k*x+a_(k-1)
		res.r = a.r*x->r-a.i*x->i + p[k].r;
		res.i = a.r*x->i+a.i*x->r + p[k].i;
		a.r=res.r;a.i=res.i;
	}

	y->r=a.r;y->i = a.i;
}





/*
void _tmcCompMul(doublecomplex *z,doublecomplex *x,doublecomplex *y)
{ // z = x*y, may be address z=:x
double re,im;

		// (a+ib)*(c+id) = =((a*c-b*d)+i(b*c+a*d))
		re = (x->r*y->r-x->i*y->i);
		im = (x->i*y->r+x->r*y->i);
		z->r = re;
		z->i = im;
}
void _tmcCompDiv(doublecomplex *q,doublecomplex *num,doublecomplex *den)
{ // q = num/den, may be address q=:num
double D;
double re,im;

		// (a+ib)/(c+id) = (a+ib)*(c-id)/(c^2+d^2)=((a*c+b*d)+i(b*c-a*d))*D
		RealReciprocal(&D,den->r*den->r+den->i*den->i);
		re = (num->r*den->r+num->i*den->i)*D;
		im = (num->i*den->r-num->r*den->i)*D;
		q->r = re;
		q->i = im;
}
void tmcroots0(long nout,long ninput,tmsMatrix *r,tmsMatrix *p)
{
	long k,m,n;
	double theta;
	doublecomplex y;
	doublecomplex an;
	tmsMatrix *A;
	long MN = tmcNumElem(p);
	integer N= MN-1;

	doublecomplex *w = MYMALLOC(sizeof(doublecomplex)*N);// w_j
	doublecomplex *pw = MYMALLOC(sizeof(doublecomplex)*N);// p(w_j)
	doublecomplex *a = MYMALLOC(sizeof(doublecomplex)*N*N);// A
	
	doublecomplex *P = MYMALLOC(sizeof(doublecomplex)*MN);// p_j


	memset(a,0,sizeof(doublecomplex)*N*N);
	for (k=0;k<MN;k++)
	{
		P[k].r = p->m_rData[k];
		if( _tmcHasIm(p))
		{
			P[k].i = p->m_iData[k];
		}
		else
			P[k].i =0;
	}

    _tmcCreateMatrix(A,N,N,1);


	an.r = P[0].r;
	an.i = P[0].i;

	for (k=0;k<N;k++)
	{
		theta = (double)k*2.0*PI/(double)N;
		w[k].r = cos(theta);
		w[k].i = sin(theta);
		a[k*N+k].r=w[k].r;
		a[k*N+k].i=w[k].i;// A1
		_tmcPolyVal(&y,P,&w[k],N);
		pw[k].r = y.r/N ;
		pw[k].i = y.i/N;
		_tmcCompDiv(&pw[k],&pw[k],&an); // pw  = (1/n/an)*A2, column
	}
	for (m=0;m<N;m++)
		for (n=0;n<N;n++)
		{
			a[n*N+m].r -=  pw[m].r*w[n].r -  pw[m].i*w[n].i;//A=A1-(1/n/an)*A2*w
			a[n*N+m].i -=  pw[m].i*w[n].r +  pw[m].r*w[n].i;
			A->m_rData[n*N+m]=a[n*N+m].r;
			A->m_iData[n*N+m]=a[n*N+m].i;
		}
//debug:	tmcDisplayMat(A);
	MYFREE(a);
	MYFREE(pw);
	MYFREE(w);


	tmceig(1,1,r,NULL,A,NULL,NULL);


//
n=length(p)-1;
an=p(1);
w=exp(j*2*pi/n*[0:1:n-1]);
A1=diag(w);
A2=zeros(n,1);
for cnt=1:n
    A2(cnt)=polyval(p,w(cnt));
end
A=A1-(1/n/an)*A2*w
r=eig(A,'nobalance')
//


}*/

void tmcroots(long nout,long ninput,tmsMatrix *r,tmsMatrix *p)
{
	long leadZN=0;
	long k,m,n;
	tmsMatrix *A;
	
	long MN = tmcNumElem(p);
	integer N= MN-1;

if (_tmcHasIm(p))
{
	doublecomplex c0;
	doublecomplex *a;

	c0.r = p->m_rData[0];
	c0.i = p->m_iData[0];
	k=1;
	while ( 0.0 ==c0.r && 0.0 ==c0.i && k<MN )
	{
		leadZN++;
		c0.r = p->m_rData[leadZN];
		c0.i = p->m_iData[leadZN];
	}
	MN -= leadZN;
	N  -= leadZN;
	if (MN<2)
	{
		// no solution
		tmcCreateMatrixEmpty(r);
		return;
	}


	a = MYMALLOC(sizeof(doublecomplex)*N*N);// A
	memset(a,0,sizeof(doublecomplex)*N*N);
	A=tmcNewMatrix();
    _tmcCreateMatrix(A,N,N,tmcCOMPLEX);

	for (k=0;k<N-1;k++)
	{
		a[k*N+k+1].r=1.;
		a[k*N+k+1].i=0.;
	}

	c0.r = 	-c0.r;
	c0.i = 	-c0.i;

	for (k=0;k<N;k++)
	{
		//	a[(N-1)*N+k].r= -p->m_rData[N-k];
		//	a[(N-1)*N+k].i= -p->m_iData[N-k];
			_Cdiv(&a[k*N].r,&a[k*N].i,p->m_rData[leadZN+k+1],p->m_iData[leadZN+k+1],c0.r,c0.i);
	}

	for (m=0;m<N;m++)
		for (n=0;n<N;n++)
		{
			A->m_rData[n*N+m]=a[n*N+m].r;
			A->m_iData[n*N+m]=a[n*N+m].i;
		}
    MYFREE(a);

}
else
{
//     -p(2)/p(1)  ...						-p(n)/p(1)
//     1     0     0     0     0     0     0
//     0     1     0     0     0     0     0
//     0     0     1     0     0     0     0
//     0     0     0     1     0     0     0
//     0     0     0     0     1     0     0
//     0     0     0     0     0     1     0

	double p0;
	doublereal *a;

	p0 = p->m_rData[0];
	k=1;
	while ( 0.0 ==p0  && k<MN )
	{
		leadZN++;
		p0 = p->m_rData[leadZN];
	}
	MN -= leadZN;
	N  -= leadZN;
	if (MN<2)
	{
		// no solution
		tmcCreateMatrixEmpty(r);
		return;
	}
	p0=-p0;

	a = MYMALLOC(sizeof(doublereal)*N*N);// A
	memset(a,0,sizeof(doublereal)*N*N);
	A=tmcNewMatrix();
    _tmcCreateMatrix(A,N,N,tmcREAL);
	
	for (k=0;k<N-1;k++)
	{
		a[k*N+k+1]=1;
	}

	for (k=0;k<N;k++)
	{
		//a[(N-1)*N+k]= -p->m_rData[N-k];
		a[  k * N ] = p->m_rData[leadZN+k+1] / p0;
	}
	for (m=0;m<N;m++)
		for (n=0;n<N;n++)
		{
			A->m_rData[n*N+m]=a[n*N+m];
		}
    MYFREE(a);
}
//	tmcDisplayMat(A);
//HAZARD_TODO: remove leading zeros and normalize by first coefficient!!!

	//tmceig(1,2,r,NULL,A,NULL,NULL);// was:tmceig(1,1,r,NULL,A,NULL,NULL) - not balance
	//tmceig(1,1,r,NULL,A,NULL,NULL);//  do not balance
		tmceig(1,2,r,NULL,A,NULL,NULL);//    balance
	tmcFreeLocalVar(A);

/*
n=length(p)-1;
an=p(1);
A =[ [zeros(1,n-1) ;   eye(n-1) ] , -fliplr(p(2:end)).'];
r=eig(A,'nobalance')
*/


}

 __inline doublecomplex  ZMULT_A_Bhat(doublecomplex a,doublecomplex b)
// return a*b'
{
	doublecomplex c;
	c.r = (a.r * b.r + a.i * b.i );
	c.i = (a.i * b.r - a.r * b.i );
	return c;
}
 __inline doublecomplex  ZMULT_A_B(doublecomplex a,doublecomplex b)
// return a*b
{
	doublecomplex c;
	c.r = (a.r * b.r - a.i * b.i );
	c.i = (a.i * b.r + a.r * b.i );
	return c;
}
void tmcqr(long nout,long ninput,tmsMatrix *Q,tmsMatrix *R,tmsMatrix *E,tmsMatrix *A,tmsMatrix *flg)
{
/*

      SUBROUTINE ZGEQRF( M, N, A, LDA, TAU, WORK, LWORK, INFO )
*
*  -- LAPACK routine (version 3.2) --
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*     November 2006
*
*     .. Scalar Arguments ..
      INTEGER            INFO, LDA, LWORK, M, N
*     ..
*     .. Array Arguments ..
      COMPLEX*16         A( LDA, * ), TAU( * ), WORK( * )
*     ..
*
*  Purpose
*  =======
*
*  ZGEQRF computes a QR factorization of a complex M-by-N matrix A:
*  A = Q * R.
*
*  Arguments
*  =========
*
*  M       (input) INTEGER
*          The number of rows of the matrix A.  M >= 0.
*
*  N       (input) INTEGER
*          The number of columns of the matrix A.  N >= 0.
*
*  A       (input/output) COMPLEX*16 array, dimension (LDA,N)
*          On entry, the M-by-N matrix A.
*          On exit, the elements on and above the diagonal of the array
*          contain the min(M,N)-by-N upper trapezoidal matrix R (R is
*          upper triangular if m >= n); the elements below the diagonal,
*          with the array TAU, represent the unitary matrix Q as a
*          product of min(m,n) elementary reflectors (see Further
*          Details).
*
*  LDA     (input) INTEGER
*          The leading dimension of the array A.  LDA >= max(1,M).
*
*  TAU     (output) COMPLEX*16 array, dimension (min(M,N))
*          The scalar factors of the elementary reflectors (see Further
*          Details).
*
*  WORK    (workspace/output) COMPLEX*16 array, dimension (MAX(1,LWORK))
*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
*
*  LWORK   (input) INTEGER
*          The dimension of the array WORK.  LWORK >= max(1,N).
*          For optimum performance LWORK >= N*NB, where NB is
*          the optimal blocksize.
*
*          If LWORK = -1, then a workspace query is assumed; the routine
*          only calculates the optimal size of the WORK array, returns
*          this value as the first entry of the WORK array, and no error
*          message related to LWORK is issued by XERBLA.
*
*  INFO    (output) INTEGER
*          = 0:  successful exit
*          < 0:  if INFO = -i, the i-th argument had an illegal value
*
*  Further Details
*  ===============
*
*  The matrix Q is represented as a product of elementary reflectors
*
*     Q = H(1) H(2) . . . H(k), where k = min(m,n).
*
*  Each H(i) has the form
*
*     H(i) = I - tau * v * v'
*
*  where tau is a complex scalar, and v is a complex vector with
*  v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in A(i+1:m,i),
*  and tau in TAU(i).
*
*  =====================================================================
*/

long m,n,ind,k;
integer stat;

doublecomplex **pS,**pS0,**pSt; // pointers to matrix product and the multiplier
doublecomplex tau_i;
doublecomplex pp;

doublecomplex OptWork;
doublecomplex *work;
integer info;
integer lwork=-1;

integer M=_tmcGetM(A);
integer N=_tmcGetN(A);
integer lda = max(1,M);

long	 mR =lda;// min(M,N);HAZARD - not as documented ?
long	 kTau=min(M,N);

doublecomplex *a = (doublecomplex *)MYMALLOC(sizeof(doublecomplex)*lda*N);
doublecomplex *tau = (doublecomplex *)MYMALLOC(sizeof(doublecomplex)*kTau);

// temporary matrixes
doublecomplex *S = (doublecomplex *)MYMALLOC(sizeof(doublecomplex)*lda*lda);
doublecomplex *S0 = (doublecomplex *)MYMALLOC(sizeof(doublecomplex)*lda*lda);
doublecomplex *H = (doublecomplex *)MYMALLOC(sizeof(doublecomplex)*lda*lda);


memset(a,0,sizeof(doublecomplex)*lda*N);

//memcpy(a,A->m_rData,sizeof(doublereal)*M*N);
	 for (m=0;m<M*N;m++)
		 {
			 a[m].r = A->value.complx.rData[m];
		 }
	 if (_tmcHasIm(A))
	 for (m=0;m<M*N;m++)
		 {
			 a[m].i = A->value.complx.iData[m];
		 }


stat = zgeqrf_(&M, &N,  a,  &lda, tau,
	&OptWork, &lwork, &info);

lwork = (integer)OptWork.r;
	work = MYMALLOC(max(1,lwork)*sizeof(doublereal));

stat = zgeqrf_(&M, &N,  a, &lda, tau,
	work, &lwork, &info);




	 if (nout==1) // q=qr(A)
	 {
     _tmcCreateMatrix(Q,M,N,(short)(_tmcHasIm(A) ));
	 for (m=0;m<M;m++)
		 for (n=0;n<N;n++)
		 {
			 Q->m_rData[n*M+m]=a[lda*n+m].r;
			 if (	_tmcHasIm(A) )
					Q->m_iData[n*M+m]=a[lda*n+m].i;
		 }
	 }
	 else if (nout>1) // [q,r]=qr(A)
	 {
     _tmcCreateMatrix(R,mR,N,(short)(_tmcHasIm(A) ));

	 // get upper trapesoidal matrix
//the elements on and above the diagonal of the array
//*          contain the min(M,N)-by-N upper trapezoidal matrix R (R is
//*          upper triangular if m >= n)
	 for (m=0;m<mR;m++)
		 for (n=m;n<N;n++)
		 {
			 R->m_rData[n*M+m]=a[lda*n+m].r;
			 if (	_tmcHasIm(A) )
					R->m_iData[n*M+m]=a[lda*n+m].i;
		 }

	// calculate Q matrix
//the elements below the diagonal,
//*          with the array TAU, represent the unitary matrix Q as a
//*          product of min(m,n) elementary reflectors:
//*  The matrix Q is represented as a product of elementary reflectors
//*
//*     Q = H(1) H(2) . . . H(k), where k = min(m,n).
//*  Each H(i) has the form
//*     H(i) = I - tau * v * v'
//*  where tau is a complex scalar, and v is a complex vector with
//*  v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in A(i+1:m,i),
//*  and tau in TAU(i).

	memset(S,0,sizeof(doublecomplex)*lda*lda);
	memset(S0,0,sizeof(doublecomplex)*lda*lda);
	//memset(H,0,sizeof(doublecomplex)*lda*lda);

			pS0 = &S0;
			pS  = &S;

	for (ind = 0; ind < kTau; ind++)
	{
		tau_i.r = -tau[ind].r;
		tau_i.i = -tau[ind].i;

		// calculate H(i)=I - tau_i * v(i) * v(i)'
		// indeed H = H'
		memset(H,0,sizeof(doublecomplex)*lda*lda);
		for (m=0;m<ind;m++)
		{
			H[m+m*lda].r = 1;
		}
		
		H[ind+ind*lda] =  tau_i;
		H[ind+ind*lda].r += 1;

		for (m=ind+1;m<lda;m++)
		{
			H[m+ind*lda]=ZMULT_A_B(a[ind*lda+m],tau_i); // -tau(i) * v_i^(m)
			//H[m+ind*lda].r += 1; 
		}
		for (n=ind+1;n<lda;n++)
		{
			H[ind+n*lda] =ZMULT_A_Bhat(tau_i, a[ind*lda+n] ); // -tau(i) * conj(  v_i^(n))
			//H[ind+n*lda].r += 1;
		}

		for (m=ind+1;m<lda;m++)
			for(n=ind+1;n<lda;n++)
			{
				H[m+n*lda] =ZMULT_A_B(ZMULT_A_Bhat(a[ind*lda+m],a[ind*lda+n]),tau_i);//-tau(i) *v_i^(m)*conj(  v_i^(n))
				if (m==n)
					H[m+n*lda].r += 1;
			}
		if (ind>0)
		{
			  // pS = pS0 * H
			for (m=0;m<lda;m++)
				 for (n=0;n<lda;n++)
				 {
					 (*pS)[m+lda*n].r=0;
					 (*pS)[m+lda*n].i=0;
						for (k=0; k<lda;k++)
						{
							pp = ZMULT_A_B( (*pS0)[m+lda*k],H[k+n*lda]);
							(*pS)[m+lda*n].r += pp.r;
							(*pS)[m+lda*n].i += pp.i;
						}
				 }
			// change pointers: pS -> to  buffer for  new result, pS0 -> to last product
			pSt = pS0;
			pS0 = pS;
			pS  = pSt;
			
		}
		else
		{
			// S0 = H
			memcpy(S0,H,sizeof(doublecomplex)*lda*lda);
			//pS0 = &S0;
			//pS  = &S;
			// here pS0 -> to last product = H(0)
			// pS -> to  buffer for new result
		}
	}
    pS = pS0; // pointer to result Q
	// pack results
     _tmcCreateMatrix(Q,lda,lda,(short)(_tmcHasIm(A) ));
	for (m=0;m<lda;m++)
		 for (n=0;n<lda;n++)
		 {
			 Q->m_rData[n*lda+m]=(*pS)[m+lda*n].r;
			 if (	_tmcHasIm(A) )
					Q->m_iData[n*lda+m]=(*pS)[m+lda*n].i;
		 }


/*
	 for (m=0;m<M;m++)
		 for (n=0;n<N;n++)
		 {
			 Q->m_rData[n*M+m]=a[lda*n+m].r;
			 if (	_tmcHasIm(A) )
					Q->m_iData[n*M+m]=a[lda*n+m].i;
		 }
*/
	 }

 	MYFREE(H);
	MYFREE(S0);
	MYFREE(S);

	MYFREE(work);
	MYFREE(tau);
	MYFREE(a);
}


void _tmcdet_z(long nout,long ninput,tmsMatrix *y,tmsMatrix *A)
{
/*
    Purpose   
    =======   

    ZGETRF computes an LU factorization of a general M-by-N matrix A   
    using partial pivoting with row interchanges.   

    The factorization has the form   
       A = P * L * U   
    where P is a permutation matrix, L is lower triangular with unit   
    diagonal elements (lower trapezoidal if m > n), and U is upper   
    triangular (upper trapezoidal if m < n).   

    This is the right-looking Level 3 BLAS version of the algorithm.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    A       (input/output) COMPLEX*16 array, dimension (LDA,N)   
            On entry, the M-by-N matrix to be factored.   
            On exit, the factors L and U from the factorization   
            A = P*L*U; the unit diagonal elements of L are not stored.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    IPIV    (output) INTEGER array, dimension (min(M,N))   
            The pivot indices; for 1 <= i <= min(M,N), row i of the   
            matrix was interchanged with row IPIV(i).   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   
            > 0:  if INFO = i, U(i,i) is exactly zero. The factorization   
                  has been completed, but the factor U is exactly   
                  singular, and division by zero will occur if it is used   
                  to solve a system of equations.   


*/
integer M,info;
int stat;
doublereal dr,di;
int k;
short detsig;
doublecomplex *a;
integer *ipiv;


		M=_tmcGetM(A);
		// Already checked:
		//if (_tmcGetN(A) != M || M==0)
		//{
		//	_tmcRaiseException(err_bad_index,s_module,"tmcdet","Matrix mast be square.",1,A);
		//}

		_tmcClearRegister(y);
		_tmcCreateMatrix(y,1,1,tmcCOMPLEX );
		a = (doublecomplex*)MYMALLOC(M*M*sizeof(doublecomplex));
		for (k=0;k<M*M;k++)
		{
			a[k].r = A->value.complx.rData[k];
			a[k].i = A->value.complx.iData[k];
		}
		ipiv=(integer*)MYMALLOC(M*sizeof(integer));

		stat = zgetrf_(&M,&M,a,&M,ipiv,&info);
		dr=1;di=0;detsig=0;
		if (info==0)
		{
			detsig=1;
			for (k=0;k<M;k++)
			{
				if (ipiv[k] != k)
				{
					detsig = -detsig;
				}
				dr = dr * a[k+k*M].r - di * a[k+k*M].i;
				di = dr * a[k+k*M].i + di * a[k+k*M].r;
			}
			dr = dr * detsig;
			di = di * detsig;
		}
		MYFREE(ipiv);
		MYFREE(a);
		y->value.complx.rData[0]=dr;
		y->value.complx.iData[0]=di;
}
void tmcdet(long nout,long ninput,tmsMatrix *y,tmsMatrix *A)
{
// based on dgetrf,zgetrf
/*
    Purpose   
    =======   

    DGETRF computes an LU factorization of a general M-by-N matrix A   
    using partial pivoting with row interchanges.   

    The factorization has the form   
       A = P * L * U   
    where P is a permutation matrix, L is lower triangular with unit   
    diagonal elements (lower trapezoidal if m > n), and U is upper   
    triangular (upper trapezoidal if m < n).   

    This is the right-looking Level 3 BLAS version of the algorithm.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)   
            On entry, the M-by-N matrix to be factored.   
            On exit, the factors L and U from the factorization   
            A = P*L*U; the unit diagonal elements of L are not stored.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    IPIV    (output) INTEGER array, dimension (min(M,N))   
            The pivot indices; for 1 <= i <= min(M,N), row i of the   
            matrix was interchanged with row IPIV(i).   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   
            > 0:  if INFO = i, U(i,i) is exactly zero. The factorization   
                  has been completed, but the factor U is exactly   
                  singular, and division by zero will occur if it is used   
                  to solve a system of equations.   

*/
integer M,info;
int stat;
doublereal d;
int k;
short detsig;
doublereal *a;
integer *ipiv;


		M=_tmcGetM(A);
		if (_tmcGetN(A) != M || M==0)
		{
			_tmcRaiseException(err_bad_index,s_module,"tmcdet","Matrix mast be square.",1,A);
		}

		if (_tmcHasIm(A))
		{
			_tmcdet_z(nout,ninput,y,A);
			return;
		}

		_tmcClearRegister(y);
		_tmcCreateMatrix(y,1,1,tmcREAL );
		a = (doublereal*)MYMALLOC(M*M*sizeof(doublereal));
		memcpy(a,A->value.complx.rData,M*M*sizeof(doublereal));
		ipiv=(integer*)MYMALLOC(M*sizeof(integer));

		stat = dgetrf_(&M,&M,a,&M,ipiv,&info);
		d=1;detsig=0;
		if (info==0)
		{
			detsig=1;
			for (k=0;k<M;k++)
			{
				if (ipiv[k] != k)
				{
					detsig = -detsig;
				}
				d = d * a[k+k*M];
			}
			d = d * detsig;
		}
		MYFREE(ipiv);
		MYFREE(a);
		y->value.complx.rData[0]=d;
}
