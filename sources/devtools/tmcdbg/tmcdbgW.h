// tmcdbgW.h : main header file for the TMCDBGW application
//


#if !defined(AFX_TMCDBGW_H__F463CEE0_B1BA_4EA6_A2BD_A1F8F5FE60D9__INCLUDED_)
#define AFX_TMCDBGW_H__F463CEE0_B1BA_4EA6_A2BD_A1F8F5FE60D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

extern "C"
{
#include "tmc.h"
}
#include <Afxcview.h>

	class CMatRecord
	{
	public:
		tmsMatrix   *m;
		wchar_t * mname;
		void*		remoteAddress;
	public:
		CMatRecord::CMatRecord()
		{

		};
		CMatRecord::CMatRecord(tmsMatrix   *_m,const wchar_t* _mname,void* _remoteAddress)
		{
			m=_m;
			mname=(wchar_t*)malloc((sizeof(wchar_t))*(wcslen(_mname)+1));
			wcscpy(mname,_mname);
			mname[wcslen(_mname)]=0;
			remoteAddress=_remoteAddress;
		};
		CMatRecord::~CMatRecord()
		{
			//_tmcClearRegister(m);
			//tmcFreeLocalVar(m);
		};

	};



extern "C"
{
	char* get_out(void);
	LPCTSTR uni_get_out(void);
	void buffer_to_uni();
	const wchar_t * string2uni(const char *str);
	long remote_frame_length(void);
	LPCSTR  remote_frame_name_at(long k);
	void    * remote_frame_addr_at(long k);
	short  remote_etype_at(long k);
	const char * hcode2string_remote(STRINGCODE hcode);
}


extern "C"
{
	short ConnectTmc();
	short PrintMatrix(void *_lpBaseAddress);
	short PrintMatrixLocal(tmsMatrix *mat,short fmt);
	short InitTmc(void);
	short FreeTmc(void);
	void LoadExternalMatrix(tmsMatrix *mat,void *_lpBaseAddress);
}
/////////////////////////////////////////////////////////////////////////////
// CTmcdbgWApp:
// See tmcdbgW.cpp for the implementation of this class
//

class CTmcdbgWApp : public CWinApp
{
public:
	CTmcdbgWApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTmcdbgWApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTmcdbgWApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TMCDBGW_H__F463CEE0_B1BA_4EA6_A2BD_A1F8F5FE60D9__INCLUDED_)
