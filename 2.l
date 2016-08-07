%{
    /* definitions of manifest constants
    LT, LE, EQ, NE, GT, GE,
    IF, THEN, ELSE, ID, NUMBER, RELOP */
    #define LT 1
    #define LE 2
    #define EQ 3
    #define NE 4
    #define GT 5
    #define GE 6
    #define IF 7
    #define THEN 8
    #define ELSE 9
    #define WHILE 13
    #define ID 10
    #define NUMBER 11
    #define RELOP 12
%}


/* regular definitions */
delim   [ \t\n]
ws      {delim}+
letter  [a-zA-Z_]
digit   [0-9]
id      {letter}({letter}|{digit})*
number  {digit}+(\.{digit}+)?(E[+-]?{digit}+)?

%%

{ws}    {/* no action and no return */}
if      {printf("keyword :  if\n");}
then    {printf("keyword :  then\n");}
else    {printf("keyword :  else\n");}
while   {printf("keyword : while\n");}
{id}    {printf("identifier : %s\n", yytext);}
{number} {printf("number : %s\n", yytext);}
"<"     {printf("relop :  <\n");}
"<="     {printf("relop :  <=\n");}
"=="     {printf("relop :  ==\n");}
"!="     {printf("relop :  !=\n");}
">"     {printf("relop :  >\n");}
">="     {printf("relop :  >=\n");}

%%
char* sym[150];
int s = 0;
int installID() {/* function to install the lexeme, whose
                    first character is pointed to by yytext,
                    and whose length is yyleng, into the
                    symbol table and return a pointer
                    thereto */
	sym[s] = yytext;
	++s;
	return s - 1;
}
char *num[150];
int n = 0;
int installNum() {/* similar to installID, but puts numer-
                     ical constants into a separate table */
	num[n] = yytext;
	n += 1;
	return n - 1;
}
int main()
{
	yylex();
}
