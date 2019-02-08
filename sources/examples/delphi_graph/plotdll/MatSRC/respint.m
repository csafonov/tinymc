function [Mag,Ph,num,den]=respint(Ni,w)
% calculate response of integrators
s = j*w;
% if Ni>0
%     P = 1./ s;
% else
%     P = ones(1,length(w));
% end
 P = 1./ (s.^Ni);
Mag = 20*log10(abs(P));
Ph = unwrap( angle( P ) ) /pi * 180;
num = 1;
den = [1,zeros(1,Ni)];
