/*================================================================= 
 * function Y = json_read(X)
 * json_read,1,1,x;
 *=================================================================*/
#define _CRT_SECURE_NO_DEPRECATE
#define YYDEBUG 1
// c file: main.c
#include <stdio.h>
#include <stdlib.h>
#include "JsonRead.tab.h"

#include "JMatrix.h"

extern FILE* Json_in;
int yylineno;
extern tmsMatrix * head_tmc_obj;

#include <math.h>
#include "mex.h"

#define TMCMEX_DLL // must define for TMC


#ifndef TMCMEX_DLL

#include "mexport.h"
#define mY	plhs[0]
#define mFname  prhs[0]

void mexFunction( int nlhs, mxArray *plhs[],
int nrhs, const mxArray*prhs[] )

#else
#define nrhs	nargin
#define nlhs	nargout
void tmcjson_read(int nargout, int nargin,tmsMatrix *mY,
				 tmsMatrix *mFname)
#endif
{
    	char *sBuf;
int stat;
    /* Check for proper number of arguments */
    if (nrhs > 1)
    {
        mexErrMsgTxt("One or zero input arguments required (stdin=0 or filename).");
    }
    if (nlhs !=1) {
        mexErrMsgTxt("One output argument required.");
    }

  // if a file is given read from it
  // otherwise we'll read from STDIN
  if(nrhs == 1)
  {
 	sBuf=_tmcMat2String(mFname);
    if(!(Json_in = fopen(sBuf,"r")))
    {
      perror("cant open json-file");
      return EXIT_FAILURE;
    }
  }
  stat =  Json_parse();
  if (stat==0 && nlhs>0)
  {
	 tmcAssign(mY,head_tmc_obj);
  }
_tmcClearRegister(head_tmc_obj);
tmcFreeLocalVar(head_tmc_obj);

}


