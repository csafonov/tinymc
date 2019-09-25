/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license.
 * 
  *****************************************************************************/
// File: tmccell.c
#include "tmc.h"
#include "clapack_types.h"

#include  <math.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h> // ANSI compatibility

#include <stdio.h>



static char *s_module="tmccell.c";

void _tmcCreateCellArray(tmsMatrix *res,long M,long N)
{// memory must be allocated already 
	res->m_desc.m_nRows=M;
	res->m_desc.m_nCols=N;
	memset(&res->value,0,sizeof(res->value));
	if (M*N)
	{
	res->value.m_cells = MYMALLOC(M*N*sizeof(tmsMatrix *));
	memset(res->value.m_cells,0,M*N*sizeof(tmsMatrix *));
	}
	res->m_desc.m_type = TYPE_CELL_ARRAY;
	_tmcClearExtraDims(res);
}
void _tmcCreateCellArrayMD(tmsMatrix *res,short ndim,long* arrdims)
{// memory must be allocated already 
long M,N;
short cnt;
	if (ndim<3)
	{
		_tmcCreateCellArray(res,arrdims[0],arrdims[1]);
		return;
	}
	res->m_desc.m_nRows=M=arrdims[0];
	res->m_desc.m_nCols=N=_tmcCountM(ndim,arrdims);
	memset(&res->value,0,sizeof(res->value));
	if (M*N)
	{
	res->value.m_cells = MYMALLOC(M*N*sizeof(tmsMatrix *));
	memset(res->value.m_cells,0,M*N*sizeof(tmsMatrix *));
	}
	res->m_desc.m_type = TYPE_CELL_ARRAY;

	_tmcClearExtraDims(res);
	_tmcCreateDims(res,ndim);
	_tmcSetExtraDim(res,ndim-2);
	for (cnt=0;cnt<ndim;cnt++)
	{
		_tmcSetDim(res,cnt,arrdims[cnt]);
	}
}

void tmccell(long nout,long ninput,tmsMatrix *Y, tmsMatrix *in1,...)
{// restriction: only cell(M,N) syntax is supported
	long m ;

tmsMatrix *in2;
long *arrdims;
short cnt;
	va_list marker;
	va_start( marker, in1 );     // Initialize variable arguments. 
	if (ninput<3)
	{
		in2 = va_arg( marker,  tmsMatrix * );
		_tmcCreateCellArray(Y,(long)in1->value.complx.rData[0],(long)in2->value.complx.rData[0]);
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
		_tmcCreateCellArrayMD(Y,(short)ninput,arrdims);
		MYFREE(arrdims);
	}
		va_end( marker );              // Reset variable arguments.      
	
		for (m=0;m<tmcNumElem(Y);m++)
		Y->value.m_cells[m]= tmcNewMatrix();

}


void _tmcSetCell(tmsMatrix *resmat,long ind, tmsMatrix *a )
{
	resmat->value.m_cells[ind]=a;
}
tmsMatrix * _tmcGetCell(tmsMatrix *X,long ind)
{
	return X->value.m_cells[ind];
}
void tmcCreateCellEmpty(tmsMatrix *matres)
{
	tmcReallocRegister(matres);
	_tmcCreateCellArray(matres,0,0);
}

/**
	\brief Collect rows like [X ; x] (Internal function)
	\param matres: reallocated result
	\param numrows: number of matrices
	\param matN: allocated array of pointers to matrixes, freed by caller.
	Called from tmcCollectRows() operation
*/
void _tmcCollectCellRowsN(tmsMatrix *matres, long numrows, tmsMatrix **matN,long sum_row_dim, long act_numcols)
{
	long ind, ind1,ind2,m,n,M, nc;
	long cnt;
	_tmcCreateCellArray(matres, sum_row_dim, act_numcols);

	nc = 0;//  full number of filled rows
	for (cnt = 0; cnt<numrows; cnt++)
	{
		M = _tmcGetM(matN[cnt]);
		if (!_tmcIsCellArray(matN[cnt]) && !_tmcIsEmptyMatrix(matN[cnt]))
		_tmcRaiseException(must_be_cell_array, s_module, "_tmcCollectCellRowsN", "[X;x]: x must be also cell array", 2,matN[0], matN[cnt]);
		
		if (_tmcGetN(matN[cnt]) != act_numcols && !_tmcIsEmptyMatrix(matN[cnt]))
		{
			_tmcRaiseException(err_invalid_dimentions, s_module, "_tmcCollectCellRowsN", "[X;x]: must have the same number of columns", 2, matN[0], matN[cnt]);
		}

		for (m = 0; m < M; m++) // by row of each added matrix
		{
			ind1 = nc;
			ind2 = m;
			for (n = 0; n<act_numcols; n++)
			{
				matres->value.m_cells[ind1] = tmcNewMatrix();
				tmcAssign(matres->value.m_cells[ind1], matN[cnt]->value.m_cells[ind2]);
				ind1 += sum_row_dim;
				ind2 += M;
			}
			nc++;
		}
	}

}
void tmcCollectCellRows(tmsMatrix *matres,long numrows,tmsMatrix *a,...)
{ // collect some rows of matrixes into a cell array
  // e.g. A= { c1 ; c2 }, c1,c2 must be cell arrays (rows, created internally)
long ind,ind1,nc;
va_list marker;
long sum_row_dim;
long cnt;
long act_numcols;
long M,N;
long m,n,ind2;
tmsMatrix **matN = (tmsMatrix **)MYMALLOC(sizeof(tmsMatrix *) * numrows);

	tmcReallocRegister(matres);

	va_start( marker, a );     // Initialize variable arguments. 
	ind=1;
	matN[0]=a;
	sum_row_dim = _tmcGetM(a);
	act_numcols = _tmcGetN(a); // may be zero
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
		ind++;
	}
	va_end( marker );              // Reset variable arguments.      

	_tmcCreateCellArray(matres,sum_row_dim,act_numcols);
	
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
				matres->value.m_cells[ind1] = tmcNewMatrix();
				tmcAssign(matres->value.m_cells[ind1],matN[cnt]->value.m_cells[ind2]);
				ind1 +=sum_row_dim;
				ind2 +=M;
			}
			nc++;
		}
	}
	MYFREE(matN);
}

/**
\brief Collect columns like [X , x] for single row (Internal function)
\param matres: reallocated result
\param numrows: number of matrices
\param matN: allocated array of pointers to matrixes, freed by caller.
Called from tmcCollectColumns() operation
*/
void _tmcCollectCellColumnsN(tmsMatrix *matres, long numcols, tmsMatrix **matN, long sum_col_dim, long act_numrows)
{
	long m, n,ind1,ind2,cnt,nr,N,M;
	_tmcCreateCellArray(matres, act_numrows, sum_col_dim);
	nr = 0;
	ind1 = 0;
	for (cnt = 0; cnt < numcols; cnt++)
	{
		
		N = _tmcGetN(matN[cnt]);
		M = _tmcGetM(matN[cnt]);

		if (!_tmcIsCellArray(matN[cnt]) && !_tmcIsEmptyMatrix(matN[cnt]))
		_tmcRaiseException(must_be_cell_array, s_module, "_tmcCollectCellColumnsN", "[X,x]: x must be also cell array", 2,matN[0], matN[cnt]);

		if (M != act_numrows && !_tmcIsEmptyMatrix(matN[cnt]))
		{
		_tmcRaiseException(err_invalid_dimentions, s_module, "_tmcCollectCellColumnsN", "[X,x]: must have the same number of columns", 2, matN[0], matN[cnt]);
		}

		ind2 = 0;
		for (n = 0; n <N; n++) // by column of each added matrix
		{
			for (m = 0; m<act_numrows; m++)
			{
					matres->value.m_cells[ind1] = tmcNewMatrix();
					tmcAssign(matres->value.m_cells[ind1], matN[cnt]->value.m_cells[ind2]);
					ind1 +=1;
					ind2 +=1;
				}
				nr++;
			}
		
	}
}

void tmcCollectCellColumns(tmsMatrix *colres,long numcols,tmsMatrix *a,...)
{ // collect a set of matrixes into a cell array (row)
long ind;
va_list marker;
tmsMatrix *mat;


	tmcReallocRegister(colres);

	va_start( marker, a );     // Initialize variable arguments. 
	_tmcCreateCellArray(colres,1,numcols);
	ind=1;
	mat=a;
	colres->value.m_cells[0] = tmcNewMatrix();
	tmcAssign(colres->value.m_cells[0],mat);
	while (ind<numcols)
	{
		mat = va_arg( marker,  tmsMatrix * );
		// simply copy all the matrixes into the single row
		colres->value.m_cells[ind] = tmcNewMatrix();
		tmcAssign(colres->value.m_cells[ind],mat);
		ind++;
	}
	va_end( marker );              // Reset variable arguments.      
}


tmsMatrix  * _tmcGetByIndexCellForce(tmsMatrix *src,long numdims,tmsMatrix **refs)
// get referenced element. If not present - resize matrix.
{
long ind,m,n;
long  arrdims[MAX_MATRIX_DIM];
long  d[MAX_MATRIX_DIM];
long NN;
long k;
short bMustResize=0;
	if (numdims == 1) //HSKOST 2019.09.05 FIX for numdims>1 cells
	{
		if (( _tmcGetM(refs[0])!=1) || (_tmcGetN(refs[0])!=1) || (refs[0]->m_desc.m_type != TYPE_MATRIX))
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"XtmcGetByIndexCell","Illegal cell reference. Too many elements.",1,refs[0]);
		}
		ind = (long)refs[0]->m_rData[0]-1;
		if ( ind<0)
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"XtmcGetByIndexCell","Index negative.",1,refs[0]);
		}

		if (ind >= tmcNumElem(src)  )
		{
			_tmcResizeCellArray(src,numdims,ind,0);
		}
	}
	else if (numdims==2)
	{
		if (( _tmcGetM(refs[1])!=1) || (_tmcGetN(refs[1])!=1) || (refs[1]->m_desc.m_type != TYPE_MATRIX))
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"XtmcGetByIndexCell","Illegal cell reference. Too many elements.",1,refs[1]);
		}
		m=(long)refs[0]->m_rData[0]-1;
		n=(long)refs[1]->m_rData[0]-1;
		if (m<0 ||  n<0)
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"XtmcGetByIndexCell","Index negative.",2,refs[0],refs[1]);
		}
		if (m >= _tmcGetM(src) || n >= _tmcGetN(src) )
		{
			// resize the matrix
			_tmcResizeCellArray(src,numdims,m,n);
		}
		ind = m + n *_tmcGetM(src);
	}
	else if (numdims>=3)
	{//GetByIndexCellForcecellMD

		for (k=0;k<numdims;k++)
		{
			if ( tmcNumElem(refs[k])!=1 ||  (refs[k]->m_desc.m_type != TYPE_MATRIX))
			{
				_tmcRaiseException(err_bad_cell_index,s_module,"_tmcGetByIndexCellForce","Illegal cell reference. Too many elements.",1,refs[k]);
			}
			d[k]=(long)(_tmcScalarVal(refs[k]))-1;
			if (d[k]<0)
			{
			_tmcRaiseException(err_bad_cell_index,s_module,"_tmcGetByIndexCellForce","Index negative.",1,refs[k]);
			}
				arrdims[k] = _tmcGetDimS(src,1+k) ;
				if (d[k] >= arrdims[k])
				{
					bMustResize=	1;
					arrdims[k] = d[k]+1;
				}
		}
		// reshape the result matrix
		// default is not needed reshape
		if (bMustResize)
		{
				_tmcResizeCellArrayMD(src,(short)numdims,arrdims);
		}

		if (numdims == 3)
		{
			ind = d[0] + d[1] * arrdims[0] + d[2] * arrdims[0] * arrdims[1];//see 1-46, HSKOST fix for 3D only 2019.09.22
		}
		else
		{
			_tmcRaiseException(err_bad_cell_index, s_module, "tmcGetByIndexCell", "4D not supported", 0, NULL);
		}

		//ind=d[0];
		//NN=_tmcGetDimS(src,1);
		//for (k=1;k<numdims;k++)
		//{
		//	ind += d[1]*NN;
		//	NN  *= _tmcGetDimS(src,k+1);
		//}


	}
	src->m_desc.m_type = TYPE_CELL_ARRAY;
	return  src->value.m_cells[ind];
}

void tmcGetByIndexCell(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix *I1,...)
{// restriction: only simplified syntax is supported:
 // s{I1} , I1=scalar
 // s{I1,I2} ,I1,I2=scalars
	
va_list marker;
long k;
long ind,m,n;
tmsMatrix **refs = (tmsMatrix **)MYMALLOC(sizeof(tmsMatrix *) * numdims);
long  arrdims[MAX_MATRIX_DIM];
long  d[MAX_MATRIX_DIM];
long NN;

	if (src->m_desc.m_type != TYPE_CELL_ARRAY)
	{
			_tmcRaiseException(err_bad_cell_index,s_module,"tmcGetByIndexCell","Cell contents reference from a non-cell array object.",1,src);
	}



	refs[0]=I1;
	_tmcClearRegister(matres);
	va_start( marker, I1 );     // Initialize variable arguments. 
	for (k=1;k<numdims;k++)
	{
		refs[k] = va_arg( marker,  tmsMatrix * );
	}
	va_end( marker );              // Reset variable arguments.      
	if (numdims==1) //HSKOST 2019.09.05 FIX for numdims>1 cells
	{
		if (( _tmcGetM(refs[0])!=1) || (_tmcGetN(refs[0])!=1) || (refs[0]->m_desc.m_type != TYPE_MATRIX))
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"tmcGetByIndexCell","Illegal cell reference. Too many elements.",1,refs[0]);
		}
		ind = (long)refs[0]->m_rData[0]-1;
		if (ind >= tmcNumElem(src) || ind<0)
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"tmcGetByIndexCell","Index exceeds matrix dimensions.",1,refs[0]);
		}
	}
	else if (numdims==2)
	{
		if (( _tmcGetM(refs[1])!=1) || (_tmcGetN(refs[1])!=1) || (refs[1]->m_desc.m_type != TYPE_MATRIX))
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"tmcGetByIndexCell","Illegal cell reference. Too many elements.",1,refs[1]);
		}
		m=(long)refs[0]->m_rData[0]-1;
		n=(long)refs[1]->m_rData[0]-1;

		if (m >= _tmcGetM(src) || m<0 || n >= _tmcGetN(src) || n<0)
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"tmcGetByIndexCell","Index exceeds matrix dimensions.",2,refs[0],refs[1]);
		}
		ind = m + n *_tmcGetM(src);
	}
	else if (numdims>=3)
	{// getbyindexcellMD 
		for (k=0;k<numdims;k++)
		{
			if ( tmcNumElem(refs[k])!=1 ||  (refs[k]->m_desc.m_type != TYPE_MATRIX))
			{
				_tmcRaiseException(err_bad_cell_index,s_module,"_tmcGetByIndexCell","Illegal cell reference. Too many elements.",1,refs[k]);
			}
			d[k]=(long)(_tmcScalarVal(refs[k]))-1;
			if (d[k]<0)
			{
			_tmcRaiseException(err_bad_cell_index,s_module,"_tmcGetByIndexCell","Index negative.",1,refs[k]);
			}
				arrdims[k] = _tmcGetDimS(src,1+k) ;
				if (d[k] >= arrdims[k])
				{
				_tmcRaiseException(err_bad_cell_index,s_module,"_tmcGetByIndexCell","Index (1) out of range (2).",2,refs[k],src);
				}
		}
		if (numdims == 3)
		{
			ind = d[0] + d[1] * arrdims[0] + d[2] * arrdims[0] * arrdims[1];//see 1-46, HSKOST fix for 3D only 2019.09.22
		}
		else
		{
			_tmcRaiseException(err_bad_cell_index, s_module, "tmcGetByIndexCell", "4D not supported", 0, NULL);
		}
		//ind=d[0];
		//NN=_tmcGetDimS(src,1);
		//for (k=1;k<numdims;k++)
		//{
		//	ind += d[1]*NN;
		//	NN  *= _tmcGetDimS(src,k+1);
		//}
	}

	    tmcAssign(matres,src->value.m_cells[ind]);
		//tmcAssignNoCopy(matres,src->value.m_cells[ind]);

MYFREE(refs);

}
void tmcGetRefByIndexCell(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix *I1,...)
{// restriction: only simplified syntax is supported:
 // s{I1}=x , I1=scalar
 // s{I1,I2}=x ,I1,I2=scalars

va_list marker;
long k;


	if (src->m_desc.m_type != TYPE_REF)
	{
		RefHelper.ndims=0;RefHelper.nrefs=0;RefHelper.src=src;
	}

	RefHelper.dims[RefHelper.ndims]=(short)numdims;
	RefHelper.type[RefHelper.ndims]='{';
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

void _tmcResizeCellArray(tmsMatrix *matres,long numdims,long m,long n)
{// (m,n) are new index we want set.
struct tag_tmsMatrix ** temp;
long ind;
long cnt;
long L;
long M,N;
long M2,N2;
long cntm,cntn;

		M=_tmcGetM(matres);
		N=_tmcGetN(matres);
		L=tmcNumElem(matres);


	if(numdims==1)
	{
				ind = m;

				// new matrix size
				if(M<2)//HAZARD:force reformat corrected 16.12.2012
				{// empty or scalar  --> row
					N2=ind+1;
					M2=1;
				}
				else
				{
					N2=1;
					M2=ind+1;
				}



			if (L>0)
			{
				temp = matres->value.m_cells; // old data
				matres->value.m_cells =MYMALLOC(sizeof(struct tag_tmsMatrix *)*M2*N2); // new room
				memcpy(matres->value.m_cells,temp,L*sizeof(struct tag_tmsMatrix *));
				MYFREE(temp);// MYFREE old data
			}
			else
			{
				matres->value.m_cells=MYMALLOC(sizeof(struct tag_tmsMatrix *)*M2*N2);
				matres->m_desc.m_type=TYPE_CELL_ARRAY;
			}
			for (cnt=L;cnt<=ind;cnt++)
			{
				matres->value.m_cells[cnt]=tmcNewMatrix();
			}
	}
	else if(numdims==2)
	{
		// new matrix size
		M2=__max(m+1,M);
		N2=__max(n+1,N);

		if (L>0)
		{
				temp = matres->value.m_cells; // old data
				matres->value.m_cells =MYMALLOC(sizeof(struct tag_tmsMatrix *)*M2*N2); // new room

			// put back old data
			// must resize existing BUG corrected
			// the matrix data is according column. Go through old columns now:
			ind=0;
			for(cntn=0;cntn<N;cntn++)
			{
				for(cntm=0;cntm<M;cntm++)
				{
					matres->value.m_cells[cntn*M2+cntm]=temp[ind++];
				}
			}
			MYFREE(temp);// MYFREE old data

		}
		else
		{
			// create new
			matres->value.m_cells=MYMALLOC(sizeof(struct tag_tmsMatrix *)*(m+1)*(n+1));
			matres->m_desc.m_type=TYPE_CELL_ARRAY;
		}

		for(cntm=M;cntm<M2;cntm++)
		{
			for(cntn=0;cntn<N;cntn++)
			{
				matres->value.m_cells[cntn*M2+cntm]=tmcNewMatrix();
			}
		}
		for(cntm=0;cntm<M2;cntm++)
		{
			for(cntn=N;cntn<N2;cntn++)
			{
				matres->value.m_cells[cntn*M2+cntm]=tmcNewMatrix();
			}
		}
	}
	else if (numdims>=3)
	{
			_tmcRaiseException(err_invalid_dimentions,s_module,"_tmcResizeCellArray","Illegal dimension.",0,NULL);
	}
	matres->m_desc.m_nCols=N2;
	matres->m_desc.m_nRows=M2;
}

void  _tmcSetByIndexCell(tmsMatrix *matres,tmsMatrix *src,long numdims,tmsMatrix **refs)
{// actual assignment to cell array
 // restriction: only simplified syntax is supported:
 // s{I1}=x , I1=scalar
 // s{I1,I2}=x ,I1,I2=scalars
 // s MUST be cell array of the appropriate dimension.
 // matres already exists
short k;
long ind,m,n;
short bMustResize=0;
long  arrdims[MAX_MATRIX_DIM];
long  d[MAX_MATRIX_DIM];
long NN;

	if (matres->m_desc.m_type == TYPE_NOTHING)
	{
			matres->m_desc.m_type=TYPE_CELL_ARRAY;// empty cell array
	}


	if (matres->m_desc.m_type != TYPE_CELL_ARRAY)
	{
		_tmcClearRegister(matres);
		//	_tmcRaiseException(err_bad_cell_index,s_module,"_tmcSetByIndexCell","Lhs must be cell array.",1,src);
	}

	if (numdims==1)
	{
		if (( _tmcGetM(refs[0])!=1) || (_tmcGetN(refs[0])!=1) || (refs[0]->m_desc.m_type != TYPE_MATRIX))
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"_tmcSetByIndexCell","Illegal cell reference. Too many elements.",1,refs[0]);
		}
		ind = (long)refs[0]->m_rData[0]-1;
		if (ind<0)
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"_tmcSetByIndexCell","Index negative.",1,refs[0]);
		}
		if (ind >= tmcNumElem(matres) )
		{
			// resize the matrix
			_tmcResizeCellArray(matres,numdims,ind,0);
		}

	}
	else if (numdims==2)
	{
		if (( _tmcGetM(refs[1])!=1) || (_tmcGetN(refs[1])!=1) || (refs[1]->m_desc.m_type != TYPE_MATRIX))
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"_tmcSetByIndexCell","Illegal cell reference. Too many elements.",1,refs[1]);
		}
		m=(long)refs[0]->m_rData[0]-1;
		n=(long)refs[1]->m_rData[0]-1;
		if ( m<0 ||   n<0)
		{
			_tmcRaiseException(err_bad_cell_index,s_module,"_tmcSetByIndexCell","Index negative.",2,refs[0],refs[1]);
		}
		if (m >= _tmcGetM(matres)  || n >= _tmcGetN(matres)  )
		{
			// resize the matrix
			_tmcResizeCellArray(matres,numdims,m,n);
		}
		ind = m + n *_tmcGetM(matres);

	}
	else if (numdims>=3)
	{

		for (k=0;k<numdims;k++)
		{
			if ( tmcNumElem(refs[k])!=1 ||  (refs[k]->m_desc.m_type != TYPE_MATRIX))
			{
				_tmcRaiseException(err_bad_cell_index,s_module,"_tmcSetByIndexCell","Illegal cell reference. Too many elements.",1,refs[k]);
			}
			d[k]=(long)(_tmcScalarVal(refs[k]))-1;
			if (d[k]<0)
			{
			_tmcRaiseException(err_bad_cell_index,s_module,"_tmcSetByIndexCell","Index negative.",1,refs[k]);
			}
				arrdims[k] = _tmcGetDimS(matres,1+k) ;
				if (d[k] >= arrdims[k])
				{
					bMustResize=	1;
					arrdims[k] = d[k]+1;
				}
		}
		// reshape the result matrix
		// default is not needed reshape
		if (bMustResize)
		{
				_tmcResizeCellArrayMD(matres,(short)numdims,arrdims);
		}
		if (numdims==3)
		{
			ind = d[0] + d[1] * arrdims[0] + d[2] * arrdims[0] * arrdims[1];//see 1-46, HSKOST fix for 3D only 2019.09.22
		}
		else
		{
			_tmcRaiseException(err_bad_cell_index, s_module, "_tmcSetByIndexCell", "4D not supported", 0,NULL);
		}
		//ind=d[0];
		//NN=_tmcGetDimS(matres,1);
		//for (k=1;k<numdims;k++)
		//{
		//	ind += d[1]*NN;
		//	NN  *= _tmcGetDimS(matres,k+1);
		//}
	}
	tmcAssign(matres->value.m_cells[ind],src);
}
void tmccell2mat(long nout,long ninput, tmsMatrix *y, tmsMatrix *x)
{
//HAZARD_TODO_QFD:
	_tmcRaiseException(err_unsupported,"main","tmccell2mat","FATAL: tmccell2mat is not yet implemented!!!.",0,NULL);
}
void _tmcResizeCellArrayMD(tmsMatrix *matres,short numdims,long *arrdims)
{
	long L;
	long n;
long  d[MAX_MATRIX_DIM];
long  SrcDimProd[MAX_MATRIX_DIM-1];
long  DstDimProd[MAX_MATRIX_DIM-1];
long  SrcDim[MAX_MATRIX_DIM];

long  inx[MAX_MATRIX_DIM];
long  inxs[MAX_MATRIX_DIM];
long MN;
short k;
struct tag_tmsMatrix ** temp;

numdims = _tmcGetReducedDim(numdims,arrdims);
	if (numdims<3)
	{
		_tmcResizeCellArray(matres,numdims,arrdims[0]-1,arrdims[1]-1);
	}
	else
	{

				if (numdims>4)
				{
						_tmcRaiseException(err_unsupported,s_module,"_tmcResizeCellArrayMD","x(I,J,...) supported for ndim<5",0,NULL);
				}


		L=tmcNumElem(matres);

		    MN=1;// new matrix size
			for (k=0;k<numdims;k++)
			{
				SrcDim[k] = _tmcGetDim(matres,1+k); // old dims
				arrdims[k] = __max(arrdims[k], SrcDim[k]  );// new dims
				MN *= arrdims[k]; 

			}

			DstDimProd[0] = arrdims[0];// M
			SrcDimProd[0] = SrcDim[0];// M

			for (k=1;k<numdims-1;k++)
			{
				DstDimProd[k] = arrdims[k] * DstDimProd[k-1];// M*N,M*N*K etc.
				SrcDimProd[k] = SrcDim[k] * SrcDimProd[k-1];// M*N,M*N*K etc.
			}
			// set new dimentions 
			_tmcRedimArrayMD(matres,numdims,arrdims);


				// create new
			    temp = matres->value.m_cells; // old data
				matres->value.m_cells =MYMALLOC(sizeof(struct tag_tmsMatrix *)*MN); // new room
				memset(matres->value.m_cells,0,sizeof(struct tag_tmsMatrix *)*MN);
				matres->m_desc.m_type=TYPE_CELL_ARRAY;

		if (L>0)
		{
				// copy existing data
				if (numdims==3)
				{
					for (d[2]=0;d[2]<SrcDim[2];d[2]++)
					{
						inx[2]=  d[2] * DstDimProd[1];// M*N*k
						inxs[2]=  d[2] * SrcDimProd[1];// M*N*k

						for(d[1]=0;d[1]<SrcDim[1];d[1]++)
						{
							inx[1]=(d[1]  * DstDimProd[0])+ inx[2];// M*n+M*N*k
							inxs[1]=(d[1]  * SrcDimProd[0])+ inxs[2];// M*n+M*N*k

							for (d[0]=0;d[0]<SrcDim[0];d[0]++)
							{
							inx[0]= d[0] +inx[1];// m+M*n+M*N*k
							inxs[0]= d[0] +inxs[1];// m+M*n+M*N*k

							matres->value.m_cells[inx[0]]=temp[inxs[0]];
							}
						}
					}
				}
				else if (numdims==4)
				{
				for (d[3]=0;d[3]<SrcDim[3];d[3]++)
					{
						inx[3]=  d[3] * DstDimProd[2];// M*N*K*l
						inxs[3]=  d[3] * SrcDimProd[2];// M*N*K*l

						for (d[2]=0;d[2]<SrcDim[2];d[2]++)
						{
							inx[2]= (d[2] * DstDimProd[1])+inx[3];// M*N*k+M*N*K*l
							inxs[2]= (d[2] * SrcDimProd[1])+inxs[3];// M*N*k+M*N*K*l

							for(d[1]=0;d[1]<SrcDim[1];d[1]++)
							{
								inx[1]= ( d[1]  * DstDimProd[0])+ inx[2];// M*n+M*N*k+.
								inxs[1]= ( d[1]  * SrcDimProd[0])+ inxs[2];// M*n+M*N*k+.
								for (d[0]=0;d[0]<SrcDim[0];d[0]++)
								{

								inx[0]= d[0] +inx[1];// m+M*n+M*N*k+.
								inxs[0]= d[0] +inxs[1];// m+M*n+M*N*k+.

								matres->value.m_cells[inx[0]]=temp[inxs[0]];
								}
							}
						}
					}
				}
				else
				{
						_tmcRaiseException(err_unsupported,s_module,"_tmcResizeCellArrayMD","x(I,J,...) supported for ndim<5",0,NULL);
				}
				MYFREE(temp);// MYFREE old data

		}
		// assign empty matrix at not initialized indexes
		for (n=0;n<MN;n++)
		{
			if (matres->value.m_cells[n]==NULL)
			{
				matres->value.m_cells[n]=tmcNewMatrix();
			}
		}
//	_tmcRaiseException(err_unsupported,"main","_tmcResizeCellArrayMD","HAZARD_TODO_QFD_MD!!!.",0,NULL);


	}

}
