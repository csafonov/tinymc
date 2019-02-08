#include "blaswrap.h"
#include "f2c.h"

doublereal dcabs1_(doublecomplex *z__)
{
    /* System generated locals */
    doublereal ret_val, d__1, d__2;
    /// Builtin functions
#ifndef USE_QDMATH

    double d_imag(doublecomplex *);
#endif
/*  Purpose   
    =======   
    DCABS1 computes absolute value of a double complex number */
    ret_val = (d__1 = z__->r, abs(d__1)) + (d__2 = d_imag(z__), abs(d__2));
    return ret_val;
} /* dcabs1_ */

