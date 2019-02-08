
%option prefix = "puffer_"
%option yylineno
%option noyywrap


%{
#define YY_NEVER_INTERACTIVE	1
short nTildas;
%}

S	[ \t]
NL	((\n)|(\r)|(\r\n))
SNL	({S}|{NL})

%%
",~," {   printf(",junkTilda%d,",++nTildas) ;	 }
"~," {    printf("junkTilda%d,",++nTildas) ;	 }
NL	{ ECHO ;}
. { ECHO ;}
%%


void reset_lexer(){
  BEGIN (INITIAL);
}

int main(int argc, char* argv[])
{
	nTildas =0;
	if (argc>0)
	{
		yyin = fopen(argv[1],"r");
		if (!yyin)
		{
			perror(argv[1]);
			return -1;
		}
		puffer_lex();
	}
	return 0;
}


