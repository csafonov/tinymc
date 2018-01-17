/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
// symbols dictionary and files list
#ifndef _tmclsp_matrix_h_
#define _tmclsp_matrix_h_

// common and parser structures
#define MYMALLOC(x) malloc(x)

typedef char LSP_IDENT[1024];
enum CONST_VAL_TYPES
{
	const_val_real=0,
	const_val_complex=1,
	const_val_ident=2,
	const_val_str=3,
	const_val_empty_matrix=4,
	const_val_empty_cell=5,
	const_val_mag_col=6
};
struct ComplexVal
{
	double re;
	double im;
};

struct tree_const_val
{
    enum CONST_VAL_TYPES const_val_type;
	union u_const_val
	{
	ComplexVal num;
	char   *str;
	LSP_IDENT   ident;
	} const_val;
};
// data structures
enum MATRIX_TYPES
{
	TYPE_NOTHING=-1,
	TYPE_MATRIX=0, // simple matrix
	TYPE_STRUCT=1,
	TYPE_STRING=2,
	TYPE_CELL_ARRAY=3,
	TYPE_MAGIC_COLON=4,
//	TYPE_REF=5,
	TYPE_ITERATOR=7,
	TYPE_FNC_HANDLE=9,
};
#define MODIFIER_MASK_HAS_IM		0x0002
#define MODIFIER_MASK_NOTCOPY		0x0004
#define MODIFIER_MASK_BOOL			0x0008
#define MODIFIER_MASK_BOOL_TRUE		0x0010
enum HAS_IMAGINE_FLAG
{
	tmcREAL=0,
	tmcCOMPLEX=1
};
	struct tagReIm
	{
	double *rData;// double matrix data
	double *iData;
	};
#define m_rData value.complx.rData
#define m_iData value.complx.iData
struct tag_tmcMatrixDecriptor
{
	enum	MATRIX_TYPES m_type;
	short	m_modifier;
	long	m_nRows;
	long	m_nCols;
};
struct tag_tmsMatrix
{
	// data is stored by columns
	struct tag_tmcMatrixDecriptor m_desc;// matrix type and dimentions
	union tag_val {
//	struct tagStructDef StructDef;
	struct tagReIm complx;
	struct tag_tmsMatrix **m_cells; // cells data (array of cells)
//	void (*fnc_ptr)(long,long,...);
	double	    scalar_val; // value
//	struct tagForStruct ForStruct;
//	STRINGCODE  hcode_val; // string code
	} value;
};
//#define tmcIsEmptyMatrix(x) ( (x.m_desc.m_nRows==0 ||  x.m_desc.m_nCols==0) ? 1:0)
//#define tmcHasIm(x) ((short)((x.m_desc.m_modifier & MODIFIER_MASK_HAS_IM) ? 1:0))
//#define tmcIsChar(x) ((short)(x.m_desc.m_type==TYPE_STRING))
//#define mdblIsInteger( x ) ((short)((x==floor(x)) ? 1:0))
// multi-dim structures not supported
//#define tmcGetM(x) ( (x.m_desc.m_type ==TYPE_STRUCT) ? 1 : x.m_desc.m_nRows) 
//#define tmcGetN(x) ( (x.m_desc.m_type ==TYPE_STRUCT) ? 1 : x.m_desc.m_nCols)
//#define tmcGetType(x) (x.m_desc.m_type)
//#define tmcGetNf(x) ((x.m_desc.m_type ==TYPE_STRUCT) ? x.value.StructDef.m_nFields : 0)

#define _tmcIsMatrix(x) (((x->m_desc.m_nRows>1) && (x->m_desc.m_nCols>1))? 1:0 )
#define _tmcIsEmptyMatrix(x) ( (x->m_desc.m_nRows==0 ||  x->m_desc.m_nCols==0) ? 1:0)
#define _tmcHasIm(x) ((short)((x->m_desc.m_modifier & MODIFIER_MASK_HAS_IM) ? 1:0))
#define _tmcIsChar(x) ((short)(x->m_desc.m_type==TYPE_STRING))
#define _tmcIsMagicColon(x) ((short)(x->m_desc.m_type==TYPE_MAGIC_COLON))
#define _tmcIsMatrixArray(x) ((short)(x->m_desc.m_type==TYPE_MATRIX))
#define _tmcIsCellArray(x) ((short)(x->m_desc.m_type==TYPE_CELL_ARRAY))


#define _mdblIsInteger( x ) ((short)((x==floor(x)) ? 1:0))
// multi-dim structures not supported
#define _tmcGetM(x) ( (x->m_desc.m_type ==TYPE_STRUCT) ? 1 : x->m_desc.m_nRows) 
#define _tmcGetN(x) ( (x->m_desc.m_type ==TYPE_STRUCT) ? 1 : x->m_desc.m_nCols)
#define _tmcGetType(x) (x->m_desc.m_type)
#define _tmcGetNf(x) ((x->m_desc.m_type ==TYPE_STRUCT) ? x->value.StructDef.m_nFields : 0)

typedef struct tag_tmsMatrix  tmsMatrix ;

std::string tmcPrintMatrix(tmsMatrix *x);
std::string tmcPrintMatrixType(tmsMatrix *x);
void AssignMtoStr(std::string& str,tmsMatrix *src);
const char* _tmcMat2String(tmsMatrix *src);

void tmcScalar(tmsMatrix *dest,double x);
void tmcComplexScalar(tmsMatrix *dest,double xr,double xi);
void tmcReallocRegister(tmsMatrix *src);
void _tmcCreateMatrix(tmsMatrix *res,long M,long N,short bHasImagine);
void _tmcCreateCellArray(tmsMatrix *res,long M,long N);
void _tmcClearRegister(tmsMatrix *x);
void tmcCreateString(tmsMatrix *matres,const char *str);
void _tmcSetString(tmsMatrix *y,const char *str);
void tmcCreateMagicColon(tmsMatrix *magcolM);
tmsMatrix * __tmcNewMatrix(void);
void tmcFreeRegister(tmsMatrix *src);
void _tmcSetMatrixEmpty(tmsMatrix *y);
#endif