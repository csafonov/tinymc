function [plants,Fw,ki,kp,kd,polew]=TestO(pars) 
% Inputs:
% 			pars(1)= R;
% 			pars(2) = L;
% 			pars(3) = Ts;
% 			pars(4) = Delay;
% Outputs:
%   plants = P(j*w)
%   Fw      =  w [rad/sec]
%     Ki,kp,kd,polew = arrays of solutions
% e.g. pars=[ 1,1e-3,5e-6,0  ];
    PlantModel = struct('R',pars(1),'L',pars(2),'Ts',pars(3),'Delay',pars(4));
    
    [PlantModel,Ctrl] = findcompensator(PlantModel);
    plants=PlantModel.P;
    Fw     =PlantModel.F*2*pi; 
    n = length(Ctrl);
    ki  =zeros(1,n);
    kp=zeros(1,n);
    kd=zeros(1,n);
    polew=zeros(1,n);
    for kk=1:n
        if isfield(Ctrl{kk},'KI'),  ki(kk)=Ctrl{kk}.KI;end;
        if isfield(Ctrl{kk},'KP'),  kp(kk)=Ctrl{kk}.KP;end;
        if isfield(Ctrl{kk},'KD'),  kd(kk)=Ctrl{kk}.KD;end;
        if isfield(Ctrl{kk},'w'),  polew(kk)=Ctrl{kk}.w;end;
    end
