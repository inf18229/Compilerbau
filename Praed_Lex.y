%{
    #include <stdio.h>
    //#include "Datatypes.h"
    extern int yyerror(char* err);
    extern int yylex(void);
    extern FILE *yyin;
%}

%code requires{
  #include "Datatypes.h"
};

%union {
    char* val;

    term_s* term; //term
    param_s* param; //termlist,
    atom_s* atom;
    formel_s* formel;
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
%precedence CONSTANT
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

stmtseq: formel {printf("reducing formel to startsymbol\n");}


formel: atom {printf("reducing atom to formel\n");}
      | NOT formel {printf("reducing NOT formel to formel\n");}
      | OPENPAR formel CLOSEPAR {printf("reducing (formel) to formel\n");}
      | TOP {printf("reducing top to formel\n");}
      | BOTTOM {printf("reducing bottom to formel\n");}
      | formel AND formel {printf("reducing formel and formel to formel\n");}
      | formel OR formel {printf("reducing formel or formel to formel\n");}
      | formel IMPLIZIT formel {printf("reducing formel -> formel to formel\n");}
      | formel EQUIVALENT formel {printf("reducing formel <-> formel to formel\n");}
      | ALL VARIABLE formel {printf("reducing all variable formel to formel\n");}
      | EX VARIABLE formel {printf("reducing ex variable formel to formel\n");}




term: VARIABLE{printf("reduced VARIABLE to term\n");}
    | CONSTANT {printf("reduced CONSTANT to term\n");}
    | FUNCSYMBOL OPENPAR param CLOSEPAR {printf("reducing f(param) to term\n");}


atom: PREDICATE OPENPAR param CLOSEPAR {printf("reducing R(param) to atom\n");}
    | PREDICATE OPENPAR CLOSEPAR {printf("reducing R() to atom");}
    | PREDICATE {printf("reducing R tp atom");}


param: term  {printf("reducing term to param\n");} //-->Wie in der Lösung termlist
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

term_s *term=createTerm("T",NULL);
printf("Hier\n");
printf("%s\n",term->varfunc);

}
