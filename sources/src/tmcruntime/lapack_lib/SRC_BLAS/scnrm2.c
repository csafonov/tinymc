#include "blaswrap.h"
#include "f2c.h"

doublereal scnrm2_(integer *n, complex *x, integer *incx)
{
/*        The following loop is equivalent to this call to the LAPACK   
          auxiliary routine:   
          CALL CLASSQ( N, X, INCX, SCALE, SSQ ) */
    /* System generated locals */
    integer i__1, i__2, i__3;
    real ret_val, r__1;
    /* Builtin functions */
    double r_imag(complex *), sqrt(doublereal);
    /* Local variables */
    static integer ix;
    static real ssq, temp, norm, scale;
/*  Purpose   
    =======   
    SCNRM2 returns the euclidean norm of a vector via the function   
    name, so that   
       SCNRM2 := sqrt( conjg( x' )*x )   
    -- This version written on 25-October-1982.   
       Modified on 14-October-1993 to inline the call to CLASSQ.   
       Sven Hammarling, Nag Ltd.   
       Parameter adjustments */
    --x;
    /* Function Body */
    if (*n < 1 || *incx < 1) {
	norm = 0.f;
    } else {
	scale = 0.f;
	ssq = 1.f;


	i__1 = (*n - 1) * *incx + 1;
	i__2 = *incx;
	for (ix = 1; i__2 < 0 ? ix >= i__1 : ix <= i__1; ix += i__2) {
	    i__3 = ix;
	    if (x[i__3].r != 0.f) {
		i__3 = ix;
		temp = (r__1 = x[i__3].r, dabs(r__1));
		if (scale < temp) {
/* Computing 2nd power */
		    r__1 = scale / temp;
		    ssq = ssq * (r__1 * r__1) + 1.f;
		    scale = temp;
		} else {
/* Computing 2nd power */
		    r__1 = temp / scale;
		    ssq += r__1 * r__1;
		}
	    }
	    if (r_imag(&x[ix]) != 0.f) {
		temp = (r__1 = r_imag(&x[ix]), dabs(r__1));
		if (scale < temp) {
/* Computing 2nd power */
		    r__1 = scale / temp;
		    ssq = ssq * (r__1 * r__1) + 1.f;
		    scale = temp;
		} else {
/* Computing 2nd power */
		    r__1 = temp / scale;
		    ssq += r__1 * r__1;
		}
	    }
/* L10: */
	}
	norm = scale * sqrt(ssq);
    }

    ret_val = norm;
    return ret_val;

/*     End of SCNRM2. */

} /* scnrm2_ */
