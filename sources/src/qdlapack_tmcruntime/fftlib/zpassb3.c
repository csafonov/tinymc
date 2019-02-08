/* zpassb3.f -- translated by f2c (version 20060506).
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

/*<       subroutine zpassb3 (ido,l1,cc,ch,wa1,wa2) >*/
/* Subroutine */ int zpassb3_(integer *ido, integer *l1, doublereal *cc, 
	doublereal *ch, doublereal *wa1, doublereal *wa2)
{
    /* Initialized data */

    static doublereal taur = -.5;
    static doublereal taui = .866025403784439;

    /* System generated locals */
    integer cc_dim1, cc_offset, ch_dim1, ch_dim2, ch_offset, i__1, i__2;

    /* Local variables */
    integer i__, k;
    doublereal ci2, ci3, di2, di3, cr2, cr3, dr2, dr3, ti2, tr2;

/*<       implicit double precision (a-h,o-z) >*/
/*<    >*/
/*<       data taur,taui /-.5,.866025403784439d0/ >*/
    /* Parameter adjustments */
 //	--cc;--ch;// HSKOST
   ch_dim1 = *ido;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2);
    ch -= ch_offset;
    cc_dim1 = *ido;
    cc_offset = 1 + (cc_dim1 << 2);
    cc -= cc_offset;
    --wa1;
    --wa2;

    /* Function Body */
/*<       if (ido .ne. 2) go to 102 >*/
    if (*ido != 2) {
	goto L102;
    }
/*<       do 101 k=1,l1 >*/
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
/*<          tr2 = cc(1,2,k)+cc(1,3,k) >*/
	tr2 = cc[(k * 3 + 2) * cc_dim1 + 1] + cc[(k * 3 + 3) * cc_dim1 + 1];
/*<          cr2 = cc(1,1,k)+taur*tr2 >*/
	cr2 = cc[(k * 3 + 1) * cc_dim1 + 1] + taur * tr2;
/*<          ch(1,k,1) = cc(1,1,k)+tr2 >*/
	ch[(k + ch_dim2) * ch_dim1 + 1] = cc[(k * 3 + 1) * cc_dim1 + 1] + tr2;
/*<          ti2 = cc(2,2,k)+cc(2,3,k) >*/
	ti2 = cc[(k * 3 + 2) * cc_dim1 + 2] + cc[(k * 3 + 3) * cc_dim1 + 2];
/*<          ci2 = cc(2,1,k)+taur*ti2 >*/
	ci2 = cc[(k * 3 + 1) * cc_dim1 + 2] + taur * ti2;
/*<          ch(2,k,1) = cc(2,1,k)+ti2 >*/
	ch[(k + ch_dim2) * ch_dim1 + 2] = cc[(k * 3 + 1) * cc_dim1 + 2] + ti2;
/*<          cr3 = taui*(cc(1,2,k)-cc(1,3,k)) >*/
	cr3 = taui * (cc[(k * 3 + 2) * cc_dim1 + 1] - cc[(k * 3 + 3) * 
		cc_dim1 + 1]);
/*<          ci3 = taui*(cc(2,2,k)-cc(2,3,k)) >*/
	ci3 = taui * (cc[(k * 3 + 2) * cc_dim1 + 2] - cc[(k * 3 + 3) * 
		cc_dim1 + 2]);
/*<          ch(1,k,2) = cr2-ci3 >*/
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 1] = cr2 - ci3;
/*<          ch(1,k,3) = cr2+ci3 >*/
	ch[(k + ch_dim2 * 3) * ch_dim1 + 1] = cr2 + ci3;
/*<          ch(2,k,2) = ci2+cr3 >*/
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 2] = ci2 + cr3;
/*<          ch(2,k,3) = ci2-cr3 >*/
	ch[(k + ch_dim2 * 3) * ch_dim1 + 2] = ci2 - cr3;
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
/*<             tr2 = cc(i-1,2,k)+cc(i-1,3,k) >*/
	    tr2 = cc[i__ - 1 + (k * 3 + 2) * cc_dim1] + cc[i__ - 1 + (k * 3 + 
		    3) * cc_dim1];
/*<             cr2 = cc(i-1,1,k)+taur*tr2 >*/
	    cr2 = cc[i__ - 1 + (k * 3 + 1) * cc_dim1] + taur * tr2;
/*<             ch(i-1,k,1) = cc(i-1,1,k)+tr2 >*/
	    ch[i__ - 1 + (k + ch_dim2) * ch_dim1] = cc[i__ - 1 + (k * 3 + 1) *
		     cc_dim1] + tr2;
/*<             ti2 = cc(i,2,k)+cc(i,3,k) >*/
	    ti2 = cc[i__ + (k * 3 + 2) * cc_dim1] + cc[i__ + (k * 3 + 3) * 
		    cc_dim1];
/*<             ci2 = cc(i,1,k)+taur*ti2 >*/
	    ci2 = cc[i__ + (k * 3 + 1) * cc_dim1] + taur * ti2;
/*<             ch(i,k,1) = cc(i,1,k)+ti2 >*/
	    ch[i__ + (k + ch_dim2) * ch_dim1] = cc[i__ + (k * 3 + 1) * 
		    cc_dim1] + ti2;
/*<             cr3 = taui*(cc(i-1,2,k)-cc(i-1,3,k)) >*/
	    cr3 = taui * (cc[i__ - 1 + (k * 3 + 2) * cc_dim1] - cc[i__ - 1 + (
		    k * 3 + 3) * cc_dim1]);
/*<             ci3 = taui*(cc(i,2,k)-cc(i,3,k)) >*/
	    ci3 = taui * (cc[i__ + (k * 3 + 2) * cc_dim1] - cc[i__ + (k * 3 + 
		    3) * cc_dim1]);
/*<             dr2 = cr2-ci3 >*/
	    dr2 = cr2 - ci3;
/*<             dr3 = cr2+ci3 >*/
	    dr3 = cr2 + ci3;
/*<             di2 = ci2+cr3 >*/
	    di2 = ci2 + cr3;
/*<             di3 = ci2-cr3 >*/
	    di3 = ci2 - cr3;
/*<             ch(i,k,2) = wa1(i-1)*di2+wa1(i)*dr2 >*/
	    ch[i__ + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 1] * di2 + 
		    wa1[i__] * dr2;
/*<             ch(i-1,k,2) = wa1(i-1)*dr2-wa1(i)*di2 >*/
	    ch[i__ - 1 + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 1] * dr2 
		    - wa1[i__] * di2;
/*<             ch(i,k,3) = wa2(i-1)*di3+wa2(i)*dr3 >*/
	    ch[i__ + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 1] * di3 + wa2[
		    i__] * dr3;
/*<             ch(i-1,k,3) = wa2(i-1)*dr3-wa2(i)*di3 >*/
	    ch[i__ - 1 + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 1] * dr3 - 
		    wa2[i__] * di3;
/*<   103    continue >*/
/* L103: */
	}
/*<   104 continue >*/
/* L104: */
    }
/*<       return >*/
    return 0;
/*<       end >*/
} /* zpassb3_ */

