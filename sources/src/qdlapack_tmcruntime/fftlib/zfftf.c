/* zfftf.f -- translated by f2c (version 20060506).
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

/*<       subroutine zfftf (n,c,wsave) >*/
/* Subroutine */ int zfftf_(integer *n, doublereal *c__, doublereal *wsave)
{
    integer iw1, iw2;
    extern /* Subroutine */ int zfftf1_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *);

/*<       implicit double precision (a-h,o-z) >*/
/*<       dimension       c(*)       ,wsave(*) >*/
/*<       if (n .eq. 1) return >*/
    /* Parameter adjustments */
    --wsave;
    --c__;

    /* Function Body */
    if (*n == 1) {
	return 0;
    }
/*<       iw1 = n+n+1 >*/
    iw1 = *n + *n + 1;
/*<       iw2 = iw1+n+n >*/
    iw2 = iw1 + *n + *n;
/*<       call zfftf1 (n,c,wsave,wsave(iw1),wsave(iw2)) >*/
    zfftf1_(n, &c__[1], &wsave[1], &wsave[iw1], &wsave[iw2]);
/*<       return >*/
    return 0;
/*<       end >*/
} /* zfftf_ */

