//! \file tmc_mak_lc.cpp
//! \brief Main() function implementation for tmclsp (tmcco.exe)

////////////// main //////////////////
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/

#ifndef LINUX_GPL
#include <windows.h>
#endif

//#pragma warning(disable:4267) // hazard conversion from 'size_t' to 'int', possible loss of data

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef LINUX_GPL
#include <io.h>
#endif

#include <string>
#include <stack>

#define OWNWER_LEXVARS

#include "tmcpar_tree.h"
#include "TmcLspParser.tab.hpp"
#include "tmcpar_utils.h"





int CompileMode_all()
// simple method - parse and compile all the files using lists
{

   //init_compiler();
    //load_external_func_list();
tmc_output=NULL;
	create_filelist(IncInputDirList,IncInputFileList,inputfilelist_file_name,BIT_FILE_TYPE_LSP);
	TmcFileList.LoadFileList(inputfilelist_file_name,&TmcSymbolTable); // load inputfilelist.txt

	// load built-in functions list: <name, in_args,out_args>
	// for function with variable number of inputs: ,in_args<0
	Load_FncNames(buildin_fnc_file_name);
	Load_FncNames(external_fnc_file_name);

/*
	// special symbols
	// e.g: symbol_table::register_fnc_name("nargin",0,1);
	// these functions are used in with command syntax and if not defined - parser is
	// aborted since they are assumed to be vaiables and lexer doesnt enter COMMAND_START state.
	// e.g: symbol_table::register_fnc_name("hold",1,0);
*/

	// PASS1: only populate the symbol table and check syntax.
	TmcFileList.PushFileStack(input_file_name);
	char buffer_l[PATH_MAX];

	while (TmcFileList.IsFileStackEmpty()==false)
	{
		std::string fn=TmcFileList.PopFileStack();
		symbol_table::record_iterator p =TmcSymbolTable.find_symbol(fn,false,-1);//!< search for a function
		if (p!=TmcSymbolTable.nil())
		{
			p->m_modifier.m_in_stack=0;
		}
		// if the file is already parsed - skip it. We dont put such file to the stack.
		//sprintf_s(buffer_l,PATH_MAX-2,"%s","C:\\Data_D\\HSKOST\\Borisenko\\tinyMcc\\MatExSrc\\myfilter.m");
		sprintf(buffer_l,"%s",fn.c_str());
		//errno_t err = fopen_s(&tmclsp_in,buffer_l,"rt");
		tmclsp_in=fopen(buffer_l,"rt");
        if (tmclsp_in == NULL) {
            perror(std::string("Could not open input file:").append(buffer_l).c_str()); 
 			exit(1);
		}
		//if (Compiler.bUseDumpFile) fprintf(dump_file,"\n------------- PASS1 BEGIN FILE: %s-----------\n ",fn.c_str());
		if (Compiler.bUseDumpFile) fprintf(dump_file,"%s\n ",fn.c_str());
		reset_lspparser();
		curr_fcn_file_full_name=fn;
		try
		{
		tmclsp_parse();// call yyparse(), add symbols to the symbol table and filenames to FileStack 
		if(Compiler.lsp_output)
				print_tmcpar_tree(tmcpar_parsing_module);
		//fprintf(stderr,"\n pass1 FILE: %s done\n ",fn.c_str());
		}
		catch(...)
		{
		if (Compiler.bUseDumpFile) fprintf(dump_file,"\n**** Errors in FILE (%d): %s-----------\n ",tmclsp_lineno,fn.c_str());
		fprintf(stderr,"\n**** Errors in FILE (%d): %s-----------\n ",tmclsp_lineno,fn.c_str());
		}
		fclose(tmclsp_in);
		tmclsp_in=NULL;
		//if (Compiler.bUseDumpFile) fprintf(dump_file,"\n------------- PASS1 END FILE: %s-----------\n ",fn.c_str());
		TmcFileList.AppendFinalList(fn);
		TmcSymbolTable.erase_local_variables();
	}
	// PASS2: generate code (.c and .h files)
	std::string fn=TmcFileList.InitIterateFinalList();
	stdhead_file = fopen(stdhead_file_name, "w");
	
	while (fn.length())
	{
		std::string h_file_name=fn;
		
		c_file_name = output_dir_name;
		c_file_name.append(extract_file_name(fn));

		tmclsp_in = fopen(fn.c_str(), "rt");
        if (tmclsp_in == NULL) {
            perror("Could not open input file");
			exit(1);
		}
		if (Compiler.C_output)
		{
			tmc_output = fopen(c_file_name.append(".c").c_str(), "w");
			if (tmc_output == NULL) {
				perror("Could not open output file"); exit(1);
			}
		}

		if (Compiler.bUseDumpFile) fprintf(dump_file,"\n------------- PASS2 BEGIN FILE: %s-----------\n ",fn.c_str());
		reset_lspparser();
		try
		{
		tmclsp_parse();// call yyparse(), add symbols to the symbol table and filenames to FileStack 
		if(Compiler.lsp_output)
				print_tmcpar_tree(tmcpar_parsing_module);// print debug listing
		generate_rtl_list();// print compiled output

		fprintf(stderr,"\n code FILE: %s done\n ",fn.c_str());
		}
		catch(...)
		{
		if (Compiler.bUseDumpFile) fprintf(dump_file,"\n**** Pass 2: Errors in FILE (%d): %s-----------\n ",tmclsp_lineno,fn.c_str());
		fprintf(stderr,"\n**** Pass 2: Errors in FILE (%d): %s-----------\n ",tmclsp_lineno,fn.c_str());
		}
		fclose(tmclsp_in);tmclsp_in=NULL;
		if (tmc_output) fclose(tmc_output);tmc_output=NULL;
		if (Compiler.bUseDumpFile) fprintf(dump_file,"\n------------- PASS2 END FILE: %s-----------\n ",fn.c_str());
		fn=TmcFileList.NextIterateFinalList();
		TmcSymbolTable.erase_local_variables();
	}
	fclose(stdhead_file);
	stdhead_file=NULL;


	if (Compiler.bUseDumpFile) fclose(dump_file);
    return error_level;

}
int CompileMode_prep_sym_table()
{
		std::string m_file_name;
		std::string lsp_file_name;

	fprintf(stderr,"\nPASS1...\n");

   //init_compiler();
    //load_external_func_list();

	create_filelist(IncInputDirList,IncInputFileList,inputfilelist_file_name,BIT_FILE_TYPE_LSP);
	TmcFileList.LoadFileList(inputfilelist_file_name,&TmcSymbolTable); // load filelist.txt

	if (Compiler.ask_print_src)
	{
	create_filelist(IncSrcDirList,IncSrcFileList,srcfilelist_file_name,BIT_FILE_TYPE_M);
	}
	// load built-in functions list: <name, in_args,out_args>
	// for function with variable number of inputs: in_args<0
	Load_FncNames(buildin_fnc_file_name);
	Load_FncNames(external_fnc_file_name);

	// PASS1: only populate the symbol table and check syntax.
	TmcFileList.PushFileStack(input_file_name);
//	char buffer_l[PATH_MAX];

	while (TmcFileList.IsFileStackEmpty()==false)
	{
		std::string fn=TmcFileList.PopFileStack();
		symbol_table::record_iterator p =TmcSymbolTable.find_symbol(fn,false,-1);// search for a function
		if (p!=TmcSymbolTable.nil())
		{
			p->m_modifier.m_in_stack=0;
		}
		// if the file is already parsed - skip it. We dont put such file to the stack.
		//sprintf_s(buffer_l,PATH_MAX-2,"%s","C:\\Data_D\\HSKOST\\Borisenko\\tinyMcc\\MatExSrc\\myfilter.m");
		
		m_file_name = fn;//root_dir_name;
		//m_file_name.append(extract_file_name(fn));
		tmclsp_in = fopen(m_file_name.c_str(), "rt");
		
		//sprintf_s(buffer_l,PATH_MAX-2,"%s",fn.c_str());
		//errno_t err = fopen_s(&tmclsp_in,buffer_l,"rt");
        if (tmclsp_in == NULL) {
            perror("Could not open input file"); exit(1);
		}

		if (Compiler.lsp_output)
		{
			lsp_file_name = output_dir_name;
			lsp_file_name.append(change_file_ext(extract_file_name(fn),"lsp"));
			lsp_file = fopen(lsp_file_name.c_str(), "w");
			if (lsp_file == NULL) {
				perror("Could not open lsp output file"); exit(1);
			}
		}
		//if (Compiler.bUseDumpFile) fprintf(dump_file,"\n------------- PASS1 BEGIN FILE: %s-----------\n ",fn.c_str());
				if (Compiler.bUseDumpFile) fprintf(dump_file,"%s\n ",fn.c_str());
		reset_lspparser();
		curr_fcn_file_full_name=fn;
		try
		{
		if (Compiler.quiet==false)
		fprintf(stderr,"%s\n ",fn.c_str());
	
		tmclsp_parse();// call yyparse(), add symbols to the symbol table and filenames to FileStack 
		if(Compiler.lsp_output)
				print_tmcpar_tree(tmcpar_parsing_module);
		//fprintf(stderr,"\n pass1 FILE: %s done\n ",fn.c_str());
		}
		catch(...)
		{
		if (Compiler.bUseDumpFile) fprintf(dump_file,"\n**** Errors in FILE (%d): %s-----------\n ",tmclsp_lineno,fn.c_str());
		fprintf(stderr,"\n**** Errors in FILE (%d): %s-----------\n ",tmclsp_lineno,fn.c_str());
		}
		fclose(tmclsp_in);
		tmclsp_in=NULL;
        if (lsp_file)
			fclose(lsp_file);
		lsp_file=NULL;

		//if (Compiler.bUseDumpFile) fprintf(dump_file,"\n------------- PASS1 END FILE: %s-----------\n ",fn.c_str());
		TmcFileList.AppendFinalList(fn);
		TmcSymbolTable.erase_local_variables();
		//fclose(lsp_file);lsp_file=NULL;

	}
	TmcSymbolTable.PrintSymTable(symtable_file_name);
	TmcSymbolTable.PrintCommonHeader(stdhead_file_name);
	TmcSymbolTable.PrintGlobalsDefs(globalhead_file_name,globalc_file_name);



	FILE* tmc_hash = fopen(string_hash_file_name_out, "w");
        if (tmc_hash == NULL) {
            perror("Could not open output string_hash_file"); exit(1);
		}

	StringHash.print_hash_table(tmc_hash);
	fclose(tmc_hash);

	if (Compiler.bUseDumpFile) fclose(dump_file);



    return error_level;

}
int CompileMode_codegen(bool bSingleFile)
{
perf_latch_time(0);
tmc_output=NULL;
stdhead_file=NULL;
	fprintf(stderr,"\nFILES LOADING...\n");
	fflush(stderr);
	std::string lsp_file_name;

		if (Compiler.code_output==1)
		{
			if (code_file_name[0] != 0) {
				code_file = fopen(code_file_name, "w");
				if (code_file == NULL) {
					perror("Could not open the code file"); exit(1);
				}
			}
			fprintf(code_file,"\t%%include \"PE_head.inc\"\n");

			fprintf(code_file,"\t%%include \"%s.hash_init.dat.inc\"\n",ws_file_name);
			fprintf(code_file,"\t%%include \"%s.globals.inc\"\n",ws_file_name);

			fprintf(code_file,"\t%%define MAIN_ENTRY\t_tmc%s\n",ws_file_name);

			fprintf(code_file,"\t%%include \"myinc.inc\"\n");
		}
if (Compiler.mode != '?')
{
	create_filelist(IncInputDirList,IncInputFileList,inputfilelist_file_name,BIT_FILE_TYPE_M|BIT_FILE_TYPE_LSP);
}
	if (Compiler.ask_print_src)
	create_filelist(IncSrcDirList,IncSrcFileList,srcfilelist_file_name,BIT_FILE_TYPE_M);


if (Compiler.C_output)
	create_init_hash_data_file(init_hash_data_file_name);

if (Compiler.mode != '?')
	TmcFileList.LoadFileList(inputfilelist_file_name,&TmcSymbolTable); // load filelist.txt
	// load built-in functions list: <name, in_args,out_args>
	// for function with variable number of inputs: in_args<0
	
	// Actually symbol table is ready.
	//Load_FncNames(buildin_fnc_file_name);
	Load_FncNames(symtable_file_name);
	if (Compiler.pass2only==true)
	{
	Load_FncNames(external_fnc_file_name);
	}

	if (Compiler.pass2only==false)
	{
		FILE* tmc_hash_tmp = fopen(string_hash_file_name_in, "r");
			if (tmc_hash_tmp == NULL) {
				perror("Could not open string_hash_file_name_in file"); exit(1);
			}

		if (	StringHash.load_hash_table(tmc_hash_tmp))
		{
			fclose(tmc_hash_tmp);
			exit(2);
		}
			fclose(tmc_hash_tmp);
	}

if (Compiler.mode != '?')
	if (bSingleFile==false)
		TmcFileList.LoadFinalList(inputfilelist_file_name,&TmcSymbolTable); // load filelist.txt

	//HAZARD: the main file is in the FinalList
	//TmcSymbolTable.AppendFinalList(input_file_name);//HAZARD

	// ONLY PASS2: generate code (.c and .h files)
	std::string fn=TmcFileList.InitIterateFinalList();
	if (Compiler.C_output)
		if (bSingleFile==false)
			stdhead_file = fopen(stdhead_file_name, "w");
	
	fprintf(stderr,"\nLSP CONVERSION...\n");
	fflush(stderr);

perf_latch_time(1);

	while (fn.length())
	{
		std::string h_file_name=fn;
		std::string m_file_name;

		m_file_name = fn;//root_dir_name;
		Compiler.bfFileType = get_file_type(m_file_name);
		Compiler.InitFileErrLog(m_file_name);
		//m_file_name.append(extract_file_name(fn));

		c_file_name = output_dir_name;
		c_file_name.append(change_file_ext(extract_file_name(fn),"c"));

		tmclsp_in = fopen(m_file_name.c_str(), "rt");
        if (tmclsp_in == NULL) {
            perror("Could not open input file"); exit(1);
		}
		Compiler.print_src=0;
		if (Compiler.ask_print_src)
		{
			std::string fnSrc = find_src_in_filelist(IncSrcFileList,get_func_name_only(fn));
				if (fnSrc.length()>0)
				{
					tmc_src = fopen(fnSrc.c_str(), "rt");
					if (tmc_src == NULL)
					{
						//perror("Could not open src file"); exit(1);
					}
				}
				if (tmc_src == NULL)
				{
					Compiler.print_src=0;
					if (Compiler.bUseDumpFile) fprintf(dump_file,"** INFO: SRC file not found: %s\n",get_func_name_only(fn).c_str());
					fprintf(stderr,"** INFO: SRC file not found: %s\n",get_func_name_only(fn).c_str());
				}
				else
				{
					Compiler.print_src=1;
				}

		}


	if (Compiler.C_output)
	{
		tmc_output = fopen(c_file_name.c_str(), "w");
        if (tmc_output == NULL) {
            perror("Could not open output file"); exit(1);
		}
	}
		if (Compiler.lsp_output)
		{
			lsp_file_name = output_dir_name;
			lsp_file_name.append(change_file_ext(extract_file_name(fn),"log2.lsp"));
			lsp_file = fopen(lsp_file_name.c_str(), "w");
			if (lsp_file == NULL) {
				perror("Could not open lsp output file"); exit(1);
			}
		}

//lsp		if (Compiler.bUseDumpFile) fprintf(dump_file,"\n------------- PASS2 BEGIN FILE: %s-----------\n ",fn.c_str());
	if (Compiler.bfFileType==BIT_FILE_TYPE_LSP)
			reset_lspparser();
	else if (Compiler.bfFileType==BIT_FILE_TYPE_M)
	{
		tmc_in=tmclsp_in; // make available for tmcpar 
		reset_parser();
	}
		try
		{
			if (Compiler.quiet==false)
				fprintf(stderr,"%s\n",fn.c_str());
			Compiler.nProcessed++;

	if (Compiler.bfFileType==BIT_FILE_TYPE_LSP)
		tmclsp_parse();// call yyparse(), add symbols to the symbol table and filenames to FileStack 
	else if (Compiler.bfFileType==BIT_FILE_TYPE_M)
	{
		tmc_parse();// call yyparse(), add symbols to the symbol table and filenames to FileStack 
	}
	//tmclsp_parsing_module = get_tmclsp_parsing_module(tmcpar_parsing_module);

		if(Compiler.lsp_output)
				print_tmcpar_tree(tmcpar_parsing_module);// print debug listing
		
		generate_rtl_list();// print compiled output
		//fprintf(stderr,"\n code FILE: %s done\n ",fn.c_str());
		Compiler.FinalizeFileErrLog();
		}
		catch(...)
		{
					Compiler.nFailed++;// panic
					if (tmc_output)
					{
						tmc_output = freopen(c_file_name.c_str(),"w",tmc_output);
					}

		if (Compiler.bUseDumpFile) fprintf(dump_file,"\n**** Pass 2: Errors in FILE (%d): %s-----------\n ",tmclsp_lineno,fn.c_str());
		fprintf(stderr,"\n**** Pass 2: Errors in FILE (%d): %s-----------\n ",tmclsp_lineno,fn.c_str());
		}
		fclose(tmclsp_in);tmclsp_in=NULL;
		if (tmc_output) fclose(tmc_output);tmc_output=NULL;
		if (lsp_file) fclose(lsp_file);lsp_file=NULL;
		if (Compiler.print_src)
		fclose(tmc_src);
		tmc_src=NULL;

//lsp		if (Compiler.bUseDumpFile) fprintf(dump_file,"\n------------- PASS2 END FILE: %s-----------\n ",fn.c_str());
		fn=TmcFileList.NextIterateFinalList();
		TmcSymbolTable.erase_local_variables();
	}
	if (bSingleFile==false)

	{
		if (stdhead_file) fclose(stdhead_file);
		stdhead_file=NULL;
	}
	if (Compiler.code_output==1)
	{
			fprintf(code_file,"\t%%include \"PE_tail.inc\"\n");
			fclose(code_file);

			FILE* tmc_hash_asm = fopen(string_hash_file_asm_name_out, "w");
				if (tmc_hash_asm == NULL) {
					perror("Could not open output file"); exit(1);
				}

			StringHash.print_hash_table_asm(tmc_hash_asm);
			fclose(tmc_hash_asm);

			TmcSymbolTable.PrintGlobalsDefsAsm(globalc_asm_file_name);

	}

if (Compiler.C_output)
{
	FILE* tmc_hash = fopen(string_hash_file_name_out, "w");
        if (tmc_hash == NULL) {
            perror("Could not open output file"); exit(1);
		}
	StringHash.print_hash_table(tmc_hash);
		fclose(tmc_hash);
}

	if (dump_file)
	TmcSymbolTable.PrintDependencieTable(dump_file);

	if (Compiler.bUseDumpFile) fclose(dump_file);

	if (Compiler.pass2only==true && Compiler.C_output)
	{
		TmcSymbolTable.PrintCommonHeader(stdhead_file_name);
		TmcSymbolTable.PrintGlobalsDefs(globalhead_file_name,globalc_file_name);
	}

	//if (Compiler.costn==false)
	//	{
	//		fprintf(stderr,"***** cant find map, BAD TMC installation, please reinstall\n");
	//		haha();
	//		exit(-1000);
	//	}

perf_latch_time(2);
Compiler.PrintSummary();
//fprintf(stderr,"========== TMCCO LSP CONVERSION DONE: %d succeeded, %d failed, %d processed, times=%f,%f,%f,%f ==========\n",
//		Compiler.nProcessed-Compiler.nFailed,Compiler.nFailed,Compiler.nProcessed,
//		perf_get_timediff(0,2),perf_get_timediff(0,1),perf_get_timediff(1,2),perf_get_timeaccum(0));
//	if (Compiler.bUseDumpFile) fprintf(dump_file,"========== TMCCO LSP CONVERSION DONE: %d succeeded, %d failed, %d processed ==========\n",
//		Compiler.nProcessed-Compiler.nFailed,Compiler.nFailed,Compiler.nProcessed);

    return error_level;
}


//////////////////////////////






//////////////////////
