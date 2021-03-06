//File: TestO.c 
//Generated by TMC Converter(C)2009-2016
#include "tmc.h"
#include "stdtmc.h"

#include "TestO.globals.h"

// User provided C-code header (must be included in include path):
#include "External_func.h"

// % Lines 1--4:
//function [unusedy,unusedm]=TestO(x,n)

//global VV

//

//p = [1 1 200 1 1 1 1 1 1 1 1 10 1 1 1 1 1 1 1 1 1 1 1 1 1 1 ];

void tmcTestO(int nargout, int nargin,tmsMatrix *unusedy,tmsMatrix *unusedm
,tmsMatrix *x__input__tmc,tmsMatrix *n) {
tmsMatrix **reg=tmcCreateRegFrame(96);
tmsMatrix *x=tmcNewMatrix();
tmsMatrix *p=tmcNewMatrix();
tmsMatrix *y=tmcNewMatrix();
tmsMatrix *y_a=tmcNewMatrix();
tmsMatrix *I=tmcNewMatrix();
tmsMatrix *y_r=tmcNewMatrix();
tmsMatrix *y_i=tmcNewMatrix();
tmsMatrix *d=tmcNewMatrix();
tmsMatrix *tht=tmcNewMatrix();
tmsMatrix *AbsOffsetCorr=tmcNewMatrix();
tmsMatrix *AdvUsecCorr=tmcNewMatrix();
tmsMatrix *str=tmcNewMatrix();

tmcCopyMat(x,x__input__tmc);
TRY
TMC_DBG_PUSH_STACK_VAR("TestO",16,
x__input__tmc,"x__input__tmc",
n,"n",
unusedy,"unusedy",
unusedm,"unusedm",
x,"x",
p,"p",
y,"y",
y_a,"y_a",
I,"I",
y_r,"y_r",
y_i,"y_i",
d,"d",
tht,"tht",
AbsOffsetCorr,"AbsOffsetCorr",
AdvUsecCorr,"AdvUsecCorr",
str,"str");

//statement here,line 4

tmcScalar(reg[1],1.000000000000000e+000);
tmcScalar(reg[2],1.000000000000000e+000);
tmcScalar(reg[3],2.000000000000000e+002);
tmcScalar(reg[4],1.000000000000000e+000);
tmcScalar(reg[5],1.000000000000000e+000);
tmcScalar(reg[6],1.000000000000000e+000);
tmcScalar(reg[7],1.000000000000000e+000);
tmcScalar(reg[8],1.000000000000000e+000);
tmcScalar(reg[9],1.000000000000000e+000);
tmcScalar(reg[10],1.000000000000000e+000);
tmcScalar(reg[11],1.000000000000000e+000);
tmcScalar(reg[12],1.000000000000000e+001);
tmcScalar(reg[13],1.000000000000000e+000);
tmcScalar(reg[14],1.000000000000000e+000);
tmcScalar(reg[15],1.000000000000000e+000);
tmcScalar(reg[16],1.000000000000000e+000);
tmcScalar(reg[17],1.000000000000000e+000);
tmcScalar(reg[18],1.000000000000000e+000);
tmcScalar(reg[19],1.000000000000000e+000);
tmcScalar(reg[20],1.000000000000000e+000);
tmcScalar(reg[21],1.000000000000000e+000);
tmcScalar(reg[22],1.000000000000000e+000);
tmcScalar(reg[23],1.000000000000000e+000);
tmcScalar(reg[24],1.000000000000000e+000);
tmcScalar(reg[25],1.000000000000000e+000);
tmcScalar(reg[26],1.000000000000000e+000);
tmcCollectColumns(reg[27],26,reg[1],reg[2],reg[3],reg[4],reg[5],reg[6],reg[7],reg[8]
,reg[9],reg[10],reg[11],reg[12],reg[13],reg[14],reg[15],reg[16]
,reg[17],reg[18],reg[19],reg[20],reg[21],reg[22],reg[23],reg[24]
,reg[25],reg[26]);
tmcCollectRows(reg[28],1,reg[27]);

tmcAssign(p,reg[28]);
//statement here,line 4

// % Lines 5--5:
//y = roots(p);


//CALL function
tmcReallocRegister(reg[31]);
tmcroots(1,1, reg[31], p);

tmcAssign(y,reg[31]);
//statement here,line 5

// % Lines 6--6:
//y_a = angle(y);


//CALL function
tmcReallocRegister(reg[34]);
tmcangle(1,1, reg[34], y);

tmcAssign(y_a,reg[34]);
//statement here,line 6

// % Lines 7--7:
//[y_a,I]=sort(y_a);


//CALL function
tmcReallocRegister(reg[37]);
tmcReallocRegister(reg[38]);
tmcsort(2,1, reg[37], reg[38], y_a,NULL);

tmcAssign(y_a,reg[37]);

tmcAssign(I,reg[38]);
//statement here,line 7

// % Lines 8--8:
//y=y(I);



tmcGetByIndex(reg[43],y,1,I);

tmcAssign(y,reg[43]);
//statement here,line 8

// % Lines 9--10:
//

//y =y ;%.* exp(abs(y_a) - abs(y_a(1)));



tmcAssign(y,y);
//statement here,line 10

// % Lines 11--12:
//

//y_r=real(y);


//CALL function
tmcReallocRegister(reg[48]);
tmcreal(1,1, reg[48], y);

tmcAssign(y_r,reg[48]);
//statement here,line 12

// % Lines 13--13:
//y_i = imag(y);


//CALL function
tmcReallocRegister(reg[51]);
tmcimag(1,1, reg[51], y);

tmcAssign(y_i,reg[51]);
//statement here,line 13

// % Lines 14--14:
// figure(500);

tmcScalar(reg[53],5.000000000000000e+002);
//CALL function
tmcReallocRegister(reg[54]);
tmcfigure(0,1, reg[54], reg[53]);
//statement here,line 14

// % Lines 15--15:
// plot(y_r,y_i);



//CALL function
tmcReallocRegister(reg[57]);
tmcplot(0,2, reg[57], y_r, y_i);
//statement here,line 15

// % Lines 16--22:
//

//

//%return;

//

//

//

//p = [1,2,3];

tmcScalar(reg[58],1.000000000000000e+000);
tmcScalar(reg[59],2.000000000000000e+000);
tmcScalar(reg[60],3.000000000000000e+000);
tmcCollectColumns(reg[61],3,reg[58],reg[59],reg[60]);
tmcCollectRows(reg[62],1,reg[61]);

tmcAssign(p,reg[62]);
//statement here,line 22

// % Lines 23--23:
//y = roots(p);


//CALL function
tmcReallocRegister(reg[65]);
tmcroots(1,1, reg[65], p);

tmcAssign(y,reg[65]);
//statement here,line 23

// % Lines 24--24:
//x = polyval(p,y);



//CALL function
tmcReallocRegister(reg[69]);
tmcpolyval(1,2, reg[69], p, y);

tmcAssign(x,reg[69]);
//statement here,line 24

// % Lines 25--26:
//

//d=CheckVar1(p,y);



//CALL function
tmcReallocRegister(reg[73]);
tmcCheckVar1(1,2, reg[73], p, y);

tmcAssign(d,reg[73]);
//statement here,line 26

// % Lines 27--28:
//

//disp(y);


//CALL function
tmcReallocRegister(reg[76]);
tmcdisp(0,1, reg[76], y);
//statement here,line 28

// % Lines 29--29:
//disp(x);


//CALL function
tmcReallocRegister(reg[78]);
tmcdisp(0,1, reg[78], x);
//statement here,line 29

// % Lines 30--30:
//disp(d-x);



tmcSub(reg[81],d,x);
//CALL function
tmcReallocRegister(reg[82]);
tmcdisp(0,1, reg[82], reg[81]);
//statement here,line 30

// % Lines 31--32:
//

//[tht,AbsOffsetCorr,AdvUsecCorr] =btlCalcCommut;

//CALL function
tmcReallocRegister(reg[83]);
tmcReallocRegister(reg[84]);
tmcReallocRegister(reg[85]);
tmcbtlCalcCommut(3,0, reg[83], reg[84], reg[85]);

tmcAssign(tht,reg[83]);

tmcAssign(AbsOffsetCorr,reg[84]);

tmcAssign(AdvUsecCorr,reg[85]);
//statement here,line 32

// % Lines 33--35:
//% disp(AbsOffsetCorr);

//% disp(AdvUsecCorr);

//str=sprintf('correction to AbsOffset=%d, AdvUsec=%d',AbsOffsetCorr,AdvUsecCorr);

tmcCreateString(reg[89],"correction to AbsOffset=%d, AdvUsec=%d");


//CALL function
tmcReallocRegister(reg[92]);
tmcsprintf(1,3, reg[92], reg[89], AbsOffsetCorr, AdvUsecCorr);

tmcAssign(str,reg[92]);
//statement here,line 35

// % Lines 36--36:
//disp(str);


//CALL function
tmcReallocRegister(reg[95]);
tmcdisp(0,1, reg[95], str);
//statement here,line 36

// % Lines 37--39:
//

//

label_1: ; //end Function
FINALLY
tmcFreeLocalVar(str);
tmcFreeLocalVar(AdvUsecCorr);
tmcFreeLocalVar(AbsOffsetCorr);
tmcFreeLocalVar(tht);
tmcFreeLocalVar(d);
tmcFreeLocalVar(y_i);
tmcFreeLocalVar(y_r);
tmcFreeLocalVar(I);
tmcFreeLocalVar(y_a);
tmcFreeLocalVar(y);
tmcFreeLocalVar(p);
tmcFreeLocalVar(x);
tmcFreeRegFrame(reg);

TMC_DBG_POP_STACK_VAR(16);

ENDFINALLY
}

//FUNCTION DEFINITION ENDED
//statement here,line 39

// % Lines 40--40:
