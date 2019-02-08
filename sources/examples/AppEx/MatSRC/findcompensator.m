function [PlantModel,Ctrl] = findcompensator(PlantModel)
%PlantModel = struct('R',pars(1),'L',pars(2),'Ts',pars(3),'Delay',pars(4));

[PlantModel] = getfrdRL(PlantModel);

kd = linspace(0.1,100 ,10 );
kp  = linspace(100,10000,10);
w0 = 10000;
cnt=0;
for cnt1=1:10
    for cnt2=1:10
        cnt=cnt+1;
        Ctrl{cnt}.KP=kp(cnt1);
        Ctrl{cnt}.KD=kd(cnt2);
        Ctrl{cnt}.w=w0;
    end
end