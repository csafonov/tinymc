/* zfftb1.f -- translated by f2c (version 20060506).
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

/*<       subroutine zfftb1 (n,c,ch,wa,ifac) >*/
/* Subroutine */ int zfftb1_(integer *n, doublereal *c__, doublereal *ch, 
	doublereal *wa, integer *ifac)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    integer i__, k1, l1, l2, n2, na, nf, ip, iw, ix2, ix3, ix4, nac, ido, 
	    idl1, idot;
    extern /* Subroutine */ int zpassb_(integer *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), zpassb2_(integer *, 
	    integer *, doublereal *, doublereal *, doublereal *), zpassb3_(
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), zpassb4_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), zpassb5_(
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

/*<       implicit double precision (a-h,o-z) >*/
/*<       dimension       ch(*)      ,c(*)       ,wa(*)      ,ifac(*) >*/
/*<       nf = ifac(2) >*/
    /* Parameter adjustments */
    --ifac;
    --wa;
    --ch;
    --c__;

    /* Function Body */
    nf = ifac[2];
/*<       na = 0 >*/
    na = 0;
/*<       l1 = 1 >*/
    l1 = 1;
/*<       iw = 1 >*/
    iw = 1;
/*<       do 116 k1=1,nf >*/
    i__1 = nf;
    for (k1 = 1; k1 <= i__1; ++k1) {
/*<          ip = ifac(k1+2) >*/
	ip = ifac[k1 + 2];
/*<          l2 = ip*l1 >*/
	l2 = ip * l1;
/*<          ido = n/l2 >*/
	ido = *n / l2;
/*<          idot = ido+ido >*/
	idot = ido + ido;
/*<          idl1 = idot*l1 >*/
	idl1 = idot * l1;
/*<          if (ip .ne. 4) go to 103 >*/
	if (ip != 4) {
	    goto L103;
	}
/*<          ix2 = iw+idot >*/
	ix2 = iw + idot;
/*<          ix3 = ix2+idot >*/
	ix3 = ix2 + idot;
/*<          if (na .ne. 0) go to 101 >*/
	if (na != 0) {
	    goto L101;
	}
/*<          call zpassb4 (idot,l1,c,ch,wa(iw),wa(ix2),wa(ix3)) >*/
	zpassb4_(&idot, &l1, &c__[1], &ch[1], &wa[iw], &wa[ix2], &wa[ix3]);
/*<          go to 102 >*/
	goto L102;
/*<   101    call zpassb4 (idot,l1,ch,c,wa(iw),wa(ix2),wa(ix3)) >*/
L101:
	zpassb4_(&idot, &l1, &ch[1], &c__[1], &wa[iw], &wa[ix2], &wa[ix3]);
/*<   102    na = 1-na >*/
L102:
	na = 1 - na;
/*<          go to 115 >*/
	goto L115;
/*<   103    if (ip .ne. 2) go to 106 >*/
L103:
	if (ip != 2) {
	    goto L106;
	}
/*<          if (na .ne. 0) go to 104 >*/
	if (na != 0) {
	    goto L104;
	}
/*<          call zpassb2 (idot,l1,c,ch,wa(iw)) >*/
	zpassb2_(&idot, &l1, &c__[1], &ch[1], &wa[iw]);
/*<          go to 105 >*/
	goto L105;
/*<   104    call zpassb2 (idot,l1,ch,c,wa(iw)) >*/
L104:
	zpassb2_(&idot, &l1, &ch[1], &c__[1], &wa[iw]);
/*<   105    na = 1-na >*/
L105:
	na = 1 - na;
/*<          go to 115 >*/
	goto L115;
/*<   106    if (ip .ne. 3) go to 109 >*/
L106:
	if (ip != 3) {
	    goto L109;
	}
/*<          ix2 = iw+idot >*/
	ix2 = iw + idot;
/*<          if (na .ne. 0) go to 107 >*/
	if (na != 0) {
	    goto L107;
	}
/*<          call zpassb3 (idot,l1,c,ch,wa(iw),wa(ix2)) >*/
	zpassb3_(&idot, &l1, &c__[1], &ch[1], &wa[iw], &wa[ix2]);
/*<          go to 108 >*/
	goto L108;
/*<   107    call zpassb3 (idot,l1,ch,c,wa(iw),wa(ix2)) >*/
L107:
	zpassb3_(&idot, &l1, &ch[1], &c__[1], &wa[iw], &wa[ix2]);
/*<   108    na = 1-na >*/
L108:
	na = 1 - na;
/*<          go to 115 >*/
	goto L115;
/*<   109    if (ip .ne. 5) go to 112 >*/
L109:
	if (ip != 5) {
	    goto L112;
	}
/*<          ix2 = iw+idot >*/
	ix2 = iw + idot;
/*<          ix3 = ix2+idot >*/
	ix3 = ix2 + idot;
/*<          ix4 = ix3+idot >*/
	ix4 = ix3 + idot;
/*<          if (na .ne. 0) go to 110 >*/
	if (na != 0) {
	    goto L110;
	}
/*<          call zpassb5 (idot,l1,c,ch,wa(iw),wa(ix2),wa(ix3),wa(ix4)) >*/
	zpassb5_(&idot, &l1, &c__[1], &ch[1], &wa[iw], &wa[ix2], &wa[ix3], &
		wa[ix4]);
/*<          go to 111 >*/
	goto L111;
/*<   110    call zpassb5 (idot,l1,ch,c,wa(iw),wa(ix2),wa(ix3),wa(ix4)) >*/
L110:
	zpassb5_(&idot, &l1, &ch[1], &c__[1], &wa[iw], &wa[ix2], &wa[ix3], &
		wa[ix4]);
/*<   111    na = 1-na >*/
L111:
	na = 1 - na;
/*<          go to 115 >*/
	goto L115;
/*<   112    if (na .ne. 0) go to 113 >*/
L112:
	if (na != 0) {
	    goto L113;
	}
/*<          call zpassb (nac,idot,ip,l1,idl1,c,c,c,ch,ch,wa(iw)) >*/
	zpassb_(&nac, &idot, &ip, &l1, &idl1, &c__[1], &c__[1], &c__[1], &ch[
		1], &ch[1], &wa[iw]);
/*<          go to 114 >*/
	goto L114;
/*<   113    call zpassb (nac,idot,ip,l1,idl1,ch,ch,ch,c,c,wa(iw)) >*/
L113:
	zpassb_(&nac, &idot, &ip, &l1, &idl1, &ch[1], &ch[1], &ch[1], &c__[1],
		 &c__[1], &wa[iw]);
/*<   114    if (nac .ne. 0) na = 1-na >*/
L114:
	if (nac != 0) {
	    na = 1 - na;
	}
/*<   115    l1 = l2 >*/
L115:
	l1 = l2;
/*<          iw = iw+(ip-1)*idot >*/
	iw += (ip - 1) * idot;
/*<   116 continue >*/
/* L116: */
    }
/*<       if (na .eq. 0) return >*/
    if (na == 0) {
	return 0;
    }
/*<       n2 = n+n >*/
    n2 = *n + *n;
/*<       do 117 i=1,n2 >*/
    i__1 = n2;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<          c(i) = ch(i) >*/
	c__[i__] = ch[i__];
/*<   117 continue >*/
/* L117: */
    }
/*<       return >*/
    return 0;
/*<       end >*/
} /* zfftb1_ */

