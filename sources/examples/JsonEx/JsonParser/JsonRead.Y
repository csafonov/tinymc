%{

// bison file: JsonRead.y
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tmc.h"
#include "JMatrix.h"

extern int yylineno;
extern char* yytext;
int yylex();
void yyerror(const char *s);

// gives good debug information
int yydebug=1;


tmsMatrix * head_tmc_obj; 
JMatrix   * head_jobj;

%}

%name-prefix="Json_"

%token LCURLY RCURLY LBRAC RBRAC COMMA COLON
%token VTRUE VFALSE VNULL VINF  VMINF 
%token <string> STRING;
%token <decimal> DECIMAL;


%union {
  char *string;
  double decimal;
  struct CJMatrix *obj;
  struct tag_tmsMatrix  *tmc_obj;
}

// non-terminal symbols with their types
%type <obj> value object array member members values
%type <tmc_obj> json

%start json

%%

json:
    {
    $$ = make_tmc_obj( NULL,0 );
    head_tmc_obj = $$; 
	head_jobj = NULL;
YYACCEPT;
    }
    | value
    {
    $$ = make_tmc_obj( $1,0 );
    head_tmc_obj = $$; 
	head_jobj = $1;
YYACCEPT;
    }
    ;

value: object
	{
	$$ = $1;
	}
     | STRING
     {
      $$ = make_jstring( $1 );
     }

     | DECIMAL
     {
      $$ = make_jvalue( $1 );
     }
     
     | array
     {
      $$ =   $1  ;
     }
     
     | VTRUE
     {
      $$ = make_jlogics(1);
     }
     
     | VFALSE
     {
      $$ = make_jlogics( 0 );
     }
     
     | VNULL
     {
      $$ = make_null(  );
     }


     | VINF
     {
      $$ = make_inf( 1 );
     }

     | VMINF
     {
      $$ = make_inf( -1 );
     }
     
     ;

object: LCURLY RCURLY
		{
		$$ = make_jobject(NULL);
		}
      | LCURLY members RCURLY
   		{
		$$ = make_jobject($2);
		}
      ;

members: member
		{
			$$ = members_add_member(NULL,$1);
		}
       | members COMMA member
       {
			$$ = members_add_member($1,$3);
       }
       ;
 
member: STRING COLON value
     { 
		$$ = make_member($1,$3);
     }
      ;

array: LBRAC RBRAC
     { 
		$$ = make_array(NULL);
     }

     | LBRAC values RBRAC
     { 
		$$ = make_array($2);
     }
     
     ;

values: value
      {
      $$ = values_add_value(NULL,$1);
      }

      | values COMMA value
      {
      $$ = values_add_value($1,$3);
      }
      ;

%%

void
yyerror(const char *s)
{
  fprintf(stderr,"error: %s on line %d\n", s, yylineno);
}
