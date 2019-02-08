// MyFunc.cpp

#include "../lapack_lib/INCLUDE/f2c.h"
//extern "C" {
#include "../lapack_lib/INCLUDE/clapack.h"
//}

#ifdef STATIC_LIB_MLAPACK
#define EXPORTSPECIF	
#else
#define EXPORTSPECIF	__declspec(dllexport)
#endif

//extern "C" {
int __cdecl zffti_(integer *n, doublereal *wsave);
int __cdecl zfftf_(integer *n, doublereal *c__, doublereal *wsave);
//}
/*
******************************************************************

subroutine cffti(n,wsave)

******************************************************************

subroutine cffti initializes the array wsave which is used in
both cfftf and cfftb. the prime factorization of n together with
a tabulation of the trigonometric functions are computed and
stored in wsave.

input parameter

n       the length of the sequence to be transformed

output parameter

wsave   a work array which must be dimensioned at least 4*n+15
        the same work array can be used for both cfftf and cfftb
        as long as n remains unchanged. different wsave arrays
        are required for different values of n. the contents of
        wsave must not be changed between calls of cfftf or cfftb.

******************************************************************

subroutine cfftf(n,c,wsave)

******************************************************************

subroutine cfftf computes the forward complex discrete fourier
transform (the fourier analysis). equivalently , cfftf computes
the fourier coefficients of a complex periodic sequence.
the transform is defined below at output parameter c.

the transform is not normalized. to obtain a normalized transform
the output must be divided by n. otherwise a call of cfftf
followed by a call of cfftb will multiply the sequence by n.

the array wsave which is used by subroutine cfftf must be
initialized by calling subroutine cffti(n,wsave).

input parameters


n      the length of the complex sequence c. the method is
       more efficient when n is the product of small primes. n

c      a complex array of length n which contains the sequence

wsave   a real work array which must be dimensioned at least 4n+15
        in the program that calls cfftf. the wsave array must be
        initialized by calling subroutine cffti(n,wsave) and a
        different wsave array must be used for each different
        value of n. this initialization does not have to be
        repeated so long as n remains unchanged thus subsequent
        transforms can be obtained faster than the first.
        the same wsave array can be used by cfftf and cfftb.

output parameters

c      for j=1,...,n

           c(j)=the sum from k=1,...,n of

                 c(k)*exp(-i*(j-1)*(k-1)*2*pi/n)

                       where i=sqrt(-1)

wsave   contains initialization calculations which must not be
        destroyed between calls of subroutine cfftf or cfftb

******************************************************************
subroutine cfftb(n,c,wsave)

******************************************************************

subroutine cfftb computes the backward complex discrete fourier
transform (the fourier synthesis). equivalently , cfftb computes
a complex periodic sequence from its fourier coefficients.
the transform is defined below at output parameter c.

a call of cfftf followed by a call of cfftb will multiply the
sequence by n.

the array wsave which is used by subroutine cfftb must be
initialized by calling subroutine cffti(n,wsave).

input parameters


n      the length of the complex sequence c. the method is
       more efficient when n is the product of small primes.

c      a complex array of length n which contains the sequence

wsave   a real work array which must be dimensioned at least 4n+15
        in the program that calls cfftb. the wsave array must be
        initialized by calling subroutine cffti(n,wsave) and a
        different wsave array must be used for each different
        value of n. this initialization does not have to be
        repeated so long as n remains unchanged thus subsequent
        transforms can be obtained faster than the first.
        the same wsave array can be used by cfftf and cfftb.

output parameters

c      for j=1,...,n

           c(j)=the sum from k=1,...,n of

                 c(k)*exp(i*(j-1)*(k-1)*2*pi/n)

                       where i=sqrt(-1)

wsave   contains initialization calculations which must not be
        destroyed between calls of subroutine cfftf or cfftb


*/


/////* Subroutine */ int dgels_(char *trans, integer *m, integer *n, integer *
//	nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, 
//	doublereal *work, integer *lwork, integer *info);
//extern "C"
//{

// eig():
EXPORTSPECIF int dgeevx(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, doublereal *a, integer *lda, doublereal *wr, 
	doublereal *wi, doublereal *vl, integer *ldvl, doublereal *vr, 
	integer *ldvr, integer *ilo, integer *ihi, doublereal *scale, 
	doublereal *abnrm, doublereal *rconde, doublereal *rcondv, doublereal  	
	*work, integer *lwork, integer *iwork, integer *info);

EXPORTSPECIF int __cdecl zgeevx(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, doublecomplex *a, integer *lda, doublecomplex *w, 
	doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, 
	integer *ilo, integer *ihi, doublereal *scale, doublereal *abnrm, 
	doublereal *rconde, doublereal *rcondv, doublecomplex *work, integer * 	
	lwork, doublereal *rwork, integer *info);


// ls():
EXPORTSPECIF int __cdecl dgels(char *trans, integer *m, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, 
	doublereal *work, integer *lwork, integer *info);
EXPORTSPECIF  int __cdecl zgels(char *trans, integer *m, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *work, integer *lwork, integer *info);


// svd():
EXPORTSPECIF int __cdecl dgesvd(char *jobu, char *jobvt, integer *m, integer *n, 
	doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
	ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
	integer *info);
EXPORTSPECIF int __cdecl zgesvd(char *jobu, char *jobvt, integer *m, integer *n, 
	doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u, 
	integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *info);

// qr():
EXPORTSPECIF int dgeqrf(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
EXPORTSPECIF int zgeqrf(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork,
	 integer *info);

// fft():
EXPORTSPECIF int __cdecl zffti(integer *n, doublereal *wsave);
EXPORTSPECIF int __cdecl zfftf(integer *n, doublereal *c__, doublereal *wsave);
//}

// QR- Orthogonal-triangular decomposition
EXPORTSPECIF int dgeqrf(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info)
{
	return dgeqrf_(m,n, a, lda, tau, work, lwork,info);
}

EXPORTSPECIF int zgeqrf(integer *m, integer *n, doublecomplex *a, 
	integer *lda, doublecomplex *tau, doublecomplex *work, integer *lwork,
	 integer *info)
{
	return zgeqrf_(m,n, a,lda, tau,work,lwork,info);
}

EXPORTSPECIF int __cdecl dgels(char *trans, integer *m, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, 
	doublereal *work, integer *lwork, integer *info)
{
	return dgels_(trans,m,n,nrhs,a,lda,b,ldb, 
	work, lwork, info);
}
EXPORTSPECIF int __cdecl dgesvd(char *jobu, char *jobvt, integer *m, integer *n, 
	doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
	ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, 
	integer *info)
{
	return dgesvd_(jobu,jobvt,m,n, 
	a, lda, s, u, ldu, vt, ldvt, work, lwork, 
	info);
}

EXPORTSPECIF int __cdecl zgesvd(char *jobu, char *jobvt, integer *m, integer *n, 
	doublecomplex *a, integer *lda, doublereal *s, doublecomplex *u, 
	integer *ldu, doublecomplex *vt, integer *ldvt, doublecomplex *work, 
	integer *lwork, doublereal *rwork, integer *info)
{
	return zgesvd_(jobu,jobvt,m,n, 
	a, lda, s, u, ldu, vt, ldvt, work, lwork, rwork,
	info);
}
EXPORTSPECIF  int __cdecl zgels(char *trans, integer *m, integer *n, integer *
	nrhs, doublecomplex *a, integer *lda, doublecomplex *b, integer *ldb, 
	doublecomplex *work, integer *lwork, integer *info)
{
	return zgels_(trans,m,n,nrhs,a,lda,b,ldb,work,lwork,info);
}

// eig():
EXPORTSPECIF int dgeevx(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, doublereal *a, integer *lda, doublereal *wr, 
	doublereal *wi, doublereal *vl, integer *ldvl, doublereal *vr, 
	integer *ldvr, integer *ilo, integer *ihi, doublereal *scale, 
	doublereal *abnrm, doublereal *rconde, doublereal *rcondv, doublereal  	
	*work, integer *lwork, integer *iwork, integer *info)
{
return dgeevx_(balanc,jobvl,jobvr,sense,n,a,lda,wr, wi,
	vl,ldvl,vr,ldvr, 
	ilo,ihi,scale,abnrm, 
	rconde,rcondv,work,lwork,iwork,info);
}
// LU for det
EXPORTSPECIF int dgetrf(integer *m, integer *n, doublereal *a, integer *
	lda, integer *ipiv, integer *info)
{
	return dgetrf_(m, n, a,  lda,  ipiv, info);
}

EXPORTSPECIF int zgetrf(integer *m, integer *n, doublecomplex *a, 
	integer *lda, integer *ipiv, integer *info)
{
	return zgetrf_(m, n, a, lda, ipiv, info);
}

EXPORTSPECIF int __cdecl zgeevx(char *balanc, char *jobvl, char *jobvr, char *
	sense, integer *n, doublecomplex *a, integer *lda, doublecomplex *w, 
	doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr, 
	integer *ilo, integer *ihi, doublereal *scale, doublereal *abnrm, 
	doublereal *rconde, doublereal *rcondv, doublecomplex *work, integer * 	
	lwork, doublereal *rwork, integer *info)
{
return zgeevx_(balanc,jobvl,jobvr,sense,n,a,lda,w, 
	vl,ldvl,vr,ldvr, 
	ilo,ihi,scale,abnrm, 
	rconde,rcondv,work,lwork,rwork,info);
}

EXPORTSPECIF int __cdecl zffti(integer *n, doublereal *wsave)
{
	return zffti_(n,wsave);
}
EXPORTSPECIF int __cdecl zfftf(integer *n, doublereal *c__, doublereal *wsave)
{
	return zfftf_(n,c__,wsave);
}

//#ifdef _TMC_EMBEDDED_
void f_exit(void)
{
	
}
void bsd_signal(void)
{
}
//#endif
