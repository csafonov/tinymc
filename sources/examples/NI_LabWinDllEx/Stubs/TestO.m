function [r,y]=TestO(p) 
% calculate roots of a polynom

r = roots(p);
y = polyval(p,r);


