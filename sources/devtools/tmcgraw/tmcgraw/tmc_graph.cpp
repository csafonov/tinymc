#include <stdio.h>



#include <memory.h>
#include <stdlib.h>

#include <windows.h>	   // Standard header for MS Windows applications
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glaux.h>		   // Open Graphics Library (OpenGL) header

#include "tmcgra_gl.h"
#include <math.h>
#include "tmc_graph.h"

class CtmcFigureList g_tmcFigureList; // main root
HINSTANCE	hInstance;		// Holds The Instance Of The Application

GLvoid _tmcglPrint(const char *fmt, ...);

	GLuint	base;				// Base Display List For The Font Set


/// some utilities ////////
void _tmcglPutString(float m,float n,const char* str,int len)
{
	glColor3f(0,0,0);
    glRasterPos3f(n,m,-0.1f);

	//_tmcglPrint(str);
	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists((GLsizei)len, GL_UNSIGNED_BYTE, str);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits


	// HSKOST_TODO: print font
	//for (int k=0;k<len;k++)
	//{
	//		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[k]);
	//}
}

///////// Ctmc_karman_list ///////////////
Ctmc_karman_list::Ctmc_karman_list() : numplots(0),plottype(0),first(NULL),last(NULL)
{
   memset(&stat,0,sizeof(stat));
   memset(&metr,0,sizeof(metr));

}
void Ctmc_karman_list::ClearKarmanList(void)
{
	struct Ctmc_karman *p = first;
	struct Ctmc_karman *p_next;
	while ( p != NULL)
	{
		if (p->xx)
			free(p->xx);
		if (p->yy)
			free(p->yy);
		p_next = p->next;
		free(p);
		p = p_next;
	}
};

void Ctmc_karman_list::ReadKarmanList(FILE *fp)
{
	size_t n;
	struct Ctmc_karman *prev=NULL;

  numplots=0;
  plottype=0;
  first=0;
  last=0;
   memset(&stat,0,sizeof(stat));
   memset(&metr,0,sizeof(metr));

	n =fread(&numplots,sizeof(unsigned short),1,fp);
	n =fread(&plottype,sizeof(unsigned short),1,fp);
	for (unsigned  short k=0; k<numplots;k++)
	{
		last = (struct Ctmc_karman *)malloc(sizeof(struct Ctmc_karman));
		memset(last,0,sizeof(struct Ctmc_karman));
		if (k==0)
		{
			first=last;
		}
		else
		{
			prev->next = last;
		}
		n =fread(&last->hdr,sizeof(struct Ctmc_plot_inp_hdr),1,fp);
		if (last->hdr.mask & 1)
		{
			last->xx = (double*)malloc(sizeof(double)*last->hdr.len);
			n = fread(last->xx,sizeof(double),last->hdr.len,
				fp);
		}
		last->yy = (double*)malloc(sizeof(double)*last->hdr.len);
		n = fread(last->yy,sizeof(double),last->hdr.len,fp);
		
		prev = last;
	}
	GetStatistics();
	GetMetrics();
};

void getarr_range(const double *pxx,double *minx,double *maxx,long len,double xmin0,double xmax0)
{
	*minx = xmin0;//pxx[0];
	*maxx = xmax0;//pxx[0];
	for (long k=0;k<len;k++)
	{
		if (pxx[k]>*maxx)
		{
			*maxx=pxx[k];
		}
		if (pxx[k]<*minx)
		{
			*minx=pxx[k];
		}
	}
}

void Ctmc_karman_list::GetStatistics(void)
{
	struct Ctmc_karman * pKarman = first;
double *pxx,*pyy;
unsigned long len;
double minx,miny,maxx,maxy;

	for (unsigned short ka=0;ka<numplots;ka++)
	{
			pxx = pKarman->xx;
			pyy = pKarman->yy;
			len = pKarman->hdr.len;
			if (ka==0)
			{
				minx=maxx=pxx[0];
				miny=maxy=pyy[0];
			}
			getarr_range(pxx,&minx,&maxx,len,minx,maxx);
			getarr_range(pyy,&miny,&maxy,len,miny,maxy);
		pKarman = pKarman->next;
	}
	stat.max_y = maxy;
	stat.min_y = miny;
	stat.max_x = maxx;
	stat.min_x = minx;

}

#define ___MIN(x,y) ( ((x)>(y))? (y): (x) )
#define ___MAX(x,y) ( ((x)>(y))? (x): (y) )

double round_frac(double x)
{
  double n = pow(10, floor(log10(fabs(x))));
  double  y = floor(x / n + 1/1.8) * n;
  return y;
}

#define sign(x) ( ((x)>0) ? 1: ((x)<0 ? -1:0  )   )
 void Ctmc_karman_list::GetMetrics(void)
 {
		metr.line_y_num = 11; // number of lines, 1 plus number of bars
		metr.line_dy = (stat.max_y-stat.min_y) / (metr.line_y_num-1);
		metr.line_y0 =stat.min_y;
			// here we can adjust the grid...
		metr.line_dy =round_frac(metr.line_dy);
		//metr.line_y0 = ___MIN(stat.min_y ,  round_frac(  )  );
        metr.line_y_num = (short)ceil((stat.max_y-stat.min_y) / metr.line_dy) + 1;
	 
/////////

		metr.line_x_num = 11;
		metr.line_dx = (stat.max_x-stat.min_x) / (metr.line_x_num-1);
		metr.line_x0 =stat.min_x;
			// here we can adjust the grid...
		metr.line_dx =round_frac(metr.line_dx);
		//metr.line_x0 = ___MIN(stat.min_x ,  round_frac(  )  );
        metr.line_x_num = (short)ceil((stat.max_x-stat.min_x) / metr.line_dx) + 1;


/////////
	 metr.line_x2 = metr.line_x0+(metr.line_x_num-1)*metr.line_dx;
	 metr.line_y2 = metr.line_y0+(metr.line_y_num-1)*metr.line_dy;
	 // may a bit resize range here to increase.
/*
	stat.max_y = metr.line_y2;
	stat.min_y = metr.line_y0;
	stat.max_x = metr.line_x2;
	stat.min_x = metr.line_x0;
*/


 }
//////////////////////////////////////////
void _tmcStorePlot(FILE *fp,const double *x,const double *y,unsigned long colr,
				  unsigned long len, short bNew,unsigned short nPlots,unsigned short plottype)
{
	struct Ctmc_plot_inp_hdr plot_inp_hdr;
	if (bNew)
	{
		fwrite(&nPlots ,sizeof(unsigned short),1,fp);
		fwrite(&plottype,sizeof(unsigned short),1,fp);
	}
	memset(&plot_inp_hdr,0,sizeof(plot_inp_hdr));
	plot_inp_hdr.len = len;
	if (x==NULL)
	{
		plot_inp_hdr.mask=0;
	}
	else
	{
		plot_inp_hdr.mask=1;
	}
	plot_inp_hdr.plot_color  = colr;

	fwrite(&plot_inp_hdr ,sizeof(plot_inp_hdr),1,fp);
	if (plot_inp_hdr.mask & 1)
	{
		fwrite(x ,sizeof(double),plot_inp_hdr.len,fp);
	}
	fwrite(y ,sizeof(double),plot_inp_hdr.len,fp);
}

//////////////////////
void _tmcglFigure(int ind)
// open new empty window /or select exiting with given index. If win=0 - defaut counting
// ind <0 : automatic ind creation
{
	// register the figure in the list and open
	g_tmcFigureList.SelectFig(ind); // return 1 if new figure
}
void _tmcglClose(int ind)
// close specified figure (ind<0: close current figure)
{
	g_tmcFigureList.Remove(ind);
}
void _tmcglPlot(const char *fn)
{
	// plot at the selected subplot at the selected figure from the file
	CtmcFigure *_fig  = g_tmcFigureList.GetFigSelected();
    CtmcSubPlotArray * _subplots  = _fig->GetSubplots();
	CtmcSubPlot *_subplot;

	if (_subplots == NULL)
	{
		_fig->CreateSubPlots(1,1,1);
		_subplots  = _fig->GetSubplots();
	}
	_subplot = _subplots->GetSelPlot();
	_subplot->LoadKarmans(fn);

	//SetFocus(_fig->GetWin());
	_fig->SetCurrentWindow();
	_fig->MarkUpdate();
	//glutSetWindow(_fig->GetWin());
	//glutPostRedisplay(); // redisplay current window

}

///////////////////////// CtmcFigure ////////////////

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport
/*
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
*/
}



int  CtmcFigure::KillWorkGLWindow(void)								// Properly Kill The Window
{
	if (hRC)
	{
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(hRC);
		if (hDC)
		{
			ReleaseDC(hWnd,hDC);
		}
	}
	DestroyWindow(hWnd);
			KillFont();		

	/*
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,L"Release Of DC And RC Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,L"Release Rendering Context Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,L"Release Device Context Failed.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,L"Could Not Release hWnd.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass(L"tmcgrafigwin",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,L"Could Not Unregister Class.",L"SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
	*/
	return FALSE;
}

int CtmcFigure::CreateWorkGLWindow(void)
{
			hDC=NULL;		// Private GDI Device Context
		hRC=NULL;		// Permanent Rendering Context


	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)m_width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)m_height;		// Set Bottom Value To Requested Height

		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	m_title_w	=	new wchar_t[256];
	swprintf(m_title_w,L"figure No.%d",ind);
	
	m_bits = 16;

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								L"tmcgrafigwin",							// Class Name
								m_title_w,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillWorkGLWindow();								// Reset The Display
		MessageBox(NULL,L"Window Creation Error.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}
//////////////////////
	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		m_bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillWorkGLWindow();								// Reset The Display
		MessageBox(NULL,L"Can't Create A GL Device Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillWorkGLWindow();								// Reset The Display
		MessageBox(NULL,L"Can't Find A Suitable PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillWorkGLWindow();								// Reset The Display
		MessageBox(NULL,L"Can't Set The PixelFormat.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillWorkGLWindow();								// Reset The Display
		MessageBox(NULL,L"Can't Create A GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillWorkGLWindow();								// Reset The Display
		MessageBox(NULL,L"Can't Activate The GL Rendering Context.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	//ReSizeGLScene(m_width, m_height);					// Set Up Our Perspective GL Screen

	//if (!InitGL())									// Initialize Our Newly Created GL Window
	InitFigGL(m_width,m_height);
	//{
	//	KillWorkGLWindow();								// Reset The Display
	//	MessageBox(NULL,L"Initialization Failed.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
	//	return FALSE;								// Return FALSE
	//}


return TRUE;
//////////////////////
}

/*int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	return TRUE;										// Initialization Went OK
}*/

void CtmcFigure::InitFigGL (int width, int height) 
{
	float field_of_view_angle=90.0f;
	float z_near=0.0f;
	float z_far=0.0f;

    glMatrixMode(GL_PROJECTION);												// select projection matrix
    glViewport(0, 0, width, height);									// set the viewport
    glMatrixMode(GL_PROJECTION);												// set matrix mode
    glLoadIdentity();															// reset projection matrix
    GLfloat aspect = 1;//(GLfloat) win.width / win.height;
	gluPerspective(field_of_view_angle, aspect, z_near, z_far);		// set up a perspective projection matrix
    glMatrixMode(GL_MODELVIEW);													// specify which matrix is the current matrix
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );														// specify the clear value for the depth buffer
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						// specify implementation-specific hints
	
	glClearColor(0.8f,0.8f,0.8f, 1.0f);		//was white=255,255,255									// specify clear values for the color buffers								

	//glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	SetFigCursor(IDC_CROSS);
	BuildFont();



	return ;
}

CtmcFigure::CtmcFigure(int _ind) : 
	ind(_ind), // user figure number
	m_SubPlotList(NULL),
	next(NULL),m_update(0)
{
	m_width=640;
	m_height=480;
	m_title=new char[256];
	sprintf(m_title,"figure No.%d",_ind);
	
	SetReshape(m_width,m_height);

	// create GL figure
	//glutInitWindowSize(m_width,m_height);					// set window size
	//__glutCreateWindowWithExit(m_title,WinExitFunc);								// create Window
	//glutDisplayFunc(display);									// register Display Function
	//glutReshapeFunc(reshape);									// register reshape Function
	////glutIdleFunc( display );									// register Idle Function
    //
	//glutKeyboardFunc( keyboard );								// register Keyboard Handler
	//glutMouseFunc(mousefunc);// register mouse buttons Handler
	//InitFigGL(m_width,m_height);
	//win = glutGetWindow();

	// Work-arounds
	CreateWorkGLWindow();
	//InitFigGL(m_width,m_height);

}
CtmcFigure::~CtmcFigure()
{
	//glutDestroyWindow(this->win);
	KillWorkGLWindow();
	delete m_SubPlotList;
}
void CtmcFigure::SetFigCursor(LPWSTR t)
{
	xcursor = LoadCursor(NULL, IDC_CROSS);
}
void CtmcFigure::SetCurrentWindow(void)
{
	// TODO:may be must remember the current window
    HGLRC currentContext = wglGetCurrentContext();                    
    HDC currentDc = wglGetCurrentDC();                                
                                                                      
	if (currentContext !=  GetHRC() || currentDc !=  GetHDC() )
	{                             
      wglMakeCurrent(GetHDC(), GetHRC());  
	}
}
void CtmcFigure::ReshapeWindow(void) 
{
	if (m_ReshapeNow.bDoNow)
	{
		m_ReshapeNow.bDoNow=0;
		SetCurrentWindow();
		glViewport(0, 0, m_ReshapeNow.width, m_ReshapeNow.height);
	}
	return;
}

void CtmcFigure::WinExitFunc(void) // HWND hWnd
{// WM_CLOSE Handler
	fprintf(stderr,"window is closed\n");
	// close the window
		CtmcFigure * _fig =this; // g_tmcFigureList.FindFigByHWND(hWnd);
		g_tmcFigureList.Remove(_fig->GetInd());
	if (g_tmcFigureList.GetNumFigures()==0)
		exit(11);
}

void CtmcFigure::CreateSubPlots(unsigned short m,unsigned short n,unsigned short sel)
{
		if (m_SubPlotList==NULL)
		{
			m_SubPlotList =  new CtmcSubPlotArray(m,n);
		}
		else
		{
			m_SubPlotList->Redim(m,n,sel);
		}
}
void CtmcFigure::DisplaySubPlots(void)
{


	if ( GetSubplots()==NULL)
	{
		return ;
		// pkarman_list = &karman_list;
	}
	else
	{
	 GetSubplots()->DrawSubPlots();
	}

}
///////////////// CtmcFigureList ///////////////////
class CtmcFigure*	CtmcFigureList::FindFigByInd(int _ind,class CtmcFigure **prev)
{
	class CtmcFigure *ptr=NULL;
	
	class CtmcFigure *next_ptr=first;

	class CtmcFigure *prev_ptr=NULL;

	while (next_ptr != NULL)
	{
		if (next_ptr->GetInd() == _ind)
		{
			ptr=next_ptr;
			break;
		}
		if (next_ptr->next !=NULL)
		{
			prev_ptr = next_ptr;
		}
		next_ptr = next_ptr->next;
	};

	if (prev !=NULL)
	{
		* prev  = prev_ptr;
	}
	return ptr;
}
class CtmcFigure *CtmcFigureList::FindFigByHWND(HWND hWnd)
{
	class CtmcFigure *ptr=NULL;
	class CtmcFigure *next_ptr=g_tmcFigureList.GetFirstFig();
	while (next_ptr != NULL)
	{
		if (next_ptr->GetWin() == hWnd)
		{
			ptr=next_ptr;
			break;
		}
		next_ptr = next_ptr->next;
	};
	return ptr;
}
int CtmcFigureList::SelectFig(int ind)
{
	// return: 1:new,0:found
int stat = 1; 

	if (ind<=0)
	{
		ind = ++max_fig_ind;
	}
	if (ind>max_fig_ind)
	{
		max_fig_ind=ind;
	}

	class CtmcFigure *ptr = FindFigByInd(ind);
	// try find the window in the list
	if (ptr==NULL)
	{
		// not found, create new figure
		ptr = new CtmcFigure(ind);
		num_figures++;
		// append the figure to the list
		if (this->last == NULL)
		{
			// list was emply
			this->last  = ptr;
			this->first = ptr;
		}
		else
		{
			this->last->next  = ptr;
			this->last = ptr;
		}
	}
	else
	{
		// found, select it for plot/close
		stat = 0;
	}
	SetFigSelected(ptr);
	SetFocus(ptr->GetWin());

	return stat;
}

void CtmcFigureList::Remove(int ind)
{
	class CtmcFigure *ptr;
	class CtmcFigure *prev_ptr;

	if (ind <=0)
	{
		ptr = GetFigSelected();
		ind = ptr->GetInd();
	}

	ptr = FindFigByInd(ind,&prev_ptr);
	if (ptr)
	{
		if (prev_ptr==NULL)
		{
			first = ptr->next;
			if (last==ptr)
			{
				last=first;//both are NULL
			}
		}
		else
		{
			prev_ptr->next=ptr->next;
			if (last==ptr)
			{
				last = prev_ptr;
			}
		}
		delete ptr;
	--num_figures;
	}
}
void CtmcFigureList::DisplayFig(HWND hWnd)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     // Clear Screen and Depth Buffer
    glPushMatrix();
	
	CtmcFigure * _fig =g_tmcFigureList.FindFigByHWND(hWnd);
	if (_fig)
	_fig->DisplaySubPlots();//draw plots

	 //_tmcglplotkarmans();
	 //_tmcglputgrid(0.5,0.2);
	 //_tmcglputframe(FRAME_DN,FRAME_DM);
    glPopMatrix();
	//glutSwapBuffers();
}
void CtmcFigureList::DisplayFig(CtmcFigure * _fig)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     // Clear Screen and Depth Buffer
    glPushMatrix();
	
	//CtmcFigure * _fig =g_tmcFigureList.FindFigByHWND(hWnd);
	if (_fig)
	_fig->DisplaySubPlots();//draw plots

	 //_tmcglplotkarmans();
	 //_tmcglputgrid(0.5,0.2);
	 //_tmcglputframe(FRAME_DN,FRAME_DM);
    glPopMatrix();
	//glutSwapBuffers();
}
//////// work-arounds //////////////
long n;
void CtmcFigureList::MsgLoop(void)
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	while(!done)									// Loop That Runs While done=FALSE
	{
		
		MsgWaitForMultipleObjects(0, NULL, FALSE, 2, QS_ALLEVENTS);
n = ((n+1) & 1023);


		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
			GdiFlush();
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			
			CtmcFigure * _fig =g_tmcFigureList.first ;//.FindFigByHWND(msg.hwnd);
			while (_fig)
			{


			if (_fig)
			{



				if (_fig->GetUpdate())
				{
				_fig->ClearUpdate();
				_fig->SetCurrentWindow();
				g_tmcFigureList.DisplayFig(_fig);//msg.hwnd
				_fig->ReshapeWindow();


					//if (_fig)
						SwapBuffers(_fig->GetHDC());

				/*

				


				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
				glLoadIdentity();									// Reset The Current Modelview Matrix
				glTranslatef(-1.5f,0.0f,-6.0f);						// Move Left 1.5 Units And Into The Screen 6.0
				glBegin(GL_TRIANGLES);								// Drawing Using Triangles
					glVertex3f( 0.0f, 1.0f, 0.0f);					// Top
					glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
					glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
				glEnd();											// Finished Drawing The Triangle
				glTranslatef(3.0f,0.0f,0.0f);						// Move Right 3 Units
				glBegin(GL_QUADS);									// Draw A Quad
					glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
					glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
					glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
					glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
				glEnd();											// Done Drawing The Quad
				*/
				}
				else
				{
					//
					//movie
					if (_fig->GetInd()==1)
					{
						_fig->SetCurrentWindow();
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
			     glBegin(GL_LINES);
					glVertex2f(0,0);
					glVertex2f(0.5*sin( (n)/1024.0f*2*3.14f   ) ,0.5*cos( (n)/1024.0f*2*3.14f   ));
				glEnd();
			     glBegin(GL_LINES);
					glVertex2f(0,0);
					glVertex2f(0.15*sin( (n)/1024.0f*2*3.14f  *5. ) ,0.15*cos( (n)/1024.0f*2*3.14f   *5.));
				glEnd();
				SwapBuffers(_fig->GetHDC());
					}
				}


			}
				_fig = _fig->next;
			}

		//if (_fig)
			//SwapBuffers(_fig->GetHDC());					// Swap Buffers (Double Buffering)
			// Here may process registreted keys
			// .........
		}
	}
}

// common windows procedure for figures
// The procedure must save some events for idle loop proccessing
LRESULT CALLBACK TmcGraFigWinWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//int wmId, wmEvent;
	//PAINTSTRUCT ps;
	//HDC hdc;
	CtmcFigure* _fig = g_tmcFigureList.FindFigByHWND(hWnd);

	if (message == WM_PAINT || message == WM_PAINT || message ==WM_SIZE ||
		message == WM_CHAR)
	{
			if (_fig)
				_fig->MarkUpdate();
	}

	switch (message)
	{
//	case WM_COMMAND:
//		wmId    = LOWORD(wParam);
//		wmEvent = HIWORD(wParam);
//		// Parse the menu selections:
//		switch (wmId)
//		{
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//		break;
	//case WM_PAINT:
		//hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		//EndPaint(hWnd, &ps);

	//	break;
	case WM_CLOSE:
		if (_fig)
			_fig->WinExitFunc();
		break;
	case WM_DESTROY:
		//PostQuitMessage(0);
		break;

	case WM_CHAR:
		keyboard ( hWnd, (char)(TCHAR) wParam,0, 0);
		break;

	case WM_SIZE:								// Resize The OpenGL Window
		{
			//ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			//glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
			if (_fig)
			_fig->SetReshape(LOWORD(lParam), HIWORD(lParam));
			return 0;								// Jump Back
		}
	//case WM_SETCURSOR:
	//	{
	//		//if (_fig)
	//TODO: SetCursor(_fig->GetFigCursor());
	//	}
	//	break;
////////////////////////


	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;


}
void CtmcFigureList::InitWorkAround(void)
{
	WNDCLASS	wc;						// Windows Class Structure

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) TmcGraFigWinWndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= L"tmcgrafigwin";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,L"Failed To Register The Window Class.",L"ERROR",MB_OK|MB_ICONEXCLAMATION);
		return ;											// Return FALSE
	}

}
void CtmcFigureList::FinishWorkAround(void)
{
	UnregisterClass(L"tmcgrafigwin",hInstance);
}
///////// fonts /////////////////////////
GLvoid CtmcFigure::BuildFont(GLvoid)								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	base = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-12,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_NORMAL,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						L"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, base);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}

GLvoid CtmcFigure::KillFont(GLvoid)									// Delete The Font List
{
	glDeleteLists(base, 96);							// Delete All 96 Characters
}

GLvoid _tmcglPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists((GLsizei)strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}

//////////// CtmcSubPlotArray //////////
CtmcSubPlotArray::CtmcSubPlotArray(unsigned short M,unsigned short N):
		num_subplots(M*N),m_dim(M), n_dim(N),
		selected_k(0)
{
   m_subplots = (CtmcSubPlot **)malloc(sizeof(CtmcSubPlot*) * M * N  );
   int k=0;
   for (unsigned short m=0;m<M;m++)
   {	k++;
		for (unsigned short n=0;n<N;n++)
		{
		m_subplots[m+M*n] = new CtmcSubPlot(this,k-1);
		}
   }
}
void CtmcSubPlotArray::Redim(unsigned short M,unsigned short N,unsigned short sel)
{
	if (m_dim != M || n_dim != N)
	{
		   for (unsigned short m=0;m<m_dim;m++)
		   {
				for (unsigned short n=0;n<n_dim;n++)
				{
					delete m_subplots[m+m_dim*n];
				}
		   }
	   m_subplots = (CtmcSubPlot **)realloc(m_subplots, sizeof(CtmcSubPlot*) * M * N  );
   		num_subplots=M*N;
		m_dim=M;n_dim=N;
	   int k=0;
	   for (unsigned short m=0;m<M;m++)
	   {k++;
			for (unsigned short n=0;n<N;n++)
			{
			m_subplots[m+M*n] = new CtmcSubPlot(this,k-1);
			}
	   }
	}
	selected_k  = sel-1; // 0-based index
}
CtmcSubPlotArray::CtmcSubPlotArray():num_subplots(0),m_dim(0),n_dim(0),
m_subplots(NULL),selected_k(0)
{
}
CtmcSubPlotArray::~CtmcSubPlotArray()
{
   for (unsigned short m=0;m<m_dim;m++)
   {
		for (unsigned short n=0;n<n_dim;n++)
		{
			delete m_subplots[m+m_dim*n];
		}
   }
   if (m_subplots)
	   free(m_subplots);

}
void CtmcSubPlotArray::DrawSubPlots(void)
{
   for (unsigned short m=0;m<m_dim;m++)
   {
		for (unsigned short n=0;n<n_dim;n++)
		{
			m_subplots[m+m_dim*n]->DrawSubPlot();
		}
   }

}
///////////////// CtmcSubPlot /////////////
void CtmcSubPlot::LoadKarmans(const char *fn)
{
	FILE *fp = fopen(fn,"rb");
	karman_list.ReadKarmanList(fp);
	fclose(fp);
}
CtmcSubPlot::CtmcSubPlot(CtmcSubPlotArray *_m_parent,int _k) : m_parent(_m_parent),k(_k),
dn((2-2*FRAME_DN-(m_parent->GetDimN()-1)*SP_DN)/m_parent->GetDimN()),
dm((2-2*FRAME_DM-(m_parent->GetDimM()-1)*SP_DM)/m_parent->GetDimM())
{
	//memset(&karman_list,0,sizeof(karman_list));
m = ((k+1) / _m_parent->GetDimN())-1;
n = k - m*_m_parent->GetDimN();
offn=(FRAME_DN+n*(dn+SP_DN));
offm=(FRAME_DM+m*(dm+SP_DM));
}
CtmcSubPlot::~CtmcSubPlot()
{
	karman_list.ClearKarmanList();
}
void CtmcSubPlot::DrawSubPlot(void)
{
	double *pxx,*pyy;
	union Utmcplotcolor c;
	struct Ctmc_karman *pKarman;
	Ctmc_karman_list *pkarman_list;

	float X1,X2,Y1,Y2;
	long len;
	double minx,miny;
	double dx,dy;

	pkarman_list = GetKarmanList();


	PutFrame();

	glLineWidth(1);


	dx = (pkarman_list->metr.line_x2 - pkarman_list->metr.line_x0);
	dy = (pkarman_list->metr.line_y2 - pkarman_list->metr.line_y0);
	minx = pkarman_list->metr.line_x0;
	miny = pkarman_list->metr.line_y0;


	pKarman = pkarman_list->first;
	for (unsigned short ka=0;ka<pkarman_list->numplots;ka++)
	{
			//c =  (pKarman->hdr.plot_color & 0xF);
	        //glColor3f(mycol[c][0],mycol[c][1],mycol[c][2]);
			c.all = pKarman->hdr.plot_color;
			glColor3f(c.color_style.r/256.0f,c.color_style.g/256.0f,c.color_style.b/256.0f);
			pxx = pKarman->xx;
			pyy = pKarman->yy;
			len = pKarman->hdr.len;
	
			// Get first point
				X1 = (float)((pxx[0]-minx) / dx*dn -1+offn);
				Y1 = (float)((pyy[0]-miny) / dy*dm +(1-offm-dm));
			if (len==1)
			{
					//  plot of length 1
					glBegin(GL_POINTS);
					glVertex3f(X1, Y1, 0.0f);
					glEnd();

			}
			for (int k=1; k< len;k+=1)
			{
				X2 = (float)((pxx[k]-minx) / dx*dn -1+offn);
				Y2 = (float)((pyy[k]-miny) / dy*dm +(1-offm-dm));
					glBegin(GL_LINES);
					glVertex3f(X1, Y1, 0.0f);
					glVertex3f(X2, Y2, 0.0f);
					glEnd();
				X1=X2;Y1=Y2;
			}
		pKarman = pKarman->next;
	}
	PutGrid();
}
void CtmcSubPlot::PutFrame(void)
{
	glColor3f(255,255,255);
	glPolygonMode(GL_FRONT, GL_FILL);
		glBegin(GL_POLYGON);
			//glVertex2f(-1+FRAME_DN+offn,1-FRAME_DM+offm);
			//glVertex2f(1-FRAME_DN+offn+dn,1-FRAME_DM+offm);
			//glVertex2f(1-FRAME_DN+offn+dn,-1+FRAME_DM+offm+dm);
			//glVertex2f(-1+FRAME_DN+offn,-1+FRAME_DM+offm+dm);

			glVertex2f(-1+offn,1-offm);
			glVertex2f(-1+offn+dn,1-offm);
			glVertex2f(-1+offn+dn,1-(offm+dm) );
			glVertex2f(-1+offn,1-(offm+dm) );
		glEnd();

		glBegin(GL_LINES);
			glVertex2f(-1+offn,1-offm);
			glVertex2f(-1+offn+dn,1-offm);
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(-1+offn+dn,1-offm);
			glVertex2f(-1+offn+dn,1-(offm+dm) );
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(-1+offn+dn,1-(offm+dm) );
			glVertex2f(-1+offn,1-(offm+dm) );
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(-1+offn,1-(offm+dm) );
			glVertex2f(-1+offn,1-offm);
		glEnd();

		_tmcglPutString(-0.999f+FRAME_DM/8.0f,0,"Time [sec]",10);
}
void CtmcSubPlot::PutGrid(void)
{
	char buf[100];
	int n ;//= 2/stepn;
	int m ;//= 2/stepm;
	float X,Y;//karman
	float N,M; // rastr
	double dx,dy,minx,miny;

	float stepnt = 0.023f;
	float stepmt = 0.023f;

	int nt = (int)(dn/stepnt);
	int mt = (int)(dm/stepmt);

	// find selected plot, if not found temporary plot default list
	Ctmc_karman_list *pkarman_list = GetKarmanList();

	n = pkarman_list->metr.line_x_num;
	m = pkarman_list->metr.line_y_num;

	dx = (pkarman_list->metr.line_x2 - pkarman_list->metr.line_x0);
	dy = (pkarman_list->metr.line_y2 - pkarman_list->metr.line_y0);
	minx = pkarman_list->metr.line_x0;
	miny = pkarman_list->metr.line_y0;


	glColor3f(0,0,0);
	glLineWidth(0.5);
	for (int kn=0;kn<n;kn++)
	{
			X =(float)( pkarman_list->metr.line_x0 + kn*pkarman_list->metr.line_dx);
			
			N =(float)( (X-minx) / dx*dn -1+offn);

			// vertical lines
		for (int kmt=0;kmt<mt;kmt++)
		{

		glBegin(GL_LINES);
			glVertex2f(N,(1-dm-offm)+stepmt*(kmt-0.25f));
			glVertex2f(N,(1-dm-offm)+stepmt*(kmt+0.25f));
		glEnd();
		}
		sprintf(buf,"%5.5g",X);
		_tmcglPutString(1-dm-offm-SP_DM*0.5f,N-SP_DN*0.5f,buf,5);
	}
	for (int km=0;km<m;km++)
	{
			Y =(float)( pkarman_list->metr.line_y0 + km*pkarman_list->metr.line_dy);
			M =(float)( (Y-miny) / dy*dm +(1-dm-offm));
		
		// horizontal lines
		for (int knt=0;knt<nt;knt++)
		{
		glBegin(GL_LINES);
			glVertex2f(-1+offn+stepnt*(knt-0.25f), M);
			glVertex2f(-1+offn+stepnt*(knt+0.25f), M);
		glEnd();
		}
		sprintf(buf,"%5.5g",Y);
		_tmcglPutString(M,-1+offn-SP_DM*0.5f,buf,5);
	}
}
///////////////////////////////////////////

void _tmcglSubplot(int m,int n,int k) // create subplot dimentions/select subplot for plotting
{
	CtmcFigure * _fig =g_tmcFigureList.GetFigSelected();
	_fig->CreateSubPlots(m,n,k);


	//SetFocus(_fig->GetWin());
	_fig->SetCurrentWindow();
	_fig->MarkUpdate();
	//glutSetWindow(_fig->GetWin());
	//glutPostRedisplay(); // redisplay current window
}

