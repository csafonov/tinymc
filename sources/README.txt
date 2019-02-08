Release 1.11 of TMC Compiler:
- Bugs fixes
- New feature: local functions compilation
- Updated examples:
	-- usage with Embarcadero Delphi/C++ Builder
	-- MEX-function interfaces for run-time functions

Release 1.03 of TMC Compiler 
-----------------------------
- Updated examples: added examples for usage in NI LabView(TM) and NI LabWindows/CVI

Release 1.02 of TMC Compiler 
-----------------------------
- Updated reference manual
- Updated examples
- Implementation of roots_qd() function based on 128-bit float-point (quad) port of CLAPACK. 
(only Windows paltform with MINGW using GNU QUADMATH library).
- Imporved converter errors report
- Added simple development tools: 
		- tmcdbg: debugger/variables viewer 
		- tmcgra: simple visualization utility that supports figure() and plot() features for debuggin
- Changed licensing for runtime library to simplified BSD 2-Clause license

Release 1.01 of TMC Compiler 
-----------------------------

- Fixes needed for building the runtime for Windows (x86 and x64)
- Added batch and MSVC workspace files for building tmcruntime for Windows
- Added batch and MSVC workspace files for building example application for Windows
- Added example for building JNI application for Android (ADT Eclipse workspace)


Release 1.00 of TMC Compiler binaries and  sources for i486 Windows/Linux
-------------------------------------------------------------------------
Archive contents:

/examples/  example files
/tmclib/: runtime library binaries and include files
/src/tmcwood: M-to-C converter sources
/src/tmcruntime/ :  runtime sources
/doc/    : TMC compiler manual 


Installation: copy the files to a home directory 

Linux platform:

Run example: open terminal in AppEx and run make
Build runtime: run make in /src/tmcruntime/
Build converter: run make in /src/tmcwood/

Needed tools to build applications and runtime:
-----------------------------------------------
http://sourceforge.net/projects/mingw-w64/
http://sourceforge.net/projects/mingw/
ADT Eclipse (for Android application example)

Support:
-----------------------------------------------
Author blog page: http://csafonov.blogspot.co.il/p/tmc.html
Wiki page: https://sourceforge.net/p/tmc-m-files-to-c-compiler/wiki/Home/
Author direct contact e-mail: csafonov@gmail.com
Mailing list: http://sourceforge.net/p/tmc-m-files-to-c-compiler/mailman/tmc-m-files-to-c-compiler-tmccompiler/




