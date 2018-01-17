//! \file  tmc_rtl.h
//! \brief Implements intermediate instruction (RTL) list  generated from parsed tree

/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
// final instruction list generation for tiny-mc
#ifndef _tmc_rtl_h_
#define _tmc_rtl_h_
#include <list>


void generate_rtl_list(); // main external function

#include "tmcpar_env.h"

#define MAX_CIREG	20000

enum Spec_Regs
{
	Set_Helper_Reg=-10,
	//Get_Helper_Reg=-11
};


enum REG_TYPES
{
	REG_TYPE_UNUSED=0,
	REG_TYPE_LOCAL=1,
	REG_TYPE_IDENT=2,
	REG_TYPE_CONTROL=3,
	REG_TYPE_SET_HELPER=4,
	REG_TYPE_GET_HELPER=5
};

struct CRegDescr
{
	enum REG_TYPES m_reg_type;
	std::string varname;
};



typedef int CILabel; // type for a label
typedef int CIReg;	// type for a register

struct CIRegEx
{
	bool is_mat_name;
	struct 
	{
		std::string varname;
		CIReg       reg;
	} r;
};

std::string get_reg_name(CIReg reg);

// instruction
class CInstrList;
class L_funcpar;

//! Incapsulates a single   instruction
class CInstr
{
private:
	std::string m_comment; // some comment (for labels etc.)

public:
	//! instruction operation types
	enum instr_types
	{
		instr_nothing=-1,
		instr_label=0, // no operation, only label
		instr_goto,
		instr_not,            // not
		instr_uplus,          // uplus
		instr_uminus,         // uminus
		instr_transpose,      // transpose
		instr_hermitian,      // ctranspose
		instr_add,            // plus
		instr_sub,            // minus
		instr_mul,            // mtimes
		instr_div,            // mrdivide
		instr_pow,            // mpower
		instr_ldiv,           // mldivide
		instr_lt,             // lt
		instr_le,             // le
		instr_eq,             // eq
		instr_ge,             // ge
		instr_gt,             // gt
		instr_ne,             // ne
		instr_el_mul,         // times
		instr_el_div,         // rdivide
		instr_el_pow,         // power
		instr_el_ldiv,        // ldivide
		instr_el_and,         // and
		instr_el_or,         // or
		instr_boolean_and, // bool and
		instr_boolean_or, // bools or
		instr_scalar, // make a scalar matrix
		instr_complex, // make a complex matrix
		instr_assign, // assign matrix to a variable
		instr_assign_bool,// assign bool to a variable
		instr_copy_var, // copy variable to variable with given names
		instr_get_var_addr, // assign address of the variable to reg
		instr_func_declaration, // function declaration
		instr_mexfunc_declaration, // for -a option to symplify mex-prototype generation
		instr_funct_call,
		instr_isfield_call,// call isfield()
		instr_fnc_handle,
		instr_block_end, // function end
		instr_fnc_end, // function end for assembler
		instr_test_value, // test a register value for false
		instr_test_value_t, // test a register value for true
		instr_test_value_ass, // test a register value for false and assign
		instr_test_value_t_ass, // test a register value for true and assign
		instr_index_get, // get subset from the matrix
		instr_index_set, // assign subset from the matrix
		instr_cellarray_index_get, // get subset from the cell array
		instr_cellarray_index_set, // assign subset from the cell array
		instr_get_field, // get field
		instr_set_field,  // set field
		instr_create_colon, // get colon
		instr_collect_columns, // collect columns - build a row
		instr_collect_cell_columns, // collect cell columns - build a cell row
		instr_collect_rows, // collect rows - build a matrix,
		instr_collect_cell_rows, // // collect rows - build a cell-matrix,
		instr_create_cell_empty,
		instr_create_matrix_empty,
		instr_create_string_empty,
		instr_create_string,
		instr_create_magic_colon, // like x(1,:)
		instr_magic_end, // like x(1:end) or x(1,2:end)
		instr_magic_end_r, // like s.x(1:end) or s.x(1,2:end)
		instr_for_init,
		instr_for_next,
		instr_calc_switch_exp_value,// calculate value for switch exp (hcode or double)
		instr_compare_case_v,// compare with cell array members,obsolete
		instr_compare_case_s,// compare with evaluated string constant
		instr_compare_case_d,// compare with evaluated double constant
		instr_var_decl,//
		instr_clear_local_vars,
		instr_end_statement,
		instr_syntax_error,
		instr_save_call,
		instr_try_catch_begin, // try in try-catch-end
		instr_try_catch_catch, // catch in try-catch-end
		instr_try_catch_end, // end in try-catch-end
		instr_debuginfo_pushstackvars,
		instr_debuginfo_popstackvars
	};
	instr_types m_inst_type;
	std::string m_text;// rtl string for debugging
	int src_line;
	std::string m_icode;// code string
	CIReg outreg; // output register
	CILabel ilabel; // label
	CILabel igoto_label; // goto label

	std::string m_ident_name; // identificator name
	int nipars; // number of parameters
	int nipars_out;
	std::list<CIReg> ipars;// parameters list
	std::list<CIReg> ipars_out;// parameters list
	std::string lh_var;
	std::string rh_var;

	void set_comment(std::string x) {m_comment=x; };
	int n_argin;
	std::list<std::string> args_in;// func input parameters list
	int n_argout;
	std::list<std::string> args_out;// func input parameters list
	int max_nargin;
	int max_nargout;
	int mag_end_dimension;
	int mag_end_ndimensions;

	double m_Real;
	double m_Imag;
	CInstr() {outreg=0;ilabel=0;nipars=0;nipars_out=0;m_inst_type=instr_nothing;n_argin=0;n_argout=0;};
	void appendpar(const CIReg& ireg)
	{
		ipars.push_back (ireg);
		nipars++;
	}
	void appendpar_out(const CIReg& ireg)
	{
		ipars_out.push_back (ireg);
		nipars_out++;
	}

	void append_argin(const std::string& ar)
	{
		args_in.push_back (ar);
		n_argin++;
	}
	void append_argout(const std::string& ar)
	{
		args_out.push_back (ar);
		n_argout++;
	}

	std::string gen_icode(CInstrList *ilist);
//	instr_types BinaryInstrType(std::string op);
	
	instr_types BinaryInstrType(enum operation_types op);

//	instr_types UnaryInstrType(std::string op);
	instr_types UnaryInstrType(enum unary_operation_types op);
	
	instr_types BooleanInstrType(std::string op);
	std::string gen_asmcode(CInstrList *ilist);

};

//! Instruction list generated for a single function
class CInstrList : public std::list<CInstr>
{
private:
	int last_reg;//!< last used register
	int last_label;
	int m_max_reg;//!< maximal used registers. For RegFrame size calculation 
	int  indFunc; //!< stores index of a function (0:main,>0:local)
	static const std::string out_var_suf;
	void reset_regs() //!< clear registers usage before a new function in module
	{
		m_max_reg=0;// reset frame length
	 last_reg=0;
	 for (long k=0;k<MAX_CIREG;k++)
	 {
		 RegDescr[k].m_reg_type=REG_TYPE_UNUSED;
	 }
	}
public:
	void store_function_ind(int _indFunc)  {indFunc=_indFunc;}//! stores function index before printing code

	static struct CRegDescr RegDescr[MAX_CIREG];
	static const std::string input_var_suf;
	CInstrList()  :m_max_reg(0),indFunc(0)
	{last_label=0;
	 reset_regs();
	};
	~CInstrList()
	{
	}
	void print_rtl(int indFunc);
	int get_sr_reg() {return 0;};
	//! Allocate new register number or store local variable name into instruction
	int get_new_reg(enum REG_TYPES reg_type=REG_TYPE_LOCAL,std::string ident_name="")
	{
		if (reg_type==REG_TYPE_SET_HELPER)
		{
			return Set_Helper_Reg;
		}
		//if (reg_type==REG_TYPE_SET_HELPER)
		//{
		//	return Get_Helper_Reg;
		//}

		m_max_reg=(++last_reg>m_max_reg) ? last_reg:m_max_reg;
		if (m_max_reg>=MAX_CIREG)
		{
			Compiler.LogErr(100, "Can't allocate register,internal error",ident_name, 1,true);
		}
		RegDescr[last_reg].m_reg_type=reg_type;
		if (reg_type==REG_TYPE_IDENT)
		{
			RegDescr[last_reg].varname=ident_name;
		}
		return last_reg;
	};
	void free_registers()
	{//HAZARD_HAZARD_TO_DEFINE_LIFE-TIME: last_reg=0;
	};
	CILabel get_new_label() {return ++last_label;};
	void reset_new_local_function()//! clear registers,labels and instruction list after a function code printing
	{
			last_label=0;
			reset_regs();//hazard todo, chech for locals last_reg=0;
			// clear all the list
			this->clear();
	}
	const bool is_local_function() {return indFunc>0 ? true:false;}
	const int get_local_function_ind() {return indFunc;}//!< get local function enumeration for code generation
	//int max_regs() {return m_max_reg;};
	const int get_RegFrame_size(){ return m_max_reg+1; }
	CInstrList::iterator FindNextStmt(int *src_line,iterator p);
	void PrintSrcLines(FILE *file_output,FILE *file_in,int src_line1,int src_line2,char fmt_type);



	CInstr* append(CInstr i)//!< append an intruction to the list.
	{
		push_back(i);
		return &(back());
	}
	//! \brief Create label instruction
	//! \param	xlabel: label number
	//! \param  comment: text for source comment
	//! \return New instruction (label)
	CInstr* append_label(CILabel xlabel,std::string comment)
	{
		CInstr iLabel;
		iLabel.ilabel      = xlabel;
		iLabel.m_inst_type = CInstr::instr_label;
		iLabel.set_comment(comment);
		return append(iLabel);
	}
	//! \brief Create goto instruction
	//! \param	xlabel: label number
	//! \param  comment: text for source comment
	//! \return New instruction (label)
	CInstr* append_goto(CILabel xlabel,std::string comment)
	{
			CInstr iBranch;
			iBranch.m_inst_type=CInstr::instr_goto;
			iBranch.igoto_label=xlabel;
			iBranch.set_comment(comment);
			return append(iBranch);
	}
	//! \brief Create boolen short-circuit instruction (like expreg1 OP expreg2)
	//! \param  op_str: operation string ( & or |)
	//! \param	endLabel: label for block end
	//! \param  expreg1: first register operand
	//! \param  expreg2: second register operand
	//! \return New instruction (label)
	CInstr* append_boolean_shortcircuitexpr(std::string op_str,CILabel endLabel,CIReg expreg1,CIReg expreg2)
	{
		CInstr iBooleanOp;
		iBooleanOp.outreg=get_new_reg();
		iBooleanOp.igoto_label=endLabel;

		iBooleanOp.BooleanInstrType(op_str); // get inst type from the string
		iBooleanOp.appendpar(expreg1);
		iBooleanOp.appendpar(expreg2);
		return append(iBooleanOp);
	}

	CInstr* append_branch_if_false(CIReg expr_reg,CILabel xlabel,std::string comment)
	{
			CInstr iBranchIfFalse;
			iBranchIfFalse.m_inst_type=CInstr::instr_test_value;
			iBranchIfFalse.igoto_label=xlabel;// goto to the end of the clause if the expression is false
			iBranchIfFalse.appendpar(expr_reg);// expression to be tested
			iBranchIfFalse.set_comment(comment);
			return append(iBranchIfFalse);
	}
		CInstr* append_branch_if_true(CIReg expr_reg,CILabel xlabel,std::string comment)
	{
			CInstr iBranchIfFalse;
			iBranchIfFalse.m_inst_type=CInstr::instr_test_value_t;
			iBranchIfFalse.igoto_label=xlabel;// goto to the end of the clause if the expression is false
			iBranchIfFalse.appendpar(expr_reg);// expression to be tested
			iBranchIfFalse.set_comment(comment);
			return append(iBranchIfFalse);
	}
	CInstr* append_assign_false_and_branch_if_false(CIReg out_reg,CIReg expr_reg,CILabel xlabel,std::string comment)
	{
			CInstr iBranchIfFalse;
			iBranchIfFalse.m_inst_type=CInstr::instr_test_value_ass;
			iBranchIfFalse.igoto_label=xlabel;// goto to the end of the clause if the expression is false
			iBranchIfFalse.appendpar(expr_reg);// expression to be tested
			iBranchIfFalse.appendpar(out_reg);// register to assign
			iBranchIfFalse.set_comment(comment);
			return append(iBranchIfFalse);
	}
	CInstr* append_assign_true_and_branch_if_true(CIReg out_reg,CIReg expr_reg,CILabel xlabel,std::string comment)
	{
			CInstr iBranchIfFalse;
			iBranchIfFalse.m_inst_type=CInstr::instr_test_value_t_ass;
			iBranchIfFalse.igoto_label=xlabel;// goto to the end of the clause if the expression is false
			iBranchIfFalse.appendpar(expr_reg);// expression to be tested
			iBranchIfFalse.appendpar(out_reg);// register to assign
			iBranchIfFalse.set_comment(comment);
			return append(iBranchIfFalse);
	}
	CInstr* append_calc_switch_exp_value(CIReg expr_reg)
	{// get value of switch expression (hcode or double)
			CInstr i;
			CIReg exp_value_reg = get_new_reg();
			i.m_inst_type=CInstr::instr_calc_switch_exp_value;
			i.appendpar(expr_reg);
			i.appendpar(exp_value_reg);
			i.outreg=exp_value_reg;
			return append(i);
	}

	CInstr* append_compare_case_v(CIReg expr_reg,CIReg label_reg,CILabel xlabel,std::string comment)
	{// obsolete
			CInstr iBranchIfFalse;
			iBranchIfFalse.m_inst_type=CInstr::instr_compare_case_v;
			iBranchIfFalse.igoto_label=xlabel;// goto to the end of the clause if the expression is false
			iBranchIfFalse.appendpar(expr_reg);// expression to be tested
			iBranchIfFalse.appendpar(label_reg);// expression to be tested
			iBranchIfFalse.set_comment(comment);
			return append(iBranchIfFalse);
	}
	CInstr* append_compare_case_s(CIReg expr_reg,std::string label_val,CILabel xlabel,std::string comment)
	{// case with string constant
			CInstr iBranchIfFalse;
			iBranchIfFalse.m_inst_type=CInstr::instr_compare_case_s;
			iBranchIfFalse.igoto_label=xlabel;// goto to the begin of the clause if the expression is true
			iBranchIfFalse.appendpar(expr_reg);// expression to be tested
			iBranchIfFalse.m_ident_name=label_val;// constant to be tested
			iBranchIfFalse.set_comment(comment);
			return append(iBranchIfFalse);
	}
	CInstr* append_compare_case_d(CIReg expr_reg,double label_val,CILabel xlabel,std::string comment)
	{// case with double constant
			CInstr iBranchIfFalse;
			iBranchIfFalse.m_inst_type=CInstr::instr_compare_case_d;
			iBranchIfFalse.igoto_label=xlabel;// goto to the begin of the clause if the expression is true
			iBranchIfFalse.appendpar(expr_reg);// expression to be tested
			iBranchIfFalse.m_Real=label_val;// constant to be tested
			iBranchIfFalse.set_comment(comment);
			return append(iBranchIfFalse);
	}
	CInstr* append_isfield_call(CIReg struct_reg,std::string fnname)
	{
		CInstr iFunCall;
		iFunCall.m_inst_type=CInstr::instr_isfield_call;
		iFunCall.appendpar(struct_reg);//  structure
		iFunCall.m_ident_name = fnname; // field name
		iFunCall.outreg = get_new_reg();
		return append(iFunCall);
	}

	CInstr* append_save_call(CInstr iFunCall)
	{
		return append(iFunCall);
	}

	CInstr* append_func_call(int nNumFuncArgIn,int nNumFuncArgOut,int nActualOutPars,std::string fname,std::list<CInstr*> *input_rtl_list)
	{
						int kk;
						CInstr iFunCall;
						iFunCall.m_inst_type=CInstr::instr_funct_call;
						iFunCall.max_nargin=nNumFuncArgIn; // maximal input accoding to symtab
						iFunCall.max_nargout=nNumFuncArgOut; // maximal input accoding to symtab

						// A.1 output arguments for function  call - according to the parent assignment operator
						// Changed: always pass return arguments.
						for ( kk=0;kk<nActualOutPars;kk++)
						{
							CIReg reg_out=get_new_reg();
							iFunCall.appendpar_out(reg_out);
							iFunCall.outreg = reg_out; // register for first function output!!
						}
						// append register for not used parameters in order to avoid NULLs.
						// HAZARD: another solution is to copy create out arguments inside the function.
						for ( kk=nActualOutPars;kk<nNumFuncArgOut;kk++)
						{
							CIReg reg_out=get_new_reg();
							iFunCall.appendpar_out(reg_out);
						}
						iFunCall.nipars_out=nActualOutPars;// re-write valid actual nargout.
						iFunCall.m_ident_name=fname;
						// A.2 input arguments for function call
						for(std::list<CInstr*>::iterator p=input_rtl_list->begin(); p!=input_rtl_list->end();p++)
						{
							CInstr *elt = *p;
							iFunCall.appendpar(elt->outreg);
						}

						// max_nargin: max nargin by SymTab or -1
						// max_nargout: max nargout by SymTab or -1
						// nipars: actual number rhs pars
						// nipars_out: actual number lhs pars

						// for unlimited number of parameters use actual number of parameters
						if (iFunCall.max_nargin<0)
							iFunCall.max_nargin=iFunCall.nipars;

						if(iFunCall.max_nargout<0)
							iFunCall.max_nargout=iFunCall.nipars_out;
						// max_nargin : actual number rhs pars (extended by NULLs)
						// max_nargout: actual number lhs pars (extended by regs)


						return append(iFunCall); 

	}
	CInstr* append_index(CIReg indexed_var,std::list<CInstr*> indexes_rtl_list,bool bSetOp,bool bCellArray)
	{
					CInstr iIndex;
					iIndex.appendpar(indexed_var);// addressed matrix
					if (bSetOp)
					{
						iIndex.outreg = get_new_reg(REG_TYPE_SET_HELPER);// output register

						if (bCellArray==false)
						iIndex.m_inst_type = CInstr::instr_index_set; // set by index to subset from the matrix
						else
						iIndex.m_inst_type = CInstr::instr_cellarray_index_set; // set by index to subset from the matrix
					}
					else
					{
						iIndex.outreg = get_new_reg(REG_TYPE_GET_HELPER);// output register
					
						if (bCellArray==false)
						iIndex.m_inst_type = CInstr::instr_index_get; // get subset from the matrix
						else
						iIndex.m_inst_type = CInstr::instr_cellarray_index_get; // get subset from the matrix
					}
					for (std::list<CInstr*>::iterator p = indexes_rtl_list.begin (); p != indexes_rtl_list.end (); p++)
					{
					  CInstr *elt = *p;
					  iIndex.appendpar(elt->outreg);
					}
					return append(iIndex);
	}
	
	CInstr* append_field(CIReg struct_reg,std::string fieldname,bool bSetOp)
	{
		        CInstr iField;
				iField.outreg = get_new_reg();
				iField.appendpar(struct_reg); // addressed structure
				iField.m_ident_name = fieldname; // field name
				if (bSetOp)
				{
					iField.outreg = get_new_reg(REG_TYPE_SET_HELPER);
					iField.m_inst_type = CInstr::instr_set_field;
				}
				else
				{
					iField.outreg = get_new_reg(REG_TYPE_GET_HELPER);
					iField.m_inst_type = CInstr::instr_get_field;
				}
				return append(iField);
	}
	CInstr* append_var_decl(void)
	{
			CInstr i;
			i.m_inst_type = CInstr::instr_var_decl;
			return append(i);
	}
	CInstr* append_clear_local_vars(void)
	{
			CInstr i;
			i.m_inst_type = CInstr::instr_clear_local_vars;
			return append(i);
	}
	CInstr* append_block_end(void)
	{
			CInstr i;
			i.m_inst_type = CInstr::instr_block_end;
			return append(i);
	}
	CInstr* append_fnc_end(std::string fn)
	{
			CInstr i;
			i.m_inst_type = CInstr::instr_fnc_end;
			i.m_ident_name=fn;
			return append(i);
	}


	CInstr* append_syntax_error(int l,int c,std::string errmsg)
	{
			CInstr i;
			i.m_inst_type = CInstr::instr_syntax_error;
			i.m_text = errmsg;
			i.src_line = l;
			return append(i);
	}
	CInstr* append_assignment(CIReg lh_reg,CIReg rh_reg)
	{
			CInstr iAssign;
			iAssign.m_inst_type=CInstr::instr_assign;
			iAssign.appendpar(lh_reg);//left
			iAssign.appendpar(rh_reg);//right
			iAssign.outreg=lh_reg;// used for boolean expressions
			return append(iAssign);
	}
	CInstr* append_assignment_bool(CIReg lh_reg,CIReg rh_reg)
	{
			CInstr iAssign;
			iAssign.m_inst_type=CInstr::instr_assign_bool;
			iAssign.appendpar(lh_reg);//left
			iAssign.appendpar(rh_reg);//right
			iAssign.outreg=lh_reg;// used for boolean expressions
			return append(iAssign);
	}

	CInstr* append_copy_var(std::string lh_var,std::string rh_var)
	{
			CInstr iAssignVar;
			iAssignVar.m_inst_type=CInstr::instr_copy_var;
			iAssignVar.rh_var=rh_var;
			iAssignVar.lh_var=lh_var;
			return append(iAssignVar);
	}
	CInstr* append_magic_end(struct CIRegEx r,int mat_index_dim,int mat_index_ndims)
	{
		CInstr iMagicEnd;
			CIReg reg_out=get_new_reg();
			iMagicEnd.outreg = reg_out;
			iMagicEnd.mag_end_dimension=mat_index_dim;
			iMagicEnd.mag_end_ndimensions=mat_index_ndims;
			if (r.is_mat_name)
			{
				iMagicEnd.m_ident_name=r.r.varname;
				iMagicEnd.m_inst_type=CInstr::instr_magic_end;
			}
			else
			{
				iMagicEnd.appendpar(r.r.reg);
				iMagicEnd.m_inst_type=CInstr::instr_magic_end_r;
			}
			return append(iMagicEnd);
	}
	CInstr* append_get_var_addr(std::string varname)
	{
				// assign adress of the variable
				CInstr i;
				i.outreg=get_new_reg(REG_TYPE_IDENT,varname);
				i.m_inst_type = CInstr::instr_get_var_addr;
				i.m_ident_name= varname; // variable name
				return append(i);
	}

	CInstr* append_end_statement(int src_line)
	{
			CInstr i;
			i.m_inst_type=CInstr::instr_end_statement;
			i.m_text = "//statement here";
			i.src_line=src_line;
			return append(i);
	}
	CInstr* append_for_init_next(std::string it_varname,CIReg expr_outreg,CILabel for_start_ilabel,CILabel m_exit_ilabel)
	{
		CInstr iIteratorInit;
		CIReg regIter=get_new_reg();
		iIteratorInit.m_inst_type= CInstr::instr_for_init;
		iIteratorInit.m_ident_name = it_varname;
		iIteratorInit.appendpar(regIter); //iterator
		iIteratorInit.appendpar(expr_outreg);// init expression
		append(iIteratorInit);
		
		// do start label
		append_label(for_start_ilabel,"FOR begin");

		// for-next
		CInstr iIteratorNext;
		iIteratorNext.m_inst_type= CInstr::instr_for_next;
		iIteratorNext.appendpar(regIter); //iterator
		iIteratorNext.appendpar(expr_outreg);// init expression
		iIteratorNext.igoto_label=m_exit_ilabel;
		return append(iIteratorNext);
	}
	//////// try-catch-end //////////////////////
	CInstr* append_try(CILabel LabelExcHandler)
	{
			CInstr i;
			std::string str="TRY";
			i.m_inst_type= CInstr::instr_try_catch_begin;
			i.m_text = str.c_str();
			i.ilabel = LabelExcHandler;
			return append(i);
	}

	CInstr* append_catch(CILabel LabelExcHandler, CILabel LabelNoExceptionExcHandler)
	{
			CInstr i;
			std::string str="CATCH";
			i.m_inst_type= CInstr::instr_try_catch_catch;
			i.m_text = str.c_str();
			i.ilabel = LabelExcHandler;
			i.igoto_label = LabelNoExceptionExcHandler;
			return append(i);
	}
	CInstr* append_endcatch(CILabel LabelExceptionHandledExcHandler,CILabel LabelNoExceptionExcHandler)
	{
			CInstr i;
			std::string str="ENDCATCH";
			i.m_inst_type= CInstr::instr_try_catch_end;
			i.m_text = str.c_str();
			i.ilabel = LabelNoExceptionExcHandler; // first label
			i.igoto_label = LabelExceptionHandledExcHandler; // last label
			return append(i);
	}
	///////////// try-finally ////////////
	CInstr* append_tryfinal_try()
	{
			CInstr i;
			std::string str="TRY";
			i.m_text = str.c_str();
			return append(i);
	}
	CInstr* append_finally()
	{
			CInstr i;
			std::string str="FINALLY";
			i.m_text = str.c_str();
			return append(i);
	}
	CInstr* append_endfinally()
	{
			CInstr i;
			std::string str="ENDFINALLY";
			i.m_text = str.c_str();
			return append(i);
	}
/////////////// debug info support //////////////////////
	CInstr* append_debug_pushstackvars(std::string fnc_name,L_funcpar *param_list,L_funcpar *ret_list);
	CInstr* append_debug_popstackvars(int numpars);
///////////////
	CInstr* append_func_decl(std::string func_name,L_funcpar *param_list,
		L_funcpar *ret_list);
	CInstr* append_store_input_vars(L_funcpar *param_list,L_funcpar *ret_list);
	CInstr* append_restore_input_vars(L_funcpar *param_list,L_funcpar *ret_list);
};
// utilities
std::string AppendSlashes(std::string x);
#endif
