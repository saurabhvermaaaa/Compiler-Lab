%token VAR
%left '+'
%left '*'

%%
S 	: 	S E	'\n'				{printf("\n");}
	|	S  '\n'					{printf("\n");}
	|
	;

E	: 	E '+' T					{printf("+");}
	| 	E '-' T 				{printf("-");}
	|	T
	;

T 	: 	T '*' F					{printf("*");}
	| 	T '/' F					{printf("/");}
	|	F
	;

F	: '(' E ')'
	|'-' F						{printf("-");}
	| VAR						{printf("%c",(char)$1);}
	;
%%

yylex()
{
	int c = getchar();
	if((char)c !='+' && (char)c !='-' && (char)c !='/' && (char)c !='*' && (char)c!='\n' && (char)c !='(' && (char)c !=')')
	{
		yylval = c;
		return VAR;
	}
	return c;
}
