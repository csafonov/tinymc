/* Build:
mex -g -D_MBCS gettmcmat.c user32.lib  __init_hash_data.c ..\tmclib\cmatrix.c ..\tmclib\tmccell.c  ..\tmclib\tmclib.c ..\tmclib\tmcmstruct.c ..\tmclib\tmcstringhash.c
*/
#include <windows.h>
#include "mex.h"
#include "..\tmclib\tmc.h"

#define DEBUG_MEM_LEN 10

void *lpBaseAddress;
char Buffer[DEBUG_MEM_LEN];
DWORD nSize;
DWORD NumberOfBytesRead;
HANDLE hProcess_copy;
DWORD h_Other_id;

int ReadRemoteMatrix(tmsMatrix *mat,mxArray **Y,void* lpBaseAddress);

int ReadRemoteMatrix(tmsMatrix *mat,mxArray **Y,void* lpBaseAddress)
{
DWORD NumberOfBytesRead;
int stat;
double *ptr;
long NN;
long k;
double *dPtr;
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
		Y[0] = mxCreateDoubleMatrix( _tmcGetM(mat) , _tmcGetN(mat) ,_tmcHasIm(mat)? mxCOMPLEX : mxREAL ) ; 
		dPtr = mxGetPr( Y[0] ) ;
			for (k=0;k<tmcNumElem(mat);k++)
			{
				dPtr[k]=mat->value.complx.rData[k];
			}
		if (_tmcHasIm(mat))
		{
			ptr=(double*)MYMALLOC(sizeof(double)*tmcNumElem(mat));
			stat=ReadProcessMemory(hProcess_copy,(void*)mat->value.complx.iData,ptr,NN,&NumberOfBytesRead);
			mat->value.complx.iData=ptr;

			dPtr = mxGetPi( Y[0] ) ;
			for (k=0;k<tmcNumElem(mat);k++)
			{
				dPtr[k]=mat->value.complx.iData[k];
			}
		
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
			stat= ReadRemoteMatrix(mat->value.StructDef.m_fields[k],Y,m_fields[k]);
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
			stat= ReadRemoteMatrix(mat->value.m_cells[k],Y,m_fields[k]);
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

void mexFunction(int nlhs, mxArray *plhs[], 
				 int nrhs, const mxArray *prhs[])
{    
double *dPtr;
HANDLE hWnd;
tmsMatrix mat;
mxArray *Y;

	if (nlhs >1 || nrhs != 1)
	{
		mexErrMsgTxt("Correct syntax: mat = gettmcmat( address )\n");
	}


	lpBaseAddress = (void *)(long)*mxGetPr( prhs[0] ) ;


tmcInitLib();

		hWnd=FindWindow("edit","tmcdebug");
		if (hWnd)
			GetWindowThreadProcessId(hWnd,&h_Other_id);
		else
		{
			mexErrMsgTxt("Cant connect to debugged appication. Start the application and try again!\n");
		}
		hProcess_copy = OpenProcess(PROCESS_ALL_ACCESS,FALSE,h_Other_id);
		ReadRemoteMatrix(&mat,&Y,lpBaseAddress);
		//tmcdisp(1,1,&mat);
		_tmcClearRegister(&mat);


	plhs[0] = Y; // mxCreateDoubleMatrix( 1 , 1 , mxREAL ) ; 
//	dPtr = mxGetPr( plhs[0] ) ;
//	dPtr[0]=(long)hProcess_copy;

} 
