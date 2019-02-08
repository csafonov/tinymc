// tmc.h
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license. 
  *****************************************************************************/
/*
   Some parts of this file (data definititions and exported functions prototypes)
   may be included in generated application provided that user has an appropriate license.
*/
#ifndef _tmc_h_
#define _tmc_h_

//#define NO_LAPACK_DLL
#ifndef  _TMC_SITARA_
#pragma warning(disable : 4028) // temporary: int and long compat
#pragma warning(disable : 4996) // unsafe
#pragma warning( disable : 4102 ) // disable warning message "unreferenced label"
#pragma warning( disable : 4554 ) // disable warning message "'<<' : check operator precedence for possible error; use parentheses to clarify precedence"
#pragma warning( disable : 4102 ) // disable warning message "unreferenced label"
#pragma warning( disable : 4723 ) // disable warning message "potential divide by 0"


#else
#define _TMC_EMBEDDED_	1
typedef	long long __int64;
#define _isnan	isnan

//typedef unsigned short wchar_t;
#define __cdecl
#include <stdlib.h>
#endif

#include <float.h>
#include <setjmp.h>
#include <stdio.h>

#ifdef _MBCS
#include <crtdbg.h>
// The following macros set and clear, respectively, given bits
// of the C runtime library debug flag, as specified by a bitmask.
#ifdef   _DEBUG
#define  SET_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#define  CLEAR_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else
#define  SET_CRT_DEBUG_FIELD(a)   ((void) 0)
#define  CLEAR_CRT_DEBUG_FIELD(a) ((void) 0)
#endif

#ifdef _DEBUG
#define _DEBUG_MEMORY
extern char dbg_buf[1000];
#endif

#else

#ifndef _BCC55_

#define NO_LAPACK_DLL
// not MSVC

#ifndef min
#define min(a,b) ((a) <= (b) ? (a) : (b))
#define max(a,b) ((a) >= (b) ? (a) : (b))
#endif

#ifndef __min
#define __min(a,b) ((a) <= (b) ? (a) : (b))
#define __max(a,b) ((a) >= (b) ? (a) : (b))
#endif

#else // borland
#define __min(a,b) ((a) <= (b) ? (a) : (b))
#define __max(a,b) ((a) >= (b) ? (a) : (b))
#endif

#endif

// For Borland C++ 5.5 compiler:
#ifdef _BCC55_
#define _CRTIMP
#ifdef _RT_EXPORT_
#define TMCDLLSPEC __declspec(dllexport)
#endif
#endif


#include "cmatrix.h"
#include "tmcstringhash.h"


#define MAX_PRINTF_LEN 5000
#define MAX_FGETS_LEN  5000

#define MAX_MATRIX_DIM	4 // maximal array dimension supported for non-recurcive indexing so far. 

#ifndef NULL
#define NULL 0
#endif

//#ifndef PI
#define dbl_constant_PI ((double)(3.1415926535897932384626433832795))
//#endif

#define tmcnargin(shum,klum,x)	tmcScalar(x,(double)nargin)
#define tmcnargout(shum,klum,x) tmcScalar(x,(double)nargout)


#define tmcAssignFalse(x) tmcScalar(x,0)
#define tmcAssignTrue(x) tmcScalar(x,1)

//#define tmcnot(shum,klum,y,x) tmcNot(y,x) // like ~

enum MATRIX_TYPES
{
	TYPE_NOTHING=-1,
	TYPE_MATRIX=0, // simple matrix
	TYPE_STRUCT=1,
	TYPE_STRING=2,
	TYPE_CELL_ARRAY=3,
	TYPE_MAGIC_COLON=4,
	TYPE_REF=5,
	TYPE_ITERATOR=7,
	TYPE_FNC_HANDLE=9
};
enum REFERENCE_TYPES
{
	REF_INDEX=100,
	REF_FIELD=101,
	REF_CELL_INDEX=102,
	REF_STRUCT_INDEX=103
};

#define MODIFIER_MASK_HAS_IM		0x0002
#define MODIFIER_MASK_NOTCOPY		0x0004
#define MODIFIER_MASK_BOOL			0x0008
#define MODIFIER_MASK_BOOL_TRUE		0x0010

#define MODIFIER_MASK_MULTI_DIM		0xF000
#define MODIFIER_SHIFTS_MULTI_DIM		12


enum HAS_IMAGINE_FLAG
{
	tmcREAL=0,
	tmcCOMPLEX=1
};
//#define MODIFIER_MASK_EMPTY			0x0004

//#define STATUS_MASK_ADDR			0x0001
//#define STATUS_MASK_HAS_IM			0x0002
//#define STATUS_MASK_IS_INDEX_REF	0x0004
//#define STATUS_MASK_IS_ITERATOR		0x0008
//#define STATUS_MASK_IS_MAGIC_COLON  0x0010
//#define STATUS_MASK_IS_FIELD_REF    0x0020
//#define STATUS_MASK_IS_STRUCT	    0x0040
//#define STATUS_MASK_IS_STRING		0x0080
//#define STATUS_MASK_IS_CELL_ARRAY	0x0100


// High 4 bits of m_modifier repesent additional dimentions of multi-dimentional matrix.
struct tag_tmcMatrixDecriptor
{
	enum	MATRIX_TYPES m_type;
	unsigned short	m_modifier;
	long	m_nRows;// first dimension size
	long	m_nCols;// multiplication of all other dimensions 
	long	*m_dims;// array of all dimentions of muli-dim matrix only
};

/// struct field descriptor
struct tag_tmsMatrix;
//struct tag_tmcField
//{
//	//char *fn;// field name
//	STRINGCODE hcfn;
//	struct tag_tmsMatrix *src; // field data
////	struct tag_tmcField *next_field; // next field in list 
//};


	struct tagForStruct
	{
	long   iterator;// for "for" implementation
	struct tag_tmsMatrix *iter_var; // for "for" implementation
	};
	struct tagReIm
	{
	double *rData;// double matrix data
	double *iData;
	};
	struct tagStructDef
	{
	STRINGCODE *hcFields;
	struct tag_tmsMatrix **m_fields; // m x n x k
	short      m_nFields;
	};


#define m_rData value.complx.rData
#define m_iData value.complx.iData

struct tag_tmsMatrix
{
	// data is stored by columns
	struct tag_tmcMatrixDecriptor m_desc;// matrix type and dimentions
	union tag_val {
	struct tagStructDef StructDef;
	struct tagReIm complx;
//	struct tag_tmcField  **m_fields; // struct field list (pointer to first field)
	struct tag_tmsMatrix **m_cells; // cells data (array of cells)
	void (*fnc_ptr)(long,long,...);
	double	    scalar_val; // value
	struct tagForStruct ForStruct;
	STRINGCODE  hcode_val; // string code
	} value;
};

#define MAX_REF_DEEP	25
#define MAX_REFS		50

struct tag_RefHelper
{
	struct tag_tmsMatrix *refI[MAX_REFS];
//	const  char *		 refFn[MAX_REFS];
	STRINGCODE		 refhcFn[MAX_REFS];
	short  nrefs; // max index in refs
	short  dims[MAX_REF_DEEP];
	char   type[MAX_REF_DEEP];
	short  ndims; // max index in dims
	struct tag_tmsMatrix *src;
};

extern struct tag_RefHelper RefHelper;// HAZARD : static struct
extern struct tag_RefHelper GetHelper;// HAZARD : static struct
extern short __Mdontcopy;

typedef struct tag_tmsMatrix  tmsMatrix ;
typedef struct tag_tmsMatrix* tmcMatrixRef ;

//extern tmsMatrix	*pRefHelper;
//extern tmsMatrix	*pGetHelper;

#define BITMAX	((double)9.007199254740991e15)	 // 2^53-1

#define _tmcIsMatrix(x) (((x->m_desc.m_nRows>1) && (x->m_desc.m_nCols>1))? 1:0 )
#define _tmcIsEmptyMatrix(x) ( (x->m_desc.m_nRows==0 ||  x->m_desc.m_nCols==0) ? 1:0)
#define _tmcHasIm(x) ((short)((x->m_desc.m_modifier & MODIFIER_MASK_HAS_IM) ? 1:0))
#define _tmcIsChar(x) ((short)(x->m_desc.m_type==TYPE_STRING))


#define _mdblIsInteger( x ) ((short)((x==floor(x)) ? 1:0))

// multi-dim structures not supported
#define _tmcGetM(x) ( ((x)->m_desc.m_type ==TYPE_STRUCT) ? 1 : (x)->m_desc.m_nRows) 
#define _tmcGetN(x) ( ((x)->m_desc.m_type ==TYPE_STRUCT) ? 1 : (x)->m_desc.m_nCols)
#define _tmcGetType(x) ((x)->m_desc.m_type)
#define _tmcGetNf(x) (((x)->m_desc.m_type ==TYPE_STRUCT) ? (x)->value.StructDef.m_nFields : 0)
#define _tmcGetExtraDim(x) (((x)->m_desc.m_modifier>>MODIFIER_SHIFTS_MULTI_DIM) ) 
#define _tmcGetNdim(x) ( (2+_tmcGetExtraDim(x)) )
#define _tmcGetDim(X,k) (  _tmcHasExtraDim(X) ?   (X)->m_desc.m_dims[(k)-1] : ((k)==1 ? _tmcGetM(X):_tmcGetN(X)  ) ) // k = 1...MAX_DIM
#define _tmcGetDimS(X,k) (  (  _tmcGetNdim(X) >=(k) ?  _tmcGetDim((X),(k)) : 1 ) )
#define _tmcSetExtraDim(x,ndim) (  (x)->m_desc.m_modifier =((x)->m_desc.m_modifier & (~MODIFIER_MASK_MULTI_DIM)) | ((ndim)<<MODIFIER_SHIFTS_MULTI_DIM)  )
#define _tmcSetDim(X,d,v) ( (X)->m_desc.m_dims[(d)]=(v)  ) // d = 0..MAX_DIM-1
#define _tmcScalarVal(X) ( ((X)->m_rData[0])  )
#define _tmcCreateDims( X,n  ) (  (X)->m_desc.m_dims=MYMALLOC(sizeof(long)*(n)) )
#define _tmcKillDims(X) (  MYFREE( (X)->m_desc.m_dims  )) 
#define _tmcHasExtraDim(x) ( ((x)->m_desc.m_modifier & MODIFIER_MASK_MULTI_DIM)  )
#define _tmcSetM(x,m) (  (x)->m_desc.m_nRows=(m) )
#define _tmcSetN(x,n) (  (x)->m_desc.m_nCols=(n) )

///////////////// INTERNAL UTILITIES /////////////////////////////
//tmsMatrix *_tmcGetByRef(tmsMatrix *x);
//void  tmcCreateVarRef(tmsMatrix *dest,tmsMatrix *src);

tmsMatrix ** tmcCreateRegFrame(long len);
void tmcFreeRegFrame(tmsMatrix **reg);

void tmcwarning(long nout,long ninput, tmsMatrix *msg_string,tmsMatrix *msg_string2);

// Exception handling, try-catch etc. 
void _tmcInstallUnhandledExceptionFilter(void);
void _tmcUninstallUnhandledExceptionFilter(void);
void tmcerror(long nout,long ninput,tmsMatrix *ydummy, tmsMatrix *msg_string);
void _tmcRaiseException(long errcode,const char *module_name,const char *func_name,const char *errmsg,long numargin,tmsMatrix *x,...);
void tmcSyntaxError(const char *msg); // run-time error
extern long _tmcDumpErrors; // 1: display error info even if catched

void tmclasterr(long nout,long ninput,tmsMatrix *msg_string_out, tmsMatrix *msg_string);

// SEH if supported only by Microsoft compiler.
// try-catch-finally for other platforms now yet is not supported
#ifndef TMC_NO_SEH
//jmp_buf tmc_mark; // HAZARD: no nesting try. Better not to use it at all. 
//#define TRY \
//{ \
//    jmp_buf _tmc_mark; \
//    if (!setjmp(_tmc_mark)) {
//
//#define CATCH \
//        \
//    } else {{ \
//
//#define ENDCATCH }}}
#define TRY \
	__try {

#define CATCH \
	} __except (1) {
#define ENDCATCH }		

#define FINALLY \
	} __finally {
#define ENDFINALLY }		
#endif

// Run-time errors
#define err_bad_index			-1
#define err_field_absent		-2
#define err_invalid_number_of_input_pars	-3
#define err_invalid_switch_exp -4
#define err_bad_cell_index -5
#define err_unsupported -6
#define err_invalid_dimentions -7
#define err_must_be_real -8
#define err_must_be_matrix -9
#define err_bad_init -10
#define file_not_found	-11
#define out_of_int_range	-12

////////////////////

double _tmcCabs(double re,double im); 

//void _tmcCreateRefObject(tmsMatrix *matres,enum REFERENCE_TYPES reftype,tmsMatrix *src,long numdims,tmcMatrixRef *refs,
//						 const char *fn);
tmsMatrix  * _tmcGetByIndexCellForce(tmsMatrix *src,long numdims,tmcMatrixRef *refs);

void _tmcResizeCellArray(tmsMatrix *matres,long numdim,long m,long n);
void _tmcForceComplexMatrix(tmsMatrix *res);
void _tmcResizeMatrix(tmsMatrix *matres,long M2,long N2,short bHasIm);
void _tmcClearMatrix(tmsMatrix *x);
void _tmcClearColumns(tmsMatrix *x,tmsMatrix *J);
void _tmcClearRows(tmsMatrix *x,tmsMatrix *I);

void _tmcCreateMatrix(tmsMatrix *res,long M,long N,short bHasImagine);
long tmcNumElem(tmsMatrix *x);
void  _tmcSetByIndex(tmsMatrix *matres,tmsMatrix *src,long numdims,tmcMatrixRef *refs);

void  tmcGetEnd(tmsMatrix *matres,tmsMatrix *src,long dim,long numdims);

short _tmcFindFieldMat(tmsMatrix **x_field,tmsMatrix *src,long ind,tmsMatrix *m_fn);
short _Mstrcmp(tmsMatrix *x,const char *fn);
tmsMatrix *_tmcGetField(tmsMatrix *S,long ind,const char *fname);

void _tmcCreateStruct(tmsMatrix *matres,long M,long N,short nfields,STRINGCODE *hcFields);
void _tmcClearStruct(tmsMatrix *matres);
void _tmcOnesFac(long nout,long ninput,tmsMatrix *Y, tmsMatrix *in1,tmsMatrix *in2,double fac);// internal



void _tmcTransposeMatrix(tmsMatrix *V,short bScalar);
void _tmcAddScalar(tmsMatrix *sum,tmsMatrix *X,tmsMatrix *sclB,short bSignX,short bSignB);
void _tmcMultByScalar(tmsMatrix *prod,tmsMatrix *X,tmsMatrix *scalarB);
short _tmcIsScalar(tmsMatrix *x);
short RealReciprocal(double *result,double D);
void _tmcLongGetMaxVal(long *max_val,long *ind_at_max,tmsMatrix *x);

//////////////////////////////////////////////////////////////////

void tmcFreeLocalVar(tmsMatrix *src);// free local var at exit
void tmcFreeRegister(tmsMatrix *src);// free register at exit if it is not a reference
void _tmcClearRegister(tmsMatrix *reg);// clear register content before reusage
void tmcReallocRegister(tmsMatrix *src);// prepare the register for re-usage

void _tmcCreateCellArray(tmsMatrix *res,long M,long N);
void tmcCreateCellEmpty(tmsMatrix *src);
void tmcCollectCellRows(tmsMatrix *matres,long numrows,tmsMatrix *a,...);
void tmcCollectCellColumns(tmsMatrix *colres,long numcols,tmsMatrix *a,...);
void _tmcCreateCellMat(tmsMatrix *y,long M,long N);
void _tmcSetCell(tmsMatrix *resmat,long ind,  tmsMatrix *a );
tmsMatrix * _tmcGetCell(tmsMatrix *X,long ind);


void tmcGetByIndexCell(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix *I1,...);
void tmcGetRefByIndexCell(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix *I1,...);
void  _tmcSetByIndexCell(tmsMatrix *matres,tmsMatrix *src,long numdims,tmcMatrixRef *refs);


void  tmcAdd(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b);
void  tmcMul(tmsMatrix *prod,tmsMatrix *a,tmsMatrix *b);
void  tmcMulScalar(tmsMatrix *prod,tmsMatrix *a,tmsMatrix *b);

void tmcAssign(tmsMatrix *dest,tmsMatrix *src);
void tmcCopyMat(tmsMatrix *dest,tmsMatrix *src);
void tmcAssignNoCopy(tmsMatrix *dest,tmsMatrix *src);
void tmcMoveMat(tmsMatrix *dest,tmsMatrix *src); // for not-modified mex only
void tmcAssignBool(tmsMatrix *matres,tmsMatrix *src);

void tmcScalar(tmsMatrix *dest,double x);
void tmcComplexScalar(tmsMatrix *dest,double xr,double xi);

tmsMatrix * __tmcNewMatrix(void);
tmsMatrix * _tmcNewMatrix_dbg(const char *filename, int linenumber);

void  tmcNeg(tmsMatrix *sum,tmsMatrix *x);
void  tmcSub(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b);

// condition check
void  tmcGt(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b);
void  tmcGe(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b);
void  tmcLt(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b);
void  tmcLe(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b);
void  tmcEq(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b);
void  tmcNe(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b);


short  tmcIsFalse(tmsMatrix *x);
short  tmcIsTrue(tmsMatrix *x);

void tmcDivScalar(tmsMatrix *divres,tmsMatrix *a,tmsMatrix *b);
void _tmcDivByScalar(tmsMatrix *divres,tmsMatrix *a,tmsMatrix *sclB,short bLeftDiv);
void tmcLeftDiv(tmsMatrix *X,tmsMatrix *A,tmsMatrix *B);
void tmcDiv(tmsMatrix *X,tmsMatrix *A,tmsMatrix *B);

void tmcCollectColumns(tmsMatrix *colres,long numcols,tmsMatrix *a,...);
void tmcCollectRows(tmsMatrix *matres,long numrows,tmsMatrix *a,...);
void tmcCreateMatrixEmpty(tmsMatrix *matres);

void tmcGetByIndex(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix *I1,...);
void tmcGetRefByIndex(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix *I1,...);

void _tmcGetByIndexStruct(tmsMatrix *matres,tmsMatrix *src,tmsMatrix **Iarr,short numdims);

// obsolete  for mex-compat
short _tmcGetFieldNumber(tmsMatrix *src,const char *fn);


// HASH
void tmcGetRefByFieldHcode(tmsMatrix *matres,tmsMatrix *src,STRINGCODE hcode);
void tmcGetByFieldHcode(tmsMatrix *matres,tmsMatrix *src,STRINGCODE hcode);
short _tmcFindField(tmsMatrix **x_field,tmsMatrix *src,long ind,STRINGCODE hcode);
tmsMatrix  * _tmcGetByFieldForce(tmsMatrix *src,long ind,STRINGCODE hcode);
//void _tmcCreateField(struct tag_tmcField **fd,STRINGCODE hcode);
void _tmcSetByField(tmsMatrix *matres,long ind,tmsMatrix *src,STRINGCODE hcode);
short _tmcRemoveField(tmsMatrix *src,STRINGCODE hcode);
void tmcIsFieldHcode(tmsMatrix *matres,tmsMatrix *src,STRINGCODE hcode); // matres=isfield(src,string(hcode))
// HASH END

////////////////////// MULTI-DIM /////////////
void _tmcCreateMatrixMD(tmsMatrix *res,short ndim,long* arrdims,short bHasImagine);
void _tmcCreateCellArrayMD(tmsMatrix *res,short ndim,long* arrdims);
void _tmcClearExtraDims(tmsMatrix *res);
long _tmcCountM(short ndim,long* arrdims);
void  _tmcSetByIndexMD(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix **refs);
void _tmcResizeMatrixMD(tmsMatrix *matres,short ndim,long* arrdims,short bHasIm);
void _tmcGetByIndexMD(tmsMatrix *matres,const tmsMatrix *src,short numdims,tmsMatrix **matN);
void _tmcRemoveSigleton(tmsMatrix *x);
void _tmcResizeCellArrayMD(tmsMatrix *y,short numdims,long *arrdims);
short _tmcGetReducedDim(short numdim,long* arrdims);
void  _tmcRedimArrayMD(tmsMatrix *matres,short numdims,long *arrdims);

/////////////////////////////////////////////

void tmcTransposeScalar(tmsMatrix *matres,tmsMatrix *src);
void tmcTranspose(tmsMatrix *matres,tmsMatrix *src);

void tmcDisplayMat(tmsMatrix *x,short bVerb);
void tmcStoreMat(FILE *fp,const char*fn,tmsMatrix *x);//temp

void tmcCreateColonBaseIncLimit(tmsMatrix *matres,tmsMatrix *base,tmsMatrix *increment,tmsMatrix *limit);
void tmcCreateColonBaseLimit(tmsMatrix *matres,tmsMatrix *base,tmsMatrix *limit);

void tmcForIterInit(tmsMatrix *iteratorM,tmsMatrix *rangeM,tmsMatrix *iterator_variableM);
short tmcForIterNext(tmsMatrix *iteratorM,tmsMatrix *rangeM);

void tmcCreateMagicColon(tmsMatrix *magcolM);
void _tmcSetMatrixEmpty(tmsMatrix *y);

void tmcCreateString(tmsMatrix *matres,const char *str);
void tmcCreateStringEmpty(tmsMatrix *matres);
char* _tmcMat2String(tmsMatrix *src);
wchar_t* _tmcMat2UniString(tmsMatrix *src);
char* _tmcMat2StringESC(tmsMatrix *src); // for usage in sprintf,fprintf only, inserts ESC-seq

void _tmcSetString(tmsMatrix *y,const char *str);
short _tmcGetString(const tmsMatrix *src , char *str_des , long maxlen );
long _dstrlen(const double *x,long maxlen);

short tmcNotCase(tmsMatrix *expression,tmsMatrix *case_value);

void tmcFncHandle(tmsMatrix *reg,void (*)(long,long,...),const char *nm);
void tmcfeval(long nout,long ninput,tmsMatrix *y, tmsMatrix *fnc_handle, tmsMatrix *x1,...);


// in-built functions ////////////////
void tmcstruct(long nout,long ninput,tmsMatrix *matres,...);
void tmcsize(long nout,long ninput,tmsMatrix *m,...);
void tmclength(long nout,long ninput, tmsMatrix *len, tmsMatrix *X);
void tmcones(long nout,long ninput,tmsMatrix *Y, tmsMatrix *in1,tmsMatrix *in2);
void tmczeros(long nout,long ninput,tmsMatrix *Y, tmsMatrix *in1,...);
void tmceye(long nout,long ninput, tmsMatrix *y, tmsMatrix *in1, tmsMatrix *in2);
void tmcndims(long nout,long ninput, tmsMatrix *y, tmsMatrix *M);
void tmccell2mat(long nout,long ninput, tmsMatrix *y, tmsMatrix *x);
void tmcnumel(long nout,long ninput, tmsMatrix *y, tmsMatrix *x);


void tmciscell(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);
void tmcisfield(long nout,long ninput,tmsMatrix *y, tmsMatrix *S, tmsMatrix *m_fn);
void tmcgetfield(long nout,long ninput, tmsMatrix *y, tmsMatrix *S, tmsMatrix *m_fn);
void tmcrmfield(long nout,long ninput, tmsMatrix *y, tmsMatrix *S, tmsMatrix *m_fn);
void tmcischar(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);
void tmccell(long nout,long ninput,tmsMatrix *Y, tmsMatrix *in1,...);
void tmcsetfield(long nout,long ninput, tmsMatrix *y, tmsMatrix *S, tmsMatrix *m_fn,tmsMatrix *v);
void tmcorderfields(long nout,long ninput, tmsMatrix *ne, tmsMatrix *pe, tmsMatrix *S1,tmsMatrix *S2);


void tmcnargchk(long nout,long ninput, tmsMatrix *message, tmsMatrix *low, tmsMatrix *high,tmsMatrix *n);

void tmcdeal(long nout,long ninput,tmsMatrix *y,... );


void tmcisequal(long nout,long ninput,tmsMatrix *res,tmsMatrix *x1,...);

void tmcisempty(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);
void tmcfieldnames(long nout,long ninput,tmsMatrix *flist,tmsMatrix *S);
void tmcfields(long nout,long ninput,tmsMatrix *flist,tmsMatrix *S);

void tmcstrcmp(long nout,long ninput, tmsMatrix *y,tmsMatrix *s1,tmsMatrix *s2);
void tmcdiff(long nout,long ninput, tmsMatrix *dx,tmsMatrix *x);
void tmcfind(long nout,long ninput, tmsMatrix *I,tmsMatrix *J,tmsMatrix *V, tmsMatrix *x,tmsMatrix *Opt,tmsMatrix *sOpt);
void tmcsum(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcprod(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcimag(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcconj(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);



void tmcreal(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcmin(long nout,long ninput, tmsMatrix *y,tmsMatrix *I,tmsMatrix *x1,tmsMatrix *x2,tmsMatrix *d);
void tmcmax(long nout,long ninput, tmsMatrix *y,tmsMatrix *I,tmsMatrix *x1,tmsMatrix *x2,tmsMatrix *d);
void tmcisstruct(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);
void tmcsort(long nout,long ninput, tmsMatrix *y1,tmsMatrix *y2,tmsMatrix *x,tmsMatrix *c);
void tmcisscalar(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcisvector(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcall(long nout,long ninput, tmsMatrix *y,tmsMatrix *x,tmsMatrix *dim_a);
void tmcany(long nout,long ninput, tmsMatrix *y,tmsMatrix *x,tmsMatrix *dim_a);
void tmcisfinite(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcisnan(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcisnumeric(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcfliplr(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcisreal(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcsign(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcinv(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcdiag(long nout,long ninput,tmsMatrix *y,tmsMatrix *d);
void tmccumprod(long nout,long ninput,tmsMatrix *y,tmsMatrix *x,tmsMatrix *dim);
void tmcsqueeze(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);

// MATH UTILS //////////////////////////
void tmcmod(long nout,long ninput,tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2);
void tmcrem(long nout,long ninput,tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2);
void tmccos(long nout,long ninput,tmsMatrix *matres,tmsMatrix *x);
void tmcsin(long nout,long ninput,tmsMatrix *matres,tmsMatrix *x);
void tmctan(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcpolyval(long nout,long ninput,tmsMatrix *y,tmsMatrix *p,tmsMatrix *x);
void tmclog10(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);
void tmclog(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);
void tmcexp(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);
void tmcabs(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcangle(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcsqrt(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcatan(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcatan2(long nout,long ninput, tmsMatrix *y,tmsMatrix *xs,tmsMatrix *xc);
void tmcasin(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcacos(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);

void tmcfloor(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcfix(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcceil(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcround(long nout,long ninput, tmsMatrix *y,tmsMatrix *x);
void tmcunwrap(long nout,long ninput, tmsMatrix *y,tmsMatrix *x,tmsMatrix *mrange);
void tmclogspace(long nout,long ninput, tmsMatrix *y, tmsMatrix *x1, tmsMatrix *x2,tmsMatrix *nP);
void tmclinspace(long nout,long ninput, tmsMatrix *y, tmsMatrix *x1, tmsMatrix *x2,tmsMatrix *nP);
void tmcdeconv(long nout,long ninput, tmsMatrix *q, tmsMatrix *r, tmsMatrix *v,tmsMatrix *u);
void tmcinterp1(long nout,long ninput, tmsMatrix *yi, tmsMatrix *x, tmsMatrix *y, tmsMatrix *xi,tmsMatrix *typeinter,tmsMatrix *typeextr);

void tmcconv(long nout,long ninput, tmsMatrix *C, tmsMatrix *A, tmsMatrix *B);
void tmcnorm(long nout,long ninput, tmsMatrix *y, tmsMatrix *X, tmsMatrix *n);


// SET Utils
void tmcunique(long nout,long ninput, tmsMatrix *y, tmsMatrix *I,tmsMatrix *J,tmsMatrix *x);
void tmcsetdiff(long nout,long ninput, tmsMatrix *y, tmsMatrix *I,tmsMatrix *A,tmsMatrix *B,tmsMatrix *rs);
void tmcintersect(long nout,long ninput, tmsMatrix *y, tmsMatrix *I,tmsMatrix *J,tmsMatrix *A,tmsMatrix *B);
void tmcismember(long nout,long ninput, tmsMatrix *y, tmsMatrix *A,tmsMatrix *S);

// operators
void tmcPowerScalar(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2); // y=src1.^src2
void tmcPower(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2); // y=src1^src2
void tmcAndBoolean(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2);
void tmcOrBoolean(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2);
void tmcNot(tmsMatrix *matres,tmsMatrix *src);

void tmcAndScalar(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2);
void tmcOrScalar(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2);

// graphic stubs
void tmchold(long nout,long ninput,tmsMatrix *ydummy,tmsMatrix *onoff);
void tmcgrid(long nout,long ninput,tmsMatrix *ydummy,tmsMatrix *onoff);
void tmcfigure(long nout,long ninput,tmsMatrix *fhand,tmsMatrix *fnum);
void tmcgcf(long nout,long ninput,...);
void tmcishold(long nout,long ninput,tmsMatrix *y,tmsMatrix *fhan);

void tmcget(long nout,long ninput,tmsMatrix *val,tmsMatrix *obj,tmsMatrix *prop);
void tmcwaitbar(long nout,long ninput,tmsMatrix *hand,tmsMatrix *frac, tmsMatrix *title,tmsMatrix *pt1,tmsMatrix *pv1,tmsMatrix *pt2,tmsMatrix *pv2);
void tmcclose(long nout,long ninput,tmsMatrix *stat,tmsMatrix *hand);
void tmcaxis(long nout,long ninput,tmsMatrix *hand,...);
void tmcgca(long nout,long ninput,tmsMatrix *hand);
void tmcset(long nout,long ninput,tmsMatrix *stat,tmsMatrix *obj,tmsMatrix *pt,tmsMatrix *pv,...);
void tmcylabel(long nout,long ninput,tmsMatrix *hand, tmsMatrix *title);
void tmcxlabel(long nout,long ninput,tmsMatrix *hand, tmsMatrix *title);
void tmcfill(long nout,long ninput,tmsMatrix *hand, tmsMatrix *x, tmsMatrix *y, tmsMatrix *c);
void tmcplot(long nout,long ninput, tmsMatrix *hand, tmsMatrix *x, tmsMatrix *y, tmsMatrix *c,...);
void tmctext(long nout,long ninput, tmsMatrix *hand, tmsMatrix *x1,...);
void tmctitle(long nout,long ninput, tmsMatrix *hand,tmsMatrix *str,...);
void tmcsubplot(long nout,long ninput, tmsMatrix *hand,tmsMatrix *x1,...);

// Text output
void tmcdisp(long nout,long ninput,tmsMatrix *ydummy,tmsMatrix *x);
void tmcfopen(long nout,long ninput,tmsMatrix *h,tmsMatrix *fname,tmsMatrix *perm);
void tmcfclose(long nout,long ninput,tmsMatrix *ydummy,tmsMatrix *h);
void tmcfprintf(long nout,long ninput, tmsMatrix *fm,...);
void tmcsprintf(long nout,long ninput, tmsMatrix *sbuf,tmsMatrix *fm,...);
void tmcnum2str(long nout,long ninput,tmsMatrix *sbuf, tmsMatrix *x, tmsMatrix *fm);
void tmcfgetl(long nout,long ninput,tmsMatrix *str,tmsMatrix *h);
void tmcfgets(long nout,long ninput,tmsMatrix *str,tmsMatrix *h);
void tmcfeof(long nout,long ninput,tmsMatrix *y,tmsMatrix *h);

// system utilities
void tmcpause(long nout,long ninput,tmsMatrix *ydummy,tmsMatrix *d);
void tmcexist(long nout,long ninput,tmsMatrix *y,tmsMatrix *x,tmsMatrix *mtype);//not supported

// Legacy input/output functions
void tmcload(long nout,long ninput,tmsMatrix *W,tmsMatrix *fn,...);
void tmcsave(long nout,long ninput,tmsMatrix *filename,tmsMatrix *Mat1,char *varname1,...);

// Conversion utilities
void tmcstr2num(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);
void tmchex2dec(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);
void tmcdec2hex(int nargout, int nargin,tmsMatrix *y,tmsMatrix *x,tmsMatrix *n);
void tmclower(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);
void tmcchar(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);
void tmcdouble(long nout,long ninput,tmsMatrix *y,tmsMatrix *x);


// String manipulations
void tmcfindstr(long nout,long ninput,tmsMatrix *K,tmsMatrix *S1,tmsMatrix *S2);
void tmcstrfind(long nout,long ninput,tmsMatrix *K,tmsMatrix *sTEXT,tmsMatrix *sPATTERN);

// bit operations
void tmcbitand(long nout,long ninput,tmsMatrix *y,tmsMatrix *a,tmsMatrix *b);
void tmcbitor(long nout,long ninput,tmsMatrix *y,tmsMatrix *a,tmsMatrix *b);
void tmcbitshift(long nout,long ninput,tmsMatrix *y,tmsMatrix *a,tmsMatrix *k,tmsMatrix *n);



// UNSUPPORTED
void tmceval(long nout,long ninput,tmsMatrix *ydummy, tmsMatrix *str);
void tmcssdata(long nout,long ninput,...);
void tmcss2tf(long nout,long ninput,...);
void tmctf2ss(long nout,long ninput,...);
void tmcss(long nout,long ninput,...);
void tmczpkdata(long nout,long ninput,...);
void tmczpk(long nout,long ninput,tmsMatrix *y,tmsMatrix *z,tmsMatrix *p,tmsMatrix *k,tmsMatrix *tsamp);
void tmcfrd(long nout,long ninput,tmsMatrix *y,tmsMatrix *Resp,tmsMatrix *Freqs);

void tmctf(long nout,long ninput,...);
void tmcget(long nout,long ninput, tmsMatrix *y, tmsMatrix *S, tmsMatrix *str);
void tmcisa(long nout,long ninput,tmsMatrix *y, tmsMatrix *x, tmsMatrix *str);
void tmctfdata(long nout,long ninput, tmsMatrix *num, tmsMatrix *den,tmsMatrix *tsamp, tmsMatrix *sys,tmsMatrix *mopt);
void tmcfreqresp(long nout,long ninput, tmsMatrix *y, tmsMatrix *sys,tmsMatrix *w);
void tmcfrdata(long nout,long ninput, tmsMatrix *num, tmsMatrix *den,tmsMatrix *tsamp, tmsMatrix *sys,tmsMatrix *mopt);
void tmcnichols(long nout,long ninput,tmsMatrix *sys,tmsMatrix *mopt);

void tmcfrdqfd(long nout,long ninput,tmsMatrix *sys,tmsMatrix *L,tmsMatrix *Freqs);

//lapackutils
void tmcsvd(long nout,long ninput,tmsMatrix *U,tmsMatrix *S,tmsMatrix *V,tmsMatrix *X,tmsMatrix *flag);
void _tmcRealLeftDiv(tmsMatrix *X,tmsMatrix *A,tmsMatrix *B);
void _tmcComplexLeftDiv(tmsMatrix *X,tmsMatrix *A,tmsMatrix *B);

void tmcfft(long nout,long ninput,tmsMatrix *out,tmsMatrix *in);
void tmceig(long nout,long ninput,tmsMatrix *out1,tmsMatrix *out2,tmsMatrix *in1,tmsMatrix *in2,tmsMatrix *in3);
void tmcroots(long nout,long ninput,tmsMatrix *r,tmsMatrix *p);
void tmcqr(long nout,long ninput,tmsMatrix *q,tmsMatrix *r,tmsMatrix *e,tmsMatrix *A,tmsMatrix *flg);
void tmcdet(long nout,long ninput,tmsMatrix *y,tmsMatrix *A);
void tmccond(long nout,long ninput,tmsMatrix *y,tmsMatrix *A,tmsMatrix *p);
void tmcpoly(long nout,long ninput,tmsMatrix *y,tmsMatrix *A);

// special routines
void tmcrand(long nout,long ninput,tmsMatrix *y,tmsMatrix *m,tmsMatrix *n);


// VM features
void *my_malloc_dbg( size_t size,const char *filename, int linenumber  );
void *my_malloc( size_t size);
void  mmy_free( void *memblock );

// elementary constants
//#define tmci	tmcj
//#define tmcj(shum,klum,x) tmcComplexScalar(x,0,1)
//#define tmcpi(shum,klum,x) tmcScalar(x,PI)
//#define tmcinf(shum,klum,x) tmcScalar(x,DBL_MAX) // like 1/0
//#define tmcNaN(shum,klum,x) tmcScalar(x,DBL_MAX) // like 0/0
//#define tmceps(shum,klum,x) tmcScalar(x,DBL_EPSILON)
void tmcinf(long nout,long ninput,tmsMatrix *dest);// like 1/0
void tmcNaN(long nout,long ninput,tmsMatrix *dest);// like 0/0
void tmceps(long nout,long ninput,tmsMatrix *dest,tmsMatrix *R);
void tmcpi(long nout,long ninput,tmsMatrix *dest);
void tmcj(long nout,long ninput,tmsMatrix *dest);
void tmci(long nout,long ninput,tmsMatrix *dest);

//#ifndef MATLAB_MEX_FILE
//_CRTIMP void   __cdecl mmy_free( void *memblock );
//#endif

// switch-case support
void tmcCalcSwitchExpVal(tmsMatrix *expr_code,tmsMatrix *x);
short tmcIsCaseString(tmsMatrix *expr_code,STRINGCODE n);
short tmcIsCaseDouble(tmsMatrix *expr_code,double x);

//#include "..\MatExSrc\External_func.h" // temporary

#ifdef _DEBUG_MEMORY
#define MYMALLOC(x)	my_malloc_dbg(x,__FILE__, __LINE__)
#ifndef MATLAB_MEX_FILE
#define MYFREE	mmy_free
#endif
#define tmcNewMatrix() _tmcNewMatrix_dbg(__FILE__, __LINE__) 
#else
#define MYMALLOC(x)	my_malloc(x)
#ifndef MATLAB_MEX_FILE
#define MYFREE	mmy_free
#endif
#define tmcNewMatrix() __tmcNewMatrix() 
#endif

// global initialization routines
struct CInit_funcs_table
{
	const struct CInitHashData* pInitHashData;
	const long* pInitHashDataLen;
	void (*InitGlobals)(void);
	void (*FreeGlobals)(void);
	tmsMatrix	**ppRefHelper;
	tmsMatrix	**ppGetHelper;
};
//const struct CInit_funcs_table Init_funcs_table = { InitHashData,&InitHashDataLen,tmcInitGlobals,tmcFreeGlobals  };
extern const struct CInit_funcs_table Init_funcs_table;


void tmcInitGlobals(void);
void tmcFreeGlobals(void);


short tmcInitLib(const struct CInit_funcs_table *pInit_funcs_table);
short tmcFreeLib(void);

#undef PI // for QFD-style which frequently uses PI as proportional-integral

#include "tmcdebugger.h"
// for debugging
void tmcDisplayMatF(FILE *fp,tmsMatrix *x,short bVerb);
#endif
