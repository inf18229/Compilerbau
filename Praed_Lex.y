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


formel: atom {printf("reducing atom to formel\n");
              $<formel>$ = createFormulaATOM(atom, $<atom>1);
              printf("Formel-Typ: %d\n",$<formel>$->typ_s);

}
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

term: VARIABLE{printf("reduced VARIABLE to term\n");
               $<term>$=createTerm($<val>1,NULL);
               printf("Variable: %s\n",$<term>$->varfunc);
}
    | CONSTANT {printf("reduced CONSTANT to term\n");
                $<term>$=createTerm($<val>1,NULL);
                printf("Constant: %s\n",$<term>$->varfunc);
}
    | FUNCSYMBOL OPENPAR param CLOSEPAR {printf("reducing f(param) to term\n");
                                         $<term>$=createTerm($<val>1,$<param>3);
                                         printf("MyList First element: %s\n",$<term>$->myparam_s->first->varfunc);
}
atom: PREDICATE OPENPAR param CLOSEPAR {printf("reducing R(param) to atom\n");
                                        $<atom>$=createAtom($<val>1,$<param>3);
                                        printf("Atom: %s\n",$<atom>$->name);
}
    | PREDICATE OPENPAR CLOSEPAR {printf("reducing R() to atom\n");
                                  $<atom>$=createAtom($<val>1,NULL);
                                  printf("Atom: %s\n",$<atom>$->name);
  }
    | PREDICATE {printf("reducing R tp atom\n");
                 $<atom>$=createAtom($<val>1,NULL);
                 printf("Atom: %s\n",$<atom>$->name);
  }
param: term  {printf("reducing term to param\n");//-->Wie in der Lösung termlist
              $<param>$=createParam($<term>1, NULL);
              //printf("ParamList: %s\n",$<param>$->first->varfunc);

}
    | term COMMA param {printf("reducing (term,term) to param\n");
                        $<param>$=createParam($<term>1,$<param>3);
                        printf("Parameter: %s,%s\n",$<param>$->first->varfunc,$<param>$->first->next->varfunc);
  }
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
