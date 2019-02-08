/* zpassb.f -- translated by f2c (version 20060506).
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

/*<       subroutine zpassb (nac,ido,ip,l1,idl1,cc,c1,c2,ch,ch2,wa) >*/
/* Subroutine */ int zpassb_(integer *nac, integer *ido, integer *ip, integer 
	*l1, integer *idl1, doublereal *cc, doublereal *c1, doublereal *c2, 
	doublereal *ch, doublereal *ch2, doublereal *wa)
{
    /* System generated locals */
    integer ch_dim1, ch_dim2, ch_offset, cc_dim1, cc_dim2, cc_offset, c1_dim1,
	     c1_dim2, c1_offset, c2_dim1, c2_offset, ch2_dim1, ch2_offset, 
	    i__1, i__2, i__3;

    /* Local variables */
    integer i__, j, k, l, jc, lc, ik, nt, idj, idl, inc, idp;
    doublereal wai, war;
    integer ipp2, idij, idlj, idot, ipph;

/*<       implicit double precision (a-h,o-z) >*/
/*<    >*/
/*<       idot = ido/2 >*/
    /* Parameter adjustments */
 //	--cc;--ch;// HSKOST
   ch_dim1 = *ido;
    ch_dim2 = *l1;
    ch_offset = 1 + ch_dim1 * (1 + ch_dim2);
    ch -= ch_offset;
    c1_dim1 = *ido;
    c1_dim2 = *l1;
    c1_offset = 1 + c1_dim1 * (1 + c1_dim2);
    c1 -= c1_offset;
    cc_dim1 = *ido;
    cc_dim2 = *ip;
    cc_offset = 1 + cc_dim1 * (1 + cc_dim2);
    cc -= cc_offset;
    ch2_dim1 = *idl1;
    ch2_offset = 1 + ch2_dim1;
    ch2 -= ch2_offset;
    c2_dim1 = *idl1;
    c2_offset = 1 + c2_dim1;
    c2 -= c2_offset;
    --wa;

    /* Function Body */
    idot = *ido / 2;
/*<       nt = ip*idl1 >*/
    nt = *ip * *idl1;
/*<       ipp2 = ip+2 >*/
    ipp2 = *ip + 2;
/*<       ipph = (ip+1)/2 >*/
    ipph = (*ip + 1) / 2;
/*<       idp = ip*ido >*/
    idp = *ip * *ido;

/*<       if (ido .lt. l1) go to 106 >*/
    if (*ido < *l1) {
	goto L106;
    }
/*<       do 103 j=2,ipph >*/
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
/*<          jc = ipp2-j >*/
	jc = ipp2 - j;
/*<          do 102 k=1,l1 >*/
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
/*<             do 101 i=1,ido >*/
	    i__3 = *ido;
	    for (i__ = 1; i__ <= i__3; ++i__) {
/*<                ch(i,k,j) = cc(i,j,k)+cc(i,jc,k) >*/
		ch[i__ + (k + j * ch_dim2) * ch_dim1] = cc[i__ + (j + k * 
			cc_dim2) * cc_dim1] + cc[i__ + (jc + k * cc_dim2) * 
			cc_dim1];
/*<                ch(i,k,jc) = cc(i,j,k)-cc(i,jc,k) >*/
		ch[i__ + (k + jc * ch_dim2) * ch_dim1] = cc[i__ + (j + k * 
			cc_dim2) * cc_dim1] - cc[i__ + (jc + k * cc_dim2) * 
			cc_dim1];
/*<   101       continue >*/
/* L101: */
	    }
/*<   102    continue >*/
/* L102: */
	}
/*<   103 continue >*/
/* L103: */
    }
/*<       do 105 k=1,l1 >*/
    i__1 = *l1;
    for (k = 1; k <= i__1; ++k) {
/*<          do 104 i=1,ido >*/
	i__2 = *ido;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<             ch(i,k,1) = cc(i,1,k) >*/
	    ch[i__ + (k + ch_dim2) * ch_dim1] = cc[i__ + (k * cc_dim2 + 1) * 
		    cc_dim1];
/*<   104    continue >*/
/* L104: */
	}
/*<   105 continue >*/
/* L105: */
    }
/*<       go to 112 >*/
    goto L112;
/*<   106 do 109 j=2,ipph >*/
L106:
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
/*<          jc = ipp2-j >*/
	jc = ipp2 - j;
/*<          do 108 i=1,ido >*/
	i__2 = *ido;
	for (i__ = 1; i__ <= i__2; ++i__) {
/*<             do 107 k=1,l1 >*/
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
/*<                ch(i,k,j) = cc(i,j,k)+cc(i,jc,k) >*/
		ch[i__ + (k + j * ch_dim2) * ch_dim1] = cc[i__ + (j + k * 
			cc_dim2) * cc_dim1] + cc[i__ + (jc + k * cc_dim2) * 
			cc_dim1];
/*<                ch(i,k,jc) = cc(i,j,k)-cc(i,jc,k) >*/
		ch[i__ + (k + jc * ch_dim2) * ch_dim1] = cc[i__ + (j + k * 
			cc_dim2) * cc_dim1] - cc[i__ + (jc + k * cc_dim2) * 
			cc_dim1];
/*<   107       continue >*/
/* L107: */
	    }
/*<   108    continue >*/
/* L108: */
	}
/*<   109 continue >*/
/* L109: */
    }
/*<       do 111 i=1,ido >*/
    i__1 = *ido;
    for (i__ = 1; i__ <= i__1; ++i__) {
/*<          do 110 k=1,l1 >*/
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
/*<             ch(i,k,1) = cc(i,1,k) >*/
	    ch[i__ + (k + ch_dim2) * ch_dim1] = cc[i__ + (k * cc_dim2 + 1) * 
		    cc_dim1];
/*<   110    continue >*/
/* L110: */
	}
/*<   111 continue >*/
/* L111: */
    }
/*<   112 idl = 2-ido >*/
L112:
    idl = 2 - *ido;
/*<       inc = 0 >*/
    inc = 0;
/*<       do 116 l=2,ipph >*/
    i__1 = ipph;
    for (l = 2; l <= i__1; ++l) {
/*<          lc = ipp2-l >*/
	lc = ipp2 - l;
/*<          idl = idl+ido >*/
	idl += *ido;
/*<          do 113 ik=1,idl1 >*/
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
/*<             c2(ik,l) = ch2(ik,1)+wa(idl-1)*ch2(ik,2) >*/
	    c2[ik + l * c2_dim1] = ch2[ik + ch2_dim1] + wa[idl - 1] * ch2[ik 
		    + (ch2_dim1 << 1)];
/*<             c2(ik,lc) = wa(idl)*ch2(ik,ip) >*/
	    c2[ik + lc * c2_dim1] = wa[idl] * ch2[ik + *ip * ch2_dim1];
/*<   113    continue >*/
/* L113: */
	}
/*<          idlj = idl >*/
	idlj = idl;
/*<          inc = inc+ido >*/
	inc += *ido;
/*<          do 115 j=3,ipph >*/
	i__2 = ipph;
	for (j = 3; j <= i__2; ++j) {
/*<             jc = ipp2-j >*/
	    jc = ipp2 - j;
/*<             idlj = idlj+inc >*/
	    idlj += inc;
/*<             if (idlj .gt. idp) idlj = idlj-idp >*/
	    if (idlj > idp) {
		idlj -= idp;
	    }
/*<             war = wa(idlj-1) >*/
	    war = wa[idlj - 1];
/*<             wai = wa(idlj) >*/
	    wai = wa[idlj];
/*<             do 114 ik=1,idl1 >*/
	    i__3 = *idl1;
	    for (ik = 1; ik <= i__3; ++ik) {
/*<                c2(ik,l) = c2(ik,l)+war*ch2(ik,j) >*/
		c2[ik + l * c2_dim1] += war * ch2[ik + j * ch2_dim1];
/*<                c2(ik,lc) = c2(ik,lc)+wai*ch2(ik,jc) >*/
		c2[ik + lc * c2_dim1] += wai * ch2[ik + jc * ch2_dim1];
/*<   114       continue >*/
/* L114: */
	    }
/*<   115    continue >*/
/* L115: */
	}
/*<   116 continue >*/
/* L116: */
    }
/*<       do 118 j=2,ipph >*/
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
/*<          do 117 ik=1,idl1 >*/
	i__2 = *idl1;
	for (ik = 1; ik <= i__2; ++ik) {
/*<             ch2(ik,1) = ch2(ik,1)+ch2(ik,j) >*/
	    ch2[ik + ch2_dim1] += ch2[ik + j * ch2_dim1];
/*<   117    continue >*/
/* L117: */
	}
/*<   118 continue >*/
/* L118: */
    }
/*<       do 120 j=2,ipph >*/
    i__1 = ipph;
    for (j = 2; j <= i__1; ++j) {
/*<          jc = ipp2-j >*/
	jc = ipp2 - j;
/*<          do 119 ik=2,idl1,2 >*/
	i__2 = *idl1;
	for (ik = 2; ik <= i__2; ik += 2) {
/*<             ch2(ik-1,j) = c2(ik-1,j)-c2(ik,jc) >*/
	    ch2[ik - 1 + j * ch2_dim1] = c2[ik - 1 + j * c2_dim1] - c2[ik + 
		    jc * c2_dim1];
/*<             ch2(ik-1,jc) = c2(ik-1,j)+c2(ik,jc) >*/
	    ch2[ik - 1 + jc * ch2_dim1] = c2[ik - 1 + j * c2_dim1] + c2[ik + 
		    jc * c2_dim1];
/*<             ch2(ik,j) = c2(ik,j)+c2(ik-1,jc) >*/
	    ch2[ik + j * ch2_dim1] = c2[ik + j * c2_dim1] + c2[ik - 1 + jc * 
		    c2_dim1];
/*<             ch2(ik,jc) = c2(ik,j)-c2(ik-1,jc) >*/
	    ch2[ik + jc * ch2_dim1] = c2[ik + j * c2_dim1] - c2[ik - 1 + jc * 
		    c2_dim1];
/*<   119    continue >*/
/* L119: */
	}
/*<   120 continue >*/
/* L120: */
    }
/*<       nac = 1 >*/
    *nac = 1;
/*<       if (ido .eq. 2) return >*/
    if (*ido == 2) {
	return 0;
    }
/*<       nac = 0 >*/
    *nac = 0;
/*<       do 121 ik=1,idl1 >*/
    i__1 = *idl1;
    for (ik = 1; ik <= i__1; ++ik) {
/*<          c2(ik,1) = ch2(ik,1) >*/
	c2[ik + c2_dim1] = ch2[ik + ch2_dim1];
/*<   121 continue >*/
/* L121: */
    }
/*<       do 123 j=2,ip >*/
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
/*<          do 122 k=1,l1 >*/
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
/*<             c1(1,k,j) = ch(1,k,j) >*/
	    c1[(k + j * c1_dim2) * c1_dim1 + 1] = ch[(k + j * ch_dim2) * 
		    ch_dim1 + 1];
/*<             c1(2,k,j) = ch(2,k,j) >*/
	    c1[(k + j * c1_dim2) * c1_dim1 + 2] = ch[(k + j * ch_dim2) * 
		    ch_dim1 + 2];
/*<   122    continue >*/
/* L122: */
	}
/*<   123 continue >*/
/* L123: */
    }
/*<       if (idot .gt. l1) go to 127 >*/
    if (idot > *l1) {
	goto L127;
    }
/*<       idij = 0 >*/
    idij = 0;
/*<       do 126 j=2,ip >*/
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
/*<          idij = idij+2 >*/
	idij += 2;
/*<          do 125 i=4,ido,2 >*/
	i__2 = *ido;
	for (i__ = 4; i__ <= i__2; i__ += 2) {
/*<             idij = idij+2 >*/
	    idij += 2;
/*<             do 124 k=1,l1 >*/
	    i__3 = *l1;
	    for (k = 1; k <= i__3; ++k) {
/*<                c1(i-1,k,j) = wa(idij-1)*ch(i-1,k,j)-wa(idij)*ch(i,k,j) >*/
		c1[i__ - 1 + (k + j * c1_dim2) * c1_dim1] = wa[idij - 1] * ch[
			i__ - 1 + (k + j * ch_dim2) * ch_dim1] - wa[idij] * 
			ch[i__ + (k + j * ch_dim2) * ch_dim1];
/*<                c1(i,k,j) = wa(idij-1)*ch(i,k,j)+wa(idij)*ch(i-1,k,j) >*/
		c1[i__ + (k + j * c1_dim2) * c1_dim1] = wa[idij - 1] * ch[i__ 
			+ (k + j * ch_dim2) * ch_dim1] + wa[idij] * ch[i__ - 
			1 + (k + j * ch_dim2) * ch_dim1];
/*<   124       continue >*/
/* L124: */
	    }
/*<   125    continue >*/
/* L125: */
	}
/*<   126 continue >*/
/* L126: */
    }
/*<       return >*/
    return 0;
/*<   127 idj = 2-ido >*/
L127:
    idj = 2 - *ido;
/*<       do 130 j=2,ip >*/
    i__1 = *ip;
    for (j = 2; j <= i__1; ++j) {
/*<          idj = idj+ido >*/
	idj += *ido;
/*<          do 129 k=1,l1 >*/
	i__2 = *l1;
	for (k = 1; k <= i__2; ++k) {
/*<             idij = idj >*/
	    idij = idj;
/*<             do 128 i=4,ido,2 >*/
	    i__3 = *ido;
	    for (i__ = 4; i__ <= i__3; i__ += 2) {
/*<                idij = idij+2 >*/
		idij += 2;
/*<                c1(i-1,k,j) = wa(idij-1)*ch(i-1,k,j)-wa(idij)*ch(i,k,j) >*/
		c1[i__ - 1 + (k + j * c1_dim2) * c1_dim1] = wa[idij - 1] * ch[
			i__ - 1 + (k + j * ch_dim2) * ch_dim1] - wa[idij] * 
			ch[i__ + (k + j * ch_dim2) * ch_dim1];
/*<                c1(i,k,j) = wa(idij-1)*ch(i,k,j)+wa(idij)*ch(i-1,k,j) >*/
		c1[i__ + (k + j * c1_dim2) * c1_dim1] = wa[idij - 1] * ch[i__ 
			+ (k + j * ch_dim2) * ch_dim1] + wa[idij] * ch[i__ - 
			1 + (k + j * ch_dim2) * ch_dim1];
/*<   128       continue >*/
/* L128: */
	    }
/*<   129    continue >*/
/* L129: */
	}
/*<   130 continue >*/
/* L130: */
    }
/*<       return >*/
    return 0;
/*<       end >*/
} /* zpassb_ */

