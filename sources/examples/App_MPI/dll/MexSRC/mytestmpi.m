function [x,y]=mytestmpi
%!mpiexec -n 2 MATLAB
%!mpiexec -n 10 MATLAB /r getcurloop

x = MPI_Init;
c=MPI_Comm_Load;
mm= MPI_Comm_size(c);
rr = MPI_Comm_rank(c);
disp(['size=',num2str(mm),' rank=',num2str(rr)]);
if (rr==0)
    INFO = MPI_Send(12345,[1:mm-1],188,c);
else
    [Y, INFO] = MPI_Recv(0,188,c);
    disp(Y);
end

y=MPI_Finalize;

