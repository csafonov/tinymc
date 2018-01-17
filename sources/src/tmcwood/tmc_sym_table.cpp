/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "tmcpar_env.h"
#include "tmc_sym_table.h"

CTmcFileList TmcFileList;
symbol_table TmcSymbolTable;

CStringHash StringHash;



void  CTmcFileList::LoadFinalList(char* file_name,symbol_table *pSymTable)
	// load files list and also register all its functions as unparsed.
	{
		char buff[PATH_MAX+2];
		FILE *filelist_file;

	// loads filelist from filelist_file
        //int err=fopen_s(&filelist_file,file_name, "r");
		filelist_file=fopen(file_name, "r");
        if (filelist_file == NULL) {
            perror("Could not open the filelist file"); exit(1);
        }
		while (fgets(buff,sizeof(buff)-1,filelist_file))
		{
			if(buff[0]!=0)
			{
				int len=strlen(buff);
				for (short kk=len-1;kk>=0;kk--)
				{
					if ( (buff[kk]==' ') || (buff[kk]==10 ))
					{
						buff[kk]=0;
					}
					else
					{
						break;
					}
				}
				len=strlen(buff);

				if(buff[len-1]==10)
				{
					buff[len-1]=0;
				}
				FileList.push_back(buff);

				if(Compiler.gen_for_all_list==true)
				{
				PushFileStack(buff);
				}

				std::string fn=get_func_name_only(buff);
				if(Compiler.gen_for_all_list==false)
				{
					symbol_table::record_iterator p =pSymTable->find_symbol(fn,false,-1);//load function list
					if (p!=pSymTable->nil())
					{
						if (p->m_modifier.m_extern_func_parsed==1 )
						{
							AppendFinalList(buff);
						}
					}
				}
				//else
				//{
				//		AppendFinalList(buff);
				//}

			}
		}
		fclose(filelist_file);
	}
void CTmcFileList::LoadFileList(char* file_name,symbol_table *pSymTable)
	// load files list and also register all its functions as unparsed.
	{
		char buff[PATH_MAX+2];
		FILE *filelist_file;

	// loads filelist from filelist_file
        //int err=fopen_s(&filelist_file,file_name, "r");
		filelist_file=fopen(file_name, "r");
        if (filelist_file == NULL) {
            perror("Could not open the filelist file"); exit(1);
        }
		while (fgets(buff,sizeof(buff)-1,filelist_file))
		{
			if(buff[0]!=0)
			{
				int len=strlen(buff);
				for (short kk=len-1;kk>=0;kk--)
				{
					if ( (buff[kk]==' ') || (buff[kk]==10 ))
					{
						buff[kk]=0;
					}
					else
					{
						break;
					}
				}
				len=strlen(buff);

				if(buff[len-1]==10)
				{
					buff[len-1]=0;
				}
			FileList.push_back(buff);
			}
			std::string fn=get_func_name_only(buff);
			pSymTable->register_fnc_name(fn,-1,-1,buff,true);

		}
		fclose(filelist_file);
	}
/////////////////////////////////////////////////////////////////

/**
			\brief Find symbol: function name or variable of given scope.
			May be called at any of the stages:
			1. Parser. Scope is defined by Compiler.indFunc
			2. RTL generator. ? ? ?
			3. Code output. Scope is stored in InstrList
*/
symbol_table::record_iterator  symbol_table::find_symbol(std::string x,bool caseinsencitive,int indFunc)
{
	perf_latch_time(3);
	if (caseinsencitive==false) 
	{
	 for (record_iterator p=SymList.begin();p!=SymList.end();p++)
	 {
		if (p->name().compare(x)==0  && 
				( (p->m_modifier.m_is_var==0) || //!< a function
				(p->m_modifier.m_indFunc ==  indFunc) )  ) //! or a variable of the given scope

		{
			perf_latch_time(4);perf_do_timeaccum(0,3,4);

			return p;
		}
	 }
	}
	else
	{ // with this option search only for functions
	 for (record_iterator p=SymList.begin();p!=SymList.end();p++)
	 {
		if (_stricmp(p->name().c_str(),x.c_str() )==0 /* &&
			( (p->m_modifier.m_is_var==0) || //!< a function
				(p->m_modifier.m_indFunc == indFunc) ) */ ) //! or a variable of the given scope
		{
			perf_latch_time(4);perf_do_timeaccum(0,3,4);
			return p;
		}
	 }
	}
	perf_latch_time(4);perf_do_timeaccum(0,3,4);
	return SymList.end();
}
/**
		\brief	Register a symbol (function or variable) in the symbol table.
		Called from parser only (create_identifier).
*/
  symbol_table::symbol_record& symbol_table::insert_name (const std::string& name,class CTmcFileList *pTmcFileList)
  {
    bool is_new_var;
  	symbol_record *sr;
	record_iterator p =find_symbol(name,false,Compiler.indFunc);
	if (p==nil())
	{
		// HAZARD: try find case-insensitive function
		//HAZARD_VANDAL: we have a problem with I that is replaced by i. May be is not possible for in-built functions: p =find_symbol(name,true);
		p =find_symbol(name,false,Compiler.indFunc);//HAZARD_VANDAL
		if (p==nil())
	    {
			is_new_var=true;
		}
		else
		{
		// if found variable - ignore, this is another variable.
		if (p->m_modifier.m_is_var==0)
			is_new_var=false;
		else
			is_new_var=true;
		}
	}
	else
	{
		is_new_var=false;
	}

	if (is_new_var==true)
	{
		// if not found - this is a variable
		sr = new symbol_record;
	    sr->set_name(name);
		sr->m_modifier.m_is_var=1;// is the symbol is not already included from PATH
		sr->m_modifier.m_global=0;
		sr->m_modifier.m_indFunc = Compiler.indFunc; //!< store local function index to separate local variables per local functions
	    append_symbol(sr);
		return *sr;
	}
	else
	{
		// if the symbol is found as a function PATH, then put the src file name into stack.
		if (p->m_modifier.m_extern_func_parsed==0 && p->m_modifier.m_is_var==0)
		{
			if(p->m_modifier.m_in_stack==0)
			{
				pTmcFileList->PushFileStack(p->src_file_name());
				p->m_modifier.m_in_stack=1;
			}
		}

	}
	sr = new symbol_record;
	*sr =*p;
	return *sr;
  }

int  symbol_table::PrintSymTable(std::string filename)
	{
		FILE *fp = fopen(filename.c_str(),"w");
		//errno_t err=fopen_s(&fp,filename.c_str(),"w");
		if (fp==NULL)
		{
			return -1;
		}
		for (record_iterator p=SymList.begin();p!=SymList.end();p++)
		{
			if (p->m_modifier.m_is_var ==0 && p->m_modifier.m_extern_func_parsed==1)
			{
				fprintf(fp,"%s,%d,%d,%c;\n",p->name().c_str(),p->in_args,p->out_args,'m');
			}
		}
		fclose(fp);
	return 0;
	}

int  symbol_table::PrintDependencieTable(FILE *fp)
	{
		fprintf(fp,"\nDEPENDENCIES:\n");
		for (record_iterator p=SymList.begin();p!=SymList.end();p++)
		{
			if (p->m_modifier.m_is_var ==0 &&  p->is_refernced())
			{
				fprintf(fp,"%s,%d,%d,%c;\n",p->name().c_str(),p->in_args,p->out_args,'m');
			}
		}
		fprintf(fp,"\nEND DEPENDENCIES ****************\n");
		fprintf(fp,"\nLOCALS:\n");
		print_hashtab(fp);
		fprintf(fp,"\nEND LOCALS ****************\n");

	return 0;
	}

void symbol_table::append_symbol(symbol_table::symbol_record *sr)
{//HSKOST_TODO
	SymList.push_back(*sr);
	record_iterator p = SymList.end();
	hashtab.sym_hash_insert(sr->name().c_str(),(void*)&p);
	// store pointer to added record into the  
};
