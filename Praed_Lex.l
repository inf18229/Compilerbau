%option noyywrap
INTEGER  [0-9]
VARIABLE  [n-z]
FUNCSYMBOL  [a-be-m]
PREDICATE [A-Z]
CONSTANT [c-d]
%{
  #include "Praed_Lex.tab.h"
%}

%%
"," {
  printf("scanning COMMA \n");
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
  yylval.val = strdup(yytext); //yytext+1
  return VARIABLE;
}
{CONSTANT}{INTEGER}* {
  printf("scanning CONSTANT %s\n",yytext);
  yylval.val = strdup(yytext);
  return CONSTANT;
}
{FUNCSYMBOL}{INTEGER}* {
  printf("scanning FUNCSYMBOL %s\n",yytext);
  yylval.val = strdup(yytext);
  return FUNCSYMBOL;
}
{PREDICATE}{INTEGER}* {
  printf("scanning PREDICATE %s\n",yytext);
  yylval.val = strdup(yytext);
  return PREDICATE;
}



\n {
 /*SKIP leerzeichen und Enter*/
 }
" " {
 /*SKIP leerzeichen und Enter*/
 }

%%
