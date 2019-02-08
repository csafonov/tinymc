function [F,Mag,Ph]=TestO(f1,d1,f2,d2, NumFreqs,Fmin,Fmax,Nint)
% [F,Mag,Ph]=TestO(1000,0.07,1500,0.7, 100,0.2,100000,0)
% Calculate 2nd-order filter frequency responce 

if NumFreqs <2 || f1<= 0 || f2 <=0 
    F=0; Mag=0; Ph=0;
    return;
end
if nargin <6
Fmin = min(f1,f2)*0.2;
Fmax = max(f1,f2)/0.2;
end
if (nargin <8)
    Nint=0;
end

F = logspace( log10(Fmin),log10(Fmax), NumFreqs ); 
w1 = f1*2*pi; w2 = f2*2*pi;
w = F * 2*pi;
[Mag,Ph,num,den]=resp2nd(w1,d1,w2,d2,w);
[Mag2,Ph2,num2,den2]=respint(Nint,w);
Mag = Mag+Mag2;
Ph  = Ph + Ph2;
num=conv(num,num2);
den=conv(den,den2);
save('result.mat','Mag','Ph','num','den','w1','w2','d1','d2','w','NumFreqs','Fmin','Fmax','F');

% figure(10);
% subplot(2,1,1);
% plot(F, Mag,'b');
% subplot(2,1,2);
% plot(F, Ph,'b');





