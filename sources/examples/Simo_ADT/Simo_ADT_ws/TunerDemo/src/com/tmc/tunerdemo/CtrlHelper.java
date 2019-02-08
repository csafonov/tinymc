package com.tmc.tunerdemo;


public class CtrlHelper {

	public static void ones(int len,double [] re,double [] im)
	{
		for (int kk=0; kk<len; kk++){
			re[kk]=1.0;
			im[kk]=0.0;
		}
	};
	
	public static void pole1(int len,double [] re,double [] im, double [] w, double BndRadSec)
	{
		double d;
		double bb = BndRadSec*BndRadSec;
		
		for (int kk=0; kk<len; kk++){
			d = bb + w[kk]*w[kk];
			re[kk]= bb/d ;
			im[kk]= -BndRadSec*w[kk]/d;
		}
	};
	
	public static void mult(int len,double [] re,double [] im, double [] re2,double [] im2)
	{   // (x+iy)(z+iu)=(x*z-y*u)+i(x*u+y*z)
		double Re,Im;
		for (int kk=0;kk<len;kk++) {
			Re = re[kk]*re2[kk] - im[kk]*im2[kk];
			Im = re[kk]*im2[kk] + im[kk]*re2[kk];
			re[kk]=Re; im[kk]=Im;
		}
	};
	public static void mult(int len,double [] re,double [] im, double [] re2)
	{   // (a+ib)*(c)=(a*c)+i( b*c)
		
		for (int kk=0;kk<len;kk++) {
			re[kk]=re[kk] * re2[kk];
			im[kk]=im[kk] * re2[kk];
		}
	};
	public static void mult(int len,double [] re,double [] im, double C)
	{   // (a+ib)*(c)=(a*c)+i( b*c)
		
		for (int kk=0;kk<len;kk++) {
			re[kk]=re[kk] * C;
			im[kk]=im[kk] * C;
		}
	};
	
	public static void add(int len,double [] re,double [] im, double [] re2,double [] im2)
	{   		
		for (int kk=0;kk<len;kk++) {
			re[kk]= re[kk]+re2[kk];
			im[kk]= im[kk]+im2[kk];
		}
	};
	public static void add(int len,double [] re,double [] im, double [] re2,double C)
	{   		
		for (int kk=0;kk<len;kk++) {
			re[kk]= re[kk]+re2[kk]*C;
		}
	};
	public static void add(int len,double [] re,double [] im, double C)
	{   		
		for (int kk=0;kk<len;kk++) {
			re[kk]= re[kk]+ C;
		}
	};
	public static void div(int len,double [] re,double [] im, double [] re2,double [] im2)
	{   // // (a+ib)/(c+id) = (a+ib)*(c-id)/(c^2+d^2)=
		// =  (a*c+b*d)+i(b*c-a*d)
		double Re,Im,D;
		for (int kk=0;kk<len;kk++) {
			D = re2[kk]*re2[kk] + im2[kk]*im2[kk];
			if (D != 0)
			{
				D = 1/D;
			}
			
			Re = re[kk]*re2[kk] + im[kk]*im2[kk];
			Im = re2[kk]*im[kk] - re[kk]*im2[kk];
			re[kk]=Re*D; im[kk]=Im*D;
		}
	};
	public static void j(int len,double [] re,double [] im)
	{
		for (int kk=0; kk<len; kk++){
			re[kk]=0.0;
			im[kk]=1.0;
		}
	};	
	public static void db(int len,double [] res,double [] re,double [] im)
	{
		double d;
		for (int kk=0; kk<len; kk++){
			d = Math.sqrt(re[kk]*re[kk]+im[kk]*im[kk]);
			  if (d>0)
				  res[kk]=20.0f * Math.log10(d);
			  else
				  res[kk]= -200.0;
		}
	};

	
	public static double db(double re,double  im)
	{
		double d,res;
		
			d = Math.sqrt(re*re+im*im);
			  if (d>0)
				  res=20.0f * Math.log10(d);
			  else
				  res= -200.0;
		return res;
	};
	public static void phase(int len,double [] res,double [] re,double [] im) {
		for (int kk=0; kk<len; kk++){
			res[kk]= Math.atan2(im[kk], re[kk])/Math.PI*180.0f;
		}
	}
	public static double phase(double  re,double im) {
		return	  Math.atan2(im , re )/Math.PI*180.0f;
		
	}	
	
	public static double [] unwrap(int len,double [] x, double mrange)
	{

	int k;
	double prev_val;
	double v;
	double delta;
	
	
		double [] y  = new double [len];
		
			
			prev_val = x[0];
			v=	x[0];
			y[0]=v;
			for (k=1;k<len;k++)
			{
				delta=x[k]-prev_val;
				if (delta>=mrange)
				{
						delta -=2.0F*mrange;
				}
				else
					if (delta<-mrange)
					{
						delta +=2.0F*mrange;
					}
				v +=delta;
				y[k]=v;
				prev_val=x[k];
			}
	return y;
	}
	///////////////
	public static void LinSpace(double a,double b,long n,double [] arr)
	{
		double d ;
		int ind ;
		if( n <= 1 )
		{
			arr[0] = a ;
			return ;
		}
		else
		{
			d = (b-a)/(n-1);
		}
		for( ind = 0 ; ind < n ; ind++ )
		{
		    arr[ind] = a + d*ind ;
		}
	}

	public static double DBB(double TF)
	{
		double dBTF ;
		dBTF    = Math.abs(TF);
		if( dBTF == 0 )		
		{
			dBTF = 2.2204e-016;
		}
		dBTF    = 20*Math.log10(dBTF);
		return dBTF;
	}
	
} // class
