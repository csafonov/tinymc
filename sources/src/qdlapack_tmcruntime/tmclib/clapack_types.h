// File: clapack_types.h
#ifndef _clapack_types_h_
#define _clapack_types_h_

typedef long int integer;
typedef unsigned long int uinteger;
typedef char *address;
typedef short int shortint;
#ifdef USE_QDMATH
#ifdef __INTEL_COMPILER
#include "..\lapack_lib\include\intel_quad.h"
#else
#include <quadmath.h>
typedef __float128 real;
typedef __float128 doublereal;
#endif
#else
typedef float real;
typedef double doublereal;
#endif
typedef struct { real r, i; } complex;
typedef struct { doublereal r, i; } doublecomplex;
typedef long int logical;
typedef short int shortlogical;
typedef char logical1;
typedef char integer1;
#ifdef INTEGER_STAR_8	/* Adjust for integer*8. */
typedef long long longint;		/* system-dependent */
typedef unsigned long long ulongint;	/* system-dependent */
#define qbit_clear(a,b)	((a) & ~((ulongint)1 << (b)))
#define qbit_set(a,b)	((a) |  ((ulongint)1 << (b)))
#endif

#define VOID void

typedef int /* Unknown procedure type */ (*U_fp)();
typedef shortint (*J_fp)();
typedef integer (*I_fp)();
typedef real (*R_fp)();
typedef doublereal (*D_fp)(), (*E_fp)();
typedef /* Complex */ VOID (*C_fp)();
typedef /* Double Complex */ VOID (*Z_fp)();
typedef logical (*L_fp)();
typedef shortlogical (*K_fp)();
typedef /* Character */ VOID (*H_fp)();
typedef /* Subroutine */ int (*S_fp)();

#endif
