package com.tmc.tunerdemo;

import android.os.Bundle;
import android.view.View;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.app.Activity;


import android.content.Context;
//import android.graphics.Bitmap;
//import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.RectF;
import android.util.AttributeSet;
import  java.lang.Math ;
import java.util.LinkedList;
import java.util.ListIterator;

/////////////
class MyTrans
{
	// GL coordinates: (0,0) is Centre,axes: x right,y up. W = 2,H=2
	// New coordinates: (0,0) is left-top. Centre is (W/2,-H/2),axes: x right,y down.
	static private int w;
	static private int h;
	static public void init(int width,int height) {
		w = width; h  = height;
	}
	static public float x(float glx)
	{
		return  w/2*glx + w/2 ;
	};
	static public float y(float gly)
	{
		return -h/2*gly + h/2  ;
	};	
};

class Ctmc_plot_inp_hdr
{
	int len;
	int mask; // 0: y only , 1: x present
	int plot_color;
	Paint  mForeground;
    void setLineColor(int color) {
        mForeground = new Paint();
        mForeground.setColor(color);
    };
};

// for reading data
class Ctmc_karman
{
	public static int getKarmanLen(int numplots,int len)
	{
		return 2 + ((3+len*2))*numplots;
	};
	Ctmc_plot_inp_hdr hdr = new Ctmc_plot_inp_hdr();
	double [] xx;
	double [] yy;
	// Ctmc_karman next;
};

// karmans statistics
class RangeX
{
	double minx;
	double maxx;
	public RangeX(double xmin0,double xmax0)  {
		minx=xmin0;maxx= xmax0;
	};
	private void minmax(double x)
	{
		if (x>maxx)
		{
			maxx=x;
		}
		if (x<minx)
		{
			minx=x;
		}
	}
	public  void getarr_range(double [] pxx,long len)
	{
		for (int k=0;k<len;k++)
		{
			minmax(pxx[k]);
		}
	}
};

class Ctmc_karmans_stat
{
	double max_y=0;
	double min_y=0;
	double max_x=0;
	double min_x=0;

	void clear()
	{
		max_y=0;
		min_y=0;
		max_x=0;
		min_x=0;		
	}
	
};
class Ctmc_karmans_metr
{
	double line_y0=0;
	double line_dy=0;
	double line_x0=0;
	double line_dx=0;
	int  line_y_num=0;
	int  line_x_num=0;
	double line_y2=0;
	double line_x2=0;
	void clear()
	{
		line_y0=0;
		line_dy=0;
		line_x0=0;
		line_dx=0;
		line_y_num=0;
		line_x_num=0;
		line_y2=0;
		line_x2=0;		
	}
};
class Ctmc_karman_list
{
	final int NUM_VERTICAL_LINES = 5; // may change according to screen size etc.
	final int NUM_HORIZONTAL_LINES = 5;
	public short numplots=0;
	public short plottype=0;
	public LinkedList<Ctmc_karman> lst =  new LinkedList<Ctmc_karman>();
	public Ctmc_karmans_stat stat = new Ctmc_karmans_stat();
	public Ctmc_karmans_metr metr = new Ctmc_karmans_metr();

	public void ClearKarmanList( ) {
		lst.clear();
	};
	
	public void ReadKarmanList(Karman karman ) { // read data from double buffer returned from native code
		int n;
			
		Ctmc_karman last;
		
		
		lst.clear();
	    numplots=0;
	    plottype=0;
	    stat.clear();
	    metr.clear();
	  
	    n=0;
	    numplots =(short)(int) karman.buffer[n++];
	    plottype =(short)(int) karman.buffer[n++];
	    
    
		for (int k=0; k<numplots;k++)
		{
			last = new Ctmc_karman();
			
			last.hdr.len = (int) karman.buffer[n++];
			last.hdr.mask= (int) karman.buffer[n++]; // 0: y only , 1: x present
			last.hdr.plot_color= (int) karman.buffer[n++];
			last.hdr.setLineColor(last.hdr.plot_color);
			//last.hdr.setLineColor(Color.BLUE);
			if ( (last.hdr.mask & 1) != 0)
			{
				last.xx = new double[last.hdr.len];
				for (int kk=0; kk<last.hdr.len;kk++)
				{
					last.xx[kk] = karman.buffer[n++];
				}
			}
			
			last.yy = new double[last.hdr.len];
			for (int kk=0; kk<last.hdr.len;kk++)
			{
				last.yy[kk] = karman.buffer[n++];
			}
			
			lst.add(last);
		}
		GetStatistics();
		GetMetrics();
	};
	
	public void GetStatistics() {
		ListIterator<Ctmc_karman> iter = lst.listIterator(0);
		
		Ctmc_karman  pKarman = iter.next(); //lst.getFirst();//iter.previous();
		double [] pxx = pKarman.xx;
		double [] pyy = pKarman.yy;
		long len;
		
		RangeX rx  = new RangeX(pxx[0],pxx[0]);
		RangeX ry  = new RangeX(pyy[0],pyy[0]);
		
		// while (iter.hasNext())
			for (short ka=0;ka<numplots;ka++)
			{
					pxx = pKarman.xx;
					pyy = pKarman.yy;
					len = pKarman.hdr.len;

					rx.getarr_range(pxx,len);
					ry.getarr_range(pyy,len);
					if ( iter.hasNext() )
							pKarman = iter.next();
			}
			stat.max_y = ry.maxx;
			stat.min_y = ry.minx;
			stat.max_x = rx.maxx;
			stat.min_x = rx.minx;
	}; // calculate statistics for mapping/scaling
	
	double round_frac(double x)
	{
	  double n = Math.pow(10, Math.floor(Math.log10(Math.abs(x))));
	  double  y = Math.floor(x / n + 1/1.8) * n;
	  return y;
	};
	
	public void GetMetrics() {
		metr.line_y_num = NUM_VERTICAL_LINES; // number of lines, 1 plus number of bars
		metr.line_dy = (stat.max_y-stat.min_y) / (metr.line_y_num-1);
		metr.line_y0 =stat.min_y;
			// here we can adjust the grid...
		metr.line_dy =round_frac(metr.line_dy);
		//metr.line_y0 = ___MIN(stat.min_y ,  round_frac(  )  );
        metr.line_y_num = (int) Math.ceil((stat.max_y-stat.min_y) / metr.line_dy) + 1;
	 
/////////

		metr.line_x_num = NUM_HORIZONTAL_LINES;
		metr.line_dx = (stat.max_x-stat.min_x) / (metr.line_x_num-1);
		metr.line_x0 =stat.min_x;
			// here we can adjust the grid...
		metr.line_dx =round_frac(metr.line_dx);
		//metr.line_x0 = ___MIN(stat.min_x ,  round_frac(  )  );
        metr.line_x_num = (int) Math.ceil((stat.max_x-stat.min_x) / metr.line_dx) + 1;


/////////
	 metr.line_x2 = metr.line_x0+(metr.line_x_num-1)*metr.line_dx;
	 metr.line_y2 = metr.line_y0+(metr.line_y_num-1)*metr.line_dy;		
		
	};
};


class CtmcSubPlot	
{
//	private
	// int m_width;
	// int m_height;
	 
	final float FRAME_DM	=0.2f;
	final float FRAME_DN	=0.2f;
	final float SP_DM	=0.2f;
	final float SP_DN	=0.2f;

	
		final CtmcSubPlotArray m_parent;
		final int k;
		final float dn;
		final float dm;
		int m;
		int n;
		float offn;
		float offm;
		Ctmc_karman_list karman_list = new Ctmc_karman_list();
		private Paint  mGridColor; 
		private Paint  mFrameColor;
		private Paint  mBarrelColor;
		void PutBarrel(Canvas canvas,int width,int height)
		{
			//RectF recf = new RectF(0.4f*width, 0.4f*height, 0.6f*width, 0.8f*height) ;
	        //canvas.drawOval(recf, mBarrelColor); //.drawCircle(x, y, radius, circleColor);
			int kk;
			
			// Get first point
			//float x1 =(float) mbarrel.tetaAng[0];
			//float y1 = (float)mbarrel.dB[0];
			
			double minx,miny;
			double dx,dy;

			Ctmc_karman_list pkarman_list = GetKarmanList();
			// glLineWidth(1); Here set the thickness of the line

				//TODO: Nichols must have different shape (fixed ranges)
			dx = (pkarman_list.metr.line_x2 - pkarman_list.metr.line_x0);
			dy = (pkarman_list.metr.line_y2 - pkarman_list.metr.line_y0);
			minx = pkarman_list.metr.line_x0;
			miny = pkarman_list.metr.line_y0;
			
			/*float X1 = (float)((x1-minx) / dx*dn -1+offn);
			float Y1 = (float)((y1-miny) / dy*dm +(1-offm-dm));
			float X2,Y2;
			for (kk=1; kk< mbarrel.mBarLen; kk++)
			{
				  x1 =(float) mbarrel.tetaAng[kk];
				  y1 = (float)mbarrel.dB[kk];
				
				X2 = (float)((x1-minx) / dx*dn -1+offn);
				Y2 = (float)((y1-miny) / dy*dm +(1-offm-dm));
				
				canvas.drawLine(MyTrans.x(X1),MyTrans.y(Y1),
						MyTrans.x(X2),MyTrans.y(Y2), mBarrelColor);
				
				X1=X2;Y1=Y2;
			}*/
		}
		void PutGrid(Canvas canvas,int width,int height) {
			//char buf[100];
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
			Ctmc_karman_list pkarman_list = GetKarmanList();

			n = pkarman_list.metr.line_x_num;
			m = pkarman_list.metr.line_y_num;

			dx = (pkarman_list.metr.line_x2 - pkarman_list.metr.line_x0);
			dy = (pkarman_list.metr.line_y2 - pkarman_list.metr.line_y0);
			minx = pkarman_list.metr.line_x0;
			miny = pkarman_list.metr.line_y0;

			// select color and line width
			//glColor3f(0,0,0);
			//glLineWidth(0.5);
			Paint circleColor = mGridColor;
			for (int kn=0;kn<n;kn++)
			{
					X =(float)( pkarman_list.metr.line_x0 + kn*pkarman_list.metr.line_dx);
					
					N =(float)( (X-minx) / dx*dn -1+offn);

					// vertical lines
				for (int kmt=0;kmt<mt;kmt++)
				{
					canvas.drawLine(MyTrans.x(N),MyTrans.y((1-dm-offm)+stepmt*(kmt-0.25f)),
							MyTrans.x(N),MyTrans.y((1-dm-offm)+stepmt*(kmt+0.25f)), circleColor);
				//glBegin(GL_LINES);
				//	glVertex2f(N,(1-dm-offm)+stepmt*(kmt-0.25f));
				//	glVertex2f(N,(1-dm-offm)+stepmt*(kmt+0.25f));
				//glEnd();
				}
				//sprintf(buf,"%5.5g",X);
				//_tmcglPutString(1-dm-offm-SP_DM*0.5f,N-SP_DN*0.5f,buf,5);
				canvas.drawText(Float.toString(X),  MyTrans.x(N-SP_DN*0.5f),  MyTrans.y(1-dm-offm-SP_DM*0.5f),circleColor);
				
			}
			for (int km=0;km<m;km++)
			{
					Y =(float)( pkarman_list.metr.line_y0 + km*pkarman_list.metr.line_dy);
					M =(float)( (Y-miny) / dy*dm +(1-dm-offm));
				
				// horizontal lines
				for (int knt=0;knt<nt;knt++)
				{
				//glBegin(GL_LINES);
				//	glVertex2f(-1+offn+stepnt*(knt-0.25f), M);
				//	glVertex2f(-1+offn+stepnt*(knt+0.25f), M);
				//glEnd();
				canvas.drawLine( MyTrans.x(-1+offn+stepnt*(knt-0.25f)), MyTrans.y(M),
							MyTrans.x(-1+offn+stepnt*(knt+0.25f)),MyTrans.y(M), circleColor);
				}
				//sprintf(buf,"%5.5g",Y);
				canvas.drawText(Float.toString(Y), MyTrans.x(-1+offn-SP_DM*0.5f), MyTrans.y(M),  circleColor);
				//_tmcglPutString(M,-1+offn-SP_DM*0.5f,buf,5);
			}	
		
		
		}; // put grid by GL
		
		void PutFrame(Canvas canvas,int  width,int height) {
			
			Paint circleColor = mFrameColor;
			//glColor3f(255,255,255);
			//glPolygonMode(GL_FRONT, GL_FILL);
				//glBegin(GL_POLYGON);
			
			
					canvas.drawRect(MyTrans.x(-1+offn), MyTrans.y(1-offm),
							MyTrans.x(-1+offn+dn), MyTrans.y(1-(offm+dm)), circleColor);
			
		//	canvas.drawRect((-1+offn)*width, (1-offm)*height,
		//			(-1+offn+dn)*width, (1-(offm+dm))*height, circleColor);
					//glVertex2f(-1+offn,1-offm);
					//glVertex2f(-1+offn+dn,1-offm);
					//glVertex2f(-1+offn+dn,1-(offm+dm) );
					//glVertex2f(-1+offn,1-(offm+dm) );
				//glEnd();

				//glBegin(GL_LINES);
					canvas.drawLine(MyTrans.x(-1+offn),MyTrans.y(1-offm), 
							MyTrans.x(-1+offn+dn),MyTrans.y(1-offm), mGridColor);
					
					//glVertex2f(-1+offn,1-offm);
					//glVertex2f(-1+offn+dn,1-offm);
				//glEnd();
				//glBegin(GL_LINES);
					canvas.drawLine(MyTrans.x(-1+offn+dn),MyTrans.y(1-offm),
							MyTrans.x(-1+offn+dn),MyTrans.y(1-(offm+dm)), mGridColor);
				//	glVertex2f(-1+offn+dn,1-offm);
				//	glVertex2f(-1+offn+dn,1-(offm+dm) );
				//glEnd();
				//glBegin(GL_LINES);
					canvas.drawLine(MyTrans.x(-1+offn+dn),MyTrans.y(1-(offm+dm)),
							MyTrans.x(-1+offn),MyTrans.y(1-(offm+dm)), mGridColor);
				//	glVertex2f(-1+offn+dn,1-(offm+dm) );
				//	glVertex2f(-1+offn,1-(offm+dm) );
				//glEnd();
				//glBegin(GL_LINES);
					canvas.drawLine(MyTrans.x(-1+offn),MyTrans.y(1-(offm+dm)),
							MyTrans.x(-1+offn),MyTrans.y(1-offm), mGridColor);
				//	glVertex2f(-1+offn,1-(offm+dm) );
				//	glVertex2f(-1+offn,1-offm);
				//glEnd();

				//_tmcglPutString(-0.999f+FRAME_DM/8.0f,0,"Time [sec]",10);	
		
		
		}; // put frame bars by GL
		
	//public
		public void LoadKarmans(Karman karman) {
			karman_list.ReadKarmanList(karman);
		};
		public Ctmc_karman_list   GetKarmanList() {
			return karman_list;
		};
		public void DrawSubPlot(Canvas canvas,int width,int height) { // GL function
			double [] pxx,pyy;
			//union Utmcplotcolor c;
			Ctmc_karman pKarman;
			Ctmc_karman_list pkarman_list;

			float X1,X2,Y1,Y2;
			int len;
			double minx,miny;
			double dx,dy;

			
			pkarman_list = GetKarmanList();
			PutFrame(canvas, width, height);
			// glLineWidth(1); Here set the thickness of the line


			dx = (pkarman_list.metr.line_x2 - pkarman_list.metr.line_x0);
			dy = (pkarman_list.metr.line_y2 - pkarman_list.metr.line_y0);
			minx = pkarman_list.metr.line_x0;
			miny = pkarman_list.metr.line_y0;

			//pKarman = pkarman_list->first;
			for (int ka=0;ka< pkarman_list.numplots;ka++)
			{
					// HERE get the line color
				    //c.all = pKarman->hdr.plot_color;
					//glColor3f(c.color_style.r/256.0f,c.color_style.g/256.0f,c.color_style.b/256.0f);
					
					pKarman = pkarman_list.lst.get(ka);
					Paint circleColor = pKarman.hdr.mForeground;
										        
				    pxx = pKarman.xx;
					pyy = pKarman.yy;
					len = pKarman.hdr.len;
			
					// Get first point
						X1 = (float)((pxx[0]-minx) / dx*dn -1+offn);
						Y1 = (float)((pyy[0]-miny) / dy*dm +(1-offm-dm));
					if (len==1)
					{
							//  plot of length 1
							//glBegin(GL_POINTS);
							//glVertex3f(X1, Y1, 0.0f);
							//glEnd();
						
												
						canvas.drawLine(MyTrans.x(X1),MyTrans.y(Y1),
								MyTrans.x(X1),MyTrans.y(Y1), circleColor);
						
						//canvas.drawLine(X1*width,Y1*height, X1*width, Y1*height, circleColor);

					}
					
					//////////
					
					
					
					for (int k=1; k< len;k+=1)
					{
						X2 = (float)((pxx[k]-minx) / dx*dn -1+offn);
						Y2 = (float)((pyy[k]-miny) / dy*dm +(1-offm-dm));
						
						canvas.drawLine(MyTrans.x(X1),MyTrans.y(Y1),
								MyTrans.x(X2),MyTrans.y(Y2), circleColor);
						//canvas.drawLine((X1+1.0f)*width,(Y1+1.0f)*height, (X2+1.0f)*width, (Y2+10f)*height, circleColor);	
						
						
						//glBegin(GL_LINES);
							//glVertex3f(X1, Y1, 0.0f);
							//glVertex3f(X2, Y2, 0.0f);
							//glEnd();
						X1=X2;Y1=Y2;
					}
				
			}
			PutGrid(canvas,width,height);	
			PutBarrel(canvas,width,height);
		};// GL
		
		public CtmcSubPlot(CtmcSubPlotArray _m_parent,int _k, int width,int height) {
			 //m_width=width;
			 //m_height = height;
			 
			mGridColor = new Paint();
			mGridColor.setColor(Color.BLACK);
			mGridColor.setTextSize(8.0f);
			
			mFrameColor = new Paint();
			mFrameColor.setColor(Color.WHITE);
			
			mBarrelColor = new Paint();
			mBarrelColor.setColor(Color.BLUE);
			
			
			m_parent=_m_parent;k=_k;
			dn=((2-2*FRAME_DN-(m_parent.GetDimN()-1)*SP_DN)/m_parent.GetDimN());
			dm=((2-2*FRAME_DM-(m_parent.GetDimM()-1)*SP_DM)/m_parent.GetDimM());
			
			m = ((k+1) / _m_parent.GetDimN())-1;
			n = k - m*_m_parent.GetDimN();
			offn=(FRAME_DN+n*(dn+SP_DN));
			offm=(FRAME_DM+m*(dm+SP_DM));
		}
		public void close() {
			karman_list.ClearKarmanList();
		};	
};

class CtmcSubPlotArray
{
//	private:
		int num_subplots;
		int m_dim;
		int n_dim;
		CtmcSubPlot [] m_subplots;
		int selected_k;
		
		int m_width;
		int m_height;
		
	public  void DrawSubPlots(Canvas canvas,int width,int height) {
		for (int m=0;m<m_dim;m++)
		   {
				for (int n=0;n<n_dim;n++)
				{
					m_subplots[m+m_dim*n].DrawSubPlot(canvas,width,height);
				}
		   }		
	};
	public void Redim(int M,int N,int sel) {
		if (m_dim != M || n_dim != N)
		{
			   for (int m=0;m<m_dim;m++)
			   {
					for (int n=0;n<n_dim;n++)
					{
						m_subplots[m+m_dim*n].close();
						m_subplots[m+m_dim*n] = null;
					}
			   }
		   m_subplots = new  CtmcSubPlot [M*N]; // [] (CtmcSubPlot **)realloc(m_subplots, sizeof(CtmcSubPlot*) * M * N  );
	   		num_subplots=M*N;
			m_dim=M;n_dim=N;
		   int k=0;
		   for (int m=0;m<M;m++)
		   {k++;
				for (int n=0;n<N;n++)
				{
				m_subplots[m+M*n] = new CtmcSubPlot(this,k-1,m_width,m_height);
				}
		   }
		}
		selected_k  = sel-1; // 0-based index		
	};
	
	public int GetDimM()  {return m_dim;} ;
	public int GetDimN()  {return n_dim;} ;
	public int GetSel() {return selected_k;};
	public CtmcSubPlot GetSelPlot() { return m_subplots[selected_k]; };
	
	public CtmcSubPlotArray( int m2, int n2,int width,int height) {
		num_subplots=(m2*n2);m_dim=(m2); n_dim=(n2);
		selected_k=(0);
		m_width=width;
		m_height=height;
		
	   m_subplots = new CtmcSubPlot[m2*n2]; 
	   int k=0;
	   for (int m=0;m<m2;m++)
	   {	k++;
			for (int n=0;n<n2;n++)
			{
			m_subplots[m+m2*n] = new CtmcSubPlot(this,k-1, width, height);
			}
	   }
	};
	
	public CtmcSubPlotArray() {
		num_subplots=(0);m_dim=(0);n_dim=(0);
		m_subplots=null;selected_k=(0);
	};
	
	public void close() {
		   for (int m=0;m<m_dim;m++)
		   {
				for (int n=0;n<n_dim;n++)
				{
					m_subplots[m+m_dim*n].close();
					m_subplots[m+m_dim*n] = null;
				}
		   }
		   if (m_subplots != null)
			   m_subplots=null;
	};	
	
	
};
class CFigReshape
{
	int bDoNow=0;
	int width=0;
	int height=0;
};
class CtmcFigureView  extends View
{
//	private
		int ind; // user figure number
		CtmcSubPlotArray   m_SubPlotList;
		//void InitFigGL (int width, int height) {};
		Canvas canvas;

		//int CreateWorkGLWindow() {};
		//int  KillWorkGLWindow() {};
		int m_bits;
		int m_update;
		CFigReshape m_ReshapeNow = new CFigReshape();

		// This constructor called if View made by program and added with setContentView
		private void InitFigure(Context context,int _ind)
		{
			ind=(_ind); // user figure number
			m_SubPlotList=(null);
			//next=(null);
			m_update=(0);
		
			//m_width=    640;
			//m_height=480;
			
			m_width = getWidth();
			m_height = getHeight();
			
			//m_title=new char[256];
			//sprintf(m_title,"figure No.%d",_ind);
			
			SetReshape(m_width,m_height);
		}
		public CtmcFigureView(Context context) {
	        super(context);
	         InitFigure(context,0);
	      
	      
	        
	    }
		// This constructor called if made from XML file
	    public CtmcFigureView(Context context, AttributeSet attrs) {
	        super(context, attrs);
	        
	        InitFigure(context,0);
	        
	        
	        
	    }
	    /*
		public CtmcFigure(int _ind) {
			
			ind=(_ind); // user figure number
			m_SubPlotList=(null);
			next=(null);m_update=(0);
		
			m_width=640;
			m_height=480;
			//m_title=new char[256];
			//sprintf(m_title,"figure No.%d",_ind);
			
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
			//CreateWorkGLWindow();
			//InitFigGL(m_width,m_height);
			
		};
		*/
	    
		public void close() {}; // destructor

		int m_width;
		int m_height;
		String m_title;
		int GetInd()   { return ind;}
		Canvas GetWin() { return canvas;};
		CtmcSubPlotArray  GetSubplots() {return m_SubPlotList;};
		void CreateSubPlots(int m, int n, int sel) {
			if (m_SubPlotList==null)
			{
				m_SubPlotList =  new CtmcSubPlotArray(m,n,m_width,m_height);
			}
			else
			{
				m_SubPlotList.Redim(m,n,sel);
			}	
		
		};
		

		void DisplaySubPlots(Canvas canvas,int width,int height) { 
			if ( GetSubplots()==null)
			{
				return ;
			}
			else
			{
			 GetSubplots().DrawSubPlots(canvas,width,height);
			}	
		}; // display by GL
		
		//CtmcFigure next;
		void MarkUpdate() {  m_update++; };
		void ClearUpdate() { if(m_update>0) m_update--; };
		int  GetUpdate() {return m_update; };
		void SetCurrentWindow() {};
		void ReshapeWindow() {};
		void SetReshape(int _width, int _height)
			{ m_ReshapeNow.width=_width; m_ReshapeNow.height= _height; m_ReshapeNow.bDoNow=1;  };
		void DoneReshape() {m_ReshapeNow.bDoNow=0;};
		void WinExitFunc( ) {};
		
	@Override
	protected void onDraw(Canvas canvas) {
	        super.onDraw(canvas);
	        
			m_width = getWidth();
			m_height = getHeight();
			
			MyTrans.init(m_width, m_height);
			
	        DisplaySubPlots(canvas,m_width,m_height);
	   
	        
	        //ClearUpdate();
	        //DrawSubPlot();
	    }
}

// Figures engine
/*
class CtmcFigureList
{
public CtmcFigureList() {   };
	
private int num_figures=0;

private  LinkedList<CtmcFigure> lst = new LinkedList<CtmcFigure>();
private	 CtmcFigure  selected_fig=null;
private	int max_fig_ind=0 ; // for automatic indexing

public 	void SetFigSelected(CtmcFigure  ptr) {selected_fig=ptr;};
public	CtmcFigure GetFigSelected() {return selected_fig;};
public	CtmcFigure FindFigByInd(int ind) {  };
public		int SelectFig(int ind) {};   // create new figure and insert to list or select figure
public		void Remove(int ind) {}; // remove window figure

public	int GetNumFigures() {return num_figures;};
public	CtmcFigure GetFirstFig() {return  lst.getFirst(); };
public	void DisplayFig(CtmcFigure p) {};
*/

////////




////////////


class Karman 
{
	public double [] buffer;
	public int buffer_len;
	public Karman(double [] _buf, int _len) {
		buffer = _buf;
		buffer_len = _len;
	}
	/*
	 float[] xi;
	 float[] yi;
	 int ilen ;
	public Karman()
	{
		ilen = 10000;
		xi = new float[ilen];
		yi = new float[ilen];
		int kk;
		float theta=0;
		float r=0;
		for (kk=0;kk<ilen;kk++)
		{
			theta = theta + 0.001f; 
			r = r + 0.0001f;
			yi[kk] = (float) java.lang.Math.sin( theta ) * r + 1;
			xi[kk] = (float) java.lang.Math.cos( theta ) * r + 1;
			
		}
	}
	*/
	
}

/*
class PlotNicView extends View {
    // This constructor called if View made by program and added with setContentView
    public PlotNicView(Context context) {
        super(context);
        
    }
    // This constructor called if made from XML file
    public PlotNicView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }
    
	private Karman mKarman = new Karman();
    private Integer[] mBackgrounds =
        { Color.CYAN, Color.GRAY, Color.LTGRAY,
          Color.MAGENTA, Color.YELLOW, Color.WHITE };
    private Paint[] mForegrounds =
        { makePaint(Color.BLACK), makePaint(Color.BLUE), 
          makePaint(Color.GREEN), makePaint(Color.RED),makePaint(Color.YELLOW) };     
    private Paint makePaint(int color) {
        Paint p = new Paint();
        p.setColor(color);
        
        return(p);
    }
    private void drawKarman(Canvas canvas)
    {
    	int kk;
        int viewWidth = getWidth()/2;
        int viewHeight = getHeight()/2;
  
        Paint circleColor = mForegrounds[1];
        for (kk=0; kk< mKarman.ilen-1 ; kk++)
        {
        	canvas.drawLine(mKarman.xi[kk]*viewWidth, mKarman.yi[kk]*viewHeight, mKarman.xi[kk+1]*viewWidth, mKarman.yi[kk+1]*viewHeight, circleColor);
        }
    }

    
    // Avoid allocating objects in onDraw, especially bitmaps.
    
    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        canvas.drawColor(mBackgrounds[5]);
        int viewWidth = getWidth();
        int viewHeight = getHeight();
        int avgShapeWidth = viewWidth/5;
            drawBarrelCircle(canvas, viewWidth, viewHeight, avgShapeWidth);
            drawKarman(canvas);
    }
       
 
    
    private void drawBarrelCircle(Canvas canvas, int viewWidth, 
                                  int viewHeight, int avgShapeWidth) {
        float x = viewWidth/2;
        float y = viewHeight/2;
        float radius = avgShapeWidth/2;
        Paint circleColor = mForegrounds[4];
        RectF recf = new RectF(0.4f*x, 0.4f*y, 0.6f*x, 0.8f*y) ;
        canvas.drawOval(recf, circleColor); //.drawCircle(x, y, radius, circleColor);
    }
       
}
*/

public class PlotNic extends Activity {
    private CtmcFigureView mDrawingArea;
    private Karman mKarman;
    private PIDData pnPIDData; 
    private int indCrl=0;
    private int nCrl=0;
    private SeekBar selectCrl = null;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_plotnic);
        mDrawingArea  = (CtmcFigureView)findViewById(R.id.drawing_area);
        
        selectCrl = (SeekBar) findViewById(R.id.seek1);
        
        selectCrl.setOnSeekBarChangeListener(new OnSeekBarChangeListener()  {
			int progressChanged = 0;

			public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser){
				progressChanged = progress;
				
				selcrl(this, progress,true);
				
			}

			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
			}

			public void onStopTrackingTouch(SeekBar seekBar) {
				//Toast.makeText(SeekbarActivity.this,"seek bar progress:"+progressChanged, 
				//		Toast.LENGTH_SHORT).show();
			}
		});

        
        Bundle b = getIntent().getExtras();
        
        int numFreqs = b.getInt("numFreqs", 0);
        if (numFreqs==0)
        {
                
        double [] karmanbuf = b.getDoubleArray("karmanbuf");
        int bulen = b.getInt("buflen");
        
        mKarman = new Karman(karmanbuf,bulen);
        Plot(mKarman,mDrawingArea.m_width,mDrawingArea.m_height);
        }
        else
        {
        	// Here build the drawbuffer from the data
        	int numPlants = b.getInt("numPlants", 0);
        	double [] Plants = b.getDoubleArray("Plants");
        	
        	 nCrl = b.getInt("nCrl", 0);
        	double [] Crl = b.getDoubleArray("Crl");
        	int	typeCrl = b.getInt("typeCrl", 0);
    	   	
        	//final int indCrl=0;
            pnPIDData = new PIDData(numFreqs, numPlants, nCrl, typeCrl, Plants, Crl);
            
            int buflen = Ctmc_karman.getKarmanLen(numPlants,numFreqs);
            double [] karmanbuf =  new double[buflen];
            mKarman = new Karman(karmanbuf,buflen);
            
            selectCrl.setMax(nCrl);
           // selectCrl.setProgress(indCrl);
            // The following is done on each change of indCrl
            pnPIDData.prepKarman(mKarman.buffer,mKarman.buffer_len,indCrl); 
            Plot(mKarman,mDrawingArea.m_width,mDrawingArea.m_height);
        }
        
        
    }
    
    /** Handles events for the button. Redraws the ShapeView. */
    
    public void redraw(View clickedButton) {
        mDrawingArea.invalidate();
    }
    public void prevcrl(View clickedButton) {
    	
    	if (indCrl >0)
    	{
    		indCrl--;
        // The following is done on each change of indCrl
        pnPIDData.prepKarman(mKarman.buffer,mKarman.buffer_len,indCrl); 
        Plot(mKarman,mDrawingArea.m_width,mDrawingArea.m_height);

        mDrawingArea.invalidate();
    	}
    }
    public void nextcrl(View clickedButton) {
    	if (indCrl < nCrl-1)
    	{
    		indCrl++;
        // The following is done on each change of indCrl
        pnPIDData.prepKarman(mKarman.buffer,mKarman.buffer_len,indCrl); 
        Plot(mKarman,mDrawingArea.m_width,mDrawingArea.m_height);

        
        mDrawingArea.invalidate();
    	}
    }
    public void selcrl(OnSeekBarChangeListener onSeekBarChangeListener,int progress,boolean fromUser) {
    	indCrl=progress;
    	if (indCrl > nCrl-1)
    	{	indCrl = nCrl-1;
    	}
    	if(indCrl<0)
    		indCrl=0;
    	
        // The following is done on each change of indCrl
        pnPIDData.prepKarman(mKarman.buffer,mKarman.buffer_len,indCrl); 
        Plot(mKarman,mDrawingArea.m_width,mDrawingArea.m_height);

        
        mDrawingArea.invalidate();
    	
    }
    
    
    private void Plot(Karman karman,int m_width, int m_height)
    { // karman is in memory of D.G.Lebedev and his laboratory
    	// plot at the selected subplot at the selected figure from the karman
    	CtmcFigureView _fig  = mDrawingArea; //GetFigSelected();
        CtmcSubPlotArray _subplots  = _fig.GetSubplots();
    	CtmcSubPlot _subplot;

    	if (_subplots == null)
    	{
    		_fig.CreateSubPlots(1,1,1);
    		_subplots  = _fig.GetSubplots();
    	}
    	_subplot = _subplots.GetSelPlot();
    	_subplot.LoadKarmans(karman);

    	//SetFocus(_fig->GetWin());
    	_fig.SetCurrentWindow();
    	_fig.MarkUpdate();
    	//glutSetWindow(_fig->GetWin());
    	//glutPostRedisplay(); // redisplay current window
    };
 /////////
    public static  final int NICHOLS = 1;
    public static  final int BODE = 2;
    public static  final int LINEAR = 0;
    
    public static int StartNicholsPlot(double [] drawbuffer)
    {
    	int ind = 0;
    	drawbuffer[ind++]=0;
    	drawbuffer[ind++]=NICHOLS;
    	return ind; // next index
    }
    public static int StartLinearPlot(double [] drawbuffer)
    {
    	int ind = 0;
    	drawbuffer[ind++]=0;
    	drawbuffer[ind++]=LINEAR;
    	return ind; // next index
    }
    public static int AddNicholsPlot(double [] drawbuffer, int bufoffset,int color,
    		int len,double [] re,double [] im)
    {// e.g Color.BLUE
    	final int mask1 = 1;
    	drawbuffer[0]++;
    	int ind  = bufoffset;
    	
       	drawbuffer[ind++]=len;
    	drawbuffer[ind++]=mask1;
    	drawbuffer[ind++]=color;
    	    	
    	
    	// Phase array
    	double [] ph = new double[len];
    	for (int uu=0; uu<len; uu++)
    	{
    		ph[uu]= CtrlHelper.phase(re[uu],im[uu]); //Math.atan2(im[uu], re[uu])/Math.PI*180.0f;
    	}
    	// Unwrap the phase
    	double [] up = CtrlHelper.unwrap(len,ph,180.0);
    	for (int uu=0; uu<len; uu++)
    	{
    		drawbuffer[ind++]= up[uu] - 360; //TODO CtrlHelper.phase(re[uu],im[uu]); //Math.atan2(im[uu], re[uu])/Math.PI*180.0f;
    	}
    	
    	
    	
    	
    	for (int uu=0; uu<len; uu++)
    	{
    		drawbuffer[ind++]= CtrlHelper.db(re[uu], im[uu]);
    	}
    	return ind;
    }
    public static int AddLinearPlot(double [] drawbuffer, int bufoffset,int color,
    		int len,double [] xx,double [] yy)
    {// e.g Color.BLUE
    	final int mask1 = 1;
    	drawbuffer[0]++;
    	int ind  = bufoffset;
    	
       	drawbuffer[ind++]=len;
    	drawbuffer[ind++]=mask1;
    	drawbuffer[ind++]=color;
    	    	
    	for (int uu=0; uu<len; uu++)
    	{
    		drawbuffer[ind++]=xx[uu];
    	}
    	for (int uu=0; uu<len; uu++)
    	{
    		drawbuffer[ind++]=yy[uu];
    	}
    	return ind;
    }    
}

