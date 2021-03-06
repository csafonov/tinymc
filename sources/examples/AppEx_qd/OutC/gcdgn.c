//File: gcdgn.c 
//Generated by TMC Converter(C)2009-2016
#include "tmc.h"
#include "stdtmc.h"

#include "TestO.globals.h"

// User provided C-code header (must be included in include path):
#include "External_func.h"

// % Lines 1--17:
//function [g,u,v,res] = gcdgn(p, q, g0, u0, v0)

//%

//%  Finds extended GCD of polynomial p and q by Gauss-Newton

//%  iteration, such that

//%

//%         conv(g,u) = p,      conv(g,v) = q

//%   

//%  Calling syntax:

//%    [g,u,v,res] = gcdgn(p, q, g0, u0, v0)

//%      

//%        INPUT:  p, q -- polynomial coefficients

//%                g0, u0, v0 -- initial iterates

//%        OUTPUT: g, u, v as described above

//%                res

//%

//   

//   m = length(g0)-1; m1 = m+1;    % degree of g (i.e. gcd)

void tmcgcdgn(int nargout, int nargin,tmsMatrix *g,tmsMatrix *u,tmsMatrix *v,tmsMatrix *res
,tmsMatrix *p__input__tmc,tmsMatrix *q__input__tmc,tmsMatrix *g0__input__tmc,tmsMatrix *u0__input__tmc,tmsMatrix *v0__input__tmc) {
tmsMatrix **reg=tmcCreateRegFrame(328);
tmsMatrix *p=tmcNewMatrix();
tmsMatrix *q=tmcNewMatrix();
tmsMatrix *g0=tmcNewMatrix();
tmsMatrix *u0=tmcNewMatrix();
tmsMatrix *v0=tmcNewMatrix();
tmsMatrix *m=tmcNewMatrix();
tmsMatrix *m1=tmcNewMatrix();
tmsMatrix *n=tmcNewMatrix();
tmsMatrix *n1=tmcNewMatrix();
tmsMatrix *k=tmcNewMatrix();
tmsMatrix *k1=tmcNewMatrix();
tmsMatrix *lp=tmcNewMatrix();
tmsMatrix *lq=tmcNewMatrix();
tmsMatrix *s=tmcNewMatrix();
tmsMatrix *t=tmcNewMatrix();
tmsMatrix *b=tmcNewMatrix();
tmsMatrix *x=tmcNewMatrix();
tmsMatrix *w=tmcNewMatrix();
tmsMatrix *jj=tmcNewMatrix();
tmsMatrix *bke=tmcNewMatrix();
tmsMatrix *A=tmcNewMatrix();
tmsMatrix *d=tmcNewMatrix();
tmsMatrix *y=tmcNewMatrix();

tmcCopyMat(p,p__input__tmc);
tmcCopyMat(q,q__input__tmc);
tmcCopyMat(g0,g0__input__tmc);
tmcCopyMat(u0,u0__input__tmc);
tmcCopyMat(v0,v0__input__tmc);
TRY
TMC_DBG_PUSH_STACK_VAR("gcdgn",32,
p__input__tmc,"p__input__tmc",
q__input__tmc,"q__input__tmc",
g0__input__tmc,"g0__input__tmc",
u0__input__tmc,"u0__input__tmc",
v0__input__tmc,"v0__input__tmc",
g,"g",
u,"u",
v,"v",
res,"res",
p,"p",
q,"q",
g0,"g0",
u0,"u0",
v0,"v0",
m,"m",
m1,"m1",
n,"n",
n1,"n1",
k,"k",
k1,"k1",
lp,"lp",
lq,"lq",
s,"s",
t,"t",
b,"b",
x,"x",
w,"w",
jj,"jj",
bke,"bke",
A,"A",
d,"d",
y,"y");


//CALL function
tmcReallocRegister(reg[2]);
tmclength(1,1, reg[2], g0);
tmcScalar(reg[3],1.000000000000000e+000);
tmcSub(reg[4],reg[2],reg[3]);

tmcAssign(m,reg[4]);
//statement here,line 17


tmcScalar(reg[7],1.000000000000000e+000);
tmcAdd(reg[8],m,reg[7]);

tmcAssign(m1,reg[8]);
//statement here,line 17

// % Lines 18--18:
//   n = length(u0)-1; n1 = n+1;    % degree of u


//CALL function
tmcReallocRegister(reg[11]);
tmclength(1,1, reg[11], u0);
tmcScalar(reg[12],1.000000000000000e+000);
tmcSub(reg[13],reg[11],reg[12]);

tmcAssign(n,reg[13]);
//statement here,line 18


tmcScalar(reg[16],1.000000000000000e+000);
tmcAdd(reg[17],n,reg[16]);

tmcAssign(n1,reg[17]);
//statement here,line 18

// % Lines 19--19:
//   k = length(v0)-1; k1 = k+1;    % degree of v


//CALL function
tmcReallocRegister(reg[20]);
tmclength(1,1, reg[20], v0);
tmcScalar(reg[21],1.000000000000000e+000);
tmcSub(reg[22],reg[20],reg[21]);

tmcAssign(k,reg[22]);
//statement here,line 19


tmcScalar(reg[25],1.000000000000000e+000);
tmcAdd(reg[26],k,reg[25]);

tmcAssign(k1,reg[26]);
//statement here,line 19

// % Lines 20--20:
//   lp = length(p);                % length of p


//CALL function
tmcReallocRegister(reg[29]);
tmclength(1,1, reg[29], p);

tmcAssign(lp,reg[29]);
//statement here,line 20

// % Lines 21--21:
//   lq = length(q);                % length of q = p'


//CALL function
tmcReallocRegister(reg[32]);
tmclength(1,1, reg[32], q);

tmcAssign(lq,reg[32]);
//statement here,line 21

// % Lines 22--24:
//   

//   % making all polynomials monic

//   if p(1) ~= 1, p = p/(p(1)); end;   


tmcScalar(reg[35],1.000000000000000e+000);
tmcGetByIndex(reg[36],p,1,reg[35]);
tmcScalar(reg[37],1.000000000000000e+000);
tmcNe(reg[38],reg[36],reg[37]);
if(tmcIsFalse(reg[38])) goto label_3; // goto to the end of the clause if the expression is false


tmcScalar(reg[41],1.000000000000000e+000);
tmcGetByIndex(reg[42],p,1,reg[41]);
tmcDiv(reg[43],p,reg[42]);

tmcAssign(p,reg[43]);
//statement here,line 24

goto label_2; //branch to end IF
label_3: ; //end IF clause
label_2: ; //end IF
//statement here,line 24

// % Lines 25--25:
//   if q(1) ~= 1, q = q/(q(1)); end; 


tmcScalar(reg[46],1.000000000000000e+000);
tmcGetByIndex(reg[47],q,1,reg[46]);
tmcScalar(reg[48],1.000000000000000e+000);
tmcNe(reg[49],reg[47],reg[48]);
if(tmcIsFalse(reg[49])) goto label_5; // goto to the end of the clause if the expression is false


tmcScalar(reg[52],1.000000000000000e+000);
tmcGetByIndex(reg[53],q,1,reg[52]);
tmcDiv(reg[54],q,reg[53]);

tmcAssign(q,reg[54]);
//statement here,line 25

goto label_4; //branch to end IF
label_5: ; //end IF clause
label_4: ; //end IF
//statement here,line 25

// % Lines 26--26:
//   if g0(1) ~= 1, g0 = g0/(g0(1)); end; 


tmcScalar(reg[57],1.000000000000000e+000);
tmcGetByIndex(reg[58],g0,1,reg[57]);
tmcScalar(reg[59],1.000000000000000e+000);
tmcNe(reg[60],reg[58],reg[59]);
if(tmcIsFalse(reg[60])) goto label_7; // goto to the end of the clause if the expression is false


tmcScalar(reg[63],1.000000000000000e+000);
tmcGetByIndex(reg[64],g0,1,reg[63]);
tmcDiv(reg[65],g0,reg[64]);

tmcAssign(g0,reg[65]);
//statement here,line 26

goto label_6; //branch to end IF
label_7: ; //end IF clause
label_6: ; //end IF
//statement here,line 26

// % Lines 27--27:
//   if u0(1) ~= 1, u0 = u0/(u0(1)); end; 


tmcScalar(reg[68],1.000000000000000e+000);
tmcGetByIndex(reg[69],u0,1,reg[68]);
tmcScalar(reg[70],1.000000000000000e+000);
tmcNe(reg[71],reg[69],reg[70]);
if(tmcIsFalse(reg[71])) goto label_9; // goto to the end of the clause if the expression is false


tmcScalar(reg[74],1.000000000000000e+000);
tmcGetByIndex(reg[75],u0,1,reg[74]);
tmcDiv(reg[76],u0,reg[75]);

tmcAssign(u0,reg[76]);
//statement here,line 27

goto label_8; //branch to end IF
label_9: ; //end IF clause
label_8: ; //end IF
//statement here,line 27

// % Lines 28--28:
//   if v0(1) ~= 1, v0 = v0/(v0(1)); end; 


tmcScalar(reg[79],1.000000000000000e+000);
tmcGetByIndex(reg[80],v0,1,reg[79]);
tmcScalar(reg[81],1.000000000000000e+000);
tmcNe(reg[82],reg[80],reg[81]);
if(tmcIsFalse(reg[82])) goto label_11; // goto to the end of the clause if the expression is false


tmcScalar(reg[85],1.000000000000000e+000);
tmcGetByIndex(reg[86],v0,1,reg[85]);
tmcDiv(reg[87],v0,reg[86]);

tmcAssign(v0,reg[87]);
//statement here,line 28

goto label_10; //branch to end IF
label_11: ; //end IF clause
label_10: ; //end IF
//statement here,line 28

// % Lines 29--30:
//    

//   s = conv(g0,u0)-p; t = conv(g0,v0)-q;



//CALL function
tmcReallocRegister(reg[91]);
tmcconv(1,2, reg[91], g0, u0);

tmcSub(reg[93],reg[91],p);

tmcAssign(s,reg[93]);
//statement here,line 30



//CALL function
tmcReallocRegister(reg[97]);
tmcconv(1,2, reg[97], g0, v0);

tmcSub(reg[99],reg[97],q);

tmcAssign(t,reg[99]);
//statement here,line 30

// % Lines 31--31:
//   b = [s(2:lp)'; t(2:lq)'];   


tmcScalar(reg[102],2.000000000000000e+000);

tmcCreateColonBaseLimit(reg[104],reg[102],lp);
tmcGetByIndex(reg[105],s,1,reg[104]);
tmcTranspose(reg[106],reg[105]);
tmcCollectColumns(reg[107],1,reg[106]);

tmcScalar(reg[109],2.000000000000000e+000);

tmcCreateColonBaseLimit(reg[111],reg[109],lq);
tmcGetByIndex(reg[112],t,1,reg[111]);
tmcTranspose(reg[113],reg[112]);
tmcCollectColumns(reg[114],1,reg[113]);
tmcCollectRows(reg[115],2,reg[107],reg[114]);

tmcAssign(b,reg[115]);
//statement here,line 31

// % Lines 32--32:
//   x = [g0(2:m1)'; u0(2:n1)'; v0(2:k1)'];


tmcScalar(reg[118],2.000000000000000e+000);

tmcCreateColonBaseLimit(reg[120],reg[118],m1);
tmcGetByIndex(reg[121],g0,1,reg[120]);
tmcTranspose(reg[122],reg[121]);
tmcCollectColumns(reg[123],1,reg[122]);

tmcScalar(reg[125],2.000000000000000e+000);

tmcCreateColonBaseLimit(reg[127],reg[125],n1);
tmcGetByIndex(reg[128],u0,1,reg[127]);
tmcTranspose(reg[129],reg[128]);
tmcCollectColumns(reg[130],1,reg[129]);

tmcScalar(reg[132],2.000000000000000e+000);

tmcCreateColonBaseLimit(reg[134],reg[132],k1);
tmcGetByIndex(reg[135],v0,1,reg[134]);
tmcTranspose(reg[136],reg[135]);
tmcCollectColumns(reg[137],1,reg[136]);
tmcCollectRows(reg[138],3,reg[123],reg[130],reg[137]);

tmcAssign(x,reg[138]);
//statement here,line 32

// % Lines 33--33:
//   w = ones(length(b),1);


//CALL function
tmcReallocRegister(reg[141]);
tmclength(1,1, reg[141], b);
tmcScalar(reg[142],1.000000000000000e+000);
//CALL function
tmcReallocRegister(reg[143]);
tmcones(1,2, reg[143], reg[141], reg[142]);

tmcAssign(w,reg[143]);
//statement here,line 33

// % Lines 34--36:
//   for jj = 2:lp

//       if abs(p(jj)) > 1 

//           w(jj-1) = 1/abs(p(jj));

tmcScalar(reg[145],2.000000000000000e+000);

tmcCreateColonBaseLimit(reg[147],reg[145],lp);
tmcForIterInit(reg[148],reg[147],jj);
label_14: ; //FOR begin
if(tmcForIterNext(reg[148],reg[147])) goto label_13; // exit for


tmcGetByIndex(reg[151],p,1,jj);
//CALL function
tmcReallocRegister(reg[152]);
tmcabs(1,1, reg[152], reg[151]);
tmcScalar(reg[153],1.000000000000000e+000);
tmcGt(reg[154],reg[152],reg[153]);
if(tmcIsFalse(reg[154])) goto label_16; // goto to the end of the clause if the expression is false
tmcScalar(reg[155],1.000000000000000e+000);


tmcGetByIndex(reg[158],p,1,jj);
//CALL function
tmcReallocRegister(reg[159]);
tmcabs(1,1, reg[159], reg[158]);
tmcDiv(reg[160],reg[155],reg[159]);


tmcScalar(reg[163],1.000000000000000e+000);
tmcSub(reg[164],jj,reg[163]);
tmcGetRefByIndex(pRefHelper,w,1,reg[164]);
tmcAssign(pRefHelper,reg[160]);
//statement here,line 36

// % Lines 37--37:
//       end   

goto label_15; //branch to end IF
label_16: ; //end IF clause
label_15: ; //end IF
//statement here,line 37

// % Lines 38--38:
//   end;

label_12: ; //FOR end
goto label_14; //branch to FOR begin
label_13: ; //FOR exit
//statement here,line 38

// % Lines 39--42:
//   

//   for jj = 2:lq

//       if abs(q(jj)) > 1 

//           w(lp-2+jj) = 1/abs(q(jj));

tmcScalar(reg[165],2.000000000000000e+000);

tmcCreateColonBaseLimit(reg[167],reg[165],lq);
tmcForIterInit(reg[168],reg[167],jj);
label_19: ; //FOR begin
if(tmcForIterNext(reg[168],reg[167])) goto label_18; // exit for


tmcGetByIndex(reg[171],q,1,jj);
//CALL function
tmcReallocRegister(reg[172]);
tmcabs(1,1, reg[172], reg[171]);
tmcScalar(reg[173],1.000000000000000e+000);
tmcGt(reg[174],reg[172],reg[173]);
if(tmcIsFalse(reg[174])) goto label_21; // goto to the end of the clause if the expression is false
tmcScalar(reg[175],1.000000000000000e+000);


tmcGetByIndex(reg[178],q,1,jj);
//CALL function
tmcReallocRegister(reg[179]);
tmcabs(1,1, reg[179], reg[178]);
tmcDiv(reg[180],reg[175],reg[179]);


tmcScalar(reg[183],2.000000000000000e+000);
tmcSub(reg[184],lp,reg[183]);

tmcAdd(reg[186],reg[184],jj);
tmcGetRefByIndex(pRefHelper,w,1,reg[186]);
tmcAssign(pRefHelper,reg[180]);
//statement here,line 42

// % Lines 43--43:
//       end   

goto label_20; //branch to end IF
label_21: ; //end IF clause
label_20: ; //end IF
//statement here,line 43

// % Lines 44--44:
//   end;

label_17: ; //FOR end
goto label_19; //branch to FOR begin
label_18: ; //FOR exit
//statement here,line 44

// % Lines 45--46:
//   

//   bke = [max(abs(b.*w))]; 



tmcMulScalar(reg[189],b,w);
//CALL function
tmcReallocRegister(reg[190]);
tmcabs(1,1, reg[190], reg[189]);
//CALL function
tmcReallocRegister(reg[191]);
tmcReallocRegister(reg[192]);
tmcmax(1,1, reg[191], reg[192], reg[190],NULL,NULL);
tmcCollectColumns(reg[193],1,reg[191]);
tmcCollectRows(reg[194],1,reg[193]);

tmcAssign(bke,reg[194]);
//statement here,line 46

// % Lines 47--50:
//   

//   %fprintf('      g-n %g \n',bke(1));

//   

//   jj = 1;

tmcScalar(reg[196],1.000000000000000e+000);

tmcAssign(jj,reg[196]);
//statement here,line 50

// % Lines 51--53:
//   while jj > 0

//       

//       A = sylmat(g0,u0,v0);

label_22: ; //WHILE expression

tmcScalar(reg[199],0.000000000000000e+000);
tmcGt(reg[200],jj,reg[199]);
if(tmcIsFalse(reg[200])) goto label_24; // goto to the exit of the while if the expression is false



//CALL function
tmcReallocRegister(reg[204]);
tmcsylmat(1,3, reg[204], g0, u0, v0);

tmcAssign(A,reg[204]);
//statement here,line 53

// % Lines 54--55:
//       

//       d = scalsq(A,b,w);




//CALL function
tmcReallocRegister(reg[209]);
tmcscalsq(1,3, reg[209], A, b, w);

tmcAssign(d,reg[209]);
//statement here,line 55

// % Lines 56--56:
//       y = x - d;



tmcSub(reg[213],x,d);

tmcAssign(y,reg[213]);
//statement here,line 56

// % Lines 57--58:
//       

//       g = [1,y(1:m)']; u = [1,y(m+1:m+n)']; v = [1,y(m+n+1:m+n+k)'];

tmcScalar(reg[215],1.000000000000000e+000);

tmcScalar(reg[217],1.000000000000000e+000);

tmcCreateColonBaseLimit(reg[219],reg[217],m);
tmcGetByIndex(reg[220],y,1,reg[219]);
tmcTranspose(reg[221],reg[220]);
tmcCollectColumns(reg[222],2,reg[215],reg[221]);
tmcCollectRows(reg[223],1,reg[222]);

tmcAssign(g,reg[223]);
//statement here,line 58

tmcScalar(reg[225],1.000000000000000e+000);


tmcScalar(reg[228],1.000000000000000e+000);
tmcAdd(reg[229],m,reg[228]);


tmcAdd(reg[232],m,n);
tmcCreateColonBaseLimit(reg[233],reg[229],reg[232]);
tmcGetByIndex(reg[234],y,1,reg[233]);
tmcTranspose(reg[235],reg[234]);
tmcCollectColumns(reg[236],2,reg[225],reg[235]);
tmcCollectRows(reg[237],1,reg[236]);

tmcAssign(u,reg[237]);
//statement here,line 58

tmcScalar(reg[239],1.000000000000000e+000);



tmcAdd(reg[243],m,n);
tmcScalar(reg[244],1.000000000000000e+000);
tmcAdd(reg[245],reg[243],reg[244]);


tmcAdd(reg[248],m,n);

tmcAdd(reg[250],reg[248],k);
tmcCreateColonBaseLimit(reg[251],reg[245],reg[250]);
tmcGetByIndex(reg[252],y,1,reg[251]);
tmcTranspose(reg[253],reg[252]);
tmcCollectColumns(reg[254],2,reg[239],reg[253]);
tmcCollectRows(reg[255],1,reg[254]);

tmcAssign(v,reg[255]);
//statement here,line 58

// % Lines 59--59:
//       s = conv(g,u)-p; t = conv(g,v)-q;



//CALL function
tmcReallocRegister(reg[259]);
tmcconv(1,2, reg[259], g, u);

tmcSub(reg[261],reg[259],p);

tmcAssign(s,reg[261]);
//statement here,line 59



//CALL function
tmcReallocRegister(reg[265]);
tmcconv(1,2, reg[265], g, v);

tmcSub(reg[267],reg[265],q);

tmcAssign(t,reg[267]);
//statement here,line 59

// % Lines 60--60:
//       b = [s(2:lp)'; t(2:lq)']; bke = [bke,max(abs(b).*w)]; 


tmcScalar(reg[270],2.000000000000000e+000);

tmcCreateColonBaseLimit(reg[272],reg[270],lp);
tmcGetByIndex(reg[273],s,1,reg[272]);
tmcTranspose(reg[274],reg[273]);
tmcCollectColumns(reg[275],1,reg[274]);

tmcScalar(reg[277],2.000000000000000e+000);

tmcCreateColonBaseLimit(reg[279],reg[277],lq);
tmcGetByIndex(reg[280],t,1,reg[279]);
tmcTranspose(reg[281],reg[280]);
tmcCollectColumns(reg[282],1,reg[281]);
tmcCollectRows(reg[283],2,reg[275],reg[282]);

tmcAssign(b,reg[283]);
//statement here,line 60



//CALL function
tmcReallocRegister(reg[287]);
tmcabs(1,1, reg[287], b);

tmcMulScalar(reg[289],reg[287],w);
//CALL function
tmcReallocRegister(reg[290]);
tmcReallocRegister(reg[291]);
tmcmax(1,1, reg[290], reg[291], reg[289],NULL,NULL);
tmcCollectColumns(reg[292],2,bke,reg[290]);
tmcCollectRows(reg[293],1,reg[292]);

tmcAssign(bke,reg[293]);
//statement here,line 60

// % Lines 61--62:
//       

//       jj = jj + 1;


tmcScalar(reg[296],1.000000000000000e+000);
tmcAdd(reg[297],jj,reg[296]);

tmcAssign(jj,reg[297]);
//statement here,line 62

// % Lines 63--66:
//       %fprintf('      g-n %g,%g \n',bke(jj), norm(d));

//       

//       if bke(jj) >= bke(jj-1) 

//           g = g0; u = u0; v = v0;



tmcGetByIndex(reg[301],bke,1,jj);


tmcScalar(reg[304],1.000000000000000e+000);
tmcSub(reg[305],jj,reg[304]);
tmcGetByIndex(reg[306],bke,1,reg[305]);
tmcGe(reg[307],reg[301],reg[306]);
if(tmcIsFalse(reg[307])) goto label_26; // goto to the end of the clause if the expression is false


tmcAssign(g,g0);
//statement here,line 66



tmcAssign(u,u0);
//statement here,line 66



tmcAssign(v,v0);
//statement here,line 66

// % Lines 67--67:
//           res = bke(jj-1);



tmcScalar(reg[316],1.000000000000000e+000);
tmcSub(reg[317],jj,reg[316]);
tmcGetByIndex(reg[318],bke,1,reg[317]);

tmcAssign(res,reg[318]);
//statement here,line 67

// % Lines 68--68:
//           break;

goto label_24; //break to WHILE exit
//statement here,line 68

// % Lines 69--69:
//       end;

goto label_25; //branch to end IF
label_26: ; //end IF clause
label_25: ; //end IF
//statement here,line 69

// % Lines 70--71:
//

//       g0 = g; u0 = u; v0 = v;



tmcAssign(g0,g);
//statement here,line 71



tmcAssign(u0,u);
//statement here,line 71



tmcAssign(v0,v);
//statement here,line 71

// % Lines 72--72:
//       x = y;



tmcAssign(x,y);
//statement here,line 72

// % Lines 73--74:
//       

//   end

label_23: ; //end WHILE
goto label_22; //branch to test WHILE expression
label_24: ; //exit WHILE
//statement here,line 74

// % Lines 75--76:
//      

//  
label_1: ; //end Function
FINALLY
tmcFreeLocalVar(y);
tmcFreeLocalVar(d);
tmcFreeLocalVar(A);
tmcFreeLocalVar(bke);
tmcFreeLocalVar(jj);
tmcFreeLocalVar(w);
tmcFreeLocalVar(x);
tmcFreeLocalVar(b);
tmcFreeLocalVar(t);
tmcFreeLocalVar(s);
tmcFreeLocalVar(lq);
tmcFreeLocalVar(lp);
tmcFreeLocalVar(k1);
tmcFreeLocalVar(k);
tmcFreeLocalVar(n1);
tmcFreeLocalVar(n);
tmcFreeLocalVar(m1);
tmcFreeLocalVar(m);
tmcFreeLocalVar(v0);
tmcFreeLocalVar(u0);
tmcFreeLocalVar(g0);
tmcFreeLocalVar(q);
tmcFreeLocalVar(p);
tmcFreeRegFrame(reg);

TMC_DBG_POP_STACK_VAR(32);

ENDFINALLY
}

//FUNCTION DEFINITION ENDED
//statement here,line 76

// % Lines 77--77:
