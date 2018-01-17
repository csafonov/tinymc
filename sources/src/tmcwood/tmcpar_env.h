/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
#ifndef _tmcpar_env_
#define _tmcpar_env_

#include <stdlib.h>
#include <string.h>

#include <string>
#include <list>

#ifdef LINUX_GPL
#ifndef _MAX_PATH
#define  _MAX_PATH	10000
#endif
typedef long LARGE_INTEGER;
#define _stricmp strcasecmp    // low/upper case insencsity for identifications
#endif

//_CRT_SECURE_NO_DEPRECATE
#pragma warning( disable: 4996)
#pragma warning(disable: 4102)
#pragma warning(disable:4065) 
#pragma warning(disable:4800)

#define PATH_MAX 1024

#define BIT_FILE_TYPE_UNKNOWN		0x0000
#define BIT_FILE_TYPE_M		0x0001
#define BIT_FILE_TYPE_LSP	0x0002
#define BIT_FILE_TYPES		2

class CCompilerExcpt
{
public:
    CCompilerExcpt(){};
    ~CCompilerExcpt(){};
    const char *ShowReason() const { return "Exception"; }
};

//! Helper class
class CCompiler
{
private:
	std::string _m_file_name;
public:
	char mode; 
	bool verbose;
	short lsp_output;
	bool  gen_for_all_list; // compile all files (for prototypes generation etc.)
//	bool  costn;
	long  nFailed;//state
	long  nProcessed;//state
	long  nErrInFile;
	long  nWarnInFile;
	long  nTotalErrors;
	long  nTotalWarnings;
	bool  quiet;
	bool pass2only;
#ifdef BLD_RTL_FEATURE
	bool support_try_catch;
	short code_output;
	short C_output;			// -c
	short comments_output;  // -C comments in C  and Asm files 
	short print_src;// is -s and the src file is found 
	short debuginfo;
#endif
	bool  ask_print_src;//state
	short bfFileType; // BIT_FILE_TYPE_ mask
	bool RunBlder;
	bool bUseDumpFile;
	bool keep_S_output;
	int	indFunc;//!< Scope at parser stage. (index of local function being parsed)
	int	indFunc_RTL;//!< Scope at RTL stage. (index of local function being generated code for)
public:
	void InitFileErrLog(std::string _file_name) {nErrInFile=0;nWarnInFile=0;_m_file_name=_file_name;};
	void FinalizeFileErrLog() { if (nErrInFile > 0) throw( CCompilerExcpt()); };
	void LogErr(int errcode, std::string msg,std::string symb, int line,bool fatal=false);//!< produce error message
	void LogWarn(int errcode, std::string msg,std::string symb, int line);//!< produce warning message
	void PrintSummary(void);
	CCompiler()
	{
	 nTotalErrors=0;
	 nTotalWarnings=0;
	}
};

extern class CCompiler Compiler;
extern int error_level;

void wlo(short n1,short n2,short n3);
void rlo(short n1,short n2,short n3);
extern char klum_file_name[] ;
void han(void);
bool cost(void);

#ifdef GCC_BUILD
#define haha()   asm("	int 4")
#else
#define haha()   _asm { int 4 }
#endif

// lexer internals /////
extern int tmcpar_lex (void);
extern int tmcpar_lineno;
extern int tmcpar_colno;

extern void tmcpar_error(const char *);
extern "C" int tmcpar_wrap (void);
int tmcpar_parse ();

void reset_parser(void);// for tmcpar

int  tmc_parse(void);// call yyparse(), add symbols to the symbol table and filenames to FileStack 

//long ReturnLspToken(long TokVal);//static


#ifdef BLD_RTL_FEATURE
extern int tmclsp_lex (void);

extern int tmclsp_lineno;
void reset_lspparser(void);
void tmclsp_error(const char *);
extern "C" int tmclsp_wrap (void);
int tmclsp_parse(void);// call yyparse(), add symbols to the symbol table and filenames to FileStack 
void reset_lsp_lexer();
//void dbgPrintLspToken(long TokVal);//static
#endif

////////// FILES /////////////
extern std::list<std::string>  IncInputDirList; // analog of matlab path plus root file directory 
extern std::list<std::string>  IncInputFileList; // full list of files in all path 
// For Compiler.ask_print_src=1 option only:
#ifdef BLD_RTL_FEATURE
extern std::list<std::string>  IncSrcDirList; // analog of matlab path plus root file directory 
extern std::list<std::string>  IncSrcFileList; // full list of files in all path 
#endif

/// environment utils
extern FILE *dump_file;// listing file
extern FILE *tmc_output; // output c-file
extern FILE *lsp_file;// lsp-file
extern FILE *tmc_in;// input file for tmcpar lexer


#ifdef BLD_RTL_FEATURE
extern FILE *tmclsp_in; // current input file for lsp-parser
extern FILE *stdhead_file;
extern FILE *code_file;// code-file
extern FILE *tmc_src;// lsp-file
#endif

// Full name of file we are reading.
extern std::string curr_fcn_file_full_name;

extern char input_file_name[PATH_MAX + 2];
extern char dump_file_name[PATH_MAX + 4];
extern char output_dir_name[PATH_MAX + 4];
extern char root_dir_name[PATH_MAX + 4];
extern char libh_dir_name[PATH_MAX + 4];

extern char ws_file_name[PATH_MAX + 4];
extern char klum_file_name[PATH_MAX + 4];

extern char symtable_file_name[PATH_MAX + 4];//mynew
extern char buildin_fnc_file_name[PATH_MAX + 4];//mynew

extern char filelist_file_name[PATH_MAX + 4];

extern char module_name[_MAX_PATH+2];
extern char module_path[_MAX_PATH+2];

#ifdef BLD_RTL_FEATURE
extern std::string c_file_name;

extern char stdhead_file_name[PATH_MAX + 4];
extern char external_fnc_file_name[PATH_MAX + 4];
extern char string_hash_file_name_in[PATH_MAX + 4];
extern char string_hash_file_name_out[PATH_MAX + 4];
extern char init_hash_data_file_name[PATH_MAX + 4];
extern char globalhead_file_name[PATH_MAX + 4];
extern char globalc_file_name[PATH_MAX + 4];

extern char code_file_name[PATH_MAX + 4]; // for assembler file
extern char string_hash_file_asm_name_out[PATH_MAX + 4];// for assembler file
extern char globalc_asm_file_name[PATH_MAX + 4];// for assembler file

extern char inputfilelist_file_name[PATH_MAX + 4];
extern char srcfilelist_file_name[PATH_MAX + 4];

#endif
/////////////////////////

/// FILE UTILS ///////////
std::string extract_file_name(std::string fn);
std::string change_file_ext(std::string fn,std::string fext);
short get_file_type(std::string fn);

std::string get_func_name_only(std::string s);
std::string get_file_name_only(std::string s);
std::string get_dir_name_only(std::string s);
#ifdef BLD_RTL_FEATURE
std::string find_src_in_filelist(std::list<std::string> lst, std::string fn);
#endif	
bool append_incfilelist(std::string dn,std::string fn,std::list<std::string>& IncFileList);
void append_incdirlist(std::string str1,std::list<std::string>& IncDirList);
void create_filelist(std::list<std::string>  DirList,std::list<std::string>&  myFileList,const char *_filelist_file_name,short bfFileTypes);
int Load_FncNames(const char *filename);
short LoadIncListFromCmdStr(char* filename,std::list<std::string> &_IncInputDirList,
							std::list<std::string> &_IncSrcDirList);
/// PERF ana
#ifndef LINUX_GPL
#include <windows.h>
#endif

extern LARGE_INTEGER mytimes[10];

extern LARGE_INTEGER mytimeaccum[10];
extern LARGE_INTEGER freq;
void perf_latch_time(short n);
void perf_init(void);
double perf_get_timediff(short st,short en);
double perf_get_timeaccum(short n);
void perf_do_timeaccum(short n,short st,short en);
/////////////////////////////
/// Output tools
void create_init_hash_data_file(char *_file_name);
/////// MAKING TOOLS //////////////////////////
void parse_command_line(int argc, char*argv[]);
void print_usage();
short RunBlder(void);
short DeleteSoutput(void);

int CompileMode_prep_lsp(void);

#ifdef BLD_RTL_FEATURE
int CompileMode_all(void);
int CompileMode_prep_sym_table(void);
int CompileMode_codegen(bool bSingleFile);
#endif

#endif
