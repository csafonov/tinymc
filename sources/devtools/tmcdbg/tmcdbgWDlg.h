// tmcdbgWDlg.h : header file
//

#if !defined(AFX_TMCDBGWDLG_H__3BFC1DCF_EBCC_4871_90D4_065122F22E89__INCLUDED_)
#define AFX_TMCDBGWDLG_H__3BFC1DCF_EBCC_4871_90D4_065122F22E89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Afxtempl.h>


/////////////////////////////////////////////////////////////////////////////
// CTmcdbgWDlg dialog

class CTmcdbgWDlg : public CDialog
{
// Construction
public:
	CTmcdbgWDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTmcdbgWDlg)
	enum { IDD = IDD_TMCDBGW_DIALOG };
	CString	m_Addr;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTmcdbgWDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation

	CxSplitterWnd m_wndSplitter;
	
	CListCtrl* GetFncListCtrl()
	{
		return  & (m_wndSplitter.GetFncListView())->GetListCtrl( );
	}

	CListCtrl* GetMyListCtrl()
	{
		return  & (m_wndSplitter.GetVarListView())->GetListCtrl( );
	//	return  ((CTreeCtrl*)GetDlgItem(IDC_TREEMAT));
	}
	CTreeCtrl* GetMyTreeCtrl()
	{
		return  & (m_wndSplitter.GetVarTreeView())->GetTreeCtrl( );
	//	return  ((CTreeCtrl*)GetDlgItem(IDC_TREEMAT));
	}
	CEdit* GetMyEditCtrl()
	{
		return  & (m_wndSplitter.GetVarEditView())->GetEditCtrl( );
		// return  this->GetDlgItem(IDC_EDIT_LOG);
	
	}
	tmsMatrix *GetItemMatrix(HTREEITEM ti)
	{
		return (tmsMatrix *)GetMyTreeCtrl()->GetItemData(ti);
	}


public:
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTmcdbgWDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonPrint();
	afx_msg void OnButtonPlot();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCancelMode();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonImport();
	afx_msg void OnClose();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TMCDBGWDLG_H__3BFC1DCF_EBCC_4871_90D4_065122F22E89__INCLUDED_)
