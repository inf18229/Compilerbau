#include <stdlib.h>

#ifndef DATATYPES_H
#define DATATYPES_H

/*===================Create DATATYPES_H====================*/
typedef struct term_s term_s;
typedef struct param_s param_s;
typedef struct atom_s atom_s;
typedef struct formel_s formel_s;
/*========================================================*/

/*================Function forward definition==============*/
static void printTermList(param_s* tl );
static void printFormula(formel_s* f);
static void printTerm(term_s* t);
static void printAtom(atom_s* a);
/*========================================================*/

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

//formel
struct formel_s{
  enum typ typ_s;

  atom_s* atom;

  formel_s* subnot; //formel für ~(Formel)
  formel_s* sublinks; //formel links für -> &,...
  formel_s* subrechts;//formel rechts für -> &,...

  char* var; //Variable für ex und all Quantor
  formel_s* subqant; //formel für Ex und All Quantor

  int brackets;
};

/*===================Definition Datatype functions====================*/
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
/*========================================================*/

/*===================Print Datatype Function====================*/
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

/*========================================================*/


/*===================Transform to NNF Functions====================*/
static void transformNNF1(formel_s* f){
      formel_s* tmp1;
      formel_s* tmp2;
      formel_s* tmp3;
      switch(f->typ_s){
         case atom:
            break;// do nothing
         case and:
            transformNNF1(f->sublinks);
            transformNNF1(f->subrechts);break;
         case or:
            transformNNF1(f->sublinks);
            transformNNF1(f->subrechts);break;
         case not:
            transformNNF1(f->subnot);
            break;
         case implication:
            tmp1 = createFormulaNOT(not, f->sublinks);
            f->typ_s = or;
            f->sublinks = tmp1;
            transformNNF1(f->sublinks);
            transformNNF1(f->subrechts); break;
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
            transformNNF1(f->sublinks);
            transformNNF1(f->subrechts);
            break;

         case all: transformNNF1(f->subqant);
          break;
         case ex: transformNNF1(f->subqant);
          break;
         case top:
          break;
         case bottom:
          break;
         default: printf("ERROR in transformNNF");
          break;
      }
   }

static void transformNNF2(formel_s* f){
  formel_s* tmp1;
  formel_s* tmp2;
  switch(f->typ_s){
     case atom:
        break;    // do nothing
     case and:
        transformNNF2(f->sublinks);
        transformNNF2(f->subrechts);
        break;
     case or:
        transformNNF2(f->sublinks);
        transformNNF2(f->subrechts);
        break;
     case not:
        switch(f->subnot->typ_s){
          case all:
            tmp1 = createFormulaNOT(not, f->subnot->subqant);
            f->typ_s = ex;
            f->var = f->subnot->var;
            f->subqant = tmp1;
            transformNNF2(f->subqant);
            break;
          case ex:
            tmp1 = createFormulaNOT(not, f->subnot->subqant);
            f->typ_s = all;
            f->var = f->subnot->var;
            f->subqant = tmp1;
            transformNNF2(f->subqant);
            break;
          case and:
            tmp1 = createFormulaNOT(not, f->subnot->sublinks);
            tmp2 = createFormulaNOT(not, f->subnot->subrechts);
            f->typ_s=or;
            f->sublinks = tmp1;
            f->subrechts = tmp2;
            transformNNF2(f->sublinks);
            transformNNF2(f->subrechts);
            break;
          case or:
            tmp1 = createFormulaNOT(not, f->subnot->sublinks);
            tmp2 = createFormulaNOT(not, f->subnot->subrechts);
            f->typ_s=and;
            f->sublinks = tmp1;
            f->subrechts = tmp2;
            transformNNF2(f->sublinks);
            transformNNF2(f->subrechts);
            break;
          default: break;
        }
        transformNNF2(f->subnot);
        break;


     case all:
      transformNNF2(f->subqant);
      break;
     case ex:
      transformNNF2(f->subqant);
      break;
     case top:
      break;
     case bottom:
      break;
     default: printf("ERROR in transformNNF2\n");break;
  }
}


static void transformNNF3(formel_s* f){
  formel_s* tmp1;
      switch(f->typ_s){
      case atom:
        break;
      case and:
        transformNNF3(f->sublinks);
        transformNNF3(f->subrechts);
        break;
      case or:
        transformNNF3(f->sublinks);
        transformNNF3(f->subrechts);
        break;
      case not:
        switch(f->subnot->typ_s){
          case not:
            tmp1 = (formel_s*) (formel_s*) malloc(sizeof(formel_s));
            tmp1 = f->subnot->subnot;
            *(f) = *(tmp1);
            transformNNF3(f);
            break;
         case top:
            f->typ_s = bottom;
            break;
         case bottom:
            f->typ_s = top;
            break;
         default:
            transformNNF3(f->subnot);
         break;
       }
       break;
      case all:
        transformNNF3(f->subqant);
        break;
      case ex:
        transformNNF3(f->subqant);
        break;
      case top:
        break;
      case bottom:
        break;
      default:
        printf("ERROR in transformNNF3\n");
        break;
   }
}
/*========================================================*/

#endif
