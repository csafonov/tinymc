/* zffti1.f -- translated by f2c (version 20060506).
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

/*<       subroutine zffti1 (n,wa,ifac) >*/
/* Subroutine */ int zffti1_(integer *n, doublereal *wa, integer *ifac)
{
    /* Initialized data */

    static integer ntryh[4] = { 3,4,2,5 };

    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    //double cos(doublereal), sin(doublereal);

    /* Local variables */
    integer i__, j, i1, k1, l1, l2, ib;
    doublereal fi;
    integer ld, ii, nf, ip, nl, nq, nr;
    doublereal arg;
    integer ido, ipm;
    doublereal tpi, argh;
    integer idot, ntry;
    doublereal argld;

/*<       implicit double precision (a-h,o-z) >*/
/*<       dimension       wa(*)      ,ifac(*)    ,ntryh(4) >*/
/*<       data ntryh(1),ntryh(2),ntryh(3),ntryh(4)/3,4,2,5/ >*/
    /* Parameter adjustments */
    --ifac;
    --wa;

    /* Function Body */
/*<       nl = n >*/
    nl = *n;
/*<       nf = 0 >*/
    nf = 0;
/*<       j = 0 >*/
    j = 0;
/*<   101 j = j+1 >*/
L101:
    ++j;
/*<       if (j-4) 102,102,103 >*/
    if (j - 4 <= 0) {
	goto L102;
    } else {
	goto L103;
    }
/*<   102 ntry = ntryh(j) >*/
L102:
    ntry = ntryh[j - 1];
/*<       go to 104 >*/
    goto L104;
/*<   103 ntry = ntry+2 >*/
L103:
    ntry += 2;
/*<   104 nq = nl/ntry >*/
L104:
    nq = nl / ntry;
/*<       nr = nl-ntry*nq >*/
    nr = nl - ntry * nq;
/*<       if (nr) 101,105,101 >*/
    if (nr != 0) {
	goto L101;
    } else {
	goto L105;
    }
/*<   105 nf = nf+1 >*/
L105:
    ++nf;
/*<       ifac(nf+2) = ntry >*/
    ifac[nf + 2] = ntry;
/*<       nl = nq >*/
    nl = nq;
/*<       if (ntry .ne. 2) go to 107 >*/
    if (ntry != 2) {
	goto L107;
    }
/*<       if (nf .eq. 1) go to 107 >*/
    if (nf == 1) {
	goto L107;
    }
/*<       do 106 i=2,nf >*/
    i__1 = nf;
    for (i__ = 2; i__ <= i__1; ++i__) {
/*<          ib = nf-i+2 >*/
	ib = nf - i__ + 2;
/*<          ifac(ib+2) = ifac(ib+1) >*/
	ifac[ib + 2] = ifac[ib + 1];
/*<   106 continue >*/
/* L106: */
    }
/*<       ifac(3) = 2 >*/
    ifac[3] = 2;
/*<   107 if (nl .ne. 1) go to 104 >*/
L107:
    if (nl != 1) {
	goto L104;
    }
/*<       ifac(1) = n >*/
    ifac[1] = *n;
/*<       ifac(2) = nf >*/
    ifac[2] = nf;
/*<       tpi = 6.28318530717959d0 >*/
    tpi = 6.28318530717959;
/*<       argh = tpi/dble(n) >*/
    argh = tpi / (doublereal) (*n);
/*<       i = 2 >*/
    i__ = 2;
/*<       l1 = 1 >*/
    l1 = 1;
/*<       do 110 k1=1,nf >*/
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
/*<          ip = ifac(k1+2) >*/
	ip = ifac[k1 + 2];
/*<          ld = 0 >*/
	ld = 0;
/*<          l2 = l1*ip >*/
	l2 = l1 * ip;
/*<          ido = n/l2 >*/
	ido = *n / l2;
/*<          idot = ido+ido+2 >*/
	idot = ido + ido + 2;
/*<          ipm = ip-1 >*/
	ipm = ip - 1;
/*<          do 109 j=1,ipm >*/
	i__2 = ipm;
	for (j = 1; j <= i__2; ++j) {
/*<             i1 = i >*/
	    i1 = i__;
/*<             wa(i-1) = 1. >*/
	    wa[i__ - 1] = 1.f;
/*<             wa(i) = 0. >*/
	    wa[i__] = 0.f;
/*<             ld = ld+l1 >*/
	    ld += l1;
/*<             fi = 0. >*/
	    fi = 0.f;
/*<             argld = dble(ld)*argh >*/
	    argld = (doublereal) ld * argh;
/*<             do 108 ii=4,idot,2 >*/
	    i__3 = idot;
	    for (ii = 4; ii <= i__3; ii += 2) {
/*<                i = i+2 >*/
		i__ += 2;
/*<                fi = fi+1. >*/
		fi += 1.f;
/*<                arg = fi*argld >*/
		arg = fi * argld;
/*<                wa(i-1) = cos(arg) >*/
		wa[i__ - 1] = cos(arg);
/*<                wa(i) = sin(arg) >*/
		wa[i__] = sin(arg);
/*<   108       continue >*/
/* L108: */
	    }
/*<             if (ip .le. 5) go to 109 >*/
	    if (ip <= 5) {
		goto L109;
	    }
/*<             wa(i1-1) = wa(i-1) >*/
	    wa[i1 - 1] = wa[i__ - 1];
/*<             wa(i1) = wa(i) >*/
	    wa[i1] = wa[i__];
/*<   109    continue >*/
L109:
	    ;
	}
/*<          l1 = l2 >*/
	l1 = l2;
/*<   110 continue >*/
/* L110: */
    }
/*<       return >*/
    return 0;
/*<       end >*/
} /* zffti1_ */

