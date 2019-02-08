/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license.
 * 
  *****************************************************************************/
#ifndef  _TMC_EMBEDDED_
#include <windows.h>
#endif

#include "tmc.h"
#include "clapack_types.h"



#include  <math.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h> // ANSI compatibility

#include <stdio.h>

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

#ifndef  _TMC_EMBEDDED_

#define WM_TMC_FIGURE		(WM_USER+1) // wParam=h
#define WM_TMC_CLOSEFIGURE	(WM_USER+2) // wParam=h
#define WM_TMC_SUBPLOT		(WM_USER+3) //  m=LOWORD(lParam),n=HIWORD(lParam),k=wParam
#define WM_TMC_PLOT			(WM_USER+4)

// Color:
union Utmcplotcolor
{
	unsigned long all;
	struct {
		unsigned char r: 8;
		unsigned char g: 8;
		unsigned char b: 8;
	int	pointstyle : 4;
	int linestyle  : 2;
	int spare	   : 2;
	} color_style;
};

struct Ctmc_plot_inp_hdr
{
	unsigned long len;
	unsigned long mask; // 0: y only , 1: x present
	unsigned long plot_color;
};

////////// run tmcgra ////////////////
PROCESS_INFORMATION pi;
short InitTmcgra(void)
{
	int n;
	STARTUPINFO si;
	BOOL h;
	wchar_t sCommandLine[10000];
//	wchar_t wchar_module_path[_MAX_PATH];
	DWORD dwErr;

	size_t nlen;
	HWND hWnd;

	hWnd = FindWindow(L"TMCGRA",L"tmcgra");
	if (hWnd)
	{
		return 2; // already running 
	}
	
	nlen = strlen("tmcgra.exe /H")+1;

	swprintf(sCommandLine,nlen,L"tmcgra.exe /H");

    ZeroMemory(&si, sizeof(si) );
	ZeroMemory(&pi, sizeof(pi) );
    si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW ;//(STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	si.wShowWindow = SW_HIDE;//or SW_MINIMIZE;SW_SHOW ;
	si.hStdError = NULL ;
	si.hStdInput = NULL ;
	si.hStdOutput = NULL ;
    h = CreateProcess(0,	// No module name (use command line).
        &sCommandLine[0],				// Command line.
        0,					// Process handle not inheritable.
        0,					// Thread handle not inheritable.
        TRUE,					// Set handle inheritance to TRUE.
        0,						// No creation flags.
        0,					// Use parent's environment block.
        0,					// Use parent's starting directory.
        &si,					// Pointer to STARTUPINFO structure.
        &pi );

	if( h == 0 )
	{
		dwErr = GetLastError();

		fwprintf(stderr,L"\n****** WARNING:  tmcgra features not available,dwErr=%d\n",dwErr);
		fflush(stderr);
    ZeroMemory(&si, sizeof(si) );
	ZeroMemory(&pi, sizeof(pi) );
		return -1;
	}
	// Wait the process to start... in order not to run another process
	hWnd = FindWindow(L"TMCGRA",L"tmcgra");
	n=0;
	while  (!hWnd && n<500)
	{ n++;
		Sleep(10);
	hWnd = FindWindow(L"TMCGRA",L"tmcgra");
	}


return 0;//Ok
}
short CloseTmcgra(void)
{
	unsigned long exitCode ;
	short isActive ;
	HWND hWnd;

 	hWnd = FindWindow(L"TMCGRA",L"tmcgra");
	if (!hWnd || !pi.hProcess || !pi.hThread)
	{
		return 2; // already closed 
	}

	// Wait until child process exits.
    CloseHandle(pi.hThread );
	//fwprintf(stderr,L"\nGenerating %s...\n",OutputFileName);
	//fflush(stderr);

	//SendMessage(hWnd,WM_QUIT,0,0);

	while( 1 )
	{
		Sleep(200);
		isActive = GetExitCodeProcess( pi.hProcess, &exitCode ) ;
		if ( exitCode != STILL_ACTIVE )
		{
			break ;
		}
		if( isActive == 0 )
		{
			break;
		}
	}
    CloseHandle(pi.hProcess );

	//fwprintf(stderr,L"\nFinished generating code");
	//fflush(stderr);
	return 0;//Ok
}

void AssureTmcgra(void)
{
	InitTmcgra();
}
#else
	short CloseTmcgra(void)
	{
			return 0;
	}
#endif
///////////////////////

#ifndef  _TMC_EMBEDDED_
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
#endif


//void tmcget(long nout,long ninput,tmsMatrix *val,tmsMatrix *obj,tmsMatrix *prop)
//{
//	if (nout>0)
//	_tmcCreateMatrix(val,1,1,0);
//
//	_tmcRaiseException(err_unsupported,"kernel","get","get(classobj,'prop') not supported",2,&obj,&prop);
//}


#ifndef  _TMC_EMBEDDED_
/// This function is platform-specific
void tmcwaitbar(long nout,long ninput,tmsMatrix *hand,tmsMatrix *frac, tmsMatrix *title,tmsMatrix *pt1,tmsMatrix *pv1,tmsMatrix *pt2,tmsMatrix *pv2)
{
extern __int64 g_MemCnt;
extern __int64 g_MemN;
extern __int64 g_MemUsed;

	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);

	if (ninput>1)
		fprintf(stdout,"waitbar: %f, Mem=%I64d,N=%I64d,MU=%I64d \n",frac->m_rData[0],g_MemCnt,g_MemN,g_MemUsed);
}
#endif

void tmcclose(long nout,long ninput,tmsMatrix *stat,tmsMatrix *hand)
{
	if (nout>0)
	_tmcCreateMatrix(stat,1,1,0);
		fprintf(stdout,"closed handle %f \n",hand->m_rData[0]);
}
void tmcaxis(long nout,long ninput,tmsMatrix *hand,...)
{
	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);
		fprintf(stdout,"WARN: axis() not suppoted \n");
}
void tmcgca(long nout,long ninput,tmsMatrix *hand)
{
	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);
		fprintf(stdout,"WARN: gca not suppoted \n");
}
void tmcset(long nout,long ninput,tmsMatrix *stat,tmsMatrix *obj,tmsMatrix *pt,tmsMatrix *pv,...)
{
	if (nout>0)
	_tmcCreateMatrix(stat,1,1,0);
		fprintf(stdout,"WARN: set not suppoted \n");

}
void tmcylabel(long nout,long ninput,tmsMatrix *hand, tmsMatrix *title)
{
	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);
		fprintf(stdout,"WARN: ylabel not suppoted \n");
}

void tmcxlabel(long nout,long ninput,tmsMatrix *hand, tmsMatrix *title)
{
	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);
		fprintf(stdout,"WARN: xlabel not suppoted \n");
}
void tmcfill(long nout,long ninput,tmsMatrix *hand, tmsMatrix *x, tmsMatrix *y, tmsMatrix *c)
{
	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);
		fprintf(stdout,"WARN: fill() not suppoted \n");
}

#ifndef  _TMC_EMBEDDED_
unsigned long _tmcGetPlotType(tmsMatrix *c)
{
/*
        b     blue          .     point              -     solid
           g     green         o     circle             :     dotted
           r     red           x     x-mark             -.    dashdot 
           c     cyan          +     plus               --    dashed   
           m     magenta       *     star
           y     yellow        s     square
           k     black         d     diamond
                               v     triangle (down)
                               ^     triangle (up)
                               <     triangle (left)
                               >     triangle (right)
                               p     pentagram
                               h     hexagram
*/
	union Utmcplotcolor clr;
char col = (char)c->value.complx.rData[0];

	clr.all = 0;
	switch (col)
	{
	case 'b':
		clr.color_style.b = 255;
		break;
	case 'g':
		clr.color_style.g = 255;
		break;
	case 'r':
		clr.color_style.r = 255;
		break;
	case 'c':
		clr.color_style.g = 255;
		clr.color_style.b = 255;
		break;
	case 'm':
		clr.color_style.r = 255;
		clr.color_style.b = 255;
		break;
	case 'y':
		clr.color_style.r = 255;
		clr.color_style.g = 255;
		break;
	case 'k':
		break;

	default:
		// black
		;

	}


	return clr.all;
}
#endif

void tmcplot(long nout,long ninput, tmsMatrix *hand, tmsMatrix *x, tmsMatrix *y, tmsMatrix *c,...)
{
#ifndef  _TMC_EMBEDDED_
	HWND hWnd;
	FILE *fp;
			va_list marker;
			tmsMatrix *x2, *y2, *c2;
			long k;
			union Utmcplotcolor clr;

		long numPlots=1;
			clr.all=0;

AssureTmcgra();

	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);

	hWnd = FindWindow(L"TMCGRA",L"tmcgra");
	if (hWnd)
	{
		fp = fopen("tmcgra.dat","wb");

		if (ninput==1)
		{
			clr.color_style.b  = 255;
		_tmcStorePlot(fp,NULL,x->value.complx.rData,clr.all,
				  tmcNumElem(x), 1,(unsigned short)numPlots,0);
		} else if (ninput==2)
		{
			clr.color_style.b  = 255;
		_tmcStorePlot(fp,x->value.complx.rData,y->value.complx.rData,clr.all,
				  tmcNumElem(x), 1,(unsigned short)numPlots,0);
		}else if (ninput==3)
		{
			clr.all  = _tmcGetPlotType(c);
		_tmcStorePlot(fp,x->value.complx.rData,y->value.complx.rData,clr.all,
				  tmcNumElem(x), 1,(unsigned short)numPlots,0); // HAZARD: get color
		}
		else
		{
			numPlots = ninput/3;
			clr.all  = _tmcGetPlotType(c);
		    _tmcStorePlot(fp,x->value.complx.rData,y->value.complx.rData,clr.all,
				  tmcNumElem(x), 1,(unsigned short)numPlots,0); // HAZARD: get color
			va_start( marker, c );     // Initialize variable arguments.
			for (k=1;k<numPlots;k++)
			{
				// get new var
				x2 = va_arg( marker,  tmsMatrix * );
				y2 = va_arg( marker,  tmsMatrix * );
				c2 = va_arg( marker,  tmsMatrix * );
			clr.all  = _tmcGetPlotType(c2);
		    _tmcStorePlot(fp,x2->value.complx.rData,y2->value.complx.rData,clr.all,
				  tmcNumElem(x2), 0,0,0); // HAZARD: get color


			}
			va_end( marker );              // Reset variable arguments.
		}



		fclose(fp);
		//SendMessage(hWnd,WM_TMC_FIGURE,0,0);
		SendMessage(hWnd,WM_TMC_PLOT,0,0);
		
	}


	//	fprintf(stdout,"WARN: plot() not suppoted \n");
#else
	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);

#endif

}
void tmctext(long nout,long ninput, tmsMatrix *hand, tmsMatrix *x1,...)
{
	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);
		fprintf(stdout,"WARN: text() not suppoted \n");
}
void tmctitle(long nout,long ninput, tmsMatrix *hand,tmsMatrix *str,...)
{
	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);
		fprintf(stdout,"WARN: title() not suppoted \n");
}
void tmcsubplot(long nout,long ninput, tmsMatrix *hand,tmsMatrix *mM,...)
{
#ifndef  _TMC_EMBEDDED_

	HWND hWnd;
	long m,n,k;
	tmsMatrix *mN,*mK;
	va_list marker;

	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);
	hWnd = FindWindow(L"TMCGRA",L"tmcgra");
	if (hWnd)
	{
		if (ninput==3)
		{
			m  =(long) mM->value.complx.rData[0];
			va_start( marker, mM );     // Initialize variable arguments.
			mN = va_arg( marker,  tmsMatrix * );
			mK = va_arg( marker,  tmsMatrix * );
			n  =(long) mN->value.complx.rData[0];
			k  =(long) mK->value.complx.rData[0];
			va_end( marker );              // Reset variable arguments.

			SendMessage(hWnd,WM_TMC_SUBPLOT,k,m+(n<<16));
		}
	}
	//	fprintf(stdout,"WARN: subplot() not suppoted \n");
#else
	if (nout>0)
	_tmcCreateMatrix(hand,1,1,0);
#endif
}
void tmchold(long nout,long ninput,tmsMatrix *ydummy,tmsMatrix *onoff)
{
// this function is implemented with one output to avoid TMC compilation warnings.
	if (nout>0)
	_tmcCreateMatrix(ydummy,1,1,0);
		fprintf(stdout,"WARN: hold() not suppoted \n");

}
void tmcgrid(long nout,long ninput,tmsMatrix *ydummy,tmsMatrix *onoff)
{
// this function is implemented with one output to avoid TMC compilation warnings.
	if (nout>0)
	_tmcCreateMatrix(ydummy,1,1,0);
		fprintf(stdout,"WARN: grid() not suppoted \n");

}
void tmcfigure(long nout,long ninput,tmsMatrix *fhand,tmsMatrix *fnum)
{
#ifndef  _TMC_EMBEDDED_

WORD wParam=0;
HWND hWnd;

AssureTmcgra();
   if (ninput>0)
	if (tmcNumElem(fnum)>0)
		wParam = (WORD)(fnum->value.complx.rData[0]);
	hWnd = FindWindow(L"TMCGRA",L"tmcgra");
	if (hWnd)
	{
	SendMessage(hWnd,WM_TMC_FIGURE,wParam,0);
	}
#endif
   if (nout>0)
	_tmcCreateMatrix(fhand,1,1,0);

}
void tmcnichols(long nout,long ninput,tmsMatrix *sys,tmsMatrix *mopt)
{
		fprintf(stdout,"WARN: nichols() not suppoted \n");
}
void tmcgcf(long nout,long ninput,...)
{
		fprintf(stdout,"WARN: gcf() not suppoted \n");
}
void tmcishold(long nout,long ninput,tmsMatrix *y,tmsMatrix *fhan)
{
		fprintf(stdout,"WARN: ishold() not suppoted \n");
}
