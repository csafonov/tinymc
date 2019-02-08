// tmclib.c
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license. 
  *****************************************************************************/

#ifndef _BCC55_
#ifndef _TMCRTVC6_
//#pragma comment(lib,"..\\bin\\fdlibm.lib")
#endif
#endif

#ifndef  _TMC_EMBEDDED_
#include <windows.h>
#endif

#include "tmc.h"
#include "clapack_types.h"



#include  <math.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h> // ANSI compatibility

#include <stdio.h>
#ifndef  _TMC_EMBEDDED_
#include <malloc.h>
#endif

#include <ctype.h>



//#include <stdlib.h>

//char dbg_buf[1000];
//char dbg_buf2[1000];

static char *s_module="tmclib.c";

struct tag_RefHelper RefHelper;
struct tag_RefHelper GetHelper;

//tmsMatrix	*pRefHelper;
//tmsMatrix	*pGetHelper;
short __Mdontcopy;


struct CInit_funcs_table local_Init_funcs_table;

extern short CloseTmcgra(void);


short tmcInitLib(const struct CInit_funcs_table *pInit_funcs_table)
{
#ifndef  _TMC_EMBEDDED_
	FILE *fp;
#endif
//	const char *str;
//	long ff;

	srand(1);

	memcpy(&local_Init_funcs_table,pInit_funcs_table,sizeof(struct CInit_funcs_table));

	_tmcDumpErrors =0 ; // by default dont print additional error information.


	_tmcInstallUnhandledExceptionFilter();

	InitStringHash();
//	fp = fopen("hash_init.dat","r");
//	load_hash_table(fp);  // temp
//	fclose(fp);

// LOAD_HASH
	load_hash_table_const(local_Init_funcs_table.pInitHashData,*local_Init_funcs_table.pInitHashDataLen); // copy from contants
#ifndef  _TMC_EMBEDDED_
	fp = fopen("hash_initx.dat","w");
	print_hash_table(fp);
	fclose(fp);
#endif
//
//	ff= string2hcode("ByRL");
//	fprintf(stderr,"0x%08x\n",ff);

	*local_Init_funcs_table.ppRefHelper =tmcNewMatrix();
	*local_Init_funcs_table.ppGetHelper=tmcNewMatrix();

//	str = hcode2string(0xd0f10000);
//	fprintf(stderr,"%s\n",str);

	(*local_Init_funcs_table.ppRefHelper)->m_desc.m_type = TYPE_REF;
	(*local_Init_funcs_table.ppGetHelper)->m_desc.m_type = TYPE_REF;

	__Mdontcopy=0;
	//tmcInitGlobals();
	local_Init_funcs_table.InitGlobals();
return 0;	
}
short tmcFreeLib(void)
{
	CloseTmcgra();

	tmcFreeRegister((*local_Init_funcs_table.ppGetHelper) );
	tmcFreeRegister((*local_Init_funcs_table.ppRefHelper) );//hazard
	local_Init_funcs_table.FreeGlobals();

	DestroyStringHash();
	_tmcUninstallUnhandledExceptionFilter();
	

return 0;
}

long   framestack[100];
short  frameptr=0;

tmsMatrix ** tmcCreateRegFrame(long len)
{
	long k;
	if (len>0)
	{
		tmsMatrix *data=(tmsMatrix *)MYMALLOC(sizeof(struct tag_tmsMatrix)*len);
		tmsMatrix ** reg=(tmsMatrix **)MYMALLOC(sizeof(struct tag_tmsMatrix *)*len);
		memset(data,0,sizeof(tmsMatrix)*len);
		for (k=0;k<len;k++)
		{
			reg[k]=&data[k];
			reg[k]->m_desc.m_type=TYPE_NOTHING;
			reg[k]->m_desc.m_modifier=0;
		}
    framestack[frameptr++]=len;
	return reg;
	}
	else
	{
    framestack[frameptr++]=0;
	return NULL;
	}
}
void tmcFreeRegFrame(tmsMatrix **reg)
{
	long k;
	long len;
	len=framestack[--frameptr];
	if (len>0)
	{
		for (k=0;k<len;k++)
			_tmcClearRegister(reg[k]);

		MYFREE(reg[0]);
		MYFREE(reg);
	}
}

void tmcStoreMat(FILE *fp,const char*vecName,tmsMatrix *x)
{
	if(_tmcHasIm(x)==0)
		Store2MatFile(fp ,vecName,x->m_rData,_tmcGetM(x),_tmcGetN(x));
	else
		StoreComplex2MatFile(fp ,vecName,x->m_rData,x->m_iData,_tmcGetM(x),_tmcGetN(x));

}

short _tmcIsScalar(tmsMatrix *x)
{
	if ((x->m_desc.m_nRows==1) && (x->m_desc.m_nCols==1))
		return 1;
	else
		return 0;
}


void _tmcForceComplexMatrix(tmsMatrix *res)
{ // if  already has imagine part - do nothing
	if ((res->m_desc.m_modifier & MODIFIER_MASK_HAS_IM)==0)
	{

		res->m_iData = (double*)MYMALLOC(res->m_desc.m_nRows*res->m_desc.m_nCols*sizeof(double));
		memset(res->m_iData,0,res->m_desc.m_nRows*res->m_desc.m_nCols*sizeof(double));
		res->m_desc.m_modifier |=MODIFIER_MASK_HAS_IM;
	}
}

void _tmcResizeMatrix(tmsMatrix *matres,long M2,long N2,short bHasIm)
{
double *temp;
long ind;
long L;
long M,N;
long cntm,cntn;
long M3,N3;

		M=_tmcGetM(matres);
		N=_tmcGetN(matres);
		L=tmcNumElem(matres);


		if (L>0)
		{
//hskost13.08.2012 BUG	
		// new matrix size
		M3=__max(M2,M);
		N3=__max(N2,N);

			// must resize existing
			temp = matres->m_rData; // old data
			matres->m_rData =MYMALLOC(sizeof(double)*M3*N3); // new room
			memset(matres->m_rData,0,sizeof(double)*M3*N3);//HAZARD_OPTIMIZE
			matres->m_desc.m_nCols=N3;
			matres->m_desc.m_nRows=M3;

			// put back old data
			// the matrix data is according column. Go through old columns now:
			ind=0;
			for(cntn=0;cntn<N;cntn++)
			{
				for(cntm=0;cntm<M;cntm++)
				{
					matres->m_rData[cntn*M3+cntm]=temp[ind++];
				}
			}
			MYFREE(temp);// MYFREE old data
			if (_tmcHasIm(matres))
			{
				temp = matres->m_iData; // old data
				matres->m_iData =MYMALLOC(sizeof(double)*M3*N3); // new room
				memset(matres->m_iData,0,sizeof(double)*M3*N3);//HAZARD_OPTIMIZE
				// put back old data
				ind=0;
				for(cntn=0;cntn<N;cntn++)
				{
					for(cntm=0;cntm<M;cntm++)
					{
						matres->m_iData[cntn*M3+cntm]=temp[ind++];
					}
				}
				MYFREE(temp);// MYFREE old data
			}


		}
		else
		{
			M3=M2;N3=N2;
			// create new
			matres->m_rData=MYMALLOC(sizeof(double)*M2*N2);
			matres->m_desc.m_type=TYPE_MATRIX;
			memset(matres->m_rData,0,sizeof(double)*M2*N2);//HAZARD_OPTIMIZE
			matres->m_desc.m_nCols=N3;
			matres->m_desc.m_nRows=M3;

		}
/* HAZARD_OPTIMIZE:
		for(cntm=M;cntm<M2;cntm++)
		{
			for(cntn=0;cntn<N;cntn++)
			{
				matres->m_rData[cntn*M2+cntm]=0;
			}
		}
		for(cntm=0;cntm<M2;cntm++)
		{
			for(cntn=N;cntn<N2;cntn++)
			{
				matres->m_rData[cntn*M2+cntm]=0;
			}
		}
		if (_tmcHasIm(matres))
		{
			for(cntm=M;cntm<M2;cntm++)
			{
				for(cntn=0;cntn<N;cntn++)
				{
					matres->m_iData[cntn*M2+cntm]=0;
				}
			}
			for(cntm=0;cntm<M2;cntm++)
			{
				for(cntn=N;cntn<N2;cntn++)
				{
					matres->m_iData[cntn*M2+cntm]=0;
				}
			}
		}
*/
//	matres->m_desc.m_nCols=N3;
//	matres->m_desc.m_nRows=M3;
	if (bHasIm)
		_tmcForceComplexMatrix(matres);
}

//int dbg_counter=0;
//int dbg_here=0;
void _tmcClearExtraDims(tmsMatrix *res)
{
	if (_tmcHasExtraDim(res))
	{
		_tmcKillDims(res);
		res->m_desc.m_dims=NULL;
		_tmcSetExtraDim(res,0);
	}
}
void _tmcCreateMatrix(tmsMatrix *res,long M,long N,short bHasImagine)
{
//long *myEBP;
//
//	__asm
//	{
//		mov myEBP,ebp 
//	}
//	sprintf(dbg_buf,"_tmcCreateMatrix: %x,%s",myEBP[1],dbg_buf2);

	res->m_desc.m_nRows=M;
	res->m_desc.m_nCols=N;
	res->m_desc.m_type= TYPE_MATRIX;
	_tmcClearExtraDims(res);
	//res->m_iData =NULL;
	//res->m_rData =NULL;
	//res->value.fields_list = NULL;
	//res->value.m_cells=NULL;
	memset(&res->value,0,sizeof(res->value));
	if (M*N)
	{
//		dbg_counter++;
//		if (dbg_counter==57168 || dbg_counter==57250 || dbg_counter==111198)
//		{
//			dbg_here=1;
//		}
////VANDAL
//	res->m_rData = (double*)my_malloc_dbg(M*N*sizeof(double),dbg_buf,dbg_counter);
//	res->m_rData = (double*)my_malloc_dbg(M*N*sizeof(double),dbg_buf,__LINE__);


	res->m_rData = (double*)MYMALLOC(M*N*sizeof(double));
	memset(res->m_rData,0,M*N*sizeof(double));
	if (bHasImagine)
		{
			res->m_iData = (double*)MYMALLOC(M*N*sizeof(double));
			memset(res->m_iData,0,M*N*sizeof(double));
			res->m_desc.m_modifier |=MODIFIER_MASK_HAS_IM;
		}
		else
		{
			res->m_desc.m_modifier &=~MODIFIER_MASK_HAS_IM;
		}

	}
}


/////////////////////////////////////////////////////////////////
void tmcFreeLocalVar(tmsMatrix *src)
{ // Applied to local variable at exit
  // Free memory allocated by the variable before return.

	_tmcClearRegister(src);
	MYFREE(src);// the only place we destroy register!
}
void tmcFreeRegister(tmsMatrix *src)
{ // Applied to register  at exit, called before MYFREE of local vars
	if (src !=NULL)
	{
		_tmcClearRegister(src);
		MYFREE(src); // the only place we destroy register!
	}
}
void tmcReallocRegister(tmsMatrix *src)
{
	_tmcClearRegister(src);
}

tmsMatrix * __tmcNewMatrix(void)
{
	tmsMatrix *dest;
	dest=(tmsMatrix *)MYMALLOC(sizeof(tmsMatrix));
	_tmcSetMatrixEmpty(dest);
	return dest;
}
tmsMatrix * _tmcNewMatrix_dbg(const char *filename, int linenumber)
{
	tmsMatrix *dest;
	dest=(tmsMatrix *)my_malloc_dbg(sizeof(tmsMatrix),filename,linenumber);
	_tmcSetMatrixEmpty(dest);
	return dest;
}

void _tmcClearMatrix(tmsMatrix *x)
{// only clear all data from existing usual matrix
	if(x->m_desc.m_type == TYPE_MATRIX || x->m_desc.m_type == TYPE_STRING)
	{
		if (x->m_rData)
		MYFREE(x->m_rData);
		x->m_rData=NULL;
		if (_tmcHasIm(x))
		{
			if(x->m_iData)
			MYFREE(x->m_iData);
			x->m_iData=NULL;
		}
		x->m_desc.m_nRows=0;
		x->m_desc.m_nCols=0;
		// Clear the multi-dim information
		_tmcClearExtraDims(x);
	}
}

void _tmcClearRegister(tmsMatrix *x)
{ // MYFREE the register before re-usage
  // The main tmsMatrix destructor 

long m,n;
long M;
long N;


	if (x==NULL)
	{
		return ; // if register is reference dont clear the source.
	}

	if (x->m_desc.m_modifier & MODIFIER_MASK_NOTCOPY)
	{
		memset(x,0,sizeof(tmsMatrix));
		x->m_desc.m_type = TYPE_NOTHING;
		return ;
	}

 x->m_desc.m_modifier  &= ~MODIFIER_MASK_BOOL;
 M = _tmcGetM(x);
 N = _tmcGetN(x);

		// Clear the multi-dim information
		_tmcClearExtraDims(x);

	if (x->m_desc.m_type == TYPE_CELL_ARRAY)
	{
		for (m=0;m<M;m++)
		{
			for (n=0;n<N;n++)
			{
				_tmcClearRegister(x->value.m_cells[m+n*M]);
				MYFREE(x->value.m_cells[m+n*M]);//xaxa
			}
		}
		x->m_desc.m_type = TYPE_NOTHING;
		if (x->value.m_cells)
			MYFREE(x->value.m_cells);
		x->value.m_cells=NULL;
		x->m_desc.m_nRows=0;
		x->m_desc.m_nCols=0;
	return ;
	}

	if (x->m_desc.m_type == TYPE_STRUCT)
	{
		_tmcClearStruct(x);
		return;
	}




	if (x->m_desc.m_type == TYPE_ITERATOR )
	{
		// Not needed:
		//_tmcClearRegister(*(x->iter_var));
		x->m_desc.m_type = TYPE_NOTHING;
		return;
	}
	// Usual matrix
	if (x->m_desc.m_type == TYPE_MATRIX || x->m_desc.m_type == TYPE_STRING)
	{
		if (x->m_rData)
		MYFREE(x->m_rData);
		x->m_rData=NULL;
		if (_tmcHasIm(x))
		{
			MYFREE(x->m_iData);
			x->m_iData=NULL;
		}
		x->m_desc.m_type = TYPE_NOTHING;
		x->m_desc.m_nRows=0;
		x->m_desc.m_nCols=0;
	return ;
	}
}



void tmcAssignNoCopy(tmsMatrix *dest,tmsMatrix *src)
{
	memcpy(dest,src,sizeof(tmsMatrix));
	dest->m_desc.m_modifier |=MODIFIER_MASK_NOTCOPY;
}
void tmcMoveMat(tmsMatrix *dest,tmsMatrix *src)
{ // used for mex-files translation without modification.
  // The mex modification is prefable
	if (src != NULL)
	{
		memcpy(dest,src,sizeof(tmsMatrix));
		MYFREE(src);
	}
}
long _tmcGetLinIndex(long ndims,tmsMatrix **pI)
{// get liner index . Used for structure scalar indexing. 
 // returns 0-based index
	if (ndims==1)
		return (long)pI[0]->value.complx.rData[0]-1;
	else // only 2 is supported
		return (long)(pI[0]->value.complx.rData[0]*pI[1]->value.complx.rData[0])-1;
}
void tmcAssign(tmsMatrix *dest,tmsMatrix *src)
{
	long M,N,ind,MN;
	tmsMatrix *lh_src;
	short k;
	long st_ind;
	short edim;

//	dest = _tmcGetByRef(dest);
	if(dest==src)
	{
		return; // do nothing
	}
	if (src == NULL)
	{
	    tmcReallocRegister(dest);
		_tmcSetMatrixEmpty(dest);
		return; // do nothing
	}
	
	// must check dimentions and type.
	M =_tmcGetM(src);
	N =_tmcGetN(src);


	if (dest->m_desc.m_type == TYPE_REF)
	{	k=0;
		lh_src=RefHelper.src;
		for (ind=0;ind<RefHelper.ndims;ind++)
		{
			switch (RefHelper.type[ind])
			{
			case '[':
				if (ind==RefHelper.ndims-1)
				{
				//HAZRARD_TODO: yet not implemented for lh_src = CELL_ARRAY
					// X(I)=..
					// get submatrix as lhs (may be structure array assignment)
					_tmcSetByIndex(lh_src,src,RefHelper.dims[ind],&RefHelper.refI[k]);
				}
				else
				{
					// may be structure array
					if (RefHelper.type[ind+1]=='.')
					{
							// X(I).x=..
							// here we must resize the structure array
							// and at the next step should assign.
							//HAZARD_TO_DO_resize_struct

					}
					else
					{
					_tmcRaiseException(err_bad_index,s_module,"x(n){k}=s","unsupported",0,NULL);
					// unsupported -- error
					}
				}
				break;
			case '{':
				if (ind==RefHelper.ndims-1)
						{	// actual assignment
							_tmcSetByIndexCell(lh_src,src,RefHelper.dims[ind],&RefHelper.refI[k]);
						}
						else
						{
							// find matrix (or resize)
							lh_src = _tmcGetByIndexCellForce(lh_src,RefHelper.dims[ind],&RefHelper.refI[k]);
						}
				break;
			case '.':
				if (ind==RefHelper.ndims-1)
						{	// actual assignment
							// X.f=.. or X(I).f=..
							if (ind>0 && RefHelper.type[ind-1]=='[')
							{
										st_ind = _tmcGetLinIndex(RefHelper.dims[ind-1],&RefHelper.refI[k-RefHelper.dims[ind-1]]);
							}
							else
							{
										st_ind =0;
							}
							_tmcSetByField(lh_src,st_ind,src,RefHelper.refhcFn[k]);
						}
						else
						{
							// find matrix (or resize)
							if (ind>0 && RefHelper.type[ind-1]=='[')
							{// X(I).S..=x
							 // X must be of valid dimensions.
										st_ind = _tmcGetLinIndex(RefHelper.dims[ind-1],&RefHelper.refI[k-RefHelper.dims[ind-1]]);
							}
							else
							{
										st_ind =0;// X.S..=x
							}

							lh_src =_tmcGetByFieldForce(lh_src,st_ind,RefHelper.refhcFn[k]);
						}

				break;
			}
		k += RefHelper.dims[ind]; 
		}
		return;
  }



	_tmcClearRegister(dest);
	edim = _tmcGetExtraDim(src);
	if (edim)
	{
		_tmcCreateDims(dest,edim+2);
		_tmcSetExtraDim(dest,edim);
		
		for ( k=0;k<edim+2;k++)
		{
		_tmcSetDim(dest,k,_tmcGetDimS(src,k+1));
		}
	}



	if (src->m_desc.m_type == TYPE_STRUCT)
	{
			_tmcCreateStruct(dest,M,N,(short)(_tmcGetNf(src)),src->value.StructDef.hcFields);
			MN=M*N*_tmcGetNf(src);
			for (ind=0;ind<MN;ind++)
			{
				tmcAssign(dest->value.StructDef.m_fields[ind],src->value.StructDef.m_fields[ind]); // recursive
			}
		return;
	}

	if (src->m_desc.m_type == TYPE_CELL_ARRAY)
	{
		_tmcCreateCellArray(dest,M,N);
		for (ind=0;ind<M*N;ind++)
		{
			dest->value.m_cells[ind] = tmcNewMatrix();
			tmcAssign(dest->value.m_cells[ind],src->value.m_cells[ind]); // recursive
		}
		return;
	}


	if (src->m_desc.m_type == TYPE_MATRIX || src->m_desc.m_type == TYPE_STRING)
	{

		 dest->m_desc.m_nRows = src->m_desc.m_nRows;
		 dest->m_desc.m_nCols = src->m_desc.m_nCols;
		 dest->m_desc.m_type = src->m_desc.m_type;

		  dest->m_rData = (double*)MYMALLOC(M* N * sizeof(double));
		  memcpy(dest->m_rData,src->m_rData,M* N * sizeof(double));
		 if (_tmcHasIm(src))
		 {
			 dest->m_iData = (double*)MYMALLOC(M* N * sizeof(double));
			 memcpy(dest->m_iData,src->m_iData,M* N* sizeof(double));
			 dest->m_desc.m_modifier  |= MODIFIER_MASK_HAS_IM;
		 }
		 else
		 {
			dest->m_desc.m_modifier  &= ~MODIFIER_MASK_HAS_IM;
		 }
	}
	if (src->m_desc.m_type == TYPE_FNC_HANDLE)
	{
		 dest->m_desc.m_type = src->m_desc.m_type;
		 dest->value.fnc_ptr=src->value.fnc_ptr;
	}
}
void tmcCopyMat(tmsMatrix *des,tmsMatrix *src)
{ // des  must be initialized

	long M,N,ind,MN;
	short edim;
	short k;
//	des = _tmcGetByRef(des);
	if (src==NULL)
		return; // was null argument passed to function.
	if (des==NULL)
	{
		_tmcRaiseException(err_unsupported,"main","tmcCopyMat","FATAL: des matrix not created.",0,NULL);
		return; // impossible
	}
	// must check dimentions and type.
	M =_tmcGetM(src);
	N =_tmcGetN(src);


	_tmcClearRegister(des);
	edim = _tmcGetExtraDim(src);
	if (edim)
	{
		_tmcCreateDims(des,edim+2);
		_tmcSetExtraDim(des,edim);
		for ( k=0;k<edim+2;k++)
		{
		_tmcSetDim(des,k,_tmcGetDimS(src,k+1));
		}
	}


	if (src->m_desc.m_type == TYPE_STRUCT)
	{
			_tmcCreateStruct(des,M,N,(short)(_tmcGetNf(src)),src->value.StructDef.hcFields);
			MN=M*N*_tmcGetNf(src);
			for (ind=0;ind<MN;ind++)
			{
				tmcAssign(des->value.StructDef.m_fields[ind],src->value.StructDef.m_fields[ind]); // recursive
			}
		return;
	}


	if (src->m_desc.m_type == TYPE_CELL_ARRAY)
	{
		_tmcCreateCellArray(des,M,N);// actually adressed by value, i.e. address not used
		for (ind=0;ind<M*N;ind++)
		{
			des->value.m_cells[ind] = tmcNewMatrix();
			tmcAssign(des->value.m_cells[ind],src->value.m_cells[ind]); // recursive
		}
		return;
	}


	if (src->m_desc.m_type == TYPE_MATRIX || src->m_desc.m_type == TYPE_STRING)
	{

		 des->m_desc.m_nRows = src->m_desc.m_nRows;
		 des->m_desc.m_nCols = src->m_desc.m_nCols;
		 des->m_desc.m_type = src->m_desc.m_type;

		 des->m_rData = (double*)MYMALLOC(M* N * sizeof(double));
		 memcpy(des->m_rData,src->m_rData,M* N * sizeof(double));
		 if (_tmcHasIm(src))
		 {
			 des->m_iData = (double*)MYMALLOC(M* N * sizeof(double));
			 memcpy(des->m_iData,src->m_iData,M* N* sizeof(double));
			des->m_desc.m_modifier  |= MODIFIER_MASK_HAS_IM;
		 }
		 else
		 {
			des->m_desc.m_modifier  &= ~MODIFIER_MASK_HAS_IM;
		 }
	}
	if (src->m_desc.m_type == TYPE_FNC_HANDLE )
	{
		 des->m_desc.m_type = src->m_desc.m_type;
		 des->value.fnc_ptr=src->value.fnc_ptr;
	}
}

void tmcScalar(tmsMatrix *dest,double x)
{
//long *myEBP;
//
//	__asm
//	{
//		mov myEBP,ebp 
//	}
//	sprintf(dbg_buf2,"tmcScalar: %x,%s",myEBP[1],"...");


	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,1,1,tmcREAL);
	dest->m_rData[0]=x;
}
void tmcComplexScalar(tmsMatrix *dest,double xr,double xi)
{
	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,1,1,tmcCOMPLEX);
	dest->m_rData[0]=xr;
	dest->m_iData[0]=xi;
}


enum CMP_CONDITIONS
{
	CMP_EQ=1,
	CMP_NE=2,
//	CMP_LT=3,
	CMP_GT=4,
//	CMP_LE=5,
	CMP_GE=6
};

void  _tmcCmpCond(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b,const short fCondition)
{
long ind;
double y;
	// must check dimentions and type.

	long Ma,Na,MNa;
	long Mb,Nb,MNb;
	long M,N,MN;
	double xa,xb;

	// must check dimentions and type.
	Ma =_tmcGetM(a);
	Na =_tmcGetN(a);
	MNa=Ma*Na;
	Mb =_tmcGetM(b);
	Nb =_tmcGetN(b);
	MNb = Mb*Nb;

	if (( MNa!=1 && MNb!=1) && (MNa != MNb))
	{
		_tmcRaiseException(err_invalid_dimentions,s_module,"cmp","Matrix dimensions must agree",2,a,b);
	}
	if ((_tmcGetType(a) !=  TYPE_MATRIX && _tmcGetType(a) !=  TYPE_STRING)||
		(_tmcGetType(b) !=  TYPE_MATRIX && _tmcGetType(b) !=  TYPE_STRING)
		)
	{
		_tmcRaiseException(err_must_be_matrix,s_module,"cmp","Matrix type invalid",2,a,b);
	}

	if ( MNa==0 || MNb==0)
	{
		// case of empty matrix
		MN=0;M=0;N=0;
	}
	else
	{
		M=max(Ma,Mb);
		N=max(Na,Nb);
		MN=M*N;
	}


	tmcReallocRegister(sum);
	_tmcCreateMatrix(sum,M,N,tmcREAL);
	
	xa=a->m_rData[0];
	xb=b->m_rData[0];

		for (ind=0;ind<MN;ind++)
		{
			if (ind>0 && MNa>1)
				xa=a->m_rData[ind];

			if (ind>0 && MNb>1)
				xb=b->m_rData[ind];

			y=0;
			switch(fCondition)
			{
			case CMP_EQ://1,
				if (xa==xb) y=1;break;
			case CMP_NE://=2,
				if (xa!=xb) y=1;break;
//			case CMP_LT://=3,
//				if (xa<xb) y=1;break;
			case CMP_GT://=4,
				if (xa>xb) y=1;break;
//			case CMP_LE://=5,
//				if (xa<=xb) y=1;break;
			case CMP_GE://=6
				if (xa>=xb) y=1;break;
			default: ;
			}
			sum->m_rData[ind]= y;
		}
}

void  tmcGt(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b)
{
	_tmcCmpCond(sum,a,b,CMP_GT);
}

void  tmcLt(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b)
{
	_tmcCmpCond(sum,b,a,CMP_GT);
}
void  tmcEq(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b)
{
	_tmcCmpCond(sum,a,b,CMP_EQ);
}
void  tmcNe(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b)
{
	_tmcCmpCond(sum,a,b,CMP_NE);
}

void  tmcGe(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b)
{
	_tmcCmpCond(sum,a,b,CMP_GE);
}
void  tmcLe(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b)
{
	_tmcCmpCond(sum,b,a,CMP_GE);
}
void tmcAndBoolean(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2)
{

	tmcReallocRegister(matres);
	_tmcCreateMatrix(matres,1,1,tmcREAL);
	if (src1->m_rData[0] && src2->m_rData[0] )
	{
		matres->m_rData[0] = 1;
	}
	else
	{
		matres->m_rData[0] = 0;
	}
}
void tmcOrBoolean(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2)
{

	tmcReallocRegister(matres);
	_tmcCreateMatrix(matres,1,1,tmcREAL);
	if (src1->m_rData[0] || src2->m_rData[0] )
	{
		matres->m_rData[0] = 1;
	}
	else
	{
		matres->m_rData[0] = 0;
	}
}


#define OpScalarAND		1
#define OpScalarOR		2
#define OpBitAND		3
#define OpBitOR			4




void _tmcAndOrScalar(tmsMatrix *y,tmsMatrix *src1,tmsMatrix *src2,short bType)
{
short bScalar;
double *ptr;
long len,M,N,k;
tmsMatrix *vec;
double scal;

		if ( _tmcHasIm(src1) || _tmcHasIm(src2))
		_tmcRaiseException(err_must_be_real,s_module,"scalar AND,OR(|,&)","Operands to AND,OR must not be complex.",2,src1,src1);

		
	if ((tmcNumElem(src1)==1) || (tmcNumElem(src2)==1))
	{
		bScalar=1;
		if (tmcNumElem(src1)==1)
		{
			vec = src2;
			scal = src1->m_rData[0];
		}
		else
		{
			vec = src1;scal = src2->m_rData[0];
		}
			len=tmcNumElem(vec);
			ptr=vec->m_rData;
			M=_tmcGetM(vec);
			N=_tmcGetN(vec);
			_tmcCreateMatrix(y,M,N,tmcREAL);
			for (k=0;k<len;k++)
			{
				if (bType==OpScalarAND)
				{
					y->m_rData[k]= (ptr[k] && scal ? 1:0);
				}
				else if (bType==OpScalarOR)
				{// or
					y->m_rData[k]= (ptr[k] || scal ? 1:0); 
				}
				else if (bType==OpBitAND)
				{// and
					y->m_rData[k]= (double)((__int64)(ptr[k]) &  (__int64)scal); 
				}
				else if (bType==OpBitOR)
				{// or
					y->m_rData[k]= (double)((__int64)(ptr[k]) | (__int64)scal); 
				}

			}
	}
	else
	{
		bScalar=0;
		if ( _tmcGetM(src1) != _tmcGetM(src2) || _tmcGetN(src1) != _tmcGetN(src2) )
		_tmcRaiseException(err_invalid_dimentions,s_module,"scalar AND,OR(|,&)","Matrix dimensions must agree",2,src1,src2);

			M=_tmcGetM(src1);
			N=_tmcGetN(src1);
			_tmcCreateMatrix(y,M,N,tmcREAL);
			len = tmcNumElem(src1);
			for (k=0;k<len;k++)
			{
				if (bType==OpScalarAND)
				{
					y->m_rData[k]= (src1->m_rData[k] && src2->m_rData[k] ? 1:0);
				}
				else if (bType==OpScalarOR)
				{// or
					y->m_rData[k]= (src1->m_rData[k] || src2->m_rData[k] ? 1:0); 
				}
				else if (bType==OpBitAND)
				{// and
					y->m_rData[k]= (double)((__int64)(src1->m_rData[k]) &  (__int64)(src2->m_rData[k])); 
				}
				else if (bType==OpBitOR)
				{// or
					y->m_rData[k]= (double)((__int64)(src1->m_rData[k]) |  (__int64)(src2->m_rData[k])); 
				}
			}
	}
}
void tmcAndScalar(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2)
{
	tmcReallocRegister(matres);
	_tmcAndOrScalar(matres, src1, src2,OpScalarAND);

}
void tmcOrScalar(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2)
{
	tmcReallocRegister(matres);
	_tmcAndOrScalar(matres, src1, src2,OpScalarOR);
}

void tmcbitand(long nout,long ninput,tmsMatrix *y,tmsMatrix *a,tmsMatrix *b)
{
	_tmcAndOrScalar(y, a, b,OpBitAND);
}
void tmcbitor(long nout,long ninput,tmsMatrix *y,tmsMatrix *a,tmsMatrix *b)
{
	_tmcAndOrScalar(y, a, b,OpBitOR);
}

void tmcbitshift(long nout,long ninput,tmsMatrix *matres,tmsMatrix *src,tmsMatrix *mK,tmsMatrix *mN)
{
	/*
BITSHIFT Bit-wise shift.
    C = BITSHIFT(A,K,N) returns the value of A shifted by K bits. Shifting
    by K is the same as multiplication by 2^K and then rounding to the
    nearest integer (i.e. C = fix(A*2^K)).  If the shift causes C to
    overflow N bits, the overflowing bits are dropped.  A must contain
    non-negative integers between 0 and BITMAX.
 
    C = BITSHIFT(A,K) uses the default value of N = 53.

    BITMAX returns the maximum unsigned floating point integer for
    this machine.  It is the value when all bits are set.
    On IEEE machines, this is the value 2^53-1;
  */
//HAZARD_TODO_CHECK_RESTRICTIONS
	long M,N,MN,k;
//	double shiftfactor;
	short nshifts;
	__int64 ltemp;
	__int64 mask;
	short maxbits;


		if ( _tmcHasIm(src) )
		_tmcRaiseException(err_must_be_real,s_module,"tmcbitshift(A,K,N)","Operand to bitshift must not be complex.",1,src);

		if ( tmcNumElem(mK) != 1)
		_tmcRaiseException(err_must_be_real,s_module,"tmcbitshift(A,K,N)","RESTRICTION K to bitshift must be scalar.",1,src);

		if (ninput > 2)
				if ( tmcNumElem(mN) != 1)
				   _tmcRaiseException(err_must_be_real,s_module,"tmcbitshift(A,K,N)","RESTRICTION N to bitshift must be scalar.",1,src);
				else
					maxbits = (short)mN->m_rData[0];
		else
					maxbits  = 53;

		nshifts = (short)mK->m_rData[0];
		mask = ( (__int64)1 << maxbits) - 1;

		//if (nshifts)
		//{
		// if (nshifts>0)
		//	shiftfactor =(double)  (((__int64)1)<<nshifts);
		// else
		//	shiftfactor = (1.0f / ( ((__int64)1)<<(-nshifts) ));
		//}
		//else
		//	shiftfactor=1.0f;

		tmcReallocRegister(matres);
			M=_tmcGetM(src);
			N=_tmcGetN(src);
			_tmcCreateMatrix(matres,M,N,tmcREAL);
			MN=tmcNumElem(src);
			for (k=0;k<MN;k++)
			{
				ltemp =  (__int64) floor(src->m_rData[k]);
				if (nshifts>=0)
					ltemp = ( (ltemp << nshifts) & mask);
				else
					ltemp = ( (ltemp >> (-nshifts)) & mask);
				matres->m_rData[k] = (double)ltemp;
				//matres->m_rData[k] =  floor(src->m_rData[k]  * shiftfactor);
			}
}

void tmcAssignBool(tmsMatrix *matres,tmsMatrix *src)
{// HAZARD_TODO all operations.

	tmcScalar(matres,tmcIsTrue(src));
//	matres->m_desc.m_modifier |= MODIFIER_MASK_BOOL;
//	if (tmcIsFalse(src))
//	{
//		matres->m_desc.m_modifier &= ~MODIFIER_MASK_BOOL_TRUE;
//	}
//	else
//	{
//		matres->m_desc.m_modifier |= MODIFIER_MASK_BOOL_TRUE;
//	}
}

void tmcNot(tmsMatrix *matres,tmsMatrix *src)
{
	long M,N,MN,k;
		if ( _tmcHasIm(src) )
		_tmcRaiseException(err_must_be_real,s_module,"scalar NOT(~)","Operand to NOT must not be complex.",1,src);

		tmcReallocRegister(matres);
			M=_tmcGetM(src);
			N=_tmcGetN(src);
			_tmcCreateMatrix(matres,M,N,tmcREAL);
			MN=tmcNumElem(src);
			for (k=0;k<MN;k++)
			{
				matres->m_rData[k] = (src->m_rData[k] ? 0:1);
			}
}


short  tmcIsFalse(tmsMatrix *x)
{// Return: 1: has a zero element
 // otherwise: 0
long ind;

	long M,N,MN;

	// must check dimentions and type.
	M =_tmcGetM(x);
	N =_tmcGetN(x);
	MN=M*N;

	if (MN==0) return 1; // [] is false also
	for (ind=0;ind< MN  ;ind++)
		{
			if (x->m_rData[ind]==0)
				return 1;
		}
return 0;
}
short  tmcIsTrue(tmsMatrix *x)
{// Return: 1: has all non zero elements
 // otherwise: 0
long ind;

	long M,N,MN;

	// must check dimentions and type.
	M =_tmcGetM(x);
	N =_tmcGetN(x);
	MN=M*N;

	if (MN==0) return 0; // [] is false also
	for (ind=0;ind< MN  ;ind++)
		{
			if (x->m_rData[ind]==0)
				return 0;
		}
return 1;
}



void tmcCollectColumns(tmsMatrix *colres,long numcols,tmsMatrix *a,...)
{//HAZARD_TODO: implement collect structures into multi-dim struct
long ind,ind1;
va_list marker;
long sum_col_dim;
long cnt;
long act_numrows;
long M;
short bHasImagine;

tmsMatrix **matN = (tmsMatrix **)MYMALLOC(sizeof(tmsMatrix *) * numcols);

	tmcReallocRegister(colres);

	va_start( marker, a );     // Initialize variable arguments. 
	ind=1;
	matN[0]=a;
	sum_col_dim = _tmcGetN(a);;
	act_numrows = _tmcGetM(a); // may be zero
	bHasImagine = _tmcHasIm(a);
	while (ind<numcols)
	{
		matN[ind] = va_arg( marker,  tmsMatrix * );
		sum_col_dim += _tmcGetN(matN[ind]);
		if (act_numrows==0)
		{
			M=_tmcGetM(matN[ind]);
			if (M)
			{
					act_numrows=M;// first not-empty matrix
			}
		}
		bHasImagine |= _tmcHasIm(matN[ind]);
		ind++;
	}
	va_end( marker );              // Reset variable arguments.      

	_tmcCreateMatrix(colres,act_numrows,sum_col_dim,bHasImagine);
	// matrix is by columns - simply copy all the matrixes
	ind1=0;//  full number of filled values
	for (cnt=0;cnt<numcols;cnt++)
	{
		memcpy( &(colres->m_rData[ind1]),&(matN[cnt]->m_rData[0]),	tmcNumElem(matN[cnt])*sizeof(double));
		if (bHasImagine & _tmcHasIm(matN[cnt]))
			memcpy( &(colres->m_iData[ind1]),&(matN[cnt]->m_iData[0]),	tmcNumElem(matN[cnt])*sizeof(double));

		ind1 +=tmcNumElem(matN[cnt]);
	}
	MYFREE(matN);
    if(a->m_desc.m_type==TYPE_STRING)
	colres->m_desc.m_type=a->m_desc.m_type;
}
void tmcCollectRows(tmsMatrix *matres,long numrows,tmsMatrix *a,...)
{
long ind,ind1,nc;
va_list marker;
long sum_row_dim;
long cnt;
long act_numcols;
long M,N;
short bHasImagine;
long m,n,ind2;
tmsMatrix **matN = (tmsMatrix **)MYMALLOC(sizeof(tmsMatrix *) * numrows);

	tmcReallocRegister(matres);

	va_start( marker, a );     // Initialize variable arguments. 
	ind=1;
	matN[0]=a;
	sum_row_dim = _tmcGetM(a);
	act_numcols = _tmcGetN(a); // may be zero
	bHasImagine = _tmcHasIm(a);
	while (ind<numrows)
	{
		matN[ind] = va_arg( marker,  tmsMatrix * );
		sum_row_dim += _tmcGetM(matN[ind]);
		if (act_numcols==0)
		{
			N=_tmcGetN(matN[ind]);
			if (N>0)
			{
					act_numcols=N;// first not-empty matrix
			}
		}
		bHasImagine |= _tmcHasIm(matN[ind]);
		ind++;
	}
	va_end( marker );              // Reset variable arguments.      


	_tmcCreateMatrix(matres,sum_row_dim,act_numcols,bHasImagine);
	
	nc=0;//  full number of filled rows
	for (cnt=0;cnt<numrows;cnt++)
	{
		M = _tmcGetM(matN[cnt]);
		for (m=0;m < M;m++) // by row of each added matrix
		{
			ind1 = nc;
			ind2 = m;
			for (n=0;n<act_numcols;n++)
			{
				matres->m_rData[ind1]=matN[cnt]->m_rData[ind2];
				if (bHasImagine & _tmcHasIm(matN[cnt]))
					matres->m_iData[ind1]=matN[cnt]->m_iData[ind2];
				ind1 +=sum_row_dim;
				ind2 +=M;
			}
			nc++;
		}
	}
	MYFREE(matN);
    if(a->m_desc.m_type==TYPE_STRING)
		matres->m_desc.m_type=a->m_desc.m_type;//hazard
}

void _tmcSetMatrixEmpty(tmsMatrix *y)
{// HAZARD - matrix not freed
	memset(y,0,sizeof(tmsMatrix));
	memset(&y->m_desc,0,sizeof(struct tag_tmcMatrixDecriptor));
	y->m_desc.m_type=TYPE_NOTHING;
}

void tmcCreateMatrixEmpty(tmsMatrix *matres)
{
	 _tmcClearRegister(matres);
}


long tmcNumElem(tmsMatrix *x)
{
	return x->m_desc.m_nRows*x->m_desc.m_nCols;

}

// relations for sorting
int lcompare( const void *arg1, const void *arg2 )
{
	long n1= *(long*)arg1;
	long n2= *(long*)arg2;
	if (n1>n2)
		return 1;
	else if (n1<n2)
		return -1;
	else
		return 0;

}
int dcompare( const void *arg1, const void *arg2 )
{
	double n1= *(double*)arg1;
	double n2= *(double*)arg2;

			if (_isnan(n1) && !_isnan(n2))
				return 1;
			if (_isnan(n2) && !_isnan(n1))
				return -1;

	if (n1>n2)
		return 1;
	else if (n1<n2)
		return -1;
	else
		return 0;

}
int dcompare_descend( const void *arg1, const void *arg2 )
{
	double n1= *(double*)arg1;
	double n2= *(double*)arg2;

			if (_isnan(n1) && !_isnan(n2))
				return -1;
			if (_isnan(n2) && !_isnan(n1))
				return 1;

	if (n1>n2)
		return -1;
	else if (n1<n2)
		return 1;
	else
		return 0;

}
struct Creal_sort
{
	double val_re;
	long   ind;
};
int valindcompare( const void *arg1, const void *arg2 )
{
	double n1= ((struct Creal_sort*)arg1)->val_re;
	double n2= ((struct Creal_sort*)arg2)->val_re;

			if (_isnan(n1) && !_isnan(n2))
				return 1;
			if (_isnan(n2) && !_isnan(n1))
				return -1;


	if (n1>n2)
		return 1;
	else if (n1<n2)
		return -1;
	else
	{
		// The following if to achive:
	//	 When more than one element has the same value, the order of the
    //elements are preserved in the sorted result and the indexes of
    //equal elements will be ascending.
		if (arg1 > arg2) // 
			return 1;
		else
			return 0;
	}
}
int valindcompare_descend( const void *arg1, const void *arg2 )
{
	double n1= ((struct Creal_sort*)arg1)->val_re;
	double n2= ((struct Creal_sort*)arg2)->val_re;

			if (_isnan(n1) && !_isnan(n2))
				return -1;
			if (_isnan(n2) && !_isnan(n1))
				return 1;


	if (n1>n2)
		return -1;
	else if (n1<n2)
		return 1;
	else
	{
		if (arg1 > arg2) // ??
			return -1;
		return 0;
	}
}
struct Ccomplex_sort
{
	double val_re;
	double val_im;
	long   ind;
};
int cvalindcompare( const void *arg1, const void *arg2 )
{//for complex must compare according angle if abs are equal
 // NaN must place at the high end
	double A1,A2;
	double n1= ((struct Ccomplex_sort*)arg1)->val_re;
	double n2= ((struct Ccomplex_sort*)arg2)->val_re;
	double n1i= ((struct Ccomplex_sort*)arg1)->val_im;
	double n2i= ((struct Ccomplex_sort*)arg2)->val_im;
/*
	if (n1i == 0 && n2i == 0)
	{
	if (n1>n2)
		return 1;
	else if (n1<n2)
		return -1;
	else
		return 0;
	}
	else
	{
	A1=n1*n1+n1i*n1i;
	A2=n2*n2+n2i*n2i;
	if (A1 > A2)
		return 1;
	else if (A1<A2)
		return -1;
	else
		{
		if (n1==n2)
			return 0;
		else
			if (n1>n2)
				return 1;
			else
				return -1;
		}
	}
*/
	A1=n1*n1+n1i*n1i;
	A2=n2*n2+n2i*n2i;

			if (_isnan(A1) && !_isnan(A2))
				return 1;
			if (_isnan(A2) && !_isnan(A1))
				return -1;


	if (A1 > A2)
		return 1;
	else if (A1<A2)
		return -1;
	else
	{
		A1 = atan2(n1i,n1);
		A2 = atan2(n2i,n2);
		if (A1 > A2)
			return 1;
		else if (A1<A2)
			return -1;
		else
		{

			if (arg1 > arg2) // 
				return 1;
			else
				return 0;
		}

	}
}
int cvalindcompare_descend( const void *arg1, const void *arg2 )
{
	return -cvalindcompare(arg1,arg2);
}

void _tmcClearColumns(tmsMatrix *x,tmsMatrix *J)
{
long max_val;
//long ind_at_max;
long *ltemp;
long *lptr;
double *dptr,*dptr2,*dptr2i;
long MNj;
long k,col1,col2;
double *dtemp,*dtemp_i;
long M,N;
long val1,nVals;

	MNj=tmcNumElem(J);
	if (MNj>0)
	{// if J<>[]
		ltemp=MYMALLOC(sizeof(long)*MNj);
		for (k=0,lptr=ltemp,dptr=J->m_rData;k<MNj;k++)
		{
			*lptr++=(long)(*dptr++);
		}
		qsort(ltemp,MNj,sizeof(long),lcompare);
		// now ltemp is sorted array of indexes.
		// lets find number of unique values
		max_val=ltemp[MNj-1];
		if (max_val > _tmcGetN(x))
		{
			_tmcRaiseException(err_bad_index,s_module,"_tmcClearColumns","bad index in x(:,J)=[]",2,x,J);
		}

		val1=ltemp[0];
		nVals=1;
		for (k=1,lptr=&ltemp[1];k<MNj;k++,lptr++)
		{
			if( *lptr > val1)
			{
				nVals++;
				val1=*lptr;
			}
		}
		M=_tmcGetM(x);
		N=_tmcGetN(x);
		dtemp=MYMALLOC(sizeof(double)*M*(N-nVals));
		dptr2=dtemp; // start of destination column
		if (_tmcHasIm(x))
		{
			dtemp_i=MYMALLOC(sizeof(double)*M*(N-nVals));
			dptr2i=dtemp_i;
		}
		x->m_desc.m_nCols=N-nVals;
		// copy columns here
		k=N-nVals; // remained columns
		col1=1; // src column (1-based)
		lptr=ltemp;
		col2=*lptr;//column to be cleared
		while (k>0)
		{
			while( (col1!=col2) && (k>0))
			{
				// append column  
				memcpy(dptr2,&x->m_rData[(col1-1)*M],M*sizeof(double));
				dptr2 += M;// go to next column
				if (_tmcHasIm(x))
				{
				memcpy(dptr2i,&x->m_iData[(col1-1)*M],M*sizeof(double));
				dptr2i += M;// go to next column
				}

				k--;
				col1++;
			}
			if (k>0)
			{
				// col1==col2
				col1++; // do not copy this column
				lptr++;
				while ((col2==*lptr) && lptr!=&ltemp[MNj-1])
					lptr++;
				col2=*lptr; // new column to be removed
			}
		}
		MYFREE(x->m_rData);
		x->m_rData=dtemp;
		if (_tmcHasIm(x))
		{
			MYFREE(x->m_iData);
			x->m_iData=dtemp_i;
		}
		MYFREE(ltemp);
	}
}

void _tmcClearRows(tmsMatrix *x,tmsMatrix *I)
{
long max_val;
//long ind_at_max;
long *ltemp;
long *lptr;
double *dptr,*dptr2,*dptr2i,*dptr1;
long MNi;
long k,col1,col2;
double *dtemp,*dtemp_i;
long M,N;
long val1,nVals;
long n,M2;
	MNi=tmcNumElem(I);
	if (MNi>0)
	{// if I<>[]
		ltemp=MYMALLOC(sizeof(long)*MNi);
		for (k=0,lptr=ltemp,dptr=I->m_rData;k<MNi;k++)
		{
			*lptr++=(long)(*dptr++);
		}
		qsort(ltemp,MNi,sizeof(long),lcompare);
		// now ltemp is sorted array of indexes.
		// lets find number of unique values
		max_val=ltemp[MNi-1];
		if (max_val > _tmcGetM(x))
		{
			_tmcRaiseException(err_bad_index,s_module,"_tmcClearColumns","bad index in x(:,J)=[]",2,x,I);
		}

		val1=ltemp[0];
		nVals=1;
		for (k=1,lptr=&ltemp[1];k<MNi;k++,lptr++)
		{
			if( *lptr > val1)
			{
				nVals++;
				val1=*lptr;
			}
		}
		M=_tmcGetM(x);
		N=_tmcGetN(x);
		dtemp=MYMALLOC(sizeof(double)*N*(M-nVals));
		dptr2=dtemp; // start of destination column
		if (_tmcHasIm(x))
		{
			dtemp_i=MYMALLOC(sizeof(double)*N*(M-nVals));
			dptr2i=dtemp_i;
		}
		M2=M-nVals;
		x->m_desc.m_nRows=M2;
		// copy columns here
		k=M2; // remained rows
		col1=1; // src rows (1-based)
		lptr=ltemp;
		col2=*lptr;//row to be cleared
		while (k>0)
		{
			while( (col1!=col2) && (k>0))
			{
				// append row  
				for (n=0,dptr=dptr2,dptr1=&x->m_rData[(col1-1)];n<N;n++)
				{	//	dptr2[n*M2]=x->m_rData[(col1-1)+n*M];
					*dptr=*dptr1;
					dptr +=M2; dptr1 +=M;
				}
				dptr2 += 1;// go to next row
				if (_tmcHasIm(x))
				{
					for (n=0,dptr=dptr2i,dptr1=&x->m_iData[(col1-1)];n<N;n++)
					{	//	dptr2i[n*M2]=x->m_iData[(col1-1)+n*M];
						*dptr=*dptr1;
						dptr +=M2; dptr1 +=M;
					}
				dptr2i += 1;// go to next row
				}
				k--;
				col1++;
			}
			if (k>0)
			{
				// col1==col2
				col1++; // do not copy this row
				lptr++;
				while ((col2==*lptr) && lptr!=&ltemp[MNi-1])
					lptr++;
				col2=*lptr; // new row to be removed
			}
		}
		MYFREE(x->m_rData);
		x->m_rData=dtemp;

		if (_tmcHasIm(x))
		{
			MYFREE(x->m_iData);
			x->m_iData=dtemp_i;
		}
	MYFREE(ltemp);
	}


}

void _tmcLongGetMaxVal(long *max_val,long *ind_at_max,tmsMatrix *x)
{
long k;
long mi;
long ind;
long val;

	long MN= tmcNumElem(x);
	mi=0;ind=-1;
	for (k=0;k<MN;k++)
	{
		val=(long)x->m_rData[k];
		if (val>mi)
		{
				mi=val;ind=k;
		}
	}
	*max_val=mi;
	*ind_at_max=ind;
}

void  _tmcSetByIndex(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix **refs)
// restrictions: see tmsGetByIndex
// *matres is already initialized.

// Insertion possibilities (all matrix elements are ordered by columns,as known):
// 1. x(I,J)=a, size(a) = [size(I,1)*size(I,2) size(J,1)*size(J,2)]
//	  x(I(m),J(n))=a(m,n), m=1:size(I,1)*size(I,2),n=1:size(J,1)*size(J,2)
//	  x may be resized to [max(size(x,1),max(I)) max(size(x,2),max(J))]
// 2. x(I,J)=a, size(a)=[1 1].
//	  x(I(m),J(n))=a, m=1:size(I,1)*size(I,2),n=1:size(J,1)*size(J,2)
//	  x may be resized to [max(size(x,1),max(I)) max(size(x,2),max(J))]
// 3. x(I)=a, size(a,1)*size(a,2)=size(I,1)*size(I,2)
//    x(I(m))=a(m),m=1:size(a,1)*size(a,2)
//    if x is row/column/sclar it may be resized to row/column/column
//     [max(size(x,1),max(I)) 1] or [1 max(size(x,2),max(I))]
// 4. x(I)=[] if I is row/column clears elements I(m),m=1:length(I)
// 5. x(:)=a, size(a,1)*size(a,2)=size(x,1)*size(x,2)
//    x(m)=a(m),m=1:size(a,1)*size(a,2)
// 6. x(:,J)=[] clears columns 
// 7. x(I,:)=[] clears rows
//HAZARD_TODO: case of clear and I=[].
{
//long M,N;//,Ma,Na,Mr,Nr;
long m,n,ind1,ind2;//,indI;
short bHasIm,bLhHadIm;
short IsMagicColonIndex[2]={0,0};
long i1,i2;
tmsMatrix *I,*J;
long MNa,MNi,MNj,MNr,aScalar;

long max_val,ind_at_max;
long Na,Ma,max_valJ;
short ind1_inc;

 if (numdims >2)
 {
	_tmcSetByIndexMD(matres,src,numdims,refs);
	 return;
 }

	MNa=tmcNumElem(src); // size(a,1)*size(a,2)
		if (MNa==1)
		{
			aScalar=1;// a is scalar
		}
		else
		{
			aScalar=0;// a is not scalar
		}
	Ma=_tmcGetM(src);
	Na=_tmcGetN(src);

	bHasIm=_tmcHasIm(src);// HAZARD: must synchronize.
	bLhHadIm = _tmcHasIm(matres);
	MNr=tmcNumElem(matres); // size(x,1)*size(x,2)



	if (numdims==1)
	{
		// 3. x(I)=a, size(a,1)*size(a,2)=size(I,1)*size(I,2)
		//    x(I(m))=a(m),m=1:size(a,1)*size(a,2)
		//    if x is row/column/sclar it may be resized to row/column/column
		//     [max(size(x,1),max(I)) 1] or [1 max(size(x,2),max(I))]

		// check dimentions
		I=refs[0];
		MNi=tmcNumElem(I); // size(I,1)*size(I,2)
		if (I->m_desc.m_type == TYPE_MAGIC_COLON)
		{
			IsMagicColonIndex[0]=1;
			MNi=tmcNumElem(matres);
		}

		if (_tmcIsEmptyMatrix(src))
		{
			// x(I)=[] or x(:)=[]
			if (IsMagicColonIndex[0])
			{
				// x(:)=[]
				_tmcClearMatrix(matres);
			}
			else
			{
				if (_tmcGetM(matres)<_tmcGetN(matres))
				{
					_tmcClearColumns(matres,I);
				}
				else
				{
					_tmcClearRows(matres,I);
				}
			}
			return;
		}

		if (aScalar==0)
		{
			if (MNa != MNi)
			{
			_tmcRaiseException(err_bad_index,s_module,"_tmcSetByIndex","numelem(I)<>numelem(a) in x(I)=a",2,I,src);
			}
		}
		// reshape the result matrix
		if(IsMagicColonIndex[0]==0)
		{
			_tmcLongGetMaxVal(&max_val,&ind_at_max,I); // find maximal index
			if (max_val > MNr)
			{
				if (_tmcIsMatrix(matres))
				{
					_tmcRaiseException(err_bad_index,s_module,"_tmcSetByIndex","cant resize matrix x in x(I)=a",2,matres,I);
				}
				else
				{
					// is row or column or scalar
					if (_tmcGetM(matres)>1)
					{
							_tmcResizeMatrix(matres,max_val,1,bHasIm);
					}
					else
					{
							_tmcResizeMatrix(matres,1,max_val,bHasIm);
					}
				}
			}
		}
		else
		{
			// x(:)=a.
		}

		if(bHasIm)
		{
				_tmcForceComplexMatrix(matres);// add zero imagine part if needed
		}

		if(aScalar)
		{
			if(IsMagicColonIndex[0])
			{
				// insert real part
				for(m=0;m<MNi;m++)
				{
					matres->m_rData[m]=src->m_rData[0];
				}
				// optionally insert imagine part
				if (bHasIm)
				for(m=0;m<MNi;m++)
				{
						matres->m_iData[m]=src->m_iData[0];
				}
				else if (bLhHadIm)
				{
					for(m=0;m<MNi;m++)
					{
							matres->m_iData[m]=0;
					}
				}
			}
			else
			{
				// insert real part
				for(m=0;m<MNi;m++)
				{
					ind2=(long)(I->m_rData[m]-1);
					matres->m_rData[ind2]=src->m_rData[0];
				}
				// optionally insert imagine part
				if (bHasIm)
				for(m=0;m<MNi;m++)
				{
					ind2=(long)(I->m_rData[m]-1);
						matres->m_iData[ind2]=src->m_iData[0];
				}
				else if (bLhHadIm)
				{
					for(m=0;m<MNi;m++)
					{
						ind2=(long)(I->m_rData[m]-1);
							matres->m_iData[ind2]=0;
					}
				}
			}
		}
		else
		{
			if(IsMagicColonIndex[0])
			{
				// insert real part
				for(m=0;m<MNi;m++)
				{
					matres->m_rData[m]=src->m_rData[m];
				}
				// optionally insert imagine part
				if (bHasIm)
				for(m=0;m<MNi;m++)
				{
						matres->m_iData[m]=src->m_iData[m];
				}
				else if (bLhHadIm)
				{
					for(m=0;m<MNi;m++)
					{
							matres->m_iData[m]=0;
					}
				}
			}
			else
			{
				// insert real part
				for(m=0;m<MNi;m++)
				{
					ind2=(long)(I->m_rData[m]-1);
					matres->m_rData[ind2]=src->m_rData[m];
				}
				// optionally insert imagine part
				if (bHasIm)
				for(m=0;m<MNi;m++)
				{
					ind2=(long)(I->m_rData[m]-1);
						matres->m_iData[ind2]=src->m_iData[m];
				}
				else if (bLhHadIm)
				{
					for(m=0;m<MNi;m++)
					{
						ind2=(long)(I->m_rData[m]-1);
							matres->m_iData[ind2]=0;
					}
				}

			}
		}
	}
	if (numdims==2)
	{
// 1. x(I,J)=a, size(a) = [size(I,1)*size(I,2) size(J,1)*size(J,2)]
//	  x(I(m),J(n))=a(m,n), m=1:size(I,1)*size(I,2),n=1:size(J,1)*size(J,2)
//	  x may be resized to [max(size(x,1),max(I)) max(size(x,2),max(J))]
// 2. x(I,J)=a, size(a)=[1 1].
//	  x(I(m),J(n))=a, m=1:size(I,1)*size(I,2),n=1:size(J,1)*size(J,2)
//	  x may be resized to [max(size(x,1),max(I)) max(size(x,2),max(J))]



		// check dimentions
		I=refs[0];
		J=refs[1];
		MNi=tmcNumElem(I); // size(I,1)*size(I,2)
		MNj=tmcNumElem(J); // size(J,1)*size(J,2)

		if (I->m_desc.m_type == TYPE_MAGIC_COLON)
		{
			IsMagicColonIndex[0]=1;
			MNi=_tmcGetM(matres);
		}
		if (J->m_desc.m_type == TYPE_MAGIC_COLON)
		{
			IsMagicColonIndex[1]=1;
			MNj=_tmcGetN(matres);
		}

		if (_tmcIsEmptyMatrix(src))
		{

			if (IsMagicColonIndex[0]==0 && IsMagicColonIndex[1]==0)
			{
			_tmcRaiseException(err_bad_index,s_module,"_tmcSetByIndex","x(I,J)=[],must be x(:,J) or x(I,:)",2,I,J);
			}

			// x(I,:)=[] or x(:,J)  x(:,:)=[]
			if (IsMagicColonIndex[0] && IsMagicColonIndex[1])
			{
				// x(:,:)=[]
				_tmcClearMatrix(matres);
			}
			else
			{
				if (IsMagicColonIndex[0])
				{ // x(:,J)
					_tmcClearColumns(matres,J);
				}
				else
				{ // x(I,:)
					_tmcClearRows(matres,I);
				}
			}
			return;
		}



		if (aScalar==0)
		{
			ind1_inc=1;
			if ( Ma != MNi)
			{
			_tmcRaiseException(err_bad_index,s_module,"_tmcSetByIndex","numelem(I)<>size(a,1) in x(I)=a",2,I,src);
			}
			if ( Na != MNj)
			{
			_tmcRaiseException(err_bad_index,s_module,"_tmcSetByIndex","numelem(J)<>size(a,2) in x(I)=a",2,J,src);
			}
		}
		else
		{
			ind1_inc=0; // always take only first element of src
		}
		// reshape the result matrix
		// default is not needed reshape
		max_val=_tmcGetM(matres);
		max_valJ=_tmcGetN(matres);

		if(IsMagicColonIndex[0]==0)
		{
			_tmcLongGetMaxVal(&max_val,&ind_at_max,I); // find maximal index I
		}
		if(IsMagicColonIndex[1]==0)
		{
			_tmcLongGetMaxVal(&max_valJ,&ind_at_max,J); // find maximal index J
		}
		if (max_val>_tmcGetM(matres) || max_valJ>_tmcGetN(matres))
		{
				_tmcResizeMatrix(matres,max_val,max_valJ,bHasIm);
		}
		if(bHasIm)
		{
				_tmcForceComplexMatrix(matres);// add zero imagine part if needed
		}

				// less optimized by mach simplier
				// insert real part

		// may optimize  if going by columns
		ind1=0;
		for (n=0;n<Na;n++)
		{
			i1= IsMagicColonIndex[1] ? n : (long)(J->m_rData[n]-1);// n
			for(m=0;m<Ma;m++)
			{
				i2= IsMagicColonIndex[0] ? m : (long)(I->m_rData[m]-1);// m
				//ind1= (aScalar==0)? n*Ma+m : 0; 
				ind2=(long)(i1 * _tmcGetM(matres) + i2);
				matres->m_rData[ind2]=src->m_rData[ind1];
				if (bHasIm)
					matres->m_iData[ind2]=src->m_iData[ind1];
				else if (bLhHadIm)
				{
					matres->m_iData[ind2]=0;
				}
				ind1 += ind1_inc;
			}
		}


	}
    if(src->m_desc.m_type==TYPE_STRING)
	matres->m_desc.m_type=src->m_desc.m_type;
}


void tmcGetByIndex(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix *I1,...)
// only numdims<=2 dim matrix is supported
// (I1) or (I1,I2) define the index subset; 
// Restriction:
//   1. if (I1,I2) each matrix is one-dimentioned (col or row) 
//   2. Structure array is implementes as cell array of structs.
{
va_list marker;
long k;
long M,N;
long m,n,ind1,ind2,indI;
short bHasIm;
long i1,i2;
tmsMatrix **matN = (tmsMatrix **)MYMALLOC(sizeof(tmsMatrix *) * numdims);
short IsMagicColonIndex[2]={0,0};
short bScalarSrc=0;
	matN[0]=I1;

	 _tmcClearRegister(matres);
	va_start( marker, I1 );     // Initialize variable arguments. 
	for (k=1;k<numdims;k++)
	{
		matN[k] = va_arg( marker,  tmsMatrix * );
	}
	va_end( marker );              // Reset variable arguments.      

	if (numdims>2)  
	{
		if (_tmcGetExtraDim(src)>0 )
		{
		_tmcGetByIndexMD(matres,src,(short)numdims,matN);
		MYFREE(matN);
		return;
		}
		else
		{
			numdims=2;
		}
	}



	if ((src->m_desc.m_type==TYPE_STRUCT) || (src->m_desc.m_type==TYPE_CELL_ARRAY))
	{
		// special treatment for structs array or single struct.
		// Restriction: indexing () of cell array is not supported.
		_tmcGetByIndexStruct(matres,src,matN,(short)numdims);
		MYFREE(matN);
		return;
	}

	if (numdims==1)
	{
		// if dim(src)<dim(I) then I defines dims
		// else src defines dims.
		M=_tmcGetM(matN[0]);
		N=_tmcGetN(matN[0]);
		if (( N==1) || (M==1))
		{//HAZARD
				if (_tmcGetM(src)==1 || _tmcGetN(src)==1)
				{
					// keep dim(src)
					if (_tmcGetM(src)==1)
					{
						// Special case of src=scalar.
						if (_tmcGetN(src)==1)
						{
							M=_tmcGetM(matN[0]);
							N=_tmcGetN(matN[0]);
							bScalarSrc=1;
						}
						else
						{
							M=1;
							N=tmcNumElem(matN[0]);
						}
					}
					else
					{
						N=1;
						M=tmcNumElem(matN[0]);
					}
				}
		}
	}
	if (numdims==2)
	{
		M=tmcNumElem(matN[0]); // rows
		N=tmcNumElem(matN[1]); // cols
	}
	// process magic colon
	if (numdims==1)
	{
		if (matN[0]->m_desc.m_type == TYPE_MAGIC_COLON)
		{
					M = tmcNumElem(src);
					N = 1;
					IsMagicColonIndex[0]=1;
		}
	}
	if (numdims==2)
	{
		if (matN[0]->m_desc.m_type == TYPE_MAGIC_COLON)
		{
					M = _tmcGetM(src);
					IsMagicColonIndex[0]=1;
		}
		if (matN[1]->m_desc.m_type == TYPE_MAGIC_COLON)
		{
					N = _tmcGetN(src);
					IsMagicColonIndex[1]=1;
		}

	}




	bHasIm=_tmcHasIm(src);
	_tmcCreateMatrix(matres,M,N,bHasIm);
	if (numdims==1)
	{
		for (m=0;m<M;m++)
		{
			// in matlab the matrix enumeration is by columns!
			for(n=0;n<N;n++)
			{
				ind1=n*M+m;
				if (IsMagicColonIndex[0])
				{
					indI=n*M + m;
					ind2 = indI;
				}
				else
				{
					if(bScalarSrc==0)
					{
					indI=n*_tmcGetM(matN[0]) + m;
					ind2 = (long)(matN[0]->m_rData[indI]-1);
					}
					else
					{
							ind2 = 0;
					}
				}
				matres->m_rData[ind1]=src->m_rData[ind2];
				if (bHasIm)
					matres->m_iData[ind1]=src->m_iData[ind2];
			}
		}

	}
	if (numdims==2)
	{
		for (m=0;m<M;m++)
		{
			for(n=0;n<N;n++)
			{//HAZARD- must correct
				ind1=n*M+m;
				if (IsMagicColonIndex[0])
				{
					i1=m;
				}
				else
				{
					i1=(long)(matN[0]->m_rData[m]-1);
				}
				if (IsMagicColonIndex[1])
				{
					i2=n;
				}
				else
				{
					i2=(long)(matN[1]->m_rData[n]-1);
				}

				ind2=(long)(i2 * _tmcGetM(src) + i1);

				matres->m_rData[ind1]=src->m_rData[ind2];
				if (bHasIm)
					matres->m_iData[ind1]=src->m_iData[ind2];
			}
		}

	}

    if(src->m_desc.m_type==TYPE_STRING)
	matres->m_desc.m_type=src->m_desc.m_type;

MYFREE(matN);
}


void tmcTransposeScalar(tmsMatrix *matres,tmsMatrix *src)
{
	long M,N,MN;
	long m,n;

	tmcReallocRegister(matres);


	M =_tmcGetM(src);
	N =_tmcGetN(src);
	MN=M*N;

	_tmcCreateMatrix(matres,N,M,_tmcHasIm(src) );
		for (m=0;m<M;m++)
			for (n=0;n<N;n++)
		{
				matres->m_rData[m*N+n]= src->m_rData[n*M+m] ;
		}
	if (_tmcHasIm(src))
	{
		for (m=0;m<M;m++)
			for (n=0;n<N;n++)
		{
				matres->m_iData[m*N+n]= src->m_iData[n*M+m] ;
		}
	}


}
void tmcTranspose(tmsMatrix *matres,tmsMatrix *src)
{
	long M,N,MN;
	long m,n;

	tmcReallocRegister(matres);

	M =_tmcGetM(src);
	N =_tmcGetN(src);
	MN=M*N;

	_tmcCreateMatrix(matres,N,M,_tmcHasIm(src) );
	matres->m_desc.m_type=src->m_desc.m_type;

		for (m=0;m<M;m++)
			for (n=0;n<N;n++)
		{
				matres->m_rData[m*N+n]= src->m_rData[n*M+m] ;
		}
	if (_tmcHasIm(src))
	{
		for (m=0;m<M;m++)
			for (n=0;n<N;n++)
		{
				matres->m_iData[m*N+n]= -src->m_iData[n*M+m] ;
		}
	}


}
void tmcCreateColonBaseIncLimit(tmsMatrix *matres,tmsMatrix *base,tmsMatrix *increment,tmsMatrix *limit)
{
// create [base:increment:limit]
//HAZARD
	long M,N;
	long n;

	tmcReallocRegister(matres);

	if (tmcNumElem(base)==0 || tmcNumElem(limit)==0)
	{
		M=0;N=0;
	}
	else
	{
		M =1;
		if (increment !=NULL)
		{
			if (tmcNumElem(increment)>0)
			{
				N = (long)(( limit->m_rData[0]- base->m_rData[0]) /   increment->m_rData[0])+1;
				if (N<=0)
					{
					N=0;M=0;
					}
			}
			else
			{
				M=0;N=0;
			}
		}
		else
		{
			N = (long)(( limit->m_rData[0]- base->m_rData[0]) )+1;
			if (N<=0)
			{N=0;M=0;}
		}
	}
	_tmcCreateMatrix(matres,M,N,tmcREAL );
	if (increment !=NULL)
		for (n=0;n<N;n++)
		{
			matres->m_rData[n]= base->m_rData[0] + n*  increment->m_rData[0];
		}
	else
		for (n=0;n<N;n++)
		{
			matres->m_rData[n]= base->m_rData[0] + n;
		}

}
void tmcCreateColonBaseLimit(tmsMatrix *matres,tmsMatrix *base,tmsMatrix *limit)
{
	tmcCreateColonBaseIncLimit(matres,base,NULL,limit);
}

/*void _tmcCreateRefObject(tmsMatrix *matres,enum REFERENCE_TYPES reftype,tmsMatrix *src,long numdims,tmsMatrix **refs,
						 const char *fn)
{// create matrix of the reference type
// Arguments:
//  matres: result reg
//  reftype: first reference type
//	numdims: number of dimentions addressed (not for field)
//	src: source data matrix for referencing
//  refs[numdims]: indexes list (not for field)
//  fn: field name (for field)
struct tagRefMatInfo *pRefMatInfo;


		_tmcClearRegister(matres);

		pRefMatInfo = (struct tagRefMatInfo*)MYMALLOC(sizeof(struct tagRefMatInfo) );
		pRefMatInfo->num_ref_dims = numdims;
		pRefMatInfo->refs = refs;
		pRefMatInfo->next_ref_info=NULL;
		pRefMatInfo->ref_fn=fn;
		pRefMatInfo->reftype=reftype;

	if (src->m_desc.m_type != TYPE_REF)
	{
		// Create reference object. The next assignment to it will apply the data and remove the ref info
		pRefMatInfo->src = src; // actual matrix for operation
		matres->ref_mat_info= pRefMatInfo;
		matres->last_ref_info=pRefMatInfo;
		matres->m_desc.m_type = TYPE_REF;
	}
	else
	{
		// append reference information to existing reference object
		// put at the head of the list thus as the true src is at the last object.
		pRefMatInfo->src = NULL; // actual matrix for operation

		matres->ref_mat_info= src->ref_mat_info;
		src->last_ref_info->next_ref_info = pRefMatInfo;
		
		//src->ref_mat_info->next_ref_info = pRefMatInfo;
		//src->last_ref_info = pRefMatInfo;

		matres->last_ref_info=pRefMatInfo;
		matres->m_desc.m_type = TYPE_REF;


		src->m_desc.m_type = TYPE_NOTHING; // prevent MYFREE memory twice
		src->last_ref_info=NULL;
		src->ref_mat_info=NULL;
	}
}
*/

void tmcGetRefByIndex(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix *I1,...)
{
// Creates reference object (not matrix!)
// matres = for result refernce object
// src	  = matrix to be updated
// I1 or I1,I2 = dimentions to be updated.
va_list marker;
long k;

	if (src->m_desc.m_type != TYPE_REF)
	{
		RefHelper.ndims=0;RefHelper.nrefs=0;RefHelper.src=src;
	}

	RefHelper.dims[RefHelper.ndims]=(short)numdims;
	RefHelper.type[RefHelper.ndims]='[';
	RefHelper.ndims++;

	RefHelper.refI[RefHelper.nrefs]=I1;
	RefHelper.nrefs++;

	va_start( marker, I1 );     // Initialize variable arguments. 
	for (k=1;k<numdims;k++)
	{
		RefHelper.refI[RefHelper.nrefs]=va_arg( marker,  tmsMatrix * );
		RefHelper.nrefs++;
	}
	va_end( marker );              // Reset variable arguments.   
	matres->m_desc.m_type = TYPE_REF;
}

void _tmcTransposeMatrix(tmsMatrix *V,short bScalar)
{// transpose the matrix at place

	long M,N;
	long m,n;
	short bHasIm = _tmcHasIm(V);
	double ImFac;
	double p;

	M =_tmcGetM(V);
	N =_tmcGetN(V);
	ImFac = (bScalar ? 1.0:-1.0);


		for (m=0;m<M;m++)
			for (n=0;n<N;n++)
		{
				if (n>m)
				{
					p = V->m_rData[m*N+n];
					V->m_rData[m*N+n] = V->m_rData[n*M+m];
					V->m_rData[n*M+m] =  p;
				}
		}

	if (_tmcHasIm(V))
	{
		for (m=0;m<M;m++)
			for (n=0;n<N;n++)
		{
				if (n>m)
				{
					p = V->m_iData[m*N+n];
					V->m_iData[m*N+n] = V->m_iData[n*M+m];
					V->m_iData[n*M+m] = p;
				}
		}
		for (m=0;m<M*N;m++)
				V->m_iData[m] = -V->m_iData[m];
	}
    V->m_desc.m_nCols = M;
    V->m_desc.m_nRows = N;

}
void tmcForIterInit(tmsMatrix *iteratorM,tmsMatrix *rangeM,tmsMatrix *iterator_variableM)
{
	// initializes for iteratorM=rangeM
	tmcReallocRegister(iteratorM);
	_tmcCreateMatrix(iteratorM,0,0,tmcREAL);
	iteratorM->value.ForStruct.iterator=0;
	iteratorM->value.ForStruct.iter_var = iterator_variableM;
	_tmcClearRegister(iterator_variableM);// initially the iterator variable is cleared
	iteratorM->m_desc.m_type = TYPE_ITERATOR;

}
short tmcForIterNext(tmsMatrix *iteratorM,tmsMatrix *rangeM)
{//HAZARD: must implement assuming the same structure.
	// iterates for iteratorM=rangeM
	// return 0 is proceeds (for exits),1 is cant iterate
	//Restriction: iterator variable must be matrix (not cell etc.)
	long iter;
	tmsMatrix *iter_var;
	long m;
	long M = _tmcGetM(rangeM);
	long r_len = _tmcGetN(rangeM);
	if (iteratorM->value.ForStruct.iterator >= r_len)
	{
		// may clear iterator here - HAZARD_BUG_BUG: must assign the latest value to the variable

	//HAZARD_BUG_BUG	_tmcClearRegister(iteratorM->value.ForStruct.iter_var);
		_tmcClearRegister(iteratorM);
		return 1;
	}
	else
	{
		// assign new value to the iterator
		iter=iteratorM->value.ForStruct.iterator;
		//_tmcClearRegister(iteratorM->iter_var);
		if (iteratorM->value.ForStruct.iter_var->m_desc.m_type == TYPE_NOTHING)
		{	// re-crate the matrix only for the first iteration. It must preserve the same sizes.
			_tmcCreateMatrix(iteratorM->value.ForStruct.iter_var,M,1,(short)(_tmcHasIm(rangeM) ));
		}
		iter_var = iteratorM->value.ForStruct.iter_var;
		for (m=0;m<M;m++)
		{   // get m-th column of rangeM
			iter_var->m_rData[m]=rangeM->m_rData[iter*M+m];
			if (_tmcHasIm(rangeM) )
			{
				iter_var->m_iData[m]=rangeM->m_iData[iter*M+m];
			}
		}
		iteratorM->value.ForStruct.iterator++;
		
		return 0;
	}
}

void tmcCreateMagicColon(tmsMatrix *magcolM)
{
	tmcReallocRegister(magcolM);
	_tmcCreateMatrix(magcolM,0,0,tmcREAL);
	magcolM->m_desc.m_type = TYPE_MAGIC_COLON;
}



short _Mstrcmp(tmsMatrix *x,const char *fn)
{// return 0 is string matrix == fn
	short k;
	short stat=-1;
	long len= tmcNumElem(x);
	const char *p = fn;

	for (k=0; k<len;k++)
	{
		if (*p==0)
			return -1;
		if (*p !=(char)x->m_rData[k])
			return -1;
		p++;
	}
	if (*p == 0)
		return 0;
	else
		return -1;
}


short _tmcGetString(const tmsMatrix *src , char *str_des , long maxlen )
{ // analog of mxGetString
long n;
	if (src->m_desc.m_type != TYPE_STRING)
		return -1;

	for(n=0;n<_tmcGetN(src) && n<maxlen-1;n++)
	{
		str_des[n] = (char)src->m_rData[n];
	}
	str_des[n]=0;

return 0;
}

char* _tmcMat2String(tmsMatrix *src)
{// create char buffer

char *buf;
long n;

	buf = MYMALLOC(sizeof(char)*(_tmcGetN(src)+1));
	for(n=0;n<_tmcGetN(src);n++)
	{
		buf[n] = (char)src->m_rData[n];
	}
	buf[n]=0;
return buf; // must be MYFREE by caller
}

wchar_t* _tmcMat2UniString(tmsMatrix *src)
{// create UNICODE buffer

wchar_t *buf;
long n;

	buf = MYMALLOC(sizeof(wchar_t)*(_tmcGetN(src)+1));
	for(n=0;n<_tmcGetN(src);n++)
	{
		buf[n] = (wchar_t)src->m_rData[n];
	}
	buf[n]=0;
return buf; // must be MYFREE by caller
}
unsigned short * _tmcMat2StringW(tmsMatrix *src)
{// create short buffer for save()

	unsigned short *buf;
	long n;

	buf = MYMALLOC(sizeof(unsigned short)*(_tmcGetN(src) + 1));
	for (n = 0; n<_tmcGetN(src); n++)
	{
		buf[n] = (unsigned short)src->m_rData[n];
	}
	buf[n] = 0;
	return buf; // must be MYFREE by caller
}

char* _tmcMat2StringESC(tmsMatrix *src)
{// create char buffer for sprintf,fprintf
 // correction: convert ESC-seq 
/* SPRINTF:
The special formats \n,\r,\t,\b,\f can be used to produce linefeed,
    carriage return, tab, backspace, and formfeed characters respectively.
    Use \\ to produce a backslash character and %% to produce the percent
    character.
*/
char *buf;
long n,n2;
long len;
char c1,c2;	

	len = _tmcGetN(src);
	buf = MYMALLOC(sizeof(char)*(len+1));
	for(n=0,n2=0;n<len;n++,n2++)
	{
		c1 = (char)src->m_rData[n];
		if (c1 == '\\' && n<len-1)
		{
			c2 = (char)src->m_rData[n+1];
			switch (c2)
			{
			case '\\':
				n++;break;
			case 'r':
				c1='\r';n++;break;
			case 'n':
				c1='\n';n++;break;
			case 't':
				c1='\t';n++;break;
			case 'b':
				c1='\b';n++;break;
			case 'f':
				c1='\f';n++;break;
			case '%':
				c1='%';n++;break;
			default:
				c1=c2;n++;
			}
		}
		buf[n2] = c1;
	}
	buf[n2]=0;
return buf; // must be MYFREE by caller
}




void _tmcSetString(tmsMatrix *y,const char *str)
{
long n;
	long len = (long)strlen(str); //x64 without NULL-termination.
	_tmcCreateMatrix(y,1,len,tmcREAL);
	y->m_desc.m_type = TYPE_STRING;
	for(n=0;n<len;n++)
		y->m_rData[n]=str[n];
}

void tmcCreateString(tmsMatrix *matres,const char *str)
{
	// In MATLAB all implicit strings  have no ESC-seq, thus in TMC they contain
	// additional \.
	// In C exist Escape Sequences
	// only sprintf and fprintf functions convert the formats TMC to C
	// e.g. "\\r" ->> "\r"
	tmcReallocRegister(matres);
	_tmcSetString(matres,str);
}

void _mreadcomplex(double *re,double *im,char *str)
{// HAZARD: only real values are supported
short k;
short len;
	len  = (short)strlen(str);//x64
	for (k=0;k<len;k++)
	{
		if (str[k]=='i' || str[k]=='j')
				_tmcRaiseException(err_unsupported,"main","tmcstr2num","comlplex values unsupported",0,NULL);
	}
	*re=  atof(str);
	*im=  0;
}

void tmcstr2num(long nout,long ninput,tmsMatrix *y,tmsMatrix *x)
{
	long nNum;
	char* token;
	double re,im;
	short bHasIm=tmcREAL;
	char* str =  _tmcMat2String(x);
	const char seps[]   = " ,\t\n";

	nNum=0;
	token = strtok( str, seps );
    while( token != NULL )
    {
	   nNum++;
	   _mreadcomplex(&re,&im,token);
	   if (im !=0)
	   {
			bHasIm=tmcCOMPLEX;
	   }
       token = strtok( NULL, seps );
    }
	_tmcCreateMatrix(y,1,nNum,bHasIm);
	nNum=0;
	if (str)
		MYFREE(str);
	str =  _tmcMat2String(x);
	token = strtok( str, seps );
    while( token != NULL )
    {
	   nNum++;
	   _mreadcomplex(&re,&im,token);
			 y->m_rData[nNum-1]= re;
	   if (bHasIm==tmcCOMPLEX)
	   {
			 y->m_iData[nNum-1]= im;
	   }
       token = strtok( NULL, seps );
    }




	if (str)
		MYFREE(str);
}


short Dig2Num(char c)
{
	short n;

	if (c >= 'a' && c<='f')
		n = c-'a'+10;
	else
		if (c >= 'A' && c<='F')
			n = c-'A'+10;
		else
			if (c >= '0' && c<='9')
				n = c- '0';
			else
				n=0;
	return n;
}
void tmchex2dec(long nout,long ninput,tmsMatrix *y,tmsMatrix *x)
{
	short k;
	double scale=1;
	double res=0;
	
	short len=(short)tmcNumElem(x);
	for (k=len-1;k>=0;k--)
	{
		res += scale * Dig2Num((char)x->value.complx.rData[k]);
		scale *= 16;

	}
	_tmcCreateMatrix(y,1,1,tmcREAL);
	y->m_rData[0]=  res;
	

}

const char dig2c[17]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F',0};
void tmcdec2hex(int nargout, int nargin,tmsMatrix *y,tmsMatrix *x,tmsMatrix *n)
{
short maxnumdigs,numdigs;
short m;
double dval;
__int64 val;
short k;
short c,mask,rshifts;
	
	maxnumdigs=0;
	for (m=0; m< tmcNumElem(x);m++)
	{
		dval =  x->value.complx.rData[m];
		if (dval >  BITMAX || dval < 0)
		{
				_tmcRaiseException(out_of_int_range,s_module,"dec2hex","X must be 0..2^53-1",1,x);
		}
		val = (__int64)floor(dval);
		if (val != dval)
		{
				_tmcRaiseException(out_of_int_range,s_module,"dec2hex","X must be integer",1,x);
		}
		if (dval>0)
		numdigs = (short)floor(log10(dval)/log10(16.0)+1);
		else
			numdigs = 1;

		if (numdigs>maxnumdigs)
				maxnumdigs=numdigs;
	}
	if (nargin==2 && n->value.complx.rData[0]>maxnumdigs)
			maxnumdigs = (short)n->value.complx.rData[0];

	_tmcCreateMatrix(y,tmcNumElem(x),maxnumdigs,tmcREAL);
	y->m_desc.m_type = TYPE_STRING;
	for (m=0; m< tmcNumElem(x);m++)
	{
		dval =  x->value.complx.rData[m];
		val = (__int64)floor(dval);
		mask = 0xF;
		rshifts =0;
		for (k=0;k<maxnumdigs;k++)
		{
			c = (short)((val>>rshifts) &  mask);
			rshifts += 4;
			y->value.complx.rData[m*maxnumdigs + (maxnumdigs-k-1)] = dig2c[c];
		}
	}
}

short tmcNotCase(tmsMatrix *expression,tmsMatrix *case_value)
{// return 0 is expression=value, otherwise return 1
long ind;
long Na=tmcNumElem(expression);
long Nb=tmcNumElem(case_value);
short c;
short stat;

	if (expression->m_desc.m_type == TYPE_STRUCT)
	{
	_tmcRaiseException(err_invalid_switch_exp,s_module,"tmcNotCase","Switch expression may not be STRUCT",2,case_value,expression);
	return 1;
	}
	if (case_value->m_desc.m_type != TYPE_MATRIX && case_value->m_desc.m_type != TYPE_CELL_ARRAY && case_value->m_desc.m_type != TYPE_STRING)
	{
	_tmcRaiseException(err_invalid_switch_exp,s_module,"tmcNotCase","Case expression must be MATRIX, STRING or CELL ARRAY",2,case_value,expression);
	return 1;
	}

	if (case_value->m_desc.m_type==TYPE_MATRIX || case_value->m_desc.m_type==TYPE_STRING)
	{
	if (Na!=Nb)
		return 1;

	for (ind=0;ind<Na;ind++)//HAZARD_TODO: case_value may be cell array !!!
		if (expression->m_rData[ind] != case_value->m_rData[ind])
		{
			return 1;
		}
	return 0;
	}
	else // TYPE_CELL_ARRAY
	{
		for (c=0;c<Nb;c++)
		{
			stat=tmcNotCase(expression,case_value->value.m_cells[c]);
			if (stat==0)
				return 0;// if one of cells is matched - case is valid
		}
		return 1;// no cells matched - not this case 
	}
}


void  tmcGetEnd(tmsMatrix *matres,tmsMatrix *src,long dim,long numdims)
{
	long d=0;

	if (numdims==2)
	{
			if (dim==1)
			{
				d=_tmcGetM(src);
			}
			else if (dim==2)
			{
				d=_tmcGetN(src);
			}
	}
	else if (numdims==1)
	{
		d = _tmcGetM(src)*_tmcGetN(src);
	}
			tmcScalar(matres,(double)d);
}

void tmcsize(long nout,long ninput,tmsMatrix *out1,...)
//void tmcsize(long nout,long ninput, tmsMatrix *out1,tmsMatrix *out2,tmsMatrix *out3,tmsMatrix *X,tmsMatrix *dim)
{
tmsMatrix *out2;
tmsMatrix *out3;
tmsMatrix *X;
tmsMatrix *dim;
tmsMatrix **matN;
va_list marker;
short xndims;
short k;

	va_start( marker, out1 );     // Initialize variable arguments. 

	if (nout==1)
	{
		// n=size(X) is vector of ndims
		// n=size(X,dim) is scalar
		X= va_arg( marker,  tmsMatrix * );
		xndims = _tmcGetNdim(X);

		if (ninput==1)
		{
			_tmcCreateMatrix(out1,1,xndims,tmcREAL);
			if (xndims==2)
			{
			out1->m_rData[0]=_tmcGetM(X);
			out1->m_rData[1]=_tmcGetN(X);
			}
			else
			{
			out1->m_rData[0]=_tmcGetM(X);
				for (k=1;k<xndims;k++)
				{
					out1->m_rData[k]=_tmcGetDim(X,k+1);
				}
			}
		}
		else if (ninput==2)
		{
			dim= va_arg( marker,  tmsMatrix * );
			_tmcCreateMatrix(out1,1,1,tmcREAL);
			if (xndims==2)
			{
				if (dim->m_rData[0]==1)
				{
					out1->m_rData[0]=_tmcGetM(X);
				}
				else if (dim->m_rData[0]==2)
				{
					out1->m_rData[0]=_tmcGetN(X);
				}
				else
					out1->m_rData[0]=1;// singleton
			}
			else
			{
				k = (short)(dim->m_rData[0]);
				out1->m_rData[0]= _tmcGetDimS(X,k);// may be singleton dimention
			}
		}
	}
	else if (nout==2)
	{
		// [m,n]=size(X), also for multi-dim
		out2= va_arg( marker,  tmsMatrix * );
		X	= va_arg( marker,  tmsMatrix * );

			_tmcCreateMatrix(out1,1,1,tmcREAL);
			out1->m_rData[0]=_tmcGetM(X);
			_tmcCreateMatrix(out2,1,1,tmcREAL);
			out2->m_rData[0]=_tmcGetN(X);
	}
	else if (nout==3)
	{
		// [m,n,k]=size(X)
		out2= va_arg( marker,  tmsMatrix * );
		out3= va_arg( marker,  tmsMatrix * );
		X	= va_arg( marker,  tmsMatrix * );

			_tmcCreateMatrix(out1,1,1,tmcREAL);
			out1->m_rData[0]=_tmcGetM(X);

			_tmcCreateMatrix(out2,1,1,tmcREAL);
			_tmcCreateMatrix(out3,1,1,tmcREAL);
			
			xndims = _tmcGetExtraDim(X);
			if ( xndims )
			{
				out2->m_rData[0]=_tmcGetDimS(X,2);
				out3->m_rData[0]=_tmcGetDimS(X,3);
			}
			else
			{
				out2->m_rData[0]=_tmcGetN(X);
				out3->m_rData[0]=1;
			}
	}
	else 
	{ // more than 3 dims
		matN = (tmsMatrix **)MYMALLOC(sizeof(tmsMatrix *) * nout);
		matN[0]=out1;
		for (k=1;k<nout;k++)
		{
			matN[k]= va_arg( marker,  tmsMatrix * );
		}
		X	= va_arg( marker,  tmsMatrix * );
		xndims = _tmcGetExtraDim(X);
		for (k=0;k<nout;k++)
		{
			_tmcCreateMatrix(matN[k],1,1,tmcREAL);
			if ( xndims )
			{
				matN[k]->m_rData[0]=_tmcGetDimS(X,k+1);
			}
			else
			{
				if (k==0)
					matN[k]->m_rData[0]= _tmcGetM(X);
				else if (k==1)
					matN[k]->m_rData[0]= _tmcGetN(X);
				else
					matN[k]->m_rData[0]=1;
			}
		}
	}

	
	va_end( marker );              // Reset variable arguments.      


}
void tmclength(long nout,long ninput, tmsMatrix *len, tmsMatrix *X)
{
			_tmcCreateMatrix(len,1,1,tmcREAL);
			if (tmcNumElem(X)==0)
				len->m_rData[0]=0;
			else

			if (_tmcGetN(X)>_tmcGetM(X))
			{
				len->m_rData[0]=_tmcGetN(X);
			}
			else
				len->m_rData[0]=_tmcGetM(X);
}
void tmciscell(long nout,long ninput,tmsMatrix *y,tmsMatrix *x)
{
			_tmcCreateMatrix(y,1,1,tmcREAL);
			y->m_rData[0]=  ( (x->m_desc.m_type ==TYPE_CELL_ARRAY) ? 1:0);
}

void tmcisempty(long nout,long ninput,tmsMatrix *y,tmsMatrix *x)
{
			_tmcCreateMatrix(y,1,1,tmcREAL);
			if (x->m_desc.m_type == TYPE_STRUCT)
			{
				y->m_rData[0]= (_tmcGetNf(x)==0 ? 1:0);
			}
			else
				y->m_rData[0]=_tmcIsEmptyMatrix(x);
}


void tmcstrcmp(long nout,long ninput, tmsMatrix *y,tmsMatrix *s1,tmsMatrix *s2)
{ 
	long cnt;
	long len1,len2;
	short stat=1;

	// return 1 if s1==s2 otherwise return 0
	// if s1 or s2 is not string return 0. 
	if ((s1->m_desc.m_type == TYPE_STRING || s1->m_desc.m_type == TYPE_MATRIX) &&
		(s2->m_desc.m_type == TYPE_STRING || s2->m_desc.m_type == TYPE_MATRIX))
	{
		len1=tmcNumElem(s1);
		len2=tmcNumElem(s2);
		if (len1 == len2)
		{
			for (cnt=0;cnt<len1;cnt++)
			{
				if (s1->m_rData[cnt] != s2->m_rData[cnt])
				{
					stat= 0;
					break;
				}
			}
		}
		else
		{
				stat=0;
		}
	}
	else
	{
		stat=0;
	}
	_tmcCreateMatrix(y,1,1,tmcREAL);
	y->m_rData[0]=stat;
}
void tmcdiff(long nout,long ninput, tmsMatrix *dx,tmsMatrix *x)
{ // restriction: dx=diff(x) only syntax is supported
long M,N;
long m,n;
	M=_tmcGetM(x);
	N=_tmcGetN(x);


	if (_tmcIsMatrix(x))
	{
		_tmcCreateMatrix(dx,M-1,N,_tmcHasIm(x));
		for (n=0;n<N;n++)
		{
			for (m=0;m<M-1;m++)
			{
				dx->m_rData[m+n*(M-1)] = x->m_rData[m+1+n*M]-x->m_rData[m+n*M];
			}
			if (_tmcHasIm(x))
				for (m=0;m<M-1;m++)
				{
					dx->m_iData[m+n*(M-1)] = x->m_iData[m+1+n*M]-x->m_iData[m+n*M];
				}
		}
	}
	else
	{
		if (M>1)
		{
			_tmcCreateMatrix(dx,M-1,N,_tmcHasIm(x));
		}
		else // N>1
		{
			_tmcCreateMatrix(dx,M,N-1,_tmcHasIm(x));
		}
		for (m=0;m<M*N-1;m++)
		{
			dx->m_rData[m] = x->m_rData[m+1]-x->m_rData[m];
		}
		if (_tmcHasIm(x))
		for (m=0;m<M*N-1;m++)
		{
			dx->m_iData[m] = x->m_iData[m+1]-x->m_iData[m];
		}
	}

}
void tmcfind(long nout,long ninput, tmsMatrix *I,tmsMatrix *J,tmsMatrix *V, tmsMatrix *x,tmsMatrix *Opt,tmsMatrix *sOpt)
{
	long len;
	short b;
	long m,k,n;
	long MN,M,N; 
	long M0,N0,k0;
	long MaxNumToFind=-1;
	char cOpt;
	short bFirst=-1;

		// RESTRICTION: the only case supported: I=find(X,opt,sopt)
		MN =  tmcNumElem(x);
		M0 = _tmcGetM(x);
		N0 = _tmcGetN(x);

		if (ninput>1)
		{
			MaxNumToFind =(long)_tmcScalarVal(Opt);
		}
		if (ninput>2)
		{
			cOpt = (char)_tmcScalarVal(sOpt);
			if (cOpt=='f' || cOpt=='F')
				bFirst=1;
			else
				bFirst=0;
		}

	if (MaxNumToFind<0)
	{
		len=0;
		for (m=0;m< MN;m++)
		{
			if (_tmcHasIm(x))
			{
				if (x->m_rData[m] || x->m_iData[m])
					len++;
			}
			else
			{
				if (x->m_rData[m] )
					len++;
			}
		}

		// decide outputs dimensions
		if (_tmcGetM(x)==1) // X is row
		{
			M=1;N=len;// also row
		}
		else if (_tmcGetN(x)==1  ) // X is column
		{
			N=1;M=len;
		}
		else // may be matrix 
		{
			N=1;M=len; // always column

		}
		if (len==0)
		{
				M=0;N=0;
		}

		_tmcCreateMatrix(I,M,N,tmcREAL);
		if (nout > 1)
		_tmcCreateMatrix(J,M,N,tmcREAL);
		if (nout > 2)
		_tmcCreateMatrix(V,M,N,_tmcHasIm(x));

		// decide output variable
		if (nout==1) // [I]=find
		{
			k=0;
			for (m=0;m< MN;m++)
			{
				if (_tmcHasIm(x))
				{
					if (x->m_rData[m] || x->m_iData[m])
						I->m_rData[k++]=1+m;// 1-based
				}
				else
				{
					if (x->m_rData[m] )
						I->m_rData[k++]=1+m;// 1-based
				}
				
			}
		}
		else // [I,J]=find
		{
			k=0;
			k0=0;
			for (n=0;n< N0;n++)
				for (m=0;m<M0;m++)
				{
					if (_tmcHasIm(x))
					{
						b= ( (x->m_rData[k0] || x->m_iData[k0]) ? 1:0  );
					}
					else
					{
						b= ( (x->m_rData[k0] ) ? 1:0  );
					}
						if (b)
						{
							I->m_rData[k]=1+m;// 1-based
							J->m_rData[k]=1+n;// 1-based
							if (nout > 2)
							{
								V->m_rData[k]=x->m_rData[k0];// value itself
								if (_tmcHasIm(x))
								{
										V->m_iData[k]=x->m_iData[k0];
								}
							}
							k++;
						}
						k0++;
				}
		}
	}
	else
	{//HAZARD - not implemented for [I,J]
		// first count the number of data
		if (nout>1)
		{//HAZARD_TODO
		_tmcRaiseException(err_unsupported,s_module,"[I,J]=find()","I=find():unsupported more than 1 outputs",0,NULL);
		}

		len=0;
		for (m=0;m< MN;m++)
		{
			if (_tmcHasIm(x))
			{
				if (x->m_rData[m] || x->m_iData[m])
					len++;
			}
			else
			{
				if (x->m_rData[m] )
					len++;
			}
			if (len>=MaxNumToFind)
			{
				break;
			}
		}
		if (_tmcGetM(x)==1)
		{
			M=1;N=len;
		}
		else
		{
			N=1;M=len;
		}
		if (len==0)
		{
				M=0;N=0;
		}
		_tmcCreateMatrix(I,M,N,tmcREAL);
		if (nout > 1)
		_tmcCreateMatrix(J,M,N,tmcREAL);
		if (nout > 2)
		_tmcCreateMatrix(V,M,N,_tmcHasIm(x));


		if (len==0)
			return; // I=empty

		if (bFirst==0)
		{// inverse order - find last

			k=len-1;
			for (m=MN-1;m>=0;m--)
			{
				if (_tmcHasIm(x))
				{
					if (x->m_rData[m] || x->m_iData[m])
						I->m_rData[k--]=1+m;// 1-based
				}
				else
				{
					if (x->m_rData[m] )
						I->m_rData[k--]=1+m;// 1-based
				}
				if (k<0)
				{
					break; // done
				}
			}
		}
		else
		{
			k=0;
			for (m=0;m<MN;m++)
			{
				if (_tmcHasIm(x))
				{
					if (x->m_rData[m] || x->m_iData[m])
						I->m_rData[k++]=1+m;// 1-based
				}
				else
				{
					if (x->m_rData[m] )
						I->m_rData[k++]=1+m;// 1-based
				}
				if (k>=len)
				{
					break; // done
				}
			}

		}
	}

	//if (nout>1)
	//{//HAZARD_TODO
	//	if (_tmcIsMatrix(x))
	//	_tmcRaiseException(err_unsupported,s_module,"[I]=find()","I=find():unsupported more than 1 outputs",0,NULL);
	//	
	//	_tmcCreateMatrix(J,_tmcGetM(I),_tmcGetN(I),tmcREAL);
	//	len= tmcNumElem(J);
	//	for (k=0;k<len;k++)
	//		J->value.complx.rData[k]=1.0;
//
	//	//J->m_rData[0]=1;
	//}
	//if (nout>2)
	//{
	//	//if (_tmcIsMatrix(x))
	//	_tmcRaiseException(err_unsupported,s_module,"[I]=find()","I=find():unsupported more than 1 outputs",0,NULL);
//
//		//_tmcCreateMatrix(V,_tmcGetM(I),_tmcGetN(I),tmcREAL);
//		//len= tmcNumElem(V);
//		//for (k=0;k<len;k++)
//		//	V->value.complx.rData[k]=1.0;
//
//		//V->m_rData[0]=1;
//	}

}

void tmcisstruct(long nout,long ninput,tmsMatrix *y,tmsMatrix *x)
{
			_tmcCreateMatrix(y,1,1,tmcREAL);
			y->m_rData[0]=  ( (x->m_desc.m_type ==TYPE_STRUCT) ? 1:0);
}
void tmcisnumeric(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
			_tmcCreateMatrix(y,1,1,tmcREAL);
			y->m_rData[0]=  ( (x->m_desc.m_type ==TYPE_MATRIX) ? 1:0);
}
void tmcisreal(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
			_tmcCreateMatrix(y,1,1,tmcREAL);
			y->m_rData[0]=  ( (x->m_desc.m_type ==TYPE_MATRIX) && (_tmcHasIm(x)==0)  ? 1:0);
}


void tmcsort(long nout,long ninput, tmsMatrix *y1,tmsMatrix *y2,tmsMatrix *x,tmsMatrix *c)
{
//	char bSort_Mode;
//  Restriction: image part is ignored. HAZARD
	long MN;
	struct Creal_sort *pC;
	struct Ccomplex_sort *pCC;

	long k;
	short bDescend=0;
	int (*pFuncCompare)(const void*,const void*) ;

	if (ninput>1 && (_tmcIsChar(c)) && c->value.complx.rData[0]=='d')
		{
			bDescend=1;
		}
		MN = tmcNumElem(x);
		_tmcCreateMatrix(y1,_tmcGetM(x),_tmcGetN(x),_tmcHasIm(x));
		if (nout>1)
		{
		_tmcCreateMatrix(y2,_tmcGetM(x),_tmcGetN(x),tmcREAL);
		}
		if (nout==1)
		{
			if (_tmcHasIm(x))
			{
				pCC = MYMALLOC(sizeof(struct Ccomplex_sort)*MN);
				for (k=0;k<MN;k++)
				{
						pCC[k].val_re=x->m_rData[k];
						pCC[k].val_im=x->m_iData[k];
				}
				if (bDescend)
					pFuncCompare=cvalindcompare_descend;
				else
					pFuncCompare=cvalindcompare;

				qsort(pCC,MN,sizeof(struct Ccomplex_sort),pFuncCompare);
				for (k=0;k<MN;k++)
				{
						y1->m_rData[k]  = pCC[k].val_re;
						y1->m_iData[k]  = pCC[k].val_im;
				}

				MYFREE(pCC);
			}
			else
			{
			memcpy(y1->m_rData,x->m_rData,sizeof(double)*MN);
			if (bDescend)
				pFuncCompare=dcompare_descend;
			else
				pFuncCompare=dcompare;
			qsort(y1->m_rData,MN,sizeof(double),pFuncCompare);
			}
		}
		else
		{
			// nout=2
			if (_tmcHasIm(x))
			{
				pCC = MYMALLOC(sizeof(struct Ccomplex_sort)*MN);
				for (k=0;k<MN;k++)
				{
						pCC[k].val_re=x->m_rData[k];
						pCC[k].val_im=x->m_iData[k];
						pCC[k].ind = k+1;
				}
				if (bDescend)
					pFuncCompare=cvalindcompare_descend;
				else
					pFuncCompare=cvalindcompare;

				qsort(pCC,MN,sizeof(struct Ccomplex_sort),pFuncCompare);
				for (k=0;k<MN;k++)
				{
						y1->m_rData[k]=pCC[k].val_re;
						y1->m_iData[k]=pCC[k].val_im;
						y2->m_rData[k]=pCC[k].ind;
				}
				MYFREE(pCC);

			}
			else
			{
				pC = MYMALLOC(sizeof(struct Creal_sort)*MN);
				for (k=0;k<MN;k++)
				{
						pC[k].val_re=x->m_rData[k];
						pC[k].ind = k+1;
				}
				if (bDescend)
					pFuncCompare=valindcompare_descend;
				else
					pFuncCompare=valindcompare;

				qsort(pC,MN,sizeof(struct Creal_sort),pFuncCompare);
				for (k=0;k<MN;k++)
				{
						y1->m_rData[k]=pC[k].val_re;
						y2->m_rData[k]=pC[k].ind;
				}
				MYFREE(pC);
			}
//fp=fopen("debugout.mat","wb");
//	tmcStoreMat(fp ,"x" , x);
//	tmcStoreMat(fp ,"y1" , y1);
//	tmcStoreMat(fp ,"y2" , y2);
//fclose(fp);
		}
}
void tmcisscalar(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),tmcREAL);
		if (x->m_desc.m_type==TYPE_MATRIX && _tmcGetM(x) ==1 && _tmcGetN(x)==1)
		{
			y->m_rData[0]=1.0;
		}
		else
			y->m_rData[0]=0;
}
void tmcisvector(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),tmcREAL);
		if (x->m_desc.m_type==TYPE_MATRIX && ((_tmcGetM(x) ==1 && _tmcGetN(x)>=0) || (_tmcGetM(x) >=0 && _tmcGetN(x)==1)))
		{
			y->m_rData[0]=1.0;
		}
		else
			y->m_rData[0]=0;
}

void tmcall(long nout,long ninput, tmsMatrix *y,tmsMatrix *x,tmsMatrix *dim_a)
{

	long m,n,MN,M,N,offMN;
	short res=1;
	//For vectors, all(X) is true is all X are non-zero
	//For matrices, all(X) is a row vector with all() over each column.
	if (ninput>1)
			_tmcRaiseException(err_bad_index,s_module,"all","all(X,n) unsupported ninput=2",1,x);
	if (_tmcIsMatrix(x))
	{
		N=_tmcGetN(x);
		M=_tmcGetM(x);

		_tmcCreateMatrix(y,1,_tmcGetN(x),tmcREAL);
		for (n=0;n<N;n++)
		{
				offMN = n*M;
				for (m=0;m<M;m++)
					if (x->m_rData[offMN+m]==0)
					{
						res=0;	
						break;
					}
				if (_tmcHasIm(x))
				{
					for (m=0;m<M;m++)
					if (x->m_iData[offMN+m]==0)
					{
						res=0;	
						break;
					}
				}
				y->m_rData[n]=res;
		}
	}
	else
	{
		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,1,1,tmcREAL);
		for (n=0;n<MN;n++)
		{
			if (x->m_rData[n]==0)
			{
				res=0;	
				break;
			}
		}

		if (_tmcHasIm(x))
		{
			for (n=0;n<MN;n++)
			{
				if (x->m_iData[n]==0)
				{
					res=0;	
					break;
				}
			}
		}
		y->m_rData[0]=res;
	}
}
void tmcany(long nout,long ninput, tmsMatrix *y,tmsMatrix *x,tmsMatrix *dim_a)
{

	long m,n,MN,M,N,offMN;
	short res=0;
	//For vectors, any(X) is true is any of X are non-zero
	//For matrices, any(X) is a row vector with any() over each column.
	if (ninput>1)
			_tmcRaiseException(err_bad_index,s_module,"any","any(X,n) unsupported ninput=2",1,x);
	if (_tmcIsMatrix(x))
	{
		N=_tmcGetN(x);
		M=_tmcGetM(x);

		_tmcCreateMatrix(y,1,_tmcGetN(x),tmcREAL);
		for (n=0;n<N;n++)
		{
				offMN = n*M;
				for (m=0;m<M;m++)
					if (x->m_rData[offMN+m]!=0)
					{
						res=1;	
						break;
					}
				if (_tmcHasIm(x))
				{
					for (m=0;m<M;m++)
					if (x->m_iData[offMN+m]!=0)
					{
						res=1;	
						break;
					}
				}
				y->m_rData[n]=res;
		}
	}
	else
	{
		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,1,1,tmcREAL);
		for (n=0;n<MN;n++)
		{
			if (x->m_rData[n]!=0)
			{
				res=1;	
				break;
			}
		}

		if (_tmcHasIm(x))
		{
			for (n=0;n<MN;n++)
			{
				if (x->m_iData[n]!=0)
				{
					res=1;	
					break;
				}
			}
		}
		y->m_rData[0]=res;
	}
}




void tmcimag(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
long MN,k;

		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),tmcREAL);
		if (_tmcHasIm(x))
		{
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]=x->m_iData[k];
			}
		}
		else
		{
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]=0;
			}
		}
}
void tmcconj(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
long MN,k;

		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),_tmcHasIm(x));
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]=x->m_rData[k];
			}
		if ( _tmcHasIm(x) )
		{
			for (k=0;k<MN;k++)
			{
				y->m_iData[k]=-x->m_iData[k];
			}
		}


}

void tmcreal(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
long MN,k;

		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),tmcREAL);
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]=x->m_rData[k];
			}
}


void _tmcOnesFac(long nout,long ninput,tmsMatrix *Y, tmsMatrix *in1,tmsMatrix *in2,double fac)
{
long M;
long N;
long ind;
long dLen;

	if (ninput==1)
	{
		// Y=ones(mm)
		// Y=ones([m n])
		if (tmcNumElem(in1)==1)
		{
			M=(long)in1->m_rData[0];
			N=M;
		}
		else if(tmcNumElem(in1)==2)
		{
			M=(long)in1->m_rData[0];
			N=(long)in1->m_rData[1];
		}
	}
	else if (ninput==2)
	{
		// Y=ones(m,n)
		M = (long)in1->m_rData[0];
		N = (long)in2->m_rData[0];
	}
	_tmcCreateMatrix(Y,M,N,tmcREAL);
	if (fac>=0) // ones or zeros
		for (ind=0;ind<M*N;ind++)
		{
			Y->m_rData[ind]=fac;
		}
	else if (fac==-1)// eye
	{
		dLen = min(M,N);
		for (ind=0;ind<dLen;ind++)
		{
			Y->m_rData[ind+ind*M]=1.0f;
		}
	}
	else if (fac==-2) // rand
	{
		for (ind=0;ind<M*N;ind++)
		{
			Y->m_rData[ind]=rand()/(double)RAND_MAX;
		}
	}
}

void _tmczeros2D(long nout,long ninput,tmsMatrix *Y, tmsMatrix *in1,tmsMatrix *in2);
void tmczeros(long nout,long ninput,tmsMatrix *Y, tmsMatrix *in1,...)
{
tmsMatrix *in2;
long *arrdims;
short cnt;
	va_list marker;
	va_start( marker, in1 );     // Initialize variable arguments. 

	if (ninput<3)
	{
		in2 = va_arg( marker,  tmsMatrix * );
		_tmczeros2D(nout,ninput,Y,in1,in2);//HAZARD: not all syntax supported
	}
	else
	{
		arrdims = (long*)MYMALLOC(sizeof(long)*ninput);
		arrdims[0]= (long)_tmcScalarVal(in1);
		for (cnt=1;cnt<ninput;cnt++)
		{
					in2 = va_arg( marker,  tmsMatrix * );
					arrdims[cnt]=(long)_tmcScalarVal(in2);
		}
		_tmcCreateMatrixMD(Y,(short)ninput,arrdims,tmcREAL);
		MYFREE(arrdims);
	}
	va_end( marker );              // Reset variable arguments.      

}

void tmcones(long nout,long ninput,tmsMatrix *Y, tmsMatrix *in1,tmsMatrix *in2)
{
	_tmcOnesFac(nout,ninput,Y,in1,in2,1);
}
void _tmczeros2D(long nout,long ninput,tmsMatrix *Y, tmsMatrix *in1,tmsMatrix *in2)
{//HAZARD: not all syntax supported
	_tmcOnesFac(nout,ninput,Y,in1,in2,0);
}
void tmceye(long nout,long ninput,tmsMatrix *Y, tmsMatrix *in1,tmsMatrix *in2)
{
	_tmcOnesFac(nout,ninput,Y,in1,in2,-1);
}


void tmcfliplr(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
//FLIPLR(X) returns X with row preserved and columns flipped in the left/right direction.

long M,N,k;
		M=_tmcGetM(x);
		N=_tmcGetN(x);
		_tmcCreateMatrix(y,M,N,_tmcHasIm(x));

			for (k=0;k<N;k++)
			{
				memcpy(&y->m_rData[k*M],&x->m_rData[(N-1-k)*M],sizeof(double)*M);
			}
		if (_tmcHasIm(x))
			for (k=0;k<N;k++)
			{
				memcpy(&y->m_iData[k*M],&x->m_iData[(N-1-k)*M],sizeof(double)*M);
			}
}



void tmcnum2str(long nout,long ninput,tmsMatrix *sbuf, tmsMatrix *x, tmsMatrix *fm)
{// Restriction: len(x) is limited.
/*
    T = NUM2STR(X) converts the matrix X into a string representation T
    with about 4 digits and an exponent if required.  This is useful for
    labeling plots with the TITLE, XLABEL, YLABEL, and TEXT commands.
 
    T = NUM2STR(X,N) converts the matrix X into a string representation
    with a maximum N digits of precision.  The default number of digits is
    based on the magnitude of the elements of X.
 
    T = NUM2STR(X,FORMAT) uses the format string FORMAT (see SPRINTF for
    details).
*/
	char *out;
	char TempBuffer[MAX_PRINTF_LEN];// max len string
	char *sBuf;
	long k,len;
	short nStored;
short maxdigits;

	out=TempBuffer;
	if (ninput>1)
	{
		if (_tmcIsChar(fm))
		{
			sBuf=_tmcMat2String(fm);
		    maxdigits=0;
		}
		else
		{
			maxdigits=(short)fm->value.complx.rData[0];
		}

	}
	else
	{
		maxdigits=4;
	}
	for (k=0;k<tmcNumElem(x);k++)
	{
					if (maxdigits==0)
						nStored=sprintf(out,sBuf,x->m_rData[k]);// hazard "%d"
					else
						if (_mdblIsInteger(x->m_rData[k]))
							nStored=sprintf(out,"%I64d",(__int64)x->m_rData[k]);
						else
							nStored=sprintf(out,"%.15e",x->m_rData[k]);// HAZARD: fixed precision

					out += nStored;
					if (_tmcHasIm(x) && x->m_iData[k])
					{
						nStored=sprintf(out,"+");
						out += nStored;
					if (maxdigits==0)
						nStored=sprintf(out,sBuf,x->m_iData[k]);// hazard "%d"
					else
						if (_mdblIsInteger(x->m_iData[k]))
							nStored=sprintf(out,"%I64d",(__int64)x->m_iData[k]);
						else
							nStored=sprintf(out,"%.15e",x->m_iData[k]);

						out += nStored;
						nStored=sprintf(out,sBuf,"i");
						out += nStored;
					}
		if (k<tmcNumElem(x)-1)
						nStored=sprintf(out," ");
						out += nStored;
	}
if (maxdigits==0)
	MYFREE(sBuf);
	len = (long)strlen(TempBuffer); //x64 without NULL-termination.
	_tmcCreateMatrix(sbuf,1,len,tmcREAL);
	sbuf->m_desc.m_type = TYPE_STRING;
	for(k=0;k<len;k++)
		sbuf->m_rData[k]=TempBuffer[k];

}
void tmcchar(long nout,long ninput,tmsMatrix *matres,tmsMatrix *src)
{// restriction: only char(X) is supported
	long M,N,MN,k;
		if ( _tmcHasIm(src) )
		_tmcRaiseException(err_must_be_real,s_module,"char()","Operand to CHAR may not be complex.",1,src);

			M=_tmcGetM(src);
			N=_tmcGetN(src);
			_tmcCreateMatrix(matres,M,N,tmcREAL);
			MN=tmcNumElem(src);
			for (k=0;k<MN;k++)
			{
				matres->m_rData[k] = (unsigned short)(src->m_rData[k]);
			}
			matres->m_desc.m_type = TYPE_STRING;
}

void tmclower(long nout,long ninput,tmsMatrix *matres,tmsMatrix *src)
{// restriction: must be src matrix, not cells
	long M,N,MN,k;
	unsigned short wc;

	if (src->m_desc.m_type != TYPE_STRING   )
	{
		_tmcRaiseException(err_must_be_matrix,s_module,"lower","Operand to LOWER must  be string.",1,src);
	}
			M=_tmcGetM(src);
			N=_tmcGetN(src);
			_tmcCreateMatrix(matres,M,N,tmcREAL);
			MN=tmcNumElem(src);
			for (k=0;k<MN;k++)
			{
				
				wc= (unsigned short)(src->m_rData[k]);
/*
				if (wc >= 'A' && wc <= 'Z')
					wc = wc - 'A' + 'a';
				matres->m_rData[k] = wc;
*/
				matres->m_rData[k] = tolower(wc);
  }
			matres->m_desc.m_type = TYPE_STRING;
}

void tmcdouble(long nout,long ninput,tmsMatrix *matres,tmsMatrix *src)
{	/*
	DOUBLE(X) returns the double precision value for X.
    If X is already a double precision array, DOUBLE has
    no effect. */

	long M,N,MN,k;
		if (_tmcGetType(src) != TYPE_MATRIX && _tmcGetType(src) != TYPE_STRING )
		_tmcRaiseException(err_must_be_real,s_module,"double()","Operand to double may not be matrix or string.",1,src);

			M=_tmcGetM(src);
			N=_tmcGetN(src);
			_tmcCreateMatrix(matres,M,N,_tmcHasIm(src) );
			MN=tmcNumElem(src);
			for (k=0;k<MN;k++)
			{
				matres->m_rData[k] = (src->m_rData[k]);
			}
		    if ( _tmcHasIm(src) )
			{
				for (k=0;k<MN;k++)
				{
					matres->m_iData[k] = (src->m_iData[k]);
				}
			}
			matres->m_desc.m_type = TYPE_MATRIX;
}



void tmcnargchk(long nout,long ninput, tmsMatrix *message, tmsMatrix *low, tmsMatrix *high,tmsMatrix *n)
{
	if (n->m_rData[0] > high->m_rData[0])
		_tmcSetString(message,"Too many input arguments.");
	else	
		if (n->m_rData[0] < low->m_rData[0])
				_tmcSetString(message,"Not enough input arguments.");
			else
				_tmcSetMatrixEmpty(message);
}
/////// SET UTILS ///////////
__inline short _is_cequal(struct Ccomplex_sort *pC1,struct Ccomplex_sort *pC2)
{
	if (pC1->val_im==pC2->val_im && pC1->val_re==pC2->val_re)
		return 1;
	else
		return 0;
}

void tmcunique(long nout,long ninput, tmsMatrix *y, tmsMatrix *I,tmsMatrix *J,tmsMatrix *mx)
{
	// Restriction: only syntax [Y]=unique(x), [Y,I]=unique(x) is supported
long MN;
short bComplex;
	struct Ccomplex_sort *pC,*pPred;
	long *IND;
	long k,k_in,ind_out,k_out;
	long M,N;
	double Pred;
tmsMatrix *x = NULL;

//FILE *fp;

	if (nout==1)
	{
		x = 	mx;
	}
	else
	{
	_tmcRaiseException(err_unsupported,"sets","tmcunique","FATAL:only syntax [Y]=unique(x), [Y,I]=unique(x) is supported.",0,NULL);
	}

	MN = tmcNumElem(x);
	if (MN==0) // x is []
	{
	_tmcCreateMatrix(y,0,0,tmcREAL);
	if (nout>1)
	_tmcCreateMatrix(I,0,0,tmcREAL);

	return;
	}
	bComplex = _tmcHasIm(x);

			pC = MYMALLOC(sizeof(struct Ccomplex_sort)*MN);
			IND= MYMALLOC(sizeof(long)*MN);
			for (k=0;k<MN;k++)
			{
					pC[k].val_re=x->m_rData[k];
					if (bComplex)
						pC[k].val_im=x->m_iData[k];
					else
						pC[k].val_im=0;
					pC[k].ind = k+1;
			}
			qsort(pC,MN,sizeof(struct Ccomplex_sort),cvalindcompare);
	IND[0]=0;
	pPred=pC;
	ind_out=0;
	Pred=pC->val_re;
	if (bComplex)
	for (k_in=1;k_in<MN;k_in++)
	{
		if ( _is_cequal(pC+k_in,pPred)==0)
		{
			pPred=pC+k_in;
			ind_out++;
			IND[ind_out]=k_in;
		}
	}
	else
	for (k_in=1;k_in<MN;k_in++)
	{
		if ( pC[k_in].val_re!= Pred )
		{
			Pred=pC[k_in].val_re;
			ind_out++;
			IND[ind_out]=k_in;
		}
	}



	if (_tmcGetM(x)==1) // row
	{
		M=1;N=ind_out+1;
	}
	else
	{
		M=ind_out+1;N=1; // column or matrix
	}
	_tmcCreateMatrix(y,M,N,bComplex);
	if (nout>1)
	_tmcCreateMatrix(I,M,N,tmcREAL);

	for (k_out=0;k_out<=ind_out;k_out++)
	{
		k_in=IND[k_out];
		y->m_rData[k_out]=pC[k_in].val_re;
		if (bComplex)
			y->m_iData[k_out]=pC[k_in].val_im;
		if (nout>1)
			I->m_rData[k_out]=pC[k_in].ind;
	}
	MYFREE(pC);
	MYFREE(IND);
//fp=fopen("debugout.mat","wb");
//	tmcStoreMat(fp ,"x" , x);
//	tmcStoreMat(fp ,"y" , y);
//fclose(fp);
}

void tmcsetdiff(long nout,long ninput, tmsMatrix *y, tmsMatrix *I,tmsMatrix *A,tmsMatrix *B,tmsMatrix *rs)
{
// setdiff(A,B)= A-B=the values in A that are not in B.  The result will be sorted.
long *pInd;
long MNa,MNb;
long NumD;
long k,m;
tmsMatrix *y0;

	MNa = tmcNumElem(A);
	MNb = tmcNumElem(B);

	NumD=0;
	pInd = MYMALLOC(sizeof(long)* MNa);
	if (_tmcHasIm(A)==0)
	{
		A->m_iData=MYMALLOC(MNa*sizeof(double));
		memset(A->m_iData,0,sizeof(double)*MNa);
	}
	if (_tmcHasIm(B)==0)
	{
		B->m_iData=MYMALLOC(MNb*sizeof(double));
		memset(B->m_iData,0,sizeof(double)*MNb);
	}

	for (k=0;k<	MNa;k++)
	{
		for (m=0;m<MNb;m++)
		{
			if (A->m_rData[k]==B->m_rData[k] && A->m_iData[k]==B->m_iData[k])
			{
				goto NoAppendSetDiff; // do not append
			}
		}
		pInd[NumD++]=k; // resulted index
NoAppendSetDiff: ;
	}

	// create temporary matrix (not-sorted).
	y0 = tmcNewMatrix();
	_tmcCreateMatrix(y0,1,NumD+1,_tmcHasIm(A));
	for (k=0;k<NumD;k++)
	{
		y0->m_rData[k]= A->m_rData[pInd[k]];
		if (_tmcHasIm(A))
			y0->m_iData[k]= A->m_iData[pInd[k]];
	}
	tmcunique(nout,1,y,I,NULL,y0);
	_tmcClearRegister(y0);
	MYFREE(y0);


	if (_tmcHasIm(A)==0)
	{
		MYFREE(A->m_iData);
	}
	if (_tmcHasIm(B)==0)
	{
		MYFREE(B->m_iData);
	}
	MYFREE(pInd);

}

void tmcintersect(long nout,long ninput, tmsMatrix *y, tmsMatrix *I,tmsMatrix *J,tmsMatrix *A,tmsMatrix *B)
{// HAZARD_TODO:J
// intersect(A,B)= A and B=the values in A that are  in B.  The result will be sorted.
// Restriction: syntax only [AB,IA]=intersect(A,B)
long *pInd;
long MNa,MNb;
long NumD;
long k,m;
tmsMatrix *y0;

	MNa = tmcNumElem(A);
	MNb = tmcNumElem(B);

	NumD=0;
	pInd = MYMALLOC(sizeof(long)* MNa);
	if (_tmcHasIm(A)==0)
	{
		A->m_iData=MYMALLOC(MNa*sizeof(double));
		memset(A->m_iData,0,sizeof(double)*MNa);
	}
	if (_tmcHasIm(B)==0)
	{
		B->m_iData=MYMALLOC(MNb*sizeof(double));
		memset(B->m_iData,0,sizeof(double)*MNb);
	}

	for (k=0;k<	MNa;k++)
	{
		for (m=0;m<MNb;m++)
		{
			if (A->m_rData[k]==B->m_rData[m] && A->m_iData[k]==B->m_iData[m])
			{
				pInd[NumD++]=k; // resulted index
				break;// appended
			}
		}
	}

	// create temporary matrix (not-sorted).
	y0 = tmcNewMatrix();
	_tmcCreateMatrix(y0,1,NumD,_tmcHasIm(A));
	for (k=0;k<NumD;k++)
	{
		y0->m_rData[k]= A->m_rData[pInd[k]];
		if (_tmcHasIm(A))
			y0->m_iData[k]= A->m_iData[pInd[k]];
	}
	tmcunique(nout,1,y,I,NULL,y0);
	_tmcClearRegister(y0);
	MYFREE(y0);


	if (_tmcHasIm(A)==0)
	{
		MYFREE(A->m_iData);
	}
	if (_tmcHasIm(B)==0)
	{
		MYFREE(B->m_iData);
	}
	MYFREE(pInd);

}
void tmcismember(long nout,long ninput, tmsMatrix *y, tmsMatrix *A,tmsMatrix *S)
{
//HAZARD_TODO_QFD
	_tmcRaiseException(err_unsupported,"sets","tmcismember","FATAL: tmcismember is not implemented!!!.",0,NULL);
}
void tmcsqueeze(long nout,long ninput,tmsMatrix *y,tmsMatrix *x)
{
// 2-D arrays are unaffected by squeeze so that row vectors remain rows.
	tmcCopyMat(y,x);
	_tmcRemoveSigleton(y);
}

void tmcFncHandle(tmsMatrix *dest,void (*fnc_ptr)(long,long,...),const char *nm)
{//HAZARD
	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,0,0,tmcREAL);
	dest->m_desc.m_type=TYPE_FNC_HANDLE;
	dest->value.fnc_ptr = fnc_ptr;
}
void tmcfeval(long nout,long ninput,tmsMatrix *y, tmsMatrix *fnc_handle, tmsMatrix *x1,...)
{
	fnc_handle->value.fnc_ptr(ninput-1,nout,y,x1);//HAZARD: only one input parameter is supported!!!
}

__int64 g_MemCnt=0;
__int64 g_MemUsed=0;

__int64 g_MemN=0;
double *g_MemHe[1000];
short  g_MemNbuf=0;

void *my_malloc_dbg( size_t size,const char *filename, int linenumber )
{
	void *ptr;
//	long k = ceil( (double)size  / sizeof(double));
//	if ((g_MemCnt+k)*sizeof(double) < 0x1000000)
//	{
//		ptr=&g_MemHe[g_MemNbuf][g_MemCnt];
//		g_MemCnt+=k;
//	}
//	else
//	{
//			g_MemCnt=0;
//			g_MemNbuf++;
//			ptr=&g_MemHe[g_MemNbuf][g_MemCnt];
//			g_MemCnt+=k;
//	}
//
	g_MemCnt+=size;
	g_MemN+=1;
	g_MemUsed+=size;
#ifdef _DEBUG_MEMORY
	ptr = _malloc_dbg(size,_NORMAL_BLOCK, filename, linenumber );
#else
	ptr = malloc(size);
#endif
	return ptr;
}
void *my_malloc( size_t size)
{
	void *ptr;
	g_MemCnt+=size;
	g_MemN+=1;
	g_MemUsed+=size;
	ptr = malloc(size);
	return ptr;
}

void _mfindstr(tmsMatrix *K,tmsMatrix *Str,tmsMatrix *Templ)
{
	long sl , fl , ind1 , ind , match , arrLen ;
	double *dS,*dT;
	long *findArr=0;
	short breakIfFound=0;

	fl = tmcNumElem( Templ) ;	
	sl = tmcNumElem( Str ) ;

	dS=Str->value.complx.rData;
	dT=Templ->value.complx.rData;
	if (sl > 0)
	findArr=(long*)MYMALLOC(sl*sizeof(long));



	arrLen = 0 ;
	for( ind = 0 ; ind < sl ; ind++ )
	{
		match = 0 ;
		for( ind1 = 0 ; ind1 < fl ; ind1++ )
		{
			if( ind+ind1 < sl )
			{
				if( dS[ind+ind1] == dT[ind1] )									
				{
					match++;
				}
				else
				{
					break ;
				}
			}
			else
			{
				break ;
			}
		}		
		if( match == fl )
		{
			findArr[arrLen++] = ind ;
			if( breakIfFound == 1 )
			{
				break;
			}
		}
	}	
	_tmcCreateMatrix(K,1,arrLen,tmcREAL);
	for (ind=0;ind<arrLen;ind++)
	{
			K->m_rData[ind]=  findArr[ind]+1;// convert from 0-based to 1-based index.
	}
	if (findArr)
		MYFREE(findArr);

}

void tmcfindstr(long nout,long ninput,tmsMatrix *K,tmsMatrix *S1,tmsMatrix *S2)
{ 
//K = FINDSTR(S1,S2) returns the starting indices of any occurrences
//   of the shorter of the two strings in the longer.
	if (tmcNumElem( S1 )>tmcNumElem( S2 ))
	{
		_mfindstr(K,S1,S2);
	}
	else
	{
	    _mfindstr(K,S2,S1);
	}
}
void tmcstrfind(long nout,long ninput,tmsMatrix *K,tmsMatrix *sTEXT,tmsMatrix *sPATTERN)
{ 
//K = STRFIND(TEXT,PATTERN) returns the starting indices of any 
//    occurrences of the string PATTERN in the string TEXT.
//    STRFIND will always return [] if PATTERN is longer than TEXT.

	if (tmcNumElem( sTEXT )>=tmcNumElem( sPATTERN ))
	{
		_mfindstr(K,sTEXT,sPATTERN);
	}
	else
	{
	    _tmcCreateMatrix(K,0,0,tmcREAL);
	}
}

short _mIsEq(tmsMatrix *x1,tmsMatrix *x2)
{
	long m;
	double re1,im1,re2,im2;

	if (_tmcGetType(x1) == TYPE_MATRIX || _tmcGetType(x1) == TYPE_STRING)
	{
		if (_tmcGetM(x1) != _tmcGetM(x2))
			return 0;
		if (_tmcGetN(x1) != _tmcGetN(x2))
			return 0;
		for (m=0;m<tmcNumElem(x1);m++)
		{
			re1=x1->value.complx.rData[m];
			re2=x2->value.complx.rData[m];
			if ( re1 != re2 )
				return 0;

			if (_tmcHasIm(x1))
				im1 = x1->value.complx.iData[m];
			else
				im1=0;

			if (_tmcHasIm(x2))
				im2 = x2->value.complx.iData[m];
			else
				im2=0;
			if ( im1 != im2 )
				return 0;

			if (_isnan(re1) || _isnan(re2) || _isnan(im1) ||  _isnan(im2))
			{
				return 0;
			}
		}
		return 1;
	}
	else
	{
//HAZARD_TODO: only for vectors
		_tmcRaiseException(err_unsupported,"main","tmcisequal","supported only for vectors",0,NULL);
		return 0;
	}
}

void tmcisequal(long nout,long ninput,tmsMatrix *res,tmsMatrix *x1,...)
{
//True if arrays are numerically equal.
//    Numeric data types and structure field order
//    do not have to match.
//    NaNs are not considered equal to each other.
//HAZARD_TODO: only for vectors
tmsMatrix *x;
va_list marker;
short n;
short bOk=0;
	
	n=1;
	va_start( marker, x1 );     // Initialize variable arguments. 
	while (n<ninput)
	{
		x = va_arg( marker,  tmsMatrix * );
		if (_mIsEq(x1,x)==0)
			goto DoneIsEq;
		n++;
	}
	va_end( marker );              // Reset variable arguments.      
	bOk = 1;

DoneIsEq:
	    _tmcCreateMatrix(res,1,1,tmcREAL);
		res->value.complx.rData[0]=bOk;
}

// switch-case support
void tmcCalcSwitchExpVal(tmsMatrix *expr_code,tmsMatrix *x)
{
// create numeric code for string or double expression of SWITCH
	tmcReallocRegister(expr_code);
	if (x->m_desc.m_type == TYPE_STRING)
	{
		expr_code->value.hcode_val=dstring2hcode(x->m_rData,tmcNumElem(x));
	}
	else
	{
		expr_code->value.scalar_val=x->m_rData[0];
	}
}
short tmcIsCaseString(tmsMatrix *expr_code,STRINGCODE n)
{// return: 1: if expr_code<>n else 0
	return expr_code->value.hcode_val==n ? 1:0;
}
short tmcIsCaseDouble(tmsMatrix *expr_code,double x)
{// return: 1: if expr_code<>x else 0
	return expr_code->value.scalar_val==x ? 1:0;
}

void tmcischar(long nout,long ninput,tmsMatrix *y,tmsMatrix *x)
{
			_tmcCreateMatrix(y,1,1,tmcREAL);
			y->m_rData[0]=  ( (x->m_desc.m_type ==TYPE_STRING) ? 1:0);
}

void tmcpause(long nout,long ninput,tmsMatrix *ydummy,tmsMatrix *d)
{// system specific demands <windows.h>
//	extern void Sleep(unsigned long msDelay);
	unsigned long  msTimeout;
// this function is implemented with one output to avoid TMC compilation warnings.
	if (nout>0)
	_tmcCreateMatrix(ydummy,1,1,0);

#ifndef  _TMC_EMBEDDED_ // TMC_HAZARD: no sleep support in embedded system
	msTimeout = (unsigned long)(d->m_rData[0] * 1000.0f);
	Sleep(msTimeout);
#endif
}
#ifndef MATLAB_MEX_FILE
void   mmy_free( void *memblock )
{
#ifndef  _TMC_EMBEDDED_ // TMC_HAZARD: no _msize in embedded system
	g_MemUsed-=_msize(memblock);
#endif

#ifdef _DEBUG
	//_free_dbg(memblock, _NORMAL_BLOCK );
	free(memblock);
#else
	free(memblock);
#endif
}
#endif

////////////// FOR unmodifed-MEX ONLY ///////////////////
tmsMatrix* mxCreateDoubleMatrix(long m, long n , short iscomplex )
{
//long *myEBP;
//
//	__asm
//	{
//		mov myEBP,ebp 
//	}
//	sprintf(dbg_buf2,"tmcScalar: %x,%s",myEBP[1],"...");

	tmsMatrix *dest =tmcNewMatrix();
	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,m,n,iscomplex);
	return dest;
}
//////////////////////////////////////////
#ifndef  _TMC_EMBEDDED_
HANDLE hWndDebug;
HANDLE tmcconnectdebugger(long pass)
{
	if (pass==1)
	{
		hWndDebug = CreateWindow(
		  L"edit",  // pointer to registered class name
		  L"tmcdebug", // pointer to window name
		  WS_DISABLED,        // window style
		  0,                // horizontal position of window
		  0,                // vertical position of window
		  1,           // window width
		  1,          // window height
		  NULL,      // handle to parent or owner window
		  0,          // handle to menu or child-window identifier
		  NULL,     // handle to application instance
		  NULL        // pointer to window-creation data
		);


	}
	else
	{
		printf("\nfail start debugging...\n");
	}
	return hWndDebug;
}
#endif

/// Added for QFD /////////////////
// 2012.11.26
//TODO_CHECK_QFD
void tmcndims(long nout,long ninput, tmsMatrix *y, tmsMatrix *M)
{
	//not needed since ReallocRegister() is called:
	//tmcReallocRegister(y);
	_tmcCreateMatrix(y,1,1,tmcREAL);
	y->m_rData[0]=_tmcGetNdim(M);
}
void tmcnumel(long nout,long ninput, tmsMatrix *y, tmsMatrix *x)
{
//HAZARD_TODO_QFD: to implement for >2 ndims
	_tmcCreateMatrix(y,1,1,tmcREAL);
	y->m_rData[0]=tmcNumElem(x);
}
void tmcdeal(long nout,long ninput,tmsMatrix *y,... )
{ // [x1,..xn]=deal(a) or [x1,..xn]=deal(a1,..an)
	
	va_list marker;
	long ind;
	tmsMatrix *M;
	tmsMatrix **matN;

	if (nout<1 || ninput<1 || (nout!=ninput && ninput>1))
	{
			_tmcRaiseException(err_invalid_number_of_input_pars,s_module,"tmcdeal","The number of outputs should match the number of inputs.",0,NULL);
	}

	matN = (tmsMatrix **)MYMALLOC(sizeof(tmsMatrix *) * nout);
	va_start( marker, y );     // Initialize variable arguments. 

		ind=1;
		matN[0]=y;
		while (ind<nout)
		{
			matN[ind] = va_arg( marker,  tmsMatrix * );
			// Not need, already called:
			//tmcReallocRegister(matN[ind]);
		}
		M = va_arg( marker,  tmsMatrix * );
		for (ind=0;ind<nout;ind++)
		{
			// get next input
			if (ninput>1 && (ind>0))
			{
				M = va_arg( marker,  tmsMatrix * );
			}
			tmcAssign(matN[ind],M);
		}
		va_end( marker );              // Reset variable arguments.
	MYFREE(matN);
}

///////////////////////////////////
//////////////// for ASM format ///////////////////
void tmcCreateStringEmpty(tmsMatrix *matres)
{// as tmcCreateString(matres,"")
	// In MATLAB all implicit strings  have no ESC-seq, thus in TMC they contain
	// additional \.
	// In C exist Escape Sequences
	// only sprintf and fprintf functions convert the formats TMC to C
	// e.g. "\\r" ->> "\r"
	tmcReallocRegister(matres);
	_tmcSetString(matres,"");
}


void tmcj(long nout,long ninput,tmsMatrix *dest)
{
	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,1,1,tmcCOMPLEX);
	dest->m_rData[0]=0;
	dest->m_iData[0]=1;
}
void tmci(long nout,long ninput,tmsMatrix *dest)
{
	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,1,1,tmcCOMPLEX);
	dest->m_rData[0]=0;
	dest->m_iData[0]=1;
}


////////////////////// MULTI-DIM /////////////
long _tmcCountM(short ndim,long* arrdims)
{
	short cnt;
	long N=1;
	for (cnt=1;cnt<ndim;cnt++)
	{
		N *=  	arrdims[cnt];
	}
	return N;
}
void _tmcCreateMatrixMD(tmsMatrix *res,short ndim,long* arrdims,short bHasImagine)
{
long M,N;
short cnt;

	if (ndim<3)
	{
		_tmcCreateMatrix(res,arrdims[0],arrdims[1],bHasImagine);
		return;
	}

	res->m_desc.m_nRows=M=arrdims[0];
	res->m_desc.m_nCols=N=_tmcCountM(ndim,arrdims);
	res->m_desc.m_type= TYPE_MATRIX;

	memset(&res->value,0,sizeof(res->value));
	if (M*N)
	{
	res->m_rData = (double*)MYMALLOC(M*N*sizeof(double));
	memset(res->m_rData,0,M*N*sizeof(double));
	if (bHasImagine)
		{
			res->m_iData = (double*)MYMALLOC(M*N*sizeof(double));
			memset(res->m_iData,0,M*N*sizeof(double));
			res->m_desc.m_modifier |=MODIFIER_MASK_HAS_IM;
		}
		else
		{
			res->m_desc.m_modifier &=~MODIFIER_MASK_HAS_IM;
		}
	}
	_tmcClearExtraDims(res);
	_tmcCreateDims(res,ndim);
	_tmcSetExtraDim(res,ndim-2);
	for (cnt=0;cnt<ndim;cnt++)
	{
		_tmcSetDim(res,cnt,arrdims[cnt]);
	}
}
void _tmcResizeMatrixMD(tmsMatrix *matres,short ndim,long* arrdims,short bHasIm)
{
	// HAZARD_TODO_QFD

	
}
void  _tmcSetByIndexMD(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix **refs)
{
	// restriction: in A(I,J,K,..) I,J,K.. may be only columns or rows, not matrix
long MNa;
short aScalar;
short IsMagicColonIndex[MAX_MATRIX_DIM];
long  d[MAX_MATRIX_DIM];
long  SrcDim[MAX_MATRIX_DIM];
long  DstDim[MAX_MATRIX_DIM-1];
long  inx[MAX_MATRIX_DIM];
long  arrdims[MAX_MATRIX_DIM];
long newdim;
short k;
short SrcHasMagicCol=0;
short bMustResize=0;
long ind_at_max; // dummy
short ind_src_inc;
short bHasIm,bLhsHadIm;
long ind_dst,ind_src;
long IndexVolume=1;

	MNa=tmcNumElem(src); // size(a,1)*size(a,2)
		if (MNa==1)
		{
			aScalar=1;// a is scalar
			ind_src_inc=0;// increment in src 
		}
		else
		{
			aScalar=0;// a is not scalar
			ind_src_inc=1;
		}

		DstDim[0] = _tmcGetDim(matres,1);// M
		for (k=1;k<numdims-1;k++)
		{
			DstDim[k] = _tmcGetDim(matres,1+k) * DstDim[k-1];// M*N,M*N*K etc.
		}
		for (k=0;k<numdims;k++)
		{
			//IsMagicColonIndex[k] = (refs[k]->m_desc.m_type == TYPE_MAGIC_COLON) ? 1:0;
			//SrcHasMagicCol +=  IsMagicColonIndex[k];
			if ((refs[k]->m_desc.m_type == TYPE_MAGIC_COLON))
			{
					IsMagicColonIndex[k] =1;
					SrcHasMagicCol +=1;
					SrcDim[k] =_tmcGetDim(matres,1+k);
			}
			else
			{
					IsMagicColonIndex[k]=0;
					SrcDim[k] = tmcNumElem( refs[k] ) ;// index dimenion
			}
			IndexVolume *= SrcDim[k];
		}

		bHasIm=_tmcHasIm(src);
		bLhsHadIm=_tmcHasIm(matres);
		// check dimentions

		if (_tmcIsEmptyMatrix(src))
		{
			if (SrcHasMagicCol==0)
			{
				_tmcRaiseException(err_bad_index,s_module,"_tmcSetByIndex","x(I,J,...)=[],must be with an (:) indexing",0,NULL);
			}

			// x(I,:)=[] or x(:,J)  x(:,:)=[]
			if (SrcHasMagicCol==numdims)
			{
				// x(:,:)=[]
				_tmcClearMatrix(matres);
			}
			else
			{
				//RESTRICTION.
				_tmcRaiseException(err_bad_index,s_module,"_tmcSetByIndex","A null assignment can have only one non-colon index.",0,NULL);
				//if (IsMagicColonIndex[0])
				//{ // x(:,J)
				//	_tmcClearColumns(matres,J);
				//}
				//else
				//{ // x(I,:)
				//	_tmcClearRows(matres,I);
				//}
			}
			return;
		}

		if (aScalar==0)
		{
			// simplified
			if (IndexVolume != tmcNumElem(src))
			//for (k=0;k<numdims;k++)
			//{
			//	if ((SrcDim[k] !=  tmcNumElem( refs[k] ) ))
				{
					_tmcRaiseException(err_bad_index,s_module,"_tmcSetByIndex","like: numelem(I)<>size(a,1) in x(I,J,..)=a",1,src);
				}
			//}
		}


		// reshape the result matrix
		// default is not needed reshape
		for (k=0;k<numdims;k++)
		{
			arrdims[k] = _tmcGetDim(matres,1+k) ;
			if (	IsMagicColonIndex[k]==0)
			{
				_tmcLongGetMaxVal(&newdim,&ind_at_max,refs[k]); // find maximal index I
				if (newdim > arrdims[k])
				{
					bMustResize=	1;
					arrdims[k] = newdim;
				}
			}
		}
		if (bMustResize)
		{
				_tmcResizeMatrixMD(matres,(short)numdims,arrdims,bHasIm);
		}
		if(bHasIm)
		{
				_tmcForceComplexMatrix(matres);// add zero imagine part if needed
		}
		// Actual assignment
		ind_src=0;

		if (numdims==3)
		{
			for (d[2]=0;d[2]<SrcDim[2];d[2]++)
			{
				inx[2]= (IsMagicColonIndex[2] ? d[2] : (long)(refs[2]->m_rData[d[2]]-1)) * DstDim[1];// M*N*k
				for(d[1]=0;d[1]<SrcDim[1];d[1]++)
				{
					inx[1]= ((IsMagicColonIndex[1] ? d[1] : (long)(refs[1]->m_rData[d[1]]-1)) * DstDim[0])+ inx[2];// M*n+M*N*k
					for (d[0]=0;d[0]<SrcDim[0];d[0]++)
					{

					inx[0]= (IsMagicColonIndex[0] ? d[0] : (long)(refs[0]->m_rData[d[0]]-1))+inx[1];// m+M*n+M*N*k
					ind_dst= inx[0];

					matres->m_rData[ind_dst]=src->m_rData[ind_src];
					if (bHasIm)
						matres->m_iData[ind_dst]=src->m_iData[ind_src];
					else if (bLhsHadIm)
					{
							matres->m_iData[ind_dst]=0;
					}
					ind_src += ind_src_inc;
					}
				}
			}
		}
		else if (numdims==4)
		{
		for (d[3]=0;d[3]<SrcDim[3];d[3]++)
			{
				inx[3]= (IsMagicColonIndex[3] ? d[3] : (long)(refs[3]->m_rData[d[3]]-1)) * DstDim[2];// M*N*K*l
				for (d[2]=0;d[2]<SrcDim[2];d[2]++)
				{
					inx[2]= ((IsMagicColonIndex[2] ? d[2] : (long)(refs[2]->m_rData[d[2]]-1)) * DstDim[1])+inx[3];// M*N*k+M*N*K*l
					for(d[1]=0;d[1]<SrcDim[1];d[1]++)
					{
						inx[1]= ((IsMagicColonIndex[1] ? d[1] : (long)(refs[1]->m_rData[d[1]]-1)) * DstDim[0])+ inx[2];// M*n+M*N*k+.
						for (d[0]=0;d[0]<SrcDim[0];d[0]++)
						{

						inx[0]= (IsMagicColonIndex[0] ? d[0] : (long)(refs[0]->m_rData[d[0]]-1))+inx[1];// m+M*n+M*N*k+.
						ind_dst=  inx[0];

						matres->m_rData[ind_dst]=src->m_rData[ind_src];
						if (bHasIm)
							matres->m_iData[ind_dst]=src->m_iData[ind_src];
						else if (bLhsHadIm)
						{
							matres->m_iData[ind_dst]=0;
						}
						ind_src += ind_src_inc;
						}
					}
				}
			}
		}
		else
		{
				_tmcRaiseException(err_unsupported,s_module,"_tmcSetByIndex","x(I,J,...)=A supported for ndim<5",0,NULL);
		}


    if(src->m_desc.m_type==TYPE_STRING)
	matres->m_desc.m_type=src->m_desc.m_type;

}
void _tmcGetByIndexMD(tmsMatrix *matres,const tmsMatrix *src,short numdims,tmsMatrix **refs)
{// matres is cleared.
short bHasIm;
short k;
short IsMagicColonIndex[MAX_MATRIX_DIM];
long  d[MAX_MATRIX_DIM];
long  SrcDim[MAX_MATRIX_DIM];
long  DstDim[MAX_MATRIX_DIM-1];
long  inx[MAX_MATRIX_DIM];
long ind_dst,ind_src;

	bHasIm=_tmcHasIm(src);


		// Ipcha mistabra: DstDim is src dimensions,
		DstDim[0] = _tmcGetDim(src,1);// M
		for (k=1;k<numdims-1;k++)
		{
			DstDim[k] = _tmcGetDim(src,1+k) * DstDim[k-1];// M*N,M*N*K etc.
		}
		for (k=0;k<numdims;k++)
		{
			//IsMagicColonIndex[k] = (refs[k]->m_desc.m_type == TYPE_MAGIC_COLON) ? 1:0;
			//SrcHasMagicCol +=  IsMagicColonIndex[k];
			if ((refs[k]->m_desc.m_type == TYPE_MAGIC_COLON))
			{
					IsMagicColonIndex[k] =1;
					//SrcHasMagicCol +=1;
					SrcDim[k] =_tmcGetDim(src,1+k);
			}
			else
			{
					IsMagicColonIndex[k]=0;
					SrcDim[k] = tmcNumElem( refs[k] ) ;// index dimenion
			}
			//IndexVolume *= SrcDim[k];
		}
		_tmcCreateMatrixMD(matres,numdims,SrcDim,bHasIm);



		// Ipcha mistabra: DstDim is src dimensions,
		ind_dst=0;
		if (numdims==3)
		{
			for (d[2]=0;d[2]<SrcDim[2];d[2]++)
			{
				inx[2]= (IsMagicColonIndex[2] ? d[2] : (long)(refs[2]->m_rData[d[2]]-1)) * DstDim[1];// M*N*k
				for(d[1]=0;d[1]<SrcDim[1];d[1]++)
				{
					inx[1]=( (IsMagicColonIndex[1] ? d[1] : (long)(refs[1]->m_rData[d[1]]-1)) * DstDim[0])+ inx[2];// M*n+M*N*k
					for (d[0]=0;d[0]<SrcDim[0];d[0]++)
					{

					inx[0]= (IsMagicColonIndex[0] ? d[0] : (long)(refs[0]->m_rData[d[0]]-1))+inx[1];// m+M*n+M*N*k
					ind_src= inx[0];

					matres->m_rData[ind_dst]=src->m_rData[ind_src];
					if (bHasIm)
						matres->m_iData[ind_dst]=src->m_iData[ind_src];
					ind_dst += 1;
					}
				}
			}
		}
		else if (numdims==4)
		{
		for (d[3]=0;d[3]<SrcDim[3];d[3]++)
			{
				inx[3]= (IsMagicColonIndex[3] ? d[3] : (long)(refs[3]->m_rData[d[3]]-1)) * DstDim[2];// M*N*K*l
				for (d[2]=0;d[2]<SrcDim[2];d[2]++)
				{
					inx[2]= ((IsMagicColonIndex[2] ? d[2] : (long)(refs[2]->m_rData[d[2]]-1)) * DstDim[1])+inx[3];// M*N*k+M*N*K*l
					for(d[1]=0;d[1]<SrcDim[1];d[1]++)
					{
						inx[1]= ((IsMagicColonIndex[1] ? d[1] : (long)(refs[1]->m_rData[d[1]]-1)) * DstDim[0])+ inx[2];// M*n+M*N*k+.
						for (d[0]=0;d[0]<SrcDim[0];d[0]++)
						{

						inx[0]=( IsMagicColonIndex[0] ? d[0] : (long)(refs[0]->m_rData[d[0]]-1))+inx[1];// m+M*n+M*N*k+.
						ind_src=  inx[0];

						matres->m_rData[ind_dst]=src->m_rData[ind_src];
						if (bHasIm)
							matres->m_iData[ind_dst]=src->m_iData[ind_src];
						ind_dst += 1;
						}
					}
				}
			}
		}
		else
		{
				_tmcRaiseException(err_unsupported,s_module,"_tmcGetByIndex","A=x(I,J,...) supported for ndim<5",0,NULL);
		}

	_tmcRemoveSigleton(matres);//squeeze the result
    if(src->m_desc.m_type==TYPE_STRING)
	matres->m_desc.m_type=src->m_desc.m_type;

}

short _tmcGetReducedDim(short numdim,long* arrdims)
{

	// remove external dimensions if they are of length 1
	if (numdim>2)
	{
		if (numdim==3) // D3
		{
			if (arrdims[2]<2)
			{
				//arrdims[2]=0;
				numdim=2;
			}

		} 
		else if (numdim==4) // D4
		{
			if (arrdims[2]<2 && arrdims[3]<2)
			{
				//arrdims[2]=0;
				numdim=2;
			}
			else if( arrdims[3]<2)
			{
				//arrdims[3]=0;
				numdim=3;
			}
		}
	}
	return numdim;
}
void _tmcRemoveSigleton(tmsMatrix *x)
{
	// remove external dimensions if they are of length 1
	short ndims= _tmcGetExtraDim(x);
	if (ndims>0)
	{
		if (ndims==1) // D3
		{
			if (_tmcGetDim(x,3)<2)
			{
				_tmcClearExtraDims(x);
			}

		} 
		else if (ndims==2) // D4
		{
			if (_tmcGetDim(x,3)<2 && _tmcGetDim(x,4)<2)
			{
				_tmcClearExtraDims(x);
			}
			else if( _tmcGetDim(x,4)<2)
			{
				_tmcSetExtraDim(x,1);
			}
		}
	}

}
void  _tmcRedimArrayMD(tmsMatrix *matres,short numdims,long *arrdims)
{ 
short k;

  // correct number of directions
  if (_tmcGetNdim(matres)!=numdims )
  {
		if (numdims==2)
		{
			// clear MD
			_tmcKillDims(matres);
			matres->m_desc.m_dims=NULL;
			_tmcSetExtraDim(matres,0);
		}
		else if (_tmcHasExtraDim(matres))
		{
			_tmcKillDims(matres);
			_tmcCreateDims(matres,numdims);
			_tmcSetExtraDim(matres,numdims-2);
		}
  }
  			_tmcSetM(matres,arrdims[0]);
			_tmcSetN(matres,_tmcCountM(numdims,arrdims));
			if (_tmcHasExtraDim(matres))
			{
				for (k=0;k<numdims;k++)
				{
					_tmcSetDim(matres,k,arrdims[k]);
				}
			}
}
