/* MathML -> R expression conversion routines */

#include "rsbml.h"

SEXP rmathml_SEXP(const ASTNode_t *node) {
  SEXP sym = R_NilValue;
  ASTNodeType_t type = ASTNode_getType(node);
  /*Rprintf("%d\n", ASTNode_getType(node));*/
  switch(type) {
  case AST_PLUS:
  case AST_TIMES:
  case AST_MINUS:
  case AST_DIVIDE:
  case AST_POWER:
    {
      char op[] = { ASTNode_getCharacter(node), '\0' };
      sym = install(op);
    }
    break;
  case AST_INTEGER:
    sym = ScalarReal(ASTNode_getInteger(node));
    break;
  case AST_REAL:
    sym = ScalarReal(ASTNode_getReal(node));
    break;
  case AST_REAL_E: /* R reduces scientific notation to reals */
    /* FIXME: can we preserve this? */
    sym = ScalarReal(ASTNode_getMantissa(node) *
                     pow(10, ASTNode_getExponent(node)));
  case AST_RATIONAL:
    sym = lang3(install("/"), ScalarReal(ASTNode_getNumerator(node)),
                ScalarReal(ASTNode_getDenominator(node)));
    break;
  case AST_NAME:
    sym = install(ASTNode_getName(node));
    break;
  case AST_NAME_TIME:
    /* FIXME: we lose the original symbol here */
    sym = install(".t"); /* the simulation time */
    break;
  case AST_CONSTANT_E: /* FIXME: can we preserve the 'e'? */
    /* R has no constant, but can use exp(1) */
    sym = lang2(install("exp"), ScalarReal(1));
    break;
  case AST_CONSTANT_FALSE:
    sym = ScalarLogical(FALSE);
    break;
  case AST_CONSTANT_PI:
    sym = install("pi");
    break;
  case AST_CONSTANT_TRUE:
    sym = ScalarLogical(TRUE);
    break;
  case AST_LAMBDA:
    {
      SEXP closure, pargs;
      int i, num = ASTNode_getNumChildren(node);
      PROTECT(pargs = allocList(num - 1));
      for (i = 0; i < num - 1; i++) {
	SETCAR(pargs, R_MissingArg);
	SET_TAG(pargs, install(ASTNode_getName(ASTNode_getChild(node, i))));
	pargs = CDR(pargs);
      }
      sym = lang3(install("function"), pargs,
                  lang2(R_BraceSymbol,
                        rmathml_SEXP(ASTNode_getChild(node, num))));
      UNPROTECT(1);
    }
    break;
  case AST_FUNCTION_ABS:
    sym = install("abs");
    break;
  case AST_FUNCTION_ARCCOS:
    sym = install("acos");
    break;
  case AST_FUNCTION_ARCCOSH:
    sym = install("acosh");
    break;
  case AST_FUNCTION_ARCCOT: /* atan(1/x) */
    sym = install("acot");
    break;
  case AST_FUNCTION_ARCCOTH: /* atanh(1/x) */
    sym = install("acoth");
    break;
  case AST_FUNCTION_ARCCSC: /* asin(1/x) */
    sym = install("acsc");
    break;
  case AST_FUNCTION_ARCCSCH: /* asinh(1/x) */
    sym = install("acsch");
    break;
  case AST_FUNCTION_ARCSEC: /* acos(1/x) */
    sym = install("asec");
    break;
  case AST_FUNCTION_ARCSECH: /* acosh(1/x) */
    sym = install("asech");
    break;
  case AST_FUNCTION_ARCSIN:
    sym = install("asin");
    break;
  case AST_FUNCTION_ARCSINH:
    sym = install("asinh");
    break;
  case AST_FUNCTION_ARCTAN:
    sym = install("atan");
    break;
  case AST_FUNCTION_ARCTANH:
    sym = install("atanh");
    break;
  case AST_FUNCTION_CEILING:
    sym = install("ceiling");
    break;
  case AST_FUNCTION_COS:
    sym = install("cos");
    break;
  case AST_FUNCTION_COSH:
    sym = install("cosh");
    break;
  case AST_FUNCTION_COT: /* 1/tan(x) */
    sym = install("cot");
    break;
  case AST_FUNCTION_COTH: /* 1/tanh(x) */
    sym = install("coth");
    break;
  case AST_FUNCTION_CSC: /* 1/sin(x) */
    sym = install("csc");
    break;
  case AST_FUNCTION_CSCH: /* 1/sinh(x) */
    sym = install("csch");
    break;
  case AST_FUNCTION_DELAY: /* special delay function */
    sym = install(".delay");
    break;
  case AST_FUNCTION_EXP:
    sym = install("exp");
    break;
  case AST_FUNCTION_FACTORIAL:
    sym = install("fact");
    break;
  case AST_FUNCTION_FLOOR:
    sym = install("floor");
    break;
  case AST_FUNCTION_LN:
    sym = install("log");
    break;
  case AST_FUNCTION_LOG:
    sym = lang3(install("log"), rmathml_SEXP(ASTNode_getChild(node, 1)),
                rmathml_SEXP(ASTNode_getChild(node, 0)));
    break;
  case AST_FUNCTION_PIECEWISE:
    {
      int i, num = ASTNode_getNumChildren(node), nprotects = 1;
      if (num % 2 > 0) /* odd means we have 'otherwise' */
        sym = rmathml_SEXP(ASTNode_getChild(node, num - 1));
      else if (num > 0) /* it is possible to have no arguments */
        sym = lang3(install("if"), rmathml_SEXP(ASTNode_getChild(node, num - 1)),
                    rmathml_SEXP(ASTNode_getChild(node, num - 2)));
      PROTECT(sym);
      for (i = num - 2 - (num % 2 == 0); i >= 0; i -= 2) {
        PROTECT(sym = lang4(install("if"),
                            rmathml_SEXP(ASTNode_getChild(node, i)),
                            rmathml_SEXP(ASTNode_getChild(node, i-1)), sym));
        nprotects++;
      }
      UNPROTECT(nprotects);
    }
    break;
  case AST_FUNCTION_POWER:
    sym = install("^");
    break;
  case AST_FUNCTION_ROOT:
    /* there is no 'root' function in R, mapped to sqrt() or x^(1/y) here */
    if (ASTNode_isSqrt(ASTNode_getChild(node, 0)))
      sym = lang2(install("sqrt"), rmathml_SEXP(ASTNode_getChild(node, 2)));
    else
      sym = lang3(install("^"), rmathml_SEXP(ASTNode_getChild(node, 2)),
                  lang3(install("/"), ScalarInteger(1),
                        rmathml_SEXP(ASTNode_getChild(node, 1))));
    break;
  case AST_FUNCTION_SEC: /* 1/cos(x) */
    sym = install("sec");
    break;
  case AST_FUNCTION_SECH: /* 1/cosh(x) */
    sym = install("sech");
    break;
  case AST_FUNCTION_SIN:
    sym = install("sin");
    break;
  case AST_FUNCTION_SINH:
    sym = install("sinh");
    break;
  case AST_FUNCTION_TAN:
    sym = install("tan");
    break;
  case AST_FUNCTION_TANH:
    sym = install("tanh");
    break;
    /* FIXME: and, or, and xor broken for > 2 args, use
       ASTNode_reduceToBinary in next version of libsbml */
  case AST_LOGICAL_AND:
    sym = install("&");
    break;
  case AST_LOGICAL_NOT:
    sym = install("!");
    break;
  case AST_LOGICAL_OR:
    sym = install("|");
    break;
  case AST_LOGICAL_XOR:
    sym = install("xor");
    break;
  case AST_RELATIONAL_EQ:
    sym = install("==");
    break;
  case AST_RELATIONAL_GEQ:
    sym = install(">=");
    break;
  case AST_RELATIONAL_GT:
    sym = install(">");
    break;
  case AST_RELATIONAL_LEQ:
    sym = install("<=");
    break;
  case AST_RELATIONAL_LT:
    sym = install("<");
    break;
  case AST_RELATIONAL_NEQ:
    sym = install("!=");
    break;
  default:
    error("Unknown MathML node encountered: %s", ASTNode_getName(node)); 
  }

  /* make a function call if we don't already have one */
  if (TYPEOF(sym) != LANGSXP && ASTNode_getNumChildren(node) > 0) {
    SEXP fun;
    int i, num = ASTNode_getNumChildren(node);
    PROTECT(sym);
    PROTECT(fun = allocVector(LANGSXP, num + 1));
    SETCAR(fun, sym);
    sym = fun;
    fun = CDR(fun);
    for (i = 0; i < num; i++) {
      SETCAR(fun, rmathml_SEXP(ASTNode_getChild(node, i)));
      fun = CDR(fun);
    }
    UNPROTECT(2);
  }
  
  return sym;
}

ASTNode_t *rmathml_ASTNode(SEXP sym) {
  ASTNode_t *node = NULL;
  ASTNodeType_t type;
  /* Rprintf("%d\n", TYPEOF(sym)); */
  /* if (isSymbol(sym)) */
  /*   Rprintf("\t%s\n", CHAR(PRINTNAME(sym))); */
  /* could optimize by caching symbol codes */
  switch(TYPEOF(sym)) {
  case LANGSXP:
    {
      SEXP args = CDR(sym);
      sym = CAR(sym);
      if (sym == install("+"))
        type = AST_PLUS;
      else if (sym == install("*"))
        type = AST_TIMES;
      else if (sym == install("-"))
        type = AST_MINUS;
      else if (sym == install("/"))
        type = AST_DIVIDE;
      else if (sym == install("^"))
        type = AST_POWER;
      else if (sym == install("sqrt"))
        type = AST_FUNCTION_ROOT;
      else if (sym == install("=="))
        type = AST_RELATIONAL_EQ;
      else if (sym == install(">="))
        type = AST_RELATIONAL_GEQ;
      else if (sym == install(">"))
        type = AST_RELATIONAL_GT;
      else if (sym == install("<="))
        type = AST_RELATIONAL_LEQ;
      else if (sym == install("<"))
        type = AST_RELATIONAL_LT;
      else if (sym == install("!="))
        type = AST_RELATIONAL_NEQ;
      else if (sym == install("&"))
        type = AST_LOGICAL_AND;
      else if (sym == install("!"))
        type = AST_LOGICAL_NOT;
      else if (sym == install("|"))
        type = AST_LOGICAL_OR;
      else if (sym == install("xor"))
        type = AST_LOGICAL_XOR;
      else if (sym == install("abs"))
        type = AST_FUNCTION_ABS;
      else if (sym == install("log")) {
        if (LENGTH(args) == 1) /* if log(x) make 'ln' */
          type = AST_FUNCTION_LN;
        else type = AST_FUNCTION_LOG;
      }
      else if (sym == install("exp")) {
        if (isReal(CAR(args))) { /* if exp(1) make 'e' */
          if (asReal(CAR(args)) == 1) {
            type = AST_CONSTANT_E;
            args = CDR(args);
          }
        }
        type = AST_FUNCTION_EXP;
      } else if (sym == install("cos"))
        type = AST_FUNCTION_COS;
      else if (sym == install("sin"))
        type = AST_FUNCTION_SIN;
      else if (sym == install("tan"))
        type = AST_FUNCTION_TAN;
      else if (sym == install("acos"))
        type = AST_FUNCTION_ARCCOS;
      else if (sym == install("acosh"))
        type = AST_FUNCTION_ARCCOSH;
      else if (sym == install("acot"))
        type = AST_FUNCTION_ARCCOT;
      else if (sym == install("acoth"))
        type = AST_FUNCTION_ARCCOTH;
      else if (sym == install("acsc"))
        type = AST_FUNCTION_ARCCSC;
      else if (sym == install("acsch"))
        type = AST_FUNCTION_ARCCSCH;
      else if (sym == install("asec"))
        type = AST_FUNCTION_ARCSEC;
      else if (sym == install("asech"))
        type = AST_FUNCTION_ARCSECH;
      else if (sym == install("asin"))
        type = AST_FUNCTION_ARCSIN;
      else if (sym == install("asinh"))
        type = AST_FUNCTION_ARCSINH;
      else if (sym == install("atan"))
        type = AST_FUNCTION_ARCTAN;
      else if (sym == install("atanh"))
        type = AST_FUNCTION_ARCTANH;
      else if (sym == install("ceiling"))
        type = AST_FUNCTION_CEILING;
      else if (sym == install("cosh"))
        type = AST_FUNCTION_COSH;
      else if (sym == install("cot"))
        type = AST_FUNCTION_COT;
      else if (sym == install("coth"))
        type = AST_FUNCTION_COTH;
      else if (sym == install("csc"))
        type = AST_FUNCTION_CSC;
      else if (sym == install("csch"))
        type = AST_FUNCTION_CSCH;
      else if (sym == install(".delay"))
        type = AST_FUNCTION_DELAY;
      else if (sym == install("fact"))
        type = AST_FUNCTION_FACTORIAL;
      else if (sym == install("floor"))
        type = AST_FUNCTION_FLOOR;
      else if (sym == install("sec"))
        type = AST_FUNCTION_SEC;
      else if (sym == install("sech"))
        type = AST_FUNCTION_SECH;
      else if (sym == install("sinh"))
        type = AST_FUNCTION_SINH;
      else if (sym == install("tanh"))
        type = AST_FUNCTION_TANH;
      else if (sym == install("if")) /* initial 'if' */
        type = AST_FUNCTION_PIECEWISE;
      else type = AST_NAME; /* user-defined function */
      node = ASTNode_createWithType(type);
      if (type == AST_NAME)
        ASTNode_setName(node, CHAR(PRINTNAME(sym)));
      while(!isNull(CAR(args))) {
        ASTNode_addChild(node, rmathml_ASTNode(CAR(args)));
        args = CDR(args);
      }
    }
    break;
  case SYMSXP:
    if (sym == install("pi")) 
      type = AST_CONSTANT_PI;
    else if (sym == install(".t"))
      type = AST_NAME_TIME;
    else if (sym != install("if")) /* ignore 'else if' */
      type = AST_NAME;
    node = ASTNode_createWithType(type);
    if (type == AST_NAME)
      ASTNode_setName(node, CHAR(PRINTNAME(sym)));
    break;
  case REALSXP:
    node = ASTNode_createWithType(AST_REAL);
    ASTNode_setReal(node, asInteger(sym));
    break;
  case INTSXP:
    node = ASTNode_createWithType(AST_INTEGER);
    ASTNode_setInteger(node, asInteger(sym));
    break;
  case LGLSXP:
    if (asLogical(sym))
      type = AST_CONSTANT_TRUE;
    else type = AST_CONSTANT_FALSE;
    node = ASTNode_createWithType(type);
    break;
  case CLOSXP:
    {
      SEXP pargs = CADR(sym);
      int i, npargs = LENGTH(pargs);
      ASTNode_t *child;
      node = ASTNode_createWithType(AST_LAMBDA);
      for (i = 0; i < npargs; i++) {
        child = ASTNode_createWithType(AST_NAME);
        ASTNode_setName(child, CHAR(PRINTNAME(TAG(pargs))));
        ASTNode_addChild(node, child);
        pargs = CDR(pargs);
      }
      ASTNode_addChild(node, rmathml_ASTNode(CADR(CADDR(sym))));
    }
    break;
    default:
      error("Unknown R type encountered: %d", TYPEOF(sym)); 
  }
  
  return node;
}

