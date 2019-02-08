function [Mag,Ph,num,den]=resp2nd(w1,d1,w2,d2,w)
% calculate response of second-order filter
s = j*w;
P = (s.^2 +  2 * d1 * w1 * s + w1 ^ 2) ./ (s.^2 +  2 * d2 * w2 * s + w2 ^ 2  ) * (w2/w1)^2 ;
Mag = 20* log10(abs(P));
Ph = unwrap( angle( P ) ) /pi * 180;

num = [1, 2 * d1 * w1,  w1^2] / w1^2;
den = [1, 2 * d2 * w2,  w2^2] / w2^2;
