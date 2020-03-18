%{
    #include <stdio.h>

    extern int yyerror(char* err);
    extern int yylex(void);
    extern FILE *yyin;
%}

%union {
    char* var;
}
%start stmtseq

%token TOP
%token BOTTOM
%token VARIABLE





%precedence TOP
%precedence BOTTOM
%precedence EQUIVALENT
%precedence IMPLIZIT
%precedence OR
%precedence AND
%precedence NOT
%precedence VARIABLE
%left EX
%left ALL
//%precedence EX
//%precedence ALL
%precedence PRAEDICATE
%precedence FUNCSYMBOL
%precedence COMMA
%precedence OPENPAR
%precedence CLOSEPAR

%%
stmtseq: EX {printf("parser funktioniert!\n");}
%%

int yyerror(char* err)
{
  printf("Error: %s\n",err);
}
void main(int argc, char* argv[])
{
  ++argv, --argc;
  if ( argc > 0 )
      yyin = fopen( argv[0], "r" );
  else
    yyin = stdin;
yyparse();
}
