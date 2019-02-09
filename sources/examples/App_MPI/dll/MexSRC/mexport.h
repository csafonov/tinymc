// File: mexport.h
// Porting mex-files to TMC portable library
#ifndef _mexport_h_
#define _mexport_h_

#define TMCMEX_CREATE_DOUBLE_MATRIX(y,m,n,tmcTYPE)  (y=mxCreateDoubleMatrix(m,n,tmcTYPE))  

#define TMCMEX_CREATE_CELL_MATRIX(y,m,n)   (y=mxCreateCellMatrix(m,n))

#define TMCMEX_NEW_DOUBLE_MATRIX(y,m,n,tmcTYPE)  (y=mxCreateDoubleMatrix(m,n,tmcTYPE ))  

#endif