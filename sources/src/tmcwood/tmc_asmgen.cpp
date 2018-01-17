/// File: tmc_asmgen.cpp
/// Purpose: x86 assembler code generator
/// The code contains also pre-defined opcodes for x86 for tmcbuilder
/// Actually this code is only a demonstration for generation of assembler code and building simple PE without linker and C compiler.
/// It became obsolete due to x64 introduction and very unlikely to be ported to x64.

/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#ifndef LINUX_GPL
#include <io.h>
#endif

#include <cctype>
#include <cstring>

#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <stack>
#include <list>

#include "tmcpar_env.h"

#include "tmc_sym_table.h"
#include "tmcpar_tree.h"

#include "tmc_string_hash.h"
#include "tmc_asmgen.h"
CAsmSymTable	AsmSymTable;
CAsmGenIntel	asmgenintel;

extern FILE *code_file;

/*
; 53   : tmcroots(1,1, reg[35], p);

  00290	8b 45 d4			mov	 eax, DWORD PTR _p$[ebp]
  00293	50					push	 eax
  00294	8b 4d e0			mov	 ecx, DWORD PTR _reg$[ebp]
  00297	8b 91 8c 00 00 00	mov	 edx, DWORD PTR [ecx+140]
  0029d	52					push	 edx
  0029e	6a 01				push	 1
  002a0	6a 01				push	 1
  002a2	e8 00 00 00 00		call	 _tmcroots
  002a7	83 c4 10			add	 esp, 16			; 00000010H
*/

std::string asm_save_call(std::string fn,CIReg fname,long nipars,std::stack<CAsmStrRec> arr_args_names)
{// like: tmcsave(0,nipars,filename_reg[],var1,"var1",... )
	std::string retval="";
    int cnt=0;
    CAsmStrRec s;

	while (! arr_args_names.empty())
	{
		s =   arr_args_names.top();
			  arr_args_names.pop();

		retval.append(asmgenintel.asm_gen_push_str(s.str_ord));
		retval.append(asmgenintel.asm_gen_push_var_s(s.strtext));

		cnt++;
	}
	retval.append(asmgenintel.asm_gen_push_var(fname));
	retval.append(asmgenintel.asm_gen_push_long(nipars));
	retval.append(asmgenintel.asm_gen_push_long(0));

		retval.append(asmgenintel.asm_gen_call(std::string("_tmc").append(fn).c_str(),cnt*ASM_PCHAR_SIZE +cnt*ASM_PTR_TMCMATRIX_SIZE + 2*ASM_LONG_SIZE +ASM_PTR_TMCMATRIX_SIZE));
		return retval;
}

std::string asm_tmcfunc_call(std::string fn,long nargout,long nargin,long max_arout,long max_argin,
							std::stack<CIReg> arr_args_out,std::stack<CIReg> arr_args_in)
{
// like: tmcroots(nargout,nargin,arr_args_out, arr_args_in)
	std::string retval="";
int cnt;
CIReg r_;
int len_args_out=arr_args_out.size();
// tmcfunction(nargout,nargin,args_out,..,args_in,..)
	for (cnt=0;cnt<(max_argin-nargin);cnt++)
	{
		retval.append(asmgenintel.asm_gen_push_long(0));
	}
	for (cnt=0;cnt<nargin ;cnt++) // additional protection
	{
		if (arr_args_in.empty()==false)
		{
		r_ = arr_args_in.top();
			 arr_args_in.pop();
		retval.append(asmgenintel.asm_gen_push_var(r_));
		}
		else
		{
			// here is ERROR
			Compiler.LogWarn(8, "invalid call",fn, 1);
		}
	}

	// append register for not used parameters in order to avoid NULLs.
	for (cnt=0;cnt<(max_arout-len_args_out);cnt++)
	{
		retval.append(asmgenintel.asm_gen_push_long(0));
	}
	for (cnt=0;cnt<len_args_out;cnt++)
	{
		r_ = arr_args_out.top();
			  arr_args_out.pop();
		retval.append(asmgenintel.asm_gen_push_var(r_));
	}


		retval.append(asmgenintel.asm_gen_push_long(nargin));
		retval.append(asmgenintel.asm_gen_push_long(nargout));
		
		retval.append(asmgenintel.asm_gen_call(std::string("_tmc").append(fn).c_str(),(max_argin+max_arout)*ASM_PTR_TMCMATRIX_SIZE + 2*ASM_LONG_SIZE ));

		return retval;
}
std::string asm_tmcoper_call(std::string fn,long nipars,std::stack<CIReg> arr_args_out,std::stack<CIReg> arr_args_in)
{// like: tmcCollectColumns(arr_args_out,nipars,arr_args_in )
	std::string retval="";
    int cnt=0;
    CIReg r_;

	while (! arr_args_in.empty())
	{
		r_ = arr_args_in.top();
			  arr_args_in.pop();
		retval.append(asmgenintel.asm_gen_push_var(r_));
		cnt++;
	}
	retval.append(asmgenintel.asm_gen_push_long(nipars));

	while (! arr_args_out.empty())
	{
		r_ = arr_args_out.top();
			  arr_args_out.pop();
		retval.append(asmgenintel.asm_gen_push_var(r_));
		cnt++;
	}
		retval.append(asmgenintel.asm_gen_call(std::string("_").append(fn).c_str(),cnt*ASM_PTR_TMCMATRIX_SIZE + 1*ASM_LONG_SIZE ));
		return retval;
}




std::string asm_call_fnc_r(const char *fn,CIReg r1)
{// like: tmcNeg(r1,r2)
	std::string retval="";
	retval.append(asmgenintel.asm_gen_push_var(r1));
	retval.append(asmgenintel.asm_gen_call(fn,1*ASM_PTR_TMCMATRIX_SIZE));
return retval;
}
std::string asm_call_fnc_rr(const char *fn,CIReg r1,CIReg r2)
{// like: tmcNeg(r1,r2)
	std::string retval="";
	retval.append(asmgenintel.asm_gen_push_var(r2)).append(asmgenintel.asm_gen_push_var(r1));
	retval.append(asmgenintel.asm_gen_call(fn,2*ASM_PTR_TMCMATRIX_SIZE));
return retval;
}
std::string asm_call_fnc_rrn(const char *fn,CIReg r1,CIReg r2,long n1)
{// like: tmcIsFieldHcode(r1,r2,n1)
	std::string retval="";
	retval.append(asmgenintel.asm_gen_push_long(n1));
	retval.append(asmgenintel.asm_gen_push_var(r2)).append(asmgenintel.asm_gen_push_var(r1));
	retval.append(asmgenintel.asm_gen_call(fn,2*ASM_PTR_TMCMATRIX_SIZE+ASM_LONG_SIZE));
return retval;
}
std::string asm_call_fnc_rrnn(const char *fn,CIReg r1,CIReg r2,long n1,long n2)
{// like: tmcGetEnd(r1,r2,n1,n2)
	std::string retval="";
	retval.append(asmgenintel.asm_gen_push_long(n2)).append(asmgenintel.asm_gen_push_long(n1));
	retval.append(asmgenintel.asm_gen_push_var(r2)).append(asmgenintel.asm_gen_push_var(r1));
	retval.append(asmgenintel.asm_gen_call(fn,2*ASM_PTR_TMCMATRIX_SIZE+ASM_LONG_SIZE));
return retval;
}
std::string asm_call_fnc_rrr(const char *fn,CIReg r1,CIReg r2,CIReg r3)
{// like: tmcAdd(r1,r2,r3)
	std::string retval="";
	retval.append(asmgenintel.asm_gen_push_var(r3)).
		append(asmgenintel.asm_gen_push_var(r2)).append(asmgenintel.asm_gen_push_var(r1));
	retval.append(asmgenintel.asm_gen_call(fn,3*ASM_PTR_TMCMATRIX_SIZE));
return retval;
}
std::string asm_call_fnc_rrrr(const char *fn,CIReg r1,CIReg r2,CIReg r3,CIReg r4)
{// like: tmcCreateColonBaseIncLimit(r1,r2,r3,r4)
	std::string retval="";

	retval.append(asmgenintel.asm_gen_push_var(r4)).append(asmgenintel.asm_gen_push_var(r3)).
		append(asmgenintel.asm_gen_push_var(r2)).append(asmgenintel.asm_gen_push_var(r1));
	retval.append(asmgenintel.asm_gen_call(fn,4*ASM_PTR_TMCMATRIX_SIZE));
return retval;
}
std::string asm_call_fnc_vv(const char *fn,std::string v1,std::string v2)
{// like: tmcCopyMat(v1,v2)
	std::string retval="";
	retval.append(asmgenintel.asm_gen_push_var_s(v2)).append(asmgenintel.asm_gen_push_var_s(v1));
	retval.append(asmgenintel.asm_gen_call(fn,2*ASM_PTR_TMCMATRIX_SIZE));
return retval;
}
std::string asm_call_fnc_rvnn(const char *fn,CIReg r1,std::string v1,long n1,long n2)
{// like: tmcGetEnd(r1,v1,n1,n2)
	std::string retval="";
	retval.append(asmgenintel.asm_gen_push_long(n2)).append(asmgenintel.asm_gen_push_long(n1)).
		append(asmgenintel.asm_gen_push_var_s(v1)).append(asmgenintel.asm_gen_push_var(r1));
	retval.append(asmgenintel.asm_gen_call(fn,2*ASM_PTR_TMCMATRIX_SIZE+2*ASM_LONG_SIZE));
return retval;
}
std::string asm_call_fnc_rrv(const char *fn,CIReg r1,CIReg r2,std::string v1)
{// like: tmcForIterInit(r1,r2,v1)
	std::string retval="";
	retval.append(asmgenintel.asm_gen_push_var_s(v1)).
		append(asmgenintel.asm_gen_push_var(r2)).append(asmgenintel.asm_gen_push_var(r1));
	retval.append(asmgenintel.asm_gen_call(fn,3*ASM_PTR_TMCMATRIX_SIZE));
return retval;
}

std::string CInstr::gen_asmcode(CInstrList *ilist)
	// create an instruction code for printing
	{
		char buff[200];
		int na;// number of printed arguments. used to include newline.

		std::string retval="";
		CIReg r1,r2,r3;
		std::list<CIReg>::iterator p=ipars.begin();
		r1=0;r2=0;r3=0;
		if(nipars>0)
			r1=*p++;// first parameter of the binary operation
		if(nipars>1)
			r2=*p++;// second parameter of the binary operation
		if(nipars>2)
			r3=*p;// limit of colon


		switch(m_inst_type)
		{
		case instr_func_declaration:// function declaration begin
			{
			AsmSymTable.clear(); 
			AsmSymTable.addvar(1,"nargout");
			AsmSymTable.addvar(2,"nargin");
/* E.g.:
[ztmc,y]=testM(a,b)

void tmctestM(int nargout, int nargin,tmsMatrix *ztmc,tmsMatrix *y
,tmsMatrix *a,tmsMatrix *b) {
*/
			short varcnt=2;
				for ( std::list<std::string>::iterator p=args_out.begin(); p != args_out.end(); p++)
				{
					varcnt++;
					std::string elt = *p;
					AsmSymTable.addvar(varcnt,elt.c_str());
				}
				for ( std::list<std::string>::iterator p=args_in.begin(); p != args_in.end(); p++)
				{
					varcnt++;
					std::string elt = *p;
					AsmSymTable.addvar(varcnt,elt.c_str());
				}
			}

			retval.append(asmgenintel.asm_gen_fnc_enter(m_ident_name,max_stack_frame_size));

// HAZARD: must calculate input/output parameters frame, store names and offsets in frame
// The following only generate the C-comment:
	if (Compiler.comments_output)
	{
			sprintf(buff,"tmc%s(",m_ident_name.c_str());
			retval.append("\t;void ").append(buff);
			retval.append("int nargout, int nargin");

			for ( std::list<std::string>::iterator p=args_out.begin(); p != args_out.end(); p++)
			{
				std::string elt = *p;
				//retval.append(",tmsMatrix **").append(elt.c_str());
				//Memory management and garbage collection is realized internally.
				//Thus all parameters are passed by values only as objects.
				retval.append(",tmsMatrix *").append(elt.c_str());
			}
			retval.append("\n\t;");
			for ( std::list<std::string>::iterator p=args_in.begin(); p != args_in.end(); p++)
			{
				std::string elt = *p;
				retval.append(",tmsMatrix *").append(elt.c_str());
			}

			retval.append("\t;) {");
	}
			break;

		case instr_fnc_end:
		// here can add strings and other constants after ret
			retval.append(asmgenintel.asm_gen_fnc_leave(m_ident_name,max_stack_frame_size));
			retval.append(asmgenintel.asm_gen_strpool());
			break;

		case instr_funct_call:
			{
				// void tmcsomefunction(long nout,long ninput,tmsMatrix *matres,tmsMatrix *x...);
				short is_spec_fnc=0;

				if (m_ident_name.compare("nargin")==0)
						is_spec_fnc=REG_NARGIN;
				else if (m_ident_name.compare("nargout")==0)
						is_spec_fnc=REG_NARGOUT;
				// special function calls
				if (is_spec_fnc)
				{
					std::list<CIReg>::iterator po=ipars_out.begin();
					CIReg reg_out=*po;
				//#define tmcnargin(shum,klum,x)	tmcScalar(x,(double)nargin)
				retval.append(asmgenintel.asm_gen_push_var(is_spec_fnc));
				retval.append(asmgenintel.asm_gen_push_var(reg_out));
				retval.append(asmgenintel.asm_gen_call("_tmcScalar",ASM_DOUBLE_SIZE+ASM_PTR_TMCMATRIX_SIZE));
				break;
				}
		//#define tmcnargout(shum,klum,x) tmcScalar(x,(double)nargout)



				int k=0;
				int all_num_args;
				int n=0;

				std::stack<CIReg>  arr_args_in;
				std::stack<CIReg>  arr_args_out;


				//if (max_nargin>=0)
				//{
					all_num_args = max_nargout+max_nargin;// fixed number of input parameters
				//}
				//else
				//{
				//	all_num_args =max_nargout+nipars;// variable number of input parameters
				//	max_nargin = nipars;
				//}



	if (Compiler.comments_output)
	{
				retval=std::string("\t;//CALL function\n");
				std::list<CIReg>::iterator p1=ipars_out.begin();// first actual out_par
				for (k=0;k<max_nargout;k++)
				{	
					if(p1 != ipars_out.end())
					{
						CIReg reg = *p1;
						sprintf(buff,"\t;tmcReallocRegister(%s);\n",get_reg_name(reg).c_str());
						retval.append(buff);


						p1++;
					}
				}

				sprintf(buff,"\t;tmc%s(%d,%d",m_ident_name.c_str(),nipars_out,nipars);
				retval.append(buff);//retval=std::string(buff);

				if(n<all_num_args)
						retval.append(",");
	}

				std::list<CIReg>::iterator p=ipars_out.begin();// first actual out_par
				n=0;na=0;
				for (k=0;k<max_nargout;k++)
				{	
					if(p != ipars_out.end())
					{
						CIReg reg = *p;
						//retval.append("&").append(get_reg_name(reg).c_str());
					if (Compiler.comments_output)
					{
					retval.append(" ").append(get_reg_name(reg).c_str());
					}
						arr_args_out.push(reg); // for asm generator in order to get inverse order of the pars

						p++;
					} 
					else
					{
						if (Compiler.comments_output) 
							retval.append("NULL");
					}
					if (Compiler.comments_output)
					{
					if(n<all_num_args-1)
						retval.append(",");
					}
					n++;
					na++;
					if (Compiler.comments_output) 
					{
						if ((na & 7)==0)
							retval.append("\n\t;");
					}
				}
				std::list<CIReg>::iterator p2=ipars.begin();// first actual in_par
				na=0;
				for (k=0;k<max_nargin;k++)
				{
					if(p2 != ipars.end())
					{
						CIReg reg = *p2;
						if (Compiler.comments_output)
						{
							//retval.append("&").append(get_reg_name(reg).c_str());
						retval.append(" ").append(get_reg_name(reg).c_str());
						}
						arr_args_in.push(reg); // for asm generator in order to get inverse order of the pars
						p2++;
					}
					else
					{
						if (Compiler.comments_output)
							retval.append("NULL");
					}
					if (Compiler.comments_output)
					{
					if(n<all_num_args-1)
						retval.append(",");
					}
					n++;
					na++;
					if (Compiler.comments_output)
					{
					if ((na & 7)==0)
						retval.append("\n\t;");
					}
				}
				if (Compiler.comments_output)
					retval.append(");\n");
				else
					retval = "";

				// reallocate output arguments
				std::list<CIReg>::iterator p1a=ipars_out.begin();// first actual out_par
					while(p1a != ipars_out.end())
					{
						CIReg reg = *p1a;
						retval.append(asmgenintel.asm_gen_push_var(reg));
						retval.append(asmgenintel.asm_gen_call("_tmcReallocRegister",ASM_PTR_TMCMATRIX_SIZE));
						p1a++;
					}
				retval.append(asm_tmcfunc_call(m_ident_name,nipars_out,nipars,max_nargout,max_nargin,arr_args_out,arr_args_in));


			}
			break;

		case instr_save_call:
			{
			int k=0;
			int all_num_args;
			int n=0;

			std::stack<CAsmStrRec> arr_args_names;

				all_num_args =n_argin;// variable number of input parameters
				max_nargin = n_argin;

			retval=std::string(";\t//CALL function save\n");
			// the function has no outputs
			sprintf(buff,";\ttmc%s(%d,%d",m_ident_name.c_str(),0,1 + n_argin);
			retval.append(buff);//retval=std::string(buff);
			retval.append(",");
			retval.append(" ").append(get_reg_name(outreg).c_str());
			retval.append(",");

			std::list<std::string>::iterator p2=args_in.begin();// first actual in_par
			na=0;
			for (k=0;k<max_nargin;k++)
			{
				if(p2 != args_in.end())
				{
					std::string savedvarname = *p2;
					retval.append(" ").append(savedvarname.c_str());
					retval.append(", \"").append(savedvarname.c_str()).append("\"");

					p2++;

					CAsmStrRec s;
					s.strtext = savedvarname;
					s.str_ord = AsmSymTable.addstring(savedvarname);
					arr_args_names.push(s);


				}
				else
				{
					retval.append("NULL");
				}
				if(n<all_num_args-1)
					retval.append(",");
				n++;
				na++;if ((na & 7)==0)
					retval.append("\n\t;");

			}
				retval.append(");\n");

				if (!Compiler.comments_output)
				{
					retval = "";
				}
				retval.append(asm_save_call(m_ident_name,outreg,1 + n_argin,arr_args_names));

			}

			break;
		case instr_block_end:// function end
			//retval=std::string("}");
			retval=std::string("\n");
			break;
		case instr_clear_local_vars:// clear local vars at function exit
			retval="";

			// finally clear local vars
			for (symbol_table::record_iterator p=TmcSymbolTable.SymList.end();p!=TmcSymbolTable.SymList.begin(); )
			{
				p--;
				if (p->is_local_var(ilist->get_local_function_ind() ))
				{
			if (Compiler.comments_output)
			{
				 sprintf(buff,"\t;tmcFreeLocalVar(%s);\n",
			 		p->name().c_str());
				 retval.append(buff);
			}

				 retval.append(asmgenintel.asm_gen_push_var_s(p->name()));
				 retval.append(asmgenintel.asm_gen_call("_tmcFreeLocalVar",ASM_PTR_TMCMATRIX_SIZE));
				}
			}
			if (Compiler.comments_output)
			{
					sprintf(buff,"\t;tmcFreeRegFrame(reg);\n");
					retval.append(buff);
			}
				 retval.append(asmgenintel.asm_gen_push_var_s("reg"));
				 retval.append(asmgenintel.asm_gen_call("_tmcFreeRegFrame",ASM_PTR_TMCMATRIX_SIZE));

			break;
		case instr_goto: // goto
			if (Compiler.comments_output)
			{
			sprintf(buff,";\tgoto label_%d; //%s\n",igoto_label,m_comment.c_str());
			retval=std::string(buff);
			}
			retval.append(asmgenintel.asm_bf_unc(igoto_label));

			break;
		case instr_label: // no operation, only label
			if (Compiler.comments_output)
			{
			sprintf(buff,".label_%d: ; //%s",ilabel,m_comment.c_str());
			}
			else
			{
			sprintf(buff,".label_%d:",ilabel);
			}
			retval=std::string(buff);
			break;
		case instr_isfield_call:// isfield
			if (Compiler.comments_output)
			{
			sprintf(buff,"\t;tmcIsFieldHcode(%s,%s,0x%08x);/* %s */",
				get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),
				StringHash.string2hcode(m_ident_name.c_str()),m_ident_name.c_str());
			retval=std::string(buff);
			}
			retval.append(asm_call_fnc_rrn("_tmcIsFieldHcode",outreg,r1,StringHash.string2hcode(m_ident_name.c_str()))); 

			break;
		case instr_test_value:// test a register
			if (Compiler.comments_output)
			{
			sprintf(buff,";\tif(tmcIsFalse(%s)) goto label_%d; // %s\n",
				get_reg_name(r1).c_str(),igoto_label,m_comment.c_str());
			retval=std::string(buff);
			}

			retval.append(asm_call_fnc_r("_tmcIsFalse",r1));
			retval.append(asmgenintel.asm_bf_ne(igoto_label));


			break;
		case instr_test_value_t:// test a register
			if (Compiler.comments_output)
			{
			sprintf(buff,";\tif(tmcIsTrue(%s)) goto label_%d; // %s\n",
				get_reg_name(r1).c_str(),igoto_label,m_comment.c_str());
			retval=std::string(buff);
			}
			retval.append(asm_call_fnc_r("_tmcIsTrue",r1));
			retval.append(asmgenintel.asm_bf_ne(igoto_label));

			break;

		case instr_test_value_ass:// test a register
			if (Compiler.comments_output)
			{
			sprintf(buff,";\tif(tmcIsFalse(%s)) {\n;\ttmcAssignFalse(%s); goto label_%d; } // %s\n",
				get_reg_name(r1).c_str(),get_reg_name(r2).c_str(),igoto_label,m_comment.c_str());
			retval=std::string(buff);
			}
//#define tmcAssignFalse(x) tmcScalar(x,0)

			retval.append(asm_call_fnc_r("_tmcIsFalse",r1));
			retval.append(asmgenintel.asm_bf_eq(igoto_label,'a'));
//			retval.append(asm_call_fnc_r("_tmcAssignFalse",r2));
			retval.append(asmgenintel.asm_gen_push_double(0));
			retval.append(asmgenintel.asm_gen_push_var(r2));
			retval.append(asmgenintel.asm_gen_call("_tmcScalar",ASM_DOUBLE_SIZE+ASM_PTR_TMCMATRIX_SIZE));
			retval.append(asmgenintel.asm_bf_unc(igoto_label));
			retval.append(asmgenintel.asm_label(igoto_label,'a'));


			break;
		case instr_test_value_t_ass:// test a register
			if (Compiler.comments_output)
			{
			sprintf(buff,";\tif(tmcIsTrue(%s)) {\n;\ttmcAssignTrue(%s); goto label_%d;} // %s\n",
				get_reg_name(r1).c_str(),get_reg_name(r2).c_str(),igoto_label,m_comment.c_str());
			retval=std::string(buff);
			}
//#define tmcAssignTrue(x) tmcScalar(x,1)

			retval.append(asm_call_fnc_r("_tmcIsTrue",r1));
			retval.append(asmgenintel.asm_bf_eq(igoto_label,'a'));
//			retval.append(asm_call_fnc_r("_tmcAssignTrue",r2));
			retval.append(asmgenintel.asm_gen_push_double(1));
			retval.append(asmgenintel.asm_gen_push_var(r2));
			retval.append(asmgenintel.asm_gen_call("_tmcScalar",ASM_DOUBLE_SIZE+ASM_PTR_TMCMATRIX_SIZE));
			retval.append(asmgenintel.asm_bf_unc(igoto_label));
			retval.append(asmgenintel.asm_label(igoto_label,'a'));


			break;


		case instr_index_get: // get subset from matrix - get refernce info to submatix.
		case instr_index_set: // assign subset from matrix
		case instr_cellarray_index_get: // get subset from matrix - get refernce info to submatix.
		case instr_cellarray_index_set: // assign subset from matrix
			{
				std::string fn;
				std::stack<CIReg> arr_ind;
				std::stack<CIReg> arr_args;

				if(m_inst_type==instr_index_get)
					fn="tmcGetByIndex";
				else if (m_inst_type==instr_index_set)
					fn="tmcGetRefByIndex";
				else if (m_inst_type==instr_cellarray_index_get)
					fn="tmcGetByIndexCell";
				else if (m_inst_type==instr_cellarray_index_set)
					fn="tmcGetRefByIndexCell";
				else fn="x?";
			if (Compiler.comments_output)
			{
				sprintf(buff,"(%s,%s,%d",
					get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),nipars-1);
				
				retval=std::string("\t;").append(fn);
				retval.append(buff);
			}
				{
					std::list<CIReg>::iterator pIndexDim=ipars.begin();pIndexDim++;//skip addressed matrix
					for (  ; pIndexDim != ipars.end(); pIndexDim++)
					{
						CIReg elt = *pIndexDim;
						if (Compiler.comments_output)
							retval.append(",").append(get_reg_name(elt).c_str());

						arr_ind.push(elt);
					}
					if (Compiler.comments_output)
						retval.append(");\n");
				}
				arr_args.push(outreg);
				arr_args.push(r1);

				retval.append(asm_tmcoper_call(fn,nipars-1,arr_args,arr_ind)); 
			}
			break;
		//case instr_index_set: // assign subset from matrix
		//	sprintf(buff,"tmsSetByIndex(&%s,%s,%d",
		//		get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),nipars-1);
		//	retval=std::string(buff);
		//	{
		//		std::list<CIReg>::iterator pIndexDim=ipars.begin();pIndexDim++;//skip addressed matrix
		//		for (  ; pIndexDim != ipars.end(); pIndexDim++)
		//		{
		//			CIReg elt = *pIndexDim;
		//			retval.append(",").append(get_reg_name(elt).c_str());
		//		}
		//		retval.append(");");
		//	}
		//	break;
		case instr_collect_columns:
		case instr_collect_cell_columns:
		case instr_collect_rows:
		case instr_collect_cell_rows:
			{

				std::stack<CIReg>  arr_args_in;
				std::stack<CIReg>  arr_args_out;
				std::string fn;

				if (m_inst_type==instr_collect_columns)
				{
					fn="tmcCollectColumns";
				}
				else if (m_inst_type==instr_collect_rows)
				{
					fn="tmcCollectRows";
				}
				else if (m_inst_type==instr_collect_cell_columns)
				{
					fn = "tmcCollectCellColumns";
				}
				else if (m_inst_type==instr_collect_cell_rows)
				{
					fn = "tmcCollectCellRows";
				}
				else
					fn="xx?";
				na=0;

				if (Compiler.comments_output)
				{
				retval = std::string(";").append(fn);
				sprintf(buff,"(%s,%d",get_reg_name(outreg).c_str(),nipars);
				retval.append(buff);
				}

				arr_args_out.push(outreg);
				{
					std::list<CIReg>::iterator pIndexCols=ipars.begin();
					for (  ; pIndexCols != ipars.end(); pIndexCols++)
					{
						CIReg elt = *pIndexCols;
						if (Compiler.comments_output)
							retval.append(",").append(get_reg_name(elt).c_str());
						na++;
						if ((na & 7)==0) 
							if (Compiler.comments_output)
							retval.append("\n;");

						arr_args_in.push(elt);

					}
					if (Compiler.comments_output)
						retval.append(");\n");
				}
				retval.append(asm_tmcoper_call(fn,nipars,arr_args_out,arr_args_in));
			}
			break;

		case instr_get_field: // get field - get reference info in the matrix to field.
			if (Compiler.comments_output)
			{
			//sprintf(buff,"tmcGetByField(%s,%s,\"%s\");",
			//	get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),m_ident_name.c_str());
			sprintf(buff,"\t;tmcGetByFieldHcode(%s,%s,0x%08x);/* %s */\n",
				get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),
				StringHash.string2hcode(m_ident_name.c_str()),m_ident_name.c_str());
			retval=std::string(buff);
			}
			retval.append(asm_call_fnc_rrn("_tmcGetByFieldHcode",outreg,r1,StringHash.string2hcode(m_ident_name.c_str()))); 

			break;
		case instr_set_field:  // set field
			if (Compiler.comments_output)
			{
//			sprintf(buff,"tmcGetRefByField(%s,%s,\"%s\");",
//				get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),m_ident_name.c_str());
			sprintf(buff,"\t;tmcGetRefByFieldHcode(%s,%s,0x%08x);/* %s */\n",
				get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),
				StringHash.string2hcode(m_ident_name.c_str()),m_ident_name.c_str());
			retval=std::string(buff);
			}
			retval.append(asm_call_fnc_rrn("_tmcGetRefByFieldHcode",outreg,r1,StringHash.string2hcode(m_ident_name.c_str()))); 

			break;
		case instr_create_colon:// create colon
			if (Compiler.comments_output)
			{
				if(nipars==3)
				{
				sprintf(buff,";\ttmcCreateColonBaseIncLimit(%s,%s,%s,%s);\n",
					get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),
					get_reg_name(r2).c_str(),get_reg_name(r3).c_str());
				}
				else
				{
					sprintf(buff,";\ttmcCreateColonBaseLimit(%s,%s,%s);\n",
					get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
				}
				retval=std::string(buff);
			}

			if(nipars==3)
			{
				retval.append(asm_call_fnc_rrrr("_tmcCreateColonBaseIncLimit",outreg,r1,r2,r3)); 
			}
			else
			{
				retval.append(asm_call_fnc_rrr("_tmcCreateColonBaseLimit",outreg,r1,r2)); 
			}

			break;
		case instr_assign: // assignement
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s",get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcAssign(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rr("_tmcAssign",r1,r2)); // call internal function with two reg pars
			
			
			break;
		case instr_assign_bool: // assignement bool
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s",get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcAssignBool(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rr("_tmcAssignBool",r1,r2)); // call internal function with two reg pars

			break;

		case instr_copy_var: // copy var
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s",lh_var.c_str(),rh_var.c_str());
			retval=std::string("\t;tmcCopyMat(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_vv("_tmcCopyMat",lh_var,rh_var)); 

			break;
		case instr_magic_end:// x(1:2:end)
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%d,%d",get_reg_name(outreg).c_str(),m_ident_name.c_str(),mag_end_dimension,mag_end_ndimensions);
			retval=std::string("\t;tmcGetEnd(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rvnn("_tmcGetEnd",outreg,m_ident_name,mag_end_dimension,mag_end_ndimensions));

			break;
		case instr_magic_end_r:// s.x(1:2:end)
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%d,%d",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),mag_end_dimension,mag_end_ndimensions);
			retval=std::string("\t;tmcGetEnd(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrnn("_tmcGetEnd",outreg,r1,mag_end_dimension,mag_end_ndimensions));
			break;

		case instr_get_var_addr: // get address of a var - NOT SUPPORTED IN C also
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),m_ident_name.c_str());
			}
			retval="\n";//std::string("//tmcCreateVarRef(").append(buff).append(");");
			break;
		case instr_not:            // not
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str());
			retval=std::string("\t;tmcNot(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rr("_tmcNot",outreg,r1)); 
			break;

		case instr_uplus:          // uplus HAZARD
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str());
			retval=std::string("\t;tmcClone(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rr("_tmcClone",outreg,r1)); 
			break;
		case instr_uminus:         // uminus
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str());
			retval=std::string("\t;tmcNeg(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rr("_tmcNeg",outreg,r1)); // call internal function with two reg pars

			break;
		case instr_transpose:      // transpose
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str());
			retval=std::string("\t;tmcTranspose(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rr("_tmcTranspose",outreg,r1)); 
			break;
		case instr_hermitian:      // ctranspose
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str());
			retval=std::string("\t;tmcTransposeScalar(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rr("_tmcTransposeScalar",outreg,r1)); 
			break;
		case instr_add:            // plus
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcAdd(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcAdd",outreg,r1,r2));
			break;
		case instr_sub:            // minus
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcSub(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcSub",outreg,r1,r2));
			break;
		case instr_mul:            // mtimes
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcMul(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcMul",outreg,r1,r2));
			break;
		case instr_div:            // mrdivide
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcDiv(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcDiv",outreg,r1,r2));
			break;
		case instr_pow:            // mpower
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcPower(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcPower",outreg,r1,r2));
			break;
		case instr_ldiv:           // mldivide
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcLeftDiv(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcLeftDiv",outreg,r1,r2));
			break;
		case instr_lt:             // lt
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcLt(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcLt",outreg,r1,r2));
			break;
		case instr_le:             // le
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcLe(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcLe",outreg,r1,r2));
			break;
		case instr_eq:             // eq
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcEq(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcEq",outreg,r1,r2));
			break;
		case instr_ge:            // ge
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcGe(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcGe",outreg,r1,r2));
			break;
		case instr_gt:             // gt
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcGt(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcGt",outreg,r1,r2));
			break;
		case instr_ne:             // ne
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcNe(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcNe",outreg,r1,r2));
			break;
		case instr_el_mul:         // times
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcMulScalar(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcMulScalar",outreg,r1,r2));
			break;
		case instr_el_div:         // rdivide
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcDivScalar(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcDivScalar",outreg,r1,r2));
			break;
		case instr_el_pow:         // power
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcPowerScalar(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcPowerScalar",outreg,r1,r2));
			break;
		case instr_el_ldiv:        // ldivide
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcLeftDivScalar(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcLeftDivScalar(",outreg,r1,r2));
			break;
		case instr_el_and:         // and
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcAndScalar(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcAndScalar",outreg,r1,r2));
			break;
		case instr_el_or:         // or
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcOrScalar(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcOrScalar",outreg,r1,r2));
			break;
		case instr_boolean_and:         // and
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcAndBoolean(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcAndBoolean",outreg,r1,r2));
			break;
		case instr_boolean_or:         // or
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("\t;tmcOrBoolean(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrr("_tmcOrBoolean",outreg,r1,r2));
			break;

		case instr_scalar: // make a scalar matrix
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%.15e",get_reg_name(outreg).c_str(),m_Real);
			retval=std::string("\t;tmcScalar(").append(buff).append(");\n");
			}
/*
   ;	tmcScalar(reg[3],1.700000000000000e+001);
   ;	
	push      1076953088 ;// low of 64bit double
	push      0			 ;// high of 64bit double
	mov       ecx,dword ptr [ebp-40]
	mov		  eax,dword ptr [ecx+12]
	push      eax
	call      _tmcScalar
	add       esp,12


; 71   : tmcScalar(p,4.656f);

 00000254  68 40129FBE						push	   1074962366
    321	00000259  68 80000000				push	   -2147483648
    322	0000025E  FF 75	D4					push	   dword ptr [ebp-44]
    323	00000261  E8 00000000e				call	   _tmcScalar
    324	00000266  83 C4	0C					add	   esp,12


*/
			retval.append(asmgenintel.asm_gen_push_double(m_Real));
			retval.append(asmgenintel.asm_gen_push_var(outreg));
			retval.append(asmgenintel.asm_gen_call("_tmcScalar",ASM_DOUBLE_SIZE+ASM_PTR_TMCMATRIX_SIZE));

			break;
		case instr_complex: // make a complex matrix
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%.15e,%.15e",get_reg_name(outreg).c_str(),m_Real,m_Imag);
			retval=std::string("\t;tmcComplexScalar(").append(buff).append(");\n");
			}
			retval.append(asmgenintel.asm_gen_push_double(m_Imag));
			retval.append(asmgenintel.asm_gen_push_double(m_Real));
			retval.append(asmgenintel.asm_gen_push_var(outreg));
			retval.append(asmgenintel.asm_gen_call("_tmcComplexScalar",2*ASM_DOUBLE_SIZE+ASM_PTR_TMCMATRIX_SIZE));

			break;
		case instr_create_cell_empty:
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s",get_reg_name(outreg).c_str());
			retval=std::string("\t;tmcCreateCellEmpty(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_r("_tmcCreateCellEmpty",outreg));
			break;
		case instr_create_matrix_empty:
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s",get_reg_name(outreg).c_str());
			retval=std::string("\t;tmcCreateMatrixEmpty(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_r("_tmcCreateMatrixEmpty",outreg));
			break;
		case instr_create_string_empty:
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s",get_reg_name(outreg).c_str());
			retval=std::string("\t;tmcCreateStringEmpty(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_r("_tmcCreateStringEmpty",outreg));
			break;
		case instr_create_string:
			//hazard: if string contains \ must duplicate it 
			//AppendSlashes

			{
				if (Compiler.comments_output)
				{
			//sprintf(buff,"%s,\"%s\"",get_reg_name(outreg).c_str(),AppendSlashes(m_ident_name).c_str());
			//retval=std::string(";\ttmcCreateString(").append(buff).append(");\n");

			retval=std::string(";tmcCreateString(").append(get_reg_name(outreg)).append(",\"").append(
				AppendSlashes(m_ident_name)).append("\"").append(");\n");
				}
			
			long strord = AsmSymTable.addstring((m_ident_name)); // not needed append slashes !!!!

			retval.append(asmgenintel.asm_gen_push_str(strord));
			retval.append(asmgenintel.asm_gen_push_var(outreg));
			retval.append(asmgenintel.asm_gen_call("_tmcCreateString",ASM_PCHAR_SIZE+ASM_PTR_TMCMATRIX_SIZE));


			}
			break;
		case instr_fnc_handle:
			{
				if (Compiler.comments_output)
				{
			sprintf(buff,"%s,&tmc%s,\"%s\"",get_reg_name(outreg).c_str(),m_ident_name.c_str(),m_ident_name.c_str());
			retval=std::string("\t;tmcFncHandle(").append(buff).append(");\n");
				}
			//like:tmcFncHandle(reg[301],&tmctest2,"test2")
			
			long str_ord= AsmSymTable.addstring(m_ident_name);

			retval.append(asmgenintel.asm_gen_push_str(str_ord));
			retval.append(asmgenintel.asm_gen_push_fncaddr_s(std::string("_tmc").append(m_ident_name)));
			retval.append(asmgenintel.asm_gen_push_var(outreg));

			retval.append(asmgenintel.asm_gen_call("_tmcFncHandle",ASM_PCHAR_SIZE +ASM_PTR_TMCMATRIX_SIZE+ASM_FNCADDR_SIZE));

			}
			break;

		case instr_create_magic_colon:
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s",get_reg_name(outreg).c_str());
			retval=std::string("\t;tmcCreateMagicColon(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_r("_tmcCreateMagicColon",outreg));
			break;
		case instr_for_init:
			if (Compiler.comments_output)
			{
			sprintf(buff,"%s,%s,%s",get_reg_name(r1).c_str(),get_reg_name(r2).c_str(),m_ident_name.c_str());
			retval=std::string("\t;tmcForIterInit(").append(buff).append(");\n");
			}
			retval.append(asm_call_fnc_rrv("_tmcForIterInit",r1,r2,m_ident_name));

			break;
		case instr_for_next:
			if (Compiler.comments_output)
			{
			sprintf(buff,";\tif(tmcForIterNext(%s,%s)) goto label_%d; // exit for\n",
				get_reg_name(r1).c_str(),get_reg_name(r2).c_str(),igoto_label);
			retval=std::string(buff);
			}
			retval.append(asm_call_fnc_rr("_tmcForIterNext",r1,r2));
			retval.append(asmgenintel.asm_bf_ne(igoto_label));


			break;
		case instr_calc_switch_exp_value:
			if (Compiler.comments_output)
			{
			sprintf(buff,"\t;tmcCalcSwitchExpVal(%s,%s);\n",
				get_reg_name(r2).c_str(),get_reg_name(r1).c_str());
			retval=std::string(buff);
			}
			retval.append(asm_call_fnc_rr("_tmcCalcSwitchExpVal",r2,r1));

			break;
//		case instr_compare_case_v:// cell or var case (obsolete)
//			sprintf(buff,"if(tmcNotCase(%s,%s)) goto label_%d; // exit for",
//				get_reg_name(r1).c_str(),get_reg_name(r2).c_str(),igoto_label);
//			retval=std::string(buff);
//			break;
		case instr_compare_case_s:// string case (exp,label)
			if (Compiler.comments_output)
			{
			sprintf(buff,";\tif(tmcIsCaseString(%s,0x%08x)) goto label_%d; // begin  CASE %s\n",
				get_reg_name(r1).c_str(),StringHash.string2hcode(m_ident_name.c_str()),igoto_label,
				m_ident_name.c_str());
			retval=std::string(buff);
			}

			retval.append(asmgenintel.asm_gen_push_long(StringHash.string2hcode(m_ident_name.c_str())));
			retval.append(asmgenintel.asm_gen_push_var(r1));
			retval.append(asmgenintel.asm_gen_call("_tmcIsCaseString",ASM_LONG_SIZE+ASM_PTR_TMCMATRIX_SIZE));
			retval.append(asmgenintel.asm_bf_ne(igoto_label));

			break;
		case instr_compare_case_d:// double case
			if (Compiler.comments_output)
			{
			sprintf(buff,";\tif(tmcIsCaseDouble(%s,%.15e)) goto label_%d; // begin CASE\n",
				get_reg_name(r1).c_str(),m_Real,igoto_label);
			retval=std::string(buff);
			}
			retval.append(asmgenintel.asm_gen_push_double(m_Real));
			retval.append(asmgenintel.asm_gen_push_var(r1));
			retval.append(asmgenintel.asm_gen_call("_tmcIsCaseDouble",ASM_DOUBLE_SIZE+ASM_PTR_TMCMATRIX_SIZE));
			retval.append(asmgenintel.asm_bf_ne(igoto_label));

			break;

		case instr_end_statement:
			if (Compiler.comments_output)
			{
			sprintf(buff,"\t;%s,line %d\n",m_text.c_str(),src_line);
			retval=std::string(buff);
			}
			break;
		case instr_syntax_error:
			sprintf(buff,";tmcSyntaxError(\"%s, at line %d\");\n",m_text.c_str(),src_line);
			retval=std::string(buff);
			break;
		case instr_try_catch_begin:
			if (Compiler.comments_output)
			{
				retval="\t;";
				retval.append(m_text).append("\n");
			}
				retval.append(asmgenintel.asm_try_catch_begin(ilabel));

			break;


		case instr_try_catch_catch:
			if (Compiler.comments_output)
			{
				retval="\t;";
				retval.append(m_text).append("\n");
			}
				retval.append(asmgenintel.asm_try_catch_catch(ilabel,igoto_label));
			break;


		case instr_try_catch_end:
			if (Compiler.comments_output)
			{
				retval="\t;";
				retval.append(m_text).append("\n");
			}
				retval.append(asmgenintel.asm_try_catch_end(ilabel,igoto_label));
			break;

		case instr_var_decl:
			// print here all the varable declarations from sym_table and reg list
			retval="";
			//HSKOST 26.07.2012: corrected, added one

			AsmSymTable.addvar(0,"reg");
			AsmSymTable.addvar(0,"pRefHelper");

			if (Compiler.comments_output)
			{
			sprintf(buff,"\t;tmsMatrix **reg=tmcCreateRegFrame(%d);\n",ilist->get_RegFrame_size());
			retval.append(buff);
			}

			retval.append(asmgenintel.asm_gen_push_long(ilist->get_RegFrame_size()));
			retval.append(asmgenintel.asm_gen_call("_tmcCreateRegFrame",ASM_LONG_SIZE));
			retval.append(asmgenintel.asm_store_longretval_in_frame(AsmSymTable.get_reg_offset()));

			// now print local vars
			for (symbol_table::record_iterator p=TmcSymbolTable.SymList.begin();p!=TmcSymbolTable.SymList.end(); )
			{
				if (p->is_local_var(ilist->get_local_function_ind() ))
				{
					if (Compiler.comments_output)
					{
					 sprintf(buff,"\t;tmsMatrix *%s=tmcNewMatrix();\n",
			 			p->name().c_str());
					 retval.append(buff);
					}
				 long var_ofs = AsmSymTable.addvar(0,p->name().c_str());

					retval.append(asmgenintel.asm_gen_call("___tmcNewMatrix",0));
					retval.append(asmgenintel.asm_store_longretval_in_frame(var_ofs));
				}
				p++;
			}
			break;

		default:
			if (Compiler.comments_output)
			{
			retval="\t;";//HAZARD_TODO TRY_FINALLY_ENDFINALLY
			retval.append(m_text);
			}
		}
		m_text = retval;
		m_icode=retval;
		return retval;
	};
/////////// Additional information output //////////
int  symbol_table::PrintGlobalsDefsAsm(std::string inc_filename)
	{
		FILE *fp =fopen(inc_filename.c_str(),"w") ;
		//errno_t err;
		//err=fopen_s(&fp,inc_filename.c_str(),"w");

		if (fp==NULL)
		{
			return -1;
		}
/*
_pRefHelper:
	DD 0
_pGetHelper:
	DD 0

_KK:
	DD 0

*/
		fprintf(fp,"_pRefHelper:\n\tDD\t0\n");
		fprintf(fp,"_pGetHelper:\n\tDD\t0\n");
std::list<std::string> done_globals;
		for (record_iterator p=TmcSymbolTable.SymList.begin();p!=TmcSymbolTable.SymList.end();p++)
		{
			if (p->is_global_variable()&& p->is_enlisted(done_globals)==false)
			{p->enlist(done_globals);
				fprintf(fp,"_%s:\n\tDD\t0\n",p->name().c_str());
			}
		}done_globals.clear();

/*
_tmcInitGlobals:
	;tmsMatrix *KK=tmcNewMatrix();
	call	___tmcNewMatrix
	mov	[_KK+MY_LOAD_ADDRESS], eax

	ret
*/
		fprintf(fp,"_tmcInitGlobals:\n");
		for (record_iterator p=TmcSymbolTable.SymList.begin();p!=TmcSymbolTable.SymList.end();p++)
		{
			if (p->is_global_variable()&& p->is_enlisted(done_globals)==false)
			{p->enlist(done_globals);
				if (Compiler.comments_output)
					fprintf(fp,";\t%s=tmcNewMatrix();\n",p->name().c_str());
				fprintf(fp,"\tcall\t___tmcNewMatrix\n\tmov [_%s+MY_LOAD_ADDRESS], eax\n\tret\n",p->name().c_str());

			}
		}done_globals.clear();
		fprintf(fp,"\n");
/*
_tmcFreeGlobals:
	mov	eax, [_KK+MY_LOAD_ADDRESS]
	push	eax
	call	_tmcFreeLocalVar
	add	esp, 4
	ret

	mov	eax, _KK+MY_LOAD_ADDRESS

*/
		fprintf(fp,"_tmcFreeGlobals:\n");

		for (record_iterator p=TmcSymbolTable.SymList.begin();p!=TmcSymbolTable.SymList.end();p++)
		{
			if (p->is_global_variable()&& p->is_enlisted(done_globals)==false)
			{p->enlist(done_globals);
				if (Compiler.comments_output)
					fprintf(fp,";\ttmcFreeLocalVar(%s);\n",p->name().c_str());
				fprintf(fp,"\tmov\teax,[_%s+MY_LOAD_ADDRESS]\n"
							"\tpush\teax\n"
							"\tcall\t_tmcFreeLocalVar\n"
							"\tadd\tesp, 4\n"
							"\tret\n"
					,p->name().c_str());

			}
		}done_globals.clear();
		fprintf(fp,"\n");

		fclose(fp);

	return 0;
	}
/////////////