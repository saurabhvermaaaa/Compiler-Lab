%{
   /**
       Yacc program to recognise a regular expression
       and produce a parse tree as output
    */
   #include <stdio.h>
   #include <ctype.h>
   #include <stdlib.h>
   #include <string.h>

   /* To store the productions */
   #define N 100

   int getREindex(const char*);

   char productions[N][N];
   int count = 0, i, j;
   char temp[N * 2], temp2[N * 2];
%}

%token ALPHABET

%left '|'
%left '.'
%nonassoc '*' '+'

%%
S       :     re '\n'       {  printf("This is the rightmost derivation.\n");
                               for(i = count - 1 ; i >= 0 ; --i)
                               {
                                   if(i == count - 1)
                                   {
                                        printf("re => ");
                                        strcpy(temp, productions[i]);
                                        printf("%s", productions[i]);
                                   }
                                   else
                                   {
                                        printf("\n   => ");
                                        j = getREindex (temp);
                                        temp[j] = '\0';
                                        sprintf( temp2, "%s%s%s", temp, productions[i], (temp + j + 2));
                                        printf("%s", temp2);
                                        strcpy(temp, temp2);
                                   }
                                   printf("\n");
                               }
                               printf("\n");
                               exit(0);
                            }


re      :   ALPHABET       {temp[0] = yylval; temp[1] = '\0'; strcpy(productions[count++], temp);}
        |   '(' re ')'     {strcpy(productions[count++], "(re)"); }
        |   re '*' un      {strcpy(productions[count++], "re* un"); }
        |   re '+' un      {strcpy(productions[count++], "re+ un"); }
        |   re '|' re      {strcpy(productions[count++], "re | re");}
        |   re '.' re      {strcpy(productions[count++], "re.re");}
        ;

un      :   ALPHABET       {temp[0] = yylval; temp[1] = '\0'; strcpy(productions[count++], temp);}
        |                  {temp[0]='\0'; strcpy(productions[count++], temp);}
%%

int main(int argc, char **argv)
{
    yyparse();
    return 0;
}

yylex()
{
    int c = getchar();
    yylval = c;
    if(isalpha(c))
        return ALPHABET;
    return c;
}

yyerror()
{
    fprintf(stderr, "Invalid Regular Expression!!\n");
    exit(1);
}

int getREindex(const char *str)
{
    int i = strlen(str)- 1;
    for(; i > 0 ; --i)
    {
        if(str[i] == 'e' && str[i-1] == 'r' || (str[i] == 'n' && str[i-1] == 'u'))
            return i-1;
    }
}
