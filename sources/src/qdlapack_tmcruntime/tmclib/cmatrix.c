/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license. 
  *****************************************************************************/
// cmatrix.c
// Pure C interface for V4 matlab matrix
#include <stdio.h>
#include <string.h>

#include "cmatrix.h"



short Store2MatFile( FILE *fp , const char *vecName , 
				double *data , long rows , long cols )
{
	struct Fmatrix x ;
	// double ddata ; 
	x.type  =  0 ;
	x.mrows = rows  ;
	x.ncols = cols  ;
	x.imagf = 0L  ;
	x.namlen = (long)strlen(vecName) + 1 ;
	fwrite( &x , sizeof(struct Fmatrix) , 1 , fp ) ;
	fwrite( vecName , sizeof(char) , x.namlen , fp ) ;
	fwrite( data , sizeof(double) , cols * rows , fp ) ;
	return 1 ; 
}
///////////
short StoreComplex2MatFile( FILE *fp ,const char *vecName , 
				double *rdata , double *idata ,long rows , long cols )
{
	struct Fmatrix x ;
	// double ddata ; 
	x.type  =  0 ;
	x.mrows = rows  ;
	x.ncols = cols  ;
	if (idata==NULL)
	x.imagf = 0L  ;
	else
	x.imagf = 1L  ;

	x.namlen = (long)strlen(vecName) + 1 ;
	fwrite( &x , sizeof(struct Fmatrix) , 1 , fp ) ;
	fwrite( vecName , sizeof(char) , x.namlen , fp ) ;
	fwrite( rdata , sizeof(double) , cols * rows , fp ) ;
	if (idata!=NULL)
	fwrite( idata , sizeof(double) , cols * rows , fp ) ;
	return 1 ; 
}
