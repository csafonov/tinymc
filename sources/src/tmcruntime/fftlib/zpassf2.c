/* zpassf2.f -- translated by f2c (version 20060506).
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

/*<       subroutine zpassf2 (ido,l1,cc,ch,wa1) >*/
/* Subroutine */ int zpassf2_(integer *ido, integer *l1, doublereal *cc, 
	doublereal *ch, doublereal *wa1)
{
    /* System generated locals */
    integer cc_dim1, cc_offset, ch_dim1, ch_dim2, ch_offset, i__1, i__2;

    /* Local variables */
    integer i__, k;
    doublereal ti2, tr2;

/*<       implicit double precision (a-h,o-z) >*/
/*<    >*/
/*<       if (ido .gt. 2) go to 102 >*/
    /* Parameter adjustments */
	//--cc;--ch;// HSKOST
    ch_dim1 = *ido;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2);
    ch -= ch_offset;
    cc_dim1 = *ido;
    cc_offset = 1 + cc_dim1 * 3;
    cc -= cc_offset;
    --wa1;

    /* Function Body */
    if (*ido > 2) {
	goto L102;
    }
/*<       do 101 k=1,l1 >*/
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
/*<          ch(1,k,1) = cc(1,1,k)+cc(1,2,k) >*/
	ch[(k + ch_dim2) * ch_dim1 + 1] = cc[((k << 1) + 1) * cc_dim1 + 1] + 
		cc[((k << 1) + 2) * cc_dim1 + 1];
/*<          ch(1,k,2) = cc(1,1,k)-cc(1,2,k) >*/
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 1] = cc[((k << 1) + 1) * cc_dim1 
		+ 1] - cc[((k << 1) + 2) * cc_dim1 + 1];
/*<          ch(2,k,1) = cc(2,1,k)+cc(2,2,k) >*/
	ch[(k + ch_dim2) * ch_dim1 + 2] = cc[((k << 1) + 1) * cc_dim1 + 2] + 
		cc[((k << 1) + 2) * cc_dim1 + 2];
/*<          ch(2,k,2) = cc(2,1,k)-cc(2,2,k) >*/
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 2] = cc[((k << 1) + 1) * cc_dim1 
		+ 2] - cc[((k << 1) + 2) * cc_dim1 + 2];
/*<   101 continue >*/
/* L101: */
    }
/*<       return >*/
    return 0;
/*<   102 do 104 k=1,l1 >*/
L102:
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
/*<          do 103 i=2,ido,2 >*/
	i__2 = *ido;
	for (i__ = 2; i__ <= i__2; i__ += 2) {
/*<             ch(i-1,k,1) = cc(i-1,1,k)+cc(i-1,2,k) >*/
	    ch[i__ - 1 + (k + ch_dim2) * ch_dim1] = cc[i__ - 1 + ((k << 1) + 
		    1) * cc_dim1] + cc[i__ - 1 + ((k << 1) + 2) * cc_dim1];
/*<             tr2 = cc(i-1,1,k)-cc(i-1,2,k) >*/
	    tr2 = cc[i__ - 1 + ((k << 1) + 1) * cc_dim1] - cc[i__ - 1 + ((k <<
		     1) + 2) * cc_dim1];
/*<             ch(i,k,1) = cc(i,1,k)+cc(i,2,k) >*/
	    ch[i__ + (k + ch_dim2) * ch_dim1] = cc[i__ + ((k << 1) + 1) * 
		    cc_dim1] + cc[i__ + ((k << 1) + 2) * cc_dim1];
/*<             ti2 = cc(i,1,k)-cc(i,2,k) >*/
	    ti2 = cc[i__ + ((k << 1) + 1) * cc_dim1] - cc[i__ + ((k << 1) + 2)
		     * cc_dim1];
/*<             ch(i,k,2) = wa1(i-1)*ti2-wa1(i)*tr2 >*/
	    ch[i__ + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 1] * ti2 - 
		    wa1[i__] * tr2;
/*<             ch(i-1,k,2) = wa1(i-1)*tr2+wa1(i)*ti2 >*/
	    ch[i__ - 1 + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 1] * tr2 
		    + wa1[i__] * ti2;
/*<   103    continue >*/
/* L103: */
	}
/*<   104 continue >*/
/* L104: */
    }
/*<       return >*/
    return 0;
/*<       end >*/
} /* zpassf2_ */

