%{
    #include <stdio.h>

    extern int yyerror(char* err);
    extern int yylex(void);
%}

%union {
    char* var;
}
%start stmtseq

%precedence FUNKTIONSSYMBOLE
%precedence PRAEDIKAT
%precedence QUANTOR
%precedence NOT
%precedence AND
%precedence OR
%precedence IMPLIKATION
%precedence AEQUIVALENZ


%left ALL
%left EX

%token TOP
%token BOTTOM
%token OPENPAR
%token CLOSEPAR
%token KOMMA
%token VARIABLE

