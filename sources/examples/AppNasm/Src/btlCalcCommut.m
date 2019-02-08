function [tht,AbsOffsetCorr,AdvUsecCorr] =btlCalcCommut

JV_tests   = [750000,1000000,1500000,2000000,3000000];

FileNames={'BtlMotor1_comm_jv750000_13p6V.mat', ...
'BtlMotor1_comm_jv1000000_13p6V.mat',  ...                        
'BtlMotor1_comm_jv1500000_13p6V.mat' ,  ...                                          
'BtlMotor1_comm_jv2000000_13p6V.mat' ,  ...                 
'BtlMotor1_comm_jv3000000_6p9V.mat'  ,  ...                   
};
Thetas_min_a=[];
for cnt=1:length(JV_tests)
        www= load(FileNames{cnt});
        Iq_ave =   www.Iq_ave;
        Thetas = www.Thetas;
        
        Y1=min(Iq_ave);
        Y2=max(Iq_ave);
        [I2] =find( Iq_ave < (Y1 + 0.5*( Y2-Y1  )   )  );
        Iq_ave=Iq_ave(I2);
        Thetas=Thetas(I2);

        
        lena = length(Iq_ave);
        
        Ha = [Thetas(:).^2, Thetas(:), ones(lena,1)];
        thta = (Ha'*Ha)\(Ha'*Iq_ave(:)); % Iq_ave = Thetas^2*thta(1) + Thetas*thta(2)+thta(3)
    
    Thetas_simul = [Thetas(1):1:Thetas(end)];  
    Ha_simul = [Thetas_simul(:).^2, Thetas_simul(:), ones(length(Thetas_simul),1)];

    Iq_simul=Ha_simul*thta;
%     figure(1000);
%      plot(Thetas,Iq_ave,'r.-',Thetas_simul,Iq_simul,'b');grid on;
     [Y,I]=min(Iq_simul);
     Thetas_min_a(cnt)=Thetas_simul(I);
end


NumPoles=3;
BitsPerRev = 2^16;

EangleCorrRes = 2^16;

 Thetas_min = [3200,3600,4800,5400,6700];
 Thetas_min = Thetas_min_a;%[3200,3600,4800,5400,6700];

len = length(JV_tests);

ElecVel       =  JV_tests / BitsPerRev * NumPoles * 360;
AngleElecCorr =  Thetas_min / EangleCorrRes * 360;

H = [ElecVel(:),ones(len,1)];
tht = inv(H'*H)*(H'*AngleElecCorr(:)); % AngleElecCorr = ElecVel*tht(1) + tht(2)

figure(50);
plot(ElecVel,AngleElecCorr,'r.-',[0,ElecVel],[0,ElecVel]*tht(1)+tht(2),'b');grid on;

AbsOffsetCorr = tht(2)/360 / NumPoles * BitsPerRev;
AdvUsecCorr   = tht(1)*1e6;

% tht = FitLine(JV_tests,Thetas_min,1);

w = logspace(-1,3,1000);
s = j*w;
w0=120;w1=250;d0=0.07;d1=0.55;
P = (s.^2 + 2*d0*w0*s+w0^2)./(s.^2 + 2*d1*w1*s+w1^2)*(w1/w0)^2 ./ (s.^2) ./(s+10000)*10000;
ph=unwrap(angle(P))/pi*180 -360;
Mag=20*log10(abs(P));
figure(123);
subplot(2,1,1);
plot(w,Mag,'b');
subplot(2,1,2);
plot(w,ph,'b');
% 
% figure(124);
% subplot(2,1,1);
% plot(log10(w),Mag,'b');
% subplot(2,1,2);
% plot(log10(w),ph,'b');


