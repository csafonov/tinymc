function [PropGain,IntGain,FreqLen,FreqHz,OL_Mag,OL_Ph,CL_Mag,CL_Ph,RespLen,RespTime,Resp]=TestO(R,L,Ts,Ovs)

COMM=MPI_Comm_Load;
numproc = MPI_Comm_size(COMM);
%my_rank = MPI_Comm_rank(COMM);
%str = ['We are running on ',num2str(numproc), ' cores. I am ',num2str(my_rank)];
%disp(str);

%RANKS  = [0:numproc-1];
%if (my_rank==0)
%	INFO = MPI_Send([1,-2 ; 3+2i,i],RANKS(2:end),0,COMM);
%else
%	[Y, INFO] = MPI_Recv(0,0,COMM);
%	disp('Received matrix:');
%	disp(Y);
%end
save ('in1.mat','R','L','Ts','Ovs','numproc');
[PropGain,IntGain,FreqLen,FreqHz,OL_Mag,OL_Ph,CL_Mag,CL_Ph,RespLen,RespTime,Resp]=getcurloop(R,L,Ts,Ovs);