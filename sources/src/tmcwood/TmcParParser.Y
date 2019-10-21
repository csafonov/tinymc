%{
//! Gramma for m-file parser

/******************************************************************************
 * Copyright (c) 2009-2015 by Shmuel Safonov.
 * All rights are reserved.
 * The TMC software is covered under GPL license. Other usage possibilities
 * are also available under commercial license terms. 
  *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "tmcpar_tree.h"
#include "tmcpar_utils.h"


%}

%name-prefix="tmcpar_"

// Types of lexems (union type for tmclsp_lval var)
%union
{
	char   *str;
	double num;
	LSP_IDENT   ident;
	struct tree_const_val *lsp_const_val;
	long int_value;
	
	short lsp_delimiter;
// expressions
	class T_ident *lsp_ident_val;
	class T_const   *lsp_constant_val;
	class T_expr_bin *lsp_binary_expression_val;
	class T_expr_bool *lsp_boolean_expression_val;
	class T_expr_unar *lsp_unary_expression_val;
	class T_expr_gen *lsp_expression_val;
	class T_expr_col *lsp_colon_expression_val;
	class L_args *lsp_argument_list_val;
	class tree_matrix *lsp_list_of_argument_list_val;
	class tree_matrix   *lsp_cell_val;
	class T_expr_index	*lsp_index_expression_val;
	class T_expr_assign_one *lsp_simple_assignment_val;
	class T_expr_assign_many *lsp_multi_assignment_val;
	class T_expr_func *lsp_fcn_handle_val;
// statements
	class T_stmnt_gen *lsp_statement_val;
	class T_cmd_gen *lsp_command_val;
// commands
	class T_cmd_ctrl_return*	lsp_return_command_val;
	class T_cmd_decl_gen*	lsp_T_cmd_decl_gen_val;
	class T_cmd_ctrl_label*	lsp_T_cmd_ctrl_label_val;
	class T_ctrl_cmd_if*		lsp_T_ctrl_cmd_if_val;
	class T_ctrl_cmd_while*	lsp_T_ctrl_cmd_while_val;
	class T_ctrl_cmd_continue* lsp_T_ctrl_cmd_continue_val;
	class T_ctrl_cmd_break*	lsp_T_ctrl_cmd_break_val;
	class T_ctrl_cmd_switch*	lsp_T_ctrl_cmd_switch_val;
	class T_ctrl_cmd_try_catch*		lsp_tree_try_command_val;
	class T_ctrl_cmd_for*		lsp_T_ctrl_cmd_for_val;
	class T_func_hdr*    lsp_T_func_hdr_val;
	
// used in declarations	
	class L_vardecl*  lsp_L_vardecl_val;	
// used in if command
	class T_if_block*		lsp_T_if_block_val;
	class LT_if_blocks* lsp_LT_if_blocks_val; // list of clauses
// used in if,while,switch and for
	class L_stmnt_gen* lsp_L_stmnt_gen_val;
// used in switch
	class LT_sw_cases* lsp_LT_sw_cases_val;
	class T_sw_case*		 lsp_T_sw_case_val;
// used in function def
	class T_func_block*    lsp_T_func_block_val;
	
}
// terminal symbos (lexems) definitions with their types
%token	<ident> IDENT
%token  <num>   NUMBER
%token  <num>   NUMBER_IM
%token  <str>   STRING

%term   PLUS            /* + */
%term   MINUS           /* - */
%term   MUL             /* * */
%term   EMUL             /* .* */
%term   AND             /* & */
%term   OR              /* | */
%term   DIV           /* / */
%term   EDIV           /* ./ */
%term   POW           /* ^ */
%term   EPOW           /* .^ */
%term	LDIV		   /* \ */
%term   ELDIV		   /* .\ */
%term   LE           /* <= */
%term   LT           /* < */
%term   GE           /* >= */
%term   GT           /* > */
%term   NE           /* ~= */
%term   EQL           /* == */

%term	BOOL_AND		/* && */
%term	BOOL_OR		    /* || */

%term	TRANSPOSE   /* .' Transpose */
%term	CTRANSPOSE  /* '  Complex conjugate transpose */
%term	NOT   /* ~ */

%term   ASG             /* = */

%term   LPAREN              /* ( */
%term   RPAREN              /* ) */
%term   LC              /* { */
%term   RC              /* } */
%term   LBRA              /* [ */
%term   RBRA              /* ] */
%term   SM              /* ; */
%term   CM              /* , */
%term   LINE              /* newlines */
%term   COMAT             /* @  */
%term   COLON             /* : */
%term   ELLIP             /* . */

%term	MAGIC_END /* end in indexes */

%term   LEXERROR


// Increasing order of precedence
%left   SM CM
%right  ASG
%left	BOOL_OR
%left   BOOL_AND
%left   OR
%left   AND
%left   LE LT GE GT NE EQL 
%left   COLON
%left   MINUS PLUS
%left   MUL EMUL DIV EDIV LDIV ELDIV
%left   NOT
%nonassoc UNARYNOT UNARYPLUS UNARYMINUS 
%left   POW EPOW TRANSPOSE CTRANSPOSE
%left   LBRA LC LPAREN
%nonassoc COMAT



%token  END_OF_INPUT
%token  NO_OP_CMD
%token  RETURN BREAK CONTINUE
%token  IF ELSEIF ELSE END
%token  WHILE 
%token  SWITCH CASE OTHERWISE
%token  FOR
%token  FUNC_HANDLE
%token  TRY CATCH
%token FUNCTION
%token GLOBAL

// non-terminal symbols with their types
%type <lsp_ident_val> ident
%type <lsp_ident_val> magic_end
%type <lsp_constant_val> const
%type <lsp_const_val> variant_val
%type <lsp_expression_val> expression
%type <lsp_binary_expression_val> bin_expr
%type <lsp_boolean_expression_val> bool_expr
%type <lsp_unary_expression_val> un_expr
%type <lsp_colon_expression_val> colon_expr
%type <lsp_expression_val> eval_expression


%type <lsp_argument_list_val> row  row_with_commas
%type <lsp_list_of_argument_list_val> matrix rows 
%type <lsp_delimiter> boxes1 boxes1c parenthesis1
%type <lsp_cell_val> cell


%type <lsp_index_expression_val> indx_expr
%type <lsp_argument_list_val> argument_list

%type <lsp_simple_assignment_val> s_assign

%type <lsp_fcn_handle_val> fcn_handle

%type <lsp_statement_val> statement
%type <lsp_command_val> command

%type <lsp_return_command_val> return
%type <lsp_T_cmd_decl_gen_val> decl_cmd
%type <lsp_T_ctrl_cmd_if_val> if
%type <lsp_T_ctrl_cmd_while_val> while
%type <lsp_T_ctrl_cmd_continue_val> continue
%type <lsp_T_ctrl_cmd_break_val> break


%type <lsp_tree_try_command_val> try
%type <lsp_T_ctrl_cmd_for_val> for

%type <lsp_L_vardecl_val> t_list_decl   
%type <lsp_L_vardecl_val>  list_par  out_list_par in_list_par
%type <lsp_LT_if_blocks_val> t_if_clause list_if_clause elseif_list elseif_list1 elseifelse_list elseifelse_list1
%type <lsp_L_stmnt_gen_val>  list_statement module f_list_statement e_list_statement list_function 


%type <lsp_T_ctrl_cmd_switch_val> switch
%type <lsp_LT_sw_cases_val> case_list case_list1 

%type <lsp_T_func_hdr_val>  fnc_def  func_def_statement
%type <lsp_T_func_block_val>  T_func_block

%type <lsp_argument_list_val>  cmd_pars

%start module

%%

module
		: file_hdr list_function	END_OF_INPUT
		{
			$$=$2;
			tmcpar_parsing_module = $$;
			YYACCEPT;
		}
		;

list_function
		:	func_def_statement
		{
            $$ = create_module($1);
        }
		|   list_function func_def_statement
		{
            $$ = append_to_module($1,$2);
        }		
		;


//module
//                : func_def_statement  /* END_OF_INPUT  */
//		{
//		//printf("Module finished\n");
//		$$ = create_module($1);
//		//tmcpar_parsing_module = $$;
//		//YYACCEPT;
//		}
//		;

// Special type of statement: function definition. Only single function for a file module is permitted.
func_def_statement
        :  fnc_def
	{
			$$=$1;
	}
        ;

file_hdr
        : /* empty */
		| empty_lines
        | null_lines
        ;


fnc_def     : T_func_block
					{
							$$ = create_func_def_statement($1,(int)tmcpar_lineno,(int)tmcpar_colno);
					}
                   ;




T_func_block      : FUNCTION out_list_par ASG IDENT   in_list_par    f_list_statement
					{ // fnc name, inpars,outpars,stms
						 $$ = create_func_body($4,$5,$2,$6,(int)tmcpar_lineno,(int)tmcpar_colno);
					}
		   | FUNCTION  IDENT   in_list_par    f_list_statement
					{
						 $$ = create_func_body($2,$3,0,$4,(int)tmcpar_lineno,(int)tmcpar_colno);
					}
                   ;

f_list_statement   : delimiter list_statement
                   {
                   $$ = $2;
                   }
                   | opt_delimiter
                   {
                   $$ = create_statement_list_empty();
                   }
                   ;
e_list_statement
			   	   : f_list_statement
                   {
					$$ = $1;
                   }
				   | list_statement
				   {
				     $$ = $1;
				   }
				   ;



statement          : expression delimiter
                   {
                    $$ = create_expression($1,(int)tmcpar_lineno,(int)tmcpar_colno);
                   }
		   | command delimiter
                   {
                    $$ = create_command($1,(int)tmcpar_lineno,(int)tmcpar_colno);
                   }
                   ;

eval_expression
				:  expression
				{
				//$$=$1;
				$$ = try_to_colon_expression($1);
				//$$ = create_colon_expression($1,0,0,(int)tmcpar_lineno,(int)tmcpar_colno);
				}
				;
expression
				:  ident
					{
					$$=(T_expr_gen*)($1);
					}
				|  const
					{
					$$=(T_expr_gen*)($1);
					}
				|	magic_end
				{
					$$=(T_expr_gen*)($1);
				}
				    | un_expr
 					{
					$$=(T_expr_gen*)($1);
					}

				|  colon_expr
				{
					$$=(T_expr_gen*)$1;
				}

                |  s_assign
				{
					$$=(T_expr_gen*)($1);
				}

				|  indx_expr
					{
					$$=(T_expr_gen*)($1);
					}

                | bin_expr
					{
					$$=(T_expr_gen*)($1);
					}
                | bool_expr
					{
					$$=(T_expr_gen*)($1);
					}
               | cell
   					{
					$$=simplify_empty_matrix($1);
					}

                | matrix
   					{
					$$=simplify_empty_matrix($1);
					}


                |  fcn_handle
   					{
					$$=(T_expr_gen*)($1);
					}

				| LPAREN parenthesis1 expression
                                {
                                 BracketDelimiter = $2;
                                }       RPAREN
				{
				         yyinsert_comma_in_input(RPAREN);
					$$ = $3;
				}
				;

                                parenthesis1 :
                                {
                                $$ = BracketDelimiter;
                                BracketDelimiter = LPAREN;
                                }
                                ;



command
	    	       : return
   					{
					$$=(T_cmd_gen*)$1;
					}
                   | decl_cmd
   					{
					$$=(T_cmd_gen*)$1;
					}
                   | if
   					{
					$$=(T_cmd_gen*)$1;
					}
                   | while
    					{
					$$=(T_cmd_gen*)$1;
					}

                  | continue
    					{
					$$=(T_cmd_gen*)$1;
					}
                  | break
   					{
					$$=(T_cmd_gen*)$1;
					}

                   | switch
   					{
					$$=(T_cmd_gen*)$1;
					}

                   | for
   					{
					$$=(T_cmd_gen*)$1;
					}


                  | try
   					{
					$$=(T_cmd_gen*)$1;
					}
					
				 // restricted legacy syntax like: hold on;	
				  | IDENT cmd_pars 
				  {
				  $$ = (T_cmd_gen*)create_ref_index("M",$2,create_identifier($1,(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
				  }
				   ;
cmd_pars
				   :	IDENT
					{
					$$ = create_argument_list((T_expr_gen*)create_constant((CONST_VAL_TYPES)0,make_string($1),(int)tmcpar_lineno,(int)tmcpar_colno) );
					}		 
				   |    cmd_pars IDENT
					{
					$$ = append_to_argument_list($1,(T_expr_gen*)create_constant((CONST_VAL_TYPES)0,make_string($2),(int)tmcpar_lineno,(int)tmcpar_colno) );
					}		 
				   ;

out_list_par		   : LBRA  list_par RBRA
					{
					$$=$2;
					}
					| ident
					{
					$$=create_list_ident($1);
					}
					;

in_list_par		   :  LPAREN list_par RPAREN
					{
					$$=$2;
					}
					|
					{
					$$=create_list_ident_empty();
					}
					;



list_par            : ident
					{
					$$ = create_list_ident($1);
					}
                    | list_par CM ident
					{
                   	$$ = append_to_list_ident($1,$3);
					}
                   ;
                   
list_statement     : statement
                   {
                   $$ = create_statement_list($1);
                   }
                   | list_statement  statement
                   {
                   $$ = append_to_statement_list($1,$2);
                   }
                  ;
                  
ident              : IDENT
					{
					 $$ = create_identifier($1,(int)tmcpar_lineno,(int)tmcpar_colno);
					}
				   |
				   NOT
					{
					 $$ = create_identifier_dummy((int)tmcpar_lineno,(int)tmcpar_colno);
					}
				   ;
magic_end
					: MAGIC_END
					{
						 $$ = create_identifier("__end__",(int)tmcpar_lineno,(int)tmcpar_colno);
					}			 
                   ;
const              : variant_val
					{
					 $$ = create_constant((enum CONST_VAL_TYPES)0,$1,(int)tmcpar_lineno,(int)tmcpar_colno);
					}
					;
variant_val        : NUMBER
					{
					 $$ = make_number($1,0,const_val_real);
					}
                   | NUMBER_IM
                   {
                     $$ = make_number(0,$1,const_val_complex);
                   }

                   | STRING
                   {
					 $$ = make_string($1);
                   }
                   ;
 //for global:

t_list_decl
                :    ident 
		{
			$$ = create_list_ident($1);
		}
                |    t_list_decl ident
                {
                     $$ = append_to_list_ident($1,$2);
                }
		;

s_assign : expression   ASG expression
	{
	 $$ = create_s_assignment_expression(0,0,$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
	}
	;



colon_expr
          : expression COLON expression
          {
           $$ = append_colon_expression($1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
          }
          ;
          // $$ = create_colon_expression($13,$16,$19,(int)tmcpar_lineno,(int)tmcpar_colno);
          



argument_list
        : COLON
        {
          $$ =  create_argument_list( create_constant((enum CONST_VAL_TYPES)0,make_magic_col(),(int)tmcpar_lineno,(int)tmcpar_colno) );
        }
        | expression
        {
          $$ =  create_argument_list( $1);
        }
        | COLON CM argument_list
        {
          $$ = insert_head_to_argument_list($3,create_constant((enum CONST_VAL_TYPES)0,make_magic_col(),(int)tmcpar_lineno,(int)tmcpar_colno));
        }
        | expression CM argument_list
        {
          $$ = insert_head_to_argument_list($3,$1);
        }
        ;

indx_expr
        : IDENT LPAREN { indexdeep(1); } parenthesis1 argument_list
        {
        BracketDelimiter = $4;
        } RPAREN
        {
           $$ = create_ref_index("M",$5,create_identifier($1,(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RPAREN);indexdeep(-1);
        }
        | indx_expr LPAREN {indexdeep(1);} parenthesis1  argument_list
        {
        BracketDelimiter = $4;
        } RPAREN
        {
           $$ = create_ref_index("M",$5,$1,(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RPAREN);indexdeep(-1);
        }

        
        
        | IDENT LC {indexdeep(1);} parenthesis1  argument_list
        {
        BracketDelimiter = $4;
        } RC
        {
           $$ = create_ref_index("C",$5,create_identifier($1,(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RC);indexdeep(-1);
        }
        | indx_expr LC {indexdeep(1);} parenthesis1  argument_list
        {
        BracketDelimiter = $4;
        } RC
        {
           $$ = create_ref_index("C",$5,$1,(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(RC);indexdeep(-1);
        }

        
        | IDENT ELLIP IDENT
        {
            $$ = create_ref_field("F",$3,create_identifier($1,(int)tmcpar_lineno,(int)tmcpar_colno),(int)tmcpar_lineno,(int)tmcpar_colno);
         yyinsert_comma_in_input(ELLIP);
       }
        | indx_expr ELLIP IDENT
        {
            $$ = create_ref_field("F",$3,$1,(int)tmcpar_lineno,(int)tmcpar_colno);
        yyinsert_comma_in_input(ELLIP);
        }
        ;




bin_expr
	    : 	expression  PLUS expression
		{
			$$ = create_binary_expression("+",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|	expression  MINUS expression
		{
			$$ = create_binary_expression("-",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|	expression  MUL expression
		{
			$$ = create_binary_expression("*",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|	expression  EMUL expression
		{
			$$ = create_binary_expression(".*",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		
		|	expression  AND expression
		{
			$$ = create_binary_expression("&",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|	expression  OR expression
		{
			$$ = create_binary_expression("|",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		
		
		|	expression  DIV expression
		{
			$$ = create_binary_expression("/",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|	expression  EDIV expression
		{
			$$ = create_binary_expression("./",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		
		|	expression  POW expression
		{
			$$ = create_binary_expression("^",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|	expression  EPOW expression
		{
			$$ = create_binary_expression(".^",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		
		|	expression  LDIV expression
		{
			$$ = create_binary_expression("\\",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|	expression  ELDIV expression
		{
			$$ = create_binary_expression(".\\",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		
		|	expression  LE expression
		{
			$$ = create_binary_expression("<=",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|	expression  LT expression
		{
			$$ = create_binary_expression("<",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		
		|	expression  GE expression
		{
			$$ = create_binary_expression(">=",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|	expression  GT expression
		{
			$$ = create_binary_expression(">",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}

		|	expression  NE expression
		{
			$$ = create_binary_expression("!=",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);//legacy
		}
		|	expression  EQL expression
		{
			$$ = create_binary_expression("==",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		;

bool_expr : expression BOOL_AND expression
		{
			$$ = create_boolean_expression("&&",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|  expression BOOL_OR expression
		{
			$$ = create_boolean_expression("||",$1,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		;

un_expr
	    : 	PLUS expression	  %prec UNARYPLUS
		{
			$$ = create_unary_expression("+",$2,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|    MINUS expression %prec UNARYMINUS
		{
			$$ = create_unary_expression("-",$2,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
		|    NOT expression %prec UNARYNOT
		{
			$$ = create_unary_expression("!",$2,(int)tmcpar_lineno,(int)tmcpar_colno);//legacy
		}
		
		|  expression TRANSPOSE
		{
			$$ = create_unary_expression(".'",$1,(int)tmcpar_lineno,(int)tmcpar_colno);
			yyinsert_comma_in_input(TRANSPOSE);
		}
		|  expression CTRANSPOSE
		{
			$$ = create_unary_expression("'",$1,(int)tmcpar_lineno,(int)tmcpar_colno);
			yyinsert_comma_in_input(CTRANSPOSE);
		}
		;

cell
        : LC boxes1c rows
        {
        BracketDelimiter = $2;
        } RC
        {
        yyinsert_comma_in_input(RC);
         $$ = create_cell_array($3);// convert matrix to cell array
        }
        ;
boxes1c
        :
        {
        $$ = BracketDelimiter;
        BracketDelimiter = LC;
        }
        ;


matrix
        : LBRA boxes1 rows
        {
        BracketDelimiter = $2;
        } RBRA
        {
        yyinsert_comma_in_input(RBRA);
         $$ = $3;
        }
        ;
boxes1
        :
        {
        $$ = BracketDelimiter;
        BracketDelimiter = LBRA;
        }
        ;
        
rows
        :
        {
                         $$ = create_empty_matrix();
        }
        | row
        {
                         $$ = create_matrix($1);
        }
        | rows SM
        {
         $$=$1;
        }
        | rows SM row
        {
                         $$ = add_row_to_matrix($1,$3);
        }
        | rows LINE
        {
                         $$=$1;
        }
        | rows LINE row
        {
                    $$ = add_row_to_matrix($1,$3);
        }
        ;
        
row
        : expression
        {
                    $$ = create_argument_list($1);
        }
        | row_with_commas
        {
                    $$ = $1;
        }
        | row_with_commas expression
        {
                    $$ = append_to_argument_list($1,$2);
        }
        ;

row_with_commas
        : expression CM
        {
          $$ = create_argument_list($1);
        }
        | row_with_commas expression CM
        {
          $$ = append_to_argument_list($1,$2);
        }
        ;

		
fcn_handle
          : COMAT IDENT 
		{
			$$ = create_fcn_handle($2,(int)tmcpar_lineno,(int)tmcpar_colno);
		}
          ;



// Commands
return	:       RETURN
	{
		$$=create_return((int)tmcpar_lineno,(int)tmcpar_colno);
	}
	;
break	:       BREAK
	{
		$$=create_break((int)tmcpar_lineno,(int)tmcpar_colno);
	}
	;
continue	:   CONTINUE
	{
		$$=create_continue((int)tmcpar_lineno,(int)tmcpar_colno);
	}
	;

decl_cmd	: GLOBAL	t_list_decl 
	{
		$$=create_declaration("global",$2,(int)tmcpar_lineno,(int)tmcpar_colno);
	}
	;



/////////////////////////
if	: t_if_clause
	{

		$$ = create_if_statement($1,(int)tmcpar_lineno,(int)tmcpar_colno);
	}
	;
t_if_clause : list_if_clause
	{
		$$=$1;
	}
	;



list_if_clause
	:	IF eval_expression f_list_statement END
	{
		$$ = create_if_clause_list(create_if_clause($2,$3,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	|	IF eval_expression f_list_statement elseif_list
	{
		$$ = insert_head_to_if_clause_list($4,create_if_clause($2,$3,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	|   IF eval_expression f_list_statement elseifelse_list
	{
		$$ = insert_head_to_if_clause_list($4,create_if_clause($2,$3,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	;

elseif_list
	: ELSEIF eval_expression f_list_statement END
	{
		$$ = create_if_clause_list(create_if_clause($2,$3,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	| ELSEIF eval_expression f_list_statement ELSEIF elseif_list1
	{
		$$ = insert_head_to_if_clause_list($5,create_if_clause($2,$3,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	;

elseif_list1
	: eval_expression f_list_statement END
	{
		$$ = create_if_clause_list(create_if_clause($1,$2,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	| eval_expression f_list_statement ELSEIF elseif_list1
	{
		$$ = insert_head_to_if_clause_list($4,create_if_clause($1,$2,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	;

elseifelse_list
	: ELSE 	e_list_statement END
	{
	  $$ = create_if_clause_list(create_if_clause(0,$2,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	| ELSEIF eval_expression f_list_statement ELSE 	e_list_statement END
	{
		$$ = append_to_if_clause_list(
		create_if_clause_list(create_if_clause($2,$3,(int)tmcpar_lineno,(int)tmcpar_colno)),
		create_if_clause(0,$5,(int)tmcpar_lineno,(int)tmcpar_colno)
		);
	}
	| ELSEIF eval_expression f_list_statement ELSEIF elseifelse_list1
	{
		$$ = insert_head_to_if_clause_list($5,create_if_clause($2,$3,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	;
elseifelse_list1
	: eval_expression f_list_statement ELSE e_list_statement END
	{
		$$ = append_to_if_clause_list(
		create_if_clause_list(create_if_clause($1,$2,(int)tmcpar_lineno,(int)tmcpar_colno)),
		create_if_clause(0,$4,(int)tmcpar_lineno,(int)tmcpar_colno)
		);
	}
	|  eval_expression f_list_statement ELSEIF elseifelse_list1
	{
		$$ = insert_head_to_if_clause_list($4,create_if_clause($1,$2,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	;
////////////////////////
while	: WHILE eval_expression  f_list_statement  END
				{
				$$=create_while_command($2,$3,(int)tmcpar_lineno,(int)tmcpar_colno);
			//	yyinsert_comma_in_input(END);
				}
				;

/////////////////////////
switch
        : SWITCH eval_expression delimiter case_list
	{
		$$ =create_switch_command($2,$4,(int)tmcpar_lineno,(int)tmcpar_colno);
	}
	;

case_list
	: CASE eval_expression f_list_statement END
	{
	 	$$ = create_switch_cases_list(create_switch_case($2,$3,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	| CASE case_list1  eval_expression f_list_statement  END
	{
	 	$$ = append_to_switch_cases_list($2,create_switch_case($3,$4,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	| CASE eval_expression f_list_statement OTHERWISE f_list_statement END
	{
	 	$$ = append_to_switch_cases_list(create_switch_cases_list(create_switch_case($2,$3,(int)tmcpar_lineno,(int)tmcpar_colno)),
                 create_switch_case(0,$5,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	| CASE case_list1  eval_expression f_list_statement OTHERWISE f_list_statement  END
	{
	 	$$ =append_to_switch_cases_list(
                    append_to_switch_cases_list($2,create_switch_case($3,$4,(int)tmcpar_lineno,(int)tmcpar_colno)),
                    create_switch_case(0,$6,(int)tmcpar_lineno,(int)tmcpar_colno)
                    );
	}
	| OTHERWISE f_list_statement  END
	{
	 	$$ = create_switch_cases_list(create_switch_case(0,$2,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	;

case_list1
	: eval_expression f_list_statement CASE
	{
		$$ = create_switch_cases_list(create_switch_case($1,$2,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	| case_list1 eval_expression f_list_statement CASE
	{
		$$ = append_to_switch_cases_list($1,create_switch_case($2,$3,(int)tmcpar_lineno,(int)tmcpar_colno));
	}
	;
////////////////////////

for
                                : FOR ident ASG eval_expression  f_list_statement  END
				{
				$$=create_for_statement(/*convert_to_colon_expression*/($2),$4,$5,(int)tmcpar_lineno,(int)tmcpar_colno);
				}
				;





try
				: TRY f_list_statement CATCH f_list_statement END
				{
				$$=create_try_catch_statement($2,$4,(int)tmcpar_lineno,(int)tmcpar_colno);
				}
				| TRY f_list_statement  END
				{
				$$=create_try_catch_statement($2,0,(int)tmcpar_lineno,(int)tmcpar_colno);
				}
				;


opt_delimiter
	 :
	 | delimiter
	 ;
delimiter
	: null_lines
	| empty_lines
	| null_lines empty_lines
	;
null_lines
	: null_line
	| null_lines null_line
	;
null_line
	 : CM
	 | SM
	 | empty_lines CM
	 | empty_lines SM
	 ;
empty_lines
	 : LINE
	 | empty_lines LINE
	 ;

%%


