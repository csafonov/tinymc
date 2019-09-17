//! \file tmcpar_env.cpp
//! \brief Main() function for tmcco.exe

/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
////////////////////////////////////
#include <stdio.h>
#ifndef LINUX_GPL
#include <conio.h>
#else
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#endif

 


#include "tmcpar_env.h"
#include "tmc_sym_table.h"
#ifndef LINUX_GPL
#include <io.h>
//#undef HAVE_OPENDIR
#else
#define HAVE_OPENDIR
#endif


class CCompiler Compiler;
int error_level = 0;

//lexer utils
int tmcpar_colno=0;


std::list<std::string>  IncInputDirList; // analog of matlab path plus root file directory 
std::list<std::string>  IncInputFileList; // full list of files in all path 
std::list<std::string>  IncSrcDirList; // analog of matlab path plus root file directory (for tmcpar remains empty)
#ifdef BLD_RTL_FEATURE
// For Compiler.ask_print_src=1 option only:
std::list<std::string>  IncSrcFileList; // full list of files in all path 
#endif
/// environment utils
FILE *dump_file=NULL;// listing file
FILE *tmc_output=NULL; // output c-file
FILE *lsp_file=NULL;// lsp-file
FILE *tmc_in=NULL;// input file for tmcpar lexer


#ifdef BLD_RTL_FEATURE
//created in lexer: FILE *tmclsp_in; // current input file for lsp-parser
FILE *stdhead_file=NULL;
FILE *code_file=NULL;// code-file
FILE *tmc_src=NULL;// lsp-file
#endif

// Full name of file we are reading.
std::string curr_fcn_file_full_name;

char input_file_name[PATH_MAX + 2] = "";
char dump_file_name[PATH_MAX + 4] = "";
char output_dir_name[PATH_MAX + 4] = "";
char root_dir_name[PATH_MAX + 4] = "";
char libh_dir_name[PATH_MAX + 4] = "";
char ws_file_name[PATH_MAX + 4] = "";
char klum_file_name[PATH_MAX + 4] = "";

char symtable_file_name[PATH_MAX + 4] = "";//mynew
char buildin_fnc_file_name[PATH_MAX + 4]="";//mynew

char filelist_file_name[PATH_MAX + 4] = "";

char module_name[_MAX_PATH+2];
char module_path[_MAX_PATH+2];


#ifdef BLD_RTL_FEATURE
std::string c_file_name;

char stdhead_file_name[PATH_MAX + 4] = "";
char external_fnc_file_name[PATH_MAX + 4] = "";
char string_hash_file_name_in[PATH_MAX + 4] = "";
char string_hash_file_name_out[PATH_MAX + 4] = "";
char init_hash_data_file_name[PATH_MAX + 4] = "";
char globalhead_file_name[PATH_MAX + 4] = "";
char globalc_file_name[PATH_MAX + 4] = "";

char code_file_name[PATH_MAX + 4] = ""; // for assembler file
char string_hash_file_asm_name_out[PATH_MAX + 4] = "";// for assembler file
char globalc_asm_file_name[PATH_MAX + 4] = "";// for assembler file

char inputfilelist_file_name[PATH_MAX + 4] = "";
char srcfilelist_file_name[PATH_MAX + 4] = "";


#endif
/////////////////////////
void CCompiler::LogErr(int errcode, std::string msg,std::string symb, int line,bool fatal)
{
	nErrInFile++;
	nTotalErrors++;
	fprintf(stderr,"%s(%d) : error G%04d : '%s' : %s\n",_m_file_name.c_str(),line,errcode,symb.c_str(),msg.c_str()  );
	if (bUseDumpFile) fprintf(dump_file,
		           "%s(%d) : error G%04d : '%s' : %s\n",_m_file_name.c_str(),line,errcode,symb.c_str(),msg.c_str()  );
	if (fatal) throw(CCompilerExcpt());
};
void CCompiler::LogWarn(int errcode, std::string msg,std::string symb, int line)
{
	nWarnInFile++;
	nTotalWarnings++;
	fprintf(stderr,"%s(%d) : warning W%04d : '%s' : %s\n",_m_file_name.c_str(),line,errcode,symb.c_str(),msg.c_str()  );
	if (bUseDumpFile) fprintf(dump_file,
		           "%s(%d) : warning W%04d : '%s' : %s\n",_m_file_name.c_str(),line,errcode,symb.c_str(),msg.c_str()  );
};
void CCompiler::PrintSummary(void)
{
	fprintf(stderr,"=========== Finished generating code: %d succeeded, %d failed, %d processed, %d error(s), %d warning(s), times=%f,%f,%f,%f ===========\n",
		nProcessed-nFailed,nFailed,nProcessed,
		nTotalErrors,nTotalWarnings,
		perf_get_timediff(0,2),perf_get_timediff(0,1),perf_get_timediff(1,2),perf_get_timeaccum(0));
	if (bUseDumpFile) fprintf(dump_file,"========== Finished generating code: %d succeeded, %d failed, %d processed, %d error(s), %d warning(s), ==========\n",
		nProcessed-nFailed,nFailed,nProcessed,
		nTotalErrors,nTotalWarnings
		);
}

/////////////////////////
#define    NO_LOWLEVEL_ASM_EXAMPLE
#if  !defined(LINUX_GPL) && !defined(NO_LOWLEVEL_ASM_EXAMPLE)
//////////// DAO utilities //////////////////////////
unsigned long Rol32(unsigned long sn_,short lshifts);
unsigned long Ror32(unsigned long sn_,short rshifts);

struct tagcosty {  
long sn_0;
long sn_1;
long sn_2;
} costy;
const struct tagcosty mycosty[1]=
{
	0x6f6,0x00000000,0x00000000
};
struct tagcosty  ycosty[1];

unsigned long Ror32(unsigned long sn_,short rshifts)
{
	unsigned long res;
#ifdef GCC_BUILD

	asm ("	MOV CX, %2 ;\n\t"
		 "	MOV EAX,%1 ;\n\t"
		 "	ROR	EAX,CL;\n\t"
		 "	MOV	%0,EAX;\n\t"
			:"=r" (res)
			:"r" (sn_),"r" (rshifts)
			:"eax","ecx"
			);

#else
	_asm{
		MOV CX,rshifts
		MOV	EAX,sn_
		ROR	EAX,CL
		MOV	res,EAX
	}

#endif
	return res;
}
unsigned long Rol32(unsigned long sn_,short lshifts)
{
	unsigned long res;
#ifdef GCC_BUILD

	asm ("	MOV CX, %2 ;\n\t"
		 "	MOV EAX,%1 ;\n\t"
		 "	ROL	EAX,CL;\n\t"
		 "	MOV	%0,EAX;\n\t"
			:"=r" (res)
			:"r" (sn_),"r" (lshifts)
			:"eax","ecx"
			);

#else
	_asm{
		MOV CX,lshifts
		MOV	EAX,sn_
		ROL	EAX,CL
		MOV	res,EAX
	}

#endif
	return res;

}
unsigned  long get_cpu_sn()
{
#ifdef GCC_BUILD
//
//asm ( assembler template 
//           : output operands                  /* optional */
//           : input operands                   /* optional */
//           : list of clobbered registers      /* optional */
//           );

	asm ("	MOV EAX, 1 ;\n\t"
		 "	CPUID ;\n\t"
		 "	mov	%0,eax;\n\t"
		 "	MOV EAX, 3;\n\t"
		 "	CPUID ;\n\t"
		 "	mov	%1,EDX;\n\t"
		 "	mov	%2,ECX;\n\t"
			:"=m" (costy.sn_0),"=m"(costy.sn_1),"=m"(costy.sn_2)
			:
			:"eax","edx","ecx"
			);

	fprintf(stderr,"%x-%x-%x\n", costy.sn_0,costy.sn_1,costy.sn_2   );

	return costy.sn_0;
#else
	_asm{
	MOV EAX, 01H
	CPUID ;// EAX = HDWORD
	mov	costy.sn_0,eax
	MOV EAX, 03H
	CPUID ;// EDX,ECX
	mov	costy.sn_1,EDX
	mov	costy.sn_2,ECX
	}
#endif
}
bool cost()
{

	return true; // LibreSoft

	rlo('W','d','y');

	get_cpu_sn();
	for (short cnt=0; cnt < sizeof( ycosty)/sizeof( ycosty[0]);cnt++)
	{
	//	if (mycosty[cnt].sn_0==costy.sn_0 && mycosty[cnt].sn_1==costy.sn_1 && mycosty[cnt].sn_2==costy.sn_2)
	 	if (  ycosty[cnt].sn_0==costy.sn_0 &&  ycosty[cnt].sn_1==costy.sn_1 &&  ycosty[cnt].sn_2==costy.sn_2)
			//fprintf(stderr,"\nSHI\n");
			return true;
	}
			//fprintf(stderr,"\nBU\n");
	return false;
}
void wlo(short n1,short n2,short n3)
{
	get_cpu_sn();
	struct tagcosty yy=costy;

	yy.sn_0=Rol32(yy.sn_0,n1);
	yy.sn_1=Rol32(yy.sn_1,n2);
	yy.sn_2=Rol32(yy.sn_2,n3);


	char temp[]="TMC PACKAGE FOR DEMO USAGE ONLY. COPYRIGHT SHMUEL SAFONOV 2009-2015";
	FILE *fp=fopen(klum_file_name,"wb");
    fwrite( (const void *)&yy,sizeof(yy) ,1, fp);
	fprintf(fp,"%s",temp);
	fclose(fp);
}
void rlo(short n1,short n2,short n3)
{
	struct tagcosty yy;

	FILE *fp=fopen(klum_file_name,"rb");
    fread( ( void *)&yy,sizeof(yy) ,1, fp);
	fclose(fp);

	yy.sn_0=Ror32(yy.sn_0,n1);
	yy.sn_1=Ror32(yy.sn_1,n2);
	yy.sn_2=Ror32(yy.sn_2,n3);

	ycosty[0]=yy;
}

void han(void)
{

	// Handle ^Z for correct shut-down
		short nk=0;
		short n[3];

		fprintf(stderr,"TMC::>");

		for ( ; ;  )
		{
			if(_kbhit())
			{
				n[nk++] = _getch();
				if (n[nk-1]==0x1a)// ^Z
				{
					exit(-10);
				}
			}
			if (nk==3)
			{
			wlo(n[0],n[1],n[2]);
			exit(0);
			}
		}
}
#else
void han(void )
{
}
#endif
/////////////////// PERF ANA //////////////////////
LARGE_INTEGER mytimes[10];
LARGE_INTEGER freq;
LARGE_INTEGER mytimeaccum[10];
#ifndef LINUX_GPL
void perf_latch_time(short n)
{
	QueryPerformanceCounter( &mytimes[n]) ;
}
void perf_init(void)
{
	QueryPerformanceFrequency( &freq ) ;
	for (short k=0;k<10;k++) 
		mytimeaccum[k].QuadPart=0;
	
}
double perf_get_timediff(short st,short en)
{
	double out ;
	LARGE_INTEGER dt ;	
	
	dt.QuadPart = mytimes[en].QuadPart-mytimes[st].QuadPart;
	out = ((double)dt.QuadPart)/(double)(freq.QuadPart) ;//[sec]
	return out;
}
double perf_get_timeaccum(short n)
{
	double out ;
	out = ((double)mytimeaccum[n].QuadPart)/(double)(freq.QuadPart) ;//[sec]
	return out;
}
void perf_do_timeaccum(short n,short st,short en)
{
	LARGE_INTEGER dt ;	
	dt.QuadPart = mytimes[en].QuadPart-mytimes[st].QuadPart;

	mytimeaccum[n].QuadPart += dt.QuadPart;
}
#else
void perf_latch_time(short n)
{
	//QueryPerformanceCounter( &mytimes[n]) ;
}
void perf_init(void)
{
	//QueryPerformanceFrequency( &freq ) ;
	//for (short k=0;k<10;k++) 
	//	mytimeaccum[k].QuadPart=0;
	
}
double perf_get_timediff(short st,short en)
{
	double out=0 ;
	//LARGE_INTEGER dt ;	
	
	//dt.QuadPart = mytimes[en].QuadPart-mytimes[st].QuadPart;
	//out = ((double)dt.QuadPart)/(double)(freq.QuadPart) ;//[sec]
	return out;
}
double perf_get_timeaccum(short n)
{
	double out=0 ;
	//out = ((double)mytimeaccum[n].QuadPart)/(double)(freq.QuadPart) ;//[sec]
	return out;
}
void perf_do_timeaccum(short n,short st,short en)
{
	//LARGE_INTEGER dt ;	
	//dt.QuadPart = mytimes[en].QuadPart-mytimes[st].QuadPart;

	//mytimeaccum[n].QuadPart += dt.QuadPart;
}
#endif
///////// FILEs utils ////////////
std::string extract_file_name(std::string fn)
{
	int n=fn.find_last_of("\\");
	int n1 = fn.find_last_of("/");
	if (n<0)
		n=n1;
	if (n==fn.npos)
	{
		return fn;
	}
	else
	{
		return fn.substr(n+1);
	}
		
}
std::string change_file_ext(std::string fn,std::string fext)
{
	int n=fn.find_last_of(".");
	if (n==fn.npos)
	{
		return fn.append(".").append(fext);
	}
	else
	{
		return fn.substr(0,n+1).append(fext);
	}
}
short get_file_type(std::string fn)
{
	int n=fn.find_last_of(".");
	if (n==fn.npos || n<0)
	{
		return BIT_FILE_TYPE_UNKNOWN;
	}
	else
	{
		const char *str = fn.c_str();
		if (str[n+1]=='l')
			return BIT_FILE_TYPE_LSP;
		else if (str[n+1]=='m')
			return BIT_FILE_TYPE_M;
		else 
			return BIT_FILE_TYPE_UNKNOWN;
	}
}

std::string get_func_name_only(std::string s)
	{
		std::string retval=s;
		int n1=retval.find_last_of("\\");
		if (n1<0)
			n1=retval.find_last_of("/");
		int n2=retval.length( );

		//retval=retval.substr(n1+1,n2-n1-3);
		retval=retval.substr(n1+1,n2-n1);
		int n3 = retval.find_first_of(".");
		retval=retval.substr(0,n3);

		return retval;
	}
std::string get_file_name_only(std::string s)
	{
		std::string retval=s;
		int n1=retval.find_last_of("\\");
			if (n1<0)
			n1=retval.find_last_of("/");
		int n2=retval.length( );

		retval=retval.substr(n1+1,n2-n1-1);
		return retval;
	}
std::string get_dir_name_only(std::string s)
	{
		std::string retval=s;
		int n1=retval.find_last_of("\\");
		if (n1<0)
			n1=retval.find_last_of("/");
		int n2=retval.length( );

		retval=retval.substr(0,n1+1);
		return retval;
	}
#ifdef BLD_RTL_FEATURE
std::string find_src_in_filelist(std::list<std::string> lst, std::string fn)
{
	std::string res="";
	for (std::list<std::string>::iterator p=lst.begin();p!=lst.end();p++)
	{
		std::string strX =get_func_name_only( *p);
		if (strX.compare(fn)==0 )
		{
			return (*p);
		}
	}
return res;
}
#endif

bool append_incfilelist(std::string dn,std::string fn,std::list<std::string>& IncFileList)
{
	// first check this string already included
	// may not include the directory twice
	// returns bIncluded
	std::string strX,strY;
	bool bIncluded=false;
	std::string msg;
	std::string str1 = dn;
	str1.append(fn);

	for (std::list<std::string>::iterator p=IncFileList.begin();p!=IncFileList.end();p++)
	{
		strX = extract_file_name(*p);
		if (strX.compare(fn)==0 )
		{
			strY=*p;
			bIncluded=true;
		}
	}

	if (bIncluded==false)
		IncFileList.push_back(str1);
	else
	{
		msg="\n ** WARNING: FILE ";
		msg.append(str1);
		msg.append(" is already included as ");
		msg.append(strY);
		msg.append(", ignored, check -i option\n");

		fprintf(stderr,"%s\n",msg.c_str());
	}
	return bIncluded;
}

void append_incdirlist(std::string str1,std::list<std::string>& IncDirList)
{
	// first check this string already included
	// may not include the directory twice
	bool bIncluded=false;
	std::string msg;

	for (std::list<std::string>::iterator p=IncDirList.begin();p!=IncDirList.end();p++)
	{
		if ((*p).compare(str1)==0 )
		{
			bIncluded=true;
		}
	}

	if (bIncluded==false)
		IncDirList.push_back(str1);
	else
	{
		msg="\n ** Warning: PATH ";
		msg.append(str1);
		msg.append(" is already included, check -i option\n");

		fprintf(stderr,"%s",msg.c_str());
	}

}

#ifdef HAVE_OPENDIR
short bIsMFile(struct dirent *dit,short ftype);// check if the node if a regular file with demanded ext
short bIsMFile(struct dirent *dit,short ftype)
{ 
	int len;
#ifdef _DIRENT_HAVE_D_TYPE
	short is_regular_file =  (dit->d_type == DT_REG) ? 1:0;;
#else
	short is_regular_file;
	struct stat buf;
	int st = lstat(dit->d_name,&buf);
	is_regular_file = (st==0 && S_ISREG(buf.st_mode)) ? 1:0;
#endif

	
	if (is_regular_file)
	{
		// get file ext
		len = strlen(dit->d_name);
		if (ftype==BIT_FILE_TYPE_M)
		{
			if ((dit->d_name[len-1]=='m' ||  dit->d_name[len-1]=='M')
				&& dit->d_name[len-2]=='.')
				return 1;
			else
				return 0;
		}
		else
		if (ftype==BIT_FILE_TYPE_LSP)
		{
			if ( dit->d_name[len-3]=='l' && dit->d_name[len-2]=='s' && dit->d_name[len-1]=='p' 
				&& dit->d_name[len-4]=='.')
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else
		return 0;
}
#endif

void create_filelist(std::list<std::string>  DirList,std::list<std::string>&  myFileList,
					 const char *_filelist_file_name,short bfFileTypes)
{// create file list from all lsp-files in the given dir list
	FILE *fp;
	std::string mydir,mydir0,msg;
	short fTypes[BIT_FILE_TYPES]; // only too types
	
			int nDuplicated=0;
			int nFoundFiles=0;

        //int err=fopen_s(&fp,_filelist_file_name, "wt");
			fp=fopen(_filelist_file_name, "wt");
        if (fp == NULL) {
            perror("Could not open the filelist file"); exit(1);
        }
		int numPar =0;
		if (bfFileTypes & BIT_FILE_TYPE_M)
		{
			fTypes[numPar]	= 	BIT_FILE_TYPE_M;
			numPar++;
		}
		if (bfFileTypes & BIT_FILE_TYPE_LSP)
		{
			fTypes[numPar]	= 	BIT_FILE_TYPE_LSP;
			numPar++;
		}	
for (short uu=0;uu<numPar;uu++)
{
	for (std::list<std::string>::iterator p=DirList.begin();p!=DirList.end();p++)
	{
		mydir = *p;
		// enumerate files in this directory
#ifndef HAVE_OPENDIR
		struct _finddata_t m_file;
#else
		DIR *dip;
		struct dirent *dit;
#endif
		long hFile;
		mydir0=mydir;


#ifndef HAVE_OPENDIR		
		if (fTypes[uu]==BIT_FILE_TYPE_M)
			mydir.append("*.").append("m");
		else
			if (fTypes[uu]==BIT_FILE_TYPE_LSP)
				mydir.append("*.").append("lsp");

		if( (hFile = _findfirst((char*) mydir.c_str(), &m_file )) == -1L )
		{
			//fclose(fp);
			//msg="\n ** Warning: PATH ";
			//msg.append(mydir0);
			//msg.append(" not found, check -i option\n");
			//fprintf(stderr,"err=%d,%s\n",errno,msg.c_str());
			//return; // nothing found
			goto hFileDone;
		}
		else
		{		
				if (m_file.attrib !=_A_SUBDIR)

				{nFoundFiles++;
					if (append_incfilelist(mydir0.c_str(),m_file.name,myFileList))
						nDuplicated++;
					else
						fprintf(fp,"%s%s\n",mydir0.c_str(),m_file.name);

				}
		while( _findnext( hFile, &m_file ) == 0 )
            {
				if (m_file.attrib !=_A_SUBDIR) 
				{nFoundFiles++;
					if (append_incfilelist(mydir0.c_str(),m_file.name,myFileList))
						nDuplicated++;
					else
						fprintf(fp,"%s%s\n",mydir0.c_str(),m_file.name);
				}
			}
		}
		_findclose( hFile );
#else
		fprintf(stderr,"\n%s",mydir.c_str()   );
		if( (dip=opendir(mydir.c_str()))==NULL )
		{
			fprintf(stderr,"\n%s","NO ONO");
			goto hFileDone;
		}
		while( (dit=readdir(dip)) != NULL)
		{
			if(bIsMFile(dit,fTypes[uu]))
			{
			nFoundFiles++;
			fprintf(stderr,"\n%s",dit->d_name);

			if (append_incfilelist(mydir0.c_str(),dit->d_name,myFileList))
						nDuplicated++;
					else
						fprintf(fp,"%s%s\n",mydir0.c_str(),dit->d_name);
			}
		}
		closedir(dip);
#endif

hFileDone: 
		;
	}
}
	fclose(fp);
	if (nDuplicated>0)
				fprintf(stderr,"%s\n","duplicated file names in the include directories are ignored");
	if (nFoundFiles<1)
	{
				fprintf(stderr,"%s\n","no source files found");
	}
		// exit(3); // duplicated file names present in the include directories, cant proceed.
}
int Load_FncNames(const char *filename)
{
	FILE *fp;
	long nArgIn;
	long nArgOut;
	char nMode;
	char FuncName[502];
	char buf[502];
	int k,n1;

		//errno_t err = fopen_s(&fp,filename,"rt");
		fp=fopen(filename,"rt");
        if (fp == NULL) {
			perror(std::string("Could not open input file: ").append(filename).c_str()); 

			return -1;
		}
		//nread = fscanf_s(fp,"%s %d %d %c",FuncName,&nArgIn,&nArgOut);
		while (fgets(buf,500,fp) !=NULL)
		{

//fprintf(stderr,"[%s]\n",buf);

			k=0;
			FuncName[k]=buf[k];
			while (buf[k] != ',' && k<500)
			{
				FuncName[k]=buf[k];
				k++;
			}
			if (buf[k]==',')// end of func name
			{
				FuncName[k]=0;
				buf[k++]=0;
				n1=k;
				while (buf[k] != ',' && k<500)
				{
					k++;
				}
				if (buf[k]==',') // end of nargin
				{
					buf[k++]=0;
					nArgIn=atol(&buf[n1]);
					n1=k;
					while (buf[k] != ',' && k<500)
					{
						k++;
					}
					if (buf[k]==',') // end of nargout
					{
						buf[k++]=0;
						nArgOut=atol(&buf[n1]);
						n1=k;
						while (buf[k] != ';' && k<500)
						{
							k++;
						}
						if (buf[k]==';') // end string
						{
							buf[k++]=0;
							nMode=(char)(buf[n1]);
						}
					}
				}
			}
			if (k<500)
			{
				if (Compiler.verbose==true)
				fprintf(stderr,"Loaded: %s %d %d %c\n",FuncName,nArgIn,nArgOut,nMode);
				TmcSymbolTable.register_fnc_name(FuncName,nArgIn,nArgOut);
			}
			else
			{
				fprintf(stderr,"Ignored string\n");
			}
		}
		fclose(fp);
		return 0;
}

short LoadIncListFromCmdStr(char* filename,std::list<std::string> &_IncInputDirList,
							std::list<std::string> &_IncSrcDirList)
{
	FILE *fp;
	//char FuncName[1000];
	char buf[1010];
	int k,m;
	char inc_opt; // -i or -s

		//errno_t err = fopen_s(&fp,filename,"rt");
		fp=fopen(filename,"rt");
        if (fp == NULL) {
            perror("Could not open response file"); 
			return -1;
		}
		while (fgets(buf,500,fp) !=NULL)
		{
			k=0;
			while (buf[k] != '-' && k<1000)
			{
				k++;
			}
			if (buf[k] != '-')
				return -2;
			k++;
			inc_opt = buf[k];
			if (inc_opt != 'i' && inc_opt != 's')
				return -3;
			k++;
			while (buf[k] ==' ' && k<1000)
			{
				k++;
			}
			if (buf[k] == ' ')
				return -4;
			
			m=k;
			while (buf[m]!=0 && m<1000)
			{
				if (buf[m]=='\n' || buf[m]=='\r')
				{
					buf[m]=0;
					break;
				}
				m++;
			}
			if (inc_opt == 'i')
				append_incdirlist(std::string(&buf[k]),_IncInputDirList);
			else
			{
				Compiler.ask_print_src = true;// if src dir included print src lines
				append_incdirlist(std::string(&buf[k]),_IncSrcDirList);
			}

		}
		fclose(fp);
		return 0;
}
////// making tools ///////
// main data container for the compiler
int main(int argc, char *argv[]) {
    short stat=0;
#ifdef BLD_RTL_FEATURE
	fprintf(stderr,"TMC Converter, by Shmuel Safonov (C) 2009-2016, All rights reserved.\n");
#else
	fprintf(stderr,"\nTMC LSP Generator, by Shmuel Safonov (C) 2009-2016, All rights reserved.\n");
#endif
	perf_init();

	parse_command_line(argc, argv);
	Compiler.nFailed=0;Compiler.nProcessed=0;


	switch (Compiler.mode)
	{
#ifdef BLD_RTL_FEATURE
	case 'a':	
		return CompileMode_all();
	case 'p':	
		return CompileMode_prep_sym_table();
	case 'g':	
		return CompileMode_codegen(false);
	case 'f':	
		return CompileMode_codegen(true);
	case '?':
		Compiler.pass2only=true;
		CompileMode_prep_lsp();
		stat=CompileMode_codegen(false);
		if (Compiler.RunBlder) 
		{
			stat= RunBlder();
		}
		if (Compiler.keep_S_output==false)
		{
			// Delete intermediate S output
			DeleteSoutput();
		}
		return stat;
#endif
//#else // TEMPORARY
	case 'L':	
		return CompileMode_prep_lsp();
//#endif

	default:
		perror("TMC Converter -- invalid conversion option"); 
		return -1;
	}
 }

void print_usage()
{
/*
First pass (creation symbol table, string hash table):
TMCC –p –w <project name> -r <main filename> [–l <listing filename>] [–i <search path1>…] –o <out dir> 

Second pass (code generation):
TMCC –g –w <project name> -r < main filename> [–l <listing filename>] [–i <search path1>…] –o <out dir>

Compiling single file:
TMCC –w <project name> -f <filename> [–l <listing filename>] [–i <search path1>…] –o <out dir>
*/
#ifdef BLD_DEMO
	fprintf(stderr,"Usage: MCO_EXPRESS [-q] -L  -w <WKS>  -r <ROOT FILE> -l <LISTING> [–i <search path1>]* [–s <sources path1>]* -@ <INPUT LIST DIRS RSP FILE>  -o <OUTPUT DIR>\n");
	fprintf(stderr,"Usage: MCO_EXPRESS [-q] [-S] -g2 -w <WKS>  -r <ROOT FILE> -l <LISTING> [–i <search path1>]* [–s <sources path1>]* -@ <INPUT LIST DIRS RSP FILE>  -o <OUTPUT DIR>\n");
#else
	fprintf(stderr,"Usage: TMCPAR -w <WKS>  -r <ROOT FILE> -l <LISTING> [–i <search path1>]* -@ <INPUT LIST DIRS RSP FILE>  -o <OUTPUT DIR>\n");
	fprintf(stderr,"Usage: TMCCO [-d] [-q] -g2 -w <WKS>  -r <ROOT FILE> -l <LISTING> [–i <search path1>]* [–s <sources path1>]* -@ <INPUT LIST DIRS RSP FILE>  -o <OUTPUT DIR>\n");
#endif
	/*
    fprintf(stderr,
		"First pass (creation symbol table):\n %s –p –w <project name> -r <main filename> [–l <listing filename>] [–i <search path1>…] –o <out dir>\n",module_name); 

    fprintf(stderr,
		"Second pass (code generation):\n"
		"%s –g –w <project name> -r < main filename> [–l <listing filename>] [–i <search path1>…]\n"
		"–o <out dir>\n",module_name);
    fprintf(stderr,
		"Compiling single file:\n"
		"%s –w <project name> -f <filename> [–l <listing filename>] [–i <search path1>…]\n"
		"–o <out dir>\n",module_name);
	*/
    exit(1);
}

////////////////
void parse_command_line(int argc, char*argv[])
{
	std::string str1 ;
/* 
//module_name=argv[0];
	char *sPtr,*sPtrPrev;

	//GetModuleFileName( NULL , module_path , _MAX_PATH ) ;
   if (argc > 0) 
		strcpy( module_path, argv[0]);

	sPtr = strpbrk( module_path, "\\" );
	sPtrPrev=NULL;
	while (sPtr)
	{
		sPtrPrev=sPtr;
		sPtr= strpbrk( ++sPtr, "\\" );
	}
	if (sPtrPrev)
	{
		sPtrPrev[0]='\0';
	    strcpy( module_name, ++sPtrPrev);
		strcat(module_path,"\\");
	}
*/
	str1 = get_dir_name_only(argv[0]);
	strcpy( module_path, str1.c_str());
	std::string str2 = get_file_name_only(argv[0]);
	strcpy( module_name, str2.c_str());

	strcpy(klum_file_name,module_path);
	strcat(klum_file_name,"TMCHELP.BIN");

	if (argc==1)
	{han();
	}
	//Compiler.costn =true; //KOKOKO cost();



///////////////
// -w testm -f .\OdExample\testm.m -l testM.rtl.txt   -o .\Out\ -i .\OdExample\ > out.txt

    register int i;
    register char *s;
	char *opt_filename;
	char some_opt;

	dump_file_name[0]='\0';

	Compiler.mode='?';
	Compiler.RunBlder=0;
	Compiler.bUseDumpFile =false;
	Compiler.keep_S_output = false;
#ifdef BLD_RTL_FEATURE
	Compiler.code_output = 0; // asm output
	Compiler.C_output = 0;
	Compiler.comments_output = 0;
	Compiler.debuginfo=0;
	Compiler.support_try_catch = true;
#endif

	Compiler.lsp_output = 0; // debug output if needed
	Compiler.ask_print_src =false;
	Compiler.gen_for_all_list=false;
	Compiler.quiet = false;
	Compiler.pass2only=false;

    for (i = 1; i < argc; ++i)
    {
	s = argv[i];
	if (*s != '-') break;

	some_opt = *++s;
	switch (some_opt)
	{
	case '\0':
	    if (i + 1 < argc) print_usage();
	    goto opt_pars_done;

	case '-':
	    ++i;
	    goto no_more_options;

	case 'w': // work space name
	    if (*++s)
		{ 
			opt_filename = s;
		}
	    else if (++i < argc)
		opt_filename = argv[i];
	    else
		print_usage();

		strncpy(ws_file_name, opt_filename, PATH_MAX);
		continue;
#ifdef BLD_RTL_FEATURE
	case 'd': // debug information included
			Compiler.debuginfo=1;
		continue;

	case 'g': // C code generate
			Compiler.mode='g';
			if (*++s)
			{
				if (*s=='2')
				{
					Compiler.pass2only=true;
				}
			}
		continue;
	case 'p': // Parsing first stage
			Compiler.mode='p';
		continue;
	case 'S': // assembler code generation
		Compiler.code_output =1;
		Compiler.keep_S_output =1;
		continue;
	case 'c': // C code generation
		Compiler.C_output =1;
		continue;
	case 'C': // Comments generation
		Compiler.comments_output =1;
		continue;
#endif
	case 'A': // generate for all files
		Compiler.gen_for_all_list=true;
		continue;
	case 'P': // lsp code generation
		Compiler.lsp_output =1;
		continue;
	case 'L': // tmpcpar mode
			Compiler.mode='L';
		continue;
	case 'q': // quiet : minimal display
		Compiler.quiet=true;
		continue;
	case 'f': // single file C code generate

		Compiler.mode = 'f';

	    if (*++s)
		{ 
			opt_filename = s;
		}
	    else if (++i < argc)
		opt_filename = argv[i];
	    else
		print_usage();

		strncpy(input_file_name, opt_filename, PATH_MAX);

		str1 = get_dir_name_only(input_file_name);
		append_incdirlist(str1,IncInputDirList);
		strncpy(root_dir_name,str1.c_str(),str1.length()+1);

	    continue;
	case 'r': // root file name
		//Compiler.mode = *s;

	    if (*++s)
		{ 
			opt_filename = s;
		}
	    else if (++i < argc)
		opt_filename = argv[i];
	    else
		print_usage();

		strncpy(input_file_name, opt_filename, PATH_MAX);
		str1 = get_dir_name_only(input_file_name);
		append_incdirlist(str1,IncInputDirList);
		strncpy(root_dir_name,str1.c_str(),str1.length()+1);
	    continue;
	case 'l':

	    if (*++s)
		{ 
			opt_filename = s;
		}
	    else if (++i < argc)
		opt_filename = argv[i];
	    else
		print_usage();

		strncpy(dump_file_name, opt_filename, PATH_MAX);
		Compiler.bUseDumpFile=true;
	    continue;

	case 'i':  // input dir list
	case 's': // src dir list
	    if (*++s)
		{ 
			opt_filename = s;
		}
	    else if (++i < argc)
		opt_filename = argv[i];
	    else
		print_usage();

		//strncpy(input_dir_name,opt_filename, PATH_MAX);
		if (some_opt=='i')
			append_incdirlist(std::string(opt_filename),IncInputDirList);
#ifdef BLD_RTL_FEATURE
		else
		{
			Compiler.ask_print_src = true;// if src dir included print src lines
			append_incdirlist(std::string(opt_filename),IncSrcDirList);
		}
#endif
	    continue;
	case '@':
	    if (*++s)
		{ 
			opt_filename = s;
		}
	    else if (++i < argc)
		opt_filename = argv[i];
	    else
		print_usage();

		if (LoadIncListFromCmdStr(opt_filename,IncInputDirList,IncSrcDirList))
				print_usage();
	    continue;

	case 'o':

	    if (*++s)
		{ 
			opt_filename = s;
		}
	    else if (++i < argc)
		opt_filename = argv[i];
	    else
		print_usage();

		strncpy(output_dir_name,opt_filename, PATH_MAX);
	    continue;
	case 'h':

	    if (*++s)
		{ 
			opt_filename = s;
		}
	    else if (++i < argc)
		opt_filename = argv[i];
	    else
		print_usage();

		strncpy(libh_dir_name,opt_filename, PATH_MAX);
	    continue;


	default:
	    print_usage();
	}

	for (;;)
	{
	    switch (*++s)
	    {
	    case '\0':
		goto end_of_option;


	    default:
		print_usage();
	    }
	}
end_of_option:;
    }

no_more_options:;
     if (i   != argc) print_usage();

	//if (i + 1 != argc) print_usage();
    //input_file_name = argv[i];

opt_pars_done: 
///////////////
#ifdef BLD_DEMO
	Compiler.lsp_output=0;
	Compiler.gen_for_all_list=0; // compile all files (for prototypes generation etc.)
//	Compiler.costn=true;//mivtsa
	Compiler.quiet=true;
//	Compiler.pass2only=true;
	Compiler.code_output=1;
	Compiler.C_output=0;		
	Compiler.comments_output=0;   
	Compiler.RunBlder=true;
fprintf(stderr,"Running TMC EXPRESS CONVERTER...\n");
#endif
///////////////
	Compiler.verbose =false;

	if (strlen(ws_file_name)==0)
	{ // default ws name is the root function name
		std::string strX =get_func_name_only(input_file_name);
		strncpy(ws_file_name, strX.c_str(), strX.length()+1);
	}
	if (strlen(output_dir_name)==0)
	{
		strncpy(output_dir_name,"./",3);// default output dir
	}

	//TEMPORARY
	strncpy(filelist_file_name, output_dir_name, strlen(output_dir_name)+1);
	strcat(filelist_file_name, ws_file_name);
	strcat(filelist_file_name, ".filelist.txt");

    if (Compiler.bUseDumpFile) {
        dump_file = fopen(dump_file_name, "w");
        if (dump_file == NULL) {
            perror("Could not open the dump file"); exit(1);
        }
	}

	if ( Compiler.mode != 'f'  )
	{
			if (strlen(libh_dir_name)==0)
			{
				strncpy(libh_dir_name,module_path,strlen(module_path)+1);
				strcat(libh_dir_name,"../tmclib/");
			}

			if (Compiler.pass2only==false)
			{
			 strncpy(buildin_fnc_file_name, libh_dir_name, strlen(libh_dir_name)+1);
			 strcat(buildin_fnc_file_name,"buildin_fnc.sym.dat");
			}
			if (Compiler.pass2only==false)
			strncpy(symtable_file_name, output_dir_name, strlen(output_dir_name)+1);
			else
			strncpy(symtable_file_name, root_dir_name, strlen(root_dir_name)+1);

			strcat(symtable_file_name, ws_file_name);
			strcat(symtable_file_name,".sym.dat");
	}
	else
	{
		// single file compilation:
		// e.g. TMCC -d -c -C -h .\Stubs\testm.sym.dat -g2 -f EXAMPLE.m  -l .\OutC\testmx.err.log  -o .\OutC\ > outC2x.txt
		strncpy(symtable_file_name, libh_dir_name, strlen(libh_dir_name)+1);

	}
/////
#ifdef BLD_RTL_FEATURE
	strncpy(inputfilelist_file_name, output_dir_name, strlen(output_dir_name)+1);
	strcat(inputfilelist_file_name, ws_file_name);
	strcat(inputfilelist_file_name, ".inputfilelist.txt");

	strncpy(srcfilelist_file_name, output_dir_name, strlen(output_dir_name)+1);
	strcat(srcfilelist_file_name, ws_file_name);
	strcat(srcfilelist_file_name, ".srcfilelist.txt");


	strncpy(stdhead_file_name, output_dir_name, strlen(output_dir_name)+1);
	strncpy(&stdhead_file_name[strlen(output_dir_name)], "stdtmc.h", strlen("stdtmc.h")+1);



	strncpy(string_hash_file_name_in, output_dir_name, strlen(output_dir_name)+1);
	strcat(string_hash_file_name_in, ws_file_name);
	strcat(string_hash_file_name_in,".hash_init.dat");


	strncpy(string_hash_file_name_out, output_dir_name, strlen(output_dir_name)+1);
	strcat(string_hash_file_name_out, ws_file_name);
	strcat(string_hash_file_name_out,".hash_init.dat");


	strncpy(init_hash_data_file_name, output_dir_name, strlen(output_dir_name)+1);
	strcat(init_hash_data_file_name, ws_file_name);
	strcat(init_hash_data_file_name, "._init_hash_data.c");

	strncpy(globalhead_file_name, output_dir_name, strlen(output_dir_name)+1);
	strcat(globalhead_file_name, ws_file_name);
	strcat(globalhead_file_name, ".globals.h");

	strncpy(globalc_file_name, output_dir_name, strlen(output_dir_name)+1);
	strcat(globalc_file_name, ws_file_name);
	strcat(globalc_file_name, ".globals.c");


	if (Compiler.code_output==1)
	{
	strncpy(code_file_name, output_dir_name, strlen(output_dir_name)+1);
	strcat(code_file_name, ws_file_name);
	strcat(code_file_name, ".code.asm");



	strncpy(string_hash_file_asm_name_out, output_dir_name, strlen(output_dir_name)+1);
	strcat(string_hash_file_asm_name_out, ws_file_name);
	strcat(string_hash_file_asm_name_out,".hash_init.dat.inc");

	strncpy(globalc_asm_file_name, output_dir_name, strlen(output_dir_name)+1);
	strcat(globalc_asm_file_name, ws_file_name);
	strcat(globalc_asm_file_name, ".globals.inc");
	}

	strncpy(external_fnc_file_name, root_dir_name, strlen(root_dir_name)+1);
	strcat(external_fnc_file_name,"external_fnc.sym.dat");
#endif
}


long CopyChar2Uni( wchar_t *sh ,  const char *str , unsigned long maxLen );

long CopyChar2Uni( wchar_t *sh ,  const char *str , unsigned long maxLen )
{
	unsigned long ind ;
	//__asm {
	//	int 4
	//}
	for( ind = 0 ; ind < maxLen ; ind++ )  
	{
		if( str[ind] == 0 )
		{
			break ;
		}
		sh[ind] = (wchar_t)str[ind] ;		
	}
	sh[ind] = 0 ;
	return ind ;
}

short DeleteSoutput(void)
{
	//HAZARD_TODO
	return 0;
}


short RunBlder(void)
{
#ifndef LINUX_GPL
#ifdef UNICODE
	short isActive ;
	unsigned long exitCode ;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	BOOL h;
	wchar_t sCommandLine[10000];
	wchar_t InputFileName[_MAX_PATH];
	wchar_t OutputFileName[_MAX_PATH];
	wchar_t wchar_module_path[_MAX_PATH];
	wchar_t OutputPath[_MAX_PATH];

	long nlen;
	
	CopyChar2Uni(&InputFileName[0],code_file_name,_MAX_PATH-1);

	CopyChar2Uni(&OutputFileName[0],output_dir_name,_MAX_PATH-1);
	nlen = wcslen(OutputFileName);

	CopyChar2Uni(&OutputPath[0],output_dir_name,_MAX_PATH-1);


	CopyChar2Uni(&OutputFileName[nlen],ws_file_name,_MAX_PATH-1);
	nlen = wcslen(OutputFileName);

	CopyChar2Uni(&OutputFileName[nlen],".EXE",_MAX_PATH-1);

	CopyChar2Uni(&wchar_module_path[0],module_path,_MAX_PATH-1);

	swprintf(sCommandLine,L"%snasm_for_tmc.exe -I%s..\\tmclib\\ -I%s -O0   -o %s   %s",wchar_module_path,wchar_module_path,OutputPath,OutputFileName,InputFileName);

    ZeroMemory(&si, sizeof(si) );
	ZeroMemory(&pi, sizeof(pi) );
    si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW ;//(STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	si.wShowWindow = SW_HIDE;//or SW_MINIMIZE;SW_SHOW ;
	si.hStdError = NULL ;
	si.hStdInput = NULL ;
	si.hStdOutput = NULL ;
    h = CreateProcess(0,	// No module name (use command line).
        &sCommandLine[0],				// Command line.
        0,					// Process handle not inheritable.
        0,					// Thread handle not inheritable.
        TRUE,					// Set handle inheritance to TRUE.
        0,						// No creation flags.
        0,					// Use parent's environment block.
        0,					// Use parent's starting directory.
        &si,					// Pointer to STARTUPINFO structure.
        &pi );

	//	MessageBox(0,sCommandLine ,L" start EXE builder:",MB_ICONEXCLAMATION|MB_TASKMODAL);

	fwprintf(stderr,L"\nSHELL> %s\n",sCommandLine);
	fflush(stderr);

	if( h == 0 )
	{
		//MessageBox(0,sCommandLine ,L"Cant start EXE builder:",MB_ICONEXCLAMATION|MB_TASKMODAL);
		//DEBUG: fwprintf(stderr,L"\n ******** FAIL: can start process %s\n",sCommandLine);
		fwprintf(stderr,L"\n****** FAIL generating %s%s\n",OutputPath,OutputFileName);
		fflush(stderr);

		return -1;
	}

    // Wait until child process exits.
    CloseHandle(pi.hThread );


	fwprintf(stderr,L"\nGenerating %s...\n",OutputFileName);
	fflush(stderr);

	while( 1 )
	{
		Sleep(200);
		isActive = GetExitCodeProcess( pi.hProcess, &exitCode ) ;
		if ( exitCode != STILL_ACTIVE )
		{
			break ;
		}
		if( isActive == 0 )
		{
			break;
		}
	}
    CloseHandle(pi.hProcess );

	fwprintf(stderr,L"\nFinished generating code");
	fflush(stderr);
#endif // UNICODE
#endif // LINUX_GPL
	return 1;
}