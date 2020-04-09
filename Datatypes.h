#include <stdlib.h>

#ifndef DATATYPES_H
#define DATATYPES_H

typedef struct term_s term_s;
typedef struct param_s param_s;
typedef struct atom_s atom_s;
typedef struct formel_s formel_s;


enum typ{
  atom,        //0
  and,         //1
  or,          //2
  not,         //3
  implication, //4
  equ,         //5
  ex,          //6
  all,         //7
  top,         //8
  bottom       //9
};

//term
struct term_s{
  char* varfunc; //termname
  param_s* myparam_s; //kennt seine termliste
  term_s* next; //nächster term
};

//term-list
struct param_s{
  term_s* first;
};

struct atom_s{
		char* name;
		param_s* myparam;
		atom_s* next;
	};

//formula
struct formel_s{
  enum typ typ_s;

  atom_s* atom;
  //param_s* param;

  formel_s* subnot; //formel für ~(Formel)
  formel_s* sublinks; //formel links für -> &,...
  formel_s* subrechts;//formel rechts für -> &,...

  char* var; //Variable für ex und all Quantor
  formel_s* subqant; //formel für Ex und All Quantor

  //int brackets; ???
};



//Verkettete liste funktionen returned termliste

static param_s* addElement(param_s* list, term_s* term)
{
  term->next=list->first;
  list->first=term;
  return list;

}

/*
static void deleteElement(param_s* list, param_s* param)
{
  param_s* temp = list;
  if(param->first->varfunc == temp->first->varfunc){
    //fist addElement
    temp = temp->next;
    return;
  }
  while(temp->next != NULL){
    if(param->first->varfunc == temp->first->varfunc){
      temp = temp->next;
      return;
    }
    temp = temp->next;
  }
  return;
}
*/
static term_s* createTerm(char* varfunc, param_s* t1)
{
  term_s* term=(term_s*) malloc(sizeof(term_s));
  term->varfunc=varfunc;
  term->myparam_s=t1;
  term->next=NULL;
  return term;
}

static formel_s* createFormulaATOM(unsigned int type, atom_s* atom){
  formel_s* retformel = (formel_s*) malloc(sizeof(formel_s));
  retformel->typ_s = type;
  retformel->atom = atom;
  return retformel;
}

static atom_s* createAtom(char* name, param_s* param){
  atom_s* retatom = (atom_s*) malloc(sizeof(atom_s));
  retatom->name = name;
  retatom->myparam = param;
  return retatom;
}

static param_s* createParam(term_s* term,param_s* param){
  param_s* retparam;
  if(param == NULL){
    retparam = (param_s*) malloc(sizeof(param_s));
    retparam->first=term;
  }else{
    retparam = param;
    term->next = retparam->first;
    retparam->first = term;
  }
    return retparam;
}

#endif
