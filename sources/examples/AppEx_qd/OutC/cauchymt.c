//File: cauchymt.c 
//Generated by TMC Converter(C)2009-2016
#include "tmc.h"
#include "stdtmc.h"

#include "TestO.globals.h"

// User provided C-code header (must be included in include path):
#include "External_func.h"

// % Lines 1--5:
//function A = cauchymt(f,k)

//%

//% program to generate a k-column Cauchy matrix of polynomial f

//%

//   n = length(f);

void tmccauchymt(int nargout, int nargin,tmsMatrix *A
,tmsMatrix *f,tmsMatrix *k) {
tmsMatrix **reg=tmcCreateRegFrame(29);
tmsMatrix *n=tmcNewMatrix();
tmsMatrix *m=tmcNewMatrix();
tmsMatrix *j_=tmcNewMatrix();

TRY
TMC_DBG_PUSH_STACK_VAR("cauchymt",6,
f,"f",
k,"k",
A,"A",
n,"n",
m,"m",
j_,"j_");


//CALL function
tmcReallocRegister(reg[2]);
tmclength(1,1, reg[2], f);

tmcAssign(n,reg[2]);
//statement here,line 5

// % Lines 6--6:
//   m = n + k - 1;



tmcAdd(reg[6],n,k);
tmcScalar(reg[7],1.000000000000000e+000);
tmcSub(reg[8],reg[6],reg[7]);

tmcAssign(m,reg[8]);
//statement here,line 6

// % Lines 7--7:
//   A = zeros(m,k);



//CALL function
tmcReallocRegister(reg[12]);
tmczeros(1,2, reg[12], m, k);

tmcAssign(A,reg[12]);
//statement here,line 7

// % Lines 8--10:
//   

//   for j_ = 1:k

//       A(j_:j_+n-1,j_) = f';

tmcScalar(reg[14],1.000000000000000e+000);

tmcCreateColonBaseLimit(reg[16],reg[14],k);
tmcForIterInit(reg[17],reg[16],j_);
label_4: ; //FOR begin
if(tmcForIterNext(reg[17],reg[16])) goto label_3; // exit for

tmcTranspose(reg[19],f);




tmcAdd(reg[24],j_,n);
tmcScalar(reg[25],1.000000000000000e+000);
tmcSub(reg[26],reg[24],reg[25]);
tmcCreateColonBaseLimit(reg[27],j_,reg[26]);

tmcGetRefByIndex(pRefHelper,A,2,reg[27],j_);
tmcAssign(pRefHelper,reg[19]);
//statement here,line 10

// % Lines 11--11:
//   end;

label_2: ; //FOR end
goto label_4; //branch to FOR begin
label_3: ; //FOR exit
//statement here,line 11

// % Lines 12--12:
//   
label_1: ; //end Function
FINALLY
tmcFreeLocalVar(j_);
tmcFreeLocalVar(m);
tmcFreeLocalVar(n);
tmcFreeRegFrame(reg);

TMC_DBG_POP_STACK_VAR(6);

ENDFINALLY
}

//FUNCTION DEFINITION ENDED
//statement here,line 12

// % Lines 13--13:
