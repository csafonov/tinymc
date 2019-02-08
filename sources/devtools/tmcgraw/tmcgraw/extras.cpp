/*
 * OpenGLSamples (openglsamples.sf.net) Examples
 * VC++ users should create a Win32 Console project and link 
 * the program with glut32.lib, glu32.lib, opengl32.lib
 *
 * GLUT can be downloaded from http://www.xmission.com/~nate/glut.html
 * OpenGL is by default installed on your system.
 * For an installation of glut on windows for MS Visual Studio 2010 see:
 http://nafsadh.wordpress.com/2010/08/20/glut-in-ms-visual-studio-2010-msvs10/
 *
 */
#define drawLine1(x1,y1,x2,y2) glBegin(GL_LINES); \
glVertex2f ((x1),(y1)); glVertex2f ((x2),(y2)); glEnd();


Ctmc_karman_list karman_list;
/*
GLfloat mycol[16][3] = {
	1,0,0,	// red
	0,1,0,  // green
	0,0,1, // blue
	1,1,0, //
	0,1,1, //
	1,0,1,  //
	0,0,0,  //
	0,0,0,  //
	0,0,0,  //
	0,0,0,  //
	0,0,0,  //
	0,0,0,  //
	0,0,0,  //
	0,0,0,  //
	0,0,0,  //
	0,0,0  //
}; 
*/
void _tmcglgetplotdata()
{
		for (int k=0;k<1000;k++)
		{
			xx[k]=k/(1000.0)*3.1416*2.0;
			yy[k]=1.0*(0.0+sin(xx[k]*4.0f));
		}
}

void stam()
{
	FILE *fp = fopen("gr2.dat","wb");

		for (int k=0;k<1000;k++)
		{
			xx[k]=(2*k/(1000.0)-1) ;//*3.1416*2.0; \in [-1,1]
			yy[k]=0.9*(0.0+sin(xx[k]*4.0f*3.1416*20.0*3));
		}


	_tmcStorePlot(fp,xx,yy,0x01,
				  1000, 1,2,0);

		for (int k=0;k<1000;k++)
		{
			xx[k]=k/(1000.0)*3.1416*2.0;
			yy[k]=0.3*(0.0+cos(xx[k]*8.0f));
		}

	_tmcStorePlot(fp,xx,yy,0x02,
				  1000, 0,-1,-1);



	fclose(fp);

}
double xx[1000];
double yy[1000];

void _tmcglplotkarmans()
{
	double *pxx,*pyy;
	union Utmcplotcolor c;
	struct Ctmc_karman *pKarman;
	Ctmc_karman_list *pkarman_list;

	double X1,X2,Y1,Y2;
	long len;
	double minx,miny;
	double dx,dy;

	glLineWidth(1);

	// find selected plot, if not found temporary plot default list
	CtmcFigure * _fig =_tmcglFindFig(glutGetWindow());
	if (_fig->GetSubplots()==NULL)
	{
	pkarman_list = &karman_list;
	}
	else
	{
	pkarman_list = _fig->GetSubplots()->GetSelPlot()->GetKarmanList();
	}

/*	
	dx = (pkarman_list->stat.max_x - pkarman_list->stat.min_x);
	dy = (pkarman_list->stat.max_y - pkarman_list->stat.min_y);
	minx = pkarman_list->stat.min_x;
	miny = pkarman_list->stat.min_y;
*/
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
				X1 = (pxx[0]-minx) / dx*2*(1-FRAME_DN) -1+FRAME_DN;
				Y1 = (pyy[0]-miny) / dy*2*(1-FRAME_DM) -1+FRAME_DM;
			if (len==1)
			{
					//  plot of length 1
					glBegin(GL_POINTS);
					glVertex3f(X1, Y1, 0.0f);
					glEnd();

			}
			for (int k=1; k< len;k+=1)
			{
				X2 = (pxx[k]-minx) / dx*2*(1-FRAME_DN) -1+FRAME_DN;
				Y2 = (pyy[k]-miny) / dy*2*(1-FRAME_DM) -1+FRAME_DM;
					glBegin(GL_LINES);
					glVertex3f(X1, Y1, 0.0f);
					glVertex3f(X2, Y2, 0.0f);
					glEnd();
				X1=X2;Y1=Y2;
			}
		pKarman = pKarman->next;
	}
}
void _tmcglputframe(float dm,float dn)
{

	glColor3f(0.8,0.8,0.8);
	glPolygonMode(GL_FRONT, GL_FILL);
		glBegin(GL_POLYGON);
			glVertex2f(-1,1);
			glVertex2f(1,1);
			glVertex2f(1,1-dm);
			glVertex2f(-1,1-dm);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(1-dn,1);
			glVertex2f(1,1);
			glVertex2f(1,-1);
			glVertex2f(1-dn,-1);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(-1,-1+dm);
			glVertex2f(1,-1+dm);
			glVertex2f(1,-1);
			glVertex2f(-1,-1);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(-1,1);
			glVertex2f(-1+dn,1);
			glVertex2f(-1+dn,-1);
			glVertex2f(-1,-1);
		glEnd();

	_tmcglPutString(-0.999+dm/8,0,"Time [sec]",10);
}
/*
void _tmcglputgrid0(float stepm,float stepn)
{
	char buf[100];
	int n = 2/stepn;
	int m = 2/stepm;

	float stepnt = 0.023;
	float stepmt = 0.023;

	int nt = 2/stepnt;
	int mt = 2/stepmt;

	glColor3f(0,0,0);
	glLineWidth(0.5);
	for (int kn=0;kn<n;kn++)
	{
		// vertical lines
		for (int kmt=0;kmt<mt;kmt++)
		{
		glBegin(GL_LINES);
			glVertex2f(-1+stepn*kn,-1+stepmt*(kmt-0.25));
			glVertex2f(-1+stepn*kn,-1+stepmt*(kmt+0.25));
		glEnd();
		}
		sprintf(buf,"%5.5g",-1+stepn*kn);
		_tmcglPutString(-1+FRAME_DM/1.5,-1+stepn*kn,buf,5);
	}
	for (int km=0;km<m;km++)
	{
		// horizontal lines
		for (int knt=0;knt<nt;knt++)
		{
		glBegin(GL_LINES);
			glVertex2f(-1+stepnt*(knt-0.25), -1+stepm*km);
			glVertex2f(-1+stepnt*(knt+0.25),  -1+stepm*km);
		glEnd();
		}
		sprintf(buf,"%5.5g",-1+stepm*km);
		_tmcglPutString(-1+stepm*km,-1+FRAME_DM/1.8,buf,5);
	}

}
*/
void _tmcglputgrid(float stepm,float stepn)
{
	char buf[100];
	int n ;//= 2/stepn;
	int m ;//= 2/stepm;
	double X,Y;//karman
	double N,M; // rastr
	double dx,dy,minx,miny;

	float stepnt = 0.023;
	float stepmt = 0.023;

	int nt = 2/stepnt;
	int mt = 2/stepmt;

	// find selected plot, if not found temporary plot default list
	Ctmc_karman_list *pkarman_list;
	CtmcFigure * _fig =_tmcglFindFig(glutGetWindow());
	if (_fig->GetSubplots()==NULL)
	{
	pkarman_list = &karman_list;
	}
	else
	{
	pkarman_list = _fig->GetSubplots()->GetSelPlot()->GetKarmanList();
	}

	n = pkarman_list->metr.line_x_num;
	m = pkarman_list->metr.line_y_num;
/*
	dx = (pkarman_list->stat.max_x - pkarman_list->stat.min_x);
	dy = (pkarman_list->stat.max_y - pkarman_list->stat.min_y);
	minx = pkarman_list->stat.min_x;
	miny = pkarman_list->stat.min_y;
*/
	dx = (pkarman_list->metr.line_x2 - pkarman_list->metr.line_x0);
	dy = (pkarman_list->metr.line_y2 - pkarman_list->metr.line_y0);
	minx = pkarman_list->metr.line_x0;
	miny = pkarman_list->metr.line_y0;


	glColor3f(0,0,0);
	glLineWidth(0.5);
	for (int kn=0;kn<n;kn++)
	{
			X = pkarman_list->metr.line_x0 + kn*pkarman_list->metr.line_dx;
			
			N = (X-minx) / dx*2*(1-FRAME_DN) -1+FRAME_DN;

			// vertical lines
		for (int kmt=0;kmt<mt;kmt++)
		{

		glBegin(GL_LINES);
			glVertex2f(N,-1+stepmt*(kmt-0.25));
			glVertex2f(N,-1+stepmt*(kmt+0.25));
		glEnd();
		}
		sprintf(buf,"%5.5g",X);
		_tmcglPutString(-1+FRAME_DM/1.5,N,buf,5);
	}
	for (int km=0;km<m;km++)
	{
			Y = pkarman_list->metr.line_y0 + km*pkarman_list->metr.line_dy;
			M = (Y-miny) / dy*2*(1-FRAME_DM) -1+FRAME_DM;

		
		// horizontal lines
		for (int knt=0;knt<nt;knt++)
		{
		glBegin(GL_LINES);
			glVertex2f(-1+stepnt*(knt-0.25), M);
			glVertex2f(-1+stepnt*(knt+0.25), M);
		glEnd();
		}
		sprintf(buf,"%5.5g",Y);
		_tmcglPutString(M,-1+FRAME_DM/1.8,buf,5);
	}

}
void display0() 
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     // Clear Screen and Depth Buffer
	//glLoadIdentity();
	//glTranslatef(0.0f,0.0f,-1.0f);			
 
     glPushMatrix();

/*
		float X,Y;

		X =xx[0]; Y =yy[0];

		glColor3f(0,0,0);
		glBegin(GL_LINES);
			glVertex3f(-1, 0.0, 0.0f);
			glVertex3f(1,0, 0.0f);
		glEnd();

        glBegin(GL_LINES);
		glEnable(GL_LINE_STIPPLE); 
		glLineStipple(1, 0xAAAA);
			glVertex2f(0,-1 );
			glVertex2f(0,1 );
		glDisable(GL_LINE_STIPPLE);
        glEnd();
*/

	_tmcglplotkarmans();
		_tmcglputgrid(0.5,0.2);
		_tmcglputframe(FRAME_DN,FRAME_DM);


        glPopMatrix();

	glutSwapBuffers();
}

void CtmcFigure::PutFrame(void)
{
const float dn = FRAME_DN;
const float dm = FRAME_DM;

return;

	glColor3f(0.8,0.8,0.8);
	glPolygonMode(GL_FRONT, GL_FILL);
		glBegin(GL_POLYGON);
			glVertex2f(-1,1);
			glVertex2f(1,1);
			glVertex2f(1,1-dm);
			glVertex2f(-1,1-dm);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(1-dn,1);
			glVertex2f(1,1);
			glVertex2f(1,-1);
			glVertex2f(1-dn,-1);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(-1,-1+dm);
			glVertex2f(1,-1+dm);
			glVertex2f(1,-1);
			glVertex2f(-1,-1);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(-1,1);
			glVertex2f(-1+dn,1);
			glVertex2f(-1+dn,-1);
			glVertex2f(-1,-1);
		glEnd();

	_tmcglPutString(-0.999+dm/8,0,"Time [sec]",10);
}
