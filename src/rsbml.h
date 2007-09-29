#include <Rinternals.h>
#include <Rdefines.h>

#include <sbml/SBMLTypes.h>

// Layout stuff
#ifdef USE_LAYOUT
#include <sbml/layout/BoundingBox.h>
#include <sbml/layout/SpeciesGlyph.h>
#include <sbml/layout/CompartmentGlyph.h>
#include <sbml/layout/SpeciesReferenceRole.h>
#include <sbml/layout/SpeciesReferenceGlyph.h>
#include <sbml/layout/CubicBezier.h>
#include <sbml/layout/Curve.h>
#include <sbml/layout/TextGlyph.h>
#include <sbml/layout/Dimensions.h>
#include <sbml/layout/LineSegment.h>
#include <sbml/layout/GraphicalObject.h>
#include <sbml/layout/Point.h>
#include <sbml/layout/Layout.h>
#include <sbml/layout/ReactionGlyph.h>
#endif

/* functions callable from R */
SEXP rsbml_R_problems(SEXP r_doc);
SEXP rsbml_R_check_doc(SEXP r_doc);
SEXP rsbml_R_build_dom(SEXP r_doc);
SEXP rsbml_R_build_doc(SEXP r_doc);
SEXP rsbml_R_build_graph(SEXP r_doc);
SEXP rsbml_R_write_doc(SEXP r_doc, SEXP r_filename);
SEXP rsbml_R_write_doc_to_string(SEXP r_doc);
SEXP rsbml_R_read_doc(SEXP r_doc, SEXP r_filename);
SEXP rsbml_R_read_doc_from_string(SEXP r_xml, SEXP r_validate);

/* shared internal function */
SEXP rsbml_create_doc_ptr(SBMLDocument_t *doc);

