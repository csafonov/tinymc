function S=solvemyeq(a,b,ep1)
% S=solvemyeq(-10000,10000,1e-6)
global ite;
ite=0;

if ep1 < eps*5
    ep1=eps*5;
end

y1 = myeq( a);
y2 = myeq( b);
if sign(y1) == sign(y2)
    S=[];
    return;
end

x1=a;
x2=b;

while abs(x1-x2)  > ep1
    x0 = 0.5*(x1+x2);
    y0 = myeq( x0  );
    if  abs(y0) <= eps 
            break;
    end
    if sign(y0) ~= sign(x0)
        x2 = x0;
    else
        x1 = x0;
    end
end

S.x0 = x0;
S.y0 = y0;

xx=[1,3,4,5,6,10000];
rr=roots(xx);
disp(rr);
yy=polyval(xx,rr);
disp(yy);

S.rr=rr;
S.yy=yy;

% Open this comment to check if SEH is supported
% try 
%     disp(S.oo);
% catch
%     S.oo='SEH supported';
% end
disp(S)

function y=myeq(x)
global ite
y = x.^2 .* sin (x) - x.^3 .* cos(x) + x;

y = ExMex1(y , y);
ite=ite+1;

endfunction % for demonstration of OCTAVE syntax support



