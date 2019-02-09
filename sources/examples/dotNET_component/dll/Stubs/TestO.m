function [PropGain,IntGain,FreqLen,FreqHz,OL_Mag,OL_Ph,CL_Mag,CL_Ph,RespLen,RespTime,Resp]=TestO(R,L,Ts,Ovs)
save ('in1.mat','R','L','Ts','Ovs');
[PropGain,IntGain,FreqLen,FreqHz,OL_Mag,OL_Ph,CL_Mag,CL_Ph,RespLen,RespTime,Resp]=getcurloop(R,L,Ts,Ovs);