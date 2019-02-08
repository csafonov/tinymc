function [PlantModel,Ctrl] = findcompensator(PlantModel)
%PlantModel = struct('R',pars(1),'L',pars(2),'Ts',pars(3),'Delay',pars(4));

[PlantModel] = getfrdRL(PlantModel);

kp  = linspace(100,10000,10);
w0 = 10000;
cnt=0;
Ts = PlantModel.Ts;
d = PlantModel.Delay;
R=PlantModel.R;
L=PlantModel.L;
Fmax= 0.499/Ts;
p1 = 1./(j*Fmax*2*pi*L+R);
kd1 = 1./p1;
nkd=100;nkp = 400;
w2 = pi/60/(Ts + d);

kd = linspace(0.1,200 ,nkd ) * kd1;
ze  = linspace(0.05*w2,min(20*w2,w0*0.5),nkp)   ;
w = logspace(2, log10(Fmax) ) * 2*pi;
s = j*w;

z = exp(s*Ts);
b = exp(-R/L*Ts);
numz = [0,1-b   ];
denz  = [1 ,- b];
M = 1.2;
M2 = 1.8;

b2 = exp(-w0*Ts);
numzPw = [0,1-b2   ];
denzPw  = [1 ,- b2];

        numz =conv(numzPw,numz);
        denz  =conv(denzPw,denz);
gg=[];
for cnt1=1:nkd
      waitbar( cnt1/nkd  ,'please wait');
    for cnt2=1:nkp
        KD=kd(cnt1);KP=KD*ze(cnt2);
               
        C_numz = [ KD, (KP*Ts-KD)  ];
        C_denz  = [1 , -1];
        
        
        O_numz = conv(C_numz,numz);
        O_denz  = conv(C_denz,denz);
        
        CL_numz = O_numz;
        CL_denz  = O_numz + O_denz;
        
        CL_TFz = polyval(CL_numz, z   ) ./ polyval(CL_denz, z   );
        OL_TFz = polyval(O_numz, z   ) ./ polyval(O_denz, z   );
        I_cross = find( abs(OL_TFz) < 1  );

         if  (max(abs(CL_TFz)) < M)  &&  (~isempty(I_cross)) && (max(abs(1./(1+OL_TFz))) < M2)
          cnt=cnt+1;
          Ctrl1{cnt}.KI=KP;
          Ctrl1{cnt}.KP=KD;
          Ctrl1{cnt}.w=w0;
          gg=[gg, w(I_cross(1))];
          %figure(10);
          % plot(    angle(OL_TFz)/pi*180, 20*log10(abs(OL_TFz)),'b'  ); grid on;hold on;
         
        end
        
    end
end

[gg,II] = sort(gg);
% gg = fliplr(gg);
II=fliplr(II);
nC = min(length(Ctrl1),50  );

for nn=1:nC
    I1 = II(nn);
          Ctrl{nn}.KI=Ctrl1{I1}.KI;
          Ctrl{nn}.KP=Ctrl1{I1}.KP;
          Ctrl{nn}.w=Ctrl1{I1}.w;
end