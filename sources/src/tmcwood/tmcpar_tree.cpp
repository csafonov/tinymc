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

#include "tmcpar_tree.h"
// Tree loading utilities

generic_tree::~generic_tree()
{

}

T_expr_gen::~T_expr_gen()
{
}

T_func_block::~T_func_block()
{
	delete ret_list;
	delete param_list;
	delete stmt_list;
}
L_stmnt_gen::~L_stmnt_gen()
{
	erase_list();
}
T_stmnt_gen::~T_stmnt_gen()
{
	if (m_statement)
	{
		delete m_statement;
	}
}
T_cmd_gen::~T_cmd_gen()
{

}

L_funcpar::~L_funcpar()
{
	erase_list();
}


T_vardecl::~T_vardecl()
{
	//if (expr)-not supported
	//{
	//	delete expr;
	//}
	if (id)
	{
		delete id;
	}
}




//T_const
T_const::T_const(CONST_VAL_TYPES xtype,struct tree_const_val* v,int l,int c):
val(__tmcNewMatrix()),T_expr_gen(l,c)
	{
		CONST_VAL_TYPES type = v->const_val_type;
	//	m_line=l;m_column=c;

	if (type==const_val_real)
		tmcScalar(val,v->const_val.num.re);
	else if (type==const_val_complex)
		tmcComplexScalar(val,v->const_val.num.re,v->const_val.num.im);
	else if (type==const_val_empty_matrix)
		_tmcCreateMatrix(val,0,0,0);
	else if (type==const_val_empty_cell)
		_tmcCreateCellArray(val,0,0);
	else if (type==const_val_mag_col)
		tmcCreateMagicColon(val);
	else
		tmcCreateString(val,v->const_val.str);

	if (v->const_val_type== const_val_str)
	{
		free(v->const_val.str);
	}
	delete v;
	};
T_const::~T_const()
{
	tmcFreeRegister(val);
}

//T_expr_bin
T_expr_bin::T_expr_bin (enum bool_operation_types etype,T_expr_gen* te1,T_expr_gen* te2,int l,int c):
op_lhs(te1),op_rhs(te2),T_expr_gen(l,c)
{
		//m_line=l;m_column=c;
		//op_lhs=te1;op_rhs=te2;
		m_op_type.bool_op_type=etype;
}
T_expr_bin::~T_expr_bin()
{
	if (op_lhs)
	{
			delete op_lhs;
	}
	if (op_rhs)
	{
			delete op_rhs;
	}

}
T_expr_bin::T_expr_bin (enum operation_types etype,T_expr_gen* te1,T_expr_gen* te2,int l,int c):
op_lhs(te1),op_rhs(te2),T_expr_gen(l,c)
{
	//	m_line=l;m_column=c;
	//	op_lhs=te1;op_rhs=te2;
		m_op_type.binary_op_type=etype;
}
enum operation_types T_expr_bin::get_op_type(const char *op)
{
	const short len=strlen(op);
	if (len>1)
	{
		switch (op[1])
		{
			case '*':
				return operation_el_mul;
			case '/':
				return operation_el_div;
			case '^':
				return operation_el_pow;
			case '\\':
				return operation_el_ldiv;
			case '=':
				if (op[0]=='<')
					return operation_le;
				else if (op[0]=='>')
					return operation_ge;
				else if (op[0]=='!')
					return operation_ne;
				else if (op[0]=='=')
					return operation_eq;
		}
	}
	else
	{
		switch (op[0])
		{
			case '+':
				return operation_add;
			case '-':
				return operation_sub;
			case '|':
				return operation_el_or;
			case '&':
				return operation_el_and;
			case '*':
				return operation_mul;
			case '/':
				return operation_div;
			case '^':
				return operation_pow;
			case '\\':
				return operation_ldiv;
			case '<':
				return operation_lt;
			case '>':
				return operation_gt;
		}
	}
return operation_unknown;
}
//T_expr_bool
T_expr_bool::T_expr_bool (enum bool_operation_types etype,T_expr_gen* te1,T_expr_gen* te2,int l,int c)
:  T_expr_bin (etype,te1, te2, l, c)
{
}
enum bool_operation_types T_expr_bool::get_op_type(const char *op)
{
	if(op)
		switch (op[0])
		{
			case '&':
				return bool_operation_and;
			case '|':
				return bool_operation_or;
		}
return bool_operation_unknown;
}
//T_expr_unar
T_expr_unar::T_expr_unar (enum unary_operation_types etype,T_expr_gen* te,int l,int c):
op(te),op_type(etype),T_expr_gen(l,c)
{
		//m_line=l;m_column=c;
		//op =te;
		//op_type=etype;
}
T_expr_unar::~T_expr_unar()
{
	if (op) delete op;
}
enum unary_operation_types T_expr_unar::get_op_type(const char *op)
{
	const short len=strlen(op);
	if (len>1)
	{
		switch (op[1])
		{
			case '\'':
				if (op[0]=='.')
					return unary_operation_hermitian;
		}
	}
	else
	{
		switch (op[0])
		{
			case '+':
				return unary_operation_uplus;
			case '-':
				return unary_operation_uminus;
			case '\'':
				return unary_operation_transpose;
			case '!':
				return unary_operation_not;
		}
	}
return unary_operation_unknown;
}
//T_expr_col
T_expr_col::T_expr_col(T_expr_gen* base,T_expr_gen* lim,T_expr_gen* inc,int l,int c):
op_base(base),op_limit(lim),op_increment(inc),T_expr_gen(l,c),keep_childern(false)
{
		//m_line=l;m_column=c;
        //op_base=base;
        //op_limit=lim;
        //op_increment=inc;
}
T_expr_col::~T_expr_col()
{
	if (keep_childern)
		return; // only delete the object itself.
	if (op_base) delete op_base;
	if (op_limit) delete op_limit;
	if (op_increment) delete op_increment;
}
void T_expr_col::append_expr(T_expr_gen *e)
{
	//op_increment = limit();
	//op_limit = e;
}
//L_args
L_args::L_args(T_expr_gen *x):generic_tree(x->m_line,x->m_column)
#ifdef BLD_RTL_FEATURE
,simple_assign_lhs (false)
#endif
{
		//m_column=x->m_column;m_line=x->m_line;
		append(x);
};
//T_expr_index
T_expr_index::T_expr_index (const char*xtype,char* fn,T_expr_gen *e,	int l , int c ): 
#ifdef BLD_RTL_FEATURE
		m_num_out_pars(1), //BAD:Changed  15.11.2012 m_num_out_pars(1),
		m_is_lhs_in_assignment(false),
#endif
		m_fn(std::string(fn)),
		m_e(e),m_arg_list(NULL),m_is_fn(true),b_type(indexing_field),T_expr_gen(l,c)
{// field name
	//	m_line=l;m_column=c;
	//	b_type= indexing_field; 
	//	m_fn = std::string(fn);
	//	m_e = e;
	//	m_arg_list=NULL;
	//	m_is_fn=true;//x?
}
T_expr_index::T_expr_index (const char*type,L_args *lst,T_expr_gen *e,int l , int c )
:T_expr_gen(l,c),
#ifdef BLD_RTL_FEATURE
m_num_out_pars(1), //BAD:Changed  15.11.2012 m_num_out_pars(1),
m_is_lhs_in_assignment(false),
#endif
m_fn(),m_e(e),m_arg_list(lst),m_is_fn(false),
b_type((type[0]=='m' || type[0]=='M') ?  indexing_matrix  : indexing_cell)
  {// index
		//m_e = e;
		//m_arg_list = lst;
		//b_type=  (type[0]=='m' || type[0]=='M') ?  indexing_matrix  : indexing_cell;
		//m_is_fn=false;
#ifdef BLD_RTL_FEATURE
		mark_function__call();
#endif
  }
  
// T_expr_assign_one
// T_expr_assign_one
  T_expr_assign_one::T_expr_assign_one(T_expr_gen *_lhs,T_expr_gen *_rhs,int l,int c):
lhs(_lhs),rhs(_rhs),T_expr_gen(l,c)
   {
#ifdef BLD_RTL_FEATURE
		//m_line=l;m_column=c;
		////m_t=t;
	    //lhs=_lhs;rhs=_rhs;
		lhs->mark_expr_as_lhs_of_assignment();
		lhs->mark_var_in_lhs_of_assignment();

		// added 15.11.2012 to mark correcly number of outputs for 0-outputs.
		//if (rhs->is_expr_colession())
		//{
			//T_expr_col* rh_exp=(T_expr_col*)rhs;
		T_expr_gen *te_b =  rhs->baseexpr();
			if (te_b->is_expr_index())
			{
				T_expr_index * rh_index_exp=(T_expr_index *)te_b;
				rh_index_exp->store_num_out_pars(1);
			}
			else
			{
				if (te_b->is_identifier())
				{
					T_ident * rh_identifier=(T_ident *)te_b;
					rh_identifier->store_num_out_pars(1);
				}
			}
		//}
#endif
   }
  T_expr_assign_one::~T_expr_assign_one()
	{
		if (lhs) delete lhs;
		if (rhs) delete rhs;
	}
// T_expr_assign_many
  T_expr_assign_many::T_expr_assign_many(L_args *lst,T_expr_gen *r,int l,int c):
	lhs(lst),rhs(r),T_expr_gen(l,c)
   {
#ifdef BLD_RTL_FEATURE
	 //  lhs=lst;rhs=r;//etype=t;
	//   m_line=l;m_column=c;
	   //m_t=t;
	   lhs->mark_list_as_lhs_of_assignment();

		//T_expr_col* rh_exp=(T_expr_col*)rhs;
	   if (rhs->baseexpr()->is_expr_index())
		{
			T_expr_index * rh_index_exp=(T_expr_index *)rhs->baseexpr();
			rh_index_exp->store_num_out_pars(lhs->length());
		}
		else
		{
			T_ident * rh_identifier=(T_ident *)rhs->baseexpr();
			rh_identifier->store_num_out_pars(lhs->length());
		}
#endif
  }
T_expr_assign_many::~T_expr_assign_many()
	{
		if (lhs) delete lhs;
		if (rhs) delete rhs; 
	}
  /////// statements //////
// T_stmnt_gen
T_stmnt_gen::T_stmnt_gen(generic_tree *x,int l,int c):generic_tree(x->m_line,x->m_column),m_statement(x)
	{
		m_parent=NULL;
		x->m_parent =this;
#ifdef BLD_RTL_FEATURE
		mark_procedure_call();
#endif
	}
///
T_if_block::~T_if_block()
	{
		if (expr) delete expr;
		if (list) delete  list; 
	}
T_ctrl_cmd_if::~T_ctrl_cmd_if()
	{
		if (list) delete list;
	}
LT_if_blocks::~LT_if_blocks (void)
    {
		erase_list();
    }
