/*---------------------------------------------------------------------------*/
/*                                                                           */
/* FILE:    guidll.c                                                         */
/*                                                                           */
/* PURPOSE: This is a simple example of a LabWindows/CVI DLL that implements */
/*          its own GUI.  This DLL can be called from applications built in  */
/*          external compilers with no modifications to support the GUI.  If */
/*          want to compile and link code that uses LabWindows/CVI User-     */
/*          Interface callbacks directly in an external compiler, see the    */
/*          ExtComp external compiler samples.                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Include files                                                             */
/*---------------------------------------------------------------------------*/
#include <cvirte.h>   
#include <userint.h>
#include <utility.h>
#include "guidlluir.h"
#include "guidll.h"

// TMC code declarations
#include "tmc.h"

void main_tmc_app(double *Rr,double *Ri,int degP,double *P);
void tmcTestO(int nargout, int nargin,tmsMatrix *r,tmsMatrix *y
,tmsMatrix *p) ;


	 
void InitDll();
void FinDll();


/*---------------------------------------------------------------------------*/
/* DLL entry-point to handle initializations.                                */
/*---------------------------------------------------------------------------*/
int __stdcall DllMain (HINSTANCE hinstDLL, DWORD fdwReason,
                       LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
        {
        
        /* Place any initialization which needs to be done when the DLL */
        /* is loaded here. */
		
        if (InitCVIRTE (hinstDLL, 0, 0) == 0)
            return 0; 
		InitDll();
		
        } 
    else if (fdwReason == DLL_PROCESS_DETACH)
        {
        
        /* Place any clean-up which needs to be done when the DLL */
        /* is unloaded here. */
		FinDll();
        if (!CVIRTEHasBeenDetached ())
            CloseCVIRTE ();  
        }
    
    /* Return 0 to abort if initialization fails */
    return 1;
}

/*---------------------------------------------------------------------------*/
/* This function, when called, will initialize and run a GUI for this DLL.   */
/* This GUI will not interfere with other user-interfaces maintained by the  */
/* caller.  This function will not return until the GUI is unloaded.         */                                             
/*---------------------------------------------------------------------------*/
int __stdcall RunDLLUI (void)
{
    int hpanel;
    
    /* Note that we use LoadPanelEx rather than LoadPanel when our callback  */
    /* functions are not exported from a DLL.                                */
    if ((hpanel = LoadPanelEx (0, "guidlluir.uir", PANEL, __CVIUserHInst)) < 0)
        return 0;
    DisplayPanel (hpanel);
    RunUserInterface ();
    
    /* Free resources for the UI and return success */
    DiscardPanel (hpanel);
    return 1;
}

/*---------------------------------------------------------------------------*/
/* Close the User Interface panel and stop the loop.                         */
/*---------------------------------------------------------------------------*/
int CVICALLBACK CloseUICallback (int panel, int control, int event,
                                 void *callbackData, int eventData1,
                                 int eventData2)
{
    if (event == EVENT_COMMIT)
        {
        HidePanel (panel);
        QuitUserInterface (0);
        }
    return 0;
}

/*---------------------------------------------------------------------------*/
/* Respond to the UI to toggle the LED.                                      */
/*---------------------------------------------------------------------------*/
#define P_DEG 5 // deg(P)
double Rre[P_DEG];
double Rim[P_DEG]; 
double P[P_DEG+1];
int ph[P_DEG] = {0,0,0,0,0};



int  CVICALLBACK SliderCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
		 	int kk; 
    if (event == EVENT_VAL_CHANGED)
        {
		GetCtrlVal ( panel, PANEL_NUMERICSLIDE_A0, &P[0]);
		GetCtrlVal ( panel, PANEL_NUMERICSLIDE_A1, &P[1]);
		GetCtrlVal ( panel, PANEL_NUMERICSLIDE_A2, &P[2]);
		GetCtrlVal ( panel, PANEL_NUMERICSLIDE_A3, &P[3]);
		GetCtrlVal ( panel, PANEL_NUMERICSLIDE_A4, &P[4]);
		GetCtrlVal ( panel, PANEL_NUMERICSLIDE_A5, &P[5]);

		main_tmc_app(Rre,Rim,P_DEG,P);
		DeleteGraphAnnotation ( panel , PANEL_GRAPH, -1);
		ClearLegend (panel , PANEL_GRAPH);
			for (kk=0;kk<P_DEG;kk++)
			{
				if ( ph[kk] >0)
						 DeleteGraphPlot ( panel , PANEL_GRAPH, ph[kk], VAL_IMMEDIATE_DRAW);
				
			 ph[kk]= PlotPoint (panel, PANEL_GRAPH, Rre[kk], Rim[kk], VAL_SOLID_CIRCLE, VAL_RED);
			}
		
		
		}
		return 0;	
}
//////// TMC WRAPPER CODE /////////////////////
///////////////////////////////////////
//#define EXT_LINKAGE __declspec(dllimport)
extern   const struct CInit_funcs_table Init_funcs_table ;

void InitDll()
{
/////////////////
/////////////////
tmcInitLib(&Init_funcs_table);
}
void FinDll()
{
tmcFreeLib();
//////////////
//////////////
return ;
}

void main_tmc_app(double *Rr,double *Ri,int degP,double *P)
{
tmsMatrix *mr;   // [out] roots values
tmsMatrix *mp;   // [in] coeficients
tmsMatrix *my;  // when calling from user wrapper must provide all the variables !!!

   int kk;
   int n;
   
	mr = tmcNewMatrix();
	mp = tmcNewMatrix();
	 my = tmcNewMatrix();
	 
	_tmcCreateMatrix(mp,1,degP+1,tmcREAL);
	
	for (kk=0;kk<=degP ;kk++)
	{
		  mp->value.complx.rData[kk] =   P[kk];
	  
	}
	  tmcTestO(1, 1, mr,my, mp);
	  n  = _tmcGetM(mr)  * _tmcGetN(mr);
	for (kk=0;kk< degP && kk < n ;kk++)
	{
		Rr[kk] = mr->value.complx.rData[kk]  ;
		Ri[kk] = mr->value.complx.iData[kk]  ;	
	}
	for ( ;kk< degP   ;kk++) 
	{
		Rr[kk] =0;Ri[kk] =0;
	}
	
tmcFreeLocalVar(my);
tmcFreeLocalVar(mp);
tmcFreeLocalVar(mr);

}
