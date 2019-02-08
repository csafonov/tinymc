/* zpassb5.f -- translated by f2c (version 20060506).
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

/*<       subroutine zpassb5 (ido,l1,cc,ch,wa1,wa2,wa3,wa4) >*/
/* Subroutine */ int zpassb5_(integer *ido, integer *l1, doublereal *cc, 
	doublereal *ch, doublereal *wa1, doublereal *wa2, doublereal *wa3, 
	doublereal *wa4)
{
    /* Initialized data */

    static doublereal tr11 = .309016994374947;
    static doublereal ti11 = .951056516295154;
    static doublereal tr12 = -.809016994374947;
    static doublereal ti12 = .587785252292473;

    /* System generated locals */
    integer cc_dim1, cc_offset, ch_dim1, ch_dim2, ch_offset, i__1, i__2;

    /* Local variables */
    integer i__, k;
    doublereal ci2, ci3, ci4, ci5, di3, di4, di5, di2, cr2, cr3, cr5, cr4, 
	    ti2, ti3, ti4, ti5, dr3, dr4, dr5, dr2, tr2, tr3, tr4, tr5;

/*<       implicit double precision (a-h,o-z) >*/
/*<    >*/
/*<    >*/
    /* Parameter adjustments */
 	//--cc;--ch;// HSKOST
   ch_dim1 = *ido;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2);
    ch -= ch_offset;
    cc_dim1 = *ido;
    cc_offset = 1 + cc_dim1 * 6;
    cc -= cc_offset;
    --wa1;
    --wa2;
    --wa3;
    --wa4;

    /* Function Body */
/*<       if (ido .ne. 2) go to 102 >*/
    if (*ido != 2) {
	goto L102;
    }
/*<       do 101 k=1,l1 >*/
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
/*<          ti5 = cc(2,2,k)-cc(2,5,k) >*/
	ti5 = cc[(k * 5 + 2) * cc_dim1 + 2] - cc[(k * 5 + 5) * cc_dim1 + 2];
/*<          ti2 = cc(2,2,k)+cc(2,5,k) >*/
	ti2 = cc[(k * 5 + 2) * cc_dim1 + 2] + cc[(k * 5 + 5) * cc_dim1 + 2];
/*<          ti4 = cc(2,3,k)-cc(2,4,k) >*/
	ti4 = cc[(k * 5 + 3) * cc_dim1 + 2] - cc[(k * 5 + 4) * cc_dim1 + 2];
/*<          ti3 = cc(2,3,k)+cc(2,4,k) >*/
	ti3 = cc[(k * 5 + 3) * cc_dim1 + 2] + cc[(k * 5 + 4) * cc_dim1 + 2];
/*<          tr5 = cc(1,2,k)-cc(1,5,k) >*/
	tr5 = cc[(k * 5 + 2) * cc_dim1 + 1] - cc[(k * 5 + 5) * cc_dim1 + 1];
/*<          tr2 = cc(1,2,k)+cc(1,5,k) >*/
	tr2 = cc[(k * 5 + 2) * cc_dim1 + 1] + cc[(k * 5 + 5) * cc_dim1 + 1];
/*<          tr4 = cc(1,3,k)-cc(1,4,k) >*/
	tr4 = cc[(k * 5 + 3) * cc_dim1 + 1] - cc[(k * 5 + 4) * cc_dim1 + 1];
/*<          tr3 = cc(1,3,k)+cc(1,4,k) >*/
	tr3 = cc[(k * 5 + 3) * cc_dim1 + 1] + cc[(k * 5 + 4) * cc_dim1 + 1];
/*<          ch(1,k,1) = cc(1,1,k)+tr2+tr3 >*/
	ch[(k + ch_dim2) * ch_dim1 + 1] = cc[(k * 5 + 1) * cc_dim1 + 1] + tr2 
		+ tr3;
/*<          ch(2,k,1) = cc(2,1,k)+ti2+ti3 >*/
	ch[(k + ch_dim2) * ch_dim1 + 2] = cc[(k * 5 + 1) * cc_dim1 + 2] + ti2 
		+ ti3;
/*<          cr2 = cc(1,1,k)+tr11*tr2+tr12*tr3 >*/
	cr2 = cc[(k * 5 + 1) * cc_dim1 + 1] + tr11 * tr2 + tr12 * tr3;
/*<          ci2 = cc(2,1,k)+tr11*ti2+tr12*ti3 >*/
	ci2 = cc[(k * 5 + 1) * cc_dim1 + 2] + tr11 * ti2 + tr12 * ti3;
/*<          cr3 = cc(1,1,k)+tr12*tr2+tr11*tr3 >*/
	cr3 = cc[(k * 5 + 1) * cc_dim1 + 1] + tr12 * tr2 + tr11 * tr3;
/*<          ci3 = cc(2,1,k)+tr12*ti2+tr11*ti3 >*/
	ci3 = cc[(k * 5 + 1) * cc_dim1 + 2] + tr12 * ti2 + tr11 * ti3;
/*<          cr5 = ti11*tr5+ti12*tr4 >*/
	cr5 = ti11 * tr5 + ti12 * tr4;
/*<          ci5 = ti11*ti5+ti12*ti4 >*/
	ci5 = ti11 * ti5 + ti12 * ti4;
/*<          cr4 = ti12*tr5-ti11*tr4 >*/
	cr4 = ti12 * tr5 - ti11 * tr4;
/*<          ci4 = ti12*ti5-ti11*ti4 >*/
	ci4 = ti12 * ti5 - ti11 * ti4;
/*<          ch(1,k,2) = cr2-ci5 >*/
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 1] = cr2 - ci5;
/*<          ch(1,k,5) = cr2+ci5 >*/
	ch[(k + ch_dim2 * 5) * ch_dim1 + 1] = cr2 + ci5;
/*<          ch(2,k,2) = ci2+cr5 >*/
	ch[(k + (ch_dim2 << 1)) * ch_dim1 + 2] = ci2 + cr5;
/*<          ch(2,k,3) = ci3+cr4 >*/
	ch[(k + ch_dim2 * 3) * ch_dim1 + 2] = ci3 + cr4;
/*<          ch(1,k,3) = cr3-ci4 >*/
	ch[(k + ch_dim2 * 3) * ch_dim1 + 1] = cr3 - ci4;
/*<          ch(1,k,4) = cr3+ci4 >*/
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 1] = cr3 + ci4;
/*<          ch(2,k,4) = ci3-cr4 >*/
	ch[(k + (ch_dim2 << 2)) * ch_dim1 + 2] = ci3 - cr4;
/*<          ch(2,k,5) = ci2-cr5 >*/
	ch[(k + ch_dim2 * 5) * ch_dim1 + 2] = ci2 - cr5;
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
/*<             ti5 = cc(i,2,k)-cc(i,5,k) >*/
	    ti5 = cc[i__ + (k * 5 + 2) * cc_dim1] - cc[i__ + (k * 5 + 5) * 
		    cc_dim1];
/*<             ti2 = cc(i,2,k)+cc(i,5,k) >*/
	    ti2 = cc[i__ + (k * 5 + 2) * cc_dim1] + cc[i__ + (k * 5 + 5) * 
		    cc_dim1];
/*<             ti4 = cc(i,3,k)-cc(i,4,k) >*/
	    ti4 = cc[i__ + (k * 5 + 3) * cc_dim1] - cc[i__ + (k * 5 + 4) * 
		    cc_dim1];
/*<             ti3 = cc(i,3,k)+cc(i,4,k) >*/
	    ti3 = cc[i__ + (k * 5 + 3) * cc_dim1] + cc[i__ + (k * 5 + 4) * 
		    cc_dim1];
/*<             tr5 = cc(i-1,2,k)-cc(i-1,5,k) >*/
	    tr5 = cc[i__ - 1 + (k * 5 + 2) * cc_dim1] - cc[i__ - 1 + (k * 5 + 
		    5) * cc_dim1];
/*<             tr2 = cc(i-1,2,k)+cc(i-1,5,k) >*/
	    tr2 = cc[i__ - 1 + (k * 5 + 2) * cc_dim1] + cc[i__ - 1 + (k * 5 + 
		    5) * cc_dim1];
/*<             tr4 = cc(i-1,3,k)-cc(i-1,4,k) >*/
	    tr4 = cc[i__ - 1 + (k * 5 + 3) * cc_dim1] - cc[i__ - 1 + (k * 5 + 
		    4) * cc_dim1];
/*<             tr3 = cc(i-1,3,k)+cc(i-1,4,k) >*/
	    tr3 = cc[i__ - 1 + (k * 5 + 3) * cc_dim1] + cc[i__ - 1 + (k * 5 + 
		    4) * cc_dim1];
/*<             ch(i-1,k,1) = cc(i-1,1,k)+tr2+tr3 >*/
	    ch[i__ - 1 + (k + ch_dim2) * ch_dim1] = cc[i__ - 1 + (k * 5 + 1) *
		     cc_dim1] + tr2 + tr3;
/*<             ch(i,k,1) = cc(i,1,k)+ti2+ti3 >*/
	    ch[i__ + (k + ch_dim2) * ch_dim1] = cc[i__ + (k * 5 + 1) * 
		    cc_dim1] + ti2 + ti3;
/*<             cr2 = cc(i-1,1,k)+tr11*tr2+tr12*tr3 >*/
	    cr2 = cc[i__ - 1 + (k * 5 + 1) * cc_dim1] + tr11 * tr2 + tr12 * 
		    tr3;
/*<             ci2 = cc(i,1,k)+tr11*ti2+tr12*ti3 >*/
	    ci2 = cc[i__ + (k * 5 + 1) * cc_dim1] + tr11 * ti2 + tr12 * ti3;
/*<             cr3 = cc(i-1,1,k)+tr12*tr2+tr11*tr3 >*/
	    cr3 = cc[i__ - 1 + (k * 5 + 1) * cc_dim1] + tr12 * tr2 + tr11 * 
		    tr3;
/*<             ci3 = cc(i,1,k)+tr12*ti2+tr11*ti3 >*/
	    ci3 = cc[i__ + (k * 5 + 1) * cc_dim1] + tr12 * ti2 + tr11 * ti3;
/*<             cr5 = ti11*tr5+ti12*tr4 >*/
	    cr5 = ti11 * tr5 + ti12 * tr4;
/*<             ci5 = ti11*ti5+ti12*ti4 >*/
	    ci5 = ti11 * ti5 + ti12 * ti4;
/*<             cr4 = ti12*tr5-ti11*tr4 >*/
	    cr4 = ti12 * tr5 - ti11 * tr4;
/*<             ci4 = ti12*ti5-ti11*ti4 >*/
	    ci4 = ti12 * ti5 - ti11 * ti4;
/*<             dr3 = cr3-ci4 >*/
	    dr3 = cr3 - ci4;
/*<             dr4 = cr3+ci4 >*/
	    dr4 = cr3 + ci4;
/*<             di3 = ci3+cr4 >*/
	    di3 = ci3 + cr4;
/*<             di4 = ci3-cr4 >*/
	    di4 = ci3 - cr4;
/*<             dr5 = cr2+ci5 >*/
	    dr5 = cr2 + ci5;
/*<             dr2 = cr2-ci5 >*/
	    dr2 = cr2 - ci5;
/*<             di5 = ci2-cr5 >*/
	    di5 = ci2 - cr5;
/*<             di2 = ci2+cr5 >*/
	    di2 = ci2 + cr5;
/*<             ch(i-1,k,2) = wa1(i-1)*dr2-wa1(i)*di2 >*/
	    ch[i__ - 1 + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 1] * dr2 
		    - wa1[i__] * di2;
/*<             ch(i,k,2) = wa1(i-1)*di2+wa1(i)*dr2 >*/
	    ch[i__ + (k + (ch_dim2 << 1)) * ch_dim1] = wa1[i__ - 1] * di2 + 
		    wa1[i__] * dr2;
/*<             ch(i-1,k,3) = wa2(i-1)*dr3-wa2(i)*di3 >*/
	    ch[i__ - 1 + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 1] * dr3 - 
		    wa2[i__] * di3;
/*<             ch(i,k,3) = wa2(i-1)*di3+wa2(i)*dr3 >*/
	    ch[i__ + (k + ch_dim2 * 3) * ch_dim1] = wa2[i__ - 1] * di3 + wa2[
		    i__] * dr3;
/*<             ch(i-1,k,4) = wa3(i-1)*dr4-wa3(i)*di4 >*/
	    ch[i__ - 1 + (k + (ch_dim2 << 2)) * ch_dim1] = wa3[i__ - 1] * dr4 
		    - wa3[i__] * di4;
/*<             ch(i,k,4) = wa3(i-1)*di4+wa3(i)*dr4 >*/
	    ch[i__ + (k + (ch_dim2 << 2)) * ch_dim1] = wa3[i__ - 1] * di4 + 
		    wa3[i__] * dr4;
/*<             ch(i-1,k,5) = wa4(i-1)*dr5-wa4(i)*di5 >*/
	    ch[i__ - 1 + (k + ch_dim2 * 5) * ch_dim1] = wa4[i__ - 1] * dr5 - 
		    wa4[i__] * di5;
/*<             ch(i,k,5) = wa4(i-1)*di5+wa4(i)*dr5 >*/
	    ch[i__ + (k + ch_dim2 * 5) * ch_dim1] = wa4[i__ - 1] * di5 + wa4[
		    i__] * dr5;
/*<   103    continue >*/
/* L103: */
	}
/*<   104 continue >*/
/* L104: */
    }
/*<       return >*/
    return 0;
/*<       end >*/
} /* zpassb5_ */

