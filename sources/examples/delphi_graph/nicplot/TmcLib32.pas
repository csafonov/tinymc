(*  Interface for TMC run-time *)
unit TmcLib32;

interface
 type
 (*

struct tag_tmcMatrixDecriptor
{
	enum	MATRIX_TYPES m_type;
	unsigned short	m_modifier;
	long	m_nRows;// first dimension size
	long	m_nCols;// multiplication of all other dimensions
	long	*m_dims;// array of all dimentions of muli-dim matrix only
};

 struct tag_tmsMatrix
{
	// data is stored by columns
	struct tag_tmcMatrixDecriptor m_desc;// matrix type and dimentions
	union tag_val {
	struct tagStructDef StructDef;
	struct tagReIm complx;
	struct tag_tmsMatrix **m_cells; // cells data (array of cells)
	void (*fnc_ptr)(long,long,...);
	double	    scalar_val; // value
	struct tagForStruct ForStruct;
	STRINGCODE  hcode_val; // string code
	} value;
};
*)
      tmcMatrixDecriptor   =record
        m_type : Integer;
	      m_modifier : ShortInt;
	      m_nRows : Integer;// first dimension size
	      m_nCols : Integer;// multiplication of all other dimensions
	      m_dims : ^Integer;// array of all dimensions of muli-dim matrix only
       end;
        tagReIm  = record
           rData: array of Double;
           iData: array of Double;
        end;

     (* type for output matrix. So far only numeric array is supported *)
     TmcMatrix = record
        m_desc :   tmcMatrixDecriptor;
        align1 : Integer;
        complx :   tagReIm;
     end;
     PTmcMatrix = ^TmcMatrix;
     (* exported functions *)
     function __tmcNewMatrix: PTmcMatrix;cdecl; external 'tmcruntime_mingw_w32.dll';
     procedure tmcScalar(dest:PTmcMatrix;x:Double);cdecl; external 'tmcruntime_mingw_w32.dll';
     procedure tmcFreeLocalVar(src:PTmcMatrix) ;cdecl; external 'tmcruntime_mingw_w32.dll';
     function  tmcNumElem(x:PTmcMatrix):Integer;cdecl; external 'tmcruntime_mingw_w32.dll';
     (* additional exports *)
     function   tmcGetM(x:PTmcMatrix):Integer;cdecl; external 'tmcruntime_mingw_w32.dll';
     function   tmcGetN(x:PTmcMatrix):Integer;cdecl; external 'tmcruntime_mingw_w32.dll';
     function   tmcGetType(x:PTmcMatrix):Integer;cdecl; external 'tmcruntime_mingw_w32.dll';
     function   tmcHasIm(x:PTmcMatrix):ShortInt;cdecl; external 'tmcruntime_mingw_w32.dll';
     function   tmcScalarVal(x:PTmcMatrix):Double;cdecl; external 'tmcruntime_mingw_w32.dll';
     function   tmcMatrixValRe(x:PTmcMatrix;m,n:Integer):Double;cdecl; external 'tmcruntime_mingw_w32.dll';
     function   tmcMatrixValIm(x:PTmcMatrix;m,n:Integer):Double;cdecl; external 'tmcruntime_mingw_w32.dll';
     function   tmcMatrixPRe(x:PTmcMatrix):PDouble;cdecl; external 'tmcruntime_mingw_w32.dll';
     function   tmcMatrixPIm(x:PTmcMatrix):PDouble;cdecl; external 'tmcruntime_mingw_w32.dll';

implementation

end.
