/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "tmcpar_tree.h"
// Tree loading utilities
T_expr_gen* T_expr_gen::baseexpr(void)
{
if (this->is_expr_colession())
	return ((T_expr_col *)this)->base();
else
	return this;
}

//L_args
void L_args::mark_list_as_lhs_of_assignment()
	{
		for(tmclsp_list<T_expr_gen *>::iterator p=begin();p!=end();p++)
		{
				T_expr_gen *elt=*p;
				elt->mark_expr_as_lhs_of_assignment();
				elt->mark_var_in_lhs_of_assignment();
		}
	};

//T_expr_index
  bool T_expr_index::mark_function__call()
  // prevent identifier to create non-argument call 
  {
	bool retval=false;
	if(m_e)
	if (m_e->is_identifier())
	{
			T_ident *tid=(T_ident*)m_e;
			tid->mark_as_func_call(); // like f()
			retval=true;
	}
	return retval;
  }
