function y=TestO(x) 
% This example uses MultRoot by ZHONGGANG ZENG
% References:
% [1] ZHONGGANG ZENG, "COMPUTING MULTIPLE ROOTS OF INEXACT POLYNOMIALS",
% MATHEMATICS OF COMPUTATION,
% Volume 74, Number 250, Pages 869-903
% S 0025-5718(04)01692-8
% Article electronically published on July 22, 2004
% [2] ZHONGGANG ZENG, "MultRoot - A Matlab package computing polynomial roots and multiplicities"
% Journal ACM Transactions on Mathematical Software (TOMS), Volume 30 Issue 2, June 2004 , Pages 218-236

%e = [1,2,3];
%y = e(imag(e)>0);
%disp(y);
%return;

% www=load('D:\Data_D\HSKOST\TMC\qd_tmc\tmc_src-1.02\examples\AppEx_qd\testroot1.mat')
%figure(222);plot( real(www.xx),imag(www.xx),'r.',real(www.qxx),imag(www.qxx),'bo',real(roots(www.aa)),imag(roots(www.aa)),'gx');grid on;
% www=load('HH.mat');
% A=www.HH;
% B=www.B;
% disp(det(A));
% disp(det_qd(A));
% disp(eig(A));
% disp(eig_qd(A));
%disp(A\B);
%  disp(leftdivide_qd(A,B));
% return



ar = 0.00001;
ai  = 10;

x0 = ar + ai*j;
x1 = ar - ai*j;

va = [1, -2*ar,ar^2+ai^2];
vb = va;
vb2 = conv_qd(va,va);
vb4 = conv_qd(vb2,vb2);
vb8 = conv_qd(vb4,vb4);
vb9 = conv_qd(vb8,va);
vb9r = real(vb9);

vb = conv_qd(vb,va);
vb = conv_qd(vb,va);
vb = conv_qd(vb,va);
 vb = conv_qd(vb,va);
 vb = conv_qd(vb,va);
 vb = conv_qd(vb,va);
 vb = conv_qd(vb,va);
 vb = conv_qd(vb,va);
 
%   vb = conv(vb,va);
%  vb = conv(vb,va);
%  vb = conv(vb,va);

% aa=[1,909,367236,86545284,13111610526,1324272663126,...
%         89167692650484,3859687267585236,97457103506527209,1093685272684360901];

% aa = [ ...
% 1,...
% -0.18e-3, ...
% 900.000000,...
% -.1440000000,...
% 3.60000000e5,...
% -50.40000000,...
% 8.400000001e7,...
% -10080.00000,...
% 1.260000000e10,...
% -1.260000000e6,...
% 1.259999997e12,...
% -1.00800000e8,...
% 8.4000000e13,...
% -5.04000000e9,...
% 3.600000007e15,...
% (-1.440000000e11-2e7*i),...
% 9.00000001e16,...
% -1.800000000e12,...
% 1.000000000e18 ...
% ];
% 
% 
% aa = vb;
aa = vb9r;
aa = zeros(1,19);
 aa(1)= 1.00000000000000000000000000000000;      
 aa(2)=-1.799999954528175294399261474609375E-0004;
 aa(3)=  900.000000014399999272450813900107 ;     
 aa(4)=-0.143999996362926023501012475585038 ;     
 aa(5)=  360000.000010079999490735729728038 ;     
 aa(6)= -50.3999987271921082126226590587843 ;     
 aa(7)=  84000000.0030239998472247509180040 ;     
 aa(8)= -10079.9997454585816409967591802353 ;     
 aa(9)=  12600000000.5039999745377944863000 ;     
 aa(10)= -1259999.96818316270506093837654926  ;    
 aa(11)=  1260000000050.39999745377944863000  ;    
 aa(12)= -100799997.454585816409967591802353 ;     
 aa(13)=  84000000003023.9998472247509180040  ;    
 aa(14)= -5039999872.71921082126226590587843  ;    
 aa(15)=  3600000000100799.99490735729728038 ;     
 aa(16)= -143999996362.926023501012475585038  ;    
 aa(17)=  90000000001439999.9272450813900107  ;    
aa(18)=  -1799999954528.17529439926147460938 ;     
 aa(19)= 1000000000000000000.000000000000000 ;
  

xx =  roots( aa);
qxx =  roots_qd( aa);

disp('Roots=');
disp(xx);
for cnt=1:length(xx)
    yy(cnt) = polyval_qd(aa,xx(cnt));    
end
disp('P(roots)=');
disp(yy);
err_xx = abs(xx-(ar+j*ai));
disp('error(roots)=');
disp(err_xx);


disp('Quad Roots=');
disp(qxx);
for cnt=1:length(qxx)
    qyy(cnt) = polyval_qd(aa,qxx(cnt));    
end
disp('P(quad roots)=');
disp(qyy);

y1 = polyval_qd(aa,x0);
y2 = polyval_qd(aa,x1);
disp('P(x0,conj(x0))=');
disp([y1,y2]);


err_qxx = abs(qxx-(ar+j*ai));
disp('error(quad roots)=');
disp(err_qxx);

%disp('***********************************************');
%disp('Quad P(roots)=');
%disp(qyy);
%qerr = qxx - xx;
%disp(qerr);

disp('Polynom Coeficcients: aa=');
disp(aa);

mqq = multroot(aa);
disp('multroots=');
disp(mqq);

save('testroot1.mat','aa','xx','qxx','yy','qyy','x0','err_xx','err_qxx');



 