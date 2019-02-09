#include <windows.h>
#include "tmc.h"

void tmcTestO(int nargout, int nargin,tmsMatrix *PropGain,tmsMatrix *IntGain,tmsMatrix *FreqLen,tmsMatrix *FreqHz,tmsMatrix *OL_Mag,tmsMatrix *OL_Ph,tmsMatrix *CL_Mag,tmsMatrix *CL_Ph,tmsMatrix *RespLen,tmsMatrix *RespTime,tmsMatrix *Resp
,tmsMatrix *R,tmsMatrix *L,tmsMatrix *Ts,tmsMatrix *Ovs) ;


void __stdcall calccurrentctrl(double *PropGain,double *IntGain,long *FreqLen,double *FreqHz,
							   double *OL_Mag,double *OL_Ph,double *CL_Mag,double *CL_Ph,
							   long *RespLen,double *RespTime,double *Resp,long MaxFreqLen,long MaxTimeLen,double R,double L,double Ts,double Ovs)
{

	
	unsigned long k;
	unsigned long len;
tmsMatrix *mPropGain	= tmcNewMatrix();
tmsMatrix *mIntGain		= tmcNewMatrix();
tmsMatrix *mFreqLen		= tmcNewMatrix();
tmsMatrix *mFreqHz		= tmcNewMatrix();
tmsMatrix *mOL_Mag		= tmcNewMatrix();
tmsMatrix *mOL_Ph		= tmcNewMatrix();
tmsMatrix *mCL_Mag		= tmcNewMatrix();
tmsMatrix *mCL_Ph		= tmcNewMatrix();
tmsMatrix *mRespLen		= tmcNewMatrix();
tmsMatrix *mRespTime	= tmcNewMatrix();
tmsMatrix *mResp		= tmcNewMatrix();
tmsMatrix *mR			= tmcNewMatrix();
tmsMatrix *mL			= tmcNewMatrix();
tmsMatrix *mTs			= tmcNewMatrix();
tmsMatrix *mOvs			= tmcNewMatrix();

// to create input matrix use: _tmcCreateMatrix(tmsMatrix *res,long M,long N,short bHasImagine)

tmcScalar(mR,R);
tmcScalar(mL,L);
tmcScalar(mTs,Ts);
tmcScalar(mOvs,Ovs);


tmcTestO(11, 4, // nargout,nargin
		 mPropGain,mIntGain,mFreqLen,mFreqHz,mOL_Mag,mOL_Ph,mCL_Mag,mCL_Ph,mRespLen,mRespTime,mResp, // [outputs]
 mR,mL,mTs,mOvs) ; // [inputs]

	// copy outputs
	len =  tmcNumElem ( mFreqHz );
	if (len == 0)
	{
		return;// no solutions, skip it.
	}

	if (MaxFreqLen < (long)len)
	{
			len = MaxFreqLen;
	}
	*FreqLen = len;
	for (k=0;k<len;k++)
	{
		FreqHz[k]=mFreqHz->value.complx.rData[k];
		OL_Mag[k]= mOL_Mag->value.complx.rData[k];
		OL_Ph[k] = mOL_Ph->value.complx.rData[k];
		CL_Mag[k]= mCL_Mag->value.complx.rData[k];
		CL_Ph[k] = mCL_Ph->value.complx.rData[k];
	}
	len =  tmcNumElem ( mRespTime );
	if (MaxTimeLen < (long)len)
	{
			len = MaxTimeLen;
	}
	*RespLen = len;
	for (k=0;k<len;k++)
	{
		RespTime[k]=mRespTime->value.complx.rData[k];
		Resp[k]    =mResp->value.complx.rData[k];
	}
	

PropGain[0]=mPropGain->value.complx.rData[0];
IntGain[0]=mIntGain->value.complx.rData[0];


tmcFreeLocalVar(mOvs);
tmcFreeLocalVar(mTs);
tmcFreeLocalVar(mL);
tmcFreeLocalVar(mR);
tmcFreeLocalVar(mResp);
tmcFreeLocalVar(mRespTime);
tmcFreeLocalVar(mRespLen);
tmcFreeLocalVar(mCL_Ph);
tmcFreeLocalVar(mCL_Mag);
tmcFreeLocalVar(mOL_Ph);
tmcFreeLocalVar(mOL_Mag);
tmcFreeLocalVar(mFreqHz);
tmcFreeLocalVar(mFreqLen);
tmcFreeLocalVar(mIntGain);
tmcFreeLocalVar(mPropGain);

}


///////////////////
extern   const struct CInit_funcs_table Init_funcs_table ;
void __stdcall InitDLL(void)
{
	//tmcInitLib(&Init_funcs_table);
}
void __stdcall UnInitDLL(void)
{
	//tmcFreeLib();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
				tmcInitLib(&Init_funcs_table);
   break;

	case DLL_THREAD_ATTACH:
	break;

	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		tmcFreeLib();
	break;

	//	break;
	}
    return TRUE;
}


