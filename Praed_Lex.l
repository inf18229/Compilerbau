%option noyywrap
INTEGER  [0-9]
VARIABLES  [n-z]
FUNKSYMBOLS  [a-m]
PRAEDIKATE [A-Z]
%{
/*init-Code*/
%}

%%
"," {
  printf("KOMMA:%s ",yytext);
}
\( {
  printf("OPENPAR:%s ",yytext);
}
\) {
  printf("CLOSEPAR:%s ",yytext);
}
"top" {
  printf("TOP:%s ",yytext);
}
"bottom" {
  printf("BOTTOM:%s ",yytext);
}
\& {
    printf("UND ");
}
\| {
    printf("ODER ");
}
\~ {
    printf("NOT ");
}
"->" {
    printf("IMPLIZIT ");
}
"<->" {
    printf("AEQUIVALENZ ");
}
"all" {
  printf("ALL:%s ",yytext);
}
"ex" {
  printf("EX:%s ",yytext);
}
{VARIABLES}{INTEGER}* {
  printf("VARIABLES:%s ",yytext);
}
{FUNKSYMBOLS}{INTEGER}* {
  printf("FUNKSYMBOLS:%s ",yytext);
}
{PRAEDIKATE}{INTEGER}* {
  printf("PRAEDIKATE:%s ",yytext);
}



\n {
 /*SKIP leerzeichen und Enter*/
 printf("\n");
 }
" " {
 /*SKIP leerzeichen und Enter*/
 printf("LEERZEICHEN erkannt! ");
 }

%%
int main( int argc, char**argv )    {
++argv, --argc;/*skip over program name*/
if ( argc > 0 )
    yyin = fopen( argv[0], "r" );
else
    yyin = stdin;
yylex();
}
