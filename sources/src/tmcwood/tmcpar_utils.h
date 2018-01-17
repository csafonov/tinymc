/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/
#ifndef _tmcpar_utils_h_
#define _tmcpar_utils_h_



extern short BracketDelimiter;
extern short lexer_indexdeep;
extern short lexer_at_end_file;

// Main parsing symbol
extern  L_stmnt_gen *tmcpar_parsing_module; // tree result of the parsing
#ifdef BLD_RTL_FEATURE
//extern  T_func_hdr *tmclsp_parsing_module; // tree result of the parsing
#endif

void yyinsert_comma_in_input(const int tok);
void indexdeep(short inc);
short get_indexdeep();
//bool is_inbuilt_fnc(char* nm); // to recognize like hold on;

struct tree_const_val* make_ident(const char *x);
struct tree_const_val* make_number(double re,double im,enum CONST_VAL_TYPES type);
struct tree_const_val* make_string(const char *x);
struct tree_const_val* make_empty_matrix(void);
struct tree_const_val* make_empty_cell(void);
struct tree_const_val* make_magic_col(void);

class T_const* create_constant(CONST_VAL_TYPES type,struct tree_const_val* v,int l,int c);
class T_ident* create_identifier(const char *x,int l,int c);
class T_expr_bin* create_binary_expression(const char *etype,T_expr_gen* te1,T_expr_gen* te2,int l,int c);
class T_expr_bool* create_boolean_expression(const char *etype,T_expr_gen* te1,T_expr_gen* te2,int l,int c);
class T_expr_unar* create_unary_expression(const char *etype,T_expr_gen* te,int l,int c);

class T_expr_col*   create_colon_expression(T_expr_gen* base,T_expr_gen* lim,T_expr_gen* inc,int l,int c);
class T_expr_col*   append_colon_expression(T_expr_gen* e1,T_expr_gen* e2,int l,int c);
class T_expr_col*   convert_to_colon_expression(T_expr_gen* e);//legacy
class T_expr_gen*      try_to_colon_expression(T_expr_gen* e);//legacy



class L_args* create_argument_list(T_expr_gen* te);
class L_args* append_to_argument_list(L_args*tal,T_expr_gen* te);
class L_args* insert_head_to_argument_list(L_args*tal,T_expr_gen* te);

class tree_matrix* create_matrix(class L_args* tal);
class tree_matrix* add_row_to_matrix(class tree_matrix* tm, class L_args* tal);
class tree_matrix* create_empty_matrix(void);
class tree_matrix*   create_cell_array(class tree_matrix* tm);

class T_expr_gen* simplify_empty_matrix(class tree_matrix* tm);



class T_expr_index* create_ref_index(const char* type,class L_args *tal,class T_expr_gen* te, int l, int c);
class T_expr_index* create_ref_field(const char* type,char *fn,class T_expr_gen* te, int l, int c);
class T_expr_assign_one* create_s_assignment_expression(int res_type,char* res_op,
	class T_expr_gen* lhs,class T_expr_gen* rhs,int l,int c);
class T_expr_assign_many* create_m_assignment_expression(int res_type,char* res_op,
class L_args *lhs,class T_expr_gen *rhs,int l,int c);

class T_expr_func*	create_fcn_handle(const char* fname,int l,int c);

// statements
//class T_stmnt_gen* create_statement(class generic_tree* gt,int l,int c);
class T_stmnt_gen* create_expression(class T_expr_gen* gt,int l,int c);
class T_stmnt_gen* create_command(class T_cmd_gen* gt,int l,int c);

class L_stmnt_gen* create_module(class T_func_hdr* tfd);
class L_stmnt_gen* append_to_module(class L_stmnt_gen* lstmt ,class T_func_hdr* tfd);

class T_func_hdr* create_func_def_statement(T_func_block* fb,int l,int c);
class T_func_block* create_func_body(const char* fname,L_vardecl* in_parlist,L_vardecl* ret_parlist,L_stmnt_gen* stl,int l,int c);
class L_vardecl* create_list_ident(T_ident *ti);
class L_vardecl* append_to_list_ident(L_vardecl*tdil,T_ident *ti);
class L_vardecl* create_list_ident_empty();
class L_stmnt_gen* create_statement_list_empty();
class L_stmnt_gen* create_statement_list(T_stmnt_gen* st);
class L_stmnt_gen* append_to_statement_list(L_stmnt_gen* stl,T_stmnt_gen* st);
class T_cmd_ctrl_return* create_return(int l,int c);
class T_ctrl_cmd_break* create_break(int l,int c);
class T_ctrl_cmd_continue* create_continue(int l,int c);
class T_cmd_decl_gen* create_declaration(const char* type,L_vardecl* tdil, int l,int c);
class T_cmd_ctrl_label* create_cmd_ctrl_label(const char* type,int l,int c);
class T_ctrl_cmd_if* create_if_statement(LT_if_blocks*ticl,int l,int c);
class LT_if_blocks* create_if_clause_list(T_if_block* tic);
class LT_if_blocks* append_to_if_clause_list(LT_if_blocks* ticl,T_if_block* tic);

class LT_if_blocks* insert_head_to_if_clause_list(LT_if_blocks* ticl,T_if_block* tic);

class LT_if_blocks* create_if_clause_list_empty();
class T_if_block* create_if_clause(T_expr_gen* te,L_stmnt_gen* sl,int l,int c);
class T_ctrl_cmd_while* create_while_command(T_expr_gen* te,L_stmnt_gen* sl,int l,int c);
class T_ctrl_cmd_switch* create_switch_command(T_expr_gen* te,LT_sw_cases*tscl,int l,int c);
class LT_sw_cases* create_switch_cases_list(T_sw_case* tsc);
class LT_sw_cases* append_to_switch_cases_list(LT_sw_cases* tscl, T_sw_case* tsc);

class LT_sw_cases* insert_head_to_switch_cases_list(LT_sw_cases* tscl, T_sw_case* tsc);

class LT_sw_cases* create_switch_cases_list_empty();
class T_sw_case* create_switch_case(T_expr_gen* te,L_stmnt_gen* sl,int l,int c);
class T_ctrl_cmd_for* create_for_statement(T_expr_gen* lhs_te,T_expr_gen* rhs_te,L_stmnt_gen* sl,int l,int c);
class T_ctrl_cmd_try_catch* create_try_catch_statement(L_stmnt_gen*try_sl,L_stmnt_gen*catch_sl,int l,int c);

void print_tmcpar_tree(L_stmnt_gen *parsing_module); // print tmcpar lsp output
//void print_tmclsp_tree(T_func_hdr *parsing_module); // print debug listing (tmclsp)


//class T_func_hdr * get_tmclsp_parsing_module(L_stmnt_gen* _tmcpar_parsing_module);

//class L_stmnt_gen* create_function_list(L_stmnt_gen* st);
//class L_stmnt_gen* append_to_function_list(L_stmnt_gen* stl,L_stmnt_gen* st);

#endif