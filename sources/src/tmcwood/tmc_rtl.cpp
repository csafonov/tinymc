//! \file tmc_rtl.cpp
//! \brief Generation final C code output from instructions ('RTL') list

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
#include "tmc_string_hash.h"

#include "tmclsp_matrix.h"
#include "tmcpar_tree.h"


extern FILE *code_file;


bool is_reg_type_ident(CIReg reg)
{
	if (CInstrList::RegDescr[reg].m_reg_type==REG_TYPE_IDENT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//! \brief create an instruction C code for printing from this instruction
//! \param ilist : containing list of instructions (stores some global data)
//! \return string of C-code
std::string CInstr::gen_icode(CInstrList *ilist)
	{
		char buff[200];
		int na;// number of printed arguments. used to include newline.

		std::string retval="//";
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
			sprintf(buff,"tmc%s(",m_ident_name.c_str());
			if (ilist->is_local_function())
			{
				retval=std::string("static void ").append(buff);
			}
			else
				retval=std::string("void ").append(buff);

			retval.append("int nargout, int nargin");

			for ( std::list<std::string>::iterator p=args_out.begin(); p != args_out.end(); p++)
			{
				std::string elt = *p;
				//retval.append(",tmsMatrix **").append(elt.c_str());
				//Memory management and garbage collection is realized internally.
				//Thus all parameters are passed by values only as objects.
				retval.append(",tmsMatrix *").append(elt.c_str());
			}
			retval.append("\n");
			for ( std::list<std::string>::iterator p=args_in.begin(); p != args_in.end(); p++)
			{
				std::string elt = *p;
				retval.append(",tmsMatrix *").append(elt.c_str());
			}

			retval.append(") {");
			break;
		case instr_mexfunc_declaration: // for mex-prototype (-a option)
			
			retval=std::string();
			retval.append("\n");
			retval.append("\n");
			na=0;
			for (std::list<std::string>::iterator p=args_out.begin(); p != args_out.end(); p++)
			{
				std::string elt = *p;
				sprintf(buff,"#define\tm%s\t\t\tplhs[%d]\n",elt.c_str(),na++);
				retval.append(buff);
			}
			retval.append("\n");
			na=0;
			for (std::list<std::string>::iterator p=args_in.begin(); p != args_in.end(); p++)
			{
				std::string elt = *p;
				sprintf(buff,"#define\tm%s\t\t\tprhs[%d]\n",elt.c_str(),na++);
				retval.append(buff);
			}

			sprintf(buff,"tmc%s(",m_ident_name.c_str());
			retval.append("void ").append(buff);
			retval.append("\tint nargout, int nargin");
			na=0;
			for (std::list<std::string>::iterator p=args_out.begin(); p != args_out.end(); p++)
			{
				if (na==0)
				{
					retval.append(",\n\t");
				}
				else
				{
					retval.append(",");
				}
				na++;
				std::string elt = *p;
				//retval.append(",tmsMatrix **").append(elt.c_str());
				//Memory management and garbage collection is realized internally.
				//Thus all parameters are passed by values only as objects.
				retval.append("tmsMatrix *m").append(elt.c_str());
			}
			na=0;
			for (std::list<std::string>::iterator p=args_in.begin(); p != args_in.end(); p++)
			{
				if (na==0)
				{
					retval.append(",\n\t");
				}
				else
				{
					retval.append(",");
				}
				na++;
				std::string elt = *p;
				retval.append("tmsMatrix *m").append(elt.c_str());
			}

			retval.append(") {");

			break;

		case instr_funct_call:
			{
			int k=0;
			int all_num_args;
			int n=0;
			
			// max_nargin: max nargin by SymTab or -1
			// max_nargout: max nargout by SymTab or -1
			// nipars: actual number rhs pars
			// nipars_out: actual number lhs pars
			//if (max_nargin<0)
			//	max_nargin=nipars;

			//if(max_nargout<0)
			//	max_nargout=nipars_out;

			all_num_args = max_nargout+max_nargin;
			// max_nargin : actual number rhs pars (extended by NULLs)
			// max_nargout: actual number lhs pars (extended by regs)


/* E.g.:
	tmcFreeRegister(&reg3);
	reg3 = tmcNewMatrix();
	tmcaver(1,1,reg3,reg1);
*/
			retval=std::string("//CALL function\n");
			std::list<CIReg>::iterator p1=ipars_out.begin();// first actual out_par
			for (k=0;k<max_nargout;k++)
			{	
				if(p1 != ipars_out.end())
				{
					CIReg reg = *p1;
					sprintf(buff,"tmcReallocRegister(%s);\n",get_reg_name(reg).c_str());
					retval.append(buff);
					p1++;
				}
			}

			sprintf(buff,"tmc%s(%d,%d",m_ident_name.c_str(),nipars_out,nipars);
			retval.append(buff);//retval=std::string(buff);

			if(n<all_num_args)
					retval.append(",");

			std::list<CIReg>::iterator p=ipars_out.begin();// first actual out_par
			n=0;na=0;
			for (k=0;k<max_nargout;k++)
			{	
				if(p != ipars_out.end())
				{
					CIReg reg = *p;
					//retval.append("&").append(get_reg_name(reg).c_str());
					retval.append(" ").append(get_reg_name(reg).c_str());
					p++;
				} 
				else
				{
					retval.append("NULL");
				}
				if(n<all_num_args-1)
					retval.append(",");
				n++;
				na++;if ((na & 7)==0)
					retval.append("\n");
			}
			std::list<CIReg>::iterator p2=ipars.begin();// first actual in_par
			na=0;
			for (k=0;k<max_nargin;k++)
			{
				if(p2 != ipars.end())
				{
					CIReg reg = *p2;
	//				retval.append("&").append(get_reg_name(reg).c_str());
					retval.append(" ").append(get_reg_name(reg).c_str());
					p2++;
				}
				else
				{
					retval.append("NULL");
				}
				if(n<all_num_args-1)
					retval.append(",");
				n++;
				na++;if ((na & 7)==0)
					retval.append("\n");

			}
				retval.append(");");
			}
			break;

		case instr_save_call:
			{
			int k=0;
			int all_num_args;
			int n=0;

				all_num_args =n_argin;// variable number of input parameters
				max_nargin = n_argin;

			retval=std::string("//CALL function save\n");
			// the function has no outputs
			sprintf(buff,"tmc%s(%d,%d",m_ident_name.c_str(),0,1 + n_argin);
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
				}
				else
				{
					retval.append("NULL");
				}
				if(n<all_num_args-1)
					retval.append(",");
				n++;
				na++;if ((na & 7)==0)
					retval.append("\n");

			}
				retval.append(");");
			}

			break;
		case instr_block_end:// function end
			retval=std::string("}");
			break;
		case instr_clear_local_vars:// clear local vars at function exit
			retval="";

			// finally clear local vars
			for (symbol_table::record_iterator p=TmcSymbolTable.SymList.end();p!=TmcSymbolTable.SymList.begin(); )
			{
				p--;
				if (p->is_local_var(ilist->get_local_function_ind() ))
				{
				 sprintf(buff,"tmcFreeLocalVar(%s);\n",
			 		p->name().c_str());
				 retval.append(buff);
				}
			}
			// clear registers
			/*
			for (CIReg kk=ilist->max_regs()-1;kk>1;kk--)
			{
				if (is_reg_type_ident(kk)==false)
				{				
					sprintf(buff,"tmcFreeRegister(%s);\n",
			 		get_reg_name(kk).c_str());
					retval.append(buff);
				}
			}
			*/
					sprintf(buff,"tmcFreeRegFrame(reg);\n");
					retval.append(buff);

			break;
		case instr_goto: // goto
			sprintf(buff,"goto label_%d; //%s",igoto_label,m_comment.c_str());
			retval=std::string(buff);
			break;
		case instr_label: // no operation, only label
			sprintf(buff,"label_%d: ; //%s",ilabel,m_comment.c_str());
			retval=std::string(buff);
			break;
		case instr_isfield_call:// isfield
			sprintf(buff,"tmcIsFieldHcode(%s,%s,0x%08x);/* %s */",
				get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),
				StringHash.string2hcode(m_ident_name.c_str()),m_ident_name.c_str());
			retval=std::string(buff);

			break;
		case instr_test_value:// test a register
			sprintf(buff,"if(tmcIsFalse(%s)) goto label_%d; // %s",
				get_reg_name(r1).c_str(),igoto_label,m_comment.c_str());
			retval=std::string(buff);
			break;
		case instr_test_value_t:// test a register
			sprintf(buff,"if(tmcIsTrue(%s)) goto label_%d; // %s",
				get_reg_name(r1).c_str(),igoto_label,m_comment.c_str());
			retval=std::string(buff);
			break;

		case instr_test_value_ass:// test a register
			sprintf(buff,"if(tmcIsFalse(%s)) {\n\ttmcAssignFalse(%s); goto label_%d; } // %s",
				get_reg_name(r1).c_str(),get_reg_name(r2).c_str(),igoto_label,m_comment.c_str());
			retval=std::string(buff);
			break;
		case instr_test_value_t_ass:// test a register
			sprintf(buff,"if(tmcIsTrue(%s)) {\n\ttmcAssignTrue(%s); goto label_%d;} // %s",
				get_reg_name(r1).c_str(),get_reg_name(r2).c_str(),igoto_label,m_comment.c_str());
			retval=std::string(buff);
			break;


		case instr_index_get: // get subset from matrix - get refernce info to submatix.
		case instr_index_set: // assign subset from matrix
		case instr_cellarray_index_get: // get subset from matrix - get refernce info to submatix.
		case instr_cellarray_index_set: // assign subset from matrix
			if(m_inst_type==instr_index_get)
				retval="tmcGetByIndex(";
			else if (m_inst_type==instr_index_set)
				retval="tmcGetRefByIndex(";
			else if (m_inst_type==instr_cellarray_index_get)
				retval="tmcGetByIndexCell(";
			else if (m_inst_type==instr_cellarray_index_set)
				retval="tmcGetRefByIndexCell(";
			else retval="x?";
			sprintf(buff,"%s,%s,%d",
				get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),nipars-1);
			retval.append(buff);
			{
				std::list<CIReg>::iterator pIndexDim=ipars.begin();pIndexDim++;//skip addressed matrix
				for (  ; pIndexDim != ipars.end(); pIndexDim++)
				{
					CIReg elt = *pIndexDim;
					retval.append(",").append(get_reg_name(elt).c_str());
				}
				retval.append(");");
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
			if (m_inst_type==instr_collect_columns)
			{
				retval=std::string("tmcCollectColumns");
			}
			else if (m_inst_type==instr_collect_rows)
			{
				retval=std::string("tmcCollectRows");
			}
			else if (m_inst_type==instr_collect_cell_columns)
			{
				retval=std::string("tmcCollectCellColumns");
			}
			else if (m_inst_type==instr_collect_cell_rows)
			{
				retval=std::string("tmcCollectCellRows");
			}
			else
				retval="xx?";
			na=0;
			sprintf(buff,"(%s,%d",
				get_reg_name(outreg).c_str(),nipars);
			retval.append(buff);
			{
				std::list<CIReg>::iterator pIndexCols=ipars.begin();
				for (  ; pIndexCols != ipars.end(); pIndexCols++)
				{
					CIReg elt = *pIndexCols;
					retval.append(",").append(get_reg_name(elt).c_str());
					na++;if ((na & 7)==0) 
						retval.append("\n");
				}
				retval.append(");");
			}


			break;

		case instr_get_field: // get field - get reference info in the matrix to field.
			//sprintf(buff,"tmcGetByField(%s,%s,\"%s\");",
			//	get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),m_ident_name.c_str());
			sprintf(buff,"tmcGetByFieldHcode(%s,%s,0x%08x);/* %s */",
				get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),
				StringHash.string2hcode(m_ident_name.c_str()),m_ident_name.c_str());
			retval=std::string(buff);

			break;
		case instr_set_field:  // set field
//			sprintf(buff,"tmcGetRefByField(%s,%s,\"%s\");",
//				get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),m_ident_name.c_str());
			sprintf(buff,"tmcGetRefByFieldHcode(%s,%s,0x%08x);/* %s */",
				get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),
				StringHash.string2hcode(m_ident_name.c_str()),m_ident_name.c_str());
			retval=std::string(buff);
			break;
		case instr_create_colon:// create colon
			if(nipars==3)
			sprintf(buff,"tmcCreateColonBaseIncLimit(%s,%s,%s,%s);",
				get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),
				get_reg_name(r2).c_str(),get_reg_name(r3).c_str());
			else
			sprintf(buff,"tmcCreateColonBaseLimit(%s,%s,%s);",
				get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());

			retval=std::string(buff);

			break;
		case instr_assign: // assignement
			sprintf(buff,"%s,%s",get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcAssign(").append(buff).append(");");
			break;
		case instr_assign_bool: // assignement bool
			sprintf(buff,"%s,%s",get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcAssignBool(").append(buff).append(");");
			break;

		case instr_copy_var: // copy var
			sprintf(buff,"%s,%s",lh_var.c_str(),rh_var.c_str());
			retval=std::string("tmcCopyMat(").append(buff).append(");");
			break;
		case instr_magic_end:// x(1:2:end)
			sprintf(buff,"%s,%s,%d,%d",get_reg_name(outreg).c_str(),m_ident_name.c_str(),mag_end_dimension,mag_end_ndimensions);
			retval=std::string("tmcGetEnd(").append(buff).append(");");
			break;
		case instr_magic_end_r:// s.x(1:2:end)
			sprintf(buff,"%s,%s,%d,%d",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),mag_end_dimension,mag_end_ndimensions);
			retval=std::string("tmcGetEnd(").append(buff).append(");");
			break;

		case instr_get_var_addr: // get address of a var
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),m_ident_name.c_str());
			retval="";//std::string("//tmcCreateVarRef(").append(buff).append(");");
			break;
		case instr_not:            // not
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),get_reg_name(ipars.front()).c_str());
			retval=std::string("tmcNot(").append(buff).append(");");
			break;

		case instr_uplus:          // uplus HAZARD
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),get_reg_name(ipars.front()).c_str());
			retval=std::string("tmcClone(").append(buff).append(");");
			break;
		case instr_uminus:         // uminus
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),get_reg_name(ipars.front()).c_str());
			retval=std::string("tmcNeg(").append(buff).append(");");
			break;
		case instr_transpose:      // transpose
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),get_reg_name(ipars.front()).c_str());
			retval=std::string("tmcTranspose(").append(buff).append(");");
			break;
		case instr_hermitian:      // ctranspose
			sprintf(buff,"%s,%s",get_reg_name(outreg).c_str(),get_reg_name(ipars.front()).c_str());
			retval=std::string("tmcTransposeScalar(").append(buff).append(");");
			break;
		case instr_add:            // plus
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcAdd(").append(buff).append(");");
			break;
		case instr_sub:            // minus
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcSub(").append(buff).append(");");
			break;
		case instr_mul:            // mtimes
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcMul(").append(buff).append(");");
			break;
		case instr_div:            // mrdivide
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcDiv(").append(buff).append(");");
			break;
		case instr_pow:            // mpower
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcPower(").append(buff).append(");");
			break;
		case instr_ldiv:           // mldivide
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcLeftDiv(").append(buff).append(");");
			break;
		case instr_lt:             // lt
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcLt(").append(buff).append(");");
			break;
		case instr_le:             // le
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcLe(").append(buff).append(");");
			break;
		case instr_eq:             // eq
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcEq(").append(buff).append(");");
			break;
		case instr_ge:            // ge
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcGe(").append(buff).append(");");
			break;
		case instr_gt:             // gt
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcGt(").append(buff).append(");");
			break;
		case instr_ne:             // ne
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcNe(").append(buff).append(");");
			break;
		case instr_el_mul:         // times
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcMulScalar(").append(buff).append(");");
			break;
		case instr_el_div:         // rdivide
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcDivScalar(").append(buff).append(");");
			break;
		case instr_el_pow:         // power
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcPowerScalar(").append(buff).append(");");
			break;
		case instr_el_ldiv:        // ldivide
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcLeftDivScalar(").append(buff).append(");");
			break;
		case instr_el_and:         // and
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcAndScalar(").append(buff).append(");");
			break;
		case instr_el_or:         // or
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcOrScalar(").append(buff).append(");");
			break;
		case instr_boolean_and:         // and
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcAndBoolean(").append(buff).append(");");
			break;
		case instr_boolean_or:         // or
			sprintf(buff,"%s,%s,%s",get_reg_name(outreg).c_str(),get_reg_name(r1).c_str(),get_reg_name(r2).c_str());
			retval=std::string("tmcOrBoolean(").append(buff).append(");");
			break;

		case instr_scalar: // make a scalar matrix
			sprintf(buff,"%s,%.15e",get_reg_name(outreg).c_str(),m_Real);
			retval=std::string("tmcScalar(").append(buff).append(");");

			break;
		case instr_complex: // make a complex matrix
			sprintf(buff,"%s,%.15e,%.15e",get_reg_name(outreg).c_str(),m_Real,m_Imag);
			retval=std::string("tmcComplexScalar(").append(buff).append(");");
			break;
		case instr_create_cell_empty:
			sprintf(buff,"%s",get_reg_name(outreg).c_str());
			retval=std::string("tmcCreateCellEmpty(").append(buff).append(");");
			break;
		case instr_create_matrix_empty:
			sprintf(buff,"%s",get_reg_name(outreg).c_str());
			retval=std::string("tmcCreateMatrixEmpty(").append(buff).append(");");
			break;
		case instr_create_string_empty:
			sprintf(buff,"%s",get_reg_name(outreg).c_str());
			retval=std::string("tmcCreateStringEmpty(").append(buff).append(");");
			break;
		case instr_create_string:
			//hazard: if string contains \ must duplicate it 
			//AppendSlashes

			retval=std::string("tmcCreateString(").append(get_reg_name(outreg)).append(",\"").append(
				AppendSlashes(m_ident_name)).append("\"").append(");");


			//bug:sprintf(buff,"%s,\"%s\"",get_reg_name(outreg).c_str(),AppendSlashes(m_ident_name).c_str());
			//retval=std::string("tmcCreateString(").append(buff).append(");");
			break;
		case instr_fnc_handle:
			sprintf(buff,"%s,&tmc%s,\"%s\"",get_reg_name(outreg).c_str(),m_ident_name.c_str(),m_ident_name.c_str());
			retval=std::string("tmcFncHandle(").append(buff).append(");");
			break;

		case instr_create_magic_colon:
			sprintf(buff,"%s",get_reg_name(outreg).c_str());
			retval=std::string("tmcCreateMagicColon(").append(buff).append(");");
			break;
		case instr_for_init:
			sprintf(buff,"%s,%s,%s",get_reg_name(r1).c_str(),get_reg_name(r2).c_str(),m_ident_name.c_str());
			retval=std::string("tmcForIterInit(").append(buff).append(");");
			break;
		case instr_for_next:
			sprintf(buff,"if(tmcForIterNext(%s,%s)) goto label_%d; // exit for",
				get_reg_name(r1).c_str(),get_reg_name(r2).c_str(),igoto_label);
			retval=std::string(buff);
			break;
		case instr_calc_switch_exp_value:
			sprintf(buff,"tmcCalcSwitchExpVal(%s,%s);",
				get_reg_name(r2).c_str(),get_reg_name(r1).c_str(),igoto_label);
			retval=std::string(buff);
			break;
		case instr_compare_case_v:// cell or var case (obsolete)
			sprintf(buff,"if(tmcNotCase(%s,%s)) goto label_%d; // exit for",
				get_reg_name(r1).c_str(),get_reg_name(r2).c_str(),igoto_label);
			retval=std::string(buff);
			break;
		case instr_compare_case_s:// string case (exp,label)
			sprintf(buff,"if(tmcIsCaseString(%s,0x%08x)) goto label_%d; // begin  CASE %s",
				get_reg_name(r1).c_str(),StringHash.string2hcode(m_ident_name.c_str()),igoto_label,
				m_ident_name.c_str());
			retval=std::string(buff);
			break;
		case instr_compare_case_d:// double case
			sprintf(buff,"if(tmcIsCaseDouble(%s,%.15e)) goto label_%d; // begin CASE",
				get_reg_name(r1).c_str(),m_Real,igoto_label);
			retval=std::string(buff);
			break;

		case instr_end_statement:
			sprintf(buff,"%s,line %d\n",m_text.c_str(),src_line);
			retval=std::string(buff);
			break;
		case instr_syntax_error:
			sprintf(buff,"tmcSyntaxError(\"%s, at line %d\");",m_text.c_str(),src_line);
			retval=std::string(buff);
			break;
		case instr_try_catch_begin:
		case instr_try_catch_catch:
		case instr_try_catch_end:
				retval=m_text;
			break;
		case instr_var_decl:
			// print here all the varable declarations from sym_table and reg list
			retval="";
			//HSKOST 26.07.2012: corrected, added one
			sprintf(buff,"tmsMatrix **reg=tmcCreateRegFrame(%d);\n",ilist->get_RegFrame_size());
			retval.append(buff);

			// now print local vars
			for (symbol_table::record_iterator p=TmcSymbolTable.SymList.begin();p!=TmcSymbolTable.SymList.end(); )
			{
				if (p->is_local_var(ilist->get_local_function_ind() ))
				{
				 sprintf(buff,"tmsMatrix *%s=tmcNewMatrix();\n",
			 		p->name().c_str());
				 retval.append(buff);
				}
				p++;
			}
			break;
		
		case instr_debuginfo_pushstackvars:
			{
				retval="";
				int na=0;
				if (n_argin==0)
				{
					sprintf(buff,"TMC_DBG_PUSH_STACK_VAR(\"%s\",%d,NULL,NULL);\n", m_ident_name.c_str(),n_argin  );
					retval.append(buff);
				}
				else
				{
					sprintf(buff,"TMC_DBG_PUSH_STACK_VAR(\"%s\",%d,\n", m_ident_name.c_str(),n_argin  );
					retval.append(buff);

					for (std::list<std::string>::iterator p=args_in.begin(); p != args_in.end(); p++)
					{
						na++;
						std::string elt = *p;
						retval.append(elt.c_str()).append(",\"").append(elt.c_str()).append("\"");
						if (na<n_argin)
									retval.append(",\n");
						else
									retval.append(");\n");
					}

				}
			}

			break;

		case instr_debuginfo_popstackvars:
				 retval="";
				 sprintf(buff,"TMC_DBG_POP_STACK_VAR(%d);\n", n_argin  );
				 retval.append(buff);
			break;


		default:
			retval=m_text;
		}
		m_text = retval;
		m_icode=retval;
		return retval;
	};




//////////// additional information output /////////////////
int  symbol_table::PrintGlobalsDefs(std::string h_filename,std::string c_filename)
	{
		FILE *fp=fopen(h_filename.c_str(),"w");
		//errno_t err=fopen_s(&fp,h_filename.c_str(),"w");
		if (fp==NULL)
		{
			return -1;
		}
		fprintf(fp,"//File: %s \n//Generated by TMC Converter(C)2009-2016\n",
			extract_file_name(h_filename).c_str());
		fprintf(fp,"#include \"tmc.h\"\n");
		fprintf(fp,"#ifndef _tmc_globals_h_\n");
		fprintf(fp,"#define _tmc_globals_h_\n");
		std::list<std::string> done_globals;

		for (record_iterator p=TmcSymbolTable.SymList.begin();p!=TmcSymbolTable.SymList.end();p++)
		{
			if (p->is_global_variable() && p->is_enlisted(done_globals)==false)
			{
				fprintf(fp,"extern tmsMatrix * %s;\n",p->name().c_str());
				p->enlist(done_globals);
			}
		}
		done_globals.clear();
		fprintf(fp,"extern tmsMatrix	*pRefHelper;\n");
		fprintf(fp,"extern tmsMatrix	*pGetHelper;\n");

		fprintf(fp,"#endif\n");
		fclose(fp);

		//err=fopen_s(&fp,c_filename.c_str(),"w");
		fp=fopen(c_filename.c_str(),"w");
		if (fp==NULL)
		{
			return -1;
		}
		fprintf(fp,"//File: %s \n//Generated by TMC Converter(C)2009-2016\n",
			extract_file_name(c_filename).c_str());
		fprintf(fp,"#include \"tmc.h\"\n");
		//fprintf(tmc_output,"#include \"%s\"\n\n","stdtmc.h");
		fprintf(fp,"#include \"%s.globals.h\"\n\n",&ws_file_name[0]);
		//fprintf(tmc_output,"// User provided C-code header (must be included in include path):\n");
		//fprintf(tmc_output,"#include \"%s\"\n\n","External_func.h");

		fprintf(fp,"tmsMatrix	*pRefHelper;\n");
		fprintf(fp,"tmsMatrix	*pGetHelper;\n");

		

		for (record_iterator p=TmcSymbolTable.SymList.begin();p!=TmcSymbolTable.SymList.end();p++)
		{
			if (p->is_global_variable())
			{
				if (p->is_enlisted(done_globals)==false)
				{
					fprintf(fp,"tmsMatrix *%s;\n",p->name().c_str());
					p->enlist(done_globals);
				}
			}
		}
		done_globals.clear();

		fprintf(fp,"void tmcInitGlobals(void)\n{\n");

		for (record_iterator p=TmcSymbolTable.SymList.begin();p!=TmcSymbolTable.SymList.end();p++)
		{
			if (p->is_global_variable())
			{
				if (p->is_enlisted(done_globals)==false)
				{
				fprintf(fp,"%s=tmcNewMatrix();\n",p->name().c_str());
				p->enlist(done_globals);
				}
			}
		}
		done_globals.clear();

		fprintf(fp,"}\n");
		fprintf(fp,"void tmcFreeGlobals(void)\n{\n");

		for (record_iterator p=TmcSymbolTable.SymList.begin();p!=TmcSymbolTable.SymList.end();p++)
		{
			if (p->is_global_variable())
			{
				if (p->is_enlisted(done_globals)==false)
				{
				fprintf(fp,"tmcFreeLocalVar(%s);\n",p->name().c_str());
				p->enlist(done_globals);
				}
			}
		}
		done_globals.clear();
		fprintf(fp,"}\n");

		fclose(fp);

	return 0;
	}
////////////
int  symbol_table::PrintCommonHeader(std::string filename)
	{
		/*
		FILE *fp=fopen(filename,"w");;
		//fp=fopen_s(&fp,filename,"w");
		if (fp==NULL)
		{
			return -1;
		}
		for (record_iterator p=TmcSymbolTable.SymList.begin();p!=TmcSymbolTable.SymList.end();p++)
		{
			if (p->m_modifier.m_is_var ==0)
			{
				//fprintf(fp,"%s,%d,%d,%c;\n",p->name().c_str(),p->in_args,p->out_args,'m');
			}
		}
		fclose(fp);
		*/
	return 0;
	}
////////////
void create_init_hash_data_file(char *_file_name)
{
FILE *fp=fopen(_file_name, "wt");
	//int err=fopen_s(&fp,_file_name, "wt");
	
        if (fp == NULL) {
            perror("Could not open the init_hash_data_file"); exit(1);
        }
		std::string string_hash_file_name = ws_file_name; //get_func_name_only(extract_file_name(input_file_name));
		string_hash_file_name.append(".hash_init.dat");

		std::string globals_file_name = ws_file_name; //get_func_name_only(extract_file_name(input_file_name));


fprintf(fp,"/* generated by TMC */\n");
fprintf(fp,"#include \"tmc.h\"\n");
fprintf(fp,"#include \"%s.globals.h\"\n",globals_file_name.c_str());
fprintf(fp,"const struct CInitHashData InitHashData[]={\n");
fprintf(fp,"#include \"%s\"\n",string_hash_file_name.c_str());
fprintf(fp,"};\n");
fprintf(fp,"const long InitHashDataLen=sizeof(InitHashData)/sizeof(struct CInitHashData);\n");
fprintf(fp,"const struct CInit_funcs_table Init_funcs_table = { InitHashData,&InitHashDataLen,tmcInitGlobals,tmcFreeGlobals,&pRefHelper,&pGetHelper  };\n");
		fclose(fp);
}
