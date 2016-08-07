#include<stdlib.h>
#include<stdio.h>
int main()
{
	    yyparse();
		    return 0;
}

int yyerror(char *s)
{
	    fprintf(stderr , "%s\n", s);
		exit ( 1 );
}

