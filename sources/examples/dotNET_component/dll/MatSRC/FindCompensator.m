R = 0.2;
L = 0.002;
Ts = 90e-6;
D  = 0.5*Ts;
Ovs = 1.15;
PM=35;GM=-8;
MaxW = (PM/360)*2*pi / (Ts+D);
L1 = -10^(GM/20);
L2 = exp(1j*(-pi + (PM/360)*2*pi));
w1 = linspace(0.01*MaxW,MaxW*10,4000);
s1 = j*w1;
B1=exp(-(D+Ts)*s1);
LL1 = L1./B1.*(s1*R+s1.*s1*L);
Ki=(real(LL1));
Kp=(imag(LL1)./w1);
figure(100);
subplot(2,1,1);
plot(w1,Kp,'r' );grid on;legend('kp');
subplot(2,1,2);
plot( w1,Ki,'b');grid on;legend('ki');
w = logspace(log10(1) ,log10(0.5./Ts*2*pi),1000);
s = 1j*w;
z = s*Ts;
Ph2=angle(L2);
if Ph2>0
    Ph2=Ph2-2*pi;
end

errOvs=1;nn=0;
NomC=Ovs;
while abs(errOvs) > 0.03 && nn<5
    nn=nn+1;
figure(300);clf;
Sol=[];
for kk=1:length(Kp)
     Lopen = (Kp(kk)+Ki(kk)./s)./(R+s*L) .* exp(-(D+Ts).*s);
   %  Lopen = (Kp(kk)+Ts*Ki(kk)./(z-1))./(R+s*L) .* exp(-(D+Ts).*s);
    II1 = find( abs(Lopen)>1);
    if ~isempty(II1)
        II1=II1(end);
        Ph1 = angle(Lopen(II1));
        if Ph1>0
            Ph1=Ph1-2*pi;
        end
    else
        Ph1 = -100;
    end
    
    CL = abs(Lopen./(1+Lopen));
   % Ph1=1000;
    if ~isempty(II1) && Ph1 >= Ph2 && max(abs(CL)) < NomC && max(abs(CL)) >1.05 && Kp(kk)>0 && Ki(kk)>0
        plot(unwrap(angle(Lopen))/pi*180,20*log10(abs(Lopen)),'b',...
            angle(L1)/pi*180-360,20*log10(abs(L1)),'go',...
            angle(L2)/pi*180 ,20*log10(abs(L2)),'ro');grid on;hold on;
        Sol=[ Sol ; Kp(kk),Ki(kk),w(II1)/2/pi];
    end
end
%disp(Sol)
[YY,n]=max(Sol(:,2));
kp0=Sol(n,1);ki0=Sol(n,2);
    Lopen0 = (kp0+ki0./s)./(R+s*L) .* exp(-(D+Ts).*s);
%  Lopen0 = (kp0+Ts*ki0./(z-1))./(R+s*L) .* exp(-(D+Ts).*s);

        plot(unwrap(angle(Lopen0))/pi*180,20*log10(abs(Lopen0)),'m.-',...
            angle(L1)/pi*180-360,20*log10(abs(L1)),'go',...
            angle(L2)/pi*180 ,20*log10(abs(L2)),'ro');grid on;hold on;

sysP = tf(1,[L,R]) * tf([kp0,ki0],[1,0] );
sysCL = sysP/(1+sysP);
figure(999);
step(sysCL,3e-3);
figure(1000);

rden= -R/L;
rdend=exp(rden*Ts);
sysP1d=[0, 1/R*(1-rdend) ; 1,-rdend];
sysP2d=[kp0 ,ki0*Ts-kp0 ; 1,-1];
sysPd = [conv(sysP1d(1,:),sysP2d(1,:)) ; ...
        conv(sysP1d(2,:),sysP2d(2,:))];
sysPCLd = [ sysPd(1,:); sysPd(1,:)+sysPd(2,:) ];

%[numz,denz]=tfdata(c2d(sysCL,100e-6),'v');
% [numa,dena]=tfdata( sysCL ,'v');
% rn=roots(numa);
% rd=roots(dena);
% rn2 = exp(rn*Ts);
% rd2 = exp(rd*Ts);
% numd = poly(rn2)
% dend = poly(rd2)
% num=1;
% for k=1:length(rn2)
%     num=conv(num,[1,-rn2(k)]);
% end
% den=1;
% for k=1:length(rd2)
%     den=conv(den,[1,-rd2(k)]);
% end
num = sysPCLd(1,:);den=sysPCLd(2,:);
yy=filter_( num,den,ones(1,floor(3e-3/Ts)));
plot([0:length(yy)-1]*Ts,yy,'r');grid on;
ActOvs = max(yy);
errOvs = (Ovs-ActOvs);
NomC = NomC * (1+errOvs*0.2);
end
figure(2000);
bode(sysCL);






