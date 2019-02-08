function [unusedy,unusedm]=TestO(x,n)
global VV

p = [1 1 200 1 1 1 1 1 1 1 1 10 1 1 1 1 1 1 1 1 1 1 1 1 1 1 ];
y = roots(p);
y_a = angle(y);
[y_a,I]=sort(y_a);
y=y(I);

y =y ;%.* exp(abs(y_a) - abs(y_a(1)));

y_r=real(y);
y_i = imag(y);
 figure(500);
 plot(y_r,y_i);


%return;



p = [1,2,3];
y = roots(p);
x = polyval(p,y);

d=CheckVar1(p,y);

disp(y);
disp(x);
disp(d-x);

[tht,AbsOffsetCorr,AdvUsecCorr] =btlCalcCommut;
% disp(AbsOffsetCorr);
% disp(AdvUsecCorr);
str=sprintf('correction to AbsOffset=%d, AdvUsec=%d',AbsOffsetCorr,AdvUsecCorr);
disp(str);


