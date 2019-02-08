// File: tmcmstruct.c
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license. 
  *****************************************************************************/

#include "tmc.h"
#include "clapack_types.h"

#include  <math.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h> // ANSI compatibility

#include <stdio.h>



static char *s_module="tmcmstruct.c";

void _tmcGetByIndexStruct(tmsMatrix *matres,tmsMatrix *src,tmsMatrix **Iarr,short numdims)
{ // indexing of struct arrays
// HAZARD - only single index=1 is supported.
long k;

	if ((src->m_desc.m_type==TYPE_STRUCT) )
	{
		for (k=0;k<numdims;k++)
		{
			if (tmcNumElem(Iarr[k])>1 || Iarr[k]->m_rData[0]>1)
			{
			_tmcRaiseException(err_unsupported,"main","()","HAZARD: () is not yet fully supported for struct !!!.",1,src);
			}
			if (tmcNumElem(Iarr[k])>0 && Iarr[k]->m_rData[0]>1)
			{
			_tmcRaiseException(err_unsupported,"main","()","HAZARD: () is not yet fully supported for struct !!!.",1,src);
			}
		}
		tmcCopyMat(matres,src); // x  = x(1) for struct x.
	}
	else
	{
	_tmcRaiseException(err_unsupported,"main","()","FATAL: () is unsupported for cells !!!.",1,src);
	}
}


/*void tmcGetRefByField(tmsMatrix *matres,tmsMatrix *src,const char *fn)
{// analog tmcGetRefByIndex

	if (src->m_desc.m_type != TYPE_REF)
	{
		RefHelper.ndims=0;RefHelper.nrefs=0;RefHelper.src=src;
	}

	RefHelper.dims[RefHelper.ndims]=1;
	RefHelper.type[RefHelper.ndims]='.';
	RefHelper.ndims++;

	RefHelper.refFn[RefHelper.nrefs]=fn;
	RefHelper.nrefs++;

	matres->m_desc.m_type = TYPE_REF;
}*/


void _tmcSetByField(tmsMatrix *matres,long ind,tmsMatrix *src,STRINGCODE hcode)
{// assign to given field.
 // performs matres(ind)  = setfield(matres(ind),fn,src)
 // HAZARD - must support resize
tmsMatrix  *x_field;
tmsMatrix  **new_fields;
STRINGCODE *new_hcodes;
short k;
long MNk,n;

	if (_tmcFindField(&x_field,matres,ind,hcode)<0)
	{
		// field not found - create a new field in matres
		// copy fields, resize struct and put fields back
		// if matrix is empty (or not struct) - resize.
		if (matres->m_desc.m_type != TYPE_STRUCT || tmcNumElem(matres)==0)
		{
			_tmcClearRegister(matres);
			_tmcCreateStruct(matres,ind+1,1,1,NULL);
			matres->value.StructDef.hcFields[0]=hcode;
			x_field=matres->value.StructDef.m_fields[ind];
		}
		else
		{// resize
			new_hcodes = (STRINGCODE *)MYMALLOC(sizeof(STRINGCODE)*(1+_tmcGetNf(matres)));
			new_fields = (tmsMatrix**)MYMALLOC(sizeof(tmsMatrix *)*(tmcNumElem(matres)*(1+_tmcGetNf(matres))));
			MNk = tmcNumElem(matres)*_tmcGetNf(matres);
			for (k=0;k<_tmcGetNf(matres);k++)
			{
				new_hcodes[k]=matres->value.StructDef.hcFields[k];
			}
			new_hcodes[k]=hcode;
			if (_tmcGetNf(matres)>0)
				MYFREE(matres->value.StructDef.hcFields);
			matres->value.StructDef.hcFields=new_hcodes;
				for (n=0;n<MNk;n++)
				{
					new_fields[n]=matres->value.StructDef.m_fields[n];
				}
				while (n<MNk+tmcNumElem(matres))
				{
					new_fields[n]=tmcNewMatrix(); // actually create the field
						n++;
				}
				if (MNk)
					MYFREE(matres->value.StructDef.m_fields);
				matres->value.StructDef.m_fields=new_fields;
				matres->value.StructDef.m_nFields++;
				n = tmcNumElem(matres)*(_tmcGetNf(matres)-1)+ind;
				x_field=matres->value.StructDef.m_fields[n];
		}

	}
	else
	{
		_tmcClearRegister(x_field);
	}
	tmcAssign(x_field,src);
	//matres->m_desc.m_type = TYPE_STRUCT;// HAZARD:must clear the vector if exists
}

short _tmcFindField(tmsMatrix **x_field,tmsMatrix *src,long ind,STRINGCODE hcode)
{ // finds field fn in matrix src.
	short k;
	long n;

	k=0;
	while (k<_tmcGetNf(src))
	{
		if (hcode == src->value.StructDef.hcFields[k])
		{
			// field name is found
			n = tmcNumElem(src)*k+ind;
			*x_field = src->value.StructDef.m_fields[n];
			return (short)n;
		}
		k++;
	}
	return -1;
}
short _tmcGetFieldNumber(tmsMatrix *src,const char *fn)
{
tmsMatrix *fd;
	return _tmcFindField(&fd,src,0,string2hcode(fn));
}
short _tmcRemoveField(tmsMatrix *src,STRINGCODE hcode)
{ // finds field fn in matrix src and remove it.
	tmsMatrix  **new_fields;
	STRINGCODE *new_hcodes;
	long MN;
	
	long k,n;
	short stat=-1;
//////
	for (n=0;n<_tmcGetNf(src);n++)
	{
		if (src->value.StructDef.hcFields[n]==hcode)
		{
			stat=0;
			break;
		}
	}
	if (stat)
		return -1;// not found

		// copy fields, resize struct and pack fields back
		new_hcodes = (STRINGCODE *)MYMALLOC(sizeof(STRINGCODE)*(_tmcGetNf(src)-1));
		new_fields = (tmsMatrix**)MYMALLOC(sizeof(tmsMatrix *)*(tmcNumElem(src)*(_tmcGetNf(src)-1)));
		MN = tmcNumElem(src);
		for (k=0;k<n;k++)
		{
			new_hcodes[k]=src->value.StructDef.hcFields[k];
		}
		for (k=n+1;k<_tmcGetNf(src);k++)
		{
			new_hcodes[k-1]=src->value.StructDef.hcFields[k];
		}
		if (_tmcGetNf(src))
			MYFREE(src->value.StructDef.hcFields);
		src->value.StructDef.hcFields=new_hcodes;
			
		for (k=0;k<MN*n;k++)
		{
				new_fields[k]=src->value.StructDef.m_fields[k];
		}
		for (k=MN*n;k<MN*(n+1);k++)
		{
				_tmcClearRegister(src->value.StructDef.m_fields[k]);
				MYFREE(src->value.StructDef.m_fields[k]);
		}
		for (k=MN*(n+1);k<MN*_tmcGetNf(src);k++)
		{
				new_fields[k-MN]=src->value.StructDef.m_fields[k];
		}
			if (MN>0)
				MYFREE(src->value.StructDef.m_fields);
			src->value.StructDef.m_fields=new_fields;
			src->value.StructDef.m_nFields--;
		return 0;
}

short _tmcFindFieldMat(tmsMatrix **x_field,tmsMatrix *src,long ind,tmsMatrix *m_fn)
{ // finds field fn in matrix src.
	long k;
	long n;
	short stat=-1;
	STRINGCODE hcode=dstring2hcode(m_fn->m_rData,tmcNumElem(m_fn));

	for (k=0;k<_tmcGetNf(src);k++)
	{
		if (src->value.StructDef.hcFields[k]==hcode)
		{
			n = ind+k*tmcNumElem(src);
			*x_field = src->value.StructDef.m_fields[n];
			return (short)n;//found
		}
	}
	return -1;
}
tmsMatrix * _tmcGetByFieldForce(tmsMatrix *src,long ind,STRINGCODE hcode)
{// analog tmcGetByIndex
 // performs matres:= getfield(src(ind),fn)
 // if field not exists - create new filed with empty content
 // src matrix must be of valid dimensions.
tmsMatrix  *x_field;
tmsMatrix  **new_fields;
STRINGCODE *new_hcodes;
short k;
long MNk,n;

	if (_tmcFindField(&x_field,src,ind,hcode)<0)
	{
		// the field is absent - append new field
		// field not found - create a new field in src
		// copy fields, resize struct and put fields back
		if (src->m_desc.m_type != TYPE_STRUCT || tmcNumElem(src)==0)
		{
			_tmcClearRegister(src);
			_tmcCreateStruct(src,ind+1,1,1,NULL);
			src->value.StructDef.hcFields[0]=hcode;
			x_field=src->value.StructDef.m_fields[ind];
		}
		else
		{// resize
			new_hcodes = (STRINGCODE *)MYMALLOC(sizeof(STRINGCODE)*(1+_tmcGetNf(src)));
			new_fields = (tmsMatrix**)MYMALLOC(sizeof(tmsMatrix *)*(tmcNumElem(src)*(1+_tmcGetNf(src))));
			MNk = tmcNumElem(src)*_tmcGetNf(src);
			for (k=0;k<_tmcGetNf(src);k++)
			{
				new_hcodes[k]=src->value.StructDef.hcFields[k];
			}
			new_hcodes[k]=hcode;
			if (_tmcGetNf(src)>0)
				MYFREE(src->value.StructDef.hcFields);
			src->value.StructDef.hcFields=new_hcodes;
				for (n=0;n<MNk;n++)
				{
					new_fields[n]=src->value.StructDef.m_fields[n];
				}
				while (n<MNk+tmcNumElem(src))
				{
					new_fields[n]=tmcNewMatrix(); // actually create the field
						n++;
				}
				if (MNk>0)
					MYFREE(src->value.StructDef.m_fields);
				src->value.StructDef.m_fields=new_fields;
				src->value.StructDef.m_nFields++;
				n = tmcNumElem(src)*(_tmcGetNf(src)-1)+ind;
				x_field=src->value.StructDef.m_fields[n];
		}
	}
	//src->m_desc.m_type = TYPE_STRUCT;
	return x_field;
}


void _tmcCreateStruct(tmsMatrix *matres,long M,long N,short nfields,STRINGCODE *hcFields)
{// assumed  matres is cleared
long ind,MNk;

	matres->m_desc.m_type = TYPE_STRUCT;
	matres->m_desc.m_nCols = N;
	matres->m_desc.m_nRows = M;

	matres->value.StructDef.m_nFields = nfields;
	MNk=M* N * nfields;
	if (MNk>0)
	matres->value.StructDef.m_fields = (tmsMatrix **)MYMALLOC(MNk * sizeof(tmsMatrix *));
	if (nfields>0)
	matres->value.StructDef.hcFields = (STRINGCODE *)MYMALLOC(nfields * sizeof(STRINGCODE));
	if (hcFields != NULL)
		memcpy(matres->value.StructDef.hcFields,hcFields,nfields * sizeof(STRINGCODE));
	for (ind=0;ind<MNk;ind++)
		matres->value.StructDef.m_fields[ind]=tmcNewMatrix();
}
void _tmcClearStruct(tmsMatrix *matres)
{
long ind,MNk;
    MNk=tmcNumElem(matres)*_tmcGetNf(matres);
	for (ind=0;ind<MNk;ind++)
	{
		_tmcClearRegister(matres->value.StructDef.m_fields[ind]);
		MYFREE(matres->value.StructDef.m_fields[ind]);
	}
	if (MNk>0)
		MYFREE(matres->value.StructDef.m_fields);
	if (_tmcGetNf(matres)>0)
		MYFREE(matres->value.StructDef.hcFields);
	matres->m_desc.m_type = TYPE_NOTHING;// do it at the end since m_type was used.
}

void tmcstruct(long nout,long ninput,tmsMatrix *matres,...)
{// matres = struct('fname',fvalue,...).
 // differ from matlab: no array of structure created even if fval is not scalar (i.e. always 1x1)
va_list marker;
long nfields;
tmsMatrix *field_value;
tmsMatrix *field_name;

short ind;

	_tmcClearRegister(matres);
	_tmcCreateStruct(matres,1,1,(short)(ninput/2),NULL);
	if (ninput>0)
	{
		nfields  = ninput/2;
		if (ninput & 1)
		{
			_tmcRaiseException(err_invalid_number_of_input_pars,s_module,"tmcstruct","Field and value input arguments must come in pairs",0,NULL);
		}
		va_start( marker, matres);     // Initialize variable arguments. 
		field_name = (va_arg( marker,  tmsMatrix * ));
		field_value= (va_arg( marker,  tmsMatrix * ));

		if (!(field_name->m_desc.m_type == TYPE_STRING))
		{
			_tmcRaiseException(err_invalid_number_of_input_pars,s_module,"tmcstruct","Field must be string",1,field_name);
		}
		tmcAssign(matres->value.StructDef.m_fields[0],field_value);
		matres->value.StructDef.hcFields[0]=dstring2hcode(field_name->m_rData,tmcNumElem(field_name));

		ind=1;
		while (ind<nfields)
		{
			field_name = (va_arg( marker,  tmsMatrix * ));
			if (!(field_name->m_desc.m_type == TYPE_STRING))
			{
				_tmcRaiseException(err_invalid_number_of_input_pars,s_module,"tmcstruct","Field must be string",1,field_name);
			}
			field_value= (va_arg( marker,  tmsMatrix * ));
			tmcAssign(matres->value.StructDef.m_fields[ind],field_value);
			matres->value.StructDef.hcFields[ind]=dstring2hcode(field_name->m_rData,tmcNumElem(field_name));
			ind++;
		}
		va_end( marker );              // Reset variable arguments.      
	}
}
tmsMatrix *_tmcGetField(tmsMatrix *S,long ind,const char *fname)
{ // analog mxGetField, can use in mex files.
tmsMatrix *x_field;

	if (_tmcFindField(&x_field,S,ind,string2hcode(fname))<0)
	{
		_tmcRaiseException(err_field_absent,s_module,"tmcGetField","Attempt to reference absend field",1,S);
		return NULL;
	}
	else
	{
		return x_field;
	}

}

void tmcgetfield(long nout,long ninput, tmsMatrix *y, tmsMatrix *S, tmsMatrix *m_fn)
{

tmsMatrix *x_field;
STRINGCODE hcode;

	hcode=dstring2hcode(m_fn->m_rData,tmcNumElem(m_fn));


	if (tmcNumElem(S)>1)
	{
		_tmcRaiseException(err_invalid_dimentions,s_module,"getfield","Illegal right hand side in assignment. Too many elements.",1,S);
	}
	if (_tmcFindField(&x_field,S,0,hcode)<0)
	{
		_tmcRaiseException(err_field_absent,s_module,"getfield","Attempt to reference absend field",1,S);
	}
	else
	{
		tmcCopyMat(y,x_field);
	}
}

void tmcrmfield(long nout,long ninput, tmsMatrix *y, tmsMatrix *S, tmsMatrix *m_fn)
{
STRINGCODE hcode;
	hcode=dstring2hcode(m_fn->m_rData,tmcNumElem(m_fn));
	tmcCopyMat(y,S);
	if (_tmcRemoveField(y,hcode))
	{
		_tmcRaiseException(err_field_absent,s_module,"rmfield","A field doesn't exist.",2,S,m_fn);
	}
}
void tmcfields(long nout,long ninput,tmsMatrix *flist,tmsMatrix *S)
{// obscured/obsolete, should not be used.
	tmcfieldnames(nout,ninput,flist,S);
}
void tmcfieldnames(long nout,long ninput,tmsMatrix *flist,tmsMatrix *S)
{ // create cell array with field names
	long numfields=0;
	long m;

	if (S->m_desc.m_type != TYPE_STRUCT)
			_tmcRaiseException(-1000,s_module,"fieldnames","fieldnames(S): S must be struct",1,S);

	numfields=_tmcGetNf(S);
	_tmcCreateCellArray(flist,numfields,1);
	for (m=0;m<numfields;m++)
	{
		flist->value.m_cells[m]= tmcNewMatrix();
		tmcCreateString(flist->value.m_cells[m],hcode2string(S->value.StructDef.hcFields[m]));
	}
}
void tmcisfield(long nout,long ninput,tmsMatrix *y, tmsMatrix *S, tmsMatrix *m_fn)
{
tmsMatrix *fd;
			_tmcCreateMatrix(y,1,1,tmcREAL);
			y->m_rData[0]= ((_tmcFindFieldMat(&fd,S,0,m_fn)>=0) ? 1:0);
}
void tmcIsFieldHcode(tmsMatrix *matres,tmsMatrix *src,STRINGCODE hcode)
{
// matres=isfield(src,string(hcode))
tmsMatrix *fd;
			_tmcClearRegister(matres);//hskost15.07.2012 tmcIsFieldHcode may be  called without _tmcClearRegister
			_tmcCreateMatrix(matres,1,1,tmcREAL);
			matres->m_rData[0]= ((_tmcFindField(&fd,src,0,hcode)>=0) ? 1:0);
}
//////// HASH ////////////
void tmcGetRefByFieldHcode(tmsMatrix *matres,tmsMatrix *src,STRINGCODE hcode)
{
	if (src->m_desc.m_type != TYPE_REF)
	{
		RefHelper.ndims=0;RefHelper.nrefs=0;RefHelper.src=src;
	}

	RefHelper.dims[RefHelper.ndims]=1;
	RefHelper.type[RefHelper.ndims]='.';
	RefHelper.ndims++;

	RefHelper.refhcFn[RefHelper.nrefs]=hcode;
	RefHelper.nrefs++;

	matres->m_desc.m_type = TYPE_REF;

	//	tmcGetRefByField(matres,src,hcode2string(hcode));
}
void tmcGetByFieldHcode(tmsMatrix *matres,tmsMatrix *src,STRINGCODE hcode)
{// analog tmcGetByIndex
 // performs matres:= getfield(src,fn)
tmsMatrix *x_field;

	if (_tmcFindField(&x_field,src,0,hcode)<0)
	{
		_tmcRaiseException(err_field_absent,s_module,"tmcGetByFieldHcode","Attempt to reference absend field",1,src);
	}
	else
	{
		_tmcClearRegister(matres);
		tmcAssign(matres,x_field);
	}
}

void tmcsetfield(long nout,long ninput, tmsMatrix *y, tmsMatrix *S, tmsMatrix *m_fn,tmsMatrix *v)
{// Restriction: only 1x1 struct is supported
	STRINGCODE hcode;
	hcode=dstring2hcode(m_fn->m_rData,tmcNumElem(m_fn));
//	tmcAssign(y,S);
	tmcCopyMat(y,S);
	_tmcSetByField(y,0,v,hcode);
}
////////// 
void tmcorderfields(long nout,long ninput, tmsMatrix *ne, tmsMatrix *pe, tmsMatrix *S1,tmsMatrix *S2)
{//HAZARD_TODO_QFD
// The only syntax: S=orderfields(S)
	fprintf(stdout,"WARN: orderfields() yet not implemented - not sorted\n");
		tmcAssign(ne,S1);
}
