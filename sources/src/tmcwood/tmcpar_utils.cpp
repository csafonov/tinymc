//! \file  tmcpar_utils.h
//! \brief utilities for parsed data tree nodes creation. Used in TmcLspParser.Y and TmcLspParser.Y

/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <list>
#include <stack>
#include "tmcpar_tree.h"
#include "tmcpar_utils.h"

int tmc_colno=0;
short BracketDelimiter;
short lexer_indexdeep;
short lexer_at_end_file;

// Main parsing symbol
L_stmnt_gen *tmcpar_parsing_module=NULL; //!< tree result of the parsing, list of functions definitions
//#ifdef BLD_RTL_FEATURE
//T_func_hdr *tmclsp_parsing_module=NULL; // tree result of the parsing
//#endif


//bool is_inbuilt_fnc(char* nm)
//{
//	int x,y;
//	return symbol_table::TmcSymbolTable.get_func_pars_num(nm,&x,&y);
//}

void indexdeep(short inc)
{
	lexer_indexdeep  += inc;
}
short get_indexdeep()
{
	return lexer_indexdeep;
}
// NOTE: struct tree_const_val structures are deleted in T_const contructor!!
struct tree_const_val* make_number(double re,double im,enum CONST_VAL_TYPES type)
{
 struct tree_const_val* t= new (struct tree_const_val);
		t->const_val.num.re = re;
		t->const_val.num.im = im;
		t->const_val_type=type;
return t;
}
struct tree_const_val* make_string(const char *x)
{//HAZARD: may be not needed reallocate.
	// hazard:may be must register in hesh table
 struct tree_const_val* t= new (struct tree_const_val);
 t->const_val.str = (char*)malloc(sizeof(char)*(1+strlen(x)));
 strcpy(t->const_val.str,x); 
  t->const_val_type=const_val_str;
return t;
}

// Parser utilities
struct tree_const_val* make_empty_matrix(void)
{
 struct tree_const_val* t= new (struct tree_const_val);
  t->const_val_type=const_val_empty_matrix;
return t;
}

struct tree_const_val* make_empty_cell(void)
{
 struct tree_const_val* t= new (struct tree_const_val);
  t->const_val_type=const_val_empty_cell;
return t;
}

struct tree_const_val* make_magic_col(void)
{
 struct tree_const_val* t= new (struct tree_const_val);
  t->const_val_type=const_val_mag_col;
return t;
}
/**
		\brief Call from parser on IDENT recognition
*/
class T_ident* create_identifier(const char *x,int l,int c)
{
	/* symbol_table::symbol_record sr =*/ TmcSymbolTable.insert_name(x,&TmcFileList);
	class T_ident* t = new T_ident(x,l,c); 
	return t;
}
/**
		\brief Call from parser on list_par recognition with dummy output variable (~)  
*/

class T_ident* create_identifier_dummy(int l,int c)
{
	std::string dummy_output_name;
	/* symbol_table::symbol_record sr =*/ TmcSymbolTable.insert_name_dummy(dummy_output_name,&TmcFileList);
	class T_ident* t = new T_ident(dummy_output_name,l,c); 
	t->mark_as_dummy_output();
	return t;
}
class T_const* create_constant(CONST_VAL_TYPES type,struct tree_const_val* v,int l,int c)
{
	class T_const* t;
	t = new T_const(type,v,l,c); 
	return t;
}



class T_expr_col*   create_colon_expression(T_expr_gen* base,T_expr_gen* lim,T_expr_gen* inc,int l,int c)
{
	class T_expr_col* t;

	t = new T_expr_col(base,lim,inc,l,c); 
	return t;
}

class T_expr_col*   append_colon_expression(T_expr_gen* e1,T_expr_gen* e2,int l,int c)
{
	class T_expr_col* t;
	
	if (e1->is_expr_col())
	{
		if (e2->is_expr_col())
		{
			// SYNTAX ERROR: we don support it.
			Compiler.LogErr(4, "unsupported colon expression","(:)", l,true);// HAZARD_TODO
		}
		t = create_colon_expression( ((T_expr_col*)e1)->base(),e2,((T_expr_col*)e1)->limit(),l,c  );
		// But we cant delete it with its children, only object itself.
		((T_expr_col*)e1)->mark_keep_childern();
		delete e1;
		//t = (T_expr_col*)e1;
		//t->append_expr(e2);
	}
	else
	{
	t = new T_expr_col(e1,e2,0,l,c); // base/lim/inc
	}
	return t;
}
// legacy conversions
/*
class T_expr_col*   convert_to_colon_expression(T_expr_gen* e)
{
	if (e->is_expr_col())
		return (T_expr_col*)e;
	else
	{
		class T_expr_col* t = create_colon_expression( e,0,0,e->line(),e->column()  );
		return t;
	}
}
*/
class T_expr_gen*      try_to_colon_expression(T_expr_gen* e)
{
	if (e->is_expr_col() || (!e->is_reference() && !e->is_ident())   )
		return  e;
	else
	{
		class T_expr_col* t = create_colon_expression( e,0,0,e->line(),e->column()  );
		return (T_expr_gen*)t;
	}

}
// expression lists
class L_args* create_argument_list(T_expr_gen* te)
{
	class L_args* t;

	t = new L_args(/*convert_to_colon_expression*/(te)); 
	return t;
}
class L_args* append_to_argument_list(L_args*tal,T_expr_gen* te)
{
	class L_args* t = tal;
	tal->append(/*convert_to_colon_expression*/(te));
	return t;
}
class L_args* insert_head_to_argument_list(L_args*tal,T_expr_gen* te)
{
	class L_args* t = tal;
	tal->push_front(/*convert_to_colon_expression*/(te));
	return t;
}
class tree_matrix* create_matrix(class L_args* tal)
{
	class tree_matrix* t;
	t = new tree_matrix(); 
	t->append(tal);
	return t;
}

class tree_matrix* add_row_to_matrix(class tree_matrix* tm, class L_args* tal)
{
	class tree_matrix* t = tm;
	t->append(tal);
	return t;
}

class tree_matrix* create_empty_matrix(void)
{
	class tree_matrix* t;
	t = new tree_matrix(); 
	return t;
}


class tree_matrix* create_cell_array(class tree_matrix* tm)
{
	tm->mark_cell_matrix(true);
	return tm;
}

class T_expr_gen* simplify_empty_matrix(class tree_matrix* tm)
{
	if (tm->IsEmptyMatrix())
	{
		T_expr_gen* te;
		if (tm->is_cell_matrix())
		{
			te = (T_expr_gen*)create_constant((enum CONST_VAL_TYPES)0,make_empty_cell(),(int)tm->line(),(int)tm->column());
		}
		else
		{
			te = (T_expr_gen*)create_constant((enum CONST_VAL_TYPES)0,make_empty_matrix(),(int)tm->line(),(int)tm->column());
		}
		delete tm;	
		return te;
	}
	else
	{
		return (T_expr_gen*)tm;
	}
}

class T_expr_index* create_ref_index(const char* type,class L_args *tal,class T_expr_gen* te, int l, int c)
{
	class T_expr_index* t;
	t = new T_expr_index(type,tal,te,l,c); 
	return t;
}
class T_expr_index* create_ref_field(const char* type,char *fn,class T_expr_gen* te, int l, int c)
{
	class T_expr_index* t;
	t = new T_expr_index(type,fn,te,l,c); 
	return t;
}


class T_expr_assign_one* create_s_assignment_expression(int res_type,char* res_op,
	class T_expr_gen* lhs,class T_expr_gen* rhs,int l,int c)
{
	class T_expr_assign_one* t;

	// distinguish if we deel with multi-assignment
	if (lhs->is_matrix())
	{
		// may be like [z]=func() or [z,y]=func()
		class tree_matrix* tm = (class tree_matrix*)lhs;
		if (tm->length()!=1)
		{
		    // SYNTAX ERROR:  []=func or [x ; y ]=func 
			Compiler.LogErr(5, "unsupported assignment","[]", l,true);// HAZARD_TODO
		}
		class L_args* tal = tm->front();
		L_args::iterator p=tal->begin();
		class T_expr_gen *te = *p;
		if ( tal->length()==0)
		{
		    // SYNTAX ERROR:  []=func 
			Compiler.LogErr(6, "unsupported assignment","[]", l,true);// HAZARD_TODO
		}
		if (tal->length()==1)
		{
			// simple expression
			t = new T_expr_assign_one(/*convert_to_colon_expression*/(te),
				/*convert_to_colon_expression*/(rhs),l,c);
			//hazard: use bool keep_childern trick and delete tm.
			return  t;
		}
		else
		{
			// multi-assignment: TODO
			//hazard: use bool keep_childern trick and delete tm.
			class T_expr_assign_many* tmas;
			tmas=create_m_assignment_expression(res_type,res_op,tal,/*convert_to_colon_expression*/(rhs),l,c);
			return (T_expr_assign_one*)tmas;
		}

	}



	t = new T_expr_assign_one(/*convert_to_colon_expression*/(lhs),
		/*convert_to_colon_expression*/(rhs),l,c); 
	//debug:t->print_node();
	return t;
}

class T_expr_assign_many* create_m_assignment_expression(int res_type,char* res_op,class L_args *lhs,class T_expr_gen *rhs,int l,int c)
{
	class T_expr_assign_many* t;
	t = new T_expr_assign_many(lhs,rhs,l,c); 
	return t;
}
class T_expr_func*	create_fcn_handle(const char* fname,int l,int c)
{
	class T_expr_func* t;
	t = new T_expr_func(fname,l,c); 
	return t;
}

/// expressions //////
//bool is_bin_for_cond(char c)
//{
//	switch (c)
//	{
//	case '|':
//	case '&':
//	case '>':
//	case '~':
//	case '<':
//	case '=':
//		return true;
//	}
//	return false;
//}

class T_expr_bin* create_binary_expression(const char *op,T_expr_gen* te1,T_expr_gen* te2,int l,int c)
{
	class T_expr_bin* t;
//	char ctype=op[0];
//	if (is_bin_for_cond(ctype))
//	{
//
//		t = new T_expr_bin(T_expr_bin::get_op_type(op),/*convert_to_colon_expression*/(te1),
//			/*convert_to_colon_expression*/(te2),l,c); 
//	}
//	else
		t = new T_expr_bin(T_expr_bin::get_op_type(op),te1,te2,l,c); 
//	//debug:t->print_node();
	return t;
}
class T_expr_bool* create_boolean_expression(const char *op,T_expr_gen* te1,T_expr_gen* te2,int l,int c)
{
	class T_expr_bool* t;
	t = new T_expr_bool(T_expr_bool::get_op_type(op),te1,te2,l,c); 
	return t;
}

class T_expr_unar* create_unary_expression(const char *op,T_expr_gen* te,int l,int c)
{
	class T_expr_unar* t;
	t = new T_expr_unar(T_expr_unar::get_op_type(op),te,l,c);  
	return t;
}

//////// statements /////////////////
class T_stmnt_gen* create_expression(class T_expr_gen* gt,int res_l,int res_c)
{
	class T_stmnt_gen* t;
	t = new T_stmnt_gen((class generic_tree*)gt,res_l,res_c); 
	//debug:t->print_node();
	return t;
}
class T_stmnt_gen* create_command(class T_cmd_gen* gt,int res_l,int res_c)
{
	class T_stmnt_gen* t;
	t = new T_stmnt_gen((class generic_tree*)gt,res_l,res_c); 
	//debug:t->print_node();
	return t;
}
// commands
/// \brief Create module as list of statememts containing first parsed function
//! \param	tfd : function node to be added
class L_stmnt_gen* create_module(class T_func_hdr* tfd)
{
	class T_stmnt_gen* t;
	class L_stmnt_gen* lt;


	t = new T_stmnt_gen((class generic_tree*)tfd,tfd->line(),tfd->column()); 
	lt =  create_statement_list(t);
	//debug:t->print_node();
	return lt;
}
//! \brief Append a local function definition to the module
//! \param	lstmt : module  statements list 
//! \param	tfd : function node to be added
class L_stmnt_gen* append_to_module(class L_stmnt_gen* lstmt ,class T_func_hdr* tfd)
{
	class T_stmnt_gen* t;
	class L_stmnt_gen* lt = lstmt;
	t = new T_stmnt_gen((class generic_tree*)tfd,tfd->line(),tfd->column());
	lt->append(t);
	return lt;
}
//! \brief Create function node
//! \param fb: function information
//! \param l: source code line
//! \param c: source code column
class T_func_hdr* create_func_def_statement(T_func_block* fb,int l,int c)
{
	class T_func_hdr *t = new T_func_hdr(fb,l,c);
	return t;
}

//! \brief Create function information node
//! \param fname: function name
//! \param in_parlist: input parameters list 
//! \param ret_parlist: output parameters list
//! \param stl: statements list
//! \param l: source code line
//! \param c: source code column
class T_func_block* create_func_body(const char* fname,L_vardecl* in_parlist,L_vardecl* ret_parlist,L_stmnt_gen* stl,int l,int c)
{
int InArgs=0;
int OutArgs=0;

L_funcpar *param_list=NULL;
L_funcpar *ret_list=NULL;

if (in_parlist)
{
	if (in_parlist->length()>0)
	{
    param_list=new  L_funcpar();
		for (L_vardecl::iterator p=in_parlist->begin(); p !=in_parlist->end();p++)
		{
			InArgs++;
			T_vardecl *elt = *p;
			param_list->append(elt);
		}
#ifdef BLD_RTL_FEATURE
		param_list->mark_as_formal_parameters();
#endif
	}
}
if (ret_parlist)
{
	if (ret_parlist->length()>0)
	{
	ret_list =new  L_funcpar();
		for (L_vardecl::iterator p=ret_parlist->begin(); p !=ret_parlist->end();p++)
		{
			OutArgs++;
			T_vardecl *elt = *p;
			ret_list->append(elt);
		}
#ifdef BLD_RTL_FEATURE
		ret_list->mark_as_formal_parameters();
#endif
	}
}

	// codegen_feature; also maybe useful for command form call.
	TmcSymbolTable.register_fnc_name(fname,InArgs,OutArgs);

#ifndef BLD_RTL_FEATURE //in tmcpar HAZARD_SIMPLIFY
	//legacy
	stl->append(create_command(create_cmd_ctrl_label("endfunction",l,c),l,c));
#endif
	class T_func_block* t=new T_func_block(fname,param_list,ret_list,stl,l,c);
	//t->m_line=l; t->m_column=c;

	return t;
}
class L_vardecl* create_list_ident(T_ident *ti)
{
	class T_vardecl *t2 = new T_vardecl(ti);
	class L_vardecl *t = new L_vardecl(t2);
	return t;
}
class L_vardecl* append_to_list_ident(L_vardecl*tdil,T_ident *ti)
{
	class T_vardecl *t2 = new T_vardecl(ti);
	tdil->append(t2);
	return tdil;
}
class L_vardecl* create_list_ident_empty()
{
	class L_vardecl* t = new L_vardecl();
	return t;
}

class L_stmnt_gen* create_statement_list_empty()
{
	class L_stmnt_gen* t = new L_stmnt_gen();
	return t;
}
class L_stmnt_gen* create_statement_list(T_stmnt_gen* st)
{
	class L_stmnt_gen* t = new L_stmnt_gen(st);
	return t;
}
class L_stmnt_gen* append_to_statement_list(L_stmnt_gen* stl,T_stmnt_gen* st)
{
	stl->append(st);
	return stl;
}

//class L_stmnt_gen* create_function_list(L_stmnt_gen* st)
//{//TODO
//class L_stmnt_gen* t = new L_stmnt_gen(*(st->begin()));
//	return t;
//}
//class L_stmnt_gen* append_to_function_list(L_stmnt_gen* stl,L_stmnt_gen* st)
//{
////TODO
//stl->append(*(st->begin()));
//	return stl;
//}


class T_cmd_ctrl_return* create_return(int l,int c)
{
	class T_cmd_ctrl_return* t=new T_cmd_ctrl_return(l,c);
	return t;
}
class T_ctrl_cmd_break* create_break(int l,int c)
{
	class T_ctrl_cmd_break* t=new T_ctrl_cmd_break(l,c);
	return t;
}
class T_ctrl_cmd_continue* create_continue(int l,int c)
{
	class T_ctrl_cmd_continue* t=new T_ctrl_cmd_continue(l,c);
	return t;
}
class T_cmd_ctrl_label* create_cmd_ctrl_label(const char* type,int l,int c)
{
	class T_cmd_ctrl_label* t = new T_cmd_ctrl_label(type,l,c);
	return t;
}
class T_cmd_decl_gen* create_declaration(const char* type,L_vardecl* tdil, int l,int c)
{
	class T_cmd_decl_gen* t = new T_cmd_decl_gen(type,tdil,l,c);
	return t;
}
class T_ctrl_cmd_if* create_if_statement(LT_if_blocks*ticl,int l,int c)
{
class T_ctrl_cmd_if* t=new T_ctrl_cmd_if(ticl,l,c);
return t;
}
class LT_if_blocks* create_if_clause_list(T_if_block* tic)
{
class LT_if_blocks *t = new LT_if_blocks(tic);
	return t;
}

class LT_if_blocks* insert_head_to_if_clause_list(LT_if_blocks* ticl,T_if_block* tic)
{ // insert T_if_block* tic to head of LT_if_blocks* ticl

	ticl->push_front(tic);tic->m_parent=ticl;//HSKOST16.10.2016
	return ticl;

}

class LT_if_blocks* append_to_if_clause_list(LT_if_blocks* ticl,T_if_block* tic)
{
	ticl->append(tic);
	return ticl;
}

class LT_if_blocks* create_if_clause_list_empty()
{
class LT_if_blocks* t = new  LT_if_blocks();
	return t;
}
class T_if_block* create_if_clause(T_expr_gen* te,L_stmnt_gen* sl,int l,int c)
{
class T_if_block *t =new  T_if_block(te,sl,l,c);
	return t;
}
class T_ctrl_cmd_while* create_while_command(T_expr_gen* te,L_stmnt_gen* sl,int l,int c)
{
class T_ctrl_cmd_while* t = new T_ctrl_cmd_while(te,sl,l,c);
	return t;
}
class T_ctrl_cmd_switch* create_switch_command(T_expr_gen* te,LT_sw_cases*tscl,int l,int c)
{
class T_ctrl_cmd_switch* t = new  T_ctrl_cmd_switch(te,tscl,l,c);
	return t;
}
class LT_sw_cases* create_switch_cases_list(T_sw_case* tsc)
{
	class LT_sw_cases* t  = new LT_sw_cases(tsc);
	return t;
}
class LT_sw_cases* insert_head_to_switch_cases_list(LT_sw_cases* tscl, T_sw_case* tsc)
{
	tscl->push_front(tsc);tsc->m_parent=tscl;//HSKOST16.10.2016
	return tscl;
}
class LT_sw_cases* append_to_switch_cases_list(LT_sw_cases* tscl, T_sw_case* tsc)
{
	tscl->append(tsc);
	return tscl;
}
class LT_sw_cases* create_switch_cases_list_empty()
{
class LT_sw_cases* t = new LT_sw_cases();
	return t;
}
class T_sw_case* create_switch_case(T_expr_gen* te,L_stmnt_gen* sl,int l,int c)
{
class T_sw_case* t = new T_sw_case(te,sl,l,c);
	return t;
}
class T_ctrl_cmd_for* create_for_statement(T_expr_gen* lhs_te,T_expr_gen* rhs_te,L_stmnt_gen* sl,int l,int c)
{
	class T_ctrl_cmd_for* t = new T_ctrl_cmd_for(lhs_te,rhs_te,sl,l,c);
	return t;
}
class T_ctrl_cmd_try_catch* create_try_catch_statement(L_stmnt_gen*try_sl,L_stmnt_gen*catch_sl,int l,int c)
{
class T_ctrl_cmd_try_catch* t = new T_ctrl_cmd_try_catch(try_sl,catch_sl,l,c);
	return t;
}

//class T_func_hdr * get_tmclsp_parsing_module(L_stmnt_gen* _tmcpar_parsing_module)
//{
//	class T_func_hdr *tfd = NULL;
//	if (_tmcpar_parsing_module)
//	{
//		L_stmnt_gen::iterator p = _tmcpar_parsing_module->begin();
//		tfd = (T_func_hdr *)(*p);
//	}
//	return tfd;
//}
