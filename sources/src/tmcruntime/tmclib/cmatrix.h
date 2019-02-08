/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 File may be used in the generated application
  *****************************************************************************/
#ifndef _cmatrix_h_
#define _cmatrix_h_
// cmatrix.h
// Prototypes for cmatrix.c

////////
struct Fmatrix
{
	long type;   // type =MOPT: M:0- little endian (intel), 1-big endian,etc.,O=0,
	long mrows;  // row dimension 
	long ncols;  // column dimension 
	long imagf;  // flag indicating imag part 
	long namlen; // name length (including NULL) 
} ;


struct CMatrix 
{ 
	short m_nRows ; 
	short m_nCols ; 
	double * m_pData ;
	double * m_iData ;
};

short Store2MatFile( FILE *fp ,const char *vecName , double *data , long rows , long cols );
short StoreComplex2MatFile( FILE *fp ,const char *vecName , 
				double *rdata , double *idata ,long rows , long cols );


#endif
