NI_LabViewEx, NI_LabViewDLLEx
--------------

Example of usage TMC Compiler generated DLL in LabView

- Copy the examples to tmc_src-1.02\examples installation
- Run MakeEx1_minigw.bat in examples\NI_LabViewDLLEx to create C-files
- Build DLL from MSVC workspace in buildmsvc (SIMOR.DLL)
- Copy SIMOR.DLL --> NI_LabViewEx\Libs and rename to FiltView.dll
- Open NI_LabViewEx.lvproj, FiltView.vi

Demo: after change w1,d1,w2,d2 parameters timer calls a function in  FiltView.dll
that calculates the frequency responce that is displayed on the graph.



