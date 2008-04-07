#include "rsbml.h"
#ifdef LIBSBML3
#include <sbml/xml/XMLError.h>
#else
#include <sbml/xml/ParseMessage.h>
#endif

static SEXP
#ifdef LIBSBML3
rsbml_problem(XMLError_t *error)
#else
rsbml_problem(ParseMessage_t *msg)
#endif
{
  SEXP r_problem, r_names;
  PROTECT(r_problem = NEW_LIST(3));
  
  #ifdef LIBSBML3
  SET_VECTOR_ELT(r_problem, 0, ScalarInteger(XMLError_getLine(error)));
  SET_VECTOR_ELT(r_problem, 1, ScalarInteger(XMLError_getColumn(error)));
  SET_VECTOR_ELT(r_problem, 2, mkString(XMLError_getMessage(error)));
  #else
  SET_VECTOR_ELT(r_problem, 0, ScalarInteger(ParseMessage_getLine(msg)));
  SET_VECTOR_ELT(r_problem, 1, ScalarInteger(ParseMessage_getColumn(msg)));
  SET_VECTOR_ELT(r_problem, 2, mkString(ParseMessage_getMessage(msg)));
  #endif
  
  PROTECT(r_names = NEW_CHARACTER(3));
  SET_STRING_ELT(r_names, 0, mkChar("line"));
  SET_STRING_ELT(r_names, 1, mkChar("column"));
  SET_STRING_ELT(r_names, 2, mkChar("message"));
  SET_NAMES(r_problem, r_names);
  
  UNPROTECT(2);
  return r_problem;
}

static SEXP
rsbml_problems(SBMLDocument_t *doc)
{
  SEXP r_problems, r_warnings, r_errors, r_fatals, r_infos, r_names;
  int i, num_infos = 0, num_warnings = 0, num_errors = 0, num_fatals = 0;
  
  PROTECT(r_problems = NEW_LIST(4));
  
  #ifdef LIBSBML3
  for (i = 0; i < SBMLDocument_getNumErrors(doc); i++) {
    XMLError_t *error = (XMLError_t *)SBMLDocument_getError(doc, i);
    if (XMLError_isInfo(error))
      num_infos++;
    else if (XMLError_isWarning(error))
      num_warnings++;
    else if (XMLError_isError(error))
      num_errors++;
    else num_fatals++;
  }
  #else
  num_infos = 0;
  num_warnings = SBMLDocument_getNumWarnings(doc);
  num_errors = SBMLDocument_getNumErrors(doc);
  num_fatals = SBMLDocument_getNumFatals(doc);
  #endif
  
  r_infos = NEW_LIST(num_infos);
  SET_VECTOR_ELT(r_problems, 0, r_infos);
  r_warnings = NEW_LIST(num_warnings);
  SET_VECTOR_ELT(r_problems, 1, r_warnings);
  r_errors = NEW_LIST(num_errors);
  SET_VECTOR_ELT(r_problems, 2, r_errors);
  r_fatals = NEW_LIST(num_fatals);
  SET_VECTOR_ELT(r_problems, 3, r_fatals);
  
  PROTECT(r_names = NEW_CHARACTER(4));
  SET_STRING_ELT(r_names, 0, mkChar("info"));
  SET_STRING_ELT(r_names, 1, mkChar("warning"));
  SET_STRING_ELT(r_names, 2, mkChar("error"));
  SET_STRING_ELT(r_names, 3, mkChar("fatal"));
  SET_NAMES(r_problems, r_names);
  UNPROTECT(1);
  
  #ifdef LIBSBML3
  num_infos = num_warnings = num_errors = num_fatals = 0;
  for (i = 0; i < SBMLDocument_getNumErrors(doc); i++) {
    XMLError_t *error = (XMLError_t *)SBMLDocument_getError(doc, i);
    SEXP error_list;
    int index;
    if (XMLError_isInfo(error)) {
      index = num_infos++;
      error_list = r_infos;
    } else if (XMLError_isWarning(error)) {
      index = num_warnings++;
      error_list = r_warnings;
    } else if (XMLError_isError(error)) {
      index = num_errors++;
      error_list = r_errors;
    } else {
      index = num_fatals++;
      error_list = r_fatals;
    }
    SET_VECTOR_ELT(error_list, index, rsbml_problem(error));
  }
  #else
  for (i = 0; i < SBMLDocument_getNumWarnings(doc); i++)
    SET_VECTOR_ELT(r_warnings, i, rsbml_problem(SBMLDocument_getWarning(doc, i)));
  for (i = 0; i < SBMLDocument_getNumErrors(doc); i++)
    SET_VECTOR_ELT(r_errors, i, rsbml_problem(SBMLDocument_getError(doc, i)));
  for (i = 0; i < SBMLDocument_getNumFatals(doc); i++)
    SET_VECTOR_ELT(r_fatals, i, rsbml_problem(SBMLDocument_getFatal(doc, i)));
  #endif
  
  UNPROTECT(1);
  return r_problems;
}

SEXP
rsbml_R_problems(SEXP r_doc)
{
  SBMLDocument_t *doc = R_ExternalPtrAddr(r_doc);
  return rsbml_problems(doc);
}

Rboolean rsbml_errors(SBMLDocument_t *doc)
{
#ifdef LIBSBML3
  int i;
  for (i = 0; i < SBMLDocument_getNumErrors(doc); i++) {
    XMLError_t *error = (XMLError_t *)SBMLDocument_getError(doc, i);
    if (XMLError_isError(error) || XMLError_isFatal(error))
      return(TRUE);
  }
  return(FALSE);
#else
  return (SBMLDocument_getNumErrors(doc) || SBMLDocument_getNumFatals(doc));
#endif
}

static Rboolean
rsbml_check_doc(SBMLDocument_t *doc)
{
  #ifdef LIBSBML3
  SBMLDocument_checkConsistency(doc); /* memory leaks in 2.3.4? */
  return !SBMLDocument_getNumErrors(doc);
  #else
  return !SBMLDocument_getNumWarnings(doc) && !SBMLDocument_getNumErrors(doc) &&
    !SBMLDocument_getNumFatals(doc);
  #endif
}

SEXP
rsbml_R_check_doc(SEXP r_doc)
{
  SBMLDocument_t *doc = R_ExternalPtrAddr(r_doc);
  return ScalarLogical(rsbml_check_doc(doc));
}
