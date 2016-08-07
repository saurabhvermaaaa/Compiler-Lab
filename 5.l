/* regular definitions */
delim   [ \t\n]
ws      {delim}+
%%
[Dd][Oo][uU][Bb][Ll][eE][\ ][Pp][Rr][Ee][Cc][Ii][Ss][Ii][Oo][Nn] {printf("REAL");}
%%
int installID() {/* function to install the lexeme, whose
                    first character is pointed to by yytext,
                    and whose length is yyleng, into the
                    symbol table and return a pointer
                    thereto */
	return 0;
}
int installNum() {/* similar to installID, but puts numer-
                     ical constants into a separate table */
	return 0;
}
int main()
{
	yylex();
}
