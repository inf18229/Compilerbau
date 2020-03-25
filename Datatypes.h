#ifndef DATATYPES_H
#define DATATYPES_H

struct term{
  char* varfunc;
  struct param* arg; // f(f(x)) -->term(f,term(f,term(x,NULL)))
};
struct param{
  struct term* first;
  struct param* next;
};

struct formel{
  enum typ;
  char* pred;
  struct param* param;
  struct formel* sub1;
  struct formel* sub2;
};
enum typ{
  'atom',
  'and',
  'or',
  'not',
  'implication',
  'equ',
  'ex',
  'all',
  'top',
  'bottom'
};

//Verkettete liste funktionen
param* addElement(struct param *list, struct param *param)
{
  param->next=list;
  return param;

}
param* deleteElement(struct param *list, struct param *param)
{


}

term* createTerm(char* varfunc, struct param* t1)
{
  struct term *term;
  term=new(term);
  term->varfunc=varfunc;
  term->param=t1;
  return term;
}

#endif
