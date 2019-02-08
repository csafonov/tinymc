#include "blaswrap.h"
#include "f2c.h"

doublereal scabs1_(complex *z__)
{
    /* System generated locals */
    real ret_val, r__1, r__2;
    /* Builtin functions */
    double r_imag(complex *);
/*  Purpose   
    =======   
    SCABS1 computes absolute value of a complex number */
    ret_val = (r__1 = z__->r, dabs(r__1)) + (r__2 = r_imag(z__), dabs(r__2));
    return ret_val;
} /* scabs1_ */

