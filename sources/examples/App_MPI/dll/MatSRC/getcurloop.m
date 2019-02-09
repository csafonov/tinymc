function [PropGain,IntGain,FreqLen,FreqHz,OL_Mag,OL_Ph,CL_Mag,CL_Ph,RespLen,RespTime,Resp]=getcurloop(R,L,Ts,Ovs)
% Example: calculate open and closed loop for RL curcuit current control
% Input: R [Ohm], L [Hn] - resistance and inductance
%        Ts [sec] - sampling time of controller
%        Ovs [1..1.5] - desired maximal overshoot
% Output: 
% PropGain,IntGain : gains of PI controller
% FreqLen: number of frequencies in result
% FreqHz,OL_Mag,OL_Ph,CL_Mag,CL_Ph: vectors of
% frequencies[Hz],Magnitude[dB],Phase[deg] of open-loop and closed-loop
% RespLen: number of points of responce
% RespTime [sec],Resp - vectors of time and value of the close-loop step
% response
% Author: shmuel safonov , (C) 2017
% The code is a part of TMC Compiler examples
PropGain=[];IntGain=[];
FreqLen=0;FreqHz=[];OL_Mag=[];OL_Ph=[];CL_Mag=[];CL_Ph=[];
RespLen=0;RespTime=[];Resp=[];
if nargin==0
    R = 0.2;
    L = 0.002;
    Ts = 50e-6;
    Ovs = 1.15;
end

yyy=MPI_Init;
COMM=MPI_Comm_Load;
numproc = MPI_Comm_size(COMM);
my_rank = MPI_Comm_rank(COMM);
str = ['We are running on ',num2str(numproc), ' cores. I am ',num2str(my_rank)];
disp(str);

D  = 0.5*Ts;
PhaseM=40;GainM=-8;
MaxW = (PhaseM/360)*2*pi / (Ts+D);
L1 = -10^(GainM/20);
L2 = exp(1j*(-pi + (PhaseM/360)*2*pi));
w1 = linspace(0.01*MaxW,MaxW*10,2000);
s1 = j*w1;
B1=exp(-(D+Ts)*s1);
LL1 = L1./B1.*(s1*R+s1.*s1*L);
Ki=(real(LL1));
Kp=(imag(LL1)./w1);
II=find(Ki>0 & Kp>0 );
Ki=Ki(II);
Kp=Kp(II);

% figure(100);
% subplot(2,1,1);
% plot(w1,Kp,'r' );grid on;legend('kp');
% subplot(2,1,2);
% plot( w1,Ki,'b');grid on;legend('ki');
w = logspace(log10(1) ,log10(0.5./Ts*2*pi),1000);
s = 1j*w;
z = s*Ts;
Ph2=angle(L2);
if Ph2>0
    Ph2=Ph2-2*pi;
end

Sol_opt=[];Ovs_Opt=[];Lopen_opt=[];

if my_rank==0 % master
    Ovs_array = [0.8:0.05:1.2]*Ovs;
    disp(' distribute the task between the processes');
    Ovs_array_len  = length(Ovs_array);
    LL=Ovs_array_len;
    Tasks = cell(1,numproc);
    PortionPerProcess = ceil(Ovs_array_len / numproc);
    for kk=1:numproc
        Tasks{kk} = Ovs_array([1:PortionPerProcess] + (kk-1)*PortionPerProcess);
        LL=LL-PortionPerProcess;
        if LL==0
            break;
        end
    end
    if LL>0
        Tasks{numproc} = [Tasks{numproc}, Ovs_array(end-LL:end) ];
    end
    
    RANKS  = [0:numproc-1];
    nActiveProc = numproc;
    for cnt=2:numproc
        INFO = MPI_Send(Tasks{cnt},RANKS(cnt),0,COMM);
        if isempty(Tasks{cnt})
            nActiveProc=nActiveProc-1;
        end
    end
    MyTask = Tasks{1};
else
    [MyTask, INFO] = MPI_Recv(0,0,COMM);
    disp('Received matrix:');
    disp(MyTask);
    if isempty(MyTask)
        yyy2=MPI_Finalize;
        if my_rank>0
            exit;
        return;
        end
    end
end


%//for NomC=[0.8:0.05:1.2]*Ovs
yy_opt=[];
for NomC=MyTask
    %%    figure(300);%clf;
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
        if ~isempty(II1) && Ph1 >= Ph2 && max(abs(CL)) < NomC && max(abs(CL)) > 1.05 
            %             plot(unwrap(angle(Lopen))/pi*180,20*log10(abs(Lopen)),'b',...
            %                 angle(L1)/pi*180-360,20*log10(abs(L1)),'go',...
            %                 angle(L2)/pi*180 ,20*log10(abs(L2)),'ro');grid on;hold on;
            Sol=[ Sol ; Kp(kk),Ki(kk),w(II1)/2/pi];
        end
    end
    %disp(Sol)
    if  isempty(Sol)
        % no solution found
        disp('no solution found in this iteration,next ...');
        continue;
    end
    [YY,n]=max(Sol(:,2));
    kp0=Sol(n,1);ki0=Sol(n,2);
    Lopen0 = (kp0+ki0./s)./(R+s*L) .* exp(-(D+Ts).*s);
    %  Lopen0 = (kp0+Ts*ki0./(z-1))./(R+s*L) .* exp(-(D+Ts).*s);
    
    %%// plot(unwrap(angle(Lopen0))/pi*180,20*log10(abs(Lopen0)),'m.-',...
    %%//     angle(L1)/pi*180-360,20*log10(abs(L1)),'go',...
    %%//     angle(L2)/pi*180 ,20*log10(abs(L2)),'ro');grid on;hold on;
    
    %     sysP = tf(1,[L,R]) * tf([kp0,ki0],[1,0] );
    %     sysCL = sysP/(1+sysP);
    % figure(999);
    % step(sysCL,3e-3);
    
    %%    figure(1000);
    
    rden= -R/L;
    rdend=exp(rden*Ts);
    sysP1d=[0, 1/R*(1-rdend) ; 1,-rdend];
    sysP2d=[kp0 ,ki0*Ts-kp0 ; 1,-1];
    sysPd = [conv(sysP1d(1,:),sysP2d(1,:)) ; ...
            conv(sysP1d(2,:),sysP2d(2,:))];
    sysPCLd = [ sysPd(1,:); sysPd(1,:)+sysPd(2,:) ];
    
    
    num = sysPCLd(1,:);den=sysPCLd(2,:);
    yy=filter_( num,den,ones(1,floor(3e-3/Ts)));
    %% // plot([0:length(yy)-1]*Ts,yy,'b');grid on;hold on;
    ActOvs = max(yy);
    % Local optimization
    if isempty(Ovs_Opt) || abs(ActOvs-Ovs) < abs(Ovs_Opt-Ovs)
        Ovs_Opt=ActOvs;Lopen_opt=Lopen0;
        CL_Opt=Lopen_opt./(1+Lopen_opt);
        Sol_opt = [kp0,ki0];
        yy_opt=yy;
    end
    
end

if my_rank==0 % master
    RANKS  = [0:nActiveProc-1];
    for cnt=2:nActiveProc
        g_Sol_opt = MPI_Recv(RANKS(cnt),0,COMM);
                 if ~isempty(g_Sol_opt)
                     g_Ovs_Opt = MPI_Recv(RANKS(cnt),0,COMM);
                     g_Lopen_opt = MPI_Recv(RANKS(cnt),0,COMM);
                     g_CL_Opt = MPI_Recv(RANKS(cnt),0,COMM);
                     g_yy_opt = MPI_Recv(RANKS(cnt),0,COMM);
                 end
    end
    % Global optimization  
        if isempty(Ovs_Opt) || abs(g_Ovs_Opt-Ovs) < abs(Ovs_Opt-Ovs)
            Ovs_Opt=g_Ovs_Opt;
            Lopen_opt=g_Lopen_opt;
            CL_Opt=g_CL_Opt;
            Sol_opt = g_Sol_opt;
            yy_opt=g_yy_opt;
        end
        

    
else
    MPI_Send(Sol_opt,0,0,COMM); 
        if ~isempty( Sol_opt)
         MPI_Send([Ovs_Opt],0,0,COMM);   
         MPI_Send([Lopen_opt],0,0,COMM);
         MPI_Send([CL_Opt],0,0,COMM);
         MPI_Send([yy_opt],0,0,COMM);
        end
end
%% // plot([0:length(yy)-1]*Ts,yy_opt,'r-');grid on;hold on;
if ~isempty(Sol_opt)
    PropGain=Sol_opt(1);
    IntGain=Sol_opt(2);
    FreqHz = w/2/pi;
    FreqLen=length(FreqHz);
    CL_Opt=Lopen_opt./(1+Lopen_opt);
    OL_Mag = 20*log10(abs(Lopen_opt));
    OL_Ph = unwrap(angle(Lopen_opt))/pi*180;
    CL_Mag = 20*log10(abs(CL_Opt));
    CL_Ph = unwrap(angle(CL_Opt))/pi*180;
    RespTime = [0:length(yy_opt)-1]*Ts;
    Resp=yy_opt;
    RespLen=length(RespTime);
    % figure(3000);
    % subplot(2,1,1);
    % semilogx(FreqHz,CL_Mag,'b');ylabel('db');grid on;
    % subplot(2,1,2);
    % semilogx(FreqHz,CL_Ph,'b');ylabel('Deg');grid on;xlabel('Hz');
    save(['R_',num2str(my_rank),'result.mat'],'PropGain','IntGain','OL_Mag','OL_Ph','CL_Mag','CL_Ph','RespTime','Resp','R','L','Ts','Ovs');
    % 
    % figure(2000);
    % subplot(2,1,1);
    %bode(sysCL);
end

yyy2=MPI_Finalize;
if my_rank>0
    exit;
end










