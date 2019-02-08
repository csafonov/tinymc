// File: tmcgra_gl.cpp
// Purpose: figure windows managment

#pragma comment(lib,"glu32.lib"  )
#pragma comment(lib,"opengl32.lib")

#include <windows.h>	   // Standard header for MS Windows applications

#include <stdio.h>
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
//#include <GL/glu.h>	   
#include <stdlib.h>
#define KEY_ESCAPE 27

#include <math.h>

#include "tmcgra_gl.h"

#include "tmc_graph.h"

void _tmcglfinishgraph();





//void display()
//{
//	g_tmcFigureList.DisplayFig(hWnd);
//}




void zoomStart()
{

}
void zoomFinish()
{

}
void zoomOff()
{

}
void mousefunc(int button, int state,int x, int y)
{
//button: GLUT LEFT BUTTON, GLUT MIDDLE BUTTON, or GLUT RIGHT BUTTON
// state: GLUT UP or GLUT DOWN
	if (button==MK_LBUTTON)
	{
		if (state==WM_LBUTTONDOWN)
		{
			// start zoom
			zoomStart();
		}
		else
			if (state==WM_LBUTTONUP)
			{
				// finish zoom
				zoomFinish();
			}

	}
	else
		if (button==MK_RBUTTON)
		{
				// restore zoom
				zoomOff();
		}
}

void keyboard (HWND hWnd, unsigned char key, int mousePositionX, int mousePositionY )		
{ // used for debugging so far
	void exit(int);
class CtmcFigure *ptr;



  switch ( key ) 
  {
    case KEY_ESCAPE:   // exit application     
		_tmcglfinishgraph();   
      break;      
	
	case '1':
		// select first figure
		_tmcglFigure(1);
		break;
	case '2':
		// select 2 figure
		_tmcglFigure(2);
		break;
	case '3':
		// select 3 figure
		_tmcglFigure(3);
		break;
	case 'A':
		_tmcglPlot("gr1.dat");
		break;
	case 'B':
		_tmcglPlot("gr2.dat");
		break;
	case 'C':
		_tmcglPlot("gr3.dat");
		break;

//	case 'P': // create debugging data
//		stam();
//		_tmcglfinishgraph();
//		break;
	case 'f': // new figure
		_tmcglFigure(0);
		break;
	case 'c': // close window
		ptr = g_tmcFigureList.FindFigByHWND(hWnd);
		_tmcglClose(ptr->GetInd());
		if (g_tmcFigureList.GetNumFigures()==0)
		{
				_tmcglfinishgraph();
		}
		break;
	//case 'r':
	//	glClearColor(20,30,40,1.0);
	//	glutPostRedisplay();
	//	_fig->MarkUpdate();
	//	break;
	case 'w':
		_tmcglFigure(4);
		_tmcglSubplot(2,1,1);
		_tmcglPlot("gr1.dat");
		_tmcglSubplot(2,1,2);
		_tmcglPlot("gr2.dat");

		break;
    default:  

      break;
  }
}

void _tmcglfinishgraph()
{
	//HAZARD_TODO: karman_list.ClearKarmanList();
	g_tmcFigureList.FinishWorkAround();
	exit(0);
}

void _tmcglinitgraph()
//int main(int argc, char **argv) 
{
extern void ShowTray();
extern void fn1(int x);
extern int fn2(void);

	int argc=1;
	char *argv[1]={ "x" };

/*
	//ShowTray();
	//FILE *fp = fopen("gr1.dat","rb");
	//_tmcReadKarmanList(&karman_list,fp);
	//fclose(fp);

	//_tmcglgetplotdata();
	// initialize and run program
	__glutInitWithExit(&argc, argv,fn1);                                      // GLUT initialization
	_onexit(  fn2  );
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	_tmcglFigure(1);// Temporary by default we open here first figure;
	glutMainLoop();												// run GLUT mainloop
*/

	g_tmcFigureList.InitWorkAround();
	_tmcglFigure(1);
	g_tmcFigureList.MsgLoop();
	//return 0;
}
short here=0;
void fn1(int x)
{// dont exit
	here=12;
	return;
}
int fn2(void)
{
	here=12;
	return -100;
}

/////////// work-arounds ///////////////
