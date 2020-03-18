%{
    #include <stdio.h>

    extern int yyerror(char* err);
    extern int yylex(void);
    extern FILE *yyin;
%}

%union {
    char* val;
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
%precedence PREDICATE
%precedence FUNCSYMBOL
%precedence COMMA
%precedence OPENPAR
%precedence CLOSEPAR

%%

stmtseq: EX {printf("parser funktioniert!\n");}
        |term {printf("reducing term to startsymbol\n");}
term: VARIABLE{printf("reduced VARIABLE to term\n");}
    | FUNCSYMBOL OPENPAR param CLOSEPAR {printf("reducing f(param) to term\n");}
param: term  {printf("reducing term to param\n");}
    | term COMMA param {printf("reducing (term,term) to param\n");}
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
