#include "blaswrap.h"
#include "f2c.h"

/* Complex */ VOID cdotu_(complex * ret_val, integer *n, complex *cx, integer 
	*incx, complex *cy, integer *incy)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    complex q__1, q__2;
    /* Local variables */
    static integer i__, ix, iy;
    static complex ctemp;
/*  Purpose   
    =======   
       CDOTU forms the dot product of two vectors.   
    Further Details   
    ===============   
       jack dongarra, linpack, 3/11/78.   
       modified 12/3/93, array(1) declarations changed to array(*)   
       Parameter adjustments */
    --cy;
    --cx;
    /* Function Body */
    ctemp.r = 0.f, ctemp.i = 0.f;
     ret_val->r = 0.f,  ret_val->i = 0.f;
    if (*n <= 0) {
	return ;
    }
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }
/*        code for unequal increments or equal increments   
            not equal to 1 */
    ix = 1;
    iy = 1;
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = ix;
	i__3 = iy;
	q__2.r = cx[i__2].r * cy[i__3].r - cx[i__2].i * cy[i__3].i, q__2.i = 
		cx[i__2].r * cy[i__3].i + cx[i__2].i * cy[i__3].r;
	q__1.r = ctemp.r + q__2.r, q__1.i = ctemp.i + q__2.i;
	ctemp.r = q__1.r, ctemp.i = q__1.i;
	ix += *incx;
	iy += *incy;
/* L10: */
    }
     ret_val->r = ctemp.r,  ret_val->i = ctemp.i;
    return ;
/*        code for both increments equal to 1 */
L20:
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = i__;
	i__3 = i__;
	q__2.r = cx[i__2].r * cy[i__3].r - cx[i__2].i * cy[i__3].i, q__2.i = 
		cx[i__2].r * cy[i__3].i + cx[i__2].i * cy[i__3].r;
	q__1.r = ctemp.r + q__2.r, q__1.i = ctemp.i + q__2.i;
	ctemp.r = q__1.r, ctemp.i = q__1.i;
/* L30: */
    }
     ret_val->r = ctemp.r,  ret_val->i = ctemp.i;
    return ;
} /* cdotu_ */

