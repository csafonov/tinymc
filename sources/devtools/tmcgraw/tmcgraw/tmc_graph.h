// File: tmc_graph.h
// Interface for TMC graphic

#ifndef _tmc_graph_h_
#define _tmc_graph_h_


#define FRAME_DM	0.2f
#define FRAME_DN	0.2f
#define SP_DM	0.2f
#define SP_DN	0.2f

// File format:
// unsigned short numplots;
// unsigned short plottype;
// struct Ctmc_plot_inp  tmc_plot_inp[numplots];

//struct Ctmc_plot_inp
//{
//	struct Ctmc_plot_inp_hdr hdr;
//	double x[];
//	double y[];
//};

#define WM_TMC_FIGURE		(WM_USER+1) // wParam=h
#define WM_TMC_CLOSEFIGURE	(WM_USER+2) // wParam=h
#define WM_TMC_SUBPLOT		(WM_USER+3) // m=LOWORD(lParam),n=HIWORD(lParam),k=wParam
#define WM_TMC_PLOT			(WM_USER+4)

#pragma warning(disable : 4996) // unsafe



struct Ctmc_plot_inp_hdr
{
	unsigned long len;
	unsigned long mask; // 0: y only , 1: x present
	unsigned long plot_color;
};

// for reading data
struct Ctmc_karman
{
	struct Ctmc_plot_inp_hdr hdr;
	double *xx;
	double *yy;
	struct Ctmc_karman *next;
};

// karmans statistics
struct Ctmc_karmans_stat
{
	double max_y;
	double min_y;
	double max_x;
	double min_x;
};
struct Ctmc_karmans_metr
{
	double line_y0;
	double line_dy;
	double line_x0;
	double line_dx;
	short  line_y_num;
	short  line_x_num;
	double line_y2;
	double line_x2;
};
class Ctmc_karman_list
{
public:
 unsigned short numplots;
 unsigned short plottype;
 struct Ctmc_karman *first;
 struct Ctmc_karman *last;
 struct Ctmc_karmans_stat stat;
 struct Ctmc_karmans_metr metr;

 void ClearKarmanList(void);
 void ReadKarmanList(FILE *fp);
 void GetStatistics(void); // calculate statistics for mapping/scaling
 void GetMetrics(void);
	Ctmc_karman_list();

};


// Color:
union Utmcplotcolor
{
	unsigned long all;
	struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int	pointstyle : 4;
	int linestyle  : 2;
	int spare	   : 2;
	} color_style;
};

void _tmcStorePlot(FILE *fp,const double *x,const double *y,unsigned long colr,
				  unsigned long len, short bNew,unsigned short nPlots,unsigned short plottype);
/////////////////
struct CFigReshape
{
	int bDoNow;
	int width;
	int height;
};

class CtmcSubPlotArray;
class CtmcFigure
{
private:
	int ind; // user figure number
	//int win; // internal number
	class CtmcSubPlotArray  *m_SubPlotList;
	void InitFigGL (int width, int height);
	// work
	HWND  hWnd;
	HDC	  hDC;		// Private GDI Device Context
	HGLRC hRC;		// Permanent Rendering Context
	
	HCURSOR xcursor;

	int CreateWorkGLWindow(void);
	int  KillWorkGLWindow(void);
	wchar_t* m_title_w; 
	int m_bits;
	int m_update;
	struct CFigReshape m_ReshapeNow;
	GLvoid BuildFont(GLvoid);
	GLvoid KillFont(GLvoid);
public:
    int m_width;
	int m_height;
	char* m_title;
	int GetInd() const { return ind;}
	HWND GetWin() { return hWnd;};
	HDC  GetHDC() { return hDC;};
	HGLRC  GetHRC() { return hRC;};
	HCURSOR GetFigCursor(void) {return xcursor;};
	class CtmcSubPlotArray  *GetSubplots() {return m_SubPlotList;};
	void Create(void);
	void Select(void);
	void Close(void);
	void CreateSubPlots(unsigned short m,unsigned short n,unsigned short sel);
	void DisplaySubPlots(void); // display by GL
	class CtmcFigure *next;
	CtmcFigure(int ind);
	~CtmcFigure();
	void MarkUpdate() {  m_update++; };
	void ClearUpdate() { if(m_update>0) m_update--; };
	int  GetUpdate() {return m_update; };
	void SetCurrentWindow(void);
	void ReshapeWindow(void);
	void SetReshape(int _width, int _height)
		{ m_ReshapeNow.width=_width; m_ReshapeNow.height= _height; m_ReshapeNow.bDoNow=1;  };
	void DoneReshape(void) {m_ReshapeNow.bDoNow=0;};
	void WinExitFunc(void);
	void SetFigCursor(LPWSTR t);

};
class CtmcFigureList
{
private:
 int num_figures;
 class CtmcFigure *first;
 class CtmcFigure *last;
	class CtmcFigure *selected_fig;
	int max_fig_ind ; // for automatic indexing
public:
	void SetFigSelected(class CtmcFigure *ptr) {selected_fig=ptr;};
	class CtmcFigure * GetFigSelected(void) {return selected_fig;};

	void Destruct(); // destruct all the list
	class CtmcFigure *FindFigByInd(int ind,class CtmcFigure **prev=NULL);
	int SelectFig(int ind);   // create new figure and insert to list or select figure
	void Remove(int ind); // remove window figure
	CtmcFigureList() :num_figures(0),first(NULL),last(NULL),selected_fig(NULL),max_fig_ind(0) {   };
	int GetNumFigures() {return num_figures;};
	class CtmcFigure *GetFirstFig() {return first;};
	void DisplayFig(HWND hWnd);
	void DisplayFig(CtmcFigure *p);
public:
	void InitWorkAround(void);
	void FinishWorkAround(void);
	static void MsgLoop(void);
	class CtmcFigure *FindFigByHWND(HWND hWnd); // find figure by win32 window handle

};
class CtmcSubPlotArray;
class CtmcSubPlot
{
private:
	const CtmcSubPlotArray *m_parent;
	const int k;
	const float dn;
	const float dm;
	int m;
	int n;
	float offn;
	float offm;
private:
	Ctmc_karman_list karman_list;
	void PutGrid(void); // put grid by GL
	void PutFrame(void); // put frame bars by GL
public:
	void LoadKarmans(const char *fn);
	Ctmc_karman_list * GetKarmanList() { return &karman_list;};
	void DrawSubPlot(void) ;// GL
	CtmcSubPlot(CtmcSubPlotArray *m_parent,int _k);
	~CtmcSubPlot();
};
class CtmcSubPlotArray
{
private:
		unsigned short num_subplots;
		unsigned short m_dim;
		unsigned short n_dim;
		class CtmcSubPlot **m_subplots;
		unsigned short selected_k;
public:
	void DrawSubPlots(void);
	void Redim(unsigned short m,unsigned short n,unsigned short sel); 
	unsigned short GetDimM() const {return m_dim;} ;
	unsigned short GetDimN() const {return n_dim;} ;
	unsigned short GetSel() {return selected_k;};
	class CtmcSubPlot *GetSelPlot() { return m_subplots[selected_k]; };
	
	CtmcSubPlotArray(unsigned short m,unsigned short n);
	CtmcSubPlotArray();
	~CtmcSubPlotArray();

};
////
extern class CtmcFigureList g_tmcFigureList; // main root
////
void _tmcglPutString(float m,float n,const char* str,int len);

void _tmcglFigure(int ind); // open new empty window /or select exiting with given index. If win=0 - defaut counting
							// ind <0 : automatic ind creation
void _tmcglSubplot(int m,int n,int k); // create subplot dimentions/select subplot for plotting
void _tmcglPlot(const char *fn); // connect data and display to the current subplot and figure; 
							// if not created - create now.
void _tmcglClose(int ind); // close specified figure (ind<0: close current figure)
void _tmcglCloseAll(int bWithExit); // close all the figures


#endif