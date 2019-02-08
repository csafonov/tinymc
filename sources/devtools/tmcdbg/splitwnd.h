// SplitWnd.h : implementation file
//
#ifndef _SplitWnd_h_
#define _SplitWnd_h_

#define PANE_COL_CALLSTACK	0
#define PANE_COL_VARLIST	1
#define PANE_COL_VARTREE	2
#define PANE_COL_VAREDIT	3
#define PANE_COL_MAX		(PANE_COL_VAREDIT+1)

class CxSplitterWnd : public CSplitterWnd
{
	// Construction
	public:
		CxSplitterWnd() {};
	virtual ~CxSplitterWnd() {};
  // Operations
	public:
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CxSplitterWnd)
	//}}AFX_VIRTUAL

	// Implementation
	CListCtrl* GetFncListCtrl()
	{
		return  & ((CListView*)GetPane(0,PANE_COL_CALLSTACK))->GetListCtrl( );
	}

	CListCtrl* GetMyListCtrl()
	{
		return  & ((CListView*)GetPane(0,PANE_COL_VARLIST))->GetListCtrl( );
	//	return  ((CTreeCtrl*)GetDlgItem(IDC_TREEMAT));
	}

	CTreeCtrl* GetMyTreeCtrl()
	{
		return  & ((CTreeView*)GetPane(0,PANE_COL_VARTREE))->GetTreeCtrl( );
	//	return  ((CTreeCtrl*)GetDlgItem(IDC_TREEMAT));
	}
	CEdit* GetMyEditCtrl()
	{
		return  & ((CEditView*)GetPane(0,PANE_COL_VAREDIT))->GetEditCtrl( );
		// return  this->GetDlgItem(IDC_EDIT_LOG);
	}
	tmsMatrix *GetItemMatrix(HTREEITEM ti)
	{
		return (tmsMatrix *)GetMyTreeCtrl()->GetItemData(ti);
	}
	CListView* GetFncListView()
	{
		return  (CListView*)GetPane(0,PANE_COL_CALLSTACK) ;
	}
	CListView* GetVarListView()
	{
		return  (CListView*)GetPane(0,PANE_COL_VARLIST) ;
	}

	CTreeView* GetVarTreeView()
	{
		return  (CTreeView*)GetPane(0,PANE_COL_VARTREE) ;
	}
	CEditView* GetVarEditView()
	{
		return  (CEditView*)GetPane(0,PANE_COL_VAREDIT) ;
	}

	int fncsID;
	int varsID;
	int tID;
	int eID;
	CFont TmcMatEditFont;

	void InitSplitter(CWnd *pParent,long pos1,long pos2,long pos3,long dx,long dy,long y0);
	int OnSelectMyTreeNode(HTREEITEM tvi);
	int OnSelectFnc(int sel);
	void GetLocalVars4Fnc(LPCTSTR wstr,void* FncAddr);
	void ClearAllListMat(void);
	void ClearListMat(void);
	void ClearFncListMat(void);
	void GetCallStack(void);
	void DisplayMatTree(tmsMatrix *x,HTREEITEM ParentRoot,short fmt);
	void OnAddAddr(LPCTSTR m_Addr);
	void OnRefresh() ;

	CList<CMatRecord,CMatRecord&> all_list_mat;
	CList<CMatRecord,CMatRecord&> fnc_list_mat;
	CList<CMatRecord,CMatRecord&> list_mat;

	public:
	// These are the methods to be overridden
	virtual void StartTracking(int ht);
	virtual CWnd* GetActivePane(int* pRow = NULL, int* pCol = NULL);
	virtual void SetActivePane( int row, int col, CWnd* pWnd = NULL );
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult );
	virtual BOOL OnWndMsg( UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult );
	// Generated message map functions
	protected:
	//{{AFX_MSG(CxSplitterWnd)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif