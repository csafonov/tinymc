/// \file tmclsp_rtlgen.cpp
/// \brief Utilities for generation of intermediate code ('RTL' instruction list) from tree

/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "tmcpar_tree.h"

#define LAST_SRC_LINE 10000000L

// initialize constants
const std::string CInstrList::out_var_suf = "__out__tmc";
const std::string CInstrList::input_var_suf = "__input__tmc";
struct CRegDescr CInstrList::RegDescr[MAX_CIREG];



// rtl generation utilities from trees
std::string get_reg_name(CIReg reg)
	{
		std::string retval;
		char buf[100];
		if (CInstrList::RegDescr[reg].m_reg_type==REG_TYPE_IDENT)
		{
			retval=CInstrList::RegDescr[reg].varname;
			//sprintf_s(buf,99,"%s",retval.c_str());
			//retval.append(buf);
		}
		else if (reg==Set_Helper_Reg)
		{
				retval="pRefHelper";
		}
		//else if (reg==Get_Helper_Reg)
		//{
		//		retval="pGetHelper";
		//}
		else
		{
		/*
		sprintf_s(buf,9,"%d",reg);
		retval="reg";
		retval.append(buf);
		*/
		sprintf(buf,"[%d]",reg);
		retval="reg";
		retval.append(buf);
		}
		return retval;

	};
std::string AppendSlashes(std::string x)
{
	int indexCh1a;

	indexCh1a = x.find("\\",0);
	while (indexCh1a >=0)
	{
		x.insert(indexCh1a+1,"\\");
		indexCh1a = x.find("\\",indexCh1a+2);
	}

	indexCh1a = x.find("\"",0);
	while (indexCh1a >=0)
	{
		x.insert(indexCh1a+1,"\"");
		indexCh1a = x.find("\"",indexCh1a+2);
	}

	return x;
}

void generic_tree::generate_rtl_node(CInstrList *list)
	{
		//TODO
		CInstr i;
		i.m_text = "generic_tree";
		list->push_back(i);
	};
void generic_tree::generate_rtl(CInstrList *list,bool bIsCellArray)
	{
		if (this->is_expr_gen())
			if ( ((T_expr_gen*)this)->is_expr_bool())
			{
				// dont generate the code for boolean expression.
				goto L1;
			}
		//if (lhs() != NULL)
		//{
		//	lhs()->generate_rtl(list,bIsCellArray);// generate operand1
		//}
L1:
		generate_rtl_node(list);
	};

bool T_stmnt_gen::mark_procedure_call()
// check if the statement is a procedure call
{
	bool retval=false;
	if(m_statement)
	if (m_statement->is_expr_gen()) //is_expr_colession())
	{
		//T_expr_col *tce=(T_expr_col*)m_statement;
		T_expr_gen *te_b = ((T_expr_gen*)m_statement)->baseexpr();
		if ( te_b->is_expr_index())
		{
			T_expr_index *tie=(T_expr_index*)te_b;
			tie->store_num_out_pars(0); // like f()
			retval=true;
		}
		else if(te_b->is_identifier())
		{
			T_ident *tid=(T_ident*)te_b;
			tid->store_num_out_pars(0); // like f;
			retval=true;
		}
	}
	return retval;
}
void T_stmnt_gen::generate_rtl_node(CInstrList *ilist)
	{
		m_statement->generate_rtl(ilist);
		res_rtl =ilist->append_end_statement(m_line);
		ilist->free_registers();
	};
void T_expr_gen::mark_expr_as_lhs_of_assignment()
{
		//T_expr_col *tce=(T_expr_col *)this;
		if(baseexpr()->is_identifier())
		{
			T_ident *tid=(T_ident *)baseexpr();
			tid->mark_as_lhs_in_assignment();
		}
		else if(baseexpr()->is_expr_index())
		{
			T_expr_index *tinde=(T_expr_index *)baseexpr();
			tinde->mark_as_lhs_in_assignment();
		}
}
void T_expr_gen::mark_var_in_lhs_of_assignment()
{
	std::string varname="?";
    T_ident *tid;
	T_expr_gen *te;


		//T_expr_col *tce=(T_expr_col *)this;
		if(baseexpr()->is_identifier())
		{
			tid=(T_ident *)baseexpr();
			varname=tid->name();
		}
		else if(baseexpr()->is_expr_index())
		{
			T_expr_index *tinde=(T_expr_index *)baseexpr();
			te = tinde;
			//TEMPORARY_NOLHS
			//while (te->lhs()!=NULL)
			//{
			//	te=(T_expr_gen *)te->lhs();
			//}

			// find the identifier in the index expression, like x in   x.sua(2)
			while (te->is_expr_index())
			{
				tinde=(T_expr_index *)te;
				te=tinde->e();
			}
			if(te->is_identifier())// must be true
			{
			tid=(T_ident *)te;
			varname=tid->name();
			}
		}
		TmcSymbolTable.mark_assigned_var(varname);
}

void	T_expr_gen::mark_mag_end(struct CIRegEx mat_name,int dim,int ndims)
	{// mark possible magic  end in arithmetic expression.
		
		if (this->is_identifier())
		{
			((T_ident*)this)->put_mag_end_info(mat_name,dim,ndims);
			return;
		}
		if (this->is_expr_bin())
		{
			((T_expr_bin*)this)->oplhs()->mark_mag_end(mat_name,dim,ndims);
			((T_expr_bin*)this)->oprhs()->mark_mag_end(mat_name,dim,ndims);
			return;
		}
					if (this->is_expr_colession())//HAZARD
					{
						if (((T_expr_col *)this)->base())
							((T_expr_col *)this)->base()->mark_mag_end(mat_name,dim,ndims);
						if (((T_expr_col *)this)->increment())
							((T_expr_col *)this)->increment()->mark_mag_end(mat_name,dim,ndims);
						if (((T_expr_col *)this)->limit())
							((T_expr_col *)this)->limit()->mark_mag_end(mat_name,dim,ndims);
					}
	}

void T_expr_gen::generate_rtl_node(CInstrList *list)
	{
		//TODO
		CInstr i;
		i.m_text = "**** unknown expression";
		list->push_back(i);
	};
void T_ident::	generate_rtl_node(CInstrList *ilist)// identifier
	{//HAZARD: for VAR (not function call)

		bool bIs_FuncName=false;
		int nNumFuncArgIn=-1;
		int nNumFuncArgOut=-1;

		if(TmcSymbolTable.is_variable(name())==false)
		{
			TmcSymbolTable.get_func_pars_num(name(),&nNumFuncArgIn,&nNumFuncArgOut);
			bIs_FuncName=true;
		}

		if(bIs_FuncName==false)
		{
			//if (IsFormalPar()==false)
			//{

				// For the formal parameters:
				// saved vars must be marked as initialized
				// input pars must be marked as initialized

				if (is_lhs_in_assignment())
				{
				// mark that the variable is initialized
					TmcSymbolTable.mark_initialized_var(name());
				}
				else
				{
				// check if the variable is initialized.
				//	If not - print message that it is not variable or not initialized.
						if (TmcSymbolTable.is_initialized_var(name()))
						{

						}
						else
						{
							Compiler.LogWarn(7, "Variable is not initialized",m_ident_name, m_line);
						}
				}

				res_rtl =ilist->append_get_var_addr(name());
			//}
			//else
			//	res_rtl =&ilist->back();// do nothing
		}
		else
		{
			//HSKOST17.03.2016: a function or j/i may not be re-assigned in TMC (MATLAB allows it)
			if (is_lhs_in_assignment())
			{
				Compiler.LogErr(1, "overridding assignment is not allowed",m_ident_name, m_line);
			}
		// function call ("procedure" without input arguments)
			if (m_is_func_call==false)
			{
				// special case of magic_end:
				if (is_mag_end())
				{	
					struct CIRegEx r;
					r.is_mat_name=mag_end_info.is_byname;
					
					if (mag_end_info.is_byname==false)
					{
						r.r.reg=mag_end_info.mat_reg;
					}
					else
					{
						r.r.varname=mag_end_info.mat_name;
					}
					res_rtl =ilist->append_magic_end(r,mag_end_info.dim,mag_end_info.ndims);
				}
				else
				{
					std::list<CInstr*> EmptyInputArgList;
					res_rtl =ilist->append_func_call(nNumFuncArgIn,nNumFuncArgOut,m_num_out_pars,name(),&EmptyInputArgList);

						if (res_rtl->max_nargin>=0 && res_rtl->nipars > res_rtl->max_nargin)
						{
							Compiler.LogErr(9, "Invalid number input parameters in call",res_rtl->m_ident_name, m_line);
							//fprintf(stderr,"\n **Error: Invalid number input parameters in call %s, in %s at line %d\n",res_rtl->m_ident_name.c_str(),c_file_name.c_str(),m_line);
							//if (Compiler.bUseDumpFile) fprintf(dump_file,"\n **Error: Invalid number input parameters in call %s, in %s at line %d\n",res_rtl->m_ident_name.c_str(),c_file_name.c_str(),m_line);
						}
						if (res_rtl->max_nargout>=0 && res_rtl->nipars_out > res_rtl->max_nargout)
						{	
							Compiler.LogErr(10, "Invalid number output parameters in call",res_rtl->m_ident_name, m_line);
							//fprintf(stderr,"\n **Error: Invalid number output parameters in call %s, in %s at line %d\n",res_rtl->m_ident_name.c_str(),c_file_name.c_str(),m_line);
							//if (Compiler.bUseDumpFile) fprintf(dump_file,"\n **Error: Invalid number output parameters in call %s, in %s at line %d\n",res_rtl->m_ident_name.c_str(),c_file_name.c_str(),m_line);
						}

				}
			}
		}
		//list->push_back(i);
		//res_rtl =&list->back();

	};


void T_const::generate_rtl_node(CInstrList *ilist)// constant
	{
		CInstr iConst;
		// assign the constant to a register
		// 1. get new register
		iConst.outreg=ilist->get_new_reg();
		switch (val->m_desc.m_type)
		{
		case TYPE_MATRIX:
		 if(_tmcIsEmptyMatrix(val))
		 {
			iConst.m_inst_type = CInstr::instr_create_matrix_empty;
		 }
		 else
		 {
			if (_tmcHasIm(val))
			{
			iConst.m_inst_type =CInstr::instr_complex;
			iConst.m_Real =val->value.complx.rData[0];
			iConst.m_Imag =val->value.complx.iData[0];
			}
			else
			{
			iConst.m_inst_type = CInstr::instr_scalar;
			iConst.m_Real =val->value.complx.rData[0];
			}
		}
			break;
		case TYPE_CELL_ARRAY:
			if (_tmcIsEmptyMatrix(val))
			{
			iConst.m_inst_type = CInstr::instr_create_cell_empty;
			}
			else
			{
				// impossible so far since we dont support constants optimization
			}
			break;
		case TYPE_STRING:
		 if(_tmcIsEmptyMatrix(val))
		 {
			iConst.m_inst_type = CInstr::instr_create_string_empty;
		 }
		 else
		 {
			iConst.m_inst_type = CInstr::instr_create_string;
			AssignMtoStr(iConst.m_ident_name,val);
		  }
		break;
		case TYPE_MAGIC_COLON:
			iConst.m_inst_type = CInstr::instr_create_magic_colon;
			break;
		}
		res_rtl =ilist->append(iConst);
};
void T_expr_func::generate_rtl_node(CInstrList *ilist)// fcn_handle
	{
		CInstr iFncHandle;
		// assign the constant to a register
		iFncHandle.outreg=ilist->get_new_reg();
		iFncHandle.m_inst_type = CInstr::instr_fnc_handle;
		iFncHandle.m_ident_name =fnc_name;
		res_rtl =ilist->append(iFncHandle);
	};

void L_args::generate_rtl(CInstrList *ilist,bool bIsCellArrayRow)// add columns
	{//TODO - HAZARD: must generate ROW!!!!
				generate_rtl_list(ilist);
		// here we must connect all the columns and return the result of the connection
				CInstr iCollectColumns;
				iCollectColumns.outreg = ilist->get_new_reg();// output register
				if (bIsCellArrayRow==true)
					iCollectColumns.m_inst_type = CInstr::instr_collect_cell_columns; // collect columns to build a matrix row
				else
					iCollectColumns.m_inst_type = CInstr::instr_collect_columns; // collect columns to build a matrix row
				for (std::list<CInstr*>::iterator p = res_rtl_list.begin (); p != res_rtl_list.end (); p++)
				{
				  CInstr *elt = *p;
				  iCollectColumns.appendpar(elt->outreg);
				}
				res_rtl = ilist->append(iCollectColumns);
	};

void T_expr_col::generate_rtl_node(CInstrList *ilist) // colon
	{

		CIReg reg_base=0,reg_limit=0,reg_increment=0;
		if (op_base)
		{		
			op_base->generate_rtl(ilist);
			if(op_base->res_rtl)
			reg_base=op_base->res_rtl->outreg;
		}
		if (op_limit)
		{		
			op_limit->generate_rtl(ilist);
			if(op_limit->res_rtl)
			reg_limit=op_limit->res_rtl->outreg;
		}
		if (op_increment)
		{		
			op_increment->generate_rtl(ilist);
			if(op_increment->res_rtl)
			reg_increment=op_increment->res_rtl->outreg;
		}
	/////
		CInstr i;
		i.outreg=ilist->get_new_reg();
		i.m_inst_type = CInstr::instr_create_colon;

		bool bRemoveBase=false;
		if (op_base && op_limit && op_increment)
		{
			i.appendpar(reg_base);
			i.appendpar(reg_increment);
			i.appendpar(reg_limit);
		}
		else
			if(op_base && op_limit)
			{
				i.appendpar(reg_base);
				i.appendpar(reg_limit);
			}
			else
				if (op_base)
				{
					bRemoveBase=true;
					res_rtl =op_base->res_rtl;
				}
				else
				{
					// invalid
				}
		if(bRemoveBase==false)
		{
			res_rtl=ilist->append(i);// colon instruction
		}

	};

void T_expr_index::mark_as_lhs_in_assignment()
  {
	  generic_tree *gt=m_e;
	  m_is_lhs_in_assignment=true;
	  if (gt != NULL)
	  {
		  if (gt->is_identifier())
		  {
				T_ident *tid = (T_ident*)gt;
				tid->mark_as_lhs_in_assignment();
				return;
		  }
		  else
		  {
			  if (gt->is_expr_gen())
			  {
				T_expr_gen *te = (T_expr_gen*)gt;
				if (te->is_expr_index())
				{
					T_expr_index *tie = (T_expr_index*)te;
					tie->mark_as_lhs_in_assignment();
					return;
				}
			  }
		  }
	  }
	  // mark the identifier HSKOST_HAZARD_TODO
	  //if (m_lhs->is_identifier())
	  //{
	  // T_ident *tid = (T_ident*)m_lhs;
	  // tid->mark_as_lhs_in_assignment();
	  //}
  };

void	T_expr_index::mark_mag_end()
  {
	  struct CIRegEx mat_reg;
	  int dim=0;
	  int ndims=0;
	  T_ident *tid=NULL;

	  if(m_e)
	  {
		  	if (m_e->is_identifier())
			{
				mat_reg.r.varname=((T_ident*)m_e)->name();
				mat_reg.is_mat_name=true;
			}
			else
				// if index expression
			{
				mat_reg.r.reg = m_e->res_rtl->outreg;
				mat_reg.is_mat_name=false;
			}

		if(m_arg_list)
		{
			  ndims = m_arg_list->length();

			L_args::iterator p=m_arg_list->begin();
			while ( p != m_arg_list->end() ) 
			{
					T_expr_gen *tee;
					tee = (T_expr_gen *)*p;
					tee->mark_mag_end(mat_reg,dim+1,ndims);
					p++;dim++;
			}

		}
	  }
	    // find if magic end is used in index and call put_mag_end_info().
  }
void T_expr_index::generate_rtl_node(CInstrList *ilist)//index or field name
	{
		CInstr i;
		std::string base_id_name="?";
		bool bIsSimpleIndex=false;

				if (m_e)
				{
					m_e->generate_rtl(ilist);
				}
				if(m_e)
				if (m_e->is_identifier())
				{
					T_ident *tid=(T_ident*)m_e;
					base_id_name = tid->name();
					bIsSimpleIndex=true;
				}

		//HAZARD: if we call the function with one output - we must create res_rtl correctly.
		if (m_arg_list)
		{

				// Create index operator
				// HAZARD: 1. must recognize between SET and GET
				//         2. For function call must use another instruction type.
				//         3. For function without arguments - must treat in IDENT
				//		   4. Number of output argument - must get from parent expression (multy-assignment or not)  

				bool bIs_FuncName=false;
				int  nNumFuncArgIn=-1;
				int  nNumFuncArgOut=-1;


				if(TmcSymbolTable.is_variable(base_id_name)==false && bIsSimpleIndex)
				{
					bIs_FuncName=true;
					TmcSymbolTable.get_func_pars_num(base_id_name,&nNumFuncArgIn,&nNumFuncArgOut);
				}
				else
				{
				}


				if(bIs_FuncName==false)
				{//HAZARD_TODO: in case of mult-level-indexing must find last register and put its name in place of identifier. 
				 // this code was	already generated!			
					mark_mag_end();  // find if magic end is used in index and call put_mag_end_info().
					m_arg_list->generate_rtl_list(ilist);
					res_rtl =ilist->append_index(m_e->res_rtl->outreg,m_arg_list->res_rtl_list,is_lhs_in_assignment(),is_cell_index());

				}
				else
				{
					// special treatment for some in-built functions
					if (base_id_name.compare("isfield")==0)
					{
						L_args *input_list = this->arg_list();
						if (input_list->length()==2)
						{
						L_args::iterator p=input_list->begin();
						T_expr_gen *te_struct = *p++;
						T_expr_gen *te_fn = *p;
							//if (te_struct->is_expr_colession() && te_fn->is_expr_colession())
							//{
								/*if( ((T_expr_col*)te_struct)->base()->is_identifier() &&
									((T_expr_col*)te_fn)->base()->is_constant())
								{
									T_ident *te = (T_ident *)((T_expr_col*)te_struct)->base();
									std::string strname=te->name();
									T_const *tc=(T_const*)((T_expr_col*)te_fn)->base();
									std::string fnname=tc->val.m_string;
									res_rtl = ilist->append_isfield_call(strname,fnname);// isfield(strname,fnname)
									return;
								}
								else*/
								if (te_fn->baseexpr()->is_constant())
								{
									//T_ident *te = (T_ident *)((T_expr_col*)te_struct)->base();
									//std::string strname=te->name();
									
									te_struct->generate_rtl(ilist);
									
									T_const *tc=(T_const*)te_fn->baseexpr();
									std::string fnname; 
									AssignMtoStr(fnname,tc->val);
									res_rtl = ilist->append_isfield_call(te_struct->res_rtl->outreg,fnname);// isfield(strname,fnname)
									return;

								}

							//}

						}
					}
					if (base_id_name.compare("save")==0)
					{
						T_expr_index * rh_index_exp=this;
						L_args *input_list = rh_index_exp->arg_list();
						if (input_list->length()>1)  // save FileName var1 ...
						{
						L_args::iterator p=input_list->begin();
						T_expr_gen *te_struct = *p++;
						T_expr_gen *te_fn;// = *p; 

						te_struct->generate_rtl(ilist);
						CInstr iSaveFunc;
							iSaveFunc.outreg = te_struct->res_rtl->outreg;// output register used for the filename
							iSaveFunc.m_inst_type = CInstr::instr_save_call;
							iSaveFunc.m_ident_name = "save";
							iSaveFunc.max_nargin=nNumFuncArgIn; // maximal input accoding to symtab
							iSaveFunc.max_nargout=nNumFuncArgOut; // maximal input accoding to symtab

						 while (p != input_list->end())
						 {
							te_fn = *p;
							if (te_fn->is_constant())
							{
									T_const *tc=(T_const*)te_fn;
									std::string fnname;
									AssignMtoStr(fnname,tc->val);
									iSaveFunc.append_argin(fnname);
							}
							else if ( te_fn->baseexpr()->is_constant())
							{
									T_const *tc=(T_const*)te_fn->baseexpr();
									std::string fnname;
									AssignMtoStr(fnname,tc->val);
									iSaveFunc.append_argin(fnname);
							}
							else
							{
							Compiler.LogErr(3, "invalid call to SAVE()","save", m_line,true);
							}
							p++;
						 }
  						 res_rtl = ilist->append_save_call(iSaveFunc);// save (FileName,'Var1',...)
						 return ;
					    }
					    else
					    {
							Compiler.LogErr(3, "invalid call to SAVE()","save", m_line,true);
						}
					}

					// general case
						T_expr_index * rh_index_exp=this;//(T_expr_index *)rh_exp->base();
						L_args *input_list = rh_index_exp->arg_list();
						input_list->generate_rtl_list(ilist);
						res_rtl = ilist->append_func_call(nNumFuncArgIn,nNumFuncArgOut,m_num_out_pars,base_id_name,&input_list->res_rtl_list);
				
						if (res_rtl->max_nargin>=0 && res_rtl->nipars > res_rtl->max_nargin)
						{
							Compiler.LogErr(11, "Invalid number input parameters in call",res_rtl->m_ident_name, m_line,true);
							//fprintf(stderr,"\n **Error: Invalid number input parameters in call %s, in %s at line %d\n",res_rtl->m_ident_name.c_str(),c_file_name.c_str(),m_line);
							//if (Compiler.bUseDumpFile) fprintf(dump_file,"\n **Error: Invalid number input parameters in call %s, in %s at line %d\n",res_rtl->m_ident_name.c_str(),c_file_name.c_str(),m_line);
						}
						if (res_rtl->max_nargout>=0 && res_rtl->nipars_out > res_rtl->max_nargout)
						{						
							Compiler.LogErr(12, "Invalid number output parameters in call",res_rtl->m_ident_name, m_line,true);
							//fprintf(stderr,"\n **Error: Invalid number output parameters in call %s, in %s at line %d\n",res_rtl->m_ident_name.c_str(),c_file_name.c_str(),m_line);
							//if (Compiler.bUseDumpFile) fprintf(dump_file,"\n **Error: Invalid number output parameters in call %s, in %s at line %d\n",res_rtl->m_ident_name.c_str(),c_file_name.c_str(),m_line);
						}
				}
		}
		else
		{
			if (m_is_fn)
			{
				res_rtl=ilist->append_field(m_e->res_rtl->outreg,m_fn,is_lhs_in_assignment());
				
				//int reg1=m_lhs->res_rtl->outreg;
				//char buf[100];
				//std::string rtl_fmt="(GET_FIELD reg%d reg%d %s)"; 
				//i.outreg=list->get_new_reg();
				//sprintf_s(buf,99,rtl_fmt.c_str(),i.outreg,reg1,m_fn.c_str());
				//i.m_text = buf;
				//list->push_back(i);
				//res_rtl =&list->back();
			}
			else
			if (Compiler.bUseDumpFile) fprintf(dump_file,"<unknown index expression />\n");
		}

	};
void T_expr_assign_one::generate_rtl_node(CInstrList *ilist)// assignement
	{
		CInstr i,*i_op1,*i_op2;
		rhs->generate_rtl(ilist);
		i_op2 =rhs->res_rtl;
		lhs->generate_rtl(ilist);
		i_op1 =lhs->res_rtl;
		int reg1=0;
		int reg2=0;
		if (i_op1) reg1=i_op1->outreg;
		if (i_op2) reg2=i_op2->outreg;
		// HAZARD: only for =, actually other types are not supported at all by matlab.
		res_rtl = ilist->append_assignment(reg1,reg2);
	};
void T_expr_assign_many::generate_rtl_node(CInstrList *ilist)
	{
		rhs->generate_rtl(ilist); // genetate righ-side expression code.
		CInstr iFunCall=ilist->back();

		// generate assignments to member from lhs list from each argument of the function.
		L_args::iterator p=lhs->begin();
		std::list<CIReg>::iterator pRhs = iFunCall.ipars_out.begin(); 
		CIReg reg1;
		while ( p != lhs->end() ) 
		{
			T_expr_gen *elt= *p;
			elt->generate_rtl(ilist);
			CIReg reg2=elt->res_rtl->outreg;
			
			if (pRhs != iFunCall.ipars_out.end())
			{
			 reg1 = *pRhs;
			}
			else
			{
				Compiler.LogErr(2, "invalid multi-assignment",get_rhs_name(), m_line );
				res_rtl =ilist->append_syntax_error(m_line,1,"**Error: invalid multi-assignment");
			return;
			}
			// assignment
			res_rtl =ilist->append_assignment(reg2,reg1);
			p++;pRhs++;
		}
};
void tree_matrix::generate_rtl_node(CInstrList *ilist)// matrix
	{
		        generate_rtl_list(ilist,is_cell_matrix());
				CInstr iCollectRows;
				iCollectRows.outreg = ilist->get_new_reg();// output register

				if (is_cell_matrix())
				{
					iCollectRows.m_inst_type = CInstr::instr_collect_cell_rows; // collect rows to build a cell-matrix
					//rtl_fmt="(SET reg%d (ADD_CELL_ROWS  %d "; 
				}
				else
				{
					iCollectRows.m_inst_type = CInstr::instr_collect_rows; // collect rows to build a matrix
					//rtl_fmt="(SET reg%d (ADD_MATRIX_ROWS  %d "; 
				}
				for (std::list<CInstr*>::iterator p = res_rtl_list.begin (); p != res_rtl_list.end (); p++)
				{
				  CInstr *elt = *p;
				  iCollectRows.appendpar(elt->outreg);
				}
				res_rtl = ilist->append(iCollectRows);
	};
void T_expr_bin::generate_rtl_node(CInstrList *ilist)// binary operation
	{
		CInstr iBinaryOp,*i_op1,*i_op2;

		op_lhs->generate_rtl(ilist);
		op_rhs->generate_rtl(ilist);

		iBinaryOp.outreg=ilist->get_new_reg();
		i_op1 = op_lhs->res_rtl;
		i_op2 = op_rhs->res_rtl;
		CIReg reg1=0;
		CIReg reg2=0;
		if (i_op1) reg1=i_op1->outreg;
		if (i_op2) reg2=i_op2->outreg;


		iBinaryOp.BinaryInstrType(op_type()); // get inst type from the string
		iBinaryOp.appendpar(reg1);
		iBinaryOp.appendpar(reg2);
		res_rtl =ilist->append(iBinaryOp);
	};

void T_expr_bool::generate_rtl_node(CInstrList *ilist)// boolean expression
	{
		CInstr iBooleanOp,*i_op1,*i_op2;
		CIReg reg1=0;
		CIReg reg2=0;

		iBooleanOp.igoto_label=ilist->get_new_label();
		iBooleanOp.outreg = ilist->get_new_reg();

		op_lhs->generate_rtl(ilist);
		i_op1 = op_lhs->res_rtl;
		if (i_op1) reg1=i_op1->outreg;
		//res_rtl =ilist->append_assignment_bool(iBooleanOp.outreg,reg1);

		if (op_type()==bool_operation_and)
			ilist->append_assign_false_and_branch_if_false(iBooleanOp.outreg,reg1,iBooleanOp.igoto_label,"return(false) boolean_and expr");
		else // bool_or
			ilist->append_assign_true_and_branch_if_true(iBooleanOp.outreg,reg1,iBooleanOp.igoto_label,"return(true) boolean_or expr");

		op_rhs->generate_rtl(ilist);
		i_op2 = op_rhs->res_rtl;
		if (i_op2) reg2=i_op2->outreg;
		res_rtl =ilist->append_assignment_bool(iBooleanOp.outreg,reg2);
		ilist->append_label(iBooleanOp.igoto_label,"end boolean expr");
	};
void T_expr_unar::generate_rtl_node(CInstrList *list)// unary operation
	{
		CInstr iUnaryOp;
		op->generate_rtl(list);

		iUnaryOp.outreg=list->get_new_reg();
		CIReg reg1=0;
		if (op->res_rtl) reg1=op->res_rtl->outreg;

		iUnaryOp.UnaryInstrType(op_type); // get inst type from the string
		iUnaryOp.appendpar(reg1);
		res_rtl =list->append(iUnaryOp);
	};
void T_vardecl::generate_rtl_node(CInstrList *list)
	{
			id->generate_rtl_node(list);
	};
void L_funcpar::generate_rtl_list(CInstrList *list,bool bIsCellRow)
	{
		// generate code for function parameters.
		// Actually nothing todo, maybe must generate code to store parameters.
	}
void T_func_block::generate_rtl_node(CInstrList *ilist)
	{
// add stored vars to the symbol table
	if (param_list != NULL)
	for ( L_funcpar::iterator p=param_list->begin(); p != param_list->end(); p++)
	{
		T_vardecl* elt = *p;
		std::string out_par_name = elt->id->name();
		//! Here is a special processing for output parameters
		if (TmcSymbolTable.is_assigned_param(out_par_name) || (ret_list !=NULL && ret_list->is_in_arg(out_par_name))) /// if  is in LHS (not only ret_list->is_in_arg(out_par_name) )
		{
			elt->IsStoredInputPar(true);
			// Add a new var to the symbol table. 
			// append_var_decl and clear_local_vars MUST be called later.
			
			//std::string stored_par_name = elt->id->name().append(CInstrList::stored_var_suf);
			//symbol_table::insert_name(stored_par_name);
			//symbol_table::insert_name(out_par_name);
			if ( (ret_list ==NULL) || ret_list->is_in_arg(out_par_name)==false)
			{
					TmcSymbolTable.force_variable(out_par_name,VAR_ATTR_DEFAULT,Compiler.indFunc_RTL);// remove from formal parameters
			}
		}
		else
		{
			elt->IsStoredInputPar(false);
		}

		if (TmcSymbolTable.mark_initialized_var(elt->id->name()) ==false)
		{
			Compiler.LogErr(1, "overridding assignment is not allowed",elt->id->name(), m_line);
		}
	}
// generate function declaration
		int fnc_exit_label = ilist->get_new_label();// for exit (return implementation)
		ilist->append_func_decl(name(),param_list,ret_list);//may also generate additional varibles for storage
//generate vars declarations
		ilist->append_var_decl();
		param_list->generate_rtl_list(ilist);
		ret_list->generate_rtl_list(ilist);
// generate the store for input parameters if needed
		ilist->append_store_input_vars(param_list,ret_list);
// protect clean-up against non-handled exceptions
		if (Compiler.support_try_catch)
		{
			ilist->append_tryfinal_try();
		}
// create debug information frame
		if (Compiler.debuginfo)
		{
		ilist->append_debug_pushstackvars(name(),param_list,ret_list);
		}
// generate the function code
		stmt_list->generate_rtl_list(ilist);
// generate  function end
		ilist->append_label(fnc_exit_label,"end Function");
		if (Compiler.support_try_catch)
		{
		// clean-up against exceptions
		ilist->append_finally();
		}
		ilist->append_restore_input_vars(param_list,ret_list);// restore input vars and assign to output vars
		ilist->append_clear_local_vars();

// clear debug information frame
		if (Compiler.debuginfo)
		{
			int numpars=0;
			if (param_list !=NULL)
				numpars += param_list->length();
			if (ret_list !=NULL)
				numpars += ret_list->length();
			ilist->append_debug_popstackvars(numpars);
		}
		if (Compiler.support_try_catch)
		{
		// clean-up against exceptions
		ilist->append_endfinally();// end of finally block
		}

				 ilist->append_block_end();
		res_rtl =ilist->append_fnc_end(name());

	};
void T_func_hdr::generate_rtl_node(CInstrList *list)
	{
		CInstr i;
		m_f->generate_rtl(list);
		std::string str="//FUNCTION DEFINITION ENDED";
		i.m_text = str.c_str();
		list->push_back(i);
	};
///////////// CTRL /////////////////////
void T_cmd_ctrl_return::generate_rtl_node(CInstrList *ilist)
	{
		ilist->append_goto(get_fnc_exit_ilabel(),"branch to FUNCTION exit");//goto to the end of the Function 
	};
void T_cmd_decl_gen::generate_rtl_node(CInstrList *list)
	{
		
		//CInstr i;
		//std::string str="//DECL";
		//i.m_text = str.c_str();
		//list->push_back(i);
	};

void T_cmd_ctrl_label::generate_rtl_node(CInstrList *list)
{
		CInstr i;
		std::string str=m_type.c_str();
		i.m_text = "//";
		i.m_text.append(str.c_str());
		list->push_back(i);
};
//// switch ////
void T_sw_case::calc_label_value(void)
  {
	// create label_value list of constant values for case label CASE C  or CASE {'C','B'}
	//e.g.:
	sw_case_val c;

	//T_expr_col *tce=(T_expr_col *)label;
	T_expr_gen *tbe =label->baseexpr();// tce->base();
	
	//tree_cell *tcl = tbe;
	if (tbe->is_constant() || 	tbe->is_expr_unar())
	{			
		if (tbe->is_constant())
		{
						T_const *tc1=(T_const*)tbe;
						if (_tmcIsChar(tc1->val))
						{
								c.m_type='s';
								AssignMtoStr(c.m_str,tc1->val);
								label_value.push_back(c);
						}
						else
						{
								c.m_type='d';
								c.m_scalar=tc1->val->value.complx.rData[0];
								label_value.push_back(c);
						}
		}
		else
		{
			T_expr_unar *tue =(T_expr_unar*)tbe;
			T_const *tc1=(T_const*)tue->get_operand();
								c.m_type='d';
								if (tue->get_operation()==unary_operation_uminus)
									c.m_scalar= - tc1->val->value.complx.rData[0]; // expression was unary minus
								else
								{
										c.m_scalar=tc1->val->value.complx.rData[0];
												fprintf(stderr,"not unary minus\n");

								}
								label_value.push_back(c);

		}
	}
	else
	{
	tree_matrix *tm = (tree_matrix *)tbe;

	
	if(tm->is_cell_matrix())
	{
		tree_matrix *tcl = (tree_matrix*)tm;
		for (tmclsp_list<L_args *>::iterator p= tcl->begin();p !=tcl->end();p++)
		{
				L_args *tal= *p;
				for (tmclsp_list<T_expr_gen *>::iterator q= tal->begin();q !=tal->end();q++)
				{
						T_expr_gen *te1=*q;
						//T_expr_col *tce1=(T_expr_col *)te1;
						T_const *tc1=(T_const*)te1->baseexpr();//tce1->base();
						if (_tmcIsChar(tc1->val))
						{
								c.m_type='s';
								AssignMtoStr(c.m_str, tc1->val);
								label_value.push_back(c);
						}
						else
						{
								c.m_type='d';
								c.m_scalar=tc1->val->value.complx.rData[0];
								label_value.push_back(c);
						}
				}
		}

	}
	else
	{
		fprintf(stderr,"not cellAAAAAAAAAA\n");
	}
	}
  }
T_expr_gen * T_sw_case::get_switch_expression()
{// access switch(expr) from case
		T_expr_gen* resval;
		T_ctrl_cmd_switch *tsc=  (T_ctrl_cmd_switch*) parent()->parent();
		resval=tsc->get_expr();
		return resval;
}
CIReg  T_sw_case::get_switch_expression_val()
{
		T_ctrl_cmd_switch *tsc=  (T_ctrl_cmd_switch*) parent()->parent();
		return tsc->get_exp_val_reg();
}

void T_sw_case::generate_rtl_node(CInstrList *ilist)
	{
		// generate a label to the end of the clause
		CILabel LabelEndClause=ilist->get_new_label();
		CILabel LabelBeginClause=ilist->get_new_label();

		//// get expression
		//CIReg exp_reg=get_switch_expression()->res_rtl->outreg;
		CIReg exp_reg=get_switch_expression_val();
		if (label)
		{
			calc_label_value(); // calculate the label value
			for (std::list<sw_case_val>::iterator p = label_value.begin (); p != label_value.end (); p++)
			{
				sw_case_val v = *p;
				if (v.m_type=='s')
					res_rtl =	ilist->append_compare_case_s(exp_reg,v.m_str,LabelBeginClause,"goto to the begin of the CASE if  this case");
				else
					res_rtl =	ilist->append_compare_case_d(exp_reg,v.m_scalar,LabelBeginClause,"goto to the begin of the CASE if this case");
			}
					if(list)
						res_rtl =   ilist->append_goto(LabelEndClause,"branch to CASE end if not this case");
	
			//obsolete: 
			//label->generate_rtl(ilist);
			//if(label->res_rtl)
			//{
			//  res_rtl =	ilist->append_compare_case(exp_reg,label->res_rtl->outreg,LabelEndClause,"goto to the end of the CASE if not this case");
			//}
		}
		else //otherwise clause
		{

		}
		//// get the instruction list
		ilist->append_label(LabelBeginClause,"begin CASE");
		if(list)
		{
			//A3. Do the instructions
			list->generate_rtl_list(ilist);
			if(label)
			{
			//A4. Branch to the end after the instructions are done 
			ilist->append_goto(ilabel_end,"branch to SWITCH end");
			}
		}
		// put a label at the end of the clause
		ilist->append_label(LabelEndClause,"end CASE");

		//CInstr i;
		//std::string str="case";
		//i.m_text = str.c_str();
		//list->push_back(i);
	};
void T_ctrl_cmd_switch::generate_rtl_node(CInstrList *ilist)
	{
		//evaluate the expression
		expr->generate_rtl(ilist);
		// calculate the switch expression value (string hcode or double)
		res_rtl = ilist->append_calc_switch_exp_value(expr->res_rtl->outreg);
		exp_val_reg=res_rtl->outreg;
		// generate "CASE" clauses
			int LabelEndSwitch = ilist->get_new_label();// if end label
			// assign the lable to all the members
			for (LT_sw_cases::iterator p = list->begin (); p != list->end (); p++)
			{
				T_sw_case *elt = *p;
				elt->ilabel_end=LabelEndSwitch; 
			}
		    list->generate_rtl_list(ilist);
			// put a label at the end of the SWITCH
			ilist->append_label(LabelEndSwitch,"end SWITCH");
	};
////////// if /////////
void T_if_block::generate_rtl_node(CInstrList *ilist)// if clauses
	{
		// generate a label to the end of the clause
		CILabel LabelEndClause=ilist->get_new_label();


	//// get expression
		if(expr)
		{
			//CInstr i2;
			//char buf2[100];
			//std::string rtl_fmt2="(IF_EXPR ";
			//sprintf_s(buf2,99,rtl_fmt2.c_str());
			//i2.m_text =buf2;
			//ilist->push_back(i2);
			//res_rtl =&ilist->back();

			// A1. Calculate expression
			//CInstr i,*i_expr;
			//i.outreg=ilist->get_sr_reg();
			expr->generate_rtl(ilist);
			//i_expr = expr->res_rtl;
			//int reg1=0;
			//if (i_expr) reg1=i_expr->outreg;
			// A2. Test the expression result, branch to end if false.
			
			if(expr->res_rtl)
			{
			  res_rtl = ilist->append_branch_if_false(expr->res_rtl->outreg,LabelEndClause,"goto to the end of the clause if the expression is false");
			}

			//std::string rtl_fmt="(SET SR (IF_TRUE reg%d))\n)\n(IF_SR_BLOCK_START)";
			//char buf[100];
			//sprintf_s(buf,99,rtl_fmt.c_str(),reg1);
			//i.m_text =buf;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();


		}
		else
		{// this is an else clause


			//CInstr i;
			//std::string rtl_fmt="(IF_ELSE_BLOCK_START)";
			//char buf[100];
			//sprintf_s(buf,99,rtl_fmt.c_str());
			//i.m_text =buf;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();
		}
	//// get the instruction list
		if(list)
		{
			//A3. Do the instructions
			list->generate_rtl_list(ilist);
			if(expr)
			{
			//A4. Branch to the end after the instructions are done 
			//CInstr i;
			//std::string rtl_fmt="(GO_TO label%d)";
			//char buf[100];
			//int ilabel = this->ilabel_end;
			//sprintf_s(buf,99,rtl_fmt.c_str(),ilabel);
			//i.m_text =buf;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();

			ilist->append_goto(ilabel_end,"branch to end IF");

			//std::string rtl_fmt3="(IF_BLOCK_END)";
			//sprintf_s(buf,99,rtl_fmt3.c_str());
			//i.m_text =buf;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();

			}
		}
		// put a label at the end of the clause
		ilist->append_label(LabelEndClause,"end IF clause");

			//CInstr i;
			//std::string rtl_fmt="(IF_ELSE_BLOCK_END)";
			//char buf[100];
			//sprintf_s(buf,99,rtl_fmt.c_str());
			//i.m_text =buf;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();

	};
void T_ctrl_cmd_if::generate_rtl_node(CInstrList *ilist)// if command
	{
		// generate "IF" clauses
			int LabelEndIF = ilist->get_new_label();// if end label
			// assign the lable to all the members
			for (LT_if_blocks::iterator p = list->begin (); p != list->end (); p++)
			{
				T_if_block *elt = *p;
				elt->ilabel_end=LabelEndIF; 
			}


		    list->generate_rtl_list(ilist);

			// put a label at the end of the IF
			ilist->append_label(LabelEndIF,"end IF");

			//CInstr i;
			//std::string rtl_fmt="(LABEL label_%d)";
			//char buf[100];
			//sprintf_s(buf,99,rtl_fmt.c_str(),ilabel);
			//i.m_text =buf;
			//i.ilabel = ilabel;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();//if end label
	};
//////// while /////////
void T_ctrl_cmd_while::generate_rtl_node(CInstrList *ilist)// while
	{

		CILabel begin_ilabel = ilist->get_new_label();// while begin label
		m_end_ilabel = ilist->get_new_label();// while end label
		m_exit_ilabel = ilist->get_new_label();// while exit label


			ilist->append_label(begin_ilabel,"WHILE expression");

			// W.1 Calculate expression
			CInstr iWhileExpr;


			//CInstr i2;
			//char buf[100];
			//std::string rtl_fmt2="(WHILE_EXPR ";
			//sprintf_s(buf,99,rtl_fmt2.c_str());
			//i2.m_text =buf;
			//ilist->push_back(i2);
			//res_rtl =&ilist->back();

			//CInstr i,*i_expr;
			//i.outreg=ilist->get_sr_reg();
			expr->generate_rtl(ilist);
			// W.2 	Test the expression result, branch to end if false.
			
			if(expr->res_rtl)
			{
			  res_rtl =ilist->append_branch_if_false(expr->res_rtl->outreg,m_exit_ilabel,"goto to the exit of the while if the expression is false");
			}


			//i_expr = expr->res_rtl;
			//int reg1=0;
			//if (i_expr) reg1=i_expr->outreg;
			//std::string rtl_fmt="(SET SR (IF_TRUE reg%d))\n)\n(WHILE_SR_BLOCK_START)";
			//sprintf_s(buf,99,rtl_fmt.c_str(),reg1);
			//i.m_text =buf;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();

			// W.3 Do the instructions
			list->generate_rtl_list(ilist); 


		// end of while label
			ilist->append_label(m_end_ilabel,"end WHILE");
		// W.4 Branch to the while expression calculation
			ilist->append_goto(begin_ilabel,"branch to test WHILE expression");

			//std::string rtl_fmt4="(LABEL while_end_label_%d)";
			//sprintf_s(buf,99,rtl_fmt4.c_str(),m_end_ilabel);
			//i.m_text =buf;
			//i.ilabel = m_end_ilabel;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();//if end label

			//std::string rtl_fmt3="(WHILE_BLOCK_END)";
			//sprintf_s(buf,99,rtl_fmt3.c_str());
			//i.m_text =buf;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();

		// exit of while label
			ilist->append_label(m_exit_ilabel,"exit WHILE");

			//std::string rtl_fmt5="(LABEL while_exit_label_%d)";
			//sprintf_s(buf,99,rtl_fmt5.c_str(),m_exit_ilabel);
			//i.m_text =buf;
			//i.ilabel = m_exit_ilabel;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();//if end label

	};
/////////// continue //
void T_ctrl_cmd_continue::generate_rtl_node(CInstrList *ilist)// continue
	{
		T_cmd_gen *twc = this->get_parent_while(this);
		if (twc)
		{
			//int ilabel = twc->m_end_ilabel;
			//CInstr i;
			//std::string rtl_fmt="(GO_TO label%d)";
			//char buf[100];
			//sprintf_s(buf,99,rtl_fmt.c_str(),ilabel);
			//i.m_text =buf;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();

			ilist->append_goto(twc->end_ilabel(),"continue to WHILE end");
		}
		else
		{
			Compiler.LogErr(7, "continue out of while/for","continue", m_line,true);
			//if (Compiler.bUseDumpFile) fprintf(dump_file,"**** SYNTAX ERROR: continue out of while/for ******"); 
		}
	};
////////// break //////////
void T_ctrl_cmd_break::generate_rtl_node(CInstrList *ilist)//break
	{

		T_cmd_gen *twc = this->get_parent_while(this);
		if (twc)
		{
			//int ilabel=twc->m_exit_ilabel;

			//CInstr i;
			//std::string rtl_fmt="(GO_TO label%d)";
			//char buf[100];
			//sprintf_s(buf,99,rtl_fmt.c_str(),ilabel);
			//i.m_text =buf;
			//ilist->push_back(i);
			//res_rtl =&ilist->back();

			ilist->append_goto(twc->exit_ilabel(),"break to WHILE exit");
		}
		else
		{	Compiler.LogErr(8, "break out of while/for","break", m_line,true);
			//if (Compiler.bUseDumpFile) fprintf(dump_file,"\n****** SYNTAX ERROR: BREAK not inside a while/for *******\n");
		}
	};
//////////////// FOR ////////////
void T_ctrl_cmd_for::generate_rtl_node(CInstrList *ilist)
	{
		m_end_ilabel = ilist->get_new_label();// while end label
		m_exit_ilabel = ilist->get_new_label();// while exit label
		CILabel for_start_ilabel = ilist->get_new_label();// do start label
		std::string it_varname=((T_ident*)(this->lhs->baseexpr()))->name();
		if (TmcSymbolTable.mark_initialized_var(it_varname)==false)
		{
			Compiler.LogErr(1, "overridding assignment is not allowed",it_varname, m_line);
		}


		expr->generate_rtl(ilist);

		ilist->append_for_init_next(it_varname,expr->res_rtl->outreg,for_start_ilabel,m_exit_ilabel);

//		CInstr iIteratorInit;
//		CIReg regIter=ilist->get_new_reg();
//		iIteratorInit.m_inst_type= CInstr::instr_for_init;
//		iIteratorInit.m_ident_name = ((T_ident*)((T_expr_col*)(this->lhs))->base())->name();
//		iIteratorInit.appendpar(regIter); //iterator
//		iIteratorInit.appendpar(expr->res_rtl->outreg);// init expression
//		ilist->append(iIteratorInit);
//		
//		// do start label
//			ilist->append_label(for_start_ilabel,"FOR begin");
//
//		// for-next
//		CInstr iIteratorNext;
//		iIteratorNext.m_inst_type= CInstr::instr_for_next;
//		iIteratorNext.appendpar(regIter); //iterator
//		iIteratorNext.appendpar(expr->res_rtl->outreg);// init expression
//		iIteratorNext.igoto_label=m_exit_ilabel;
//		ilist->append(iIteratorNext);



		if(list)
			list->generate_rtl_list(ilist); 

		// end of for label
			ilist->append_label(m_end_ilabel,"FOR end");
		// go to start
			ilist->append_goto(for_start_ilabel,"branch to FOR begin");
		// exit of FOR label
			ilist->append_label(m_exit_ilabel,"FOR exit");
	};
/// try-catch /////////
void T_ctrl_cmd_try_catch::generate_rtl_node(CInstrList *ilist)
	{
		CILabel LabelExcHandler = ilist->get_new_label();
		CILabel LabelNoExceptionExcHandler = ilist->get_new_label();
		CILabel LabelExceptionHandledExcHandler = ilist->get_new_label();


		ilist->append_try(LabelExcHandler);
		try_code->generate_rtl_list(ilist);
		ilist->append_catch(LabelExcHandler,LabelNoExceptionExcHandler);

		if (catch_code)
		{
		catch_code->generate_rtl_list(ilist);
		}
		ilist->append_endcatch(LabelExceptionHandledExcHandler,LabelNoExceptionExcHandler);
	};
///////////
//////////// tree ///////////
T_cmd_gen* T_cmd_gen::get_parent_while(T_cmd_gen *t)
	{// get the inner while/for/do-until of a command
		T_cmd_gen *twc=NULL;

		T_stmnt_gen *ts = (T_stmnt_gen *)t->parent();
		L_stmnt_gen *tsl = (L_stmnt_gen *)ts->parent();
	
		generic_tree *gt=tsl;
		int ilabel=0;
		while (gt)
		{
			gt=gt->parent();
			if (gt==NULL)
				break;
			if (gt->is_while_command())
			{
				twc = (T_cmd_gen *)gt;
				break;
			}
		}
		return twc;
	}
///////////////////
CInstr::instr_types CInstr::BinaryInstrType(enum operation_types op)
{
instr_types res=instr_nothing;

	switch (op)
	{
	case operation_add:
		res = instr_add;
		break;
	case operation_sub:
		res = instr_sub;
		break;

	case operation_mul:
		res = instr_mul;
		break;

	case operation_el_mul:
		res = instr_el_mul;
		break;

	case operation_el_or:
		res = instr_el_or;
		break;

	case operation_el_and:
		res = instr_el_and;
		break;
	
	case operation_div:
		res = instr_div;
		break;

	case operation_el_div:
		res = instr_el_div;
		break;
	case operation_pow:
		res = instr_pow;
		break;
	case operation_el_pow:
		res = instr_el_pow;
		break;
	case operation_ldiv:
		res = instr_ldiv;
		break;
	case operation_el_ldiv:
		res = instr_el_ldiv;
		break;
	case operation_le:
		res = instr_le;
		break;
	case operation_lt:
		res = instr_lt;
		break;
	case operation_ge:
		res = instr_ge;
		break;
	case operation_gt:
		res = instr_gt;
		break;
	case operation_ne:
		res = instr_ne;
		break;
	case operation_eq:
		res = instr_eq;
		break;


	}
		this->m_inst_type=res;

return res;
}
/*
CInstr::instr_types CInstr::BinaryInstrType(std::string op)
{// set instruction type
	instr_types retval = instr_nothing;
	int len=op.length();
	const char *str=op.c_str();
	char c1;
	bool bScalar=false;
	bool bEq=false;

	if (len==2 )
	{
		if(str[0]=='.')
		{
		 c1=str[1];
		 bScalar=true;
		}
		else
		{
			bEq=true;
			c1=str[0];
		}
	}
	else
		c1=str[0];

	switch (c1)
	{
	case '+':// plus
			retval=instr_add;
		break;
	case '-':// minus
			retval=instr_sub;
		break;
	case '*':// mtimes
		if (bScalar==false)
			retval=instr_mul;
		else
			retval=instr_el_mul;
		break;
	case '|':// or
			retval=instr_el_or;
		break;
	case '&':// and
			retval=instr_el_and;
		break;

	case '/':// mrdivide
		if (bScalar==false)
			retval=instr_div;
		else
			retval=instr_el_div;
		break;
	case '^':// mpower
		if (bScalar==false)
			retval=instr_pow;
		else
			retval=instr_el_pow;
		break;
	case '\\': // mldivide
		if (bScalar==false)
			retval=instr_ldiv;
		else
			retval=instr_el_ldiv;
		break;
	case '<': // lt | le
		if (bEq==true)
			retval=instr_le;
		else
			retval=instr_lt;
		break;
	case '>': // gt | ge
		if (bEq==true)
			retval=instr_ge;
		else
			retval=instr_gt;
		break;
	case '!': // ne
		retval=instr_ne;
		break;
	case '=': // eq
		retval=instr_eq;
		break;
//////////////////


	}
	this->m_inst_type=retval;
return retval;
}
*/
CInstr::instr_types CInstr::UnaryInstrType(enum unary_operation_types op)
{
	instr_types res=instr_nothing;
	switch (op)
	{
	case unary_operation_uplus:
		res = instr_uplus;
		break;
	case unary_operation_not:
		res = instr_not;
		break;
	case unary_operation_uminus:
		res = instr_uminus;
		break;
	case unary_operation_transpose:
		res= instr_transpose;
		break;
	case unary_operation_hermitian: // scalar transpose
		res = instr_hermitian;
		break;
	}
	this->m_inst_type=res;
	return res;
}
/*
CInstr::instr_types CInstr::UnaryInstrType(std::string op)
{// set instruction type
	instr_types retval = instr_nothing;
	int len=op.length();
	const char *str=op.c_str();
	char c1;
	bool bScalar=false;

	if (len==2)
	{
		c1=str[1];
		bScalar=true;
	}
	else
		c1=str[0];

	switch (c1)
	{
	case '+':// uplus
			retval=instr_uplus;
		break;
	case '!':// not
			retval=instr_not;
		break;
	case '-':// uminus
			retval=instr_uminus;
		break;
	case '\'':// transpose
		if (bScalar==false)
			retval=instr_transpose;
		else
			retval=instr_hermitian;
		break;
//////////////////


	}
	this->m_inst_type=retval;
return retval;
}
*/

CInstr::instr_types CInstr::BooleanInstrType(std::string op)
{// set instruction type
	instr_types retval = instr_nothing;
	int len=op.length();
	const char *str=op.c_str();
	char c1;

	c1=str[0];// only || and && exit 

	switch (c1)
	{
///////////////
	case '&':
		retval=instr_boolean_and;break;
	case '|':
		retval=instr_boolean_or;break;
	default: ;
	}
	this->m_inst_type=retval;
return retval;
}

CInstr* CInstrList::append_func_decl(std::string func_name,L_funcpar *param_list,
		L_funcpar *ret_list)
{
	CInstr iFunc;
	// generate function declaration
	iFunc.m_inst_type = CInstr::instr_func_declaration;
	iFunc.m_ident_name= func_name; // function name
	// build arguments list
	if (param_list !=NULL)
	for ( L_funcpar::iterator p=param_list->begin(); p != param_list->end(); p++)
	{
		T_vardecl* elt = *p;
		std::string act_in_par_name = elt->id->name();
		if (elt->IsStoredInputPar() )
		{
			act_in_par_name.append(input_var_suf);
		}
		iFunc.append_argin(act_in_par_name);
	}
	if (ret_list != NULL)
	for ( L_funcpar::iterator p=ret_list->begin(); p != ret_list->end(); p++)
	{
		T_vardecl* elt = *p;
		std::string act_out_par_name = elt->id->name();
		//if (param_list != NULL)
		//if (param_list->is_in_arg(act_out_par_name))
		//{
		//	act_out_par_name.append(out_var_suf);
		//	// Add a new var to the symbol table. 
		//	// append_var_decl and clear_local_vars MUST be called later.
		//	//std::string stored_par_name = elt->id->name().append(stored_var_suf);
		//	//symbol_table::insert_name(stored_par_name);
		//}
		iFunc.append_argout(act_out_par_name);
	}
	return append(iFunc);
}
CInstr* CInstrList::append_store_input_vars(L_funcpar *param_list,L_funcpar *ret_list)
{
	CInstr *ret_instr=NULL;
	// assign input-suffixed args to their named vars
	if (param_list != NULL)
	for ( L_funcpar::iterator p=param_list->begin(); p != param_list->end(); p++)
	{
		T_vardecl* elt = *p;
		std::string out_par_name = elt->id->name();
		//if (symbol_table::is_assigned_param(out_par_name)) /// if  is in LHS (not only ret_list->is_in_arg(out_par_name) )
		//{
		//	std::string stored_par_name = elt->id->name().append(stored_var_suf);
		//	ret_instr=append_assignment_var(stored_par_name,out_par_name);
		//}
		if (elt->IsStoredInputPar())
		{
			std::string input_par_name = elt->id->name().append(input_var_suf);
			ret_instr=append_copy_var(out_par_name,input_par_name);
		}
	}
	return ret_instr;
}
CInstr* CInstrList::append_restore_input_vars(L_funcpar *param_list,L_funcpar *ret_list)
{
	// assign to output args and restore the input vars
	CInstr *ret_instr=NULL;
	// assign output args
	//if (ret_list != NULL)
	//for ( L_funcpar::iterator p=ret_list->begin(); p != ret_list->end(); p++)
	//{
	//	T_vardecl* elt = *p;
	//	std::string act_out_par_name = elt->id->name();
	//	if (param_list != NULL)
	//	if (param_list->is_in_arg(act_out_par_name))
	//	{			
	//		act_out_par_name.append(out_var_suf);
	//		std::string stored_par_name = elt->id->name().append(stored_var_suf);
	//		ret_instr=append_assignment_var(act_out_par_name,elt->id->name());
	//	}
	//}
	// restore input args
	//if (param_list != NULL)
	//for ( L_funcpar::iterator p=param_list->begin(); p != param_list->end(); p++)
	//{
	//	T_vardecl* elt = *p;
	//	std::string act_out_par_name = elt->id->name();
	//	if (param_list->is_in_arg(act_out_par_name))
	//	{			
	//		act_out_par_name.append(out_var_suf);
	//		std::string stored_par_name = elt->id->name().append(stored_var_suf);
	//		ret_instr=append_assignment_var(elt->id->name(),stored_par_name);
	//	}
	//}

	return ret_instr;
}

////////// debug information support //////////
CInstr* CInstrList::append_debug_pushstackvars(std::string fnc_name,L_funcpar *param_list,L_funcpar *ret_list)
{
			CInstr i;
			i.m_inst_type= CInstr::instr_debuginfo_pushstackvars;
			i.n_argin=0;
			i.m_ident_name=fnc_name;

			// add input parameters
			if (param_list != NULL)
			for ( L_funcpar::iterator p=param_list->begin(); p != param_list->end(); p++)
			{
				T_vardecl* elt = *p;
				std::string out_par_name = elt->id->name();
				if (elt->IsStoredInputPar())
				{
					out_par_name = elt->id->name().append(input_var_suf);
					//ret_instr=append_copy_var(out_par_name,input_par_name);
				}
				i.append_argin(out_par_name);
			}
			// add output parameters
			if (ret_list != NULL)
			for ( L_funcpar::iterator p=ret_list->begin(); p != ret_list->end(); p++)
			{
				T_vardecl* elt = *p;
				std::string out_par_name = elt->id->name();
				i.append_argin(out_par_name);
			}
			// add local vars
			for (symbol_table::record_iterator p=TmcSymbolTable.SymList.begin();p!=TmcSymbolTable.SymList.end(); )
			{
				if (p->is_local_var(this->get_local_function_ind() ))
				{
					i.append_argin(p->name());// updates n_argin
				}
				p++;
			}


			return append(i);
}
CInstr* CInstrList::append_debug_popstackvars(int numpars)
{
			CInstr i;
			i.m_inst_type= CInstr::instr_debuginfo_popstackvars;

			// count all the local vars
			i.n_argin=numpars;
			for (symbol_table::record_iterator p=TmcSymbolTable.SymList.begin();
				p!=TmcSymbolTable.SymList.end(); )
			{
				if (p->is_local_var(this->get_local_function_ind() ))
				{
					i.n_argin++;
				}
				p++;
			}
			return append(i);
}
/// main generation /////////////////

CInstrList::iterator CInstrList::FindNextStmt(int *src_line,iterator p)
{// [in/out] p from which can seek for  CInstr::instr_end_statement
	while (p != end ())
	{
		CInstr elt = *p;
		if (elt.m_inst_type==CInstr::instr_end_statement)
		{
			*src_line=elt.src_line;
			p++;// go next instr of interest
			return p;
		}
		p++;
	}
	// really we did not found.
	*src_line = LAST_SRC_LINE;
	return p;
}

static int last_printed;
char src_line_buff[1000];
void CInstrList::PrintSrcLines(FILE *file_output,FILE *file_in,int src_line1,int src_line2,char out_fmt)
{
	int k;
	char *stat;
	int xsrc_line2 = (src_line2== LAST_SRC_LINE)? src_line1 : src_line2;

	if (out_fmt=='c')
	fprintf(file_output,"// %% Lines %d--%d:\n",src_line1,xsrc_line2);
	else
	fprintf(file_output,"\t;// %% Lines %d--%d:\n",src_line1,xsrc_line2);

	while (src_line1<=last_printed)
	{
		// skip
		src_line1++;
	}
	for (k=src_line1;k<=src_line2 ;k++)
	{
		src_line_buff[0]=0;
		stat=fgets(src_line_buff,999,file_in);
		if (stat !=NULL)
		{
			if (out_fmt=='c')
				fprintf(file_output,"//%s\n",src_line_buff);
			else
				fprintf(file_output,"\t;//%s\n",src_line_buff);

		}
		else
		{
			break;
		}
	}
	last_printed=src_line2;
}


//! \brief Generate output code from instructions
//! \param indFunc: 0-first function, >1-local functions
void CInstrList::print_rtl(int indFunc)
	{
	int next_src_line=0;
	int last_src_line=1;// from here start printing
	store_function_ind(indFunc);
	iterator p_last_stmt=begin ();

	//if (Compiler.costn==false)
	//	{
	//		//fprintf(stderr,"***** cant find map, BAD TMC installation, please reinstall\n");
	//		//_asm int 4;
	//		//exit(-1000);
	//		return;
	//	}
	if (Compiler.C_output)
	{
		if (indFunc==0)// main function
		{
			// print the list
			fprintf(tmc_output,"//File: %s \n//Generated by TMC Converter(C)2009-2016\n",
				extract_file_name(c_file_name).c_str());

			fprintf(tmc_output,"#include \"tmc.h\"\n");
			fprintf(tmc_output,"#include \"%s\"\n\n","stdtmc.h");
			fprintf(tmc_output,"#include \"%s.globals.h\"\n\n",&ws_file_name[0]);
			fprintf(tmc_output,"// User provided C-code header (must be included in include path):\n");

			fprintf(tmc_output,"#include \"%s\"\n\n","External_func.h");
		
		}
			if (Compiler.print_src)
			{
				if (indFunc==0)// main function
				{
				fseek(tmc_src,0,SEEK_SET); // initialize PrintSrcLines
				last_printed=0;
				
				p_last_stmt=FindNextStmt(&next_src_line,p_last_stmt);// will iterate to next stmt
				PrintSrcLines(tmc_output,tmc_src,last_src_line,next_src_line,'c');
				last_src_line = next_src_line+1;
				}
			}

		for (iterator p = begin (); p != end (); )
		{
		  CInstr elt = *p;
			elt.gen_icode(this);
		    fprintf(tmc_output,"%s\n",elt.m_text.c_str());
			if (Compiler.mode == 'g')
			if (elt.m_inst_type==CInstr::instr_func_declaration)
			{
				if (Compiler.gen_for_all_list)
				{
					// special MEX-prototypes generation
					elt.m_inst_type=CInstr::instr_mexfunc_declaration;
					elt.gen_icode(this);
				}
				// append to common header file
				elt.m_text.replace(elt.m_text.length()-1,1,";");
				fprintf(stdhead_file,"%s\n",elt.m_text.c_str());
			}
			p++;
			if (Compiler.print_src)
			{
				if (p==p_last_stmt)
				{
					p_last_stmt=FindNextStmt(&next_src_line,p_last_stmt);// will iterate to next stmt
					if(next_src_line>=last_src_line)
					{
						PrintSrcLines(tmc_output,tmc_src,last_src_line,next_src_line,'c');
						last_src_line = next_src_line+1;
					}
				}
			}
		}
	} // print C_output
		if (Compiler.code_output==1)
		{
			fprintf(code_file,"\t ;File: %s generated by TMC Converter(C)2009-2016,Israel\n",c_file_name.c_str());
			//fprintf(code_file,"\t%%include \"PE_head.inc\"\n\t%%include \"myinc.inc\"\n");

			if (Compiler.print_src)
			{
				next_src_line=0;
				last_src_line=1;// from here start printing
				p_last_stmt=begin ();

				fseek(tmc_src,0,SEEK_SET); // initialize PrintSrcLines
				last_printed=0;

				p_last_stmt=FindNextStmt(&next_src_line,p_last_stmt);// will iterate to next stmt
				PrintSrcLines(code_file,tmc_src,last_src_line,next_src_line,'S');
				last_src_line = next_src_line+1;
			}
			for (iterator p = begin (); p != end (); )
				{
				  CInstr elt = *p;
					elt.gen_asmcode(this);
					fprintf(code_file,"%s\n",elt.m_text.c_str());
					p++;
			if (Compiler.print_src)
			{
					if (p==p_last_stmt)
					{
						p_last_stmt=FindNextStmt(&next_src_line,p_last_stmt);// will iterate to next stmt
						if(next_src_line>=last_src_line)
						{
							PrintSrcLines(code_file,tmc_src,last_src_line,next_src_line,'S');
							last_src_line = next_src_line+1;
						}
					}
				}
			}
		//fprintf(code_file,"\tPE_tail.inc\n");
		}


//lsp		if (Compiler.bUseDumpFile) fprintf(dump_file,"//-------------------- END ----------------\n");
	}

///////////////// main output function ////////////
#ifdef BLD_RTL_FEATURE
/**
* \brief Generate instructions from \link tmcpar_parsing_module \endlink list of functions
*        This is RTL generation stage with printing output code per each function. It is performed after the parsing stage.
*/

void generate_rtl_list()
// generate list of instructions from the list pointed by tmcpar_parsing_module
{
//extern T_func_hdr *tmclsp_parsing_module;
	CInstrList InstList; // instructions list 
	//parsing_list->generate_rtl_list(&InstList);
	//if (tmclsp_parsing_module)
	//{
	//		tmclsp_parsing_module->generate_rtl_node(&InstList);
	//}
	class T_func_hdr *tfd;
	extern L_stmnt_gen *tmcpar_parsing_module;
	int NumLocalFuncs=0;
	if (tmcpar_parsing_module)
	{   /// Go through list of fucntions
		for (L_stmnt_gen::iterator p = tmcpar_parsing_module->begin();p != tmcpar_parsing_module->end();p++)
		{
			tfd = (T_func_hdr *)(*p);
			Compiler.indFunc = NumLocalFuncs; // since parsing finished, reset the scope
			Compiler.indFunc_RTL = NumLocalFuncs;// reserved for flexibility

			InstList.store_function_ind(NumLocalFuncs);
			tfd->generate_rtl_node(&InstList);/// Generate instructions for each function.
			InstList.print_rtl(NumLocalFuncs);/// And finally convert instructions to the target code (e.g. C-code)
			InstList.reset_new_local_function();
			NumLocalFuncs++;
		}
	}
}
#endif


