// tmcmath.c
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license.
 * 
  *****************************************************************************/

#undef HW_INTEL_FPATAN
#ifdef  HW_INTEL_FPATAN
_INLINE_
double intel_atan2(double y,double x)
{//FPATAN instruction computes the arctangent of ST(1) divided by ST(0),
 // comparison with MATL gives 4.e10-16. Speed is faster as 1.5
	double z;
	_asm {
		fld [y]
		fld [x]
		fpatan
		fstp z
		fwait
	}
	return z;
}

#endif


#include "tmc.h"
#include "clapack_types.h"

#include  <math.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h> // ANSI compatibility

#include <stdio.h>

void _Catan(double *yre,double *yim,double xre,double xim);


static char *s_module="tmcmath.c";

void _tmcPolyVal(doublecomplex *y, doublecomplex *p,doublecomplex *x,integer N);
/*
#define sqrt	my_sqrt
#define sinh	my_sinh
#define pow		my_pow
#define log10   my_log10
#define log     my_log
#define fmod    my_fmod
#define exp		my_exp
#define cosh    my_cosh
//#define atan2   my_atan2
#define asin	my_asin
#define acos    my_acos
#define tanh    my_tanh
#define tan		my_tan
#define sin		my_sin
#define fabs	my_fabs
#define cos		my_cos
#define atan	my_atan
#define ceil	my_ceil

#define atan2	__ieee754_atan2

#if !defined(__P) || !defined( _TMC_EMBEDDED_  )
#define	__P(p)	p
#endif

extern double acos __P((double));
extern double asin __P((double));
extern double atan __P((double));
extern double atan2 __P((double, double));
extern double cos __P((double));
extern double sin __P((double));
extern double tan __P((double));

extern double cosh __P((double));
extern double sinh __P((double));
extern double tanh __P((double));

extern double exp __P((double));
extern double frexp __P((double, int *));
extern double ldexp __P((double, int));
extern double log __P((double));
extern double log10 __P((double));
extern double modf __P((double, double *));

extern double pow __P((double, double));
extern double sqrt __P((double));

extern double ceil __P((double));
extern double fabs __P((double));
extern double floor __P((double));
extern double fmod __P((double, double));

extern double erf __P((double));
extern double erfc __P((double));
extern double gamma __P((double));
//extern double hypot __P((double, double)); // gluk VC2013
extern int isnan __P((double));
extern int finite __P((double));
extern double j0 __P((double));
extern double j1 __P((double));
extern double jn __P((int, double));
extern double lgamma __P((double));
extern double y0 __P((double));
extern double y1 __P((double));
extern double yn __P((int, double));

extern double acosh __P((double));
extern double asinh __P((double));
extern double atanh __P((double));
*/

//////////// BASIC ////////////////////////
short _tmcIsInfValue(double x)
{
	if (
#if !defined(_TMC_EMBEDDED_) && !defined(_TMC_GNU_LINUX_)
			_fpclass(x)==_FPCLASS_PINF
#else
			isinf(x)
#endif
			|| x==DBL_MAX)
		return 1;
	else
		return 0;

}
short _tmcIsMinusInfValue(double x)
{
	if (
#if !defined(_TMC_EMBEDDED_) && !defined(_TMC_GNU_LINUX_)
			_fpclass(x)==_FPCLASS_NINF
#else
			isinf(x)	// TMC_HAZARD: TODO recognize -Inf from Inf
#endif
			|| x==-DBL_MAX)
		return 1;
	else
		return 0;

}
/////////////////// tmccomplex /////////
struct tmccomplex
{
	double re;
	double im;
};
_INLINE_
double  _tmcCabs(double real,double imag)
{
	double temp;

	if(real < 0)
		real = -real;
	if(imag < 0)
		imag = -imag;
	if(imag > real){
		temp = real;
		real = imag;
		imag = temp;
	}
	if((real+imag) == real)
		return(real);

	temp = imag/real;
	temp = real*sqrt(1.0 + temp*temp);  //OV
	return(temp);
//	return sqrt(re*re+im*im);
}
/*
__inline void _tmcCsqrt(struct tmccomplex *y,double a1,double b1)
{
    //a1=real(x);b1=imag(x);
    //if( b1 == 0.0 ) 
    //    if( a1 < 0.0 )
    //        %{
    //        % // arg is (a,0) where a is negative
    //        result=j*sqrt( -a1 );
    //    else 
    //        %// arg is (a,0) where a is positive
    //        result =  sqrt( a1 );
    //    end
    //else
    //    if( a1 == 0.0 ) 
    //        if( b1 < 0.0 ) 
    //            % // arg is (0,a) where a is negative
    //            t = sqrt( (-b1) / 2 );
    //            imagpart = -t;
    //        else 
    //            % // arg is (0,a) where a is positive
    //            t = sqrt( b1 / 2 );
    //            imagpart = t;
    //        end
    //        result  = t + j* imagpart;
    //    else 
    //        a = abs( a1 );
    //        b = abs( b1 );
    //        if( a >= b ) 
    //            r = b / a;
    //            t = sqrt( a ) * sqrt( ( 1 + sqrt( 1 + r * r ) ) / 2 );
    //        else 
    //            r = a / b;
    //            t = sqrt( b ) * sqrt( ( r + sqrt( 1 + r * r ) ) / 2 );
    //        end
    //        if( a1 >= 0.0 ) 
    //            result = t + j*b1 / ( 2 * t );
    //        else 
    //            if( b1 >= 0 ) 
    //                imagpart = t;
    //            else 
    //                imagpart = -t;
    //            end
    //            realpart = b1 / ( 2 * imagpart );
    //        result = realpart + j*imagpart;
    //        end
    //    end
    //end

double t,r,imagpart,a,b;

	if( b1 == 0.0 )
	{
        if( a1 < 0.0 )
		{
            // (re,0)  re <0
			y->im=sqrt( -a1 );y->re=0.0;
		}
        else
		{
            // (re,0)  re >=0
			y->re =  sqrt( a1 );y->im=0.0;
		}
	}
    else
	{
        if( a1 == 0.0 ) 
		{
            if( b1 < 0.0 ) 
			{
                // (0,im) where im is negative
                t = sqrt( (-b1) / 2 );
                imagpart = -t;
			}
            else
			{
                // (0,im) where im is positive
                t = sqrt( b1 / 2 );
                imagpart = t;
			}
			y->re=t;y->im=imagpart;
		}
        else 
		{
            a = fabs( a1 );
            b = fabs( b1 );
            if( a >= b ) 
			{
                r = b / a;
                t = sqrt( a ) * sqrt( ( 1 + sqrt( 1 + r * r ) ) / 2 );
			}
			else 
			{            
				r = a / b;
                t = sqrt( b ) * sqrt( ( r + sqrt( 1 + r * r ) ) / 2 );
			}
            if( a1 >= 0.0 ) 
			{            
				y->re = t; y->im = b1 / ( 2 * t );
			}
			else
			{
                if( b1 >= 0 ) 
				{             
					imagpart = t;
				}
				else 
				{
					imagpart = -t;
				}
				y->re = b1 / ( 2 * imagpart );
				y->im = imagpart;
			}
		}
	}
    


}
*/

_INLINE_
void _tmcCsqrt(struct tmccomplex *y,double zr,double zi)
{
	double mag, t;

	if( (mag = _tmcCabs(zr, zi)) == 0.)
		y->re = y->im = 0.;
	else if(zr > 0)
		{
		y->re = t = sqrt(0.5 * (mag + zr) );
		t = zi / t;
		y->im = 0.5 * t;
		}
	else
		{
		t = sqrt(0.5 * (mag - zr) );
		if(zi < 0)
			t = -t;
		y->im = t;
		t = zi / t;
		y->re = 0.5 * t;
		}
}

_INLINE_
double _Rdiv(double u,double v)
{// u/v
	return  u/v;
}
void _Cdiv(double *Qr,double *Qi,double ar,double ai,double br,double bi)
{

	double ratio, den;
	double abr, abi, cr;

	if( (abr = br) < 0.)
		abr = - abr;
	if( (abi = bi) < 0.)
		abi = - abi;
	if( abr <= abi )
		{
		if(abi == 0) {
//#ifdef IEEE_COMPLEX_DIVIDE
			double af, bf;
			af = bf = abr;
			if (ai != 0 || ar != 0)
				af = 1.;
			*Qi = *Qr = af / bf;
			return;
//#else
//			sig_die("complex division by zero", 1);
//#endif
			}
		
		ratio = (double)br / bi ;
		den = bi * (1 + ratio*ratio);
		cr = (ar*ratio + ai) / den;
		*Qi = (ai*ratio - ar) / den;
		
		//*Qr  = (ar*(br / bi) + ai) / (bi * (1 + (br / bi)*(br / bi)) );
		//*Qi = (ai*(br / bi) - ar) / (bi * (1 + (br / bi)*(br / bi)) );
		}

	else
		{
		
		ratio = (double)bi / br ;
		den = br * (1 + ratio*ratio);
		cr = (ar + ai*ratio) / den;
		*Qi = (ai - ar*ratio) / den;
		
		//*Qr  = (ar+ ai*(bi / br)) / (br * (1 + (bi / br)*(bi / br)) );
		//*Qi  = (ai- ar*(bi / br)) / (br * (1 + (bi / br)*(bi / br)) );

		}
	*Qr = cr;

//first-quick:
//	double D;
//
//		// (a+ib)/(c+id) = (a+ib)*(c-id)/(c^2+d^2)
//		RealReciprocal(&D,br*br + bi*bi);
//		*Qr = ((ar * br)+(ai * bi))*D;
//		*Qi = (-(ar * bi)+(ai * br))*D;
//	
// another alg:
// Divide two complex numbers and return the real part of the result.
// ( a, b )/( c, d ) = (( a, b )/( d + c*c/d )) * ( c/d, -1 )
/*
    double      tmp;
    double      quo;

    if( fabs( bi ) < fabs( br ) ) {
        tmp = ar;    // convert to (-b,a)/(-d,c)
        ar = - ai;
        ai = tmp;
        tmp = br;
        br = -bi;
        bi = tmp;
    }
    quo = br / bi;
    tmp = quo * br + bi;
    ar /= tmp;
    ai /= tmp;
    br = quo;
    *Qr = ar * br + ai;
    *Qi = ai * br - ar;
*/
//
}
///////////////////////////////////////////////////////

void _tmcAddScalar(tmsMatrix *sum,tmsMatrix *X,tmsMatrix *sclB,short bSignX,short bSignB)
{ // sum is initialized
	long ind;
	long M,N;
	long MN;
	
	double br=0;
	double bi=0;
	
	M =_tmcGetM(X);
	N =_tmcGetN(X);
	MN=M*N;
	br = sclB->m_rData[0]*bSignB;
	if(_tmcHasIm(sclB))
	{
		bi = sclB->m_iData[0]*bSignB;
	}

	if (bSignX>0)
	{
		for (ind=0;ind<MN;ind++)
		{
				sum->m_rData[ind]= X->m_rData[ind]+br;
		}
		if (_tmcHasIm(sum) )
		{
			if(_tmcHasIm(X) )
			{
				for (ind=0;ind<MN;ind++)
				{
							sum->m_iData[ind]= X->m_iData[ind]+bi;
				}
			}
			else
			{
				for (ind=0;ind<MN;ind++)
				{
							sum->m_iData[ind]= bi;
				}
			}
		}
	}
	else
	{
		for (ind=0;ind<MN;ind++)
		{
				sum->m_rData[ind]= -X->m_rData[ind]+br;
		}
		if (_tmcHasIm(sum) )
		{
			if(_tmcHasIm(X) )
			{
				for (ind=0;ind<MN;ind++)
				{
							sum->m_iData[ind]= -X->m_iData[ind]+bi;
				}
			}
			else
			{
				for (ind=0;ind<MN;ind++)
				{
							sum->m_iData[ind]= bi;
				}
			}
		}
	}
}

void _tmcMultByScalar(tmsMatrix *prod,tmsMatrix *X,tmsMatrix *sclB)
{// prod is initialized

	long ind;
	long M,N;
	long MN;
	
	double br=0;
	double bi=0;
	
	M =_tmcGetM(X);
	N =_tmcGetN(X);
	MN=M*N;
	br = sclB->m_rData[0];
	if(_tmcHasIm(sclB))
	{
		bi = sclB->m_iData[0];
	}

		if (_tmcHasIm(prod) )
		{
			if(_tmcHasIm(X) )
			{
				for (ind=0;ind<MN;ind++)
				{
					prod->m_rData[ind] = (X->m_rData[ind] * br)-(X->m_iData[ind] * bi);
					prod->m_iData[ind] = (X->m_rData[ind] * bi)+(X->m_iData[ind] * br);
				}
			}
			else
			{
				for (ind=0;ind<MN;ind++)
				{
					prod->m_rData[ind] = (X->m_rData[ind] * br);
					prod->m_iData[ind] = (X->m_rData[ind] * bi);
				}
			}
		}
		else
		{
			for (ind=0;ind<MN;ind++)
			{
				prod->m_rData[ind] = (X->m_rData[ind] * br);
			}
		}
}

short RealReciprocal(double *result,double D)
{
short claf;
#if !defined(_TMC_EMBEDDED_) && !defined(_TMC_GNU_LINUX_)
	claf = (short)_fpclass(D);
#else
	claf = (short)isfinite(D);
#endif
	*result= 1/D;
	return claf;
}

void _tmcDivByScalar(tmsMatrix *divres,tmsMatrix *X,tmsMatrix *sclB,short bLeftDiv)
{
	long ind;
	long M,N;
	long MN;
	
	double br=0;
	double bi=0;
//	double D;

	M =_tmcGetM(X);
	N =_tmcGetN(X);
	MN=M*N;
	br = sclB->m_rData[0];
	if(_tmcHasIm(sclB))
	{
		bi = sclB->m_iData[0];
	}

	if (bLeftDiv==0)
	{   
		// divres = X/b
		if (_tmcHasIm(divres))
		{
			if (_tmcHasIm(X))
			for (ind=0;ind<MN;ind++)
			{
			_Cdiv(&divres->m_rData[ind],&divres->m_iData[ind],X->m_rData[ind],X->m_iData[ind],br,bi);

						//// (a+ib)/(c+id) = (a+ib)*(c-id)/(c^2+d^2)
						//RealReciprocal(&D,br*br + bi*bi);
						//divres->m_rData[ind] = ((X->m_rData[ind] * br)+(X->m_iData[ind] * bi))*D;
						//divres->m_iData[ind] = (-(X->m_rData[ind] * bi)+(X->m_iData[ind] * br))*D;
			}
			else
			for (ind=0;ind<MN;ind++)
			{
			_Cdiv(&divres->m_rData[ind],&divres->m_iData[ind],X->m_rData[ind],0.,br,bi);

						//// (a+ib)/(c+id) = (a+ib)*(c-id)/(c^2+d^2)
						//RealReciprocal(&D,br*br + bi*bi);
						//divres->m_rData[ind] = ((X->m_rData[ind] * br)+(X->m_iData[ind] * bi))*D;
						//divres->m_iData[ind] = (-(X->m_rData[ind] * bi)+(X->m_iData[ind] * br))*D;
			}
		}
		else
		{
			for (ind=0;ind<MN;ind++)
			{
						//RealReciprocal(&D,br);
						divres->m_rData[ind] =_Rdiv( X->m_rData[ind] , br);
			}
		}


	}
	else
	{
		//divres = b/X
		if (_tmcHasIm(divres))
		{
			if (_tmcHasIm(X))
			for (ind=0;ind<MN;ind++)
			{

			_Cdiv(&divres->m_rData[ind],&divres->m_iData[ind],br,bi,X->m_rData[ind],X->m_iData[ind]);


						//// (a+ib)/(c+id) = (a+ib)*(c-id)/(c^2+d^2)
						//RealReciprocal(&D,X->m_rData[ind]*X->m_rData[ind] + X->m_iData[ind]*X->m_iData[ind]);
						//divres->m_rData[ind] = ((X->m_rData[ind] * br)+(X->m_iData[ind] * bi))*D;
						//divres->m_iData[ind] = (-(X->m_iData[ind] * br)+(X->m_rData[ind] * bi))*D;
			}
			else
			for (ind=0;ind<MN;ind++)
			{

			_Cdiv(&divres->m_rData[ind],&divres->m_iData[ind],br,bi,X->m_rData[ind],0.);

					//	// (a+ib)/(c+id) = (a+ib)*(c-id)/(c^2+d^2)
					//	RealReciprocal(&D,X->m_rData[ind]*X->m_rData[ind] );
					//	divres->m_rData[ind] = ((X->m_rData[ind] * br))*D;
					//	divres->m_iData[ind] = ((X->m_rData[ind] * bi))*D;
			}
		}
		else
		{
			for (ind=0;ind<MN;ind++)
			{
						//RealReciprocal(&D,X->m_rData[ind]);
						divres->m_rData[ind] = _Rdiv(br, X->m_rData[ind]);
			}
		}


	}


}

void  tmcAdd(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b)
{
	long ind;
	long M,N;
	long MN;

	tmcReallocRegister(sum);
	// must check dimentions and type.
		M =_tmcGetM(a);
		N =_tmcGetN(a);
		MN=M*N;

	if (_tmcIsScalar(a))
	{
		_tmcCreateMatrix(sum,_tmcGetM(b),_tmcGetN(b),(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		_tmcAddScalar(sum,b,a,1,1);
	}
	else if (_tmcIsScalar(b))
	{
		_tmcCreateMatrix(sum,M,N,(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		_tmcAddScalar(sum,a,b,1,1);
	}
	else
	{
		if (M != _tmcGetM(b) || N != _tmcGetN(b))
		{
			_tmcRaiseException(err_bad_index,s_module,"tmcAdd","Matrix dimensions must agree.",2,a,b);
			//exit(err_bad_index);
		}

		_tmcCreateMatrix(sum,M,N,(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		for (ind=0;ind<MN;ind++)
		{
				sum->m_rData[ind]= a->m_rData[ind]+b->m_rData[ind];
		}
		if (_tmcHasIm(a) & _tmcHasIm(b))
		{
			for (ind=0;ind<MN;ind++)
			{
						sum->m_iData[ind]= a->m_iData[ind]+b->m_iData[ind];
			}
		}
		else if(_tmcHasIm(a))
		{
			for (ind=0;ind<MN;ind++)
			{
						sum->m_iData[ind]= a->m_iData[ind];
			}
		}
		else if(_tmcHasIm(b))
		{
			for (ind=0;ind<MN;ind++)
			{
						sum->m_iData[ind]= b->m_iData[ind];
			}
		}
	}
}

void  tmcNeg(tmsMatrix *sum,tmsMatrix *a)
{
	long ind;
	long M,N,MN;

	M =_tmcGetM(a);
	N =_tmcGetN(a);
	MN=M*N;

	tmcReallocRegister(sum);
	_tmcCreateMatrix(sum,M,N,_tmcHasIm(a) );
		for (ind=0;ind<MN;ind++)
		{
				sum->m_rData[ind]= (-1.0F) * a->m_rData[ind] ;
		}
	if (_tmcHasIm(a))
	{
		for (ind=0;ind<MN;ind++)
		{
					sum->m_iData[ind]= (-1.0F) * a->m_iData[ind] ;
		}
	}

}

void  tmcSub(tmsMatrix *sum,tmsMatrix *a,tmsMatrix *b)
{
	long ind;
	long M,N;
	long MN;

	tmcReallocRegister(sum);

	// must check dimentions and type.
	M =_tmcGetM(a);
	N =_tmcGetN(a);
	MN=M*N;

	if (_tmcIsScalar(a))
	{
		_tmcCreateMatrix(sum,_tmcGetM(b),_tmcGetN(b),(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		_tmcAddScalar(sum,b,a,-1,1);
	}
	else if (_tmcIsScalar(b))
	{
		_tmcCreateMatrix(sum,M,N,(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		_tmcAddScalar(sum,a,b,1,-1);
	}
	else
	{
		_tmcCreateMatrix(sum,M,N,(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		for (ind=0;ind<MN;ind++)
		{
				sum->m_rData[ind]= a->m_rData[ind]-b->m_rData[ind];
		}
		if (_tmcHasIm(a) & _tmcHasIm(b))
		{
			for (ind=0;ind<MN;ind++)
			{
						sum->m_iData[ind]= a->m_iData[ind]-b->m_iData[ind];
			}
		}
		else if(_tmcHasIm(a))
		{
			for (ind=0;ind<MN;ind++)
			{
						sum->m_iData[ind]= a->m_iData[ind];
			}
		}
		else if(_tmcHasIm(b))
		{
			for (ind=0;ind<MN;ind++)
			{
						sum->m_iData[ind]= -b->m_iData[ind];
			}
		}
	}

}


void  tmcMul(tmsMatrix *prod,tmsMatrix *a,tmsMatrix *b)
{
	long m,n,ind;
	long k;
	long ind1,ind2;

	long Ma,Na,Mb,Nb;

	// must check dimentions and type.
	tmcReallocRegister(prod);
	Ma =_tmcGetM(a);
	Na =_tmcGetN(a);

	Mb =_tmcGetM(b);
	Nb =_tmcGetN(b);


	if (_tmcIsScalar(a))
	{
		_tmcCreateMatrix(prod,Mb,Nb,(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		_tmcMultByScalar(prod,b,a);
	}
	else if (_tmcIsScalar(b))
	{
		_tmcCreateMatrix(prod,Ma,Na,(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		_tmcMultByScalar(prod,a,b);
	}
	else
	{
		_tmcCreateMatrix(prod,Ma,Nb,(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		// must check dimentions and type.
		if(_tmcHasIm(a) & _tmcHasIm(b))
		{
		for (m=0;m<Ma;m++)
			for (n=0;n<Nb;n++)
			{
					ind=n* Ma + m;
					prod->m_rData[ind]=0;
					prod->m_iData[ind]=0;
					for (k=0;k<Na;k++)
					{
						ind1=k* Ma + m;
						ind2=n* Mb + k;
						prod->m_rData[ind] += (a->m_rData[ind1] * b->m_rData[ind2])-(a->m_iData[ind1] * b->m_iData[ind2]);
						prod->m_iData[ind] += (a->m_rData[ind1] * b->m_iData[ind2])+(a->m_iData[ind1] * b->m_rData[ind2]);
					}
			}
		}
		else if(_tmcHasIm(a))
		{
		for (m=0;m<Ma;m++)
			for (n=0;n<Nb;n++)
			{
					ind=n* Ma + m;
					prod->m_rData[ind]=0;
					prod->m_iData[ind]=0;
					for (k=0;k<Na;k++)
					{
						ind1=k* Ma + m;
						ind2=n* Mb + k;
						prod->m_rData[ind] += (a->m_rData[ind1] * b->m_rData[ind2]);
						prod->m_iData[ind] += (a->m_iData[ind1] * b->m_rData[ind2]);
					}
			}
		}
		else if(_tmcHasIm(b))
		{
		for (m=0;m<Ma;m++)
			for (n=0;n<Nb;n++)
			{
					ind=n* Ma + m;
					prod->m_rData[ind]=0;
					prod->m_iData[ind]=0;
					for (k=0;k<Na;k++)
					{
						ind1=k* Ma + m;
						ind2=n* Mb + k;
						prod->m_rData[ind] += (a->m_rData[ind1] * b->m_rData[ind2]);
						prod->m_iData[ind] += (a->m_rData[ind1] * b->m_iData[ind2]);
					}
			}
		}
		else
		{
			for (m=0;m<Ma;m++)
				for (n=0;n<Nb;n++)
				{
						ind=n* Ma + m;
						prod->m_rData[ind]=0;
						for (k=0;k<Na;k++)
						{
							ind1=k* Ma + m;
							ind2=n* Mb + k;
							prod->m_rData[ind] += a->m_rData[ind1] * b->m_rData[ind2];
						}
				}
		}
	}
}
void  tmcMulScalar(tmsMatrix *prod,tmsMatrix *a,tmsMatrix *b)
{
	long ind;
	long M,N;
	long MN;

	// must check dimentions and type.
	tmcReallocRegister(prod);
	M =_tmcGetM(a);
	N =_tmcGetN(a);
	MN=M*N;

	if (_tmcIsScalar(a))
	{
		_tmcCreateMatrix(prod,_tmcGetM(b),_tmcGetN(b),(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		_tmcMultByScalar(prod,b,a);
	}
	else if (_tmcIsScalar(b))
	{
		_tmcCreateMatrix(prod,M,N,(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		_tmcMultByScalar(prod,a,b);
	}
	else
	{
		_tmcCreateMatrix(prod,M,N,(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		if (_tmcHasIm(a) & _tmcHasIm(b))
		{
			for (ind=0;ind<MN;ind++)
			{
						// (x+iy)(z+iu)=(x*z-y*u)+i(x*u+y*z)
						prod->m_rData[ind] = (a->m_rData[ind] * b->m_rData[ind])-(a->m_iData[ind] * b->m_iData[ind]);
						prod->m_iData[ind] = (a->m_rData[ind] * b->m_iData[ind])+(a->m_iData[ind] * b->m_rData[ind]);
			}
		}
		else if(_tmcHasIm(a))
		{
			for (ind=0;ind<MN;ind++)
			{
						prod->m_rData[ind] = (a->m_rData[ind] * b->m_rData[ind]);
						prod->m_iData[ind] = (a->m_iData[ind] * b->m_rData[ind]);
			}
		}
		else if(_tmcHasIm(b))
		{
			for (ind=0;ind<MN;ind++)
			{
						prod->m_rData[ind] = (a->m_rData[ind] * b->m_rData[ind]);
						prod->m_iData[ind] = (a->m_rData[ind] * b->m_iData[ind]);
			}
		}
		else
		{
			for (ind=0;ind<MN;ind++)
			{
					prod->m_rData[ind]= a->m_rData[ind]*b->m_rData[ind];
			}
		}
	}
}

void tmcDivScalar(tmsMatrix *divres,tmsMatrix *a,tmsMatrix *b)
{
	long ind;
	long M,N;
	long MN;
	double D;

	// must check dimentions and type.
	tmcReallocRegister(divres);
	M =_tmcGetM(a);
	N =_tmcGetN(a);
	MN=M*N;

	if (_tmcIsScalar(a))
	{
		_tmcCreateMatrix(divres,_tmcGetM(b),_tmcGetN(b),(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		_tmcDivByScalar(divres,b,a,1);
	}
	else if (_tmcIsScalar(b))
	{
		_tmcCreateMatrix(divres,M,N,(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		_tmcDivByScalar(divres,a,b,0);
	}
	else
	{
		_tmcCreateMatrix(divres,M,N,(short)(_tmcHasIm(a) | _tmcHasIm(b)));
		if (_tmcHasIm(a) && _tmcHasIm(b))
		{
				for (ind=0;ind<MN;ind++)
				{
						_Cdiv(&divres->m_rData[ind],&divres->m_iData[ind],
							a->m_rData[ind],a->m_iData[ind],b->m_rData[ind],b->m_iData[ind]);
							//// (a+ib)/(c+id) = (a+ib)*(c-id)/(c^2+d^2)
							//RealReciprocal(&D,b->m_rData[ind]*b->m_rData[ind] + b->m_iData[ind]*b->m_iData[ind]);
							//divres->m_rData[ind] = ((a->m_rData[ind] * b->m_rData[ind])+(a->m_iData[ind] * b->m_iData[ind]))*D;
							//divres->m_iData[ind] = (-(a->m_rData[ind] * b->m_iData[ind])+(a->m_iData[ind] * b->m_rData[ind]))*D;
				}
		}
		else
		{
			if (_tmcHasIm(a))
			{
				for (ind=0;ind<MN;ind++)
				{
							//RealReciprocal(&D,b->m_rData[ind]);
							D = _Rdiv(1.,b->m_rData[ind]);
							divres->m_rData[ind] =  a->m_rData[ind] * D;
							divres->m_iData[ind] =  a->m_iData[ind] * D;
				}
			}
			else if (_tmcHasIm(b))
			{
				for (ind=0;ind<MN;ind++)
				{
					_Cdiv(&divres->m_rData[ind],&divres->m_iData[ind],
							a->m_rData[ind],0.,b->m_rData[ind],b->m_iData[ind]);

					//		RealReciprocal(&D,b->m_rData[ind]*b->m_rData[ind] + b->m_iData[ind]*b->m_iData[ind]);
					//		divres->m_rData[ind] = (a->m_rData[ind] * b->m_rData[ind])*D;
					//		divres->m_iData[ind] = (-a->m_rData[ind] * b->m_iData[ind])*D;
				}
			}
			else
			{
				for (ind=0;ind<MN;ind++)
				{
					//RealReciprocal(&D,b->m_rData[ind]);
					D = _Rdiv(1., b->m_rData[ind]);
					divres->m_rData[ind]= a->m_rData[ind] * D;
				}
			}
		}
	}

}


void tmcdiag(long nout,long ninput,tmsMatrix *y,tmsMatrix *d)
{ // Restriction: The only syntax: y=diag(d), d= vector
	long m,M,N,K;

 if (_tmcIsMatrix(d))
 {
    // d is matrix
	// y = column vector from  the elements of the n-th diagonal of X,(restriction: n=0)
	M=_tmcGetM(d);
	N=_tmcGetN(d);
	K = N;
	if (M<N)
		K=M;

	_tmcCreateMatrix(y,K,1,_tmcHasIm(d));
	for (m=0;m<K;m++)
	{
		y->m_rData[m] = d->m_rData[m + M*m];
		if (_tmcHasIm(d))
		{
			y->m_iData[m] = d->m_iData[m + M*m];
		}
	}
 }
 else
 {
	// d is a vector with M components
	// y =  square matrix  order M with the elements of d on the n-th diagonal , (restriction: n=0)

	M = tmcNumElem(d);
	_tmcCreateMatrix(y,M,M,_tmcHasIm(d));
	for (m=0;m<M;m++)
	{
		y->m_rData[m+m*M]=d->m_rData[m];
		if (_tmcHasIm(d))
		{
			y->m_iData[m+m*M]=d->m_iData[m];
		}
	}
 }
}

/**
	\brief Returns Tr(A)= sum(diag(d));
*/
void tmctrace(long nout,long ninput,tmsMatrix *y,tmsMatrix *d)
{ 
	long   m,M,N,K;
	double Dr,Di;

	M=_tmcGetM(d);
	N=_tmcGetN(d);
	K = N;
	if (M<N)
		K=M;

	Dr=0;
	Di=0;
	_tmcCreateMatrix(y,1,1,_tmcHasIm(d));
	for (m=0;m<K;m++)
	{
		Dr += d->m_rData[m];
		if (_tmcHasIm(d))
		{
			Di += d->m_iData[m];
		}
	}
	y->m_rData[0] = Dr;
	if (_tmcHasIm(d))
	{
		y->m_iData[0] = Di;
	}
}

void tmcinv(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{ // y = inv(x) = x\I thats solve x*y=I
long m;
tmsMatrix *E;
long M;

		M=_tmcGetM(x);
		if (M != _tmcGetN(x))
		{
			_tmcRaiseException(err_invalid_dimentions,s_module,"inv","inv(x), x not square",1,x);
		}
		E=tmcNewMatrix();
		_tmcCreateMatrix(E,M,M,tmcREAL);
		for (m=0;m<M;m++)
			E->m_rData[m+M*m]=1.0;

		if ( (_tmcHasIm(x)==0))
		{
			_tmcRealLeftDiv(y,x,E);
		}
		else
		{
				_tmcComplexLeftDiv(y,x,E);
		}
		_tmcClearRegister(E);
		MYFREE(E);

}

void tmcLeftDiv(tmsMatrix *X,tmsMatrix *A,tmsMatrix *B)
{// A\B

	tmcReallocRegister(X);

	if (_tmcIsScalar(A))
	{
		_tmcCreateMatrix(X,_tmcGetM(B),_tmcGetN(B),(short)(_tmcHasIm(A) | _tmcHasIm(B)));
		_tmcDivByScalar(X,B,A,0);
	}
	else if (_tmcIsScalar(B))
	{
		_tmcCreateMatrix(X,_tmcGetM(A),_tmcGetN(A),(short)(_tmcHasIm(A) | _tmcHasIm(B)));
		_tmcDivByScalar(X,A,B,1);
	}
	else
	{
		if ((_tmcHasIm(A)==0)	&& (_tmcHasIm(B)==0))
		{
			_tmcRealLeftDiv(X,A,B);
		}
		else
		{
				_tmcComplexLeftDiv(X,A,B);
		}
	}

}


void tmcDiv(tmsMatrix *X,tmsMatrix *A,tmsMatrix *B)
{// A/B = (B'\A')'
	
//	A=_tmcGetByRef(A);
//	B=_tmcGetByRef(B);
//	X=_tmcGetByRef(X);

	//HAZARD: must optimize

	tmcReallocRegister(X);

	if (_tmcIsScalar(A))
	{
		_tmcCreateMatrix(X,_tmcGetM(B),_tmcGetN(B),(short)(_tmcHasIm(A) | _tmcHasIm(B)));
		_tmcDivByScalar(X,B,A,1);
	}
	else if (_tmcIsScalar(B))
	{
		_tmcCreateMatrix(X,_tmcGetM(A),_tmcGetN(A),(short)(_tmcHasIm(A) | _tmcHasIm(B)));
		_tmcDivByScalar(X,A,B,0);
	}
	else
	{
	_tmcTransposeMatrix(A,0);
	_tmcTransposeMatrix(B,0);
		if ((_tmcHasIm(A)==0)	&& (_tmcHasIm(B)==0))
		{
			_tmcRealLeftDiv(X,B,A);
		}
		else
		{
				_tmcComplexLeftDiv(X,B,A);
		}
	_tmcTransposeMatrix(X,0);
	_tmcTransposeMatrix(A,0);
	_tmcTransposeMatrix(B,0);
	}
}


double _matmod(double x,double y)
/*
MOD    Modulus after division.
   MOD(x,y) is x - n.*y where n = floor(x./y) if y ~= 0.  If y is not an
    integer and the quotient x./y is within roundoff error of an integer,
    then n is that integer.  By convention, MOD(x,0) is x.  The input
    x and y must be real arrays of the same size, or real scalars.
 
    The statement "x and y are congruent mod m" means mod(x,m) == mod(y,m).
 
    MOD(x,y) has the same sign as y while REM(x,y) has the same sign as x.
    MOD(x,y) and REM(x,y) are equal if x and y have the same sign, but
    differ by y if x and y have different signs.
*/
{
	if (y==0)
		return x;
	else
		return x-floor(x/y)*y;

}
double _matrem(double x,double y)
/*
REM    Remainder after division.
    REM(x,y) is x - n.*y where n = fix(x./y) if y ~= 0.  If y is not an
    integer and the quotient x./y is within roundoff error of an integer,
    then n is that integer.  By convention, REM(x,0) is NaN.  The input
    x and y must be real arrays of the same size, or real scalars.
 
    REM(x,y) has the same sign as x while MOD(x,y) has the same sign as y.
    REM(x,y) and MOD(x,y) are equal if x and y have the same sign, but
    differ by y if x and y have different signs.
*/
{
	return fmod(x,y);
	//fmod returns the floating-point remainder of x / y.
	//If the value of y is 0.0, fmod returns a quiet NaN.
	// The fmod function calculates the floating-point remainder f of x / y such that x = i * y + f,
	// where i is an integer, f has the same sign as x, and the absolute value of f is less than
	// the absolute value of y.
}


void tmcmod(long nout,long ninput,tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2)
{
	long M,N,MN;
	long ind;

	M =_tmcGetM(src1);
	N =_tmcGetN(src1);
	MN=M*N;

	_tmcCreateMatrix(matres,M,N,_tmcHasIm(src1) );
	for (ind=0;ind<MN;ind++)
	{
		matres->m_rData[ind]= _matmod( src1->m_rData[ind] , src2->m_rData[0]);
	}

}
void tmcrem(long nout,long ninput,tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2)
{
	long M,N,MN;
	long ind;

	M =_tmcGetM(src1);
	N =_tmcGetN(src1);
	MN=M*N;

	_tmcCreateMatrix(matres,M,N,_tmcHasIm(src1) );
	for (ind=0;ind<MN;ind++)
	{
		matres->m_rData[ind]= _matrem( src1->m_rData[ind] , src2->m_rData[0]);
	}

}

void tmccos(long nout,long ninput,tmsMatrix *matres,tmsMatrix *x)
{//CHECKED
	long M,N,MN;
	long ind;
	double a,b;

	M =_tmcGetM(x);
	N =_tmcGetN(x);
	MN=M*N;

	_tmcClearRegister(matres);
	_tmcCreateMatrix(matres,M,N,_tmcHasIm(x) );
	if (_tmcHasIm(x)==0)
	{
		for (ind=0;ind<MN;ind++)
		{
			matres->m_rData[ind]= cos( x->m_rData[ind] );
		}
	}
	else
	{ 
		// cos(z)=0.5(exp(a)+exp(-a))cos(b) + i 0.5(exp(a)-exp(-a))sin(b)
		// where a=-imag(z), b= real(z)
		for (ind=0;ind<MN;ind++)
		{
			a = -x->m_iData[ind];
			b = x->m_rData[ind];
			matres->m_rData[ind]= cos(b)*0.5F*(exp(a)+exp(-a));
			matres->m_iData[ind]= sin(b)*0.5F*(exp(a)-exp(-a));
		}
	}
}
void tmcsin(long nout,long ninput,tmsMatrix *matres,tmsMatrix *x)
{//CHECKED
	long M,N,MN;
	long ind;
	double a,b;
	_tmcClearRegister(matres);

	M =_tmcGetM(x);
	N =_tmcGetN(x);
	MN=M*N;

	_tmcCreateMatrix(matres,M,N,_tmcHasIm(x) );
	if (_tmcHasIm(x)==0)
	{
		for (ind=0;ind<MN;ind++)
		{
			matres->m_rData[ind]= sin( x->m_rData[ind] );
		}
	}
	else
	{
		// sin(z)=0.5*(exp(a)+exp(-a))*sin(b) + i*0.5*(exp(-a)-exp(a))*cos(b)
		// where a=-imag(z), b= real(z)
		for (ind=0;ind<MN;ind++)
		{
			a = -x->m_iData[ind];
			b = x->m_rData[ind];
			matres->m_rData[ind]= sin(b)*0.5F*(exp(a)+exp(-a));
			matres->m_iData[ind]= cos(b)*0.5F*(exp(-a)-exp(a));
		}
	}
}
void tmctan(long nout,long ninput,tmsMatrix *matres,tmsMatrix *x)
{
	long M,N,MN;
	long ind;
	double a,b;
	double D;
	double a1,a2,b1,b2;
	double aa,bb;

	_tmcClearRegister(matres);

	M =_tmcGetM(x);
	N =_tmcGetN(x);
	MN=M*N;

	_tmcCreateMatrix(matres,M,N,_tmcHasIm(x) );
	if (_tmcHasIm(x)==0)
	{
		for (ind=0;ind<MN;ind++)
		{
			matres->m_rData[ind]= tan( x->m_rData[ind] );
		}
	}
	else
	{
		// tan(z)=sin(z)/cos(z)
		// sin(z)=0.5*(exp(a)+exp(-a))*sin(b) + i*0.5*(exp(-a)-exp(a))*cos(b)
		// cos(z)=0.5(exp(a)+exp(-a))cos(b) + i 0.5(exp(a)-exp(-a))sin(b)
		// where a=-imag(z), b= real(z)
		for (ind=0;ind<MN;ind++)
		{
			a = -x->m_iData[ind];
			b = x->m_rData[ind];
			aa=exp(a);
			bb=exp(-a);
			a1=aa+bb;
			b1=aa-bb;
			a2=cos(b);
			b2=sin(b);

			//RealReciprocal(&D,(a2*a1)*(a2*a1)+(b1*b2)*(b1*b2));


			//b=real(x);
			//a=-imag(x);
			//a1=exp(a)+exp(-a);
			//b1=exp(a)-exp(-a);
			//a2=cos(b);
			//b2=sin(b);
			//D=(a2*a1)^2+(b2*b1)^2;
			//y = (a2*b2*(a1*a1-b1*b1) -i*a1*b1*( a2*a2+b2*b2 ))/D;

			//matres->m_rData[ind]= a2*b2*(a1*a1-b1*b1)*D;
			//matres->m_iData[ind]= -a1*b1*( a2*a2+b2*b2 )*D;

			RealReciprocal(&D,(a2*a2)*(a1/b1)+(b2*b2)*(b1/a1)); 

			matres->m_rData[ind]= a2*b2*((a1/b1)-(b1/a1))*D;
			matres->m_iData[ind]= -( a2*a2+b2*b2 )*D;


		}
	}
}

void tmcpolyval(long nout,long ninput,tmsMatrix *y,tmsMatrix *p,tmsMatrix *x)
{

	long M,N,MN;
	long ind;
	long deg;

	doublecomplex *pol;
	doublecomplex parg;
	doublecomplex pval;

	M =_tmcGetM(x);
	N =_tmcGetN(x);
	MN=M*N;
	deg = tmcNumElem(p)-1;
	pol = MYMALLOC(sizeof(doublecomplex)*(deg+1));
	for (ind=0;ind<=deg;ind++)
	{
		pol[ind].r=p->m_rData[ind];
		if (_tmcHasIm(p))
		{
			pol[ind].i=p->m_iData[ind];
		}
		else
			pol[ind].i= 0;
	}

	_tmcClearRegister(y);
	_tmcCreateMatrix(y,M,N,(short)(_tmcHasIm(x) | _tmcHasIm(p)));
	for (ind=0;ind<MN;ind++)
	{
		parg.r= x->m_rData[ind];
		if (_tmcHasIm(x))
		{
			parg.i= x->m_iData[ind];
		}
		else
		{
			parg.i=0;
		}
		_tmcPolyVal(&pval, pol,&parg,deg);
		y->m_rData[ind]=pval.r;
		if (_tmcHasIm(y))
		{
				y->m_iData[ind]=pval.i;
		}
	}
	MYFREE(pol);
}
void tmclog10(long nout,long ninput,tmsMatrix *y,tmsMatrix *x)
{
	long M,N,MN;
	long ind;

	_tmcClearRegister(y);

	M =_tmcGetM(x);
	N =_tmcGetN(x);
	MN=M*N;

	_tmcCreateMatrix(y,M,N,_tmcHasIm(x) );
	if (_tmcHasIm(x))
	// ln (x ) = ln |x| + i * arg(x)
	{
		for (ind=0;ind<MN;ind++)
		{
			y->m_rData[ind]= log10( _tmcCabs(x->m_rData[ind],x->m_iData[ind]));
			y->m_iData[ind]= atan2( x->m_iData[ind], x->m_rData[ind])*0.43429448190325;
		}
	}
	else
	{
		for (ind=0;ind<MN;ind++)
		{
			if (x->m_rData[ind]>=0)
				y->m_rData[ind]= log10(fabs( x->m_rData[ind]) );
			else
			{
				// x<0: log10 (x) = log10(-x) + i * pi / log(10)
					y->m_rData[ind]= log10(  -x->m_rData[ind]  );
					if ( _tmcHasIm(y)==0)
					{
						_tmcForceComplexMatrix(y);
					}
					y->m_iData[ind]= 1.36437635384184;
			}
		}
	}
}
void tmclog(long nout,long ninput,tmsMatrix *y,tmsMatrix *x)
{
	long M,N,MN;
	long ind;

	_tmcClearRegister(y);

	M =_tmcGetM(x);
	N =_tmcGetN(x);
	MN=M*N;

	_tmcCreateMatrix(y,M,N,_tmcHasIm(x) );
	if (_tmcHasIm(x))
	// ln (x ) = ln |x| + i * arg(x)
	{
		for (ind=0;ind<MN;ind++)
		{
			y->m_rData[ind]= log(_tmcCabs(x->m_rData[ind],x->m_iData[ind]) ) ;
			y->m_iData[ind]= atan2( x->m_iData[ind], x->m_rData[ind]);
		}
	}
	else
	{
		for (ind=0;ind<MN;ind++)
		{
			if (x->m_rData[ind]>=0)
				y->m_rData[ind]= log(fabs( x->m_rData[ind]) );
			else
			{
				// x<0: log (x) = log(-x) + i * pi 
					y->m_rData[ind]= log(  -x->m_rData[ind]  );
					if ( _tmcHasIm(y)==0)
					{
						_tmcForceComplexMatrix(y);
					}
					y->m_iData[ind]= 3.14159265358979;
			}
		}
	}
}

void tmcexp(long nout,long ninput,tmsMatrix *y,tmsMatrix *x)
{
	long M,N,MN;
	long ind;

	_tmcClearRegister(y);

	M =_tmcGetM(x);
	N =_tmcGetN(x);
	MN=M*N;

	_tmcCreateMatrix(y,M,N,_tmcHasIm(x) );
	if (_tmcHasIm(x) )
	{
		for (ind=0;ind<MN;ind++)
		{
			{
				y->m_rData[ind]	= exp( x->m_rData[ind] ) * cos(x->m_iData[ind]);
				y->m_iData[ind]	= exp( x->m_rData[ind] ) * sin(x->m_iData[ind]);
			}
		}
	}
	else
	{
		for (ind=0;ind<MN;ind++)
		{
			y->m_rData[ind]= exp( x->m_rData[ind] );
		}
	}
}

void tmcsum(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{ 
	long m,n,MN,M,N,offMN;
	double Sr,Si;
	//For vectors, SUM(X) is the sum of the elements of X.
	//For matrices, SUM(X) is a row vector with the sum over each column.
	if (ninput>1)
			_tmcRaiseException(err_bad_index,s_module,"sum","sum(X,n) unsupported ninput=2",1,x);
	if (_tmcIsMatrix(x))
	{
		N=_tmcGetN(x);
		M=_tmcGetM(x);

		_tmcCreateMatrix(y,1,_tmcGetN(x),_tmcHasIm(x));
		for (n=0;n<N;n++)
		{
				Sr=0;Si=0;
				offMN = n*M;
				for (m=0;m<M;m++)
					Sr += x->m_rData[offMN+m];

				if (_tmcHasIm(x))
				{
					for (m=0;m<M;m++)
						Si += x->m_iData[offMN+m];
				}
				y->m_rData[n]=Sr;
				if (_tmcHasIm(x))
					y->m_iData[n]=Si;
		}
	}
	else
	{
		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,1,1,_tmcHasIm(x));
		Sr=0;Si=0;
		for (n=0;n<MN;n++)
			Sr += x->m_rData[n];

		if (_tmcHasIm(x))
		{
			for (n=0;n<MN;n++)
				Si += x->m_iData[n];
		}
		y->m_rData[0]=Sr;
		if (_tmcHasIm(x))
			y->m_iData[0]=Si;
	}

}
void tmcprod(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{ 
	long m,n,MN,M,N,offMN;
	double Pr,Pi;
	//For vectors, PROD(X) is the product of the elements of X.
	//For matrices, PROD(X) is a row vector with the product over each column.
	if (ninput>1)
			_tmcRaiseException(err_bad_index,s_module,"prod","prod(X,n) unsupported ninput=2",1,x);
	if (_tmcIsMatrix(x))
	{
		N=_tmcGetN(x);
		M=_tmcGetM(x);

		_tmcCreateMatrix(y,1,_tmcGetN(x),_tmcHasIm(x));
		for (n=0;n<N;n++)
		{
				Pr=1;
				offMN = n*M;

				if (_tmcHasIm(x))
				{
					Pi=1;
					for (m=0;m<M;m++)
					{
						Pi =Pr * x->m_iData[offMN+m] + Pi * x->m_rData[offMN+m];
						Pr =Pr * x->m_rData[offMN+m] - Pi * x->m_iData[offMN+m];
					}
				}
				else
				{
					Pi=0;
				for (m=0;m<M;m++)
					Pr *= x->m_rData[offMN+m];
				}
				y->m_rData[n]=Pr;
				if (_tmcHasIm(x))
					y->m_iData[n]=Pi;
		}
	}
	else
	{
		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,1,1,_tmcHasIm(x));
		Pr=1;
		Pi=1;//BUG 11.08.2011

		if (_tmcHasIm(x))
		{
			for (n=0;n<MN;n++)
			{
				Pi =Pr * x->m_iData[n] + Pi * x->m_rData[n];
				Pr =Pr * x->m_rData[n] - Pi * x->m_iData[n];
			}
		}
		else
		{
			Pi=0;
		for (n=0;n<MN;n++)
			Pr *= x->m_rData[n];
		}
		y->m_rData[0]=Pr;
		if (_tmcHasIm(x))
			y->m_iData[0]=Pi;
	}

}



// MINIMUM utils
double _tmcMinVec(long *ind,double *re,long len)
{ // find element with minimal real() 
  // Restriction: only real part is regarded and the result is always real.
long k;
double Res;

	Res=re[0];
	*ind=0;

	for (k=1;k<len;k++)
	{
		if (re[k]<Res)
		{
			*ind=k;Res=re[k];
		}
	}
	return Res;
}
void _tmcMinVecScalar(double *res,double *re,double scalar,long len)
{ // res = min(re,scalar)
long k;
	for (k=0;k<len;k++)
	{
		res[k]= (re[k]>scalar ? scalar:re[k]);
	}
}
void _tmcMinVecVec(double *res,double *re1,double *re2,long len)
{ // res = min(re1,re2)
long k;
	for (k=0;k<len;k++)
	{
		res[k]= (re1[k]>re2[k] ? re2[k]:re1[k]);
	}
}



void tmcmin(long nout,long ninput, tmsMatrix *y1,tmsMatrix *y2,tmsMatrix *x1,tmsMatrix *x2,tmsMatrix *d)
{ // supported syntax:
  // [V,I]=min(A), A=vector or matrix (row of minimums)
  // [V]=min(A)
  // [V]=min(A,B), A,B = matrixes of the same sizes or one of them scalar
long ind;
long n;
long M,N;
	if (ninput == 2)
	{
		// [V]=min(A,B), A,B = matrixes of the same sizes or one of them scalar
		if (_tmcIsScalar(x1))
		{
			// V=min(a,B)
			_tmcCreateMatrix(y1,_tmcGetM(x2),_tmcGetN(x2),tmcREAL);
			_tmcMinVecScalar(y1->m_rData,x2->m_rData,x1->m_rData[0],tmcNumElem(x2));
		}
		else
		{
			if (_tmcIsScalar(x2))
			{ // V=min(A,b)
				_tmcCreateMatrix(y1,_tmcGetM(x1),_tmcGetN(x1),tmcREAL);
				_tmcMinVecScalar(y1->m_rData,x1->m_rData,x2->m_rData[0],tmcNumElem(x1));
			}
			else
			{ // V=min(A,B) for matrices
				N = _tmcGetN(x1);
				M = _tmcGetM(x1);
				if (N != _tmcGetN(x2) && M != _tmcGetM(x2))
				{
						_tmcRaiseException(err_invalid_dimentions,s_module,"min","Matrix dimensions must agree",2,x1,x2);
				}
				_tmcCreateMatrix(y1,M,N,tmcREAL);
				_tmcMinVecVec(y1->m_rData,x1->m_rData,x2->m_rData,tmcNumElem(x1));
 			}
		}
	}
	else
		if (ninput == 1)
		{
		 // [V,I]=min(A), A=vector or matrix (row of minimums)
		 if (_tmcIsMatrix(x1))
		 {
				N = _tmcGetN(x1);
				M = _tmcGetM(x1);
				_tmcCreateMatrix(y1,1,N,tmcREAL);
				if (nout>1)
				{
					_tmcCreateMatrix(y2,1,N,tmcREAL);
				}
				for (n=0;n<N;n++)
				{
					y1->m_rData[n]=_tmcMinVec(&ind,&x1->m_rData[n*M],M);
					if (nout>1)
					{
						y2->m_rData[n]=1+ind;
					}
				}
		 }
		 else
		 {
				_tmcCreateMatrix(y1,1,1,tmcREAL);
				if (nout>1)
				{
					_tmcCreateMatrix(y2,1,1,tmcREAL);
				}
				y1->m_rData[0]=_tmcMinVec(&ind,&x1->m_rData[0],tmcNumElem(x1));
				if (nout>1)
				{
					y2->m_rData[0]=1+ind;
				}
		 }
		}
		else
			_tmcRaiseException(err_bad_index,s_module,"min","unsupported ninput",0,NULL);

		
}

// MAXIMUM utils
double _tmcMaxVec(long *ind,double *re,long len)
{ // find element with maximal real() 
  // Restriction: only real part is regarded and the result is always real.
long k;
double Res;

	Res=re[0];
	*ind=0;
	for (k=1;k<len;k++)
	{
		if (re[k]>Res)
		{
			*ind=k;Res=re[k];
		}
	}
	return Res;
}
void _tmcMaxVecScalar(double *res,double *re,double scalar,long len)
{ // res = max(re,scalar)
long k;
	for (k=0;k<len;k++)
	{
		res[k]= (re[k]<scalar ? scalar:re[k]);
	}
}
void _tmcMaxVecVec(double *res,double *re1,double *re2,long len)
{ // res = max(re1,re2)
long k;
	for (k=0;k<len;k++)
	{
		res[k]= (re1[k]<re2[k] ? re2[k]:re1[k]);
	}
}

void tmcmax(long nout,long ninput, tmsMatrix *y1,tmsMatrix *y2,tmsMatrix *x1,tmsMatrix *x2,tmsMatrix *d)
{
  // [V,I]=max(A), A=vector or matrix (row of maximums)
  // [V]=max(A)
  // [V]=max(A,B), A,B = matrixes of the same sizes or one of them scalar
long ind;
long n;
long M,N;
	if (ninput == 2)
	{
		// [V]=max(A,B), A,B = matrixes of the same sizes or one of them scalar
		if (_tmcIsScalar(x1))
		{
			// V=max(a,B)
			_tmcCreateMatrix(y1,_tmcGetM(x2),_tmcGetN(x2),tmcREAL);
			_tmcMaxVecScalar(y1->m_rData,x2->m_rData,x1->m_rData[0],tmcNumElem(x2));
		}
		else
		{
			if (_tmcIsScalar(x2))
			{ // V=max(A,b)
				_tmcCreateMatrix(y1,_tmcGetM(x1),_tmcGetN(x1),tmcREAL);
				_tmcMaxVecScalar(y1->m_rData,x1->m_rData,x2->m_rData[0],tmcNumElem(x1));
			}
			else
			{ // V=max(A,B) for matrices
				N = _tmcGetN(x1);
				M = _tmcGetM(x1);
				if (N != _tmcGetN(x2) && M != _tmcGetM(x2))
				{
						_tmcRaiseException(err_invalid_dimentions,s_module,"max","Matrix dimensions must agree",2,x1,x2);
				}
				_tmcCreateMatrix(y1,M,N,tmcREAL);
				_tmcMaxVecVec(y1->m_rData,x1->m_rData,x2->m_rData,tmcNumElem(x1));
 			}
		}
	}
	else
		if (ninput == 1)
		{
		 // [V,I]=max(A), A=vector or matrix (row of maximums)
		 if (_tmcIsMatrix(x1))
		 {
				N = _tmcGetN(x1);
				M = _tmcGetM(x1);
				_tmcCreateMatrix(y1,1,N,tmcREAL);
				if (nout>1)
				{
					_tmcCreateMatrix(y2,1,N,tmcREAL);
				}
				for (n=0;n<N;n++)
				{
					y1->m_rData[n]=_tmcMaxVec(&ind,&x1->m_rData[n*M],M);
					if (nout>1)
					{
						y2->m_rData[n]=1+ind;
					}
				}
		 }
		 else
		 {
				_tmcCreateMatrix(y1,1,1,tmcREAL);
				if (nout>1)
				{
					_tmcCreateMatrix(y2,1,1,tmcREAL);
				}
				if (tmcNumElem(x1)==0)
					return;
				y1->m_rData[0]=_tmcMaxVec(&ind,&x1->m_rData[0],tmcNumElem(x1));
				if (nout>1)
				{
					y2->m_rData[0]=1+ind;
				}
		 }
		}
		else
			_tmcRaiseException(err_bad_index,s_module,"max","unsupported ninput",0,NULL);
}

void tmcfloor(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
long MN,k;

	_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),_tmcHasIm(x));
	MN=tmcNumElem(x);
	for (k=0;k<MN;k++)
	{
		y->m_rData[k] = floor(x->m_rData[k]);
	}
	if (_tmcHasIm(x))
		for (k=0;k<MN;k++)
		{
			y->m_iData[k] = floor(x->m_iData[k]);
		}
}

double _mfix(double x)
{
	if (x>=0)
		return floor(x);
	else
		return -floor(-x);

}

void tmcfix(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
long MN,k;

	_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),_tmcHasIm(x));
	MN=tmcNumElem(x);
	for (k=0;k<MN;k++)
	{
		y->m_rData[k] = _mfix(x->m_rData[k]);
	}
	if (_tmcHasIm(x))
		for (k=0;k<MN;k++)
		{
			y->m_iData[k] = _mfix(x->m_iData[k]);
		}
}

void tmcceil(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
long MN,k;

	_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),_tmcHasIm(x));
	MN=tmcNumElem(x);
	for (k=0;k<MN;k++)
	{
		y->m_rData[k] = ceil(x->m_rData[k]);
	}
	if (_tmcHasIm(x))
		for (k=0;k<MN;k++)
		{
			y->m_iData[k] = ceil(x->m_iData[k]);
		}
}

void tmcround(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
long MN,k;

	_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),_tmcHasIm(x));
	MN=tmcNumElem(x);
	for (k=0;k<MN;k++)
	{
		y->m_rData[k] = floor(x->m_rData[k]+0.5F);
	}
	if (_tmcHasIm(x))
		for (k=0;k<MN;k++)
		{
			y->m_iData[k] = floor(x->m_iData[k]+0.5F);
		}

}
void tmcunwrap(long nout,long ninput, tmsMatrix *y,tmsMatrix *x,tmsMatrix *mrange)
{// Restriction:  Matrix is considered as column

long MN,k;
double prev_val;
double v;
double delta;
double PModulo;
//FILE *fp;
		if (ninput==2)
		{
			PModulo=mrange->m_rData[0];
		}
		else
			PModulo = dbl_constant_PI;

		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),tmcREAL);
		if (tmcNumElem(x)==0)
			return;

		prev_val = x->m_rData[0];
		v=	x->m_rData[0];
		y->m_rData[0]=v;
		for (k=1;k<MN;k++)
		{
			delta=x->m_rData[k]-prev_val;
			if (delta>=PModulo)
			{
					delta -=2.0F*PModulo;
			}
			else
				if (delta<-PModulo)
				{
					delta +=2.0F*PModulo;
				}
			v +=delta;
			y->m_rData[k]=v;
			prev_val=x->m_rData[k];
		}
//fp=fopen("debugout.mat","wb");
//	StoreComplex2MatFile(fp ,"x" , x->m_rData ,x->m_iData, x->m_desc.m_nRows , x->m_desc.m_nCols);
//	Store2MatFile(fp ,"y" , y->m_rData , y->m_desc.m_nRows , y->m_desc.m_nCols);
//fclose(fp);
}
void tmcabs(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
long MN,k;

		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),tmcREAL);
		if ( _tmcHasIm(x) )
		{
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]=_tmcCabs(x->m_rData[k],x->m_iData[k]);
			}
		}
		else
		{
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]=fabs(x->m_rData[k]);
			}
		}
}


void tmcisnan(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
long MN,k;


		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),tmcREAL);
		if (_tmcHasIm(x))
		{
		    for (k=0;k<MN;k++)
			{
				if (_tmcIsInfValue(x->m_rData[k]) || _tmcIsMinusInfValue(x->m_rData[k]) || _isnan(x->m_rData[k])
				||	_tmcIsInfValue(x->m_iData[k]) || _tmcIsMinusInfValue(x->m_iData[k]) || _isnan(x->m_iData[k]))
				{
				y->m_rData[k]= 1;
				}
				else
				{
					y->m_rData[k]= 0;
				}
			}
		}
		else
		{
		    for (k=0;k<MN;k++)
			{
				if (_tmcIsInfValue(x->m_rData[k]) || _tmcIsMinusInfValue(x->m_rData[k]) || _isnan(x->m_rData[k]))
				{
					y->m_rData[k]= 1;
				}
				else
				{
					y->m_rData[k]= 0;
				}
			}
		}

}
void tmcisfinite(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
	// HAZARD_RESTRICTION:
	// in matrix indexing logical vars are not supported!!!
	// At the indexing must decorate isinfinite(x) by find(isinfinite(x))

long MN,k;


		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),tmcREAL);
		if (_tmcHasIm(x))
		{
		    for (k=0;k<MN;k++)
			{
				if (_tmcIsInfValue(x->m_rData[k]) || _tmcIsMinusInfValue(x->m_rData[k]) || _isnan(x->m_rData[k])
				||	_tmcIsInfValue(x->m_iData[k]) || _tmcIsMinusInfValue(x->m_iData[k]) || _isnan(x->m_iData[k]))
				{
				y->m_rData[k]= 0;
				}
				else
				{
					y->m_rData[k]= 1;
				}
			}
		}
		else
		{
		    for (k=0;k<MN;k++)
			{
				if (_tmcIsInfValue(x->m_rData[k]) || _tmcIsMinusInfValue(x->m_rData[k]) || _isnan(x->m_rData[k]))
				{
				y->m_rData[k]= 0;
				}
				else
				{
					y->m_rData[k]= 1;
				}
			}
		}
}

void tmcangle(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{// y = atan2(imag(x), real(x));
long MN,k;

		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),tmcREAL);
		if ( _tmcHasIm(x) )
		{
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]=atan2(x->m_iData[k],x->m_rData[k]);
			}
		}
		else
		{
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]=atan2(0,x->m_rData[k]);
			}
		}
}



void tmcsqrt(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{// y = sqrt(abs(x))*(cos(angle(x)*0.5)+j*sin(angle(x)*0.5))

	// decide if result if complex.
long MN,k;
short bResHasIm;
//double ang,mag;
//double a,b,q;
struct tmccomplex yc;

		MN=tmcNumElem(x);
		bResHasIm=_tmcHasIm(x);
		if ( _tmcHasIm(x)==0 )
		{
			for (k=0;k<MN;k++)
			{
				if (x->m_rData[k]<0)
				{
					bResHasIm=1;
					break;
				}
			}
		}
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),bResHasIm);
		if (bResHasIm==0)
		{
			// sqrt(x),all x>0
			for (k=0;k<MN;k++)
			{
				y->m_rData[k] = sqrt(x->m_rData[k]);
			}
		}
		else
		{
			if (_tmcHasIm(x)==0)
			{ // sqrt(x),exist x<0
				for (k=0;k<MN;k++)
				{
					if (x->m_rData[k]>=0)
					{
						y->m_rData[k] = sqrt(x->m_rData[k]);
					}
					else
					{
						y->m_iData[k] = sqrt(-x->m_rData[k]);
					}
				}
			}
			else
			{ // x is complex
			  // y = sqrt(abs(x))*(cos(angle(x)*0.5)+j*sin(angle(x)*0.5))
			 // epes an ander:
				//a1=real(x);b1=imag(x);
				//t = sqrt( (abs(a1) + sqrt(a1*a1+b1*b1)) / 2);
				//if a1>=0  
				//	y = t+ j* (b1/t)*0.5;
				//else
				//	y = abs(b1) /t * 0.5 + j*sign(b1)*t;
				//end

				for (k=0;k<MN;k++)
				{

					_tmcCsqrt(&yc,x->m_rData[k],x->m_iData[k]);
					y->m_rData[k] = yc.re;
					y->m_iData[k] = yc.im;
					/*
					q = sqrt( 0.5*( fabs(x->m_rData[k]) + _tmcCabs(x->m_rData[k],x->m_iData[k]) ));
					if (q==0.0)
					{
						y->m_rData[k] = 0 ;
						y->m_iData[k] = 0 ;
					}
					else
					{
						if (x->m_rData[k]>=0)
						{
							y->m_rData[k] = q ;
							y->m_iData[k] = 0.5 * x->m_iData[k] / q;
						}
						else
						{
							y->m_rData[k] = 0.5 * fabs(x->m_iData[k]) / q ;
							y->m_iData[k] = q * ( x->m_iData[k]>0 ? 1:-1 );
						}
					}
					//mag = sqrt(_tmcCabs(x->m_rData[k],x->m_iData[k]));
					//ang = atan2(x->m_iData[k],x->m_rData[k])*0.5F;
					//y->m_rData[k] = mag*cos(ang);
					//y->m_iData[k] = mag*sin(ang);
					*/

				}
			}
		}
}


void _Catan(double *yre,double *yim,double xre,double xim)
{
// atan(z) = (i/2)*log((i+z)/(i-z))
// if z=a+ib
// (i+z)/(i-z) =  ((-a^2+1-b^2)+i*(-2*a)) /(a^2+(1-b)^2)
double dd,aa,bb;

	dd = xre*xre+(1-xim)*(1-xim);
	aa = (1-xre*xre-xim*xim)/dd;
	bb = -2*xre/dd;
	// ln (x ) = ln |x| + i * arg(x)

			yim[0]= 0.5* log(_tmcCabs(aa,bb) ) ;
			yre[0]= -0.5 * atan2( bb, aa);
}

void tmcatan(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
long MN,k;


		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),_tmcHasIm(x));
		if ( _tmcHasIm(x) )
		{
			for (k=0;k<MN;k++)
			{
				_Catan(&y->m_rData[k],&y->m_iData[k],x->m_rData[k],x->m_iData[k]);
			}
		}
		else
		{
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]=atan(x->m_rData[k]);
			}
		}
}
void tmcatan2(long nout,long ninput, tmsMatrix *y,tmsMatrix *xY,tmsMatrix *xX)
//
{//four-quadrant inverse tangent (arctangent) of the real parts of Y and X.
 //	Any imaginary parts are ignored.
long MN,k;


			MN=tmcNumElem(xY);
			_tmcCreateMatrix(y,_tmcGetM(xY),_tmcGetN(xY),tmcREAL);

			for (k=0;k<MN;k++)
			{
#ifndef HW_INTEL_FPATAN 
				y->m_rData[k]=atan2(xY->m_rData[k],xX->m_rData[k]);
#else
				y->m_rData[k]=intel_atan2(xY->m_rData[k],xX->m_rData[k]);
#endif
			}
}

void tmcasin(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{ // asin(z)=-i*log(iz+sqrt(1-z^2))
//CHECKED
long MN,k;
short bIsComplex;
double a,b,a1,b1,ea,ef;
double *xi=x->m_iData;
short as,sb;

	bIsComplex=_tmcHasIm(x);
			MN=tmcNumElem(x);
	if (bIsComplex==0)
	{
		for (k=0;k<MN;k++)
			{
				if (x->m_rData[k]>1.0f || x->m_rData[k]<-1.0f)
				{
					bIsComplex=1;
					xi=MYMALLOC(sizeof(double)*MN);
					memset(xi,0,sizeof(double)*MN);
					break;
				}
			}
	}

	_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),bIsComplex);
	if (bIsComplex)
	{
		for (k=0;k<MN;k++) //HAZARD: HERE BUG in im()
		{
					//if b
					//	sb=1;
					//	if b>0
					//		b=-b;sb=-1;
					//	end
					//	a1=(1-(a.^2-b.^2));
					//	b1=-2*a.*b;
					//	ea=sqrt(sqrt(a1.^2+b1.^2));
					//	ef=atan2(b1,a1)*0.5;
					//	% iz+sqrt(1-z^2)
					//	a1=ea*cos(ef)-b;
					//	b1=ea*sin(ef)+a;
					//	b=-log(sqrt(a1^2+b1^2));
					//	a=atan2(b1,a1);
					//	b=b*sb;
					//else
					//	as=1;
					//	if a<0
					//		a=-a;
					//		as=-1;
					//	end
					//	ea=sqrt(abs(1-a^2));
					//	a1=0;
					//	b1=ea+a;
					//	b=-log(abs(b1));
					//	if b1<0
					//		a=-pi/2;
					//	else
					//		a=pi/2;
					//	end
					//	a=a*as;b=b*as;
					//end
					//y=(a+j*b);

			a=x->m_rData[k];
			b=xi[k];
			if (b)
			{
				sb=1;
				if (b>0)
				{		b=-b;sb=-1;
				}
				a1=1.0-(a*a-b*b);
				b1=-2.0*a*b;
				ea=sqrt(sqrt(a1*a1+b1*b1));
				ef=atan2(b1,a1)*0.5;
				a1=ea*cos(ef)-b;
				b1=ea*sin(ef)+a;
				y->m_rData[k]=atan2(b1,a1);
				y->m_iData[k]=-log(sqrt(a1*a1+b1*b1))*sb;
			}
			else
			{
				if (fabs(a)>1.0)
				{
					as=1;
					if (a<0)
					{
						a=-a;
						as=-1;
					}
					ea=sqrt(fabs(1.0-a*a));
					b1=ea+a;
					b=-log(fabs(b1));
					if (b1<0)
					{
						a=-dbl_constant_PI*0.5;
					}
					else
					{				
						a=dbl_constant_PI*0.5;
					}
					y->m_rData[k]=a*as;
					y->m_iData[k]=b*as;
				}
				else
				{
					y->m_rData[k]=asin(a);
					y->m_iData[k]=0;
				}
			}
		}
		if (_tmcHasIm(x)==0)
		{
			MYFREE(xi);
		}
	}
	else
	{
		for (k=0;k<MN;k++)
		{
			y->m_rData[k]=asin(x->m_rData[k]);
		}
	}
}

void tmcacos(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{// acos(z)=-i*log(z+i*sqrt(1-z^2))
//CHECKED
long MN,k;
short bIsComplex;
double a,b,a1,b1,ea,ef;
double *xi=x->m_iData;
short sb;

	bIsComplex=_tmcHasIm(x);
			MN=tmcNumElem(x);
	if (bIsComplex==0)
	{
		for (k=0;k<MN;k++)
			{
				if (x->m_rData[k]>1.0f || x->m_rData[k]<-1.0f)
				{
					bIsComplex=1;
					xi=MYMALLOC(sizeof(double)*MN);
					memset(xi,0,sizeof(double)*MN);
					break;
				}
			}
	}

	_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),bIsComplex);
	if (bIsComplex)
	{
		for (k=0;k<MN;k++) 
		{
			// y = -i*log(z + i * sqrt(1- z^2)  )
			//	a=real(x);b=imag(x);
			// if b
			//	a1=(1-(a^2-b^2));
			//	b1=-2*a*b;
			//	ea=sqrt(sqrt(a1^2+b1^2));
			//	if b
			//	ef=atan2(b1,a1)*0.5;
			//	else
			//	ef=0.5*pi;
			//	end
			//	% z+i*sqrt(1-z^2)
			//	b1=ea*cos(ef)+b;
			//	a1=-ea*sin(ef)+a;
			//	b=-log(sqrt(a1^2+b1^2));
			//	a=atan2(b1,a1);
			// else
			//				a1=(1-a.^2);
			//				ea=sqrt(abs(a1));
			//	            
			//				%b1=0;
			//	%             if (a<=0)
			//					a1=-ea+a;
			//					b=-log(abs(a1));
			//	%             else
			//	%                 a1=ea+a;
			//	%                 b=-log(abs( (2*a.^2-1) /  a1));
			//	%             end
			//				if a1<0
			//					a=pi;
			//				else
			//					a=0;
			//				end
			// end
			//	y=a+j*b;
			a=x->m_rData[k];
			b=xi[k];
			if (b)
			{
			sb=1;
			if (b<0)
			{
				sb=-1;
				b=-b;
			}
			a1=1.0-(a*a-b*b);
			b1=-2.0*a*b;
			ea=sqrt(sqrt(a1*a1+b1*b1));
			//if (b)
				ef=atan2(b1,a1)*0.5;// maybe if b1=0 must ef=0.5*pi
			//else
			//	ef=0.5*PI;
			b1=ea*cos(ef)+b;
			a1=-ea*sin(ef)+a;
			y->m_rData[k]=atan2(b1,a1);
			y->m_iData[k]=-log(sqrt(a1*a1+b1*b1))*sb;
			}
			else
			{
				if (fabs(a)>1.0)
				{
					a1 = 1-a*a;
					ea = sqrt(fabs(a1));
					a1 = a-ea;
					if (a<0)
						b  = -log(fabs(a1));
					else
						b  =  log(fabs(-a-ea));
					if (a1<0)
						a=dbl_constant_PI;
					else
						a=0;
				}
				else
				{
						a=acos(a);
						b=0;
				}
				y->m_rData[k]=a;
				y->m_iData[k]=b;
			}
		}
		if (_tmcHasIm(x)==0)
		{
			MYFREE(xi);
		}
	}
	else
	{
		for (k=0;k<MN;k++)
		{
			y->m_rData[k]=acos(x->m_rData[k]);
		}
	}
}
void tmclogspace(long nout,long ninput, tmsMatrix *y, tmsMatrix *x1, tmsMatrix *x2,tmsMatrix *nP)
{
long nPoints;
long k;

	if  (ninput<3)
		nPoints=50;
	else
		nPoints = (long)floor(nP->m_rData[0]);
		//y = (10).^ [x1+(0:nPoints-2)*(x2-x1)/(floor(nPoints)-1), x2];
		_tmcCreateMatrix(y,1,nPoints,tmcREAL);

	for (k=0;k<=nPoints-2;k++)
	{
		y->m_rData[k]=pow(10.0, x1->m_rData[0]+k*(x2->m_rData[0]-x1->m_rData[0])/(double)(nPoints-1));
	}
	y->m_rData[nPoints-1]=pow(10.0,x2->m_rData[0]);
}
void tmclinspace(long nout,long ninput, tmsMatrix *y, tmsMatrix *x1, tmsMatrix *x2,tmsMatrix *nP)
{
long nPoints;
long k;

	if  (ninput<3)
		nPoints=100;
	else
		nPoints = (long)floor(nP->m_rData[0]);
		//y =  [x1+(0:nPoints-2)*(x2-x1)/(floor(nPoints)-1), x2];
		_tmcCreateMatrix(y,1,nPoints,tmcREAL);

	for (k=0;k<=nPoints-2;k++)
	{
		y->m_rData[k]= x1->m_rData[0]+k*(x2->m_rData[0]-x1->m_rData[0])/(double)(nPoints-1);
	}
	y->m_rData[nPoints-1]= x2->m_rData[0];
}


void tmcdeconv(long nout,long ninput, tmsMatrix *q, tmsMatrix *r, tmsMatrix *u,tmsMatrix *v)
{ // [q,r]=deconv(v,u): v=q*u+r

	// assuming u(1)<>0
	// assuming u,v are vectors
long NMv,NMu;
long NMq,Nq,Mq;
double *workr,*worki;
double *ui,*vi;
long k,cnt;
short bComplexResult=(short)(_tmcHasIm(u) | _tmcHasIm(v));

	NMv=tmcNumElem(v);
	NMu=tmcNumElem(u);
	NMq = NMu-NMv+1;
	if (_tmcGetM(u)>_tmcGetN(u))
	{
		Mq=NMq;Nq=1;
	}
	else
	{
		Nq=NMq;Mq=1;
	}

	if (NMu<NMv)
	{
			_tmcCreateMatrix(q,1,1,tmcREAL);
			q->m_rData[0]=0;  // q=0
			if (nout>1)
			{
				_tmcCreateMatrix(r,_tmcGetM(u),_tmcGetM(u),_tmcHasIm(u));
				memcpy(r->m_rData,u->m_rData,sizeof(double)*NMu);
				if (_tmcHasIm(u))
				{
					memcpy(r->m_iData,u->m_iData,sizeof(double)*NMu);
				}
			}
			return;
	}
	else
	{
	   // Deconvolution and polynomial division are the same operations
	   // as a digital filter's impulse response V(z)/U(z):
	   // q = filter(b, a, [1 zeros(1,nb-na)]);
       // r = b - conv(a,q);

		// but we use simple division
		/*
		nq=nu-nv+1;
		q=zeros(1,nq);
		work=zeros(1,nv);
		r=zeros(1,nu);
		q(1)=u(1)/v(1);
		for cnt=1:nv
			work(cnt)=u(cnt);    
		end
		for k=2:nq
		   for cnt=1:nv-1
				work(cnt)=work(cnt+1)- q(k-1)*v(cnt+1);       
		   end
		   work(nv)=u(k+nv-1);
		   q(k)=work(1)/v(1);
		end
		% find r
		   for cnt=1:nv-1
				work(cnt)=work(cnt+1)- q(nq)*v(cnt+1);       
		   end
		for k=1:nv-1
		   r(k+nq)=work(k);     
		end
		*/
		_tmcCreateMatrix(q,Mq,Nq,tmcCOMPLEX);
		workr  = MYMALLOC(sizeof(double)*NMv);
		worki  = MYMALLOC(sizeof(double)*NMv);
		// for simplicity allocate memory for imag(u) and imag(v)
		if (_tmcHasIm(u))
		{
			ui=u->m_iData;
		}
		else
		{
			ui  = MYMALLOC(sizeof(double)*NMu);
			memset(ui,0,sizeof(double)*NMu);
		}
		if (_tmcHasIm(v))
		{
			vi=v->m_iData;
		}
		else
		{
			vi  = MYMALLOC(sizeof(double)*NMv);
			memset(vi,0,sizeof(double)*NMv);
		}
		//q(1)=u(1)/v(1);
		_Cdiv(&q->m_rData[0],&q->m_iData[0],u->m_rData[0],ui[0],v->m_rData[0],vi[0]);
		//for cnt=1:nv
		//	work(cnt)=u(cnt);    
		//end
		memcpy(workr,&u->m_rData[0],sizeof(double)*NMv);
		memcpy(worki,&ui[0],sizeof(double)*NMv);
		//for k=2:nq
		//   for cnt=1:nv-1
		//		work(cnt)=work(cnt+1)- q(k-1)*v(cnt+1);       
		//   end
		//   work(nv)=u(k+nv-1);
		//   q(k)=work(1)/v(1);
		//end
		for (k=2;k<=NMq;k++)
		{
			for (cnt=1;cnt<NMv;cnt++)
			{
				workr[cnt-1]=workr[cnt] - (q->m_rData[k-2]*v->m_rData[cnt]	-q->m_iData[k-2]*vi[cnt]    );
				worki[cnt-1]=worki[cnt] - (q->m_rData[k-2]*vi[cnt]			+q->m_iData[k-2]*v->m_rData[cnt]    );
			}
			workr[NMv-1]=u->m_rData[k+NMv-2];
			worki[NMv-1]=ui[k+NMv-2];
			_Cdiv(&q->m_rData[k-1],&q->m_iData[k-1],workr[0],worki[0],v->m_rData[0],vi[0]);
		}
		if (nout>1)
		{
		//% find r
		//   for cnt=1:nv-1
		//		work(cnt)=work(cnt+1)- q(nq)*v(cnt+1);       
		//   end
		_tmcCreateMatrix(r,_tmcGetM(u),_tmcGetN(u),bComplexResult);
			for (cnt=1;cnt<NMv;cnt++)
			{
				workr[cnt-1]=workr[cnt] - (q->m_rData[NMq-1]*v->m_rData[cnt]	-q->m_iData[NMq-1]*vi[cnt]    );
				worki[cnt-1]=worki[cnt] - (q->m_rData[NMq-1]*vi[cnt]			+q->m_iData[NMq-1]*v->m_rData[cnt]    );
			}
			//for k=1:nv-1
			//   r(k+nq)=work(k);     
			//end
			for (k=1;k<NMv;k++)
			{
				r->m_rData[k+NMq-1]=workr[k-1];
				//if (bComplexResult==tmcCOMPLEX)
				//	r->m_iData[k+NMq-1]=worki[k-1];
			}
			if (_tmcHasIm(r))
			{
				for (k=1;k<NMv;k++)
				{
					r->m_iData[k+NMq-1]=worki[k-1];
				}
			}
		}
		// If _tmcHasIm(u)==0 & _tmcHasIm(v)==0 remove imag(q)
		if (bComplexResult==0)
		{
			MYFREE(q->m_iData);
			q->m_desc.m_modifier &= (~MODIFIER_MASK_HAS_IM);
		}
	}
	


		MYFREE(workr);
		MYFREE(worki);
		if (_tmcHasIm(u)==0)
			MYFREE(ui);
		if (_tmcHasIm(v)==0)
			MYFREE(vi);

}
void tmcsign(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{
long MN,k;
register double u,ui;
double D;

		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,_tmcGetM(x),_tmcGetN(x),_tmcHasIm(x));
		if (_tmcHasIm(x))
		{
			for (k=0;k<MN;k++)
			{
				u=x->m_rData[k];
				ui=x->m_iData[k];
				if (ui==0)
				{
					if (u==0)
					{
						y->m_rData[k]=0;
					}
					else
					{
						if (u>0)
						{
							y->m_rData[k]=1.0f;
						}
						else
						{
							y->m_rData[k]=-1.0f;
						}
					}
				}
				else
				{
					//if (u==0)
					//{
					//	y->m_rData[k]=0;
					//}
					//else
					//{
						// x/abs(x)
						//RealReciprocal(&D,u*u+ui*ui);
						//D=sqrt(D);
						D =_Rdiv(1., _tmcCabs(u,ui));
						y->m_rData[k]=x->m_rData[k]*D;
						y->m_iData[k]=x->m_iData[k]*D;
					//}
				}
			}

		}
		else
			for (k=0;k<MN;k++)
			{
				u=x->m_rData[k];
				if (u==0)
				{
					y->m_rData[k]=0;
				}
				else
				{
					if (u>0)
					{
						y->m_rData[k]=1.0f;
					}
					else
					{
						y->m_rData[k]=-1.0f;
					}
				}
			}
}
void tmcinterp1(long nout,long ninput, tmsMatrix *yi, tmsMatrix *x, tmsMatrix *y, tmsMatrix *xi,
			tmsMatrix *typeinter,tmsMatrix *typeextr)
{
// Restriction: only linear interpolation is supported; only real data
// assumed: x is sorted.
// y=interp1(x,y,xi,'linear')
long k,m;
double x0,x1;
long MN=tmcNumElem(xi);
long MN_src = tmcNumElem(x);
double  dx_,dy;
	_tmcCreateMatrix(yi,_tmcGetM(xi),_tmcGetN(xi),tmcREAL);
	
			x0 = x->m_rData[0];
			for (k=0;k<MN;k++)
			{
				x1=xi->m_rData[k];
				if (x1<=x->m_rData[0])
				{
						dy=y->m_rData[1]-y->m_rData[0];
						dx_ = _Rdiv(x1-x->m_rData[0],x->m_rData[1]-x->m_rData[0]);
						yi->m_rData[k]=y->m_rData[0]+ dy*dx_;
						//RealReciprocal(&dx_,x->m_rData[1]-x->m_rData[0]);
						//yi->m_rData[k]=y->m_rData[0]+ dy*dx_*(x1-x->m_rData[0]);

				}
				else
				{
					if (x1>=x->m_rData[MN_src-1])
					{
						dy=y->m_rData[MN_src-1]-y->m_rData[MN_src-2];
						dx_ = _Rdiv(x1-x->m_rData[MN_src-1],x->m_rData[MN_src-1]-x->m_rData[MN_src-2]);
						yi->m_rData[k]=y->m_rData[MN_src-1]+ dy*dx_;
						//RealReciprocal(&dx_,x->m_rData[MN_src-1]-x->m_rData[MN_src-2]);
						//yi->m_rData[k]=y->m_rData[MN_src-1]+ dy*dx_*(x1-x->m_rData[MN_src-1]);
					}
					else
					{
						// for xi[k] find m: x[m-1]<= xi[k] < x[m]
						m=0;
						while (x1 >= x->m_rData[m])
						{
							m++;
						}
						// now: x1<x->m_rData[m]
						dy=y->m_rData[m]-y->m_rData[m-1];
						dx_ = _Rdiv(x1-x->m_rData[m-1],x->m_rData[m]-x->m_rData[m-1]);
						yi->m_rData[k]=y->m_rData[m-1]+ dy*dx_;
						//RealReciprocal(&dx_,x->m_rData[m]-x->m_rData[m-1]);
						//yi->m_rData[k]=y->m_rData[m-1]+ dy*dx_*(x1-x->m_rData[m-1]);
					}
				}
			}
}

void tmcPowerScalar(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2)
{ // y=src1.^src2
  // Restriction:
  //  src2 must be real,scalar or src1 is scalar 
tmsMatrix *y;
long k,MN;
double scal,scali;
double mag,ang;

	tmcReallocRegister(matres);
	y = matres;

	if (_tmcHasIm(src2))
		_tmcRaiseException(err_unsupported,s_module,"PowerScalar(.^)","exponent must be real.",2,src1,src2);
	
	if (tmcNumElem(src2)==1)
	{// X^n
		_tmcCreateMatrix(y,_tmcGetM(src1),_tmcGetN(src1),_tmcHasIm(src1));
		MN=tmcNumElem(src1);
		scal = src2->m_rData[0]; // exponent

		if (_tmcHasIm(src1)==0)
		{
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]= pow(src1->m_rData[k],scal);
			}
		}
		else
		{
				  // x = src1 is complex
				  // y = pow(abs(x),n)*(cos(angle(x)*n)+j*sin(angle(x)*n))
					for (k=0;k<MN;k++)
					{
						mag = pow(_tmcCabs(src1->m_rData[k],src1->m_iData[k]),scal);
						ang = atan2(src1->m_iData[k],src1->m_rData[k])*scal;
						y->m_rData[k] = mag*cos(ang);
						y->m_iData[k] = mag*sin(ang);
					}
		}
	}
	else
	if (tmcNumElem(src1)==1) // tmcNumElem(src1)==1
	{// x^N
		_tmcCreateMatrix(y,_tmcGetM(src2),_tmcGetN(src2),_tmcHasIm(src1));
		MN=tmcNumElem(src2);
		scal = src1->m_rData[0]; // base

		if (_tmcHasIm(src1)==0)
		{
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]= pow(scal,src2->m_rData[k]);
			}
		}
		else
		{
			scali =src1->m_iData[0]; // base
				  // x = src1 is complex
				  // y = pow(abs(x),n)*(cos(angle(x)*n)+j*sin(angle(x)*n))
					for (k=0;k<MN;k++)
					{
						mag = pow(_tmcCabs(scal,scali),src2->m_rData[k]);
						ang = atan2(scali,scal)*src2->m_rData[k];
						y->m_rData[k] = mag*cos(ang);
						y->m_iData[k] = mag*sin(ang);
					}
		}

	}
	else // both numelem>1
	{
		if (_tmcGetM(src1) != _tmcGetM(src2) || _tmcGetN(src1) != _tmcGetN(src2))
		{
			_tmcRaiseException(err_invalid_dimentions,s_module,"PowerScalar(.^)","exponent and base must be equal dimentions.",2,src1,src2);
		}

		_tmcCreateMatrix(y,_tmcGetM(src2),_tmcGetN(src2),_tmcHasIm(src1));
		MN=tmcNumElem(src2);

		if (_tmcHasIm(src1)==0)
		{
			for (k=0;k<MN;k++)
			{
				y->m_rData[k]= pow(src1->m_rData[k],src2->m_rData[k]);
			}
		}
		else
		{
				  // x = src1 is complex
				  // y = pow(abs(x),n)*(cos(angle(x)*n)+j*sin(angle(x)*n))
					for (k=0;k<MN;k++)
					{
						scali =src1->m_iData[k]; // base
						scal  =src1->m_rData[k];
						mag = pow(_tmcCabs(scal,scali),src2->m_rData[k]);
						ang = atan2(scali,scal)*src2->m_rData[k];
						y->m_rData[k] = mag*cos(ang);
						y->m_iData[k] = mag*sin(ang);
					}
		}

	}
}	

void tmcPower(tmsMatrix *matres,tmsMatrix *src1,tmsMatrix *src2)
// y=src1^src2
  // Restriction: only scalar power operation is supported!!! HAZARD
{
	if (_tmcHasIm(src2))
		_tmcRaiseException(err_unsupported,s_module,"Power(^)","exponent must be real.",2,src1,src2);
	if (tmcNumElem(src2)!=1)
	{
		_tmcRaiseException(err_unsupported,s_module,"Power(^)","exponent must be scalar.",2,src1,src2);
	}
	if (_tmcGetM(src1)!=1 && _tmcGetN(src1)!=1)
	{
		_tmcRaiseException(err_unsupported,s_module,"Power(^) not supported","basic must be scalar or vector.",2,src1,src2);
	}
	tmcPowerScalar(matres,src1,src2);

}
void tmccumprod(long nout,long ninput,tmsMatrix *y,tmsMatrix *x,tmsMatrix *dim)
{ 
long M,N;
double Dr,Di;
double Yr,Yi;
long m,n;

	if (_tmcGetM(x)==1)
	{
		// row
		N=_tmcGetN(x);
		_tmcCreateMatrix(y,1,N,_tmcHasIm(x));
			Dr=1;Di=0;
			for (n=0;n<N;n++)
			{
				Yr=x->m_rData[n];
				if (_tmcHasIm(x))
				{
					Yi=x->m_iData[n];
					Dr=Dr*Yr-Di*Yi;
					Di=Dr*Yi+Di*Yr;
					y->m_rData[n]=Dr;
					y->m_iData[n]=Di;
				}
				else
				{
					Dr=Dr*Yr;
					y->m_rData[n]=Dr;
				}
			}
	}
	else
	{
		// column or matrix
		// matrix - get cumprod for each column
		M=_tmcGetM(x);
		N=_tmcGetN(x);
		_tmcCreateMatrix(y,M,N,_tmcHasIm(x));
		for (n=0;n<N;n++)
		{
			Dr=1;Di=0;
			for (m=0;m<M;m++)
			{
				Yr=x->m_rData[m];
				if (_tmcHasIm(x))
				{
					Yi=x->m_iData[m];
					Dr=Dr*Yr-Di*Yi;
					Di=Dr*Yi+Di*Yr;
					y->m_rData[n*M+m]=Dr;
					y->m_iData[n*M+m]=Di;
				}
				else
				{
					Dr=Dr*Yr;
					y->m_rData[n*M+m]=Dr;
				}
			}
		}
	}
}

void tmcrand(long nout,long ninput,tmsMatrix *y,tmsMatrix *m,tmsMatrix *n)
{
	_tmcOnesFac(nout,ninput,y,m,n,-2);
}



void tmcconv(long nout,long ninput, tmsMatrix *C, tmsMatrix *A, tmsMatrix *B)
{ // C=conv(A,B)
//TODO
//* Let nA = length(A) and nB = length(B). Then C is the vector of length nA+nB-1 whose kth element is
//* C(k)=Sum_j A(j)B(k+1-j), j=max(1,k+1-nB)..min(k,nA)
long nA,nB,lenC,mC,nC;
long k,jmax,jn,j2;
double rS,iS;

nA = tmcNumElem(A);
nB = tmcNumElem(B);
lenC = nA+nB-1;

	// dims of C go after dims B
	if (_tmcGetM(B)> _tmcGetN(B))
	{
		mC = lenC; nC=1;
	}
	else
	{
		mC= 1; nC = lenC;
	}
		_tmcCreateMatrix(C,mC,nC,_tmcHasIm(A) |_tmcHasIm(B));

		for (k=0;k<lenC;k++)
		{
			rS=0;iS=0;
			jn=max(1,(1+k)+1-nB)-1;// zero based indexes
			jmax=min((k+1),nA)-1;
			j2=(k+1)+1-(jn+1)-1;

			if (_tmcHasIm(C)==0)
			{
				for ( ;jn<=jmax;jn++,j2--)
				{
					rS += A->value.complx.rData[jn]*B->value.complx.rData[j2];
				}
			    C->value.complx.rData[k]=rS;
			}
			else
			{
				if (_tmcHasIm(A) && _tmcHasIm(B))
				{
					for ( ;jn<=jmax;jn++,j2--)
					{
						rS += A->value.complx.rData[jn]*B->value.complx.rData[j2]-
							  A->value.complx.iData[jn]*B->value.complx.iData[j2];
						iS += A->value.complx.rData[jn]*B->value.complx.iData[j2]+
							  A->value.complx.iData[jn]*B->value.complx.rData[j2];
					}
				}
				else if (_tmcHasIm(A)) // only _tmcHasIm(A)
				{
					for ( ;jn<=jmax;jn++,j2--)
					{
						rS += A->value.complx.rData[jn]*B->value.complx.rData[j2];
						iS += A->value.complx.iData[jn]*B->value.complx.rData[j2];
					}
				}
				else // only _tmcHasIm(B)
				{
					for ( ;jn<=jmax;jn++,j2--)
					{
						rS += A->value.complx.rData[jn]*B->value.complx.rData[j2];
						iS += A->value.complx.rData[jn]*B->value.complx.iData[j2];
					}
				}
				C->value.complx.rData[k]=rS;
				C->value.complx.iData[k]=iS;
			}
		}
return;
}

enum E_NORMS
{  // matrix norms
	E_NORM_1=1,
	E_NORM_2=2,
	E_NORM_INF = 3, // H_inf
	E_NORM_FROB = 4,
   // vector norms
	E_VEC_NORM_P=5,
	E_VEC_NORM_MAX=6,
	E_VEC_NORM_MIN=7,
	E_VEC_NORM_1=8,
	E_VEC_NORM_2=9

} ;

double _tmcCalcNorm(tmsMatrix *X,enum E_NORMS norm_type,double p)
{
	double res=0;
	long N,M,len;
	double sum_;
	long m,n,k;
	double x,y;

	tmsMatrix *S;
	M = _tmcGetM(X);
	N = _tmcGetN(X);
	len = min(M,N);

//	if (norm_type==E_VEC_NORM_P && p==2)
//		norm_type = E_VEC_NORM_2;

	switch (norm_type)
	{
	case E_NORM_1://=1,
    // largest column sum = max(sum(abs(X)))
		if (_tmcHasIm(X)==0)
		{
			for (n=0;n<N;n++)
			{
				for (m=0,k=n*M,sum_=0;m<M;m++)
					sum_+=fabs(X->m_rData[k+m]);
				if (sum_>res)
					res=sum_;
			}
		}
		else
		{
			for (n=0;n<N;n++)
			{
				for (m=0,k=n*M,sum_=0;m<M;m++)
				{
					x=fabs(X->m_rData[k+m]);
					y=fabs(X->m_iData[k+m]);

					sum_+=sqrt( x*x+ y*y );
				}
				if (sum_>res)
					res=sum_;
			}
		}

		break;
	case E_NORM_2://=2,

		S=tmcNewMatrix();
		tmcsvd(1,1,S,NULL,NULL,X,NULL);
		res = S->value.complx.rData[0]; // maximal singular value
	    tmcFreeLocalVar(S);

		break;
	case E_NORM_INF:// = 3, // H_inf
    // largest row sum = max(sum(abs(X')))
		if (_tmcHasIm(X)==0)
		{
			for (m=0;m<M;m++)
			{
				for (n=0,sum_=0;n<N;n++)
					sum_+=fabs(X->m_rData[m+n*M]);
				if (sum_>res)
					res=sum_;
			}
		}
		else
		{
			for (m=0;m<M;m++)
			{
				for (n=0,sum_=0;n<N;n++)
				{
					x=fabs(X->m_rData[m+n*M]);
					y=fabs(X->m_iData[m+n*M]);

					sum_+=sqrt( x*x+ y*y );
				}
				if (sum_>res)
					res=sum_;
			}
		}

		break;
	case E_NORM_FROB:// = 4,
		//  sqrt(sum(diag(X'*X)))
		if (_tmcHasIm(X)==0)
		{
			sum_=0;
			for (n=0;n<N;n++)
			for (m=0;m<M;m++)
			{
				x = X->m_rData[m+M*n]*X->m_rData[m+M*n] ;
				sum_ += x;
			}
		}
		else
		{
			sum_=0;
			for (n=0;n<N;n++)
			for (m=0;m<M;m++)
			{
				x = X->m_rData[m+M*n]*X->m_rData[m+M*n] +
					X->m_iData[m+M*n]*X->m_iData[m+M*n];
				sum_ += x;
			}
		}
		sum_ = sqrt(sum_);
		res = sum_;
		break;



   // vector norms
	case E_VEC_NORM_1://
		// sum(abs(V))
		if (_tmcHasIm(X)==0)
		{
			for (m=0,sum_=0;m<M*N;m++)
			{
				x = fabs(X->m_rData[m]);
				sum_ += x;
			}
		}
		else
		{
			for (m=0,sum_=0;m<M*N;m++)
			{
					x=fabs(X->m_rData[m]);
					y=fabs(X->m_iData[m]);

				sum_ +=sqrt(  x*x+ y*y  );
			}
		}
		res = sum_;
		break;

	case E_VEC_NORM_2://
		// sum(abs(V).^2)^(1/2).
		if (_tmcHasIm(X)==0)
		{
			for (m=0,sum_=0;m<M*N;m++)
			{
				x = fabs(X->m_rData[m]);
				sum_ += x*x;
			}
		}
		else
		{
			for (m=0,sum_=0;m<M*N;m++)
			{
					x=fabs(X->m_rData[m]);
					y=fabs(X->m_iData[m]);

				sum_ +=  x*x+ y*y  ;
			}
		}
		res = sqrt(sum_);



		break;
	case E_VEC_NORM_P://=5,
		// sum(abs(V).^P)^(1/P).

		break;

	case E_VEC_NORM_MAX://=6,
		//max(abs(V))
		if (_tmcHasIm(X)==0)
		{
			for (m=0;m<M*N;m++)
			{
				sum_ = fabs(X->m_rData[m]);
				if (sum_>res)
					res=sum_;
			}
		}
		else
		{
			for (m=0;m<M*N;m++)
			{
					x=fabs(X->m_rData[m]);
					y=fabs(X->m_iData[m]);

				sum_ = sqrt( x*x+ y*y );
				if (sum_>res)
					res=sum_;
			}
		}

		break;
	case E_VEC_NORM_MIN://=7
		//min(abs(V))
		if (_tmcHasIm(X)==0)
		{
			res = fabs(X->m_rData[0]);
			for (m=1;m<M*N;m++)
			{
				sum_ = fabs(X->m_rData[m]);
				if (sum_<res)
					res=sum_;
			}
		}
		else
		{
					x=fabs(X->m_rData[0]);
					y=fabs(X->m_iData[0]);

				res = sqrt( x*x+ y*y );

			for (m=1;m<M*N;m++)
			{
					x=fabs(X->m_rData[m]);
					y=fabs(X->m_iData[m]);

				sum_ = sqrt( x*x+ y*y );
				if (sum_<res)
					res=sum_;
			}
		}

		break;
	}
	return res;
}
void tmcnorm(long nout,long ninput, tmsMatrix *y, tmsMatrix *X, tmsMatrix *n)
{
double p=2;
enum E_NORMS norm_type;
//TODO
/* NORM   Matrix or vector norm.
    For matrices...
      NORM(X),NORM(X,2) is the largest singular value of X, max(svd(X)).
      NORM(X,1) is the 1-norm of X, the largest column sum,
                      = max(sum(abs(X))).
      NORM(X,inf) is the infinity norm of X, the largest row sum,
                      = max(sum(abs(X'))).
      NORM(X,'fro') is the Frobenius norm, sqrt(sum(diag(X'*X))).
      NORM(X,P) is available for matrix X only if P is 1, 2, inf or 'fro'.
 
    For vectors...
      NORM(V,P) = sum(abs(V).^P)^(1/P).
      NORM(V) = norm(V,2).
      NORM(V,inf) = max(abs(V)).
      NORM(V,-inf) = min(abs(V)).
*/
		_tmcCreateMatrix(y,1,1,tmcREAL);
	if (_tmcIsMatrix(X))
	{
		// matrix norm
		if (ninput==1)
			norm_type= E_NORM_2;
		else if (_tmcIsChar(n))
				norm_type= E_NORM_FROB;
			else if (_tmcIsInfValue(n->value.complx.rData[0]))
					norm_type=E_NORM_INF;
				else if (n->value.complx.rData[0]==1)
					norm_type= E_NORM_1;
				else if (n->value.complx.rData[0]==2)
					norm_type= E_NORM_2;
				else
					norm_type= E_NORM_2; // is exception here
	}
	else
	{
		// vector norm
		if (ninput==1)
		{
			norm_type= E_VEC_NORM_2; p = 2;
		}
		else
		{
			p  = n->value.complx.rData[0];

			if (_tmcIsInfValue(p))
					norm_type=E_VEC_NORM_MAX;
			else if (_tmcIsMinusInfValue(p))
					norm_type=E_VEC_NORM_MIN;
			else if (p==1)
			{
					norm_type=E_VEC_NORM_1;
			}
			else if (p==2)
			{
					norm_type=E_VEC_NORM_2;
			}
				else
				{
					norm_type= E_VEC_NORM_P; // is exception here
				}
		}
	}
	y->value.complx.rData[0]= _tmcCalcNorm (X,norm_type,p);
}
void tmccond(long nout,long ninput,tmsMatrix *y,tmsMatrix *A,tmsMatrix *p)
{
// restriction: only for p==2
double condval;
double norm1,norm2;
long M;
if (ninput<2 || _tmcScalarVal(p)==2)
	{
tmsMatrix *S = tmcNewMatrix();
		tmcsvd(1,1,S,NULL,NULL,A,NULL);
		M=_tmcGetM(S);
		condval = _Rdiv(S->value.complx.rData[0], S->value.complx.rData[M-1]);
tmcFreeLocalVar(S);
_tmcCreateMatrix(y,1,1,tmcREAL);
y->value.complx.rData[0] = condval;
return;
	}
	else
	{
	tmsMatrix *U = tmcNewMatrix();
	tmsMatrix *n = tmcNewMatrix();

	if (_tmcGetM(A) != _tmcGetN(A))
		{
				tmcFreeLocalVar(n);
				tmcFreeLocalVar(U);
	_tmcRaiseException(err_unsupported,"main","tmccond","cond(A,p<>2) defined on ly for nxn.",0,NULL);
		}


	tmcinv(1,1,U,A);
	tmcnorm(1,2, n, U, p);
	norm2  = _tmcScalarVal(n);

	tmcnorm(1,2, n, A, p);
	norm1  = _tmcScalarVal(n);

	condval = norm1 * norm2;


	tmcFreeLocalVar(n);
	tmcFreeLocalVar(U);

	_tmcCreateMatrix(y,1,1,tmcREAL);
	y->value.complx.rData[0] = condval;
	}


	//_tmcRaiseException(err_unsupported,"main","tmccond","FATAL: tmccond is not yet implemented!!!.",0,NULL);

}
void tmcinf(long nout,long ninput,tmsMatrix *dest)
{// like 1/0 HAZARD: if we change it to true Inf mut check all compares!!
	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,1,1,tmcREAL);
	dest->m_rData[0]= _Rdiv(1.0,0.0); //DBL_MAX; here warning C4723: potential divide by 0
}

void tmcNaN(long nout,long ninput,tmsMatrix *dest)
{// like 0/0
	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,1,1,tmcREAL);
	dest->m_rData[0]=DBL_MAX;
}
void tmceps(long nout,long ninput,tmsMatrix *dest,tmsMatrix *R)
{
	double x,y;
	double E;
	//union UdoublelongIEEE
	//{	
	//	double  d;
	//	int64_t l;
	//} U;
	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,1,1,tmcREAL);
	if (ninput<1)
	{
		//returns the distance from 1.0 to the next larger
		//double-precision number, that is eps = 2^(-52). 
		dest->m_rData[0]=DBL_EPSILON;
	}
	else
	{
		//(from Ver  > 7.0)
		// if abs(X) <= realmin=DBL_MIN=2.2250738585072014e-308, eps(X) = 2^(-1074).
		// else is the positive distance from abs(X) to the next larger
		//in magnitude floating point number of the same precision as X:
		//if 2^E <= abs(X) < 2^(E+1), then eps(X) = 2^(E-52) 
		x = _tmcScalarVal(R);
		if (x <= DBL_MIN)
			y=4.940656458412465e-324;
		else
		{
			// HAZARD: must check! 2^(log2(hex2double('001fffffffffffff'))-52)
			E =(short)floor( log(x)/log(2.0));
			y = pow(2.0, E-52.0) ;
			//U.d=fabs(x);
			//U.l=U.l+1; // this is the next number.?
			//y = U.d - fabs(x);
		}
		dest->m_rData[0]=y;
	}
}
void tmcpi(long nout,long ninput,tmsMatrix *dest)
{
	tmcReallocRegister(dest);
	_tmcCreateMatrix(dest,1,1,tmcREAL);
	dest->m_rData[0]=dbl_constant_PI;
}


void tmcmean(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{ 
	long m,n,MN,M,N,offMN;
	double Sr,Si;
	//For vectors, mean(X) is the sum of the elements of X / number of elements.
	//For matrices, mean(X) is a row vector with the mean over each column.
	if (ninput>1)
			_tmcRaiseException(err_bad_index,s_module,"mean","mean(X) unsupported ninput=1",1,x);
	if (_tmcIsMatrix(x))
	{
		N=_tmcGetN(x);
		M=_tmcGetM(x);

		_tmcCreateMatrix(y,1,_tmcGetN(x),_tmcHasIm(x));
		for (n=0;n<N;n++)
		{
				Sr=0;Si=0;
				offMN = n*M;
				for (m=0;m<M;m++)
					Sr += x->m_rData[offMN+m];

				if (_tmcHasIm(x))
				{
					for (m=0;m<M;m++)
						Si += x->m_iData[offMN+m];
				}
				y->m_rData[n]=Sr / M;
				if (_tmcHasIm(x))
					y->m_iData[n]=Si / M;
		}
	}
	else
	{
		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,1,1,_tmcHasIm(x));
		Sr=0;Si=0;
		for (n=0;n<MN;n++)
			Sr += x->m_rData[n];

		if (_tmcHasIm(x))
		{
			for (n=0;n<MN;n++)
				Si += x->m_iData[n];
		}
		y->m_rData[0]=Sr / MN;
		if (_tmcHasIm(x))
			y->m_iData[0]=Si / MN;
	}
}

void tmcstd(long nout,long ninput, tmsMatrix *y,tmsMatrix *x)
{ 
	long m,n,MN,M,N,offMN;
	double Sr,Si;
	double Dr,Di;
	double D;
	//For vectors, std(X) is the  of the  .
	//For matrices, std(X) is a row vector with the mean over each column.
	if (ninput>1)
			_tmcRaiseException(err_bad_index,s_module,"std","std(X) unsupported ninput=1",1,x);
	if (_tmcIsMatrix(x))
	{
		N=_tmcGetN(x);
		M=_tmcGetM(x);
		D = M - 1;
		_tmcCreateMatrix(y,1,_tmcGetN(x),_tmcHasIm(x));
		if (M < 2)
		{
			for (n = 0; n < N; n++)
			{
				y->m_rData[n] = 0;
				if (_tmcHasIm(x))
					y->m_iData[n] = 0;
			}
		}
		else
		for (n=0;n<N;n++)
		{
				Sr=0;Si=0;
				offMN = n*M;
				for (m=0;m<M;m++)
					Sr += x->m_rData[offMN+m];
				Sr = Sr / M;

				if (_tmcHasIm(x))
				{
					for (m=0;m<M;m++)
						Si += x->m_iData[offMN+m];
					Si = Si / M;
				}

				Dr=0;Di=0;
				for (m=0;m<M;m++)
					Dr += (x->m_rData[offMN+m]-Sr)*(x->m_rData[offMN+m]-Sr);
				if (_tmcHasIm(x))
				{
					for (m=0;m<M;m++)
						Di += (x->m_iData[offMN+m]-Si)*(x->m_iData[offMN+m]-Si);
				}
				y->m_rData[n]=sqrt(Dr / D );
				if (_tmcHasIm(x))
					y->m_iData[n]=sqrt(Di / D);
		}
	}
	else
	{
		MN=tmcNumElem(x);
		_tmcCreateMatrix(y,1,1,_tmcHasIm(x));
		if (MN < 2)
		{
				y->m_rData[0] = 0;
				if (_tmcHasIm(x))
					y->m_iData[0] = 0;
				return;
		}
		D = MN - 1;
		Sr=0;Si=0;
		for (n=0;n<MN;n++)
			Sr += x->m_rData[n];
		Sr=Sr/MN;

		if (_tmcHasIm(x))
		{
			for (n=0;n<MN;n++)
				Si += x->m_iData[n];
			Si=Si/MN;
		}

				Dr=0;Di=0;
				for (n=0;n<MN;n++)
					Dr += (x->m_rData[n]-Sr)*(x->m_rData[n]-Sr);
				if (_tmcHasIm(x))
				{
					for (n=0;n<MN;n++)
						Di += (x->m_iData[n]-Si)*(x->m_iData[n]-Si);
				}

				y->m_rData[0]=sqrt(Dr / D );
				if (_tmcHasIm(x))
					y->m_iData[0]=sqrt(Di / D);
	}
}
