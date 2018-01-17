// File: tmc_sym_table.h
/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/

// symbols dictionary and files list
#ifndef tmc_sym_Table_h_
#define tmc_sym_Table_h_

#include <stack>
#include <list>
#include "tmc_string_hash.h"
//#include "tmcpar.h"

// Variable attributes
#define VAR_ATTR_DEFAULT			0x0000
#define VAR_ATTR_FORMAL_PARAMETER	0x0001
#define VAR_ATTR_GLOBAL_VAR			0x0002



// some global utilities
extern std::string get_func_name_only(std::string s);

//!	Project file list and parsing order management
extern class CTmcFileList TmcFileList;
class symbol_table;
extern class symbol_table TmcSymbolTable;

class CTmcFileList
{
private:
	std::list<std::string>  FileList; // file list available by PATH
	std::stack<std::string> FileStack; // file stack to be parsed at PASS1
	std::list<std::string>  FinalList; // final file list to parsed at PASS2
	std::list<std::string>::iterator itFinalList;
public:
	std::string InitIterateFinalList()
	{
		itFinalList =  FinalList.begin();
		if (itFinalList != FinalList.end())
		{
			std::string str = *itFinalList;
			itFinalList++;
			return str;
		}
		else
			return "";
	}
	std::string NextIterateFinalList()
	{	
		if (itFinalList != FinalList.end())
		{
			std::string str = *itFinalList;
			itFinalList++;
			return str;
		}
		else
			return "";
	}
	void AppendFinalList(std::string fn)
	{
		FinalList.push_back(fn);
	}
	void LoadFinalList(char* file_name,symbol_table *pSymTable);// load files list and also register all its functions as unparsed.
	void LoadFileList(char* file_name,symbol_table *pSymTable);
	void PushFileStack(std::string fn)
	{
		FileStack.push(fn);
	}
	bool IsFileStackEmpty()
	{
		return FileStack.empty();
	}
	std::string PopFileStack()
	{
		std::string retval=FileStack.top();
		FileStack.pop();
		return retval;
	}
};
////////////////////////////////////////////////

class symbol_table
{
public:
    typedef int scope_id;
	class symbol_record
	{
	public:
		struct modifier
		{
			int  m_is_var;
			int	 m_indFunc; //!< the local variable belongs to function with indFunc
			int  m_found;
			int  m_global;
			int  m_extern_func_parsed;// function to be parsed.
			int  m_formal_parameter;
			int  m_in_stack;
			int  m_is_initialized;
			char m_sym_type; //description: 'i','m','x'
			bool m_is_assigned;
			bool m_is_referenced;// for .log info only
		};
	modifier m_modifier;
	short in_args;
	short out_args;
	
	private:
		std::string m_name;
		std::string m_src_file_name;
	public:
		symbol_record()
		{m_modifier.m_is_var=0;m_modifier.m_found=0;
		 m_modifier.m_global=0;m_modifier.m_extern_func_parsed=0;m_modifier.m_formal_parameter=0;
		 in_args=-1;out_args=-1;m_modifier.m_in_stack=0;m_modifier.m_is_initialized=0;m_modifier.m_is_assigned=false;
			m_modifier.m_sym_type='\0';m_modifier.m_is_referenced=false;
		};
		void set_name(std::string x) {m_name=x;};
		std::string& name() {return m_name;};
		std::string& src_file_name() {return m_src_file_name;};
		void set_src_file_name(std::string x) {m_src_file_name=x;};
		void mark_referenced() { m_modifier.m_is_referenced=true;};
		bool is_refernced() { return m_modifier.m_is_referenced; };
		bool is_global_variable()
		{	if (m_modifier.m_is_var ==1 && m_modifier.m_global==1)
				return true;
			else
				return false;
		}
		bool is_local_var(int indFunc) {
			if  ((m_modifier.m_indFunc==indFunc) &&
				(m_modifier.m_is_var==1) &&
				(m_modifier.m_global==0) &&
				(m_modifier.m_formal_parameter==0))
				return true;
			else
					return false;
		}
		bool is_enlisted(std::list<std::string> L)
		{
			for (std::list<std::string>::iterator itStr=L.begin();itStr!=L.end();itStr++)
			{
				if (name().compare(*itStr)==0)
					return true;
			}
			return false;
		}
		void enlist(std::list<std::string>& L)
		{
			L.push_back(name());
		}
	};
private:
	CStringHash hashtab; // hash helper
	void append_symbol(symbol_record *sr);
public:
	void print_hashtab(FILE *fp) {hashtab.print_hash_table(fp);};

public:
	std::list<symbol_record> SymList; // list of all symbols
	typedef std::list<symbol_record>::iterator record_iterator;
	record_iterator nil() {return SymList.end();};// nothing

 record_iterator  find_symbol(std::string x,bool caseinsencitive,int indFunc);
//! Insert a new name in the table. If it is a function, push its path in file list
  symbol_record& insert_name (const std::string& name,class CTmcFileList *pTmcFileList);
 
  /**
		\brief Called at RTL generation for function node. Checks output parameters.
  */
  bool is_assigned_param(std::string var_name)
  {// return if the variable occures in lhs of any assignment (and thus must be stored)
   //m_is_assigned flag is set at the tree construction.
	//	return true; // HAZARD: must return true if var is assigned.

	record_iterator p =find_symbol(var_name,false,Compiler.indFunc_RTL);
	if (p!=nil())
	{
		if (p->m_modifier.m_is_var && p->m_modifier.m_is_assigned)
		{
				return true;
		}
	}
		return false; 

  }
  /**
  *    \brief Called at RTL generation for IDENT
  */
  bool is_initialized_var(std::string var_name)
  {
	record_iterator p =find_symbol(var_name,false,Compiler.indFunc_RTL);
	if (p!=nil())
	{
		if (p->m_modifier.m_is_var && p->m_modifier.m_is_initialized)
		{
				return true;
		}
	}
		return false; 
  }
  /**
  *	\brief Called at RTL generation:
		1. IDENT
		2. Function node, output parameters
		3. FOR iteration variable
  */
  bool mark_initialized_var(std::string var_name)
  {
	record_iterator p =find_symbol(var_name,false,Compiler.indFunc_RTL);
	if (p!=nil())
	{
		if (p->m_modifier.m_is_var )
		{
			p->m_modifier.m_is_initialized=	1;
			return true;
		}
		else
		{
			return false; // error: may not initialize a function
		}
	}
	return true; // not found - Ok
  }
  /**
	\brief Called in parser
		a. FOR
		b. Assignment
		c. L_pars  
  */
 void mark_assigned_var(std::string var_name)
  {
	record_iterator p =find_symbol(var_name,false,Compiler.indFunc);
	if (p!=nil())
	{
		if (p->m_modifier.m_is_var )
		{
			p->m_modifier.m_is_assigned=true;
		}
	}
  }
/**
	\brief remove all local variables. Called before a file parsing
*/
  void erase_local_variables ()
  {
		for (record_iterator p=SymList.begin();p!=SymList.end(); )
		{
			if ((p->m_modifier.m_is_var==1) && (p->m_modifier.m_global==0))
			{
				SymList.erase(p);
				p=SymList.begin();
			}
			else
				p++;
		}
		Compiler.indFunc = 0;//! < reset the local functions enumeration
  };

/**
	\brief	Called from
	1.	Parser to mark variables that are globals and formal parameters
	2.	RTL code generator for function node , process output parameters 
*/
  void force_variable(const std::string name,int VarArrr,int indFunc)
  {
	symbol_record *sr;
	record_iterator p =find_symbol(name,false,indFunc);
	if (p==nil())
	{
  		sr = new symbol_record;
		sr->set_name(name);
		sr->m_modifier.m_is_var=1;
		sr->m_modifier.m_global=(VarArrr & VAR_ATTR_GLOBAL_VAR ? 1:0);
		sr->m_modifier.m_formal_parameter=(VarArrr & VAR_ATTR_FORMAL_PARAMETER ? 1:0);
		if (sr->m_modifier.m_global)
			sr->m_modifier.m_is_initialized=1;
		sr->m_modifier.m_indFunc = Compiler.indFunc; //!< store local function index to separate local variables per local functions
		append_symbol(sr);

	}
	else
	{
		p->m_modifier.m_is_var=1;
		p->m_modifier.m_global=(VarArrr & VAR_ATTR_GLOBAL_VAR ? 1:0);
		p->m_modifier.m_formal_parameter=(VarArrr & VAR_ATTR_FORMAL_PARAMETER ? 1:0);
		if (p->m_modifier.m_global)
			p->m_modifier.m_is_initialized=1;
	}
  };
  /**
		\brief Called in parser for function parameters creation
				mark var as a formal parameter
  */
  void mark_formal(const std::string name)
  {
			force_variable(name,VAR_ATTR_FORMAL_PARAMETER,Compiler.indFunc);
  }
  /**
		Called in parser for global declaration creation.
		Mark variable as a global
  */
  void mark_global(const std::string name)
  {
			force_variable(name,VAR_ATTR_GLOBAL_VAR,Compiler.indFunc);
  }

  /**
		\brief	Add new function to symbol table
         called at:
		 1. final function header parsing
		 2. loading file list
		 3. loading sym-file
  */

  void register_fnc_name(const std::string name,int in_args,int out_args,const std::string src_file_name="",bool bNameOnly=false)
  {
	symbol_record *sr;
	record_iterator p =find_symbol(name,false,-1);//!< search for a function
	if (p==nil())
	{
  		sr = new symbol_record;
		sr->set_name(name);
		sr->m_modifier.m_is_var=0;
		sr->m_modifier.m_global=1;
		sr->in_args=in_args;
		sr->out_args=out_args;
		sr->set_src_file_name(src_file_name);
		if(bNameOnly)
			sr->m_modifier.m_extern_func_parsed=0;// to be parsed if used
		else
			sr->m_modifier.m_extern_func_parsed=1;// just parsed

		append_symbol(sr);//!< add function name

	}
	else
	{
		p->m_modifier.m_is_var=0;
		p->in_args=in_args;
		p->out_args=out_args;
		p->m_modifier.m_global=1;
		if(bNameOnly)
			p->m_modifier.m_extern_func_parsed=0;// to be parsed if used
		else
			p->m_modifier.m_extern_func_parsed=1;// just parsed
	}
  };
/** 
*	\brief Is called for RTL generation of IDENT
*/
  bool is_variable (const std::string& name)
  {
	symbol_record sr;
	record_iterator p =find_symbol(name,false,Compiler.indFunc_RTL);
	if (p==nil())
	{
		 return false; // not found
	}
	sr=*p;
	if (sr.m_modifier.m_is_var)
		return true;
	else
		return false;

  }
  /**
		Should be called at RTL generation stage for IDENT 
  */
 //bool is_formal_par (const std::string& name,int indFunc)
 // {
//	symbol_record sr;
//	record_iterator p =find_symbol(name,false,indFunc);
//	if (p==nil())
//	{
//		return false; // not found
//	}
//	sr=*p;
//	if (sr.m_modifier.m_is_var && sr.m_modifier.m_global==0 && sr.m_modifier.m_formal_parameter)
//	{
//		return true;
//	}
//	else
//		return false;
//
 // }

 /**
			\brief Find a function with its number or RHS and LHS parameters
			Called from:
				1.	Identifier RTL generator (fucntion without argument call)
				2.	Index expression RTL generator (function call)
 */
  bool get_func_pars_num(std::string name,int *nNumFuncArgIn,int *nNumFuncArgOut)
  {
	// HAZARD: function name is defined by the filename but searched here case-insensitive!!!
    // If a name is requeted by this function it is marked as referenced.
	record_iterator p =find_symbol(name,true,-1);//! search for a function at RTL generation
	if (p==nil())
	{
		return false; // not found
	}
	if (p->m_modifier.m_is_var)
		return false;//not function
	p->mark_referenced();
	*nNumFuncArgIn = p->in_args;
	*nNumFuncArgOut = p->out_args;
	return true;
  }
   int  PrintSymTable(std::string filename);
   int  PrintDependencieTable(FILE *fp);

   int  PrintGlobalsDefs(std::string h_filename,std::string c_filename);
   int  PrintGlobalsDefsAsm(std::string inc_filename);
   int  PrintCommonHeader(std::string filename);
};


#endif
