
% http://stackoverflow.com/questions/17506343/how-can-i-write-the-matlab-filter-function-myself

%% Specification of the Linear Chebysev filters
% clc;clear all;close all
% ord = 5; %System order (from 1 to 5)
% [bq,aq] = cheby1(ord,2,0.2);
%figure;zplane(bq,aq); % Z-Pole/Zeros
u = [ones(40,1); zeros(40,1)];
%% Naive implementation of the basic algorithm
bq = [0   0.33033681246030  -0.60768863969678   0.27784633138509];
aq = [1.00000000000000  -2.62505448450708   2.30343881244097  -0.67788982378528];
theta = [bq aq(2:end)]';
ord=length(aq)-1;
y0 = filter(bq,aq,u); % Built-in filter
b = fliplr(bq);a = fliplr(aq);a(end) = [];
y1 = zeros(40,1);pad = zeros (ord,1);
yp = [pad; y1(:)];up = [pad; u(:)];
for i = 1:length(u)
    yp(i+ord) = sum(b(:).*up(i:i+ord))-sum(a(:).*yp(i:i+ord-1));
end
y1 = yp(ord+1:end); % Naive implementation
err = y0(:)-y1(:);
figure
plot(y0,'r')
hold on
plot(y1,'*g')
xlabel('Time')
ylabel('Response')
legend('My code','Built-in filter')
figure
plot(err)
xlabel('Time')
ylabel('Error')
%% Direct Form II Transposed  
% Direct realization of rational transfer functions
% trps: 0 for direct realization, 1 for transposed realisation 
% b,a: Numerator and denominator
% x:   Input sequence
% y:   Output sequence
% u:   Internal states buffer

trps = 1;
b=theta(1:ord+1);
a=theta(ord+2:end);
y2=zeros(size(u));
x=zeros(ord,1);
%%
if trps==1
    for i=1:length(u)
        y2(i)=b(1)*u(i)+x(1);
        x=[x(2:ord);0];
        x=x+b(2:end)*u(i)-a*y2(i);
    end
else
    for i=1:length(u)
        xnew=u(i)-sum(x(1:ord).*a);
        x=[xnew,x];
        y2(i)=sum(x(1:ord+1).*b);
        x=x(1:ord);
    end
end
%%
err = y2 - filter(bq,aq,u);
figure
plot(y0,'r')
hold on
plot(y2,'*g')
xlabel('Time')
ylabel('Response')
legend('Form II Transposed','Built-in filter')
figure
plot(err)
xlabel('Time')
ylabel('Error')
% end
