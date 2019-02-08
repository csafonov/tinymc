// tmcio.c
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC Runtime software is covered under covered by simplified BSD 2-Clause license.
 * 
  *****************************************************************************/

#include "tmc.h"
#include "clapack_types.h"

#include  <math.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h> // ANSI compatibility

#if !defined(_TMC_EMBEDDED_) || defined(_TMC_ANDROID_)
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#if !defined(_TMC_ANDROID_)
#include <io.h>
#else
#define _write write
#define _lseek lseek
#define _open open
#define _close close
#define	_read	read
#define	_wopen my_wopen
#define	_O_RDONLY O_RDONLY
#define _O_BINARY 0  //O_BINARY
#define  _O_RDWR  O_RDWR
#define  _O_CREAT O_CREAT
#define	 _O_TRUNC O_TRUNC
#define	 _S_IREAD (S_IRUSR|S_IROTH)		// see sys/stat.h. 
#define	 _S_IWRITE (S_IWUSR|S_IWOTH)
#define  filelength my_filelength
#endif
#endif
#include <stdio.h>

static char *s_module="tmcio.c";

//////////////

enum MATdatatypes
{
mi_INT8    =1, 
mi_UINT8   =2,
mi_INT16   =3,
mi_UINT16  =4,
mi_INT32   =5,
mi_UINT32  =6,
mi_SINGLE  =7, 
mi_DOUBLE  =9,
mi_INT64  =12,
mi_UINT64 =13,
mi_MATRIX =14
};
enum MATclasses
{
mx_CELL_CLASS    =1, 
mx_STRUCT_CLASS  =2, 
mx_OBJECT_CLASS  =3, 
mx_CHAR_CLASS    =4, 
mx_SPARSE_CLASS  =5, 
mx_DOUBLE_CLASS  =6, 
mx_SINGLE_CLASS  =7, 
mx_INT8_CLASS    =8, 
mx_UINT8_CLASS  = 9, 
mx_INT16_CLASS  =10, 
mx_UINT16_CLASS =11, 
mx_INT32_CLASS  =12, 
mx_UINT32_CLASS =13 
};

struct Cdatelmtype
{
	long Idat[2];
	long dsz;
	long dtype;
	char bCompress;
};

union buf_long
{
	long x;
	char b[4];
};
union buf_short
{
	short x;
	char b[2];
};
union buf_longlong
{
	__int64 x;
	char b[8];
};
union buf_single
{
	float x;
	char b[4];
};
union buf_double
{
	double x;
	char b[8];
};



void elmdata2double(double **DimsArr,long *DimsArr_len,const char *buf,const struct Cdatelmtype *datelmtype)
{
long len=0;
double *dptr=0;
long k ;
	union buf_long  l;
	union buf_short s;
	union buf_longlong ll;
	union buf_single f;
	union buf_double d;

	switch (datelmtype->dtype)
	{
	case mi_INT8://    =1, 
	case mi_UINT8://   =2,
		len = datelmtype->dsz;
		if (len>0)
		dptr = (double*)MYMALLOC(len*sizeof(double));

		for (k=0;k<len;k++)
		{
			if (datelmtype->dtype==mi_INT8)
			{
				dptr[k]= (double)(signed char)buf[datelmtype->Idat[0]+k];
			}
			else
			{
				dptr[k]= (double)(unsigned char)buf[datelmtype->Idat[0]+k];
			}
		}
		break;

	case mi_INT16://   =3,
	case mi_UINT16://  =4,
		len = (datelmtype->dsz >>1);
		if (len>0)
		dptr = (double*)MYMALLOC(len*sizeof(double));
		for (k=0;k<len;k++)
		{
				s.b[0]= buf[datelmtype->Idat[0]+k*2];//1
				s.b[1]= buf[datelmtype->Idat[0]+k*2+1];//256
			if (datelmtype->dtype==mi_INT16)
			{

				dptr[k]= (double)(signed short)s.x;
			}
			else
			{
				dptr[k]= (double)(unsigned short)s.x;
			}

		}
		break;

	case mi_INT32://   =5,
	case mi_UINT32://  =6,
		len = (datelmtype->dsz >>2);
		if (len>0)
		dptr = (double*)MYMALLOC(len*sizeof(double));
		for (k=0;k<len;k++)
		{

				l.b[0]= buf[datelmtype->Idat[0]+k*4];//1
				l.b[1]= buf[datelmtype->Idat[0]+k*4+1];//256
				l.b[2]= buf[datelmtype->Idat[0]+k*4+2];//256^2
				l.b[3]= buf[datelmtype->Idat[0]+k*4+3];//256^3
			if (datelmtype->dtype==mi_INT32)
			{

				dptr[k]= (double)(signed long)l.x;
			}
			else
			{
				dptr[k]= (double)(unsigned long)l.x;
			}
		}
		break;

	case mi_SINGLE://  =7, 
		len = (datelmtype->dsz >>2);
		if (len>0)
		dptr = (double*)MYMALLOC(len*sizeof(double));

		for (k=0;k<len;k++)
		{

				f.b[0]= buf[datelmtype->Idat[0]+k*4]; 
				f.b[1]= buf[datelmtype->Idat[0]+k*4+1]; 
				f.b[2]= buf[datelmtype->Idat[0]+k*4+2]; 
				f.b[3]= buf[datelmtype->Idat[0]+k*4+3]; 

				dptr[k]= (double) f.x;
		}

		break;

	case mi_DOUBLE://  =9,
		len = (datelmtype->dsz >>3);
		if (len>0)
		dptr = (double*)MYMALLOC(len*sizeof(double));


		for (k=0;k<len;k++)
		{

				d.b[0]= buf[datelmtype->Idat[0]+k*8];
				d.b[1]= buf[datelmtype->Idat[0]+k*8+1];
				d.b[2]= buf[datelmtype->Idat[0]+k*8+2];
				d.b[3]= buf[datelmtype->Idat[0]+k*8+3];

				d.b[4]= buf[datelmtype->Idat[0]+k*8+4];
				d.b[5]= buf[datelmtype->Idat[0]+k*8+5];
				d.b[6]= buf[datelmtype->Idat[0]+k*8+6];
				d.b[7]= buf[datelmtype->Idat[0]+k*8+7];

				dptr[k]= (double)d.x;
		}


		break;
	case mi_INT64://  =12,
	case mi_UINT64:// =13,
		len = (datelmtype->dsz >>3);
		if (len>0)
		dptr = (double*)MYMALLOC(len*sizeof(double));

		for (k=0;k<len;k++)
		{

				ll.b[0]= buf[datelmtype->Idat[0]+k*8];//1
				ll.b[1]= buf[datelmtype->Idat[0]+k*8+1];//256
				ll.b[2]= buf[datelmtype->Idat[0]+k*8+2];//256^2
				ll.b[3]= buf[datelmtype->Idat[0]+k*8+3];//256^3

				ll.b[4]= buf[datelmtype->Idat[0]+k*8+4];//256^4
				ll.b[5]= buf[datelmtype->Idat[0]+k*8+5];//256^5
				ll.b[6]= buf[datelmtype->Idat[0]+k*8+6];//256^6
				ll.b[7]= buf[datelmtype->Idat[0]+k*8+7];//256^7
			if (datelmtype->dtype==mi_INT64)
			{

				dptr[k]= (double)ll.x;
			}
			else
			{
				if ((double)ll.x>=0)
						dptr[k]= (double)ll.x;
				else
						dptr[k]= (double)ll.x + 9223372036854775808.0;//pow(2,64);
						
			}
		}

		break;

	//case mi_MATRIX:// =14

	default:
		;
	}
	*DimsArr_len = len;
	*DimsArr = dptr;

/*
x = A([Idat(1)+[0:dsz-1]]);

switch dtype
    case 1 % miINT8
         I=find(x>=128);
         x(I)=x(I)-256;
         y = x ; 
         
    case 2 % miUINT8
         y = x ; 
    case 3 % miINT16
         len = length(x)/2;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*2+1),x((k-1)*2+2)] * [1;256];
         end
         I=find(y>=2^15);
         y(I)=y(I)-2^16;
    case 4 % miUINT16
         len = length(x)/2;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*2+1),x((k-1)*2+2)] * [1;256];
         end
    case 5 % miINT32
         len = length(x)/4;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*4+1),x((k-1)*4+2),x((k-1)*4+3),x((k-1)*4+4)] * [1;256;256^2;256^3];
         end
         I=find(y>=2^31);
         y(I)=y(I)-2^32;
   case 6 % miUINT32
         len = length(x)/4;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*4+1),x((k-1)*4+2),x((k-1)*4+3),x((k-1)*4+4)] * [1;256;256^2;256^3];
         end
    case 7 % miSINGLE
          len = length(x)/8;
         y=zeros(1,len);
         % 8 8 [7 1] [7 1]
         % mant = x((k-1)*8+1) + x((k-1)*8+2)*256 + mod(x((k-1)*8+3),128)*256^2;
         % scl  = floor( x((k-1)*8+4) / 128
         for k=1:len
            y(k) = 11111; %[x((k-1)*8+1),x((k-1)*8+2),x((k-1)*8+3),x((k-1)*8+4),x((k-1)*8+5),x((k-1)*8+6),x((k-1)*8+7),x((k-1)*8+8)] * [1;256;256^2;256^3;256^4;256^5;256^6;256^7];
         end
    case 9 % miDOUBLE
          len = length(x)/8;
         y=zeros(1,len);
         for k=1:len
            y(k) = 22222; %[x((k-1)*8+1),x((k-1)*8+2),x((k-1)*8+3),x((k-1)*8+4),x((k-1)*8+5),x((k-1)*8+6),x((k-1)*8+7),x((k-1)*8+8)] * [1;256;256^2;256^3;256^4;256^5;256^6;256^7];
         end
    case 12 %  miINT64  
          len = length(x)/8;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*8+1),x((k-1)*8+2),x((k-1)*8+3),x((k-1)*8+4),x((k-1)*8+5),x((k-1)*8+6),x((k-1)*8+7),x((k-1)*8+8)] * [1;256;256^2;256^3;256^4;256^5;256^6;256^7];
         end
         I=find(y>=2^63);
         y(I)=y(I)-2^64;
   case 13 % miUINT64
         len = length(x)/8;
         y=zeros(1,len);
         for k=1:len
            y(k) = [x((k-1)*8+1),x((k-1)*8+2),x((k-1)*8+3),x((k-1)*8+4),x((k-1)*8+5),x((k-1)*8+6),x((k-1)*8+7),x((k-1)*8+8)] * [1;256;256^2;256^3;256^4;256^5;256^6;256^7];
         end
    otherwise
        error('TMC unsupported data type')
end
*/

}


void matfgetsube(struct Cdatelmtype *datelmtype , char *buf,long ind)
{
//% read sub-element from mat-file miMatrix
//% returns data type, subelement size, data  index (padded)
	//union buf_long  *pl;
	//union buf_short *ps;
	union buf_long  l;
	union buf_short s;

	if ( buf[ind+2]!=0 ||  buf[ind +3]!=0)
	{
		datelmtype->bCompress=1;
		//ps = (union buf_short*)&buf[ind];
		//datelmtype->dtype = ps->x;
		s.b[0]=buf[ind];
		s.b[1]=buf[ind+1];
		datelmtype->dtype =  s.x;

		//ps = (union buf_short*)&buf[ind+2];
		//datelmtype->dsz = ps->x;
		s.b[0]=buf[ind+2];
		s.b[1]=buf[ind+3];
		datelmtype->dsz =  s.x;

		datelmtype->Idat[0]=ind+4;
		datelmtype->Idat[1]=ind+4+datelmtype->dsz-1;
	}
	else
	{
		datelmtype->bCompress=0;
		//pl = (union buf_long*)&buf[ind];
		//datelmtype->dtype = pl->x;
		l.b[0]=buf[ind];
		l.b[1]=buf[ind+1];
		l.b[2]=buf[ind+2];
		l.b[3]=buf[ind+3];
		datelmtype->dtype =  l.x;
		//pl = (union buf_long*)&buf[ind+4];
		//datelmtype->dsz = pl->x;
		l.b[0]=buf[ind+4];
		l.b[1]=buf[ind+5];
		l.b[2]=buf[ind+6];
		l.b[3]=buf[ind+7];
		datelmtype->dsz =  l.x;
		datelmtype->Idat[0]=ind+8;
		datelmtype->Idat[1]=ind+8+datelmtype->dsz-1;
	}
	datelmtype->Idat[1] = (long)ceil( (datelmtype->Idat[1]+1) / 8.0f) * 8 -1;
/*
if buf(ind1+2)~=0 || buf(ind1+3)~=0
    bCompess=1;
    dtype=buf(ind1+[0:1])*[1;256];
    dsz=buf(ind1+[2:3])*[1;256];
    Idat=[ind1+4,ind1+4+dsz-1];
else
    bCompess=0;
    dtype=buf(ind1+[0:3])*[1;256;256^2;256^3];
    dsz=buf(ind1+[4:7])*[1;256;256^2;256^3];
    Idat=[ind1+8,ind1+8+dsz-1];
end

Idat(2) = ceil(Idat(2)/8)*8;
*/
}
long _tmcreadmatrixelm(tmsMatrix *W,struct Cdatelmtype *datelmtype , char *buf)
{
struct Cdatelmtype dt1,dt2,dt3,dt4,dt5;
short   matcls,hasIm;
short k;
long len,m,n,cntn,cntm;
long DimsArr_len=0;
double *DimsArr=0;
long ArrName_len=0;
double *ArrName=0;

double *xRe=0;
long xRe_len=0;
double *xIm=0;
long xIm_len=0;

double *FnLen=0;
long FnLen_len=0;


double *Fnames=0;
long    Fnames_len=0;
long   cntfd;
long   NumFd; 

long ind2;

STRINGCODE *hcFields;

tmsMatrix *Mx=0;
tmsMatrix *X=0;

ind2=129;//stam

	matfgetsube(&dt1 ,  buf,datelmtype->Idat[0]);//ArrayFlags
	matfgetsube(&dt2 ,  buf,dt1.Idat[1]+1);//DimsArr
	matfgetsube(&dt3 ,  buf,dt2.Idat[1]+1);//ArrName
/*
[dtype1,dsz1,Idat1,bCompess]=matfgetsube(A,Idat(1));% ArrayFlags
ArrayFlags = A([Idat1(1):Idat1(2)]); % elmdata2double(A,dtype1,dsz1,Idat1,bCompess); %A([Idat1(1):Idat1(2)]);

[dtype2,dsz2,Idat2,bCompess]=matfgetsube(A,Idat1(2)+1);% DimsArr
DimsArr=elmdata2double(A,dtype2,dsz2,Idat2,bCompess);

[dtype3,dsz3,Idat3,bCompess]=matfgetsube(A,Idat2(2)+1);% ArrName
ArrName=char(elmdata2double(A,dtype3,dsz3,Idat3,bCompess)); %  (A([Idat3(1)+[0:dsz3-1]]));
*/

	elmdata2double(&DimsArr,&DimsArr_len,buf,&dt2);
	elmdata2double(&ArrName,&ArrName_len,buf,&dt3);

		len=1;m=0;n=0;
		for (k=0;k<DimsArr_len;k++)
		{
			len = len * (long)DimsArr[k];
		}
		if (DimsArr_len>0)
				m=(long)DimsArr[0];

		if (len >0 && m>0)
		{
			n = len / m;
		}

// matcls=ArrayFlags(1); % matrix class
   	matcls = (short)buf[dt1.Idat[0]];
//hasIm=mod(floor(ArrayFlags(2)/8),2);
	hasIm = ((buf[dt1.Idat[0]+1] >> 3) & 0x1);
	switch (matcls)
	{
	case mx_CELL_CLASS://    =1, 
		dt5.Idat[0]=dt3.Idat[0]; dt5.Idat[1]=dt3.Idat[1];

		X = tmcNewMatrix();
		if (n >0 && m>0)
		{
			_tmcCreateCellArray(X,m,n);
			// X=cell(m,n);
			for (cntn=0;cntn<n;cntn++)
				for (cntm=0;cntm<m;cntm++)
				{
					matfgetsube(&dt5 ,  buf,dt5.Idat[1]+1);//cell
					// Mx = [];
					 Mx = tmcNewMatrix();
					 _tmcreadmatrixelm(Mx,&dt5 , buf);
					 _tmcSetCell(X,cntm+m*cntn, Mx );
					// X{cntm,cntn}=Mx;
				}
		}
		else
		{
			// X=[];
		}
			if (ArrName_len>0)
			{
				// Append to WS structure
				_tmcSetByField(W,0,X,dstring2hcode(ArrName,ArrName_len));
				// M=setfield(M,ArrName,x);
			}
			else
			{
				// M=   x;
				tmcAssign(W,X);
			}
		tmcFreeRegister(X);
		ind2 = dt5.Idat[1]+1;
/*
        Idat5=Idat3;
        len = prod(DimsArr);
        
        m = DimsArr(1);
        if len >0 && m > 0
            n = len / m;
            X=cell(m,n);
            for cntn=1:n
                for cntm=1:m
                    [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat5(2)+1); % cell
                    Mx=[];
                    [Mx,indx]=tmcreadmatrixelm(Mx,A,dtype5,dsz5,bCompess,Idat5); 
                    X{cntm,cntn}=Mx;
                end
            end
        else
            X=[];
        end
        if ~isempty(ArrName)
            M=setfield(M,ArrName,X);
        else
            M=    X;
        end
        ind2=Idat5(2)+1;
*/

		break;
	case mx_STRUCT_CLASS://  =2, 

	    matfgetsube(&dt4 ,  buf,dt3.Idat[1]+1);//FnLen
	    matfgetsube(&dt5 ,  buf,dt4.Idat[1]+1);//Fnames

		elmdata2double(&FnLen,&FnLen_len,buf,&dt4);
		elmdata2double(&Fnames,&Fnames_len,buf,&dt5);

		NumFd= Fnames_len /  (long)FnLen[0];

		// X = struct;

		X = tmcNewMatrix();
		hcFields  = MYMALLOC(NumFd * sizeof(STRINGCODE));

		for (cntfd=0;cntfd < NumFd; cntfd++)
		{
			hcFields[cntfd]=dstring2hcode(&Fnames[cntfd*(long)FnLen[0]],_dstrlen(&Fnames[cntfd*(long)FnLen[0]],(long)FnLen[0]));
		}
		_tmcCreateStruct(X,m,n,(short)NumFd,hcFields);


		Mx = tmcNewMatrix();
		if (len >0 && m>0)
		{
			for (cntn=0;cntn<n;cntn++)
				for (cntm=0;cntm<m;cntm++)
					for (cntfd=0;cntfd < NumFd; cntfd++)
					{
						matfgetsube(&dt5 ,  buf,dt5.Idat[1]+1);//Fd
						// Mx = [];
						_tmcClearRegister(Mx);
						_tmcreadmatrixelm(Mx,&dt5 , buf);
						_tmcSetByField(X,cntm+m*cntn,Mx,hcFields[cntfd]);
						// II=(k-1)*FnLen+[1:FnLen-1];
						// X=setfield(X,{cntm,cntn},Fnames(II),Mx);
					}
		}
		tmcFreeRegister(Mx);
		MYFREE(hcFields);

		MYFREE(FnLen);
		if (NumFd>0) //bug:27.11.2012: only if the struct is not empty.
				MYFREE(Fnames); 
			if (ArrName_len>0)
			{
				// Append to WS structure
				_tmcSetByField(W,0,X,dstring2hcode(ArrName,ArrName_len));
				// M=setfield(M,ArrName,x);
			}
			else
			{
				// M=   x;
				tmcAssign(W,X);
			}
		tmcFreeRegister(X);
		ind2 = dt5.Idat[1]+1;



/*
        [dtype4,dsz4,Idat4,bCompess]=matfgetsube(A,Idat3(2)+1); % FnLen
        %FnLen=A([Idat4(1)+[0:dsz4-1]])*[1;256;256^2;256^3];
        FnLen= elmdata2double(A,dtype4,dsz4,Idat4,bCompess);
        [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat4(2)+1); % Fnames
        
        %Fnames=char(A([Idat5(1)+[0:dsz5-1]]));
        Fnames=char(  elmdata2double(A,dtype5,dsz5,Idat5,bCompess)  );
        NumFd=length(Fnames) /  FnLen;
        
                    len = prod(DimsArr);
                    m = DimsArr(1);
                    if len >0 && m > 0 
                        n = len / m;
                    end    
                    X=struct;%('xuxu',cell(m,n));
                    
                    for cntn=1:n
                        for cntm=1:m
                            %X0=struct;
                            for k=1:NumFd
                                II=(k-1)*FnLen+[1:FnLen-1];
                                
                                [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat5(2)+1); % Fd
                                Mx=[];
                                [Mx,indx]=tmcreadmatrixelm(Mx,A,dtype5,dsz5,bCompess,Idat5); 
                                %X{cntm,cntn}=Mx;
                                X=setfield(X,{cntm,cntn},Fnames(II),Mx);
                            end
                            %X(cntm,cntn)=X0;
                        end
                    end
        
            
            
        if ~isempty(ArrName)
            M=setfield(M,ArrName,X);
        else
            M=    X;
        end
        ind2=Idat5(2)+1;
*/



		break;
	case mx_OBJECT_CLASS://  =3, 
	case mx_SPARSE_CLASS://  =5, 
	    // unsupported
		break;

	case mx_CHAR_CLASS://    =4, 
	case mx_DOUBLE_CLASS://  =6, 
	case mx_SINGLE_CLASS://  =7, 
	case mx_INT8_CLASS://    =8, 
	case mx_UINT8_CLASS://  = 9, 
	case mx_INT16_CLASS://  =10, 
	case mx_UINT16_CLASS:// =11, 
	case mx_INT32_CLASS://  =12, 
	case mx_UINT32_CLASS:// =13 

			X = tmcNewMatrix();
			if (matcls == mx_CHAR_CLASS)
					X->m_desc.m_type = TYPE_STRING;
				else
					X->m_desc.m_type = TYPE_MATRIX;
			X->m_desc.m_nRows=m;
			X->m_desc.m_nCols=n;

			matfgetsube(&dt4 ,  buf,dt3.Idat[1]+1);//re
			elmdata2double(&xRe,&xRe_len,buf,&dt4);
			X->value.complx.rData = xRe;
			// x=xRe
			if (hasIm)
			{
				matfgetsube(&dt5 ,  buf,dt4.Idat[1]+1);//re
				elmdata2double(&xIm,&xIm_len,buf,&dt5);
				//x=x+j*xIm;
				X->value.complx.iData = xIm;
				X->m_desc.m_modifier |=MODIFIER_MASK_HAS_IM;
			}
			else
			{
				dt5.Idat[0]=dt4.Idat[0]; dt5.Idat[1]=dt4.Idat[1];
			}
			if (ArrName_len>0)
			{
				// Append to WS structure
				_tmcSetByField(W,0,X,dstring2hcode(ArrName,ArrName_len));
				// M=setfield(M,ArrName,x);
			}
			else
			{
				// M=   x;
				tmcAssign(W,X);
			}
			tmcFreeRegister(X);
			ind2 = dt5.Idat[1]+1;
			// HAZARD: MYFREE memory or assign to matrix
/*
        [dtype4,dsz4,Idat4,bCompess]=matfgetsube(A,Idat3(2)+1);% Re
        xRe=elmdata2double(A,dtype4,dsz4,Idat4,bCompess);
        %xRe=A([Idat4(1)+[0:dsz4-1]]);
        x=xRe;
        if hasIm 
            [dtype5,dsz5,Idat5,bCompess]=matfgetsube(A,Idat4(2)+1);% Im
            %xIm=A([Idat5(1)+[0:dsz5-1]]);
            xIm=elmdata2double(A,dtype5,dsz5,Idat5,bCompess);
            x=x+j*xIm;
        else
             Idat5=Idat4;
        end
        if ~isempty(ArrName)
            M=setfield(M,ArrName,x);
        else
            M=    x;
        end
        ind2=Idat5(2)+1;
*/

		break;
	default:
		// unsupported
		;


	}

	if (DimsArr_len>0)
		MYFREE(DimsArr);
	if (ArrName_len>0)
		MYFREE(ArrName);

return ind2;
}

long _tmcreaddataelm(tmsMatrix *W,char *buf,long ind)
{
struct Cdatelmtype datelmtype;

	matfgetsube(&datelmtype,buf,ind);
	if (datelmtype.dtype == mi_MATRIX)
	{
		return _tmcreadmatrixelm( W,&datelmtype , buf);
	}
	else
	{
//		return datelmtype.Idat[2]+1; // only skip it TMC_HAZARD: BUG BUG BUG
		 		return datelmtype.Idat[1]+1; // only skip it TMC_HAZARD: BUG BUG BUG
	}
	//	% recognize data type
	//[dtype,dsz,Idat,bCompess]=matfgetsube(buf,ind);
	//if dtype ~= 14
	//    [M,ind2]=tmcreadnumelm(M,buf,dtype,dsz,bCompess,Idat); %read  numeric element
	//else
	//    [M,ind2]=tmcreadmatrixelm(M,buf,dtype,dsz,bCompess,Idat); %read  matrix element
	//end


}


//////////////
void _tmcreadmatv4(tmsMatrix *W,const char *buf,long flen)
{
// read -V4 matfile
tmsMatrix *X;
long k;
long ind;
short l;
char M;
char T;
char P;
long len;
	union buf_double d;
const char *pArrName;

//	long type;   // type : MOPT,T=0-num,1-text,2-sparse
// O=zero, P=format: 0-double,1-single,2-long,3-short,4-unsigned short,5-char
//	long mrows;  // row dimension 
//	long ncols;  // column dimension 
//	long imagf;  // flag indicating imag part 
//	long namlen; // name length (including NULL) 

	union
	{
	   struct Fmatrix x ;
	   char b[10];
	} mhdr;
ind=0;
	while (ind < flen)
	{
		for (l=0;l<sizeof(struct Fmatrix);l++)
			mhdr.b[l]=buf[ind+l];//HAZARD: mingw64 reports error here

			M = buf[ind+3];//M
						   //O
		    P = buf[ind+1];//P
			T = buf[ind+0];//T

			X = tmcNewMatrix();

			if (M != 0)
					// unsupported
					_tmcRaiseException(file_not_found,s_module,"tmcloadV4","only IEEE Little Endian supported",0,NULL);

			if (T == 1)
					X->m_desc.m_type = TYPE_STRING;
				else if (T == 0)
					X->m_desc.m_type = TYPE_MATRIX;
				else
					// unsupported
					_tmcRaiseException(file_not_found,s_module,"tmcloadV4","sparse not supported",0,NULL);

			if (P != 0)
					// unsupported
					_tmcRaiseException(file_not_found,s_module,"tmcloadV4","only double is supported",0,NULL);


			X->m_desc.m_nRows=mhdr.x.mrows;
			X->m_desc.m_nCols=mhdr.x.ncols;


			ind = ind + sizeof(struct Fmatrix);

			pArrName = &buf[ind];
			ind = ind + mhdr.x.namlen;


		len = mhdr.x.mrows * mhdr.x.ncols;
		if (len>0)
			X->value.complx.rData = (double*)MYMALLOC(len*sizeof(double));

		for (k=0;k<len;k++)
		{

				d.b[0]= buf[ind+k*8];
				d.b[1]= buf[ind+k*8+1];
				d.b[2]= buf[ind+k*8+2];
				d.b[3]= buf[ind+k*8+3];

				d.b[4]= buf[ind+k*8+4];
				d.b[5]= buf[ind+k*8+5];
				d.b[6]= buf[ind+k*8+6];
				d.b[7]= buf[ind+k*8+7];

				X->value.complx.rData[k]= (double)d.x;
		}
		ind  = ind + len*8;


		if (mhdr.x.imagf)
		{
				X->value.complx.iData = (double*)MYMALLOC(len*sizeof(double));
				X->m_desc.m_modifier |=MODIFIER_MASK_HAS_IM;

			for (k=0;k<len;k++)
			{

					d.b[0]= buf[ind+k*8];
					d.b[1]= buf[ind+k*8+1];
					d.b[2]= buf[ind+k*8+2];
					d.b[3]= buf[ind+k*8+3];

					d.b[4]= buf[ind+k*8+4];
					d.b[5]= buf[ind+k*8+5];
					d.b[6]= buf[ind+k*8+6];
					d.b[7]= buf[ind+k*8+7];

					X->value.complx.iData[k]= (double)d.x;
			}
			ind  = ind + len*8;
		}


		// Append to WS structure
		_tmcSetByField(W,0,X,string2hcode(pArrName));
		// M=setfield(M,ArrName,x);

		tmcFreeRegister(X);

	}
}

long my_filelength(int fh)
{
	long length;
	length = lseek(fh, 0, SEEK_END)+1;
	lseek(fh, 0, SEEK_SET);
	return length;
	/*
	#include <sys/stat.h>
struct stat st;
stat(filename, &st);
size = st.st_size;
*/

}

void tmcload(long nout,long ninput,tmsMatrix *W,tmsMatrix *fn,...)
// implements W=load(fn)
// reserved: filter loaded vars list 
{
	char *sBuf;
	char *A;
	int fh;
	long flen;
	int readbytes;
	long ind0;

	_tmcClearRegister(W);
	_tmcCreateStruct(W,1,1,0,NULL);


	sBuf=_tmcMat2String(fn);
	fh = _open(sBuf,_O_RDONLY | _O_BINARY);
	MYFREE(sBuf);
	if (fh<0)
	{
			_tmcRaiseException(file_not_found,s_module,"tmcload","File not found.",1,fn);
	}
	flen = filelength( fh );
	A = (char *)MYMALLOC( sizeof(char)*flen);
	readbytes = _read( fh, A, flen ) ;
	if (readbytes != flen)
	{
			_tmcRaiseException(file_not_found,s_module,"tmcload","can't read file.",1,fn);
	}
	_close(fh);
	if (A[0]==0 || A[1]==0 || A[2]==0 || A[3]==0)
	{
		_tmcreadmatv4(W,A,flen);
		return;
		//	_tmcRaiseException(file_not_found,s_module,"tmcload","ver 4 file not supported yet.",1,fn);
		
	}
	ind0 = 128; // skip the header
	while (ind0 < flen)
	{
		ind0 = _tmcreaddataelm(W,A,ind0);
	}

//while ind2<length(A)
//    [M,ind2]=tmcreaddataelm(M,A,ind0);
//    ind0=ind2;
//end
	MYFREE(A);
}


////////////////////////////////////////////////////////////////
int tmcwritesavemimatrix(int fh,tmsMatrix *MatN,const char *varnameN,long *posI);

int _tmcwritematheader(int fh)
{
char whdr[128];

	memset(whdr,' ',128);
	sprintf(whdr,"MATLAB 5.0 MAT-file, Platform: PCWIN, Created on: Tue Oct 11 16:48:36 2011");
	
	whdr[124]=0x0; //version: 0x1000
	whdr[125]=0x1;
	whdr[126]='I';
	whdr[127]='M';

	_write(fh,whdr,128);
	return 0;
}


int _tmcwritesavetag(int fh,long datatype,long numofbytes,long *posI)
{
	short m;

	if (numofbytes>=1 && numofbytes<=4)
	{
		// If the data element contains between one and four bytes of data, the compressed data type is uses.
		//	In this format, the Data Type and Number of Bytes fields are stored as 16-bit
		//values, freeing four bytes in the tag in which to store the data.
		m = (short)datatype;
		_write(fh,&m,2);
		m = (short)numofbytes;
		_write(fh,&numofbytes,2);
		posI[0]+=4;
	}
	else
	{
	_write(fh,&datatype,4);
	_write(fh,&numofbytes,4);
	posI[0] +=8;
	}
return 0;
}

const char zerobuf[8]={0,0,0,0,0,0,0,0};
int _tmcwritesavebufpadding(int fh,const char* databuf,long numofbytes,long *posI)
{

	if (numofbytes>0)
	{
		_write(fh,databuf,numofbytes);
		posI[0] += numofbytes;

		if (posI[0] % 8)
		{
			_write(fh,zerobuf,8-(posI[0] % 8));
			posI[0] += 8-(posI[0] % 8);
		}
	}
return 0;
}
int _tmcwritesavebufpaddinguni(int fh,const void* databuf,long numofbytes,long *posI)
{

	if (numofbytes>0)
	{
		_write(fh,databuf,numofbytes);
		posI[0] += numofbytes;

		if (posI[0] % 8)
		{
			_write(fh,zerobuf,8-(posI[0] % 8));
			posI[0] += 8-(posI[0] % 8);
		}
	}
return 0;
}

long stam;
const char _tmcsaveEmptyName[1]={0};
unsigned short * _tmcMat2StringW(tmsMatrix *src);
int _tmcwritedataelm(int fh,tmsMatrix *MatN,const char *varnameN,long *posI)
{
union buf_long l;
int len;
long MN,k;

//#ifdef _TMC_ANDROID_ // HAZARD_TODO: no unicode support so far
unsigned short * temp_string ;
//#else
//wchar_t* temp_string;
//#endif

int nfields;
char temp_fnbuf[32];
const char *fn;

	switch (MatN->m_desc.m_type)
	{
	case TYPE_MATRIX:
	case TYPE_STRING:
	case TYPE_NOTHING:
		// Print subelements:
		// Array Flags
		_tmcwritesavetag(fh,mi_UINT32,2*sizeof(unsigned long),posI);//2*sizeof(unsigned long)
		memset(&l,0,sizeof(l));
		if (MatN->m_desc.m_type == TYPE_MATRIX ||  MatN->m_desc.m_type == TYPE_NOTHING)
		{
			l.b[1]=0x08 * _tmcHasIm(MatN);//??
			l.b[0]=mx_DOUBLE_CLASS;
		}
		else
		{
			l.b[0]=mx_CHAR_CLASS;
		}
		_write(fh,&l.b[0], sizeof(unsigned long));
		memset(&l,0,sizeof(l));
		_write(fh,&l.b[0], sizeof(unsigned long));
		posI[0] += 2*sizeof(unsigned long);
		// dimentions array
		_tmcwritesavetag(fh,mi_INT32,2*sizeof(long),posI);//num_of_dims*sizeof(long)
		l.x = _tmcGetM(MatN);
		_write(fh,&l.b[0],sizeof(long));
		l.x = _tmcGetN(MatN);
		_write(fh,&l.b[0],sizeof(long));
		posI[0] +=2*sizeof(long);
		// array name
		len = (long)strlen(varnameN);//x64
		_tmcwritesavetag(fh,mi_INT8,len,posI);
		_tmcwritesavebufpadding(fh,varnameN,len,posI);

		if (MatN->m_desc.m_type == TYPE_MATRIX ||  MatN->m_desc.m_type == TYPE_NOTHING)
		{
			// real part
			_tmcwritesavetag(fh,mi_DOUBLE,sizeof(double)*tmcNumElem(MatN),posI);
			//stam=_tell(fh);
			stam=_write(fh,&MatN->value.complx.rData[0],sizeof(double)*tmcNumElem(MatN));
			//stam=_tell(fh);
			posI[0] += sizeof(double)*tmcNumElem(MatN);
			if (_tmcHasIm(MatN))
			{
				_tmcwritesavetag(fh,mi_DOUBLE,sizeof(double)*tmcNumElem(MatN),posI);
				_write(fh,(char*)MatN->value.complx.iData,sizeof(double)*tmcNumElem(MatN));
				posI[0] += sizeof(double)*tmcNumElem(MatN);
			}
		}
		else // string
		{
			_tmcwritesavetag(fh,mi_UINT16,2*tmcNumElem(MatN),posI);
			//#ifdef _TMC_ANDROID_
				temp_string = _tmcMat2StringW(MatN);
				_tmcwritesavebufpaddinguni(fh, (void*)temp_string, 2 * tmcNumElem(MatN), posI);
			//#else
			//	temp_string = _tmcMat2UniString(MatN);
			//	_tmcwritesavebufpaddinguni(fh, (void*)temp_string, sizeof(wchar_t)*tmcNumElem(MatN), posI);
			//#endif
			MYFREE(temp_string);
		}
		break;
	case TYPE_CELL_ARRAY:
		// Print subelements:
		// Array Flags
		_tmcwritesavetag(fh,mi_UINT32,2*sizeof(unsigned long),posI);//2*sizeof(unsigned long)
		memset(&l,0,sizeof(l));
		l.b[1]=0x00;//no flags
		l.b[0]=mx_CELL_CLASS;
		_write(fh,&l.b[0], sizeof(unsigned long));
		memset(&l,0,sizeof(l));
		_write(fh,&l.b[0], sizeof(unsigned long));
		posI[0] += 2*sizeof(unsigned long);
		// dimentions array
		_tmcwritesavetag(fh,mi_INT32,2*sizeof(long),posI);//num_of_dims*sizeof(long)
		l.x = _tmcGetM(MatN);
		_write(fh,&l.b[0],sizeof(long));
		l.x = _tmcGetN(MatN);
		_write(fh,&l.b[0],sizeof(long));
		posI[0] +=2*sizeof(long);
		// array name
		len = (long)strlen(varnameN);//x64
		_tmcwritesavetag(fh,mi_INT8,len,posI);
		_tmcwritesavebufpadding(fh,varnameN,len,posI);
		// Cells
		MN = tmcNumElem(MatN);
		for (k=0; k<MN; k++)
		{
			tmcwritesavemimatrix(fh,MatN->value.m_cells[k],_tmcsaveEmptyName,posI);
		}
		break;
	case TYPE_STRUCT:
		// Print subelements:
		// Array Flags
		_tmcwritesavetag(fh,mi_UINT32,2*sizeof(unsigned long),posI);//2*sizeof(unsigned long)
		memset(&l,0,sizeof(l));
		l.b[1]=0x00;//no flags
		l.b[0]=mx_STRUCT_CLASS;
		_write(fh,&l.b[0], sizeof(unsigned long));
		memset(&l,0,sizeof(l));
		_write(fh,&l.b[0], sizeof(unsigned long));
		posI[0] += 2*sizeof(unsigned long);
		// dimentions array
		_tmcwritesavetag(fh,mi_INT32,2*sizeof(long),posI);//num_of_dims*sizeof(long)
		l.x = _tmcGetM(MatN);
		_write(fh,&l.b[0],sizeof(long));
		l.x = _tmcGetN(MatN);
		_write(fh,&l.b[0],sizeof(long));
		posI[0] +=2*sizeof(long);
		// array name
		len = (long)strlen(varnameN);//x64
		_tmcwritesavetag(fh,mi_INT8,len,posI);
		_tmcwritesavebufpadding(fh,varnameN,len,posI);
		// Field name length
		_tmcwritesavetag(fh,mi_INT32,4,posI);
		memset(&l,0,sizeof(l));
		l.b[0] = 32;
		_write(fh,&l.b[0], sizeof(unsigned long));
		posI[0] += sizeof(long);

		// Field names
		nfields = _tmcGetNf(MatN);
		_tmcwritesavetag(fh,mi_INT8,nfields*32,posI);
		for (k=0;k<nfields;k++)
		{
			memset(temp_fnbuf,0,32);
			fn = hcode2string(MatN->value.StructDef.hcFields[k]);
			len = (long)strlen(fn);//x64
			if (len>31)
				len=31;
			strncpy(temp_fnbuf,fn,len);
			_write(fh,&temp_fnbuf[0],32);
			posI[0] +=32;
		}
		MN = tmcNumElem(MatN);
		for (k=0; k<MN*nfields; k++)
		{
			tmcwritesavemimatrix(fh,MatN->value.StructDef.m_fields[k],_tmcsaveEmptyName,posI);
		}
		break;

	}
return 0;	


}
int tmcwritesavemimatrix(int fh,tmsMatrix *MatN,const char *varnameN,long *posI)
{
	long posI0,klum;
	long spos;
	long deltaI;
		posI0=posI[0];// start of a matrix
		_tmcwritesavetag(fh,mi_MATRIX,0,posI);// place holder
	    _tmcwritedataelm(fh,MatN,varnameN,posI);
		deltaI = posI[0]-posI0;
		spos=_lseek(fh,-deltaI,SEEK_CUR);
		klum=0;
		_tmcwritesavetag(fh,mi_MATRIX,deltaI-8,&klum);
		spos=_lseek(fh,deltaI-klum,SEEK_CUR);

return 0;
}

#ifdef _TMC_ANDROID_
/* HAZARD #define MAX_PATHx 4096  
int my_wopen(const wchar_t* filename, int oflag,int pmode)  
{  
    char fn[MAX_PATHx];  
    wcstombs(fn, filename, MAX_PATHx);  
    return open(fn, oflag,pmode);  
}  
*/
#endif

void tmcsave(long nout,long ninput,tmsMatrix *filename,tmsMatrix *Mat1,char *varname1,...)
{ // ninput is number of saved matrices plus one
	int fh;
	//wchar_t *sBuf;
	va_list marker;
	tmsMatrix *MatN;
	char *varnameN;
	int n;
	long posI0;

#ifdef _TMC_ANDROID_ // HAZARD_TODO: no unicode support so far
	char * sBuf=_tmcMat2String(filename);
	fh = open(sBuf,_O_RDWR  | _O_CREAT | _O_TRUNC | _O_BINARY, _S_IREAD | _S_IWRITE );
#else
	wchar_t * sBuf=_tmcMat2UniString(filename);
	fh = _wopen(sBuf,_O_RDWR  | _O_CREAT | _O_TRUNC | _O_BINARY, _S_IREAD | _S_IWRITE );
#endif

	MYFREE(sBuf);

	_tmcwritematheader(fh);
    MatN = Mat1;
	varnameN=varname1;
	n=1;
	va_start( marker, varname1 );     // Initialize variable arguments. 
	while (n<ninput)
	{
		posI0 = 0;
		tmcwritesavemimatrix(fh,MatN,varnameN,&posI0);
		/*
		posI0=0;// start of a matrix
		_tmcwritesavetag(fh,mi_MATRIX,0,&posI0);// place holder
	    _tmcwritedataelm(fh,MatN,varnameN,&posI0);
		spos=_lseek(fh,-(long)posI0,SEEK_CUR);
		klum=0;
		_tmcwritesavetag(fh,mi_MATRIX,posI0-8,&klum);
		spos=_lseek(fh,posI0-klum,SEEK_CUR);
		*/

		MatN = va_arg( marker,  tmsMatrix * );
		varnameN = va_arg( marker,  char * );
		n++;
	}
	va_end( marker );              // Reset variable arguments.      

	_close(fh);
}

////////////////////////////////////////////////////////////////
void _tmcGetSubDimMatD2(tmsMatrix *pMat,long offs,const tmsMatrix *x)
{
				pMat->m_desc.m_dims=NULL;
				pMat->m_desc.m_modifier=x->m_desc.m_modifier;
				_tmcSetExtraDim(pMat,0);
				pMat->m_desc.m_type=x->m_desc.m_type;
				pMat->m_desc.m_nRows=_tmcGetDim(x,1);
				pMat->m_desc.m_nCols=_tmcGetDim(x,2);
				if (pMat->m_desc.m_type==TYPE_CELL_ARRAY)
				{
					pMat->value.m_cells = &(x->value.m_cells[offs*_tmcGetDim(x,1)*_tmcGetDim(x,2)]);
				}
				else
				{
					pMat->value.complx.rData = &(x->value.complx.rData[offs*_tmcGetDim(x,1)*_tmcGetDim(x,2)]);
					if (_tmcHasIm(x))
					{
						pMat->value.complx.iData = &(x->value.complx.iData[offs*_tmcGetDim(x,1)*_tmcGetDim(x,2)]);
					}
				}
}

void tmcDisplayMat(tmsMatrix *x,short bVerb)
{
	long m,n;
	short k;
	long d[MAX_MATRIX_DIM];
	tmsMatrix pMat;


	long M = _tmcGetM(x);
	long N = _tmcGetN(x);
	short ndims = _tmcGetNdim(x);

	if (ndims ==2)
	{
		if (x->m_desc.m_type == TYPE_CELL_ARRAY)
		{
			printf("CellArray(%d,%d) ={\n",M,N);
			for (m=0;m<M;m++)
			{
				for (n=0;n<N;n++)
				{
					printf("[%d,%d]=",m+1,n+1);
					tmcDisplayMat(x->value.m_cells[m+n*M],bVerb);
					printf(";\n");
				}
			}
			printf("};\n");
		return ;
		}

		if (x->m_desc.m_type == TYPE_STRUCT)
		{
			printf("Structure(%d,%d) =\n",M,N);
			for (m=0;m<M;m++)
			{
				for (n=0;n<N;n++)
				{
					printf("[%d,%d]=",m+1,n+1);
					for (k=0;k<_tmcGetNf(x);k++)
					{
						printf("\t field %s=\n",hcode2string(x->value.StructDef.hcFields[k]));
						tmcDisplayMat(x->value.StructDef.m_fields[(m+n*M)+k*M*N],bVerb);
						printf(";\n");
					}
				}
			}
			printf("END Structure;\n");
			return;
		}
		if ( bVerb || x->m_desc.m_type != TYPE_STRING)
			printf("Matrix(%d,%d) =[\n",M,N);
		if (x->m_desc.m_type == TYPE_STRING)
		{
				for (m=0;m<M;m++)
				{
					for (n=0;n<N;n++)
					{
					printf("%c",(char)x->m_rData[m*N+n]);
					}
				printf("\n");
				}
		}
		else
		for (m=0;m<M;m++)
		{
			for (n=0;n<N;n++)
			{
				if (_tmcHasIm(x)==0)
				{
				printf("%g,\t",x->m_rData[n*M+m]);
				}
				else
				{
				if(x->m_iData[n*M+m])
				printf("%g + \t%gi,\t",x->m_rData[n*M+m],x->m_iData[n*M+m]);
				else
					printf("%g\t   ,\t",x->m_rData[n*M+m]);
				}

			}
			printf(";\n");
		}
		if ( bVerb || x->m_desc.m_type != TYPE_STRING)
		printf("];\n");
		else
		printf("\n");
	}
	else
	{
		if (x->m_desc.m_type == TYPE_STRUCT)
		{
				// not supported
				printf("\nmatrix MD not supported\n");
				return;
		}
		if (ndims==3)
		{
			for (d[2]=0; d[2]< _tmcGetDim(x,3);d[2]++)
			{
				printf("MD[%d,%d,%d](:,:,%d) =\n",_tmcGetDim(x,1),_tmcGetDim(x,2),
					_tmcGetDim(x,3),d[2]+1);
				_tmcGetSubDimMatD2(&pMat,d[2],x);
				tmcDisplayMat(&pMat,bVerb);
				printf(";\n");
			}

		}
		else if(ndims==4)
		{
			for (d[3]=0; d[3]< _tmcGetDim(x,4);d[3]++)
			{
					for (d[2]=0; d[2]< _tmcGetDim(x,3);d[2]++)
					{
						printf("MD[%d,%d,%d,%d](:,:,%d,%d) =\n",_tmcGetDim(x,1),_tmcGetDim(x,2),
							_tmcGetDim(x,3),_tmcGetDim(x,4),
							d[2]+1,d[3]+1);
						_tmcGetSubDimMatD2(&pMat,d[2]+d[3]*_tmcGetDim(x,3),x);
						tmcDisplayMat(&pMat,bVerb);
						printf(";\n");
					}
			}
		}
	}

}
void tmcdisp(long nout,long ninput,tmsMatrix *ydummy,tmsMatrix *x)
{
// this function is implemented with one output to avoid TMC compilation warnings.
	if (nout>0)
	_tmcCreateMatrix(ydummy,1,1,0);
	tmcDisplayMat(x,0);
}
////////////////////////////////
void tmcDisplayMatF(FILE *fp,tmsMatrix *x,short bVerb)
{// function for debugging.
	long m,n;
	short k;
	long d[MAX_MATRIX_DIM];
	tmsMatrix pMat;


	long M = _tmcGetM(x);
	long N = _tmcGetN(x);
	short ndims = _tmcGetNdim(x);

	if (ndims ==2)
	{
		if (x->m_desc.m_type == TYPE_CELL_ARRAY)
		{
			fprintf(fp,"CellArray(%d,%d) ={\n",M,N);
			for (m=0;m<M;m++)
			{
				for (n=0;n<N;n++)
				{
					fprintf(fp,"[%d,%d]=",m+1,n+1);
					tmcDisplayMatF(fp,x->value.m_cells[m+n*M],bVerb);
					fprintf(fp,";\n");
				}
			}
			fprintf(fp,"};\n");
		return ;
		}

		if (x->m_desc.m_type == TYPE_STRUCT)
		{
			fprintf(fp,"Structure(%d,%d) =\n",M,N);
			for (m=0;m<M;m++)
			{
				for (n=0;n<N;n++)
				{
					fprintf(fp,"[%d,%d]=",m+1,n+1);
					for (k=0;k<_tmcGetNf(x);k++)
					{
						fprintf(fp,"\t field %s=\n",hcode2string(x->value.StructDef.hcFields[k]));
						tmcDisplayMatF(fp,x->value.StructDef.m_fields[(m+n*M)+k*M*N],bVerb);
						fprintf(fp,";\n");
					}
				}
			}
			fprintf(fp,"END Structure;\n");
			return;
		}
		if ( bVerb || x->m_desc.m_type != TYPE_STRING)
			fprintf(fp,"Matrix(%d,%d) =[\n",M,N);
		if (x->m_desc.m_type == TYPE_STRING)
		{
				for (m=0;m<M;m++)
				{
					for (n=0;n<N;n++)
					{
					fprintf(fp,"%c",(char)x->m_rData[m*N+n]);
					}
				fprintf(fp,"\n");
				}
		}
		else
		for (m=0;m<M;m++)
		{
			for (n=0;n<N;n++)
			{
				if (_tmcHasIm(x)==0)
				{
				fprintf(fp,"%g,\t",x->m_rData[n*M+m]);
				}
				else
				{
				if(x->m_iData[n*M+m])
				fprintf(fp,"%g + \t%gi,\t",x->m_rData[n*M+m],x->m_iData[n*M+m]);
				else
					fprintf(fp,"%g\t   ,\t",x->m_rData[n*M+m]);
				}

			}
			fprintf(fp,";\n");
		}
		if ( bVerb || x->m_desc.m_type != TYPE_STRING)
		fprintf(fp,"];\n");
		else
		fprintf(fp,"\n");
	}
	else
	{
		if (x->m_desc.m_type == TYPE_STRUCT)
		{
				// not supported
				fprintf(fp,"\nmatrix MD not supported\n");
				return;
		}
		if (ndims==3)
		{
			for (d[2]=0; d[2]< _tmcGetDim(x,3);d[2]++)
			{
				fprintf(fp,"MD[%d,%d,%d](:,:,%d) =\n",_tmcGetDim(x,1),_tmcGetDim(x,2),
					_tmcGetDim(x,3),d[2]+1);
				_tmcGetSubDimMatD2(&pMat,d[2],x);
				tmcDisplayMatF(fp,&pMat,bVerb);
				fprintf(fp,";\n");
			}

		}
		else if(ndims==4)
		{
			for (d[3]=0; d[3]< _tmcGetDim(x,4);d[3]++)
			{
					for (d[2]=0; d[2]< _tmcGetDim(x,3);d[2]++)
					{
						fprintf(fp,"MD[%d,%d,%d,%d](:,:,%d,%d) =\n",_tmcGetDim(x,1),_tmcGetDim(x,2),
							_tmcGetDim(x,3),_tmcGetDim(x,4),
							d[2]+1,d[3]+1);
						_tmcGetSubDimMatD2(&pMat,d[2]+d[3]*_tmcGetDim(x,3),x);
						tmcDisplayMatF(fp,&pMat,bVerb);
						fprintf(fp,";\n");
					}
			}
		}
	}

}
///////////////////////////////////////////////////////////////////////////
void tmcfopen(long nout,long ninput,tmsMatrix *h,tmsMatrix *fname,tmsMatrix *perm)
/*
FID = FOPEN(FILENAME,PERMISSION) opens the file FILENAME in the
    mode specified by PERMISSION.  PERMISSION can be:
    
        'r'     read
        'w'     write (create if necessary)
        'a'     append (create if necessary)
        'r+'    read and write (do not create)
        'w+'    truncate or create for read and write
        'a+'    read and append (create if necessary)
        'W'     write without automatic flushing
        'A'     append without automatic flushing
*/
{
	char *sBuf;
	char sPerm[3]={0,0,0};
	FILE *fp;

	sBuf=_tmcMat2String(fname);
	sPerm[0]=(char)perm->value.complx.rData[0];
	if (tmcNumElem(perm)>1)
		sPerm[1]=(char)perm->value.complx.rData[0];
	fp = fopen(sBuf,sPerm);
	_tmcCreateMatrix(h,1,1,tmcREAL);
	h->value.complx.rData[0]=(double)(unsigned long)fp;
	MYFREE(sBuf);
}
void tmcfclose(long nout,long ninput,tmsMatrix *ydummy,tmsMatrix *h)
{
int stat;
FILE* fp = (FILE*)(unsigned long)h->value.complx.rData[0];

// this function is implemented with one output to avoid TMC compilation warnings.
	if (nout>0)
	_tmcCreateMatrix(ydummy,1,1,0);

if (fp)
	 stat= feof(fp);
else
	_tmcRaiseException(file_not_found,s_module,"fclose","invalid file handle.",1,h);

	fclose(fp);
}
void tmcfeof(long nout,long ninput,tmsMatrix *mIsEof,tmsMatrix *h)
{
int stat;
FILE* fp = (FILE*)(unsigned long)h->value.complx.rData[0];

if (fp)
	 stat= feof(fp);
else
	_tmcRaiseException(file_not_found,s_module,"feof","invalid file handle.",1,h);


	_tmcCreateMatrix(mIsEof,1,1,tmcREAL);
	mIsEof->value.complx.rData[0]=(double)stat;

}


void tmcfprintf(long nout,long ninput, tmsMatrix *fm,...)
/*
FPRINTF behaves like ANSI C with certain exceptions and extensions. 
    These include:
    1. Only the real part of each parameter is processed.
    2. ANSI C requires an integer cast of a double argument to correctly
       use an integer conversion specifier like d. A similiar conversion
       is required when using such a specifier with non-integral MATLAB
       values. Use FIX, FLOOR, CEIL or ROUND on a double argument to
       explicitly convert non-integral MATLAB values to integral values
       if you plan to use an integer conversion specifier like d.
       Otherwise, any non-integral MATLAB values will be outputted using
       the format where the integer conversion specifier letter has been
       replaced by e.
    3. The following non-standard subtype specifiers are supported for
       conversion characters o, u, x, and X.
       t    - The underlying C datatype is a float rather than an
              unsigned integer.
       b    - The underlying C datatype is a double rather than an
              unsigned integer.
       For example, to print out in hex a double value use a format like
       '%bx'.
    4. FPRINTF is "vectorized" for the case when A is nonscalar. The
       format string is recycled through the elements of A (columnwise)
       until all the elements are used up. It is then recycled in a similar
       manner through any additional matrix arguments.
*/
{
	char *sBuf,*sTempBuf;
	char *cPtr,*cPtrPrev;
	short ind;
	va_list marker;
	tmsMatrix *M;
	tmsMatrix *fmt;

    FILE *fp;

	va_start( marker, fm );     // Initialize variable arguments. 
	
	if (_tmcIsChar(fm))
	{
		fp = stdout;
	    sBuf=_tmcMat2StringESC(fm);
		ind=1;
	}
	else
	{
		fp =(FILE*)(unsigned long)fm->value.complx.rData[0];
		fmt = va_arg( marker,  tmsMatrix * );
	    sBuf=_tmcMat2StringESC(fmt);
		ind=2;
	}

	cPtr=sBuf;
	cPtrPrev = sBuf;
//		if (ninput==1)
//				fprintf(stdout,cPtrPrev);

		while (ind<ninput)
		{
			M = va_arg( marker,  tmsMatrix * );
			cPtrPrev=cPtr;
			cPtr=strchr(cPtr,'%');
			if (cPtr==NULL)
			{
				fprintf(fp,"%s",cPtrPrev);
				break;
			}
			else
			{
				*cPtr=0; // set terminator
				fprintf(fp,"%s",cPtrPrev);
				if (cPtr[1]=='s')
				{
					// printf as string
					sTempBuf=_tmcMat2StringESC(M);
					fprintf(fp,"%s",sTempBuf);
					MYFREE(sTempBuf);
				}
				else
				{
					if (cPtr[1]=='d' && _mdblIsInteger(M->m_rData[0]))
					fprintf(fp,"%I64d",(__int64)M->m_rData[0]);
					else
					// printf as double
					fprintf(fp,"%f",M->m_rData[0]);
				}
				cPtr+=2;
			}
			ind++;
		}
		va_end( marker );              // Reset variable arguments.      
		fprintf(fp,"%s",cPtr);//was: without format: HSKOST19.04.2015 for Android corrected 19.09.2015
//		fprintf(fp,"\n");
	MYFREE(sBuf);
}
void tmcsprintf(long nout,long ninput, tmsMatrix *sbuf,tmsMatrix *fm,...)
{
	char TempBuffer[MAX_PRINTF_LEN];// max len string
	char *sBuf,*sTempBuf;
	char *cPtr,*cPtrPrev;
	short ind,nc;
	va_list marker;
	tmsMatrix *M;
	char *out;
	long nStored;
long len;
long n;

	out=TempBuffer;
	sBuf=_tmcMat2StringESC(fm);
	cPtr=sBuf;
	cPtrPrev = sBuf;
		va_start( marker, fm );     // Initialize variable arguments. 
		ind=1;nc=0;
	if (ninput==1)
				nStored=sprintf(out,"%s",cPtrPrev);

		while (ind<ninput)
		{
			M = va_arg( marker,  tmsMatrix * );
			cPtrPrev=cPtr;
			cPtr=strchr(cPtr,'%');
			if (cPtr==NULL)
			{
				sprintf(out,"%s",cPtrPrev);
				break;
			}
			else
			{
				*cPtr=0; // set terminator
				nStored=sprintf(out,"%s",cPtrPrev);
				out += nStored;
				if (cPtr[1]=='s')
				{
					// printf as string
					sTempBuf=_tmcMat2StringESC(M);
					nStored=sprintf(out,"%s",sTempBuf);
					out += nStored;
					MYFREE(sTempBuf);
				}
				else
				{
					// printf as double
					if (cPtr[1]=='f')
						nStored=sprintf(out,"%f",M->m_rData[0]);
					else if (cPtr[1]=='d' && _mdblIsInteger(M->m_rData[0]))
						nStored=sprintf(out,"%I64d",(__int64)M->m_rData[0]);
					else
						nStored=sprintf(out,"%f",M->m_rData[0]);
					out += nStored;
				}
				cPtr+=2;// HAZARD - must analyse the actual format, may be more than 2 letters!!!
				nc+=2;
			}
			ind++;
		}
		va_end( marker );              // Reset variable arguments.      
	if (ninput>1 )// print the tail of the format
		nStored=sprintf(out,"%s",cPtr);
		out += nStored;
	MYFREE(sBuf);

	len = (long)strlen(TempBuffer); //x64 without NULL-termination.
	_tmcCreateMatrix(sbuf,1,len,tmcREAL);
	sbuf->m_desc.m_type = TYPE_STRING;
	for(n=0;n<len;n++)
		sbuf->m_rData[n]=TempBuffer[n];
}

void tmcfgetl(long nout,long ninput,tmsMatrix *str,tmsMatrix *h)
{
//returns the next line of a file associated with file
//    identifier FID as a MATLAB string. The line terminator is NOT
//    included. Use FGETS to get the next line with the line terminator
//    INCLUDED. If just an end-of-file is encountered then -1 is returned.
char buffer[MAX_FGETS_LEN]; // max  length !!!
FILE *fp;
size_t len;//x64

	fp =(FILE*)(unsigned long)h->value.complx.rData[0];
	if (	fgets(buffer,MAX_FGETS_LEN-2,fp) == NULL)
	{
		_tmcCreateMatrix(str,1,1,tmcREAL);
		str->value.complx.rData[0]=-1;
	}
	else
	{
		len = strlen(buffer);
		if (buffer[len-1]=='\n')
			buffer[len-1] = 0;
		_tmcSetString(str,buffer);
	}


}
