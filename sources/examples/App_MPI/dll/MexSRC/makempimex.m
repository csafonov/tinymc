% makempimex
%!set MSMPI_LIB32
%!set MSMPI_LIB64
%!set MSMPI_INC
%-I..\..\..\..\include\
b64=1;
if ~b64
mex C:\MyClaster\MPI\Lib\x86\msmpi.lib -output MPI_Comm_size -DMATLAB_MEX_FILE -DTMC_MAKEMEX -DTMCMEX_NAME#1 -DMSMPI_NO_SAL -DMSMPI_NO_DEPRECATE_20 -IC:\MyClaster\MPI\Include\   tmc_mpi.c
mex C:\MyClaster\MPI\Lib\x86\msmpi.lib -output MPI_Init -DMATLAB_MEX_FILE -DTMC_MAKEMEX -DTMCMEX_NAME#2 -DMSMPI_NO_SAL -DMSMPI_NO_DEPRECATE_20 -IC:\MyClaster\MPI\Include\   tmc_mpi.c
else
mex C:\MyClaster\MPI\Lib\x64\msmpi.lib -output MPI_Comm_size -DMATLAB_MEX_FILE -DTMC_MAKEMEX -DTMCMEX_NAME#1 -DMSMPI_NO_SAL -DMSMPI_NO_DEPRECATE_20 -IC:\MyClaster\MPI\Include\   tmc_mpi.c
mex C:\MyClaster\MPI\Lib\x64\msmpi.lib -output MPI_Init -DMATLAB_MEX_FILE -DTMC_MAKEMEX -DTMCMEX_NAME#2 -DMSMPI_NO_SAL -DMSMPI_NO_DEPRECATE_20 -IC:\MyClaster\MPI\Include\   tmc_mpi.c
mex C:\MyClaster\MPI\Lib\x64\msmpi.lib -output MPI_Finalize -DMATLAB_MEX_FILE -DTMC_MAKEMEX -DTMCMEX_NAME#MPI_Finalize_fn -DMSMPI_NO_SAL -DMSMPI_NO_DEPRECATE_20 -IC:\MyClaster\MPI\Include\   tmc_mpi.c
mex C:\MyClaster\MPI\Lib\x64\msmpi.lib -output MPI_Comm_Load -DMATLAB_MEX_FILE -DTMC_MAKEMEX -DTMCMEX_NAME#MPI_Comm_Load_fn -DMSMPI_NO_SAL -DMSMPI_NO_DEPRECATE_20 -IC:\MyClaster\MPI\Include\   tmc_mpi.c
mex C:\MyClaster\MPI\Lib\x64\msmpi.lib -output MPI_Comm_rank -DMATLAB_MEX_FILE -DTMC_MAKEMEX -DTMCMEX_NAME#MPI_Comm_rank_fn -DMSMPI_NO_SAL -DMSMPI_NO_DEPRECATE_20 -IC:\MyClaster\MPI\Include\   tmc_mpi.c

mex C:\MyClaster\MPI\Lib\x64\msmpi.lib -output MPI_Send -DMATLAB_MEX_FILE -DTMC_MAKEMEX -DTMCMEX_NAME#MPI_Send_fn -DMSMPI_NO_SAL -DMSMPI_NO_DEPRECATE_20 -IC:\MyClaster\MPI\Include\   tmc_mpi.c
mex C:\MyClaster\MPI\Lib\x64\msmpi.lib -output MPI_Recv -DMATLAB_MEX_FILE -DTMC_MAKEMEX -DTMCMEX_NAME#MPI_Recv_fn -DMSMPI_NO_SAL -DMSMPI_NO_DEPRECATE_20 -IC:\MyClaster\MPI\Include\   tmc_mpi.c
    
end

disp('done');
