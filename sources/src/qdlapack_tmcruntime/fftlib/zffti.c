/* zffti.f -- translated by f2c (version 20060506).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/*<       subroutine zffti (n,wsave) >*/
/* Subroutine */ int zffti_(integer *n, doublereal *wsave)
{
    integer iw1, iw2;
    extern /* Subroutine */ int zffti1_(integer *, doublereal *, doublereal *)
	    ;

/*<       implicit double precision (a-h,o-z) >*/
/*<       dimension       wsave(*) >*/
/*<       if (n .eq. 1) return >*/
    /* Parameter adjustments */
    --wsave;

    /* Function Body */
    if (*n == 1) {
	return 0;
    }
/*<       iw1 = n+n+1 >*/
    iw1 = *n + *n + 1;
/*<       iw2 = iw1+n+n >*/
    iw2 = iw1 + *n + *n;
/*<       call zffti1 (n,wsave(iw1),wsave(iw2)) >*/
    zffti1_(n, &wsave[iw1], &wsave[iw2]);
/*<       return >*/
    return 0;
/*<       end >*/
} /* zffti_ */

