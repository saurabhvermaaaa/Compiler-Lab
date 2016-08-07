%token BIT
%left '&'
%left '|'
%right  '~'

%%
S 		:	S E '\n'	{printf("%d\n",$2);}
		|	S '\n'
		|
		;

E		:	E '|' T     {$$=$1|$3;}
		|	T 		    {$$=$1;}
		;

T 		:	T '&' F     {$$=$1&$3;}
		|	F		    {$$=$1;}
		;

F		:	'(' E ')'   {$$=$2;}
		|	'~'F	    {$$=1^$2;}
		|	BIT
		;
%%

yylex()
{
	int c = getchar();
	if(c == '0' || c == '1')
	{
		yylval = c - '0';
		return BIT;
	}
	return c;
}
