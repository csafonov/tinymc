function [PlantModel] = getfrdRL(PlantModel)
%PlantModel = struct('R',pars(1),'L',pars(2),'Ts',pars(3),'Delay',pars(4));
% calculate frequency-domain RL model: 1/(sL+R) with delay.
PlantModel.F = logspace(0.1, log10( 0.49/PlantModel.Ts   ), 100);
w = PlantModel.F*2*pi;
s  = j*w;
D = exp(-s*PlantModel.Delay);
PlantModel.P = 1./(s*PlantModel.L + PlantModel.R) .* D;

