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
}
\( {
  printf("scanning OPENPAR \n");
}
\) {
  printf("scanning CLOSEPAR\n");
}
"top" {
  printf("scanning TOP\n");
}
"bottom" {
  printf("scanning BOTTOM\n");
}
\& {
    printf("scanning AND\n");
}
\| {
    printf("scanning OR\n");
}
\~ {
    printf("scanning NOT\n");
}
"->" {
    printf("scanning IMPLIZIT\n");
}
"<->" {
    printf("scanning EQUIVALENT\n");
}
"all" {
  printf("scanning ALL\n");
}
"ex" {
  printf("scanning EX\n");
  return EX;
}
{VARIABLE}{INTEGER}* {
  printf("scanning VARIABLE\n");
}
{FUNCSYMBOL}{INTEGER}* {
  printf("scanning FUNCSYMBOL\n");
}
{PREDICATE}{INTEGER}* {
  printf("scanning PRAEDICATE\n");
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
