#include <sbml/SBMLTypes.h>

#include <Rinternals.h>
#include <Rdefines.h>

#if LIBSBML_VERSION >= 50600
#define USE_LAYOUT LIBSBML_HAS_PACKAGE_LAYOUT
#endif

// Layout stuff
#ifdef USE_LAYOUT
#if LIBSBML_VERSION >= 50000
#include <sbml/packages/layout/sbml/BoundingBox.h>
#include <sbml/packages/layout/sbml/SpeciesGlyph.h>
#include <sbml/packages/layout/sbml/CompartmentGlyph.h>
#include <sbml/packages/layout/sbml/SpeciesReferenceRole.h>
#include <sbml/packages/layout/sbml/SpeciesReferenceGlyph.h>
#include <sbml/packages/layout/sbml/CubicBezier.h>
#include <sbml/packages/layout/sbml/Curve.h>
#include <sbml/packages/layout/sbml/TextGlyph.h>
#include <sbml/packages/layout/sbml/Dimensions.h>
#include <sbml/packages/layout/sbml/LineSegment.h>
#include <sbml/packages/layout/sbml/GraphicalObject.h>
#include <sbml/packages/layout/sbml/Point.h>
#include <sbml/packages/layout/sbml/Layout.h>
#include <sbml/packages/layout/sbml/ReactionGlyph.h>
#include <sbml/packages/layout/extension/LayoutExtension.h>
#include <sbml/packages/layout/extension/LayoutModelPlugin.h>
#else
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

/* shared internal functions */
SEXP rsbml_create_doc_ptr(SBMLDocument_t *doc);
Rboolean rsbml_errors(SBMLDocument_t *doc);
SEXP rmathml_SEXP(const ASTNode_t *node);
ASTNode_t *rmathml_ASTNode(SEXP sym);

/* C wrappers for layout plugin API */
#ifdef USE_LAYOUT
#if LIBSBML_VERSION >= 50000
#ifdef __cplusplus
extern "C" {
#endif
  typedef struct LayoutModelPlugin LayoutModelPlugin_t;
  Layout_t *LayoutModelPlugin_createLayout(LayoutModelPlugin_t *plugin);
  int LayoutModelPlugin_getNumLayouts(LayoutModelPlugin_t *plugin);
  Layout_t *LayoutModelPlugin_getLayout(LayoutModelPlugin_t *plugin,
                                        unsigned int index);
  int SBase_enablePackage(SBase_t *sbase, const char *pkgURI,
                          const char *pkgPrefix, int flag);
#ifdef __cplusplus
}
#endif
/* libsbml includes this only for C++ */
#ifndef __cplusplus
typedef enum
  {
    SBML_LAYOUT_BOUNDINGBOX           = 100
    , SBML_LAYOUT_COMPARTMENTGLYPH      = 101
    , SBML_LAYOUT_CUBICBEZIER           = 102
    , SBML_LAYOUT_CURVE                 = 103
    , SBML_LAYOUT_DIMENSIONS            = 104
    , SBML_LAYOUT_GRAPHICALOBJECT       = 105
    , SBML_LAYOUT_LAYOUT                = 106   
    , SBML_LAYOUT_LINESEGMENT           = 107   
    , SBML_LAYOUT_POINT                 = 108    
    , SBML_LAYOUT_REACTIONGLYPH         = 109    
    , SBML_LAYOUT_SPECIESGLYPH          = 110    
    , SBML_LAYOUT_SPECIESREFERENCEGLYPH = 111
    , SBML_LAYOUT_TEXTGLYPH             = 112
  } SBMLLayoutTypeCode_t;
#endif
#endif
#endif
