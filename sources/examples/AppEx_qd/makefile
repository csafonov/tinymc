# Example AppEx makefile
# Demonstrates convertion m (matlab) files to C and compilation the final executable againts tmcruntime.a

TMCC   = ../../bin/tmcco.out
TMCINC = ../../include
TMCLIB = ../../lib


# rem -P: generate lsp-output
# -d : include debug info (C-gen)
# -lm: include math functions support  (put it AFTER the file that need it)

MYOPT =-Wformat=0  -ftree-vectorize -unroll-loops --param max-unroll-times=4 -fverbose-asm -Ofast -O3 -D TMCMEX_DLL -D SIMOLIB_EXPORTS -D _TMC_SITARA_ -D _TMC_EMBEDDED_ 
MYOPT2 = -DTMC_NO_SEH=";"  -DTRY=";" -DCATCH=";" -DENDCATCH=";" -DFINALLY=";"  -DENDFINALLY=";"  -DBLG_GCC -DEXTINY0_EXPORTS

all:  CFILES EFILE ERUN
#all: EFILE

CFILES:
	echo Symbol table generation from m-files  1st pass 
	mkdir -p  ./OutL
	mkdir -p  ./OutC
	cp ./Stubs/external_fnc.sym.dat  ./OutL/external_fnc.sym.dat
	$(TMCC)  -P -L -w TestO  -r ./Stubs/TestO.m -h $(TMCINC)/ -l ./OutL/testO.lsp.txt -@ woo1_rsp.txt  -o ./OutL/ >>out.txt
	cp 	./OutL/TestO.sym.dat ./Stubs/
	echo Generating C files...
	-$(TMCC)  -c -C   -q  -g2  -w TestO  -r ./Stubs/TestO.m -l ./OutC/testO2.err.log -@ woo2_rsp2.txt  -o ./OutC/ >outC2.txt

EFILE:  
	mkdir -p ./OutO
	find  ./OutC  -maxdepth 1   -type f -iname *.c    > OutC_listC.txt 
	gcc  $(MYOPT) $(MYOPT2)  -D UNICODE -I$(TMCINC)/  -I./Stubs/ @OutC_listC.txt ./MexSRC/ExMex1.c ./App_caller/Extiny_caller.c  $(TMCLIB)/tmcruntime.a -lm -o Ex1.out
	-mv *.o ./OutO
	
ERUN: ./Ex1.out
	./Ex1.out
# Must put cd && togather to be in one shell: #	cd  ./OutC/ && \