#include <stdlib.h>

#ifndef DATATYPES_H
#define DATATYPES_H

typedef struct term_s term_s;
typedef struct param_s param_s;
typedef struct atom_s atom_s;
typedef struct formel_s formel_s;

static void printTermList(param_s* tl );
static void printFormula(formel_s* f);
static void printTerm(term_s* t);
static void printAtom(atom_s* a);


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

  int brackets;
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

static formel_s* createFormulaBRACK(formel_s* formel, int countBrackets)
{
    formel_s* retformel = (formel_s*) malloc(sizeof(formel_s));
    retformel = formel;
    retformel->brackets = countBrackets;  //was hab ich davon? Ich überschreibe ja dann jedesmal die Zahl der Klammern
    return retformel;
}

static formel_s* createFormulaNOT(unsigned int type,  formel_s* subformel){
    formel_s* retformel = (formel_s*) malloc(sizeof(formel_s));
    retformel->typ_s = type;
    retformel->subnot = subformel;
    return retformel;
}

static formel_s* createFormulaBOOL(unsigned int type){
      formel_s* retformel = (formel_s*) malloc(sizeof(formel_s));
      retformel->typ_s = type;

      return retformel;
}
static formel_s* createFormulaJUNKT(unsigned int type,  formel_s* leftsub, formel_s* rightsub){
      formel_s* retformel = (formel_s*) malloc(sizeof(formel_s));
      retformel->typ_s = type;

      retformel->sublinks = leftsub;
      retformel->subrechts = rightsub;
      return retformel;
}
static formel_s* createFormulaQUANT(unsigned int type, formel_s* subformel, char* var){
      formel_s* retformel = (formel_s*) malloc(sizeof(formel_s));
      retformel->typ_s = type;

      retformel->subqant = subformel;
      retformel->var = var;
      return retformel;
   }

static void printAtom(atom_s* a){
  printf("%s",a->name);
  if(a->myparam == NULL){}
  else{
    printf("(");
    printTermList(a->myparam);
    printf(")");
  }
}

static void printTermList(param_s* tl ){
  term_s* myt = tl->first;

  while(myt != NULL){
     printTerm(myt);
     if(myt->myparam_s != NULL){
        printf("(");
        printTermList(myt->myparam_s);
        printf(")");
    }
     myt = myt->next;
  }

}

static void printTerm(term_s* t){

   	printf("%s",t->varfunc);
   	if(t->next == NULL){

   	}
   	else{
         printf(",");
   	}
   }

static int rekursionstiefe = 0;

static void printFormula(formel_s* f){
  for(int i=0;i<rekursionstiefe;i++){
    printf("  ");
  }
  switch(f->typ_s){
    case atom:
              printAtom(f->atom);
               break;

    case and: printf("AND\n");
              ++rekursionstiefe;
              printFormula(f->sublinks);
              --rekursionstiefe;
              printf("\n");
              ++rekursionstiefe;
              printFormula(f->subrechts);
              --rekursionstiefe;
              break;

    case or: printf("OR\n");
             ++rekursionstiefe;
             printFormula(f->sublinks);
             --rekursionstiefe;
             printf("\n");
             ++rekursionstiefe;
             printFormula(f->subrechts);
             --rekursionstiefe;
             break;
    case implication: printf("IMPL\n");
               ++rekursionstiefe;
               printFormula(f->sublinks);
               --rekursionstiefe;
               printf("\n");
               ++rekursionstiefe;
               printFormula(f->subrechts);
               --rekursionstiefe;
               break;
    case equ: printf("EQU\n");
              ++rekursionstiefe;
              printFormula(f->sublinks);
              --rekursionstiefe;
              printf("\n");
              ++rekursionstiefe;
              printFormula(f->subrechts);
              --rekursionstiefe;
              break;
    case not: printf("NOT\n");
              ++rekursionstiefe;
              printFormula(f->subnot);
              --rekursionstiefe;
              break;
    case all: printf("ALL ");
              printf("%s \n",f->var);
              ++rekursionstiefe;
              printFormula(f->subqant);
              --rekursionstiefe;
              break;
    case ex: printf("EX ");
             printf("%s \n",f->var);
             ++rekursionstiefe;
             printFormula(f->subqant);
             --rekursionstiefe;
             break;
    case top: printf("TOP");
              break;
    case bottom: printf("BOTTOM");
                 break;
    default: printf("ERROR in printFormula function!\n");
             break;
  }
}

static void transformNNF1(formel_s* f){
      formel_s* tmp1;
      formel_s* tmp2;
      formel_s* tmp3;
      switch(f->typ_s){
         case atom:
            break;// do nothing
         case and:
            transformNNF1(f->sublinks);transformNNF1(f->subrechts);break;
         case or:
            transformNNF1(f->sublinks);transformNNF1(f->subrechts);break;
         case not:
            transformNNF1(f->subnot); break;
         case implication:
            tmp1 = createFormulaNOT(not, f->sublinks);
            f->typ_s = or;
            f->sublinks = tmp1;
            transformNNF1(f->sublinks);transformNNF1(f->subrechts); break;
            break;

         case equ:
            tmp1 = createFormulaJUNKT(and,  f->sublinks, f->subrechts);
            tmp2 = createFormulaNOT(not, f->subrechts);
            tmp3 = createFormulaNOT(not, f->sublinks);
            f->typ_s = or;
            f->sublinks = tmp1;
            f->sublinks->brackets = 1;
            tmp1 = createFormulaJUNKT(and,  f->sublinks, f->subrechts);
            f->subrechts = tmp1;
            f->subrechts->brackets = 1;
            f->subrechts->sublinks = tmp3;
            f->subrechts->subrechts = tmp2;
            transformNNF1(f->sublinks);transformNNF1(f->subrechts);
            break;

         case all: transformNNF1(f->subqant); break;
         case ex: transformNNF1(f->subqant);break;
         case top:break;
         case bottom:break;
         default: printf("ERROR in transformNNF");break;
      }


   }

#endif
