/*
   Copyright (C) Shmuel Safonov 2009-2012 All rights reserved.
   Any usage of this file must be according to TMC License.
*/
// tmcdbg.cpp : Defines the entry point for the console application.
//
//#include "forcelib.h" // to assure MFC linked before CRT

#include <windows.h>
#include <stddef.h>


#include "tmc.h"
#include "tmcstringhash.h"
#include <stdio.h>
#include <conio.h>

const char * hcode2string_remote(STRINGCODE hcode);

#ifdef _DEBUG
//#pragma comment(lib,"tmcrtvc8d.lib")
#else
//#pragma comment(lib,"tmcrtvc8.lib")
#endif

/*
"short __cdecl tmcInitLib(struct CInit_funcs_table const *)" (?tmcInitLib@@YAFPBUCInit_funcs_table@@@Z)
tmcdbgW.obj : error LNK2001: unresolved external symbol "struct CInit_funcs_table const Init_funcs_table" (?Init_funcs_table@@3UCInit_funcs_table@@B)
tmcdbg.obj : error LNK2001: unresolved external symbol "struct tag_tmsMatrix * __cdecl __tmcNewMatrix(void)" (?__tmcNewMatrix@@YAPAUtag_tmsMatrix@@XZ)
tmcdbg.obj : error LNK2001: unresolved external symbol "void * __cdecl my_malloc(unsigned int)" (?my_malloc@@YAPAXI@Z)
tmcdbg.obj : error LNK2001: unresolved external symbol "long __cdecl tmcNumElem(struct tag_tmsMatrix *)" (?tmcNumElem@@YAJPAUtag_tmsMatrix@@@Z)
tmcdbg.obj : error LNK2001: unresolved external symbol "void __cdecl _tmcClearRegister(struct tag_tmsMatrix *)" (?_tmcClearRegister@@YAXPAUtag_tmsMatrix@@@Z)
tmcdbg.obj : error LNK2001: unresolved external symbol "void __cdecl tmcdisp(long,long,struct tag_tmsMatrix *)" (?tmcdisp@@YAXJJPAUtag_tmsMatrix@@@Z)
*/

#define DEBUG_MEM_LEN 10


//char Buffer[DEBUG_MEM_LEN];
//DWORD nSize;
//SIZE_T NumberOfBytesRead;
HANDLE hProcess_copy;
struct CTmcDbgCommonBlock *pcliTmcDbgCommonBlock;
struct CTmcDbgStack			cliTmcDbgStack;
DWORD err;

//cliTmcDbgStack.bp is not used  and eq zero

long remote_frame_length(void)
{
SIZE_T NumberOfBytesRead;
int	stat=ReadProcessMemory(hProcess_copy,pcliTmcDbgCommonBlock->stack_addr,&cliTmcDbgStack,2*sizeof(tmcindex),&NumberOfBytesRead);
	if (!stat)
		err=GetLastError();

return cliTmcDbgStack.sp - cliTmcDbgStack.bp;
}


#define MAX_REMOTE_NAME_LEN 500
char remote_varname[1000];
LPCSTR  remote_frame_name_at(long k)
{
long m;
SIZE_T NumberOfBytesRead;
int	stat=ReadProcessMemory(hProcess_copy,pcliTmcDbgCommonBlock->stack_addr,&cliTmcDbgStack,sizeof(cliTmcDbgStack),&NumberOfBytesRead);
	if (!stat)
		err=GetLastError();

	m=0;
	while (m<MAX_REMOTE_NAME_LEN)
	{
     stat=ReadProcessMemory(hProcess_copy,cliTmcDbgStack.stack[k].varname+m,&remote_varname[m],1,&NumberOfBytesRead);
	 if (!stat)
		err=GetLastError();
	 if (remote_varname[m]==0)
		 break;
	 m++;
	}

return remote_varname;
}
void    * remote_frame_addr_at(long k)
{
	SIZE_T NumberOfBytesRead;
int	stat=ReadProcessMemory(hProcess_copy,pcliTmcDbgCommonBlock->stack_addr,&cliTmcDbgStack,sizeof(cliTmcDbgStack),&NumberOfBytesRead);
	if (!stat)
		err=GetLastError();
return cliTmcDbgStack.stack[k].vaddr;
}

short  remote_etype_at(long k)
{
	SIZE_T NumberOfBytesRead;
int	stat=ReadProcessMemory(hProcess_copy,pcliTmcDbgCommonBlock->stack_addr,&cliTmcDbgStack,sizeof(cliTmcDbgStack),&NumberOfBytesRead);
	if (!stat)
		err=GetLastError();
	return cliTmcDbgStack.stack[k].etype;
}

int debug1; 
int ReadRemoteMatrix(tmsMatrix *mat,void* lpBaseAddress)
{
	SIZE_T NumberOfBytesRead;
int stat;
double *ptr;
long NN;
long k;
long *ptrD;

	STRINGCODE *hcFields;
	struct tag_tmsMatrix **m_fields; // m x n x k

	stat=ReadProcessMemory(hProcess_copy,lpBaseAddress,mat,sizeof(tmsMatrix),&NumberOfBytesRead);

		if (_tmcHasExtraDim(mat))
		{
			NN = sizeof(long)*(_tmcGetExtraDim(mat)+2);
			ptrD=(long*)MYMALLOC(NN);
			stat=ReadProcessMemory(hProcess_copy,(void*)mat->m_desc.m_dims,ptrD,NN,&NumberOfBytesRead);
			mat->m_desc.m_dims=ptrD;
		}

	switch (mat->m_desc.m_type)
	{
	case TYPE_NOTHING://=-1
		break;

	case TYPE_MATRIX://=0, // simple matrix
	case TYPE_STRING://=2
		NN=sizeof(double)*_tmcGetNumElem(mat);
		if (NN>0)
		{
			ptr=(double*)MYMALLOC(NN);
			stat=ReadProcessMemory(hProcess_copy,(void*)mat->value.complx.rData,ptr,NN,&NumberOfBytesRead);
			mat->value.complx.rData=ptr;
			if (_tmcHasIm(mat))
			{
				ptr=(double*)MYMALLOC(sizeof(double)*_tmcGetNumElem(mat));
				stat=ReadProcessMemory(hProcess_copy,(void*)mat->value.complx.iData,ptr,NN,&NumberOfBytesRead);
				mat->value.complx.iData=ptr;
			}
		}
		else
		{
			// matrix is empty but may be pointer remained not zero after X(I)=[]. Actually it is a bug but we should
			// protect here.
			if (mat->value.complx.rData)
			{
				mat->value.complx.rData  = NULL; // must give warning here
			}
			if (mat->value.complx.iData)
			{
				mat->value.complx.iData  = NULL; // must give warning here
			}
		}
		break;
	case TYPE_STRUCT://1
		NN=sizeof(STRINGCODE)*mat->value.StructDef.m_nFields;
		if (NN>0)
		{
			hcFields=(STRINGCODE*)MYMALLOC(NN);
				stat=ReadProcessMemory(hProcess_copy,(void*)mat->value.StructDef.hcFields,hcFields,NN,&NumberOfBytesRead);
				mat->value.StructDef.hcFields=hcFields;
			NN=sizeof(tmsMatrix *)*mat->value.StructDef.m_nFields*_tmcGetNumElem(mat);
			m_fields=(tmsMatrix **)MYMALLOC(NN);

				stat=ReadProcessMemory(hProcess_copy,(void*)mat->value.StructDef.m_fields,m_fields,NN,&NumberOfBytesRead);
			mat->value.StructDef.m_fields=(tmsMatrix **)MYMALLOC(NN);
			NN=mat->value.StructDef.m_nFields*_tmcGetNumElem(mat);
			for (k=0;k<NN;k++)
			{
				mat->value.StructDef.m_fields[k]=tmcNewMatrix();
				stat= ReadRemoteMatrix(mat->value.StructDef.m_fields[k],m_fields[k]);
			}
			free(m_fields);
		}
		else
		{
			if (mat->value.StructDef.hcFields)
			{
				mat->value.StructDef.hcFields=NULL;// must give warning here
			}
			if (mat->value.StructDef.m_fields)
			{
				mat->value.StructDef.m_fields=NULL;// must give warning here
			}
		}
		break;
	case TYPE_CELL_ARRAY://3
		NN=sizeof(tmsMatrix *)*_tmcGetNumElem(mat);
		if (NN>0)
		{
			m_fields=(tmsMatrix **)MYMALLOC(NN);

			stat=ReadProcessMemory(hProcess_copy,(void*)mat->value.m_cells,m_fields,NN,&NumberOfBytesRead);
			mat->value.m_cells=(tmsMatrix **)MYMALLOC(NN);
			NN= _tmcGetNumElem(mat);
			for (k=0;k<NN;k++)
			{
				mat->value.m_cells[k]=tmcNewMatrix();
				stat= ReadRemoteMatrix(mat->value.m_cells[k],m_fields[k]);
			}
			free(m_fields);
		}
		else
		{
			if (mat->value.m_cells)
				mat->value.m_cells = NULL;// must give warning here

		}
		break;


	/*TYPE_STRUCT=1,
	TYPE_STRING=2,
	TYPE_CELL_ARRAY=3,
	TYPE_MAGIC_COLON=4,
	TYPE_REF=5,
	TYPE_ITERATOR=7,
	TYPE_FNC_HANDLE=9,
    */


	}
	return stat;
}

short InitTmc(void)
{
//	tmcInitLib(&Init_funcs_table);
	return 0;
}
short  FreeTmc(void)
{
//tmcFreeLib();
return 0;
}

short ConnectTmc()
{
	DWORD h_Other_id;
HWND hWnd;
		hWnd=FindWindow(L"edit",L"tmcdebug");
		if (hWnd)
			GetWindowThreadProcessId(hWnd,&h_Other_id);
		else
		{
			MessageBox(NULL,L"Cant fine the debugged appication window(tmcdebug).",L"fail",MB_OK);
		//	fprintf(stdout,"Cant connect to debugged appication. Start the application and try again!\n PRESS OK...");
		//	getch();
			return -1;
		}
		hProcess_copy = OpenProcess(PROCESS_ALL_ACCESS,FALSE,h_Other_id);
		
		tmcdbgCommonMemConnect((void**)& pcliTmcDbgCommonBlock);

return 0;
}
////////////////////////////////////////////////////////////////
char tembuffer[50000000];
unsigned short uni_tembuffer[50000000];

char *out;

char* get_out(void)
{
		return tembuffer;
}
LPCTSTR uni_get_out(void)
{
		return (LPCTSTR)uni_tembuffer;
}
void buffer_to_uni()
{
	SIZE_T k;
	SIZE_T n=strlen(tembuffer);
	for (k=0;k<n;k++)
	{
		uni_tembuffer[k]=tembuffer[k];
	}
	uni_tembuffer[k]=0;

}

wchar_t wstambuf[1000];
const wchar_t * string2uni(const char *str)
{
	SIZE_T k;
	SIZE_T len=strlen(str);

	for (k=0;k<len;k++)
	{
		wstambuf[k]=str[k];
	}
wstambuf[len]=0;
return wstambuf;
}

void DisplayMat(tmsMatrix *x,short bVerb)
{
	long m,n;
	short k;
	long M = _tmcGetM(x);
	long N = _tmcGetN(x);
int lenout;


	if (x->m_desc.m_type == TYPE_CELL_ARRAY)
	{
		lenout=sprintf(out,"CellArray(%d,%d) ={\r\n",M,N);out+=lenout;
		for (m=0;m<M;m++)
		{
			for (n=0;n<N;n++)
			{
				lenout=sprintf(out,"[%d,%d]=",m+1,n+1);out+=lenout;
				DisplayMat(x->value.m_cells[m+n*M],bVerb);
				lenout=sprintf(out,";\r\n");out+=lenout;
			}
		}
		lenout=sprintf(out,"};\r\n");out+=lenout;
	return ;
	}

	if (x->m_desc.m_type == TYPE_STRUCT)
	{
		lenout=sprintf(out,"Structure(%d,%d) =\r\n",M,N);out+=lenout;
		for (m=0;m<M;m++)
		{
			for (n=0;n<N;n++)
			{
				lenout=sprintf(out,"[%d,%d]=",m+1,n+1);out+=lenout;
				for (k=0;k<_tmcGetNf(x);k++)
				{
					lenout=sprintf(out,"\t field %s=\r\n",hcode2string_remote(x->value.StructDef.hcFields[k]));out+=lenout;
				    DisplayMat(x->value.StructDef.m_fields[(m+n*M)+k*M*N],bVerb);
				    lenout=sprintf(out,";\r\n");out+=lenout;
				}
			}
		}
		lenout=sprintf(out,"END Structure;\r\n");out+=lenout;
		return;
	}
	if ( bVerb || x->m_desc.m_type != TYPE_STRING)
	{	lenout=sprintf(out,"Matrix(%d,%d) =[\r\n",M,N);out+=lenout;}
	if (x->m_desc.m_type == TYPE_STRING)
	{
			for (m=0;m<M;m++)
			{
				for (n=0;n<N;n++)
				{
				lenout=sprintf(out,"%c",(char)x->m_rData[m*N+n]);out+=lenout;
				}
			lenout=sprintf(out,"\r\n");out+=lenout;
			}
	}
	else
	for (m=0;m<M;m++)
	{
		for (n=0;n<N;n++)
		{
			if (_tmcHasIm(x)==0)
			{
			lenout=sprintf(out,"%.15g,\t",x->m_rData[n*M+m]);
			out+=lenout;
			}
			else
			{
			if(x->m_iData[n*M+m])
			{lenout=sprintf(out,"%.15g + \t%.15gi,\t",x->m_rData[n*M+m],x->m_iData[n*M+m]);
			out+=lenout;}
			else
			{lenout=sprintf(out,"%.15g\t   ,\t",x->m_rData[n*M+m]);
			out+=lenout;}
			}

		}
		lenout=sprintf(out,";\r\n");out+=lenout;
	}
	if ( bVerb || x->m_desc.m_type != TYPE_STRING)
	{lenout=sprintf(out,"];\r\n");out+=lenout;}
	else
	{lenout=sprintf(out,"\r\n");out+=lenout;}

}

short PrintMatrixLocal(tmsMatrix *mat,short fmt)
{
		out=tembuffer;
		DisplayMat(mat,fmt);
		*out=0;
		return 0;
}
void LoadExternalMatrix(tmsMatrix *mat,void *_lpBaseAddress)
{
	void *lpBaseAddress;
		lpBaseAddress=_lpBaseAddress;
		ReadRemoteMatrix(mat,lpBaseAddress);
}
short PrintMatrix(void *_lpBaseAddress)
{
tmsMatrix mat;
		LoadExternalMatrix(&mat,_lpBaseAddress);

	//lpBaseAddress=_lpBaseAddress;
		//ReadRemoteMatrix(&mat,lpBaseAddress);
		//stat=ReadProcessMemory(hProcess_copy,lpBaseAddress,&Buffer[0],nSize,&NumberOfBytesRead);
		//Sleep(100);
		PrintMatrixLocal(&mat,1);
		//out=tembuffer;
		//DisplayMat(&mat,1);
		//*out=0;
		_tmcClearRegister(&mat);

return 0;
}
void PrintOffsets()
{
FILE *fp;
		fp = fopen("matrix_off.txt","w");


		fprintf(fp,"szDouble=%zd;\n",sizeof(double));
		fprintf(fp,"szAddr=%zd;\n",sizeof(HANDLE));
		fprintf(fp,"szTmcMat=%zd;\n",sizeof(tmsMatrix));
		fprintf(fp,"ofs_m_type=%zd;\n", offsetof( tmsMatrix, m_desc.m_type ));
		fprintf(fp,"ofs_m_nRows=%zd;\n", offsetof( tmsMatrix,m_desc.m_nRows));
		fprintf(fp,"ofs_m_nCols=%zd;\n", offsetof( tmsMatrix,m_desc.m_nCols));
		fprintf(fp,"ofs_rData=%zd;\n", offsetof( tmsMatrix,value.complx.rData));
		fprintf(fp,"ofs_iData=%zd;\n", offsetof( tmsMatrix,value.complx.iData));
		fprintf(fp,"ofs_m_modifier=%zd;\n", offsetof( tmsMatrix,m_desc.m_modifier));
		fprintf(fp,"ofs_m_cells=%zd;\n", offsetof( tmsMatrix,value.m_cells));

		fprintf(fp,"ofs_m_nFields=%zd;\n", offsetof( tmsMatrix,value.StructDef.m_nFields));
		fprintf(fp,"ofs_hcFields=%zd;\n", offsetof( tmsMatrix,value.StructDef.hcFields));
		fprintf(fp,"ofs_m_fields=%zd;\n", offsetof( tmsMatrix,value.StructDef.m_fields));




		fclose(fp);

}

char buff_notsring_remote[1000];
const char * hcode2string_remote(STRINGCODE hcode)
{
	//register bucket *bp, **bpp;
	bucket *bp;
	bucket  b ;
	short n;
	unsigned long hashcode = ((hcode >> 16) & 0x0000FFFF);
	int stat;
	SIZE_T NumberOfBytesRead;
	char c;
	short ind;

	stat = ReadProcessMemory(hProcess_copy, (void*)(pcliTmcDbgCommonBlock->psymbol_table + hashcode), &bp,sizeof(bp), &NumberOfBytesRead);
	

	//bpp = symbol_table + hashcode;
	//bp = *bpp;

	n = 0;
	while (bp)
	{
		stat = ReadProcessMemory(hProcess_copy, (void*)bp, &b, sizeof(b), &NumberOfBytesRead);
		if (b.hcode == hcode)
		{
			ind = 0;
			c = '?';// read NULL-terminated string
			while (c)
			{
				stat = ReadProcessMemory(hProcess_copy, (void*)(b.name+ind), &c, sizeof(char), &NumberOfBytesRead);
				buff_notsring_remote[ind++] = c;
			}
			return (const char *)&buff_notsring_remote[0];
			//return (bp->name);
		}
		n++;
		//bpp = &bp->link;
		//bp = *bpp;
		stat = ReadProcessMemory(hProcess_copy, (void*)b.link, &bp, sizeof(bp), &NumberOfBytesRead);
	}
	buff_notsring_remote[0] = 0;
	if (bp == NULL)
	{
		fprintf(stderr, "\nHCODE=0x%x:no_string", hcode);
		sprintf(buff_notsring_remote, "HCODE_0x%x", hcode);
		//	_tmcRaiseException(err_bad_init,s_module,"no_string","Cant find string in hash table",0,NULL);
	}
	return (const char *)&buff_notsring_remote[0];
}

////////////////
