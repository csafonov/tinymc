// tmcdbg.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <stddef.h>

#include "..\tmclib\tmc.h"
#include <stdio.h>
#include <conio.h>

#define DEBUG_MEM_LEN 10

void *lpBaseAddress;
char Buffer[DEBUG_MEM_LEN];
DWORD nSize;
DWORD NumberOfBytesRead;
HANDLE hProcess_copy;
DWORD h_Other_id;

int debug1; 
int ReadRemoteMatrix(tmsMatrix *mat,void* lpBaseAddress)
{
DWORD NumberOfBytesRead;
int stat;
double *ptr;
long NN;
long k;
	STRINGCODE *hcFields;
	struct tag_tmsMatrix **m_fields; // m x n x k

	stat=ReadProcessMemory(hProcess_copy,lpBaseAddress,mat,sizeof(tmsMatrix),&NumberOfBytesRead);

	switch (mat->m_desc.m_type)
	{
	case TYPE_NOTHING://=-1
		break;

	case TYPE_MATRIX://=0, // simple matrix
	case TYPE_STRING://=2
		NN=sizeof(double)*tmcNumElem(mat);
		ptr=(double*)MYMALLOC(NN);
		stat=ReadProcessMemory(hProcess_copy,(void*)mat->value.complx.rData,ptr,NN,&NumberOfBytesRead);
		mat->value.complx.rData=ptr;
		if (_tmcHasIm(mat))
		{
			ptr=(double*)MYMALLOC(sizeof(double)*tmcNumElem(mat));
			stat=ReadProcessMemory(hProcess_copy,(void*)mat->value.complx.iData,ptr,NN,&NumberOfBytesRead);
			mat->value.complx.iData=ptr;
		}
		break;
	case TYPE_STRUCT://1
		NN=sizeof(STRINGCODE)*mat->value.StructDef.m_nFields;
		hcFields=(STRINGCODE*)MYMALLOC(NN);
			stat=ReadProcessMemory(hProcess_copy,(void*)mat->value.StructDef.hcFields,hcFields,NN,&NumberOfBytesRead);
			mat->value.StructDef.hcFields=hcFields;
		NN=sizeof(tmsMatrix *)*mat->value.StructDef.m_nFields*tmcNumElem(mat);
		m_fields=(tmsMatrix **)MYMALLOC(NN);

			stat=ReadProcessMemory(hProcess_copy,(void*)mat->value.StructDef.m_fields,m_fields,NN,&NumberOfBytesRead);
		mat->value.StructDef.m_fields=(tmsMatrix **)MYMALLOC(NN);
		NN=mat->value.StructDef.m_nFields*tmcNumElem(mat);
		for (k=0;k<NN;k++)
		{
			mat->value.StructDef.m_fields[k]=tmcNewMatrix();
			stat= ReadRemoteMatrix(mat->value.StructDef.m_fields[k],m_fields[k]);
		}
		free(m_fields);
		break;
	case TYPE_CELL_ARRAY://3
		NN=sizeof(tmsMatrix *)*tmcNumElem(mat);
		m_fields=(tmsMatrix **)MYMALLOC(NN);

		stat=ReadProcessMemory(hProcess_copy,(void*)mat->value.m_cells,m_fields,NN,&NumberOfBytesRead);
		mat->value.m_cells=(tmsMatrix **)MYMALLOC(NN);
		NN=tmcNumElem(mat);
		for (k=0;k<NN;k++)
		{
			mat->value.m_cells[k]=tmcNewMatrix();
			stat= ReadRemoteMatrix(mat->value.m_cells[k],m_fields[k]);
		}
		free(m_fields);
		break;


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

char tempbuf[100]={1,2,3,4};
double stam;
int main(int argc, char* argv[])
{
	BOOL stat;
tmsMatrix mat;
HANDLE hWnd;
FILE *fp;
/*
BOOL DuplicateHandle(
  HANDLE hSourceProcessHandle,  // handle to the source process
  HANDLE hSourceHandle,         // handle to duplicate
  HANDLE hTargetProcessHandle,  // handle to process to duplicate to
  LPHANDLE lpTargetHandle,  // pointer to duplicate handle
  DWORD dwDesiredAccess,    // access for duplicate handle
  BOOL bInheritHandle,      // handle inheritance flag
  DWORD dwOptions           // optional actions
);
*/
fprintf(stdout,"TMC Debugger, TMC Group (C) 2011\n");
tmcInitLib(&Init_funcs_table);
		
		fp = fopen("matrix_off.txt","w");


		fprintf(fp,"szDouble=%d;\n",sizeof(double));
		fprintf(fp,"szAddr=%d;\n",sizeof(HANDLE));
		fprintf(fp,"szTmcMat=%d;\n",sizeof(tmsMatrix));
		fprintf(fp,"ofs_m_type=%d;\n", offsetof( tmsMatrix, m_desc.m_type ));
		fprintf(fp,"ofs_m_nRows=%d;\n", offsetof( tmsMatrix,m_desc.m_nRows));
		fprintf(fp,"ofs_m_nCols=%d;\n", offsetof( tmsMatrix,m_desc.m_nCols));
		fprintf(fp,"ofs_rData=%d;\n", offsetof( tmsMatrix,value.complx.rData));
		fprintf(fp,"ofs_iData=%d;\n", offsetof( tmsMatrix,value.complx.iData));
		fprintf(fp,"ofs_m_modifier=%d;\n", offsetof( tmsMatrix,m_desc.m_modifier));
		fprintf(fp,"ofs_m_cells=%d;\n", offsetof( tmsMatrix,value.m_cells));

		fprintf(fp,"ofs_m_nFields=%d;\n", offsetof( tmsMatrix,value.StructDef.m_nFields));
		fprintf(fp,"ofs_hcFields=%d;\n", offsetof( tmsMatrix,value.StructDef.hcFields));
		fprintf(fp,"ofs_m_fields=%d;\n", offsetof( tmsMatrix,value.StructDef.m_fields));




		fclose(fp);

		hWnd=FindWindow("edit","tmcdebug");
		if (hWnd)
			GetWindowThreadProcessId(hWnd,&h_Other_id);
		else
		{
			fprintf(stdout,"Cant connect to debugged appication. Start the application and try again!\n PRESS OK...");
			getch();
			return -1;
		}
		hProcess_copy = OpenProcess(PROCESS_ALL_ACCESS,FALSE,h_Other_id);
		//stat=DuplicateHandle(hProcess,hProcess,hProcess,&hProcess_copy,PROCESS_DUP_HANDLE | PROCESS_VM_READ,1,0);

//lpBaseAddress=(void*)&tempbuf[0];nSize=6;
	for ( ; ; )
	{
		fprintf(stdout,"tmcMatrix>");
		scanf("%x",&lpBaseAddress);
		ReadRemoteMatrix(&mat,lpBaseAddress);
		//stat=ReadProcessMemory(hProcess_copy,lpBaseAddress,&Buffer[0],nSize,&NumberOfBytesRead);
		//Sleep(100);
		tmcdisp(1,1,&mat);
		_tmcClearRegister(&mat);
	}
	return 0;
}

//////////
//void tmcInitGlobals(void)
//{
//}
//void tmcFreeGlobals(void)
//{
//}

