function y=filter_(b,a,u)
%see http://stackoverflow.com/questions/17506343/how-can-i-write-the-matlab-filter-function-myself
%% Direct Form II Transposed  
% Direct realization of rational transfer functions
% trps: 0 for direct realization, 1 for transposed realisation 
% b,a: Numerator and denominator
% x:   Input sequence
% y:   Output sequence
% u:   Internal states buffer

% trps = 1;
% b=theta(1:ord+1);
% a=theta(ord+2:end);
a0 = a(1);
a = a(2:end)'/a0;
b =b' /a0;
y=zeros(size(u));
ord = length(b)-1;
x=zeros(ord,1);
%%
% if trps==1
    for k=1:length(u)
        y(k)=b(1)*u(k)+x(1);
        x=[x(2:ord);0];
        x=x+b(2:end)*u(k)-a*y(k);
    end
% else
%     for k=1:length(u)
%         xnew=u(k)-sum(x(1:ord).*a);
%         x=[xnew,x];
%         y(k)=sum(x(1:ord+1).*b);
%         x=x(1:ord);
%     end
% end
