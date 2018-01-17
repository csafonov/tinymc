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
#include <io.h>

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

std::string CInstr::gen_icode(CInstrList *ilist) { return "?";}

void T_func_block::print_node(void){}
void T_expr_bool::print_node(void){}
void  generic_tree::print_gen_tree(void){}
void T_expr_assign_many::print_node(void){}
void T_expr_unar::print_node(void){}
void T_expr_index::print_node(void){}
void T_expr_col::print_node(void){}
void T_const::print_node(void){}
void T_ctrl_cmd_if::print_node(void){}
void T_expr_assign_one::print_node(void){}
void T_vardecl::print_node(void){}
void T_expr_bin::print_node(void){}
void  T_if_block::print_node(void){}
void T_expr_gen::print_node(void){}
void L_args::print_node(void){}
void T_stmnt_gen::print_node(void){}
void  T_ident::print_node(void){}
void  T_ctrl_cmd_while::print_node(void){}
void  T_cmd_decl_gen::print_node(void){}
void  T_ctrl_cmd_continue::print_node(void){}
void  T_func_hdr::print_node(void){}
void  T_cmd_ctrl_return::print_node(void){}
void  tree_matrix::print_node(void){}
void  T_ctrl_cmd_try_catch::print_node(void){}
void  T_ctrl_cmd_break::print_node(void){}
void  T_sw_case::print_node(void){}
void  T_cmd_ctrl_label::print_node(void){}
void  T_ctrl_cmd_for::print_node(void){}
void   T_ctrl_cmd_switch::print_node(void){}
void   T_expr_func::print_node(void){}

void  print_tmcpar_tree(class L_stmnt_gen *){}

int nTabsLevel;

void  create_init_hash_data_file(char *){}
int tmclsp_lineno=0;
void   reset_lspparser(void){}
void   print_tmclsp_tree(class T_func_hdr *){}
int   tmclsp_parse(void){return -1;}
int  symbol_table::PrintCommonHeader(std::string filename){return -1;}
int  symbol_table::PrintGlobalsDefs(std::string h_filename,std::string c_filename){return -1;}
FILE * tmclsp_in;