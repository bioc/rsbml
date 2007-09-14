#include "rsbml.h"
#include <R_ext/Rdynload.h>

#define CENTRY(a, n) {#a, (DL_FUNC) &rsbml_R_ ## a, n}

static R_CallMethodDef callMethods[] =
{
   CENTRY(problems, 1),
   CENTRY(check_doc, 1),
   CENTRY(build_doc, 1),
   CENTRY(build_dom, 1),
   CENTRY(build_graph, 1),
   CENTRY(read_doc, 2),
   CENTRY(read_doc_from_string, 2),
   CENTRY(write_doc, 2),
   CENTRY(write_doc_to_string, 1)
};

void
R_init_rsbml(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(dll, TRUE);
}
