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

// By default, mwIndex is equivalent to int in C.
//When using the mex - largeArrayDims switch, mwIndex is equivalent to size_t in C.
//In Fortran, mwIndex is similarly equivalent to INTEGER * 4 or INTEGER * 8, based on platform and compilation flags.
#define mwSize	int
#define mwIndex int
typedef enum {
	mxUNKNOWN_CLASS,
	mxCELL_CLASS,
	mxSTRUCT_CLASS,
	mxLOGICAL_CLASS,
	mxCHAR_CLASS,
	mxVOID_CLASS,
	mxDOUBLE_CLASS,
	mxSINGLE_CLASS,
	mxINT8_CLASS,
	mxUINT8_CLASS,
	mxINT16_CLASS,
	mxUINT16_CLASS,
	mxINT32_CLASS,
	mxUINT32_CLASS,
	mxINT64_CLASS,
	mxUINT64_CLASS,
	mxFUNCTION_CLASS
} mxClassID;

#define mxArray	  tmsMatrix
#define mxREAL    tmcREAL
#define mxCOMPLEX tmcCOMPLEX

#define mxLogical double 
#define mxGetLogicals(mX) (mX->m_rData)
#define mxIsLogical(mX) (0)
#define mxIsCell(mX) ( (mX->m_desc.m_type ==TYPE_CELL_ARRAY) ? 1:0)


//inline tmsMatrix* mxCreateDoubleMatrix(long m, long n , short iscomplex ) {return (void*)0;}
#define		mxCreateDoubleMatrix _something_wrong_?_?
#define     mxCreateString       _something_wrong_?_?s

#define TMCMEX_CREATE_DOUBLE_MATRIX(y,m,n,tmcTYPE)  _tmcCreateMatrix(y, m , n , tmcTYPE ) 
#define TMCMEX_CREATE_CELL_MATRIX(y,m,n)    _tmcCreateCellArray(y, m , n )

#define TMCMEX_NEW_DOUBLE_MATRIX(y,m , n , tmcTYPE)   y=__tmcNewMatrix();_tmcCreateMatrix(y,m,n,tmcTYPE);  
#define TMCMEX_CREATE_STRING_MATRIX(y,str)  (_tmcSetString(y,str)) 
#define TMCMEX_NEW_STRING_MATRIX(y,str)  y=__tmcNewMatrix();_tmcSetString(y,str); 
#endif
