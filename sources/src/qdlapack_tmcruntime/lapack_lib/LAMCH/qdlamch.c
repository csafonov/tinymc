// File: qdlamch.c
// Experimental file for quadruple precision

#include "blaswrap.h"
#include "f2c.h"
#include <stdio.h>

/*
#define FLT128_MAX 1.18973149535723176508575932662800702e4932Q
#define FLT128_MIN 3.36210314311209350626267781732175260e-4932Q
#define FLT128_EPSILON 1.92592994438723585305597794258492732e-34Q
#define FLT128_DENORM_MIN 6.475175119438025110924438958227646552e-4966Q
#define FLT128_MANT_DIG 113
#define FLT128_MIN_EXP (-16381)
#define FLT128_MAX_EXP 16384
#define FLT128_DIG 33
#define FLT128_MIN_10_EXP (-4931)
#define FLT128_MAX_10_EXP 4932
*/

extern  logical lsame_(char *ca, char *cb);
 
// Based on QD package and mlapack.
 
//"E" denots we always calculate relative machine precision (e).
//where 1+e = 1, minimum of e.
static doublereal lamchE_qd(void)
{
    return FLT128_EPSILON;
}

//"S" denots we always calculate `safe minimum, such that 1/sfmin does not overflow'.
//cf.http://www.netlib.org/blas/dlamch.f
static doublereal lamchS_qd(void)
{
    return FLT128_MIN; // for 4q = 2^(-1022 + 3*53);
}

//"B" base  = base of the machine
//cf.http://www.netlib.org/blas/dlamch.f
static doublereal lamchB_qd(void)
{
    return 2.0q;
}

//"P" prec = eps*base
//cf.http://www.netlib.org/blas/dlamch.f
static doublereal  lamchP_qd(void)
{
    doublereal base, eps, prec;

    base =  lamchB_qd();
    eps =  lamchE_qd();
    prec = eps * base;
    return prec;
}

//"N" t = number of digits in mantissa
//cf.http://www.netlib.org/blas/dlamch.f
static doublereal lamchN_qd(void)
{
    return (doublereal)FLT128_MANT_DIG;	//52*4
}

//"R" rnd   = 1.0 when rounding occurs in addition, 0.0 otherwise
//cf.http://www.netlib.org/blas/dlamch.f
static doublereal  lamchR_qd(void)
{
     return 1.0q;
}

//"M"
//cf.http://www.netlib.org/blas/dlamch.f
static doublereal  lamchM_qd(void)
{
    return  FLT128_MIN;
}

//"U"
//cf.http://www.netlib.org/blas/dlamch.f
static doublereal  lamchU_qd(void)
{
    return FLT128_MIN; // = 2^(-1022 + 3*53);
}

//"L"
//cf.http://www.netlib.org/blas/dlamch.f
static doublereal  lamchL_qd(void)
{
    return   FLT128_MAX_EXP;
}

//"O"
//cf.http://www.netlib.org/blas/dlamch.f
static doublereal  lamchO_qd(void)
{
    return FLT128_MAX;	//approx 1.7976931348623157E+308 in float.h
}

//"Z" :dummy
//cf.http://www.netlib.org/blas/dlamch.f
static doublereal  lamchZ_qd(void)
{
    return 0.0q;
}

doublereal dlamch_(char *cmach)
/* \param[in] CMACH
*>          Specifies the value to be returned by DLAMCH:
*>          = 'E' or 'e',   DLAMCH := eps
*>          = 'S' or 's ,   DLAMCH := sfmin
*>          = 'B' or 'b',   DLAMCH := base
*>          = 'P' or 'p',   DLAMCH := eps*base
*>          = 'N' or 'n',   DLAMCH := t
*>          = 'R' or 'r',   DLAMCH := rnd
*>          = 'M' or 'm',   DLAMCH := emin
*>          = 'U' or 'u',   DLAMCH := rmin
*>          = 'L' or 'l',   DLAMCH := emax
*>          = 'O' or 'o',   DLAMCH := rmax
*>          where
*>          eps   = relative machine precision
*>          sfmin = safe minimum, such that 1/sfmin does not overflow
*>          base  = base of the machine
*>          prec  = eps*base
*>          t     = number of (base) digits in the mantissa
*>          rnd   = 1.0 when rounding occurs in addition, 0.0 otherwise
*>          emin  = minimum exponent before (gradual) underflow
*>          rmin  = underflow threshold - base**(emin-1)
*>          emax  = largest exponent before overflow
*>          rmax  = overflow threshold  - (base**emax)*(1-eps)
*> \endverbatim
*/
{

	printf("qd_dlamch:\n");
    if (lsame_(cmach, "E"))
	return lamchE_qd();
    if (lsame_(cmach, "S"))
	return lamchS_qd();
    if (lsame_(cmach, "B"))
	return lamchB_qd();
    if (lsame_(cmach, "P"))
	return lamchP_qd();
    if (lsame_(cmach, "N"))
	return lamchN_qd();
    if (lsame_(cmach, "R"))
	return lamchR_qd();
    if (lsame_(cmach, "M"))
	return lamchM_qd();
    if (lsame_(cmach, "U"))
	return lamchU_qd();
    if (lsame_(cmach, "L"))
	return lamchL_qd();
    if (lsame_(cmach, "O"))
	return lamchO_qd();

    //xerbla("dlamch", 1);
	printf("************** DLAMCH: invlaid option\n");
    return lamchZ_qd();	
}
