#ifndef _tmc_lib_h_
#define _tmc_lib_h_

#define tmcNewMatrix __tmcNewMatrix
#define _tmcHasIm(x) ((short)((x->m_desc.m_modifier & MODIFIER_MASK_HAS_IM) ? 1:0))

#define _tmcGetM(x) ( ((x)->m_desc.m_type ==TYPE_STRUCT) ? 1 : (x)->m_desc.m_nRows) 
#define _tmcGetN(x) ( ((x)->m_desc.m_type ==TYPE_STRUCT) ? 1 : (x)->m_desc.m_nCols)

#define _tmcNumElem(x)  ( _tmcGetM(x)* _tmcGetN(x))

 	typedef unsigned long STRINGCODE;
	struct CInitHashData
	{
		const char *str;
		const STRINGCODE	hc;
	};

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
	TYPE_FNC_HANDLE=9,
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

short tmcInitLib(const struct CInit_funcs_table *pInit_funcs_table);
short tmcFreeLib(void);

//tmsMatrix * __tmcNewMatrix(void);
void tmcDisplayMat(tmsMatrix *x,short bVerb);
void tmcScalar(tmsMatrix *dest,double x);
void tmcComplexScalar(tmsMatrix *dest,double xr,double xi);
//void tmcFreeLocalVar(tmsMatrix *src);// free local var at exit

// internals
void tmcdisp(long nout,long ninput,tmsMatrix *x);
void tmcAssign(tmsMatrix *dest,tmsMatrix *src);

// temporary
tmsMatrix ** tmcCreateRegFrame(long len);
void tmcFreeRegFrame(tmsMatrix **reg);

long tmcNumElem(tmsMatrix *x);

//void _tmcCreateMatrix(tmsMatrix *res,long M,long N,short bHasImagine);
//void tmcCreateString(tmsMatrix *matres,const char *str);

#endif
