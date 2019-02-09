App_MPI example demonstrates the usage of MPI interface for multi-processor calculations.

The directory contents:
App_caller     - the caller application
dll            - TMC-generated DLL code
dll_getcurloop - MSVC project for the DLL comilation

MS MPI interface (tested with v 9.0.12497) should be installed for the usage of this code.

Usage the compiled code:

1. Run on the local machine with >= 12 cores:
call mpiexec -n 12 SIMO_caller.exe

2. Run on 2 machines:
  - Run the server application
	 call smpd -d 3
    at each mashine (e.g. >= 12 cores) under the same username and password (e.g. mpiuser)
  - Run 
	mpiexec -hosts 2 localhost 12 host2 12 C:\MyClaster\SIMO_caller.exe
    at the local machine under mpiuser name. The SIMO_caller.exe should be installed
    at each machine in the same directory e.g. C:\MyClaster\

Put tmcrtvc8_x64.dll library in the application folder.

The MPI interface may be tested also in 64-bit MATLAB using MEX-files (*.mexw64) that
are in \dll\MexSRC






