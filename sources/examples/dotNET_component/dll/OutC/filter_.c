//File: filter_.c 
//Generated by TMC Converter(C)2009-2016
#include "tmc.h"
#include "stdtmc.h"

#include "TestO.globals.h"

// User provided C-code header (must be included in include path):
#include "External_func.h"

// % Lines 1--14:
//function y=filter_(b,a,u)

//%see http://stackoverflow.com/questions/17506343/how-can-i-write-the-matlab-filter-function-myself

//%% Direct Form II Transposed  

//% Direct realization of rational transfer functions

//% trps: 0 for direct realization, 1 for transposed realisation 

//% b,a: Numerator and denominator

//% x:   Input sequence

//% y:   Output sequence

//% u:   Internal states buffer

//

//% trps = 1;

//% b=theta(1:ord+1);

//% a=theta(ord+2:end);

//a0 = a(1);

void tmcfilter_(int nargout, int nargin,tmsMatrix *y
,tmsMatrix *b__input__tmc,tmsMatrix *a__input__tmc,tmsMatrix *u) {
tmsMatrix **reg=tmcCreateRegFrame(78);
tmsMatrix *b=tmcNewMatrix();
tmsMatrix *a=tmcNewMatrix();
tmsMatrix *a0=tmcNewMatrix();
tmsMatrix *ord=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrix();
tmsMatrix *k=tmcNewMatrix();

tmcCopyMat(b,b__input__tmc);
tmcCopyMat(a,a__input__tmc);
TRY
TMC_DBG_PUSH_STACK_VAR("filter_",10,
b__input__tmc,"b__input__tmc",
a__input__tmc,"a__input__tmc",
u,"u",
y,"y",
b,"b",
a,"a",
a0,"a0",
ord,"ord",
x,"x",
k,"k");


tmcScalar(reg[2],1.000000000000000e+000);
tmcGetByIndex(reg[3],a,1,reg[2]);

tmcAssign(a0,reg[3]);
//statement here,line 14

// % Lines 15--15:
//a = a(2:end)'/a0;


tmcScalar(reg[6],2.000000000000000e+000);
tmcGetEnd(reg[7],a,1,1);
tmcCreateColonBaseLimit(reg[8],reg[6],reg[7]);
tmcGetByIndex(reg[9],a,1,reg[8]);
tmcTranspose(reg[10],reg[9]);

tmcDiv(reg[12],reg[10],a0);

tmcAssign(a,reg[12]);
//statement here,line 15

// % Lines 16--16:
//b =b' /a0;


tmcTranspose(reg[15],b);

tmcDiv(reg[17],reg[15],a0);

tmcAssign(b,reg[17]);
//statement here,line 16

// % Lines 17--17:
//y=zeros(size(u));


//CALL function
tmcReallocRegister(reg[20]);
tmcsize(1,1, reg[20], u,NULL);
//CALL function
tmcReallocRegister(reg[21]);
tmczeros(1,1, reg[21], reg[20]);

tmcAssign(y,reg[21]);
//statement here,line 17

// % Lines 18--18:
//ord = length(b)-1;


//CALL function
tmcReallocRegister(reg[24]);
tmclength(1,1, reg[24], b);
tmcScalar(reg[25],1.000000000000000e+000);
tmcSub(reg[26],reg[24],reg[25]);

tmcAssign(ord,reg[26]);
//statement here,line 18

// % Lines 19--19:
//x=zeros(ord,1);


tmcScalar(reg[29],1.000000000000000e+000);
//CALL function
tmcReallocRegister(reg[30]);
tmczeros(1,2, reg[30], ord, reg[29]);

tmcAssign(x,reg[30]);
//statement here,line 19

// % Lines 20--23:
//%%

//% if trps==1

//    for k=1:length(u)

//        y(k)=b(1)*u(k)+x(1);

tmcScalar(reg[32],1.000000000000000e+000);

//CALL function
tmcReallocRegister(reg[34]);
tmclength(1,1, reg[34], u);
tmcCreateColonBaseLimit(reg[35],reg[32],reg[34]);
tmcForIterInit(reg[36],reg[35],k);
label_4: ; //FOR begin
if(tmcForIterNext(reg[36],reg[35])) goto label_3; // exit for

tmcScalar(reg[38],1.000000000000000e+000);
tmcGetByIndex(reg[39],b,1,reg[38]);


tmcGetByIndex(reg[42],u,1,k);
tmcMul(reg[43],reg[39],reg[42]);

tmcScalar(reg[45],1.000000000000000e+000);
tmcGetByIndex(reg[46],x,1,reg[45]);
tmcAdd(reg[47],reg[43],reg[46]);


tmcGetRefByIndex(pRefHelper,y,1,k);
tmcAssign(pRefHelper,reg[47]);
//statement here,line 23

// % Lines 24--24:
//        x=[x(2:ord);0];


tmcScalar(reg[51],2.000000000000000e+000);

tmcCreateColonBaseLimit(reg[53],reg[51],ord);
tmcGetByIndex(reg[54],x,1,reg[53]);
tmcCollectColumns(reg[55],1,reg[54]);
tmcScalar(reg[56],0.000000000000000e+000);
tmcCollectColumns(reg[57],1,reg[56]);
tmcCollectRows(reg[58],2,reg[55],reg[57]);

tmcAssign(x,reg[58]);
//statement here,line 24

// % Lines 25--25:
//        x=x+b(2:end)*u(k)-a*y(k);



tmcScalar(reg[62],2.000000000000000e+000);
tmcGetEnd(reg[63],b,1,1);
tmcCreateColonBaseLimit(reg[64],reg[62],reg[63]);
tmcGetByIndex(reg[65],b,1,reg[64]);


tmcGetByIndex(reg[68],u,1,k);
tmcMul(reg[69],reg[65],reg[68]);
tmcAdd(reg[70],x,reg[69]);



tmcGetByIndex(reg[74],y,1,k);
tmcMul(reg[75],a,reg[74]);
tmcSub(reg[76],reg[70],reg[75]);

tmcAssign(x,reg[76]);
//statement here,line 25

// % Lines 26--26:
//    end

label_2: ; //FOR end
goto label_4; //branch to FOR begin
label_3: ; //FOR exit
//statement here,line 26

// % Lines 27--35:
//% else

//%     for k=1:length(u)

//%         xnew=u(k)-sum(x(1:ord).*a);

//%         x=[xnew,x];

//%         y(k)=sum(x(1:ord+1).*b);

//%         x=x(1:ord);

//%     end

//% end

label_1: ; //end Function
FINALLY
tmcFreeLocalVar(k);
tmcFreeLocalVar(x);
tmcFreeLocalVar(ord);
tmcFreeLocalVar(a0);
tmcFreeLocalVar(a);
tmcFreeLocalVar(b);
tmcFreeRegFrame(reg);

TMC_DBG_POP_STACK_VAR(10);

ENDFINALLY
}

//FUNCTION DEFINITION ENDED
//statement here,line 35

// % Lines 36--36:
