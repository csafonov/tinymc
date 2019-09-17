	// SplitWnd.cpp : implementation of watch viewer
	// 
/*
   Copyright (C) Shmuel Safonov 2009-2012 All rights reserved.
   Any usage of this file must be according to TMC License.
*/
	#include "stdafx.h"

	#include <afxcview.h>


	#include "tmcdbgW.h"
	#include "SplitWnd.h" 
	#include "tmcdbgWDlg.h"


#include "tmcstringhash.h"
	#include "tmcdebugger.h"


	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif 
	 
	// HitTest return values (values and spacing between values is important)
	// Had to adopt this because it has module scope 
	enum HitTestValue
	{
		noHit = 0,
		vSplitterBox = 1,
		hSplitterBox = 2,
		bothSplitterBox = 3, // just for keyboard
		vSplitterBar1 = 101,
		vSplitterBar15 = 115,
		hSplitterBar1 = 201,
		hSplitterBar15 = 215,
		splitterIntersection1 = 301,
		splitterIntersection225 = 525
	}; 
	 
	/////////////////////////////////////////////////////////////////////////////
	// CxSplitterWnd 
	 
	BEGIN_MESSAGE_MAP(CxSplitterWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CxSplitterWnd)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	END_MESSAGE_MAP() 

///////////////////
class CTmcMatView : public CEditView
{
	DECLARE_DYNCREATE(CTmcMatView)
// Construction
	CTmcMatView();
	BOOL PreCreateWindow(CREATESTRUCT& cs);

// Attributes
public:
	// static init/term...
	//static void Initialize();
	//static void Terminate();

	//CTmcMatDoc* GetDocument();

// Operations
public:

	// Printing...
	//virtual void OnPrint(CDC* pDC, CPrintInfo *pInfo);
	//virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//virtual void OnScrollTo(CDC* pDC, CPrintInfo* pInfo, POINT point);

	// Buffer access...
	//LPCTSTR LockBuffer() const
	//	{ return CEditView::LockBuffer(); }
	//void UnlockBuffer() const
	//	{ CEditView::UnlockBuffer(); }

// Implementation
public:
	unsigned long m_BkColor;
	unsigned long m_FontColor;
	CBrush m_BkBrush;
//	CTmcMatDoc * m_pTmcMatDocument;

	//BOOL IsUpdatePending() {return (m_uTimerID != NULL);}

//#ifdef _DEBUG
//	virtual void AssertValid() const;
//	virtual void Dump(CDumpContext& dc) const;
//#endif

protected:
	//UINT_PTR m_uTimerID; // ==0 when no outstanding

	//static LOGFONT NEAR m_lfDefFont;
	//static LOGFONT NEAR m_lfDefFontOld;
	//CFont m_font;

	//static LOGFONT NEAR m_lfDefPrintFont;
	//static LOGFONT NEAR m_lfDefPrintFontOld;
	//CFont m_fontPrint;

	//static UINT m_nDefTabStops;
	//static UINT m_nDefTabStopsOld;
	//static BOOL m_bDefWordWrap;
	//static BOOL m_bDefWordWrapOld;

	//UINT m_nPreviewPage;
	//CTime m_timeHeader;
	//CTime m_timeFooter;

	//{{AFX_MSG(CPadView)
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnChooseFont();
	//afx_msg void OnWordWrap();
	//afx_msg void OnUpdateWordWrap(CCmdUI* pCmdUI);
	//afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnChoosePrintFont();
	//afx_msg void OnMirrorDisplayFont();
	//afx_msg void OnUpdateMirrorDisplayFont(CCmdUI* pCmdUI);
	//afx_msg void OnUpdateChoosePrintFont(CCmdUI* pCmdUI);
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditChange();
	//afx_msg void OnEditCopy();
	//afx_msg void OnEditCut();
	//afx_msg void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	//afx_msg void OnSetTabStops();
	//afx_msg HBRUSH OnCtlColor(CDC* pDC, UINT  nCtlColor);
	DECLARE_MESSAGE_MAP()
};

IMPLEMENT_DYNCREATE(CTmcMatView, CEditView)

BEGIN_MESSAGE_MAP(CTmcMatView, CEditView)
	//{{AFX_MSG_MAP(CPadView)
	//ON_WM_CREATE()
	//ON_COMMAND(ID_CHOOSE_FONT, OnChooseFont)
	//ON_COMMAND(ID_WORD_WRAP, OnWordWrap)
	//ON_UPDATE_COMMAND_UI(ID_WORD_WRAP, OnUpdateWordWrap)
	//ON_WM_RBUTTONDOWN()
	//ON_COMMAND(ID_CHOOSE_PRINT_FONT, OnChoosePrintFont)
	//ON_COMMAND(ID_MIRROR_DISPLAY_FONT, OnMirrorDisplayFont)
	//ON_UPDATE_COMMAND_UI(ID_MIRROR_DISPLAY_FONT, OnUpdateMirrorDisplayFont)
	//ON_UPDATE_COMMAND_UI(ID_CHOOSE_PRINT_FONT, OnUpdateChoosePrintFont)
	//ON_WM_SIZE()
	ON_CONTROL_REFLECT(EN_CHANGE, OnEditChange)
	//ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	//ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	//ON_WM_TIMER()
	//}}AFX_MSG_MAP
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	//ON_COMMAND(ID_SET_TABSTOPS, OnSetTabStops)
	//ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

CTmcMatView::CTmcMatView()
{
	  m_BkColor = RGB(255,0,0);
	 m_FontColor= RGB(0,255,0);
	 m_BkBrush.CreateSolidBrush(RGB(255,255,255));
//	m_pTmcMatDocument = new CTmcMatDoc();

}
//CTmcMatDoc* CTmcMatView::GetDocument()
//{
//		return (CTmcMatDoc*)m_pTmcMatDocument;
//}

//afx_msg HBRUSH CTmcMatView::OnCtlColor(CDC* pDC, UINT  nCtlColor )
//{//WM_CTLCOLOR
// m_BkColor is whatever background color you want to change to. You will make changes to m_BkColor by the time Windows 
// repaints
//pDC->SetBkColor(m_BkColor);
// m_FontColor is the text color
//pDC->SetTextColor(m_FontColor);
// Return a handle to a CBrush. m_BkBrush is a local variable initialized to RGB(255, 255, 255)
//return static_cast<HBRUSH>(m_BkBrush.GetSafeHandle());
//}


afx_msg void CTmcMatView::OnEditChange()
{
	return ; // do nothing - disable change in order to avoid exception
}

BOOL CTmcMatView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CEditView::PreCreateWindow(cs))
		return FALSE;

	//if (m_bDefWordWrap)
	//	cs.style &= ~(WS_HSCROLL|ES_AUTOHSCROLL);
//	cs.style |= ES_READONLY;
		 

	return TRUE;
}

///////////////////

	CWnd* CxSplitterWnd::GetActivePane(int* pRow, int* pCol)
	{
		ASSERT_VALID(this); 
		CWnd* pView = GetFocus();
		// make sure the pane is a child pane of the splitter
		if (pView != NULL && !IsChildPane(pView, pRow, pCol))
		pView = NULL; 
		return pView;
	} 
	 
	void CxSplitterWnd::SetActivePane( int row, int col, CWnd* pWnd)
	{
		// set the focus to the pane
		CWnd* pPane = pWnd == NULL ? GetPane(row, col) : pWnd;
		pPane->SetFocus();
	} 
	 
	void CxSplitterWnd::StartTracking(int ht)
	{
	ASSERT_VALID(this);
		if (ht == noHit)
			return; 
		// GetHitRect will restrict 'm_rectLimit' as appropriate
		GetInsideRect(m_rectLimit); 
		if (ht >= splitterIntersection1 && ht <= splitterIntersection225)
		{
			// split two directions (two tracking rectangles)
			int row = (ht - splitterIntersection1) / 15;
			int col = (ht - splitterIntersection1) % 15; 
			GetHitRect(row + vSplitterBar1, m_rectTracker);
			int yTrackOffset = m_ptTrackOffset.y;
			m_bTracking2 = TRUE;
			GetHitRect(col + hSplitterBar1, m_rectTracker2);
			m_ptTrackOffset.y = yTrackOffset;
		}
		else if (ht == bothSplitterBox)
		{
			// hit on splitter boxes (for keyboard)
			GetHitRect(vSplitterBox, m_rectTracker);
			int yTrackOffset = m_ptTrackOffset.y;
			m_bTracking2 = TRUE;
			GetHitRect(hSplitterBox, m_rectTracker2);
			m_ptTrackOffset.y = yTrackOffset; 
			// center it
			m_rectTracker.OffsetRect(0, m_rectLimit.Height()/2);
			m_rectTracker2.OffsetRect(m_rectLimit.Width()/2, 0);
		}
		else
		{
			// only hit one bar
			GetHitRect(ht, m_rectTracker);
		} 
	 
		// steal focus and capture
		SetCapture();
		SetFocus(); 
		// make sure no updates are pending
		RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_UPDATENOW); 
		// set tracking state and appropriate cursor
		m_bTracking = TRUE;
		OnInvertTracker(m_rectTracker);
		if (m_bTracking2)
		OnInvertTracker(m_rectTracker2);
		m_htTrack = ht;
		SetSplitCursor(ht);
	} 
	 
	/////////////////////////////////////////////////////////////////////////////
	// CSplitterWnd command routing 
	BOOL CxSplitterWnd::OnCommand(WPARAM wParam, LPARAM lParam)
	{
		// not needed - catched at OnEditChange
		//if (LOWORD(wParam)==eID)
		//{
		//	if (HIWORD(wParam)==EN_CHANGE)
		//	{
		//		//	return TRUE; // do nothing
		//	}
		//}
		
		if (CWnd::OnCommand(wParam, lParam))
		return TRUE; 
		// route commands to the splitter to the parent frame window
		return GetParent()->SendMessage(WM_COMMAND, wParam, lParam);
	} 
	 int hehr;
	BOOL CxSplitterWnd::OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult )
	{
	NMHDR *ptn;

		if ((int)wParam== this->tID )
		{
			
				ptn = (NMHDR *)lParam;
				if (ptn->code == NM_DBLCLK )// NM_CLICK)
				{
					OnSelectMyTreeNode(NULL);
					* pResult = 0;
					return TRUE;
				}
				if (ptn->code == TVN_SELCHANGED )
				{
					HTREEITEM tvi = ((LPNM_TREEVIEW)ptn)->itemNew.hItem;
					OnSelectMyTreeNode(tvi);
					* pResult = 0;
					return TRUE;
				}


		}
		else if ((int)wParam== this->eID )
		{
				ptn = (NMHDR *)lParam;
				if (ptn->code == WM_CTLCOLOR )
				{
hehr=3;
				}
		}
		else if ((int)wParam==fncsID)
		{
				ptn = (NMHDR *)lParam;
				//if (ptn->code == NM_DBLCLK )// NM_CLICK)
				//{
				//	//OnSelectMyTreeNode(NULL);
				//	* pResult = 0;
				//	return TRUE;
				//}
				if (ptn->code == NM_CLICK || ptn->code == NM_DBLCLK)
				{
					int sel = ((LPNM_LISTVIEW)ptn)->iItem;
					//OnSelectMyTreeNode(tvi);
					OnSelectFnc(sel);
					* pResult = 0;
					return TRUE;
				}



		}

		
		if (CWnd::OnNotify(wParam, lParam, pResult))
		return TRUE; 
		// route commands to the splitter to the parent frame window
		*pResult = GetParent()->SendMessage(WM_NOTIFY, wParam, lParam);
		return TRUE;
	} 
	 
	BOOL CxSplitterWnd::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
	{ 
		// The code line below is necessary if using CxSplitterWnd in a regular dll
		// AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
		return CWnd::OnWndMsg(message, wParam, lParam, pResult);
	}


	LPTSTR store_wchar_t_const_string(LPCTSTR wstr)
	{
		long namelen = wcslen(wstr)+1;
		LPTSTR wstr_ =(LPTSTR) malloc( sizeof(wchar_t)*(namelen)   );
		memcpy(wstr_,wstr,sizeof(wchar_t)*(namelen));
		return wstr_;// to be free()
	}

	int CxSplitterWnd::OnSelectMyTreeNode(HTREEITEM tvi)
	{
	HTREEITEM ti;
	LPARAM x;


	if (tvi==NULL)
		ti = GetMyTreeCtrl()->GetSelectedItem();
	else
		ti = tvi;
	//ti = ((CTreeCtrl*)GetDlgItem(IDC_TREEMAT))->HitTest(NULL);

	//NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	//ti  = pNMTreeView->itemNew.hItem;
	if (ti != NULL)
	{
		x = (LPARAM)GetItemMatrix(ti);
		if (x != NULL)
		{
			PrintMatrixLocal((tmsMatrix *)(void*)x,1);
			//char *out=get_out();
			//GetMyEditCtrl()->SetWindowText(out);
			buffer_to_uni();
			GetMyEditCtrl()->SetWindowText(uni_get_out());

		}
	}

			return 0;
	}

	int CxSplitterWnd::OnSelectFnc(int sel)
	{

		CString w_str = this->GetFncListCtrl()->GetItemText(sel,0);
	    LPCTSTR wstr = (LPCTSTR)w_str;
		GetLocalVars4Fnc(wstr,(void *)GetFncListCtrl()->GetItemData(sel)); 
		return 0;
	}

	void CxSplitterWnd::GetLocalVars4Fnc(LPCTSTR wstr,void* FncAddr)
{
	// get local vars for selected functions from stack
	if (ConnectTmc()<0)
		return;

	GetMyListCtrl()->DeleteAllItems();
	ClearAllListMat();

	long k,k0;
	long len = remote_frame_length();

void *_lpBaseAddress;
HTREEITEM VarRoot;

tmsMatrix *ptrMat;
void *remFncAddr;


	GetMyTreeCtrl()->DeleteAllItems();

	// first find the function
	for (k=0;k<len;k++)
	{
		remFncAddr = remote_frame_addr_at(k);
		if ( remote_etype_at(k)==TMC_DBG_ESTACK_FUNC && remFncAddr==FncAddr)
		{
			if (wcscmp(wstr,string2uni(remote_frame_name_at(k)))==0)
			{
				k0=k+1;
				break;
			}
		}
	}


	for (k=k0;k<len;k++)
	{
		if ( remote_etype_at(k)==TMC_DBG_ESTACK_FUNC     )
		{
			break; // done
		}

		if ( remote_etype_at(k)==TMC_DBG_ESTACK_VAR)
		{
		LPCTSTR wstr		 = string2uni(remote_frame_name_at(k));
		//LPTSTR wstr_ =		   store_wchar_t_const_string(wstr);
		void    *BaseAddress = remote_frame_addr_at(k);

		CMatRecord mr(NULL,wstr,BaseAddress   );
		all_list_mat.AddTail(mr);

		GetMyListCtrl()->InsertItem(LVIF_TEXT|LVIF_PARAM,0,wstr,0,0,0,0L);


		_lpBaseAddress = BaseAddress;
		
		ptrMat = tmcNewMatrix();
		//_tmcClearRegister(ptrMat);
		CMatRecord mr2(ptrMat,wstr,_lpBaseAddress   );
		list_mat.AddTail(mr2);
		LoadExternalMatrix(ptrMat,_lpBaseAddress);
		PrintMatrixLocal(ptrMat,1);

				buffer_to_uni();
				GetMyEditCtrl()->SetWindowText(uni_get_out());
		VarRoot=GetMyTreeCtrl()->InsertItem(TVIF_TEXT|TVIF_PARAM,wstr,0,0,0,0,(LPARAM)(void*)ptrMat,TVI_ROOT,TVI_LAST);
		DisplayMatTree(ptrMat,VarRoot,0);
		GetMyTreeCtrl()->Expand(VarRoot,TVE_EXPAND);
		GetMyTreeCtrl()->Select(VarRoot,TVGN_CARET);
		}
	}

//	GetMyListCtrl()->InsertItem(LVIF_TEXT|LVIF_PARAM,0,L"Sys",0,0,0,0L);
//	int InsertItem( UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask, int nImage, LPARAM lParam );
}

void CxSplitterWnd::ClearAllListMat(void)
{
	while (!all_list_mat.IsEmpty())
	{
		free(all_list_mat.GetTail().mname);
		all_list_mat.RemoveTail();
	}
	GetMyListCtrl()->DeleteAllItems();
}
void CxSplitterWnd::DisplayMatTree(tmsMatrix *x,HTREEITEM ParentRoot,short fmt)
{
	long m,n;
	short k;
	HTREEITEM VarRoot;
	HTREEITEM VarRoot2;
	tmsMatrix *tempM;

	long M = _tmcGetM(x);
	long N = _tmcGetN(x);
//int lenout;
wchar_t buf[100];

	if (x->m_desc.m_type == TYPE_CELL_ARRAY)
	{
		//lenout=sprintf(out,"CellArray(%d,%d) ={\r\n",M,N);out+=lenout;
		for (m=0;m<M;m++)
		{
			for (n=0;n<N;n++)
			{
				tempM = x->value.m_cells[m+n*M];
				swprintf(buf,L"{%d,%d} [%d x %d]",m,n,_tmcGetM(tempM),_tmcGetN(tempM));
				VarRoot=GetMyTreeCtrl()->InsertItem(TVIF_TEXT|TVIF_PARAM,buf,0,0,0,0,(LPARAM)(void*)tempM,ParentRoot,TVI_LAST);
				//lenout=sprintf(out,"[%d,%d]=",m+1,n+1);out+=lenout;
				DisplayMatTree(tempM,VarRoot  ,fmt);
				//lenout=sprintf(out,";\r\n");out+=lenout;
			}
		}
		GetMyTreeCtrl()->Expand(ParentRoot,TVE_EXPAND);

		//lenout=sprintf(out,"};\r\n");out+=lenout;
	return ;
	}

	if (x->m_desc.m_type == TYPE_STRUCT)
	{
		//lenout=sprintf(out,"Structure(%d,%d) =\r\n",M,N);out+=lenout;
		for (m=0;m<M;m++)
		{
			for (n=0;n<N;n++)
			{
				swprintf(buf,L"(%d,%d)",m,n);
				VarRoot=GetMyTreeCtrl()->InsertItem(TVIF_TEXT|TVIF_PARAM,buf,0,0,0,0,(LPARAM)(void*)x,ParentRoot,TVI_LAST);
				//lenout=sprintf(out,"[%d,%d]=",m+1,n+1);out+=lenout;
				for (k=0;k<_tmcGetNf(x);k++)
				{
					//lenout=sprintf(out,"\t field %s=\r\n",hcode2string(x->value.StructDef.hcFields[k]));out+=lenout;
					tempM = x->value.StructDef.m_fields[(m+n*M)+k*M*N];
					swprintf(buf,L"%s [%d x %d]",string2uni(hcode2string_remote(x->value.StructDef.hcFields[k])),_tmcGetM(tempM),_tmcGetN(tempM));
					VarRoot2=GetMyTreeCtrl()->InsertItem(
					TVIF_TEXT|TVIF_PARAM,buf,0,0,0,0,(LPARAM)(void*)tempM,VarRoot,TVI_LAST);	
					DisplayMatTree(tempM,VarRoot2,fmt);
				    //lenout=sprintf(out,";\r\n");out+=lenout;
				}
				GetMyTreeCtrl()->Expand(VarRoot,TVE_EXPAND);

			}
		}
		GetMyTreeCtrl()->Expand(ParentRoot,TVE_EXPAND);

		//lenout=sprintf(out,"END Structure;\r\n");out+=lenout;
		return;
	}
	/*
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
			lenout=sprintf(out,"%g,\t",x->m_rData[n*M+m]);out+=lenout;
			}
			else
			{
			if(x->m_iData[n*M+m])
			{lenout=sprintf(out,"%g + \t%gi,\t",x->m_rData[n*M+m],x->m_iData[n*M+m]);out+=lenout;}
			else
			{lenout=sprintf(out,"%g\t   ,\t",x->m_rData[n*M+m]);out+=lenout;}
			}

		}
		lenout=sprintf(out,";\r\n");out+=lenout;
	}
	if ( bVerb || x->m_desc.m_type != TYPE_STRING)
	{lenout=sprintf(out,"];\r\n");out+=lenout;}
	else
	{lenout=sprintf(out,"\r\n");out+=lenout;}
	*/
}
void CxSplitterWnd::OnAddAddr( LPCTSTR m_Addr )
{// add matrix to TreeView
	// TODO: Add your control notification handler code here
void *_lpBaseAddress;
//char *out;
HTREEITEM VarRoot;

tmsMatrix *ptrMat;


/*
long ind;
long M=4;
long N=3;
tmsMatrix *mat = tmcNewMatrix();
		_tmcCreateCellArray(mat,M,N);
		for (ind=0;ind<M*N;ind++)
		{
			mat->value.m_cells[ind] = tmcNewMatrix();
		//	_tmcCreateMatrix(mat->value.m_cells[ind],6,2,tmcREAL);
		}
		_tmcCreateMatrix(mat->value.m_cells[0],6,2,tmcREAL);
		_tmcCreateCellArray(mat->value.m_cells[1],2,3);
		for (ind=0;ind<2*3;ind++)
		{
				mat->value.m_cells[1]->value.m_cells[ind] = tmcNewMatrix();
		}
		_tmcCreateStruct(mat->value.m_cells[2],1,1,(short)(3),NULL);

		tmcAssign(mat->value.m_cells[2]->value.StructDef.m_fields[0],mat->value.m_cells[1]);
		mat->value.m_cells[2]->value.StructDef.hcFields[0]= 0x6aa90000;//dstring2hcode(field_name->m_rData,tmcNumElem(field_name));

		tmcAssign(mat->value.m_cells[2]->value.StructDef.m_fields[1],mat->value.m_cells[1]);
		mat->value.m_cells[2]->value.StructDef.hcFields[1]= 0x97910000;//dstring2hcode(field_name->m_rData,tmcNumElem(field_name));

		tmcAssign(mat->value.m_cells[2]->value.StructDef.m_fields[2],mat->value.m_cells[1]);
		mat->value.m_cells[2]->value.StructDef.hcFields[2]= 0x00770000;//dstring2hcode(field_name->m_rData,tmcNumElem(field_name));

*/

//	((CTreeCtrl*)GetDlgItem(IDC_TREEMAT))->DeleteAllItems();
//	VarRoot=((CTreeCtrl*)GetDlgItem(IDC_TREEMAT))->InsertItem(TVIF_TEXT|TVIF_PARAM,"M",0,0,0,0,(LPARAM)(void*)mat,TVI_ROOT,TVI_LAST);
////InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter );


//	DisplayMatTree(mat,VarRoot,0);
//	((CTreeCtrl*)GetDlgItem(IDC_TREEMAT))->Expand(VarRoot,TVE_EXPAND);

//	GetMyEditCtrl()->SendMessage(WM_CTLCOLOR,0,0);


	if (ConnectTmc()<0)
		return;

	swscanf((LPCTSTR)m_Addr,L"%x",(unsigned int*)&_lpBaseAddress);
	
	ptrMat = tmcNewMatrix();
	//_tmcClearRegister(ptrMat);
	CMatRecord mr(ptrMat,(LPCTSTR)m_Addr,_lpBaseAddress   );
	list_mat.AddTail(mr);


	LoadExternalMatrix(ptrMat,_lpBaseAddress);
	PrintMatrixLocal(ptrMat,1);

	//PrintMatrix(_lpBaseAddress);
	//out=get_out();
	//GetMyEditCtrl()->SetWindowText(out);
	
			buffer_to_uni();
			GetMyEditCtrl()->SetWindowText(uni_get_out());

//add:	GetMyTreeCtrl()->DeleteAllItems();
	VarRoot=GetMyTreeCtrl()->InsertItem(TVIF_TEXT|TVIF_PARAM,(LPCTSTR)m_Addr,0,0,0,0,(LPARAM)(void*)ptrMat,TVI_ROOT,TVI_LAST);

//	CTreeCtrl *t =& ((CTreeView*)m_wndSplitter.GetPane(0,PANE_COL_VARTREE))->GetTreeCtrl( );
//	t->DeleteAllItems();
//	VarRoot=t->InsertItem(TVIF_TEXT|TVIF_PARAM,"M",0,0,0,0,(LPARAM)(void*)&mat0,TVI_ROOT,TVI_LAST);


	
	
	DisplayMatTree(ptrMat,VarRoot,0);
	GetMyTreeCtrl()->Expand(VarRoot,TVE_EXPAND);
	GetMyTreeCtrl()->Select(VarRoot,TVGN_CARET);

	//_tmcClearRegister(&mat0);
}

void CxSplitterWnd::ClearListMat(void)
{
	while (!list_mat.IsEmpty())
	{
		_tmcClearRegister(list_mat.GetTail().m);
		tmcFreeLocalVar(list_mat.GetTail().m);
		free(list_mat.GetTail().mname);


		list_mat.RemoveTail();
	}
	GetMyTreeCtrl()->DeleteAllItems();
}

void CxSplitterWnd::OnRefresh() 
{
	// TODO: Add your control notification handler code here
// 1. must remember selection

	tmsMatrix *ptrMat ;
//char *out;
void *m_lpBaseAddress;
const wchar_t  *mname;
HTREEITEM VarRoot;
HTREEITEM OldSelection;
tmsMatrix *ptrSelectedMat =NULL;
CMatRecord mr;

	
	OldSelection = GetMyTreeCtrl()->GetSelectedItem();
	if (OldSelection != NULL)
	{
		ptrSelectedMat = GetItemMatrix(OldSelection);
	}

	GetMyTreeCtrl()->DeleteAllItems();

	for( POSITION pos = list_mat.GetHeadPosition(); pos != NULL; )
    {
		mr = list_mat.GetNext(pos); // get reference

		ptrMat				= mr.m;
		mname				= mr.mname;
		m_lpBaseAddress		= mr.remoteAddress;

		_tmcClearRegister(ptrMat);
		LoadExternalMatrix(ptrMat,m_lpBaseAddress);
		PrintMatrixLocal(ptrMat,1);
		//out=get_out();
		//GetMyEditCtrl()->SetWindowText(out);
			buffer_to_uni();
			GetMyEditCtrl()->SetWindowText(uni_get_out());

		VarRoot=GetMyTreeCtrl()->InsertItem(TVIF_TEXT|TVIF_PARAM,mname,0,0,0,0,(LPARAM)(void*)ptrMat,TVI_ROOT,TVI_LAST);
		DisplayMatTree(ptrMat,VarRoot,0);
		if (ptrMat != ptrSelectedMat)
		{
		GetMyTreeCtrl()->Expand(VarRoot,TVE_COLLAPSE);
		}
		else
		{// HAZARD: refresh also the edit box after that
		GetMyTreeCtrl()->Expand(VarRoot,TVE_EXPAND);
		GetMyTreeCtrl()->Select(VarRoot,TVGN_FIRSTVISIBLE);
		GetMyTreeCtrl()->Select(VarRoot,TVGN_CARET);
		}
    }
}
void CxSplitterWnd::GetCallStack()
{
	// get stack
	if (ConnectTmc()<0)
		return;

	//GetFncListCtrl()->DeleteAllItems();
	ClearFncListMat();

	long k;
	long len = remote_frame_length();

	for (k=0;k<len;k++)
	{
		if ( remote_etype_at(k)==TMC_DBG_ESTACK_FUNC)
		{
		LPCTSTR wstr		 = string2uni(remote_frame_name_at(k));
		//LPTSTR wstr_ =		   store_wchar_t_const_string(wstr);
		void    *BaseAddress = remote_frame_addr_at(k);

		CMatRecord mr(NULL,wstr,BaseAddress   );
		fnc_list_mat.AddTail(mr);

		GetFncListCtrl()->InsertItem(LVIF_TEXT|LVIF_PARAM,0,wstr,0,0,0,(LPARAM)BaseAddress);
		}
	}
	if (len>0)
		GetFncListCtrl()->SetSelectionMark(0);

}
void CxSplitterWnd::ClearFncListMat(void)
{
	while (!fnc_list_mat.IsEmpty())
	{
		free(fnc_list_mat.GetTail().mname);
		fnc_list_mat.RemoveTail();
	}
	GetFncListCtrl()->DeleteAllItems();
}
void CxSplitterWnd::InitSplitter(CWnd *pParent,long pos1,long pos2,long pos3,long dx,long dy,long y0)
{
	TmcMatEditFont.CreateFont(15,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,PROOF_QUALITY,
		VARIABLE_PITCH |FF_SWISS,_T("Arial"));


		CreateStatic(pParent, 1, PANE_COL_MAX);
		CreateView(0,PANE_COL_CALLSTACK,RUNTIME_CLASS(CListView), CSize(pos1,dy), NULL); 
		CreateView(0,PANE_COL_VARLIST,RUNTIME_CLASS(CListView), CSize(pos2,dy), NULL); 
		CreateView(0,PANE_COL_VARTREE,RUNTIME_CLASS(CTreeView), CSize(pos3,dy), NULL);
		CreateView(0,PANE_COL_VAREDIT,RUNTIME_CLASS(CTmcMatView), CSize(0,0), NULL); 
	 
		CRect rect(0,y0,dx,dy);
		MoveWindow(&rect);

		//CRect trect(0,0,wrect.right/2,wrect.right/2);
		//GetMyTreeCtrl()->MoveWindow( &trect  );
		
		GetMyTreeCtrl()->ModifyStyle(0,TVS_HASLINES);
		GetMyTreeCtrl()->ModifyStyle(0,TVS_HASBUTTONS);
		GetMyTreeCtrl()->ModifyStyle(0,TVS_LINESATROOT|TVS_SHOWSELALWAYS);
		//idT = GetMyTreeCtrl()->GetDlgCtrlID();
		tID =  GetMyTreeCtrl()->GetDlgCtrlID();

		//GetMyEditCtrl()->ModifyStyle(0,ES_READONLY|ES_PASSWORD);
		//GetMyEditCtrl()->SendMessage(EM_SETREADONLY,TRUE,0);
		eID =  GetMyEditCtrl()->GetDlgCtrlID();
		GetMyListCtrl()->ModifyStyle(0,LVS_LIST|LVS_SHOWSELALWAYS);
		varsID = GetMyListCtrl()->GetDlgCtrlID();

		//((CEditView*)m_wndSplitter.GetPane(0,PANE_COL_VAREDIT))->SetBkColor(RGB(256,0,0));

		((CTmcMatView*)GetVarEditView())->SetParent(this);
		((CTmcMatView*)GetVarEditView())->SetFont(&TmcMatEditFont);

		GetFncListCtrl()->ModifyStyle(0,LVS_LIST|LVS_SHOWSELALWAYS);
		fncsID =  GetFncListCtrl()->GetDlgCtrlID();

		//int cxCur,cxMin;
		//m_wndSplitter.GetColumnInfo(0,cxCur,cxMin);
		//	m_wndSplitter.SetColumnInfo(0,wrect.right/4,cxMin);
		//GetMyListCtrl()->MoveWindow(&rect);


		//GetMyEditCtrl()->SendMessage(WM_CTLCOLOR,0,0);
		//GetMyEditCtrl()->SetParent(m_wndSplitter);

//	CDocTemplate* pDocTemplate;
//	pDocTemplate = new CMultiDocTemplate(IDR_TEXTTYPE,
//		RUNTIME_CLASS(CPadDoc),
//		RUNTIME_CLASS(CPadFrame),
//		RUNTIME_CLASS(CPadView));

		//|TVS_HASLINES|TVS_LINESATROOT|TVS_SHOWSELALWAYS
	//	::SetWindowLong(((CWnd*)GetMyTreeCtrl())->GetSafeHwnd(),GWL_STYLE ,TVS_HASBUTTONS );


}