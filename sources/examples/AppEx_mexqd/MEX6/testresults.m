www = load ('test_mexqd', 'Fd', 'dLV', 'Fn', 'nLV',   'dLI', 'nLI', 'dLV');
Fd=www.Fd;
%dLV=www.dLV;
Fn=www.Fn;
nLV=www.nLV;
dLI=www.dLI;
nLI=www.nLI;
dLV=www.dLV;

x1 = conv(Fd,dLV);
x2 = conv(Fn,nLV);
x  = conv(x1+x2,dLI);
y  = conv(nLI,dLV);
y  = conv(y,Fn);
N = x+y;
D = y;

tic 
for cnt=1:40
RN = roots(N);
RD = roots(D);
end
toc

tic 
for cnt=1:40
RN = roots_d(N);
RD = roots_d(D);
end
toc

tic
for cnt=1:40
 RNq = roots_qd(N);
 RDq = roots_qd(D);
end
toc
 
wwwO.RNq=RNq;
wwwO.RDq=RDq;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(333);
plot(real(RN),imag(RN),'r.',real(wwwO.RNq),imag(wwwO.RNq),'b.');grid on;
legend('mat','tmc','tmcQD');
figure(334);
plot(real(polyval(N,RN)),imag(polyval(RN,RN)),'r.',...
    real(polyval(N,wwwO.RNq)),imag(polyval(N,wwwO.RNq)),'b.');grid on;
legend('mat','tmc','tmcQD');

