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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#ifndef LINUX_GPL
#include <io.h>
#endif


#include <string>
#include <stack>
#include <list>

#include "tmcpar_tree.h"
#include "tmcpar_env.h"
#include "tmcpar_utils.h"


int CompileMode_prep_lsp()
{
		std::string m_file_name;
		std::string lsp_file_name;
perf_latch_time(0);


 	create_filelist(IncInputDirList,IncInputFileList,filelist_file_name,BIT_FILE_TYPE_M);

	//? ? TmcFileList.LoadFinalList(filelist_file_name,&TmcSymbolTable); // load filelist.txt
	TmcFileList.LoadFileList(filelist_file_name,&TmcSymbolTable); // load filelist.txt
	TmcFileList.PushFileStack(input_file_name);

	// load built-in functions list: <name, in_args,out_args>
	// for function with variable number of inputs: in_args<0
	//Load_FncNames(buildin_fnc_file_name);
	//Load_FncNames(external_fnc_file_name);

	//if (strlen(buildin_fnc_file_name)>0)
		Load_FncNames(buildin_fnc_file_name);
	/*else
	{// load only some in-builds
	// these functions are used in with command syntax and if not defined - parser fails
	//e.g: symbol_table::register_fnc_name("hold",1,0);
	}*/

	if (Compiler.gen_for_all_list)
		TmcFileList.LoadFinalList(filelist_file_name,&TmcSymbolTable); // load filelist.txt

	Compiler.nFailed=0;Compiler.nProcessed=0;

perf_latch_time(1);

	while (TmcFileList.IsFileStackEmpty()==false)
	{
		std::string fn=TmcFileList.PopFileStack();
		symbol_table::record_iterator p =TmcSymbolTable.find_symbol(fn,false,-1);//! search for a function
		if (p!=TmcSymbolTable.nil())
		{
			p->m_modifier.m_in_stack=0;
		}
		
		m_file_name = fn;//root_dir_name;
		tmc_in = fopen(m_file_name.c_str(), "rt");
		
        if (tmc_in == NULL) {
            perror("Could not open input file"); exit(1);
		}

		if (Compiler.lsp_output)
		{
			lsp_file_name = output_dir_name;
			//lsp_file_name.append(extract_file_name(fn)).append(".lsp");
			lsp_file_name.append(change_file_ext(extract_file_name(fn),"lsp"));

			lsp_file = fopen(lsp_file_name.c_str(), "w");
			if (lsp_file == NULL) {
				perror("Could not open lsp output file"); exit(1);
			}
		}


		if (Compiler.bUseDumpFile) fprintf(dump_file,"\n------------- PASS1 BEGIN FILE: %s-----------\n ",fn.c_str());
		reset_parser();
		curr_fcn_file_full_name=fn;
		try
		{
		Compiler.nProcessed++;

		fprintf(stderr,"%s\n ",fn.c_str());
		tmc_parse();// call yyparse(), add symbols to the symbol table and filenames to FileStack 
		if(Compiler.lsp_output)
				print_tmcpar_tree(tmcpar_parsing_module);
		//fprintf(stderr,"\n pass1 FILE: %s done\n ",fn.c_str());
		Compiler.FinalizeFileErrLog();
		}
		catch(...)
		{
		Compiler.nFailed++;// panic
		if (lsp_file)
					{
						lsp_file = freopen(lsp_file_name.c_str(),"w",lsp_file);
					}

		if (Compiler.bUseDumpFile) fprintf(dump_file,"\n**** Errors in FILE (%d): %s-----------\n ",tmcpar_lineno,fn.c_str());
		fprintf(stderr,"\n**** Errors in FILE (%d): %s-----------\n ",tmcpar_lineno,fn.c_str());
		}
		fclose(tmc_in);
		tmc_in=NULL;
		if (lsp_file) fclose(lsp_file);
		lsp_file=NULL;

		if (Compiler.bUseDumpFile) fprintf(dump_file,"\n------------- PASS1 END FILE: %s-----------\n ",fn.c_str());
		TmcFileList.AppendFinalList(fn);
		TmcSymbolTable.erase_local_variables();
	}


	//if (Compiler.costn==false)
	//	{
	//		fprintf(stderr,"***** cant find map, BAD TMC installation, please reinstall\n");
	//		haha();
	//		exit(-1000);
	//	}


	TmcSymbolTable.PrintSymTable(symtable_file_name);
perf_latch_time(2);
Compiler.PrintSummary();
//	fprintf(stderr,"========== TMCPAR LSP GENERATION DONE: %d succeeded, %d failed, %d processed, times=%f,%f,%f,%f  ==========\n",
//		Compiler.nProcessed-Compiler.nFailed,Compiler.nFailed,Compiler.nProcessed,
//		perf_get_timediff(0,2),perf_get_timediff(0,1),perf_get_timediff(1,2),perf_get_timeaccum(0));
//	if (Compiler.bUseDumpFile) fprintf(dump_file,"========== TMCPAR LSP GENERATION DONE: %d succeeded, %d failed, %d processed ==========\n",
//		Compiler.nProcessed-Compiler.nFailed,Compiler.nFailed,Compiler.nProcessed);

	if (Compiler.bUseDumpFile) fclose(dump_file);

	
	
	return error_level;
}


