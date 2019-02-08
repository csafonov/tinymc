/* zpassb4.f -- translated by f2c (version 20060506).
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

/*<       subroutine zpassb4 (ido,l1,cc,ch,wa1,wa2,wa3) >*/
/* Subroutine */ int zpassb4_(integer *ido, integer *l1, doublereal *cc, 
	doublereal *ch, doublereal *wa1, doublereal *wa2, doublereal *wa3)
{
    /* System generated locals */
    integer cc_dim1, cc_offset, ch_dim1, ch_dim2, ch_offset, i__1, i__2;

    /* Local variables */
    integer i__, k;
    doublereal ci2, ci3, ci4, cr2, cr3, cr4, ti1, ti2, ti3, ti4, tr1, tr2, 
	    tr3, tr4;

/*<       implicit double precision (a-h,o-z) >*/
/*<    >*/
/*<       if (ido .ne. 2) go to 102 >*/
    /* Parameter adjustments */
 	//--cc;--ch;// HSKOST
   ch_dim1 = *ido;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2);
    ch -= ch_offset;
    cc_dim1 = *ido;
    cc_offset = 1 + cc_dim1 * 5;
    cc -= cc_offset;
    --wa1;
    --wa2;
    --wa3;

    /* Function Body */
    if (*ido != 2) {
	goto L102;
    }
/*<       do 101 k=1,l1 >*/
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
/*<          ti1 = cc(2,1,k)-cc(2,3,k) >*/
	ti1 = cc[((k << 2) + 1) * cc_dim1 + 2] - cc[((k << 2) + 3) * cc_dim1 
		+ 2];
/*<          ti2 = cc(2,1,k)+cc(2,3,k) >*/
	ti2 = cc[((k << 2) + 1) * cc_dim1 + 2] + cc[((k << 2) + 3) * cc_dim1 
		+ 2];
/*<          tr4 = cc(2,4,k)-cc(2,2,k) >*/
	tr4 = cc[((k << 2) + 4) * cc_dim1 + 2] - cc[((k << 2) + 2) * cc_dim1 
		+ 2];
/*<          ti3 = cc(2,2,k)+cc(2,4,k) >*/
	ti3 = cc[((k << 2) + 2) * cc_dim1 + 2] + cc[((k << 2) + 4) * cc_dim1 
		+ 2];
/*<          tr1 = cc(1,1,k)-cc(1,3,k) >*/
	tr1 = cc[((k << 2) + 1) * cc_dim1 + 1] - cc[((k << 2) + 3) * cc_dim1 
		+ 1];
/*<          tr2 = cc(1,1,k)+cc(1,3,k) >*/
	tr2 = cc[((k << 2) + 1) * cc_dim1 + 1] + cc[((k << 2) + 3) * cc_dim1 
		+ 1];
/*<          ti4 = cc(1,2,k)-cc(1,4,k) >*/
	ti4 = cc[((k << 2) + 2) * cc_dim1 + 1] - cc[((k << 2) + 4) * cc_dim1 
		+ 1];
/*<          tr3 = cc(1,2,k)+cc(1,4,k) >*/
	tr3 = cc[((k << 2) + 2) * cc_dim1 + 1] + cc[((k << 2) + 4) * cc_dim1 
		+ 1];
/*<          ch(1,k,1) = tr2+tr3 >*/
	ch[(k + ch_dim2) * ch_dim1 + 1] = tr2 + tr3;
/*<          ch(1,k,3) = tr2-tr3 >*/
	ch[(k + ch_dim2 * 3) * ch_dim1 + 1] = tr2 - tr3;
/*<          ch(2,k,1) = ti2+ti3 >*/
	ch[(k + ch_dim2) * ch_dim1 + 2] = ti2 + ti3;
/*<          ch(2,k,3) = ti2-ti3 >*/
	ch[(k + ch_dim2 * 3) * ch_dim1 + 2] = ti2 - ti3;
/*<          ch(1,k,2) = tr1+tr4 >*/
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 1] = tr1 + tr4;
/*<          ch(1,k,4) = tr1-tr4 >*/
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 1] = tr1 - tr4;
/*<          ch(2,k,2) = ti1+ti4 >*/
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 2] = ti1 + ti4;
/*<          ch(2,k,4) = ti1-ti4 >*/
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 2] = ti1 - ti4;
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
/*<             ti1 = cc(i,1,k)-cc(i,3,k) >*/
	    ti1 = cc[i__ + ((k << 2) + 1) * cc_dim1] - cc[i__ + ((k << 2) + 3)
		     * cc_dim1];
/*<             ti2 = cc(i,1,k)+cc(i,3,k) >*/
	    ti2 = cc[i__ + ((k << 2) + 1) * cc_dim1] + cc[i__ + ((k << 2) + 3)
		     * cc_dim1];
/*<             ti3 = cc(i,2,k)+cc(i,4,k) >*/
	    ti3 = cc[i__ + ((k << 2) + 2) * cc_dim1] + cc[i__ + ((k << 2) + 4)
		     * cc_dim1];
/*<             tr4 = cc(i,4,k)-cc(i,2,k) >*/
	    tr4 = cc[i__ + ((k << 2) + 4) * cc_dim1] - cc[i__ + ((k << 2) + 2)
		     * cc_dim1];
/*<             tr1 = cc(i-1,1,k)-cc(i-1,3,k) >*/
	    tr1 = cc[i__ - 1 + ((k << 2) + 1) * cc_dim1] - cc[i__ - 1 + ((k <<
		     2) + 3) * cc_dim1];
/*<             tr2 = cc(i-1,1,k)+cc(i-1,3,k) >*/
	    tr2 = cc[i__ - 1 + ((k << 2) + 1) * cc_dim1] + cc[i__ - 1 + ((k <<
		     2) + 3) * cc_dim1];
/*<             ti4 = cc(i-1,2,k)-cc(i-1,4,k) >*/
	    ti4 = cc[i__ - 1 + ((k << 2) + 2) * cc_dim1] - cc[i__ - 1 + ((k <<
		     2) + 4) * cc_dim1];
/*<             tr3 = cc(i-1,2,k)+cc(i-1,4,k) >*/
	    tr3 = cc[i__ - 1 + ((k << 2) + 2) * cc_dim1] + cc[i__ - 1 + ((k <<
		     2) + 4) * cc_dim1];
/*<             ch(i-1,k,1) = tr2+tr3 >*/
	    ch[i__ - 1 + (k + ch_dim2) * ch_dim1] = tr2 + tr3;
/*<             cr3 = tr2-tr3 >*/
	    cr3 = tr2 - tr3;
/*<             ch(i,k,1) = ti2+ti3 >*/
	    ch[i__ + (k + ch_dim2) * ch_dim1] = ti2 + ti3;
/*<             ci3 = ti2-ti3 >*/
	    ci3 = ti2 - ti3;
/*<             cr2 = tr1+tr4 >*/
	    cr2 = tr1 + tr4;
/*<             cr4 = tr1-tr4 >*/
	    cr4 = tr1 - tr4;
/*<             ci2 = ti1+ti4 >*/
	    ci2 = ti1 + ti4;
/*<             ci4 = ti1-ti4 >*/
	    ci4 = ti1 - ti4;
/*<             ch(i-1,k,2) = wa1(i-1)*cr2-wa1(i)*ci2 >*/
	    ch[i__ - 1 + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 1] * cr2 
		    - wa1[i__] * ci2;
/*<             ch(i,k,2) = wa1(i-1)*ci2+wa1(i)*cr2 >*/
	    ch[i__ + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 1] * ci2 + 
		    wa1[i__] * cr2;
/*<             ch(i-1,k,3) = wa2(i-1)*cr3-wa2(i)*ci3 >*/
	    ch[i__ - 1 + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 1] * cr3 - 
		    wa2[i__] * ci3;
/*<             ch(i,k,3) = wa2(i-1)*ci3+wa2(i)*cr3 >*/
	    ch[i__ + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 1] * ci3 + wa2[
		    i__] * cr3;
/*<             ch(i-1,k,4) = wa3(i-1)*cr4-wa3(i)*ci4 >*/
	    ch[i__ - 1 + (k + (ch_dim2 << 2)) * ch_dim1] = wa3[i__ - 1] * cr4 
		    - wa3[i__] * ci4;
/*<             ch(i,k,4) = wa3(i-1)*ci4+wa3(i)*cr4 >*/
	    ch[i__ + (k + (ch_dim2 << 2)) * ch_dim1] = wa3[i__ - 1] * ci4 + 
		    wa3[i__] * cr4;
/*<   103    continue >*/
/* L103: */
	}
/*<   104 continue >*/
/* L104: */
    }
/*<       return >*/
    return 0;
/*<       end >*/
} /* zpassb4_ */

