/*
Copyright (C)  2009-2012 Shmuel (Constantine V.) Safonov
*/
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


#include <string>
#include <list>

#include "tmcpar_tree.h"

int nTabsLevel;


//#define VANDAL
#ifdef VANDAL
#define m_line    1
#define m_column  1
#define m_line_gn	1
#define m_column_gn	1

#else
#define m_line_gn	generic_tree::line()
#define m_column_gn	generic_tree::column()

#endif

short etypelegacy(const char* stype)
{
	return 0;
}


// HAZARD_COMPATIBILITY:
const char* s_operation_types[]=
{
		"+",//	"operation_add",
		"-",//	"operation_sub",
		"*",//	"operation_mul",
		".*",//	"operation_el_mul",
		"|",//	"operation_el_or",
		"&",//	"operation_el_and",
		"/",//	"operation_div",
		"./",//	"operation_el_div",
		"^",//	"operation_pow",
		".^",//	"operation_el_pow",
		"\\",//	"operation_ldiv",
		".\\",//	"operation_el_ldiv",
		"<=",//	"operation_le",
		"<",//	"operation_lt",
		">=",//	"operation_ge",
		">",//	"operation_gt",
		 "!=",//   "operation_ne",//legacy
		 "==",//   "operation_eq"
};
const char* s_bool_operation_types[]=
{
			"&&", //"bool_operation_and",
			"||", //"bool_operation_or"
};
const char* s_unary_operation_types[]=
{
			"+",//"unary_operation_uplus",
			"!",//"unary_operation_not",//legacy
			"-",//"unary_operation_uminus",
			"'",//"unary_operation_transpose",
			".'",//"unary_operation_hermitian" // scalar transpose
};

std::string Print_operation_types(enum operation_types op)
{
	int n = (int)op;
	return s_operation_types[n];
}
std::string Print_bool_operation_types(enum bool_operation_types op)
{
	int n = (int)op;
	return s_bool_operation_types[n];
}
std::string Print_unary_operation_types(enum unary_operation_types op)
{
	int n = (int)op;
	return s_unary_operation_types[n];
}

// begin{class generic_tree}
void printtabs(void)
{
	int k;
	for (k=0;k<nTabsLevel;k++)
		fprintf(lsp_file," ");
		//fprintf(lsp_file,"\t");
}

//void generic_tree::print_node()
//{
//		printtabs();fprintf(lsp_file,"type=\"%s\",name=UNKNOWN,l=%d,c=%d\n",(char*)"UNKNOWN",(int)m_line,(int)m_column);
//};
void generic_tree::print_gen_tree()
	{
		printtabs();fprintf(lsp_file,"(\n");
		nTabsLevel++;
		print_node(); // here called virtual function
		nTabsLevel--;
		//fprintf(lsp_file,"\n");
		printtabs();fprintf(lsp_file,")\n");
	};
// end{class generic_tree}
// begin{class T_stmnt_gen}
void T_stmnt_gen::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=statement l=%d c=%d\n",(int)m_line,(int)m_column);
		printtabs();fprintf(lsp_file,"stmnt=\n");
		// The following was printed by general tree printing function 
		nTabsLevel++;
		m_statement->print_gen_tree();
		nTabsLevel--;
		// Indeed, it was not so good that the actual statement is assigned to left tree 
		// and not to private member.
		//fprintf(lsp_file,"\n");
	};
// begin{T_expr_gen}
void T_expr_gen::print_node()
	{
				fprintf(lsp_file,"**** unknown expression \n");
	};
// begin{T_ident}
void T_ident::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=ident l=%d c=%d name=\"%s\"\n",(int)m_line,(int)m_column,name().c_str());
	};
// begin{T_const}
void decorate_geresh(std::string& x)
{
	int I=0;
	while ((I = x.find('\'',I))>=0)
	{
		x.insert(I,"'");
		I+=2;
	}

}
void T_const::print_node()
	{
//HAZARD: must print constants correctly according to their type

//HAZARD_TODO: get from tmclspgen

		std::string str		=tmcPrintMatrix(val);
		std::string strT    =tmcPrintMatrixType(val);
		if (_tmcIsChar(val))
		{
			if (_tmcIsEmptyMatrix(val))
			{
				printtabs();fprintf(lsp_file,"tree=const l=%d c=%d type=\"STR\" val=\'\'\n",(int)m_line,(int)m_column);
			}
			else
			{
				decorate_geresh(str);
				printtabs();fprintf(lsp_file,"tree=const l=%d c=%d type=\"%s\" val=\'%s\'\n",(int)m_line,(int)m_column,strT.c_str(),str.c_str());
			}
		}	
		else if (_tmcIsMagicColon(val))
		{
			printtabs();fprintf(lsp_file,"tree=const l=%d c=%d type=\"LL\" val=(:)\n",(int)m_line,(int)m_column);
		}
		else if (_tmcIsEmptyMatrix(val) && _tmcIsMatrixArray(val))
		{
			printtabs();fprintf(lsp_file,"tree=const l=%d c=%d type=\"MN\" val=(nil)\n",(int)m_line,(int)m_column);
		}
		else if (_tmcIsEmptyMatrix(val) && _tmcIsCellArray(val))
		{
			printtabs();fprintf(lsp_file,"tree=const l=%d c=%d type=\"CN\" val=(nil)\n",(int)m_line,(int)m_column);
		}
		else
		{
			printtabs();fprintf(lsp_file,"tree=const l=%d c=%d type=\"%s\" val=%s\n",(int)m_line,(int)m_column,strT.c_str(),str.c_str());
		}
};
// begin{L_args}
void	L_args::print_node()
{// printing matrix
//HAZARD: must be corrected
		//van
		 fseek(lsp_file, -2, SEEK_CUR);
		 nTabsLevel--;


		/*van printtabs();*/ fprintf(lsp_file,"tree=argument_list\n");
		printtabs();fprintf(lsp_file,"arguments=\n");
		nTabsLevel++;
		printtabs();fprintf(lsp_file,"(list=argument\n");
		nTabsLevel++;
		print_list();
		nTabsLevel--;
		printtabs();fprintf(lsp_file,")\n");
		nTabsLevel--;
		/*van printtabs();fprintf(lsp_file,"\n");*/

		nTabsLevel++;
};
// begin{T_expr_col}
void T_expr_col::print_node()
	{

// VANDAL:
	if (op_limit==NULL && op_increment==NULL && op_base)
	{
		//if (op_base)
		//{		
			op_base->print_node();
		//}
			return;
	}

		printtabs();fprintf(lsp_file,"tree=colon_expr l=%d c=%d\n",(int)m_line,(int)m_column);
		printtabs();fprintf(lsp_file,"base=\n");
		if (op_base)
		{		
			op_base->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}
		//fprintf(lsp_file,"\n");
		printtabs();fprintf(lsp_file,"lim=\n");
		if (op_limit)
		{		
			op_limit->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}
		//fprintf(lsp_file,"\n");

		printtabs();fprintf(lsp_file,"inc=\n");
		if (op_increment)
		{		
			op_increment->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}
		//fprintf(lsp_file,"\n");

	}
void T_expr_index::print_node()
	{
		const char* ind_type;

		if (m_arg_list)
		{
		if (is_cell_index())
			ind_type="cell";
		else
			ind_type="matr";
		}
		else
		{
			ind_type="fn";
		}

		if (m_arg_list)
		{
		printtabs();fprintf(lsp_file,"tree=indx_expr l=%d c=%d type=\"%s\"\n",(int)m_line,(int)m_column,ind_type);
			printtabs();fprintf(lsp_file,"args=(list=argument\n");
			m_arg_list->print_node_for_index_expression(); // HAZARD: this is L_args used in another context? !
			printtabs();fprintf(lsp_file,")\n");
			printtabs();fprintf(lsp_file,"e=\n");
		}
		else
		{
		printtabs();fprintf(lsp_file,"tree=fn_expr l=%d c=%d type=\"%s\" ",(int)m_line,(int)m_column,ind_type);
			if (m_is_fn)
			{
			    fprintf(lsp_file,"field=\"%s\"\n",m_fn.c_str());
			    printtabs();fprintf(lsp_file,"e=\n");
			}
			else
			fprintf(lsp_file,"<unknown index expression />\n");
		}
		m_e->print_gen_tree();
		// here the indexed  identifier  was in m_lhs which is also bad.
	};
//begin{T_expr_assign_one}
void T_expr_assign_one::print_node()
	{
		std::string str="=";
//HAZARD_COMPATIBILITY:
//		printtabs();fprintf(lsp_file,"tree=s_assign l=%d c=%d op=\"%s\"\n",(int)m_line,(int)m_column,str.c_str());
		printtabs();fprintf(lsp_file,"tree=s_assign l=%d c=%d type=0 op=\"%s\"\n",(int)m_line,(int)m_column,str.c_str());
		printtabs();fprintf(lsp_file,"lhs=\n");
		if (lhs)
		{
			lhs->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)");}
		//fprintf(lsp_file,"\n");
		printtabs();fprintf(lsp_file,"rhs=\n");
		if (rhs)
		{
			rhs->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)");}
		//fprintf(lsp_file,"\n");
};
//T_expr_assign_many
void T_expr_assign_many::print_node()
	{
		std::string str="=";
		//HAZARD_COMPATIBILITY:
		//printtabs();fprintf(lsp_file,"tree=multi_assign l=%d c=%d op=\"%s\"\n",(int)m_line,(int)m_column,str.c_str());
		printtabs();fprintf(lsp_file,"tree=multi_assign l=%d c=%d type=0 op=\"%s\"\n",(int)m_line,(int)m_column,str.c_str());
		printtabs();fprintf(lsp_file,"lhs=\n");
		if (lhs)
			lhs->print_gen_tree();
		else
		{printtabs();	fprintf(lsp_file,"(nil)\n");}
		printtabs();fprintf(lsp_file,"rhs=\n");
		if (rhs)
			rhs->print_gen_tree();
		else
		{printtabs();	fprintf(lsp_file,"(nil)");}
	};
// tree_matrix
void tree_matrix::print_node()
	{
			printtabs();
			if (is_cell_matrix())
			{
			fprintf(lsp_file,"tree=cell ");
			}
			else
			{
			fprintf(lsp_file,"tree=matrix ");
			}
			fprintf(lsp_file,"l=%d c=%d\n",(int)m_line_gn,(int)m_column_gn);

			printtabs();fprintf(lsp_file,"rows=\n");
			printtabs();   fprintf(lsp_file,"(list=argument_list\n");
			print_list();
			printtabs();   fprintf(lsp_file,")");// my add \n
	}
// T_expr_bin
void T_expr_bin::print_node()
	{
		std::string str=Print_operation_types(op_type());
		//HAZARD_COMPATIBILITY:
		//printtabs();fprintf(lsp_file,"tree=bin_expr l=%d c=%d op=\"%s\"\n",(int)m_line,(int)m_column,str.c_str());
		printtabs();fprintf(lsp_file,"tree=bin_expr l=%d c=%d type=%d op=\"%s\"\n",(int)m_line,(int)m_column,etypelegacy(str.c_str()),str.c_str());
		printtabs();fprintf(lsp_file,"lhs=\n");
		if (op_lhs)
		{
			op_lhs->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}
		//fprintf(lsp_file,"\n");
		printtabs();fprintf(lsp_file,"rhs=\n");
		if (op_rhs)
		{
			op_rhs->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}
		//fprintf(lsp_file,"\n");
};
// T_expr_bool
void T_expr_bool::print_node()
	{
		std::string str=Print_bool_operation_types(op_type());
		//HAZARD_COMPATIBILITY:
		//printtabs();fprintf(lsp_file,"tree=bool_expr l=%d c=%d op=\"%s\"\n",(int)m_line,(int)m_column,str.c_str());
		printtabs();fprintf(lsp_file,"tree=bool_expr l=%d c=%d type=0 op=\"%s\"\n",(int)m_line,(int)m_column,str.c_str());
		printtabs();fprintf(lsp_file,"lhs=\n");
		if (op_lhs)
		{
			op_lhs->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}
		//fprintf(lsp_file,"\n");
		printtabs();fprintf(lsp_file,"rhs=\n");
		if (op_rhs)
		{
			op_rhs->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}
		//fprintf(lsp_file,"\n");
	};
//T_expr_unar
void T_expr_unar::print_node()
	{
		std::string str=Print_unary_operation_types(op_type);
		//HAZARD_COMPATIBILITY:
		//printtabs();fprintf(lsp_file,"tree=un_expr l=%d c=%d  op=\"%s\"\n",(int)m_line,(int)m_column,str.c_str());
		printtabs();fprintf(lsp_file,"tree=un_expr l=%d c=%d  type=0 op=\"%s\"\n",(int)m_line,(int)m_column,str.c_str());
		printtabs();fprintf(lsp_file,"operand=\n");
		if (op)
		{
			// Also we had a problem: in place of put the argument to op, we assigned it to m_lhs !!
			op->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}
};
// T_vardecl
void T_vardecl::print_node()
	{
			id->print_node();
		//fprintf(lsp_file,"name=%s",id->m_name);
	}
// T_func_block
void T_func_block::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=usr_func l=%d c=%d name=\"%s\"\n", (int)m_line,(int)m_column,name().c_str());
		printtabs();fprintf(lsp_file,"params=\n");
		if (param_list != NULL)
		{
		   printtabs();fprintf(lsp_file,"(list=par\n");
			param_list->print_node(); // print_list()
		   printtabs();fprintf(lsp_file,")");
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)");}
		fprintf(lsp_file,"\n");

		printtabs();fprintf(lsp_file,"results=\n");
		if (ret_list != NULL)
		{
		   printtabs();fprintf(lsp_file,"(list=par\n");
			ret_list->print_node(); // print_list()
		   printtabs();fprintf(lsp_file,")");
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)");}
		fprintf(lsp_file,"\n");

		printtabs();fprintf(lsp_file,"statements=\n");
		if (stmt_list != NULL)
		{
		    printtabs();fprintf(lsp_file,"(list=statement\n");
			stmt_list->print_node(); // print_list()
		    printtabs();fprintf(lsp_file,")");
		}
		else
		{fprintf(lsp_file,"(nil)");}
		fprintf(lsp_file,"\n");
	};
// T_func_hdr
void T_func_hdr::print_node()
	{

//HAZARD_COMPATIBILITY:
		printtabs();fprintf(lsp_file,"tree=fnc_def l=%d c=%d name=\"%s\"\n",m_line,m_column,m_f->name().c_str());
		//printtabs();fprintf(lsp_file,"tree=fnc_def l=%d c=%d\n",m_line,m_column);
		printtabs();fprintf(lsp_file,"func=\n");
		nTabsLevel++;
		m_f->print_gen_tree();
		nTabsLevel--;
	}
// T_expr_func
void T_expr_func::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=func_handle l=%d c=%d name=\"%s\"\n",m_line,m_column,fnc_name.c_str());
	}


// T_cmd_ctrl_return
void T_cmd_ctrl_return::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=return l=%d c=%d\n",m_line,m_column);
	}
// T_cmd_decl_gen
void T_cmd_decl_gen::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=decl_cmd l=%d c=%d decl=\"%s\"\n",m_line,m_column,name().c_str());
		printtabs();fprintf(lsp_file,"declars=\n");
		nTabsLevel++;
		printtabs();fprintf(lsp_file,"(list=decl\n");
		initializer_list()->print_node(); // print_list()
		printtabs();fprintf(lsp_file,")\n");
		nTabsLevel--;
	}
// T_cmd_ctrl_label
void T_cmd_ctrl_label::print_node()
	{// used only for end function
		printtabs();fprintf(lsp_file,"tree=no_op_cmd l=%d c=%d cmd=\"%s\"\n",m_line,m_column,m_type.c_str());
	}
// T_sw_case
void T_sw_case::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=sw_case l=%d c=%d\n",m_line,m_column);
		printtabs();fprintf(lsp_file,"case_label=\n");
		if (label)
		{
			label->print_gen_tree();
		}
		else
		{
			printtabs();fprintf(lsp_file,"(nil)\n"); // otherwise case
		}
		printtabs();fprintf(lsp_file,"statements=\n");
		if (list)
		{
			printtabs();fprintf(lsp_file,"(list=statement\n");
			list->print_node(); // print_list()
			printtabs();fprintf(lsp_file,")\n");
		}
		else
		{
			printtabs();fprintf(lsp_file,"(nil)\n");
		}
	}
// T_ctrl_cmd_switch
void T_ctrl_cmd_switch::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=switch l=%d c=%d\n",m_line,m_column);
		printtabs();fprintf(lsp_file,"sw_exp=\n");
		if (expr)
		{
		expr->print_gen_tree();
		}
		else
		{
			{printtabs();fprintf(lsp_file,"(nil)\n");}
		}
		//fprintf(lsp_file,"\n");
		printtabs();fprintf(lsp_file,"sw_cases=\n");
		printtabs();fprintf(lsp_file,"(list=sw_case\n");
		if(list)
		{
		list->print_node(); // print_list()
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)");}
		printtabs();fprintf(lsp_file,")\n");
	}
// T_if_block
void T_if_block::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=if_clause l=%d c=%d\n",m_line,m_column);
		printtabs();fprintf(lsp_file,"if_exp=\n");
		if (expr)
		{
			expr->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}
		printtabs();fprintf(lsp_file,"statements=\n");
		if (list)
		{
		    printtabs();fprintf(lsp_file,"(list=statement\n");
			list->print_node(); // print_list() 
		    printtabs();fprintf(lsp_file,")");
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}
	}
// T_ctrl_cmd_if
void T_ctrl_cmd_if::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=if l=%d c=%d\n",m_line,m_column);
		printtabs();fprintf(lsp_file,"if_cmds=\n");
		nTabsLevel++;
		printtabs();fprintf(lsp_file,"(list=if_clause\n",m_line,m_column);
		list->print_node(); // print_list()
		printtabs();fprintf(lsp_file,")\n");
		nTabsLevel--;
	}
// T_ctrl_cmd_while
void T_ctrl_cmd_while::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=while l=%d c=%d\n",m_line,m_column);
		printtabs();fprintf(lsp_file,"w_exp=\n");
		if (expr)
		{
			expr->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)");}
		printtabs();fprintf(lsp_file,"statements=\n");
		if (list)
		{
		    printtabs();fprintf(lsp_file,"(list=statement ");
			list->print_node(); // print_list() 
		    printtabs();fprintf(lsp_file,")");
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)");}
	}
// T_ctrl_cmd_continue
void T_ctrl_cmd_continue::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=continue l=%d c=%d\n",m_line,m_column);
	}
// T_ctrl_cmd_break
void T_ctrl_cmd_break::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=break l=%d c=%d\n",m_line,m_column);
	}
//tree_do_until_command
/*void tree_do_until_command::print_node()
	{// //NOT_USED

		fprintf(lsp_file,"tree=until l=%d c=%d u_exp=",m_line,m_column);
		if (expr)
		{
			expr->print_gen_tree();
		}
		else
			fprintf(lsp_file,"(nil)");
		fprintf(lsp_file,"statements=");
		if (list)
		{
		    fprintf(lsp_file,"(list=statement ");
			list->print_node(); // print_list() 
		    fprintf(lsp_file,")");
		}
		else
			fprintf(lsp_file,"(nil)");
	}
*/

// T_ctrl_cmd_for
void T_ctrl_cmd_for::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=for l=%d c=%d\n",m_line,m_column);
		printtabs();fprintf(lsp_file,"lmodify_exp=\n");
		if (lhs)
		{
			lhs->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}

		printtabs();fprintf(lsp_file,"reval_exp=\n");
		if (expr)
		{
			expr->print_gen_tree();
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}

		printtabs();fprintf(lsp_file,"statements=\n");
		if (list)
		{
			printtabs();fprintf(lsp_file,"(list=statement\n");
			list->print_node(); // print_list() 
			printtabs();fprintf(lsp_file,")\n");
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}
	}
//tree_complex_for_command
/*
void tree_complex_for_command::print_node()
	{// //NOT_USED
		fprintf(lsp_file,"tree=xfor l=%d c=%d ",m_line,m_column);
		fprintf(lsp_file,"lmodify_exp=");
		if (lhs)
		{
			lhs->print_gen_tree();
		}
		else
			fprintf(lsp_file,"(nil)");

		fprintf(lsp_file,"reval_exp=");
		if (expr)
		{
			expr->print_gen_tree();
		}
		else
			fprintf(lsp_file,"(nil)");

		fprintf(lsp_file,"statements=");
		if (list)
		{
			fprintf(lsp_file,"(list=statement ");
			list->print_node(); // print_list() 
			fprintf(lsp_file,")");
		}
		else
			fprintf(lsp_file,"(nil)");
	}
*/
//T_ctrl_cmd_try_catch
void T_ctrl_cmd_try_catch::print_node()
	{
		printtabs();fprintf(lsp_file,"tree=try l=%d c=%d\n",m_line,m_column);
		printtabs();fprintf(lsp_file,"trycode=\n");
		if (try_code)
		{
			printtabs();fprintf(lsp_file,"(list=statement\n");
			try_code->print_node(); // print_list()
			printtabs();fprintf(lsp_file,")\n");
		}
		else
		{printtabs();fprintf(lsp_file,"(nil)\n");}

	    printtabs();fprintf(lsp_file,"catchcode=\n");
	    if (catch_code)
		{
			printtabs();fprintf(lsp_file,"(list=statement\n");
			catch_code->print_node(); // print_list()
			printtabs();fprintf(lsp_file,")\n");
		}
		else // no catch clause. If no statements, the list is empty but not (nil)
		{printtabs();fprintf(lsp_file,"(nil)\n");}
	}
/////////
void print_tmcpar_tree(L_stmnt_gen * parsing_module)
// print parsing_tree  (tmcpar)
{
	
	//if (Compiler.costn==false)
	//	{
	//		//fprintf(stderr,"***** cant find map, BAD TMC installation, please reinstall\n");
	//		//_asm int 4;
	//		//exit(-1000);
	//		return;
	//	}



	nTabsLevel=0;
//	if ( parsing_list != NULL)
//	{
//	parsing_list->print_node(); // print_list()
//	}

//return;//HAZARD

	if (parsing_module)
	{
		parsing_module->print_node(); // print_list()
	}
	else
	{
		throw(CCompilerExcpt());
	}
}
//#ifdef BLD_RTL_FEATURE
//void print_tmclsp_tree(T_func_hdr *parsing_module)
//// print parsing_tree  
//{
//
////	if ( parsing_list != NULL)
////	{
////	parsing_list->print_node(); // print_list()
////	}
//	if (parsing_module)
//	{
//		parsing_module->print_node();
//	}
//	else
//	{
//		throw(CCompilerExcpt());
//	}
//}
//#endif