/*================================================================= 
 * function Y = ExMex1(X1,X2);
 example function
						Y= X1+X2
 *=================================================================*/

#include <math.h>
#include "mex.h"

#define TMCMEX_DLL // must define for TMC


#ifndef TMCMEX_DLL

#include "mexport.h"
#define mY	plhs[0]
#define mX1  prhs[0]
#define mX2  prhs[1]

void mexFunction( int nlhs, mxArray *plhs[],
int nrhs, const mxArray*prhs[] )

#else
#define nrhs	nargin
#define nlhs	nargout
void tmcExMex1(int nargout, int nargin,tmsMatrix *mY,
				 tmsMatrix *mX1,tmsMatrix *mX2)
#endif
{
    int mp, np; 	
    int  ind;     
    double * X1_rPtr;
    double * X1_iPtr;
    double * Y_rPtr;
    double * Y_iPtr;
    double * X2_rPtr;
    double * X2_iPtr;
    
    /* Check for proper number of arguments */
    if (nrhs != 2)
    {
        mexErrMsgTxt("Two input arguments required.");
    }
    if (nlhs > 1) {
        mexErrMsgTxt("One output argument required.");
    }
    
    /* Check the dimensions */
	mp = mxGetM(mX1); /* Number of rows in the first input argument */
    np = mxGetN(mX2); /* Number of rows in the first input argument */
    
    if ( mp != np )
    {
        mexErrMsgTxt("Matrix dimensions do not match.");
    }
    
    /* Create a matrix for the return argument */
    
    if ( mxGetPi ( mX1 ) == NULL && mxGetPi ( mX2 ) == NULL)
    {
        TMCMEX_CREATE_DOUBLE_MATRIX(mY,mp, np , mxREAL );
    }
    else
    {
        TMCMEX_CREATE_DOUBLE_MATRIX(mY,mp, np , mxCOMPLEX );
    }
    
    
    X1_rPtr = mxGetPr ( mX1 );
    X1_iPtr = mxGetPi ( mX2 );
    
    X2_rPtr = mxGetPr ( mX2 );
    X2_iPtr = mxGetPi ( mX2 );
    Y_rPtr = mxGetPr ( mY  );
	Y_iPtr = mxGetPi ( mY  ) ;
    
	if ( X1_iPtr == NULL )
	{
		if ( ( Y_iPtr != NULL ) && ( X2_iPtr != NULL ) )
		{
			for ( ind = 0 ; ind < mp ; ind++ )
			{	                       
                    Y_rPtr[ ind ] = X2_rPtr[ ind ] + X1_rPtr[ ind ];
                    Y_iPtr[ ind ] = X2_rPtr[ ind ] ;
            }
		}
		else
        {
			for ( ind = 0 ; ind < mp ; ind++ )
			{	
                    Y_rPtr[ ind ] = X2_rPtr[ ind ] + X1_rPtr[ ind ];
               
			}
        }
    }
    else
    {
        if ( X2_iPtr == NULL )
        {
            if ( Y_iPtr != NULL )
			{
				for ( ind = 0 ; ind < mp ; ind++ )
				{	                              
                        Y_rPtr[ ind ] = X2_rPtr[ ind ] + X1_rPtr[ ind ];
                        Y_iPtr[ ind ] = X1_iPtr[ ind ];
                }
			}
            else
            {
				for ( ind = 0 ; ind < mp ; ind++ )
				{
                        Y_rPtr[ ind ] = X2_rPtr[ ind ] + X1_rPtr[ ind ];
                    
                }
            }
        }
        else
        {
            if ( Y_iPtr != NULL )
			{
				for ( ind = 0 ; ind < mp ; ind++ )
				{	             
                        Y_rPtr[ ind ] = X2_rPtr[ ind ] + X1_rPtr[ ind ];
                        Y_iPtr[ ind ] = X1_iPtr[ ind ] + X2_iPtr[ ind ] ;
                }
			}
            else
            {
				for ( ind = 0 ; ind < mp ; ind++ )
				{
                      Y_rPtr[ ind ] = X2_rPtr[ ind ] + X1_rPtr[ ind ];
                }
            }
        }
    }
    return;
}


