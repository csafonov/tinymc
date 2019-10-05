/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 File may be used in the generated application
  *****************************************************************************/
// File: mex2tmc.h

//Purpose: some useful macros to simplify manual conversion mex-file src-files
// to tmc-standart.
// Common mex-tmc-function format is:
//  void tmcFuncName(long nlhs,long nrhs,tmsMatrix *lhsMatrix1,..tmsMatrix *lhsMatrixM, tmsMatrix *rhsMatrix1,..tmsMatrix *rhsMatrixN,)
// that replaces
// void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray*prhs[] )
//
// You must replace plhs[n] by lhsMatrixn and prhs[n] by rhsMatrixn
// You _tmcCreateMatrix() to create result plhs[n] matrixes.

#ifndef _mex2tmc_h_
#define _mex2tmc_h_


//#define mexErrMsgTxt(x) {fprintf(stderr,x);	_tmcRaiseException(err_unsupported,"MEX","error in MEX.","error in MEX.",0,NULL);}
#define mexErrMsgTxt(x) {fprintf(stderr,"%s",x);	_tmcRaiseException(err_unsupported,"MEX","error in MEX.","error in MEX.",0,NULL);}
#define mexErrMsgTxtW(x) {fwprintf(stderr,L"%s",x);	_tmcRaiseException(err_unsupported,"MEX","error in MEX.","error in MEX.",0,NULL);}
#define mxGetM(x) _tmcGetM(x)
#define mxGetN(x) _tmcGetN(x)

#define mxGetPr(x)	(x->m_rData)
#define mxGetPi(x)	(x->m_iData)

#define mxGetString _tmcGetString
#define mxGetStringW _tmcGetStringW

//#define mxSetCell	_tmcSetCell
//#define mxGetCell   _tmcGetCell
#define mxSetCell(resmat,ind,a) ((resmat)->value.m_cells[ind]=a)
#define mxGetCell(X,ind) ((X)->value.m_cells[ind])


#define mxGetField	_tmcGetField
#define _tmcCreateCellMat _tmcCreateCellArray
#define mxGetNumberOfElements tmcNumElem

#define mxIsEmpty			_tmcIsEmptyMatrix
#define mxIsChar			_tmcIsChar
#define mxArrayToString		_tmcMat2String
#define mxFree				MYFREE

#define	mexPrintf			printf

#define mxIsComplex _tmcHasIm

#define mxIsStruct(x) (((x)->m_desc.m_type ==TYPE_STRUCT))

#define mxGetFieldNumber _tmcGetFieldNumber
#define mxCalcSingleSubscript _tmcCalcSingleSubscript

#endif
