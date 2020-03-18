%option noyywrap
INTEGER  [0-9]
VARIABLE  [n-z]
FUNCSYMBOL  [a-m]
PREDICATE [A-Z]
%{
  #include "Praed_Lex.tab.h"
%}

%%
"," {
  printf("scanning COMMA \n"); //-->Semantischer Wert ist steht in yytext
  return COMMA;
}
\( {
  printf("scanning OPENPAR \n");
  return OPENPAR;
}
\) {
  printf("scanning CLOSEPAR\n");
  return CLOSEPAR;
}
"top" {
  printf("scanning TOP\n");
  return TOP;
}
"bottom" {
  printf("scanning BOTTOM\n");
  return BOTTOM;
}
\& {
    printf("scanning AND\n");
    return AND;
}
\| {
    printf("scanning OR\n");
    return OR;
}
\~ {
    printf("scanning NOT\n");
    return NOT;
}
"->" {
    printf("scanning IMPLIZIT\n");
    return IMPLIZIT;
}
"<->" {
    printf("scanning EQUIVALENT\n");
    return EQUIVALENT;
}
"all" {
  printf("scanning ALL\n");
  return ALL;
}
"ex" {
  printf("scanning EX\n");
  return EX;
}
{VARIABLE}{INTEGER}* {
  printf("scanning VARIABLE %s\n",yytext);
  yylval.val = yytext+1;
  return VARIABLE;
}
{FUNCSYMBOL}{INTEGER}* {
  printf("scanning FUNCSYMBOL %s\n",yytext);
  yylval.val = yytext+1;
  return FUNCSYMBOL;
}
{PREDICATE}{INTEGER}* {
  printf("scanning PRAEDICATE %s\n",yytext);
  yylval.val = yytext+1;
  return PREDICATE;
}



\n {
 /*SKIP leerzeichen und Enter*/
 //printf("\n");
 }
" " {
 /*SKIP leerzeichen und Enter*/
 //printf("LEERZEICHEN erkannt! ");
 }

%%
/* int main( int argc, char**argv )    {
++argv, --argc;/*skip over program name*/
/*if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
else
    yyin = stdin;
yylex();
}

*/
