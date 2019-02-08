/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 File may be used in the generated application
  *****************************************************************************/
// File: mex.h
// Purpose: defs for original (not modified) MEX support

#ifndef _mex_h_1
#define _mex_h_1
#include "tmc.h"
#include "mex2tmc.h"

#define mxArray	  tmsMatrix
#define mxREAL    tmcREAL
#define mxCOMPLEX tmcCOMPLEX

//inline tmsMatrix* mxCreateDoubleMatrix(long m, long n , short iscomplex ) {return (void*)0;}
#define		mxCreateDoubleMatrix _something_wrong_?_?

#define TMCMEX_CREATE_DOUBLE_MATRIX(y,m,n,tmcTYPE)  _tmcCreateMatrix(y, m , n , tmcTYPE ) 
#define TMCMEX_CREATE_CELL_MATRIX(y,m,n)    _tmcCreateCellArray(y, m , n )

#define TMCMEX_NEW_DOUBLE_MATRIX(y,m , n , tmcTYPE)   y=__tmcNewMatrix();_tmcCreateMatrix(y,m,n,tmcTYPE);  
#endif
