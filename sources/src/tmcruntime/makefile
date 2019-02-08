# Build TMC runtime
CC = gcc
AR = ar
RANLIB = ranlib

MYOPT= -Wformat=0 -g -lm -DMSDOS  -D STATIC_LIB_MLAPACK    -D _TMC_SITARA_ -D _TMC_EMBEDDED_ -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    
MYOPT2=-DMSDOS  -D STATIC_LIB_MLAPACK    -D _TMC_SITARA_ -D _TMC_EMBEDDED_ -D _TMC_ANDROID_ -D UNICODE -ftree-vectorize -unroll-loops --param max-unroll-times=4   -fverbose-asm    -Ofast -O2  -D TMCMEX_DLL -D SIMOLIB_EXPORTS    

OBJDIR = ./Out_lin

# find  ./OutC  -maxdepth 1   -type f -iname *.c    > OutC_listC.txt 

all: BTMCLIB BFDLIBM LAPACK BLAS BFFTLIB F2C MLAPACK TMCLIBAR


TMCLIBAR:
	find $(OBJDIR)  -maxdepth 1   -type f -iname *.o    > OutO_list_lin.txt 
	$(AR) rs tmcruntime.a  @OutO_list_lin.txt 
	$(RANLIB) tmcruntime.a
	mv  tmcruntime.a  ../../lib/linux/



BTMCLIB:
	mkdir -p $(OBJDIR)
	cd ./tmclib && \
	$(CC) -c    $(MYOPT2)  @TMCLIB_LIST.TXT &&\
	mv *.o ../$(OBJDIR)


BFDLIBM:
	mkdir -p $(OBJDIR)
	cd ./fdlibm && \
	$(CC) -c    $(MYOPT)  @FDLIB_LIST.TXT &&\
	mv *.o ../$(OBJDIR)

LAPACK:
	mkdir -p $(OBJDIR)
	cd ./lapack_lib/SRC/&& \
	$(CC) -c    $(MYOPT)  -DNO_BLAS_WRAP     @LAPACK_LIB_LIST.txt &&\
	mv *.o ../../$(OBJDIR)

BLAS:
	mkdir -p $(OBJDIR)
	cd ./lapack_lib/SRC_BLAS/&& \
	$(CC) -c    $(MYOPT)  -DNO_BLAS_WRAP     @LAPACK_BLAS_LIST.txt &&\
	mv *.o ../../$(OBJDIR)

F2C:
	mkdir -p $(OBJDIR)
	cd ./lapack_lib/SRC_F2C/&& \
	$(CC) -c    $(MYOPT)  -DMSDOS -DUSE_CLOCK -DNO_ONEXIT -DNO_BLAS_WRAP    @LAPACK_F2C_LIST.txt &&\
	mv *.o ../../$(OBJDIR)

BFFTLIB:
	mkdir -p $(OBJDIR)
	cd ./fftlib/&& \
	$(CC) -c    $(MYOPT)  @fftlib_list.txt &&\
	mv *.o ../$(OBJDIR)


MLAPACK:
	mkdir -p $(OBJDIR)
	cd ./lapack_lib/ && \
	$(CC) -c    $(MYOPT)   -D __cdecl=   MyFunc.c &&\
	mv *.o ../$(OBJDIR)



