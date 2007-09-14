#include <Rinternals.h>
#include <Rdefines.h>

#include <SBMLTypes.h>

// Layout stuff
#ifdef USE_LAYOUT
#include <layout/BoundingBox.h>
#include <layout/SpeciesGlyph.h>
#include <layout/CompartmentGlyph.h>
#include <layout/SpeciesReferenceRole.h>
#include <layout/SpeciesReferenceGlyph.h>
#include <layout/CubicBezier.h>
#include <layout/Curve.h>
#include <layout/TextGlyph.h>
#include <layout/Dimensions.h>
#include <layout/LineSegment.h>
#include <layout/GraphicalObject.h>
#include <layout/Point.h>
#include <layout/Layout.h>
#include <layout/ReactionGlyph.h>
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

