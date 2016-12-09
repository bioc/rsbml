#include "rsbml.h"
#include <R_ext/Parse.h>
#include <stdlib.h>

#define LIST_OF(var, class, func, field, id_attr) \
({ \
  int i, len = class ## _getNum ## field ## s(var); \
  SEXP r_list, r_names; \
  PROTECT(r_list = NEW_LIST(len)); \
  if (id_attr) \
    PROTECT(r_names = NEW_CHARACTER(len)); \
  for (i = 0; i < len; i++) { \
    SEXP r_element = rsbml_build_dom_ ## func(class ## _get ## field(var, i)); \
    SET_VECTOR_ELT(r_list, i, r_element); \
    if (id_attr) { \
      SEXP r_name = GET_SLOT(r_element, install(id_attr)); \
      if (GET_LENGTH(r_name)) \
        SET_STRING_ELT(r_names, i, STRING_ELT(r_name, 0)); \
    } \
  } \
  if (id_attr) { \
    SET_NAMES(r_list, r_names); \
    UNPROTECT(1); \
  } \
  UNPROTECT(1); \
  r_list; \
})

#include <Rversion.h>

#if (R_VERSION >= R_Version(2,5,0))
#define SRCFILE , R_NilValue
#else
#define SRCFILE
#endif

#define SET_MATH(class, var, Field, field) ({                      \
  SEXP lang, expr;                                                 \
  PROTECT(lang = rmathml_SEXP(class ## _get ## Field (var)));      \
  expr = allocVector(EXPRSXP, 1);                                  \
  SET_VECTOR_ELT(expr, 0, lang);                                   \
  SET_SLOT(r_ ## var, install(#field), expr);                      \
  UNPROTECT(1);                                                    \
})

#if LIBSBML_VERSION >= 50000
#define Model_getNumLayouts(m) ({                                       \
      LayoutModelPlugin_t *mplugin =                                    \
        (LayoutModelPlugin_t *)(SBase_getPlugin((SBase_t *)m, "layout")); \
      LayoutModelPlugin_getNumLayouts(mplugin);                         \
})
#define Model_getLayout(m, i) ({                                        \
      LayoutModelPlugin_t *mplugin =                                    \
        (LayoutModelPlugin_t *)(SBase_getPlugin((SBase_t *)m, "layout")); \
      LayoutModelPlugin_getLayout(mplugin, i);                          \
})
#else
#define Model_getNumLayouts(m) \
  ListOf_size(Model_getListOfLayouts(m));
#endif


static SEXP
rsbml_build_dom_cvterm(CVTerm_t *cvterm)
{
  SEXP r_cvterm;
  
  PROTECT(r_cvterm = NEW_OBJECT(MAKE_CLASS("CVTerm")));
  
  const char *qualifier_type;
  switch(CVTerm_getQualifierType(cvterm))
  {
    case MODEL_QUALIFIER:
      qualifier_type = "model";
    break;
    case BIOLOGICAL_QUALIFIER:
      qualifier_type = "biological";
    break;
    default:
      qualifier_type = "unknown";
  }
  SET_SLOT(r_cvterm, install("qualifierType"), mkString(qualifier_type));
  
  switch(CVTerm_getModelQualifierType(cvterm))
  {
    case BQM_IS:
      qualifier_type = "is";
    break;
    case BQM_IS_DESCRIBED_BY:
      qualifier_type = "isDescribedBy";
    break;
    default:
      qualifier_type = "unknown";
  }
  SET_SLOT(r_cvterm, install("modelQualifierType"), mkString(qualifier_type));
  
  switch(CVTerm_getBiologicalQualifierType(cvterm))
  {
    case BQB_IS:
      qualifier_type = "is";
    break;
    case BQB_HAS_PART:
      qualifier_type = "hasPart";
    break;
    case BQB_IS_PART_OF:
      qualifier_type = "isPartOf";
    break;
    case BQB_IS_VERSION_OF:
      qualifier_type = "isVersionOf";
    break;
    case BQB_HAS_VERSION:
      qualifier_type = "hasVersion";
    break;
    case BQB_IS_HOMOLOG_TO:
      qualifier_type = "isHomologTo";
    break;
    case BQB_IS_DESCRIBED_BY:
      qualifier_type = "isDescribedBy";
    break;
#if LIBSBML_VERSION >= 30300
  case BQB_IS_ENCODED_BY:
    qualifier_type = "isEncodedBy";
    break;
  case BQB_ENCODES:
    qualifier_type = "encodes";
    break;
  case BQB_OCCURS_IN:
    qualifier_type = "occursIn";
    break;
#endif
    default:
      qualifier_type = "unknown";
  }
  SET_SLOT(r_cvterm, install("biologicalQualifierType"), mkString(qualifier_type));
  
  XMLAttributes_t *resources = CVTerm_getResources(cvterm);
  SEXP r_resources;
  PROTECT(r_resources = NEW_CHARACTER(XMLAttributes_getLength(resources)));
  for (int i = 0; i < GET_LENGTH(r_resources); i++)
    SET_STRING_ELT(r_resources, i, mkChar(XMLAttributes_getValue(resources, i)));
  SET_SLOT(r_cvterm, install("resources"), r_resources);
  
  UNPROTECT(2);
  
  return r_cvterm;
}

static SEXP
rsbml_build_dom_s_base(SEXP r_s_base, SBase_t *s_base)
{
  if (SBase_isSetMetaId(s_base))
    SET_SLOT(r_s_base, install("metaId"), mkString(SBase_getMetaId(s_base)));
  if (SBase_isSetNotes(s_base))
    SET_SLOT(r_s_base, install("notes"), mkString(SBase_getNotesString(s_base)));
  if (SBase_isSetAnnotation(s_base))
    SET_SLOT(r_s_base, install("annotation"), mkString(SBase_getAnnotationString(s_base)));
  if (SBase_isSetSBOTerm(s_base))
    SET_SLOT(r_s_base, install("sboTerm"),
             ScalarInteger(SBase_getSBOTerm(s_base)));
  SET_SLOT(r_s_base, install("cvTerms"), LIST_OF(s_base, SBase, cvterm, CVTerm, NULL));
  return r_s_base;
}

static SEXP
rsbml_build_dom_species(Species_t *species)
{
  SEXP r_species;
  
  PROTECT(r_species = NEW_OBJECT(MAKE_CLASS("Species")));
  
  rsbml_build_dom_s_base(r_species, (SBase_t *)species);
  
  if (Species_isSetId(species))
    SET_SLOT(r_species, install("id"), mkString(Species_getId(species)));
  if (Species_isSetName(species))
    SET_SLOT(r_species, install("name"), mkString(Species_getName(species)));
  if (Species_isSetCompartment(species))
    SET_SLOT(r_species, install("compartment"), mkString(Species_getCompartment(species)));
  if (Species_isSetInitialAmount(species))
    SET_SLOT(r_species, install("initialAmount"), ScalarReal(Species_getInitialAmount(species)));
  if (Species_isSetInitialConcentration(species))
    SET_SLOT(r_species, install("initialConcentration"), ScalarReal(Species_getInitialConcentration(species)));
  if (Species_isSetSubstanceUnits(species))
    SET_SLOT(r_species, install("substanceUnits"), mkString(Species_getSubstanceUnits(species)));
  if (Species_isSetSpatialSizeUnits(species))
    SET_SLOT(r_species, install("spatialSizeUnits"), mkString(Species_getSpatialSizeUnits(species)));
  if (Species_isSetUnits(species))
    SET_SLOT(r_species, install("units"), mkString(Species_getUnits(species)));
  SET_SLOT(r_species, install("hasOnlySubstanceUnits"), ScalarLogical(Species_getHasOnlySubstanceUnits(species)));
  SET_SLOT(r_species, install("boundaryCondition"), ScalarLogical(Species_getBoundaryCondition(species)));
  if (Species_isSetCharge(species))
    SET_SLOT(r_species, install("charge"), ScalarInteger(Species_getCharge(species)));
  SET_SLOT(r_species, install("constant"), ScalarLogical(Species_getConstant(species)));
  
  UNPROTECT(1);
  return r_species;
}

static SEXP
rsbml_build_dom_parameter(Parameter_t *parameter)
{
  SEXP r_parameter;
  
  PROTECT(r_parameter = NEW_OBJECT(MAKE_CLASS("Parameter")));
  
  rsbml_build_dom_s_base(r_parameter, (SBase_t *)parameter);
  
  if (Parameter_isSetId(parameter))
    SET_SLOT(r_parameter, install("id"), mkString(Parameter_getId(parameter)));
  if (Parameter_isSetName(parameter))
    SET_SLOT(r_parameter, install("name"), mkString(Parameter_getName(parameter)));
  if (Parameter_isSetValue(parameter))
    SET_SLOT(r_parameter, install("value"), ScalarReal(Parameter_getValue(parameter)));
  if (Parameter_isSetUnits(parameter))
    SET_SLOT(r_parameter, install("units"), mkString(Parameter_getUnits(parameter)));
  SET_SLOT(r_parameter, install("constant"), ScalarLogical(Parameter_getConstant(parameter)));
  
  UNPROTECT(1);
  
  return r_parameter;
}

static SEXP
rsbml_build_dom_kinetic_law(KineticLaw_t *kinetic_law)
{
  SEXP r_kinetic_law;
  
  PROTECT(r_kinetic_law = NEW_OBJECT(MAKE_CLASS("KineticLaw")));
  
  rsbml_build_dom_s_base(r_kinetic_law, (SBase_t *)kinetic_law);
  
  if (KineticLaw_isSetMath(kinetic_law))
    SET_MATH(KineticLaw, kinetic_law, Math, math);
  if (KineticLaw_isSetFormula(kinetic_law))
  SET_SLOT(r_kinetic_law, install("formula"), mkString(KineticLaw_getFormula(kinetic_law)));
  if (KineticLaw_isSetTimeUnits(kinetic_law))
    SET_SLOT(r_kinetic_law, install("timeUnits"), mkString(KineticLaw_getTimeUnits(kinetic_law)));
  if (KineticLaw_isSetSubstanceUnits(kinetic_law))
    SET_SLOT(r_kinetic_law, install("substanceUnits"), mkString(KineticLaw_getSubstanceUnits(kinetic_law)));
  
  SET_SLOT(r_kinetic_law, install("parameters"), 
    LIST_OF(kinetic_law, KineticLaw, parameter, Parameter, "id"));
  
  UNPROTECT(1);
  return r_kinetic_law;
}

static void
rsbml_build_dom_simple_species_reference(SEXP r_simple_species_reference,
  SpeciesReference_t *simple_species_reference)
{ 
  rsbml_build_dom_s_base(r_simple_species_reference, (SBase_t *)simple_species_reference);
  
  if (SpeciesReference_isSetSpecies(simple_species_reference))
    SET_SLOT(r_simple_species_reference, install("species"), 
      mkString(SpeciesReference_getSpecies(simple_species_reference)));
  #ifdef USE_LAYOUT
  if (SpeciesReference_isSetId(simple_species_reference))
    SET_SLOT(r_simple_species_reference, install("id"), 
      mkString(SpeciesReference_getId(simple_species_reference)));
  #endif
}

static SEXP
rsbml_build_dom_stoichiometry_math(const StoichiometryMath_t *stoichiometry_math)
{
  SEXP r_stoichiometry_math;
  
  PROTECT(r_stoichiometry_math = NEW_OBJECT(MAKE_CLASS("StoichiometryMath")));
  
  SET_MATH(StoichiometryMath, stoichiometry_math, Math, math);
  
  return r_stoichiometry_math;
}

static SEXP
rsbml_build_dom_species_reference(SpeciesReference_t *species_reference)
{
  SEXP r_species_reference;
  
  PROTECT(r_species_reference = NEW_OBJECT(MAKE_CLASS("SpeciesReference")));
  
  rsbml_build_dom_simple_species_reference(r_species_reference, 
    (SpeciesReference_t *)species_reference);
  
  if (SpeciesReference_isSetStoichiometryMath(species_reference)) {
    SET_SLOT(r_species_reference, install("stoiciometryMath"),
      rsbml_build_dom_stoichiometry_math(SpeciesReference_getStoichiometryMath(species_reference)));
  }
  
  SET_SLOT(r_species_reference, install("stoichiometry"), 
    ScalarReal(SpeciesReference_getStoichiometry(species_reference)));
  SET_SLOT(r_species_reference, install("denominator"), 
    ScalarInteger(SpeciesReference_getDenominator(species_reference)));
  
  UNPROTECT(1);
  
  return r_species_reference;
}

static SEXP
rsbml_build_dom_modifier_species_reference(SpeciesReference_t *modifier_species_reference)
{
  SEXP r_modifier_species_reference;
  
  PROTECT(r_modifier_species_reference = NEW_OBJECT(MAKE_CLASS("ModifierSpeciesReference")));
  
  rsbml_build_dom_simple_species_reference(r_modifier_species_reference, 
    (SpeciesReference_t *)modifier_species_reference);
  
  UNPROTECT(1);
  
  return r_modifier_species_reference;
}

static SEXP
rsbml_build_dom_reaction(Reaction_t *reaction)
{
  SEXP r_reaction;
  
  PROTECT(r_reaction = NEW_OBJECT(MAKE_CLASS("Reaction")));
  
  rsbml_build_dom_s_base(r_reaction, (SBase_t *)reaction);
  
  if (Reaction_isSetId(reaction))
    SET_SLOT(r_reaction, install("id"), mkString(Reaction_getId(reaction)));
  if (Reaction_isSetName(reaction))
    SET_SLOT(r_reaction, install("name"), mkString(Reaction_getName(reaction)));
  if (Reaction_isSetKineticLaw(reaction))
    SET_SLOT(r_reaction, install("kineticLaw"), rsbml_build_dom_kinetic_law(Reaction_getKineticLaw(reaction)));
  SET_SLOT(r_reaction, install("reversible"), ScalarLogical(Reaction_getReversible(reaction)));
  if (Reaction_isSetFast(reaction))
    SET_SLOT(r_reaction, install("fast"), ScalarLogical(Reaction_getFast(reaction)));
  
  SET_SLOT(r_reaction, install("reactants"), LIST_OF(reaction, Reaction, species_reference, Reactant, "species"));
  SET_SLOT(r_reaction, install("products"), LIST_OF(reaction, Reaction, species_reference, Product, "species"));
  SET_SLOT(r_reaction, install("modifiers"), LIST_OF(reaction, Reaction, modifier_species_reference, Modifier, "species"));
  
  UNPROTECT(1);
  return r_reaction;
}

static SEXP
rsbml_build_dom_compartment(Compartment_t *compartment)
{
  SEXP r_compartment;
  
  PROTECT(r_compartment = NEW_OBJECT(MAKE_CLASS("Compartment")));
  
  rsbml_build_dom_s_base(r_compartment, (SBase_t *)compartment);
  
  if (Compartment_isSetId(compartment))
    SET_SLOT(r_compartment, install("id"), mkString(Compartment_getId(compartment)));
  if (Compartment_isSetName(compartment))
    SET_SLOT(r_compartment, install("name"), mkString(Compartment_getName(compartment)));
  SET_SLOT(r_compartment, install("spatialDimensions"), 
    ScalarInteger(Compartment_getSpatialDimensions(compartment)));
  if (Compartment_isSetSize(compartment))
    SET_SLOT(r_compartment, install("size"), ScalarReal(Compartment_getSize(compartment)));
  if (Compartment_isSetVolume(compartment))
    SET_SLOT(r_compartment, install("volume"), ScalarReal(Compartment_getVolume(compartment)));
  if (Compartment_isSetUnits(compartment))
    SET_SLOT(r_compartment, install("units"), mkString(Compartment_getUnits(compartment)));
  if (Compartment_isSetOutside(compartment))
    SET_SLOT(r_compartment, install("outside"), mkString(Compartment_getOutside(compartment)));
  SET_SLOT(r_compartment, install("constant"), ScalarLogical(Compartment_getConstant(compartment)));
  
  UNPROTECT(1);
  
  return r_compartment;
}

static SEXP
rsbml_build_dom_unit(Unit_t *unit)
{
  SEXP r_unit;
  
  PROTECT(r_unit = NEW_OBJECT(MAKE_CLASS("Unit")));
  
  rsbml_build_dom_s_base(r_unit, (SBase_t *)unit);
  
  SET_SLOT(r_unit, install("kind"), mkString(UnitKind_toString(Unit_getKind(unit))));
  SET_SLOT(r_unit, install("exponent"), ScalarInteger(Unit_getExponent(unit)));
  SET_SLOT(r_unit, install("unitScale"), ScalarInteger(Unit_getScale(unit)));
  SET_SLOT(r_unit, install("multiplier"), ScalarReal(Unit_getMultiplier(unit)));
  SET_SLOT(r_unit, install("offset"), ScalarReal(Unit_getOffset(unit)));
  
  UNPROTECT(1);
  
  return r_unit;
}

static SEXP
rsbml_build_dom_unit_definition(UnitDefinition_t *unit_definition)
{
  SEXP r_unit_definition;
  
  PROTECT(r_unit_definition = NEW_OBJECT(MAKE_CLASS("UnitDefinition")));
  
  rsbml_build_dom_s_base(r_unit_definition, (SBase_t *)unit_definition);
  
  if (UnitDefinition_isSetId(unit_definition))
    SET_SLOT(r_unit_definition, install("id"), mkString(UnitDefinition_getId(unit_definition)));
  if (UnitDefinition_isSetName(unit_definition))
    SET_SLOT(r_unit_definition, install("name"), mkString(UnitDefinition_getName(unit_definition)));
  
  SET_SLOT(r_unit_definition, install("units"), LIST_OF(unit_definition, UnitDefinition, unit, Unit, NULL));
  
  UNPROTECT(1);
  
  return r_unit_definition;
}

static SEXP
rsbml_build_dom_function_definition(FunctionDefinition_t *function_definition)
{
  SEXP r_function_definition;
  
  PROTECT(r_function_definition = NEW_OBJECT(MAKE_CLASS("FunctionDefinition")));
  
  rsbml_build_dom_s_base(r_function_definition, (SBase_t *)function_definition);
  
  if (FunctionDefinition_isSetId(function_definition))
    SET_SLOT(r_function_definition, install("id"), mkString(FunctionDefinition_getId(function_definition)));
  if (FunctionDefinition_isSetName(function_definition))
    SET_SLOT(r_function_definition, install("name"), mkString(FunctionDefinition_getName(function_definition)));
  if (FunctionDefinition_isSetMath(function_definition))
    SET_MATH(FunctionDefinition, function_definition, Math, math);
  
  UNPROTECT(1);
  
  return r_function_definition;
}

static SEXP
rsbml_build_dom_rule(Rule_t *rule)
{
  SEXP r_rule = R_NilValue;
  SBMLTypeCode_t type = SBase_getTypeCode((SBase_t *)rule);
  
  switch(type) {
  case SBML_ALGEBRAIC_RULE:
    PROTECT(r_rule = NEW_OBJECT(MAKE_CLASS("AlgebraicRule")));
    break;
  case SBML_ASSIGNMENT_RULE:
    PROTECT(r_rule = NEW_OBJECT(MAKE_CLASS("AssignmentRule")));
    if (Rule_isSetVariable((Rule_t *)rule))
      SET_SLOT(r_rule, install("variable"),
        mkString(Rule_getVariable(rule)));
    break;
  case SBML_RATE_RULE:
    PROTECT(r_rule = NEW_OBJECT(MAKE_CLASS("RateRule")));
    SET_SLOT(r_rule, install("variable"), mkString(
      Rule_getVariable(rule)));
    break;
  case SBML_SPECIES_CONCENTRATION_RULE:
    PROTECT(r_rule = NEW_OBJECT(MAKE_CLASS("SpeciesConcentrationRule")));
    SET_SLOT(r_rule, install("species"), mkString(
      Rule_getVariable(rule)));
    break;
  case SBML_COMPARTMENT_VOLUME_RULE:
    PROTECT(r_rule = NEW_OBJECT(MAKE_CLASS("CompartmentVolumeRule")));
    SET_SLOT(r_rule, install("compartment"), mkString(
      Rule_getVariable(rule)));
    break;
  case SBML_PARAMETER_RULE:
    PROTECT(r_rule = NEW_OBJECT(MAKE_CLASS("ParameterRule")));
    if (Rule_isSetUnits(rule))
      SET_SLOT(r_rule, install("units"), mkString(Rule_getUnits(rule)));
    break;
  default:
    error("unknown rule type");
  }
  
  if (type == SBML_SPECIES_CONCENTRATION_RULE || type == SBML_COMPARTMENT_VOLUME_RULE ||
      type == SBML_PARAMETER_RULE) {
    RuleType_t type = Rule_getType(rule);
    const char *type_name = "invalid";
    if (type == RULE_TYPE_RATE)
      type_name = "rate";
    else if (type == RULE_TYPE_SCALAR)
      type_name = "scalar";
    SET_SLOT(r_rule, install("type"), mkString(type_name));
  }
  
  rsbml_build_dom_s_base(r_rule, (SBase_t *)rule);
  
  if (Rule_isSetMath(rule))
    SET_MATH(Rule, rule, Math, math);
  
  UNPROTECT(1);
  
  return r_rule;
}

static SEXP
rsbml_build_dom_event_assignment(EventAssignment_t *event_assignment)
{
  SEXP r_event_assignment;
  
  PROTECT(r_event_assignment = NEW_OBJECT(MAKE_CLASS("EventAssignment")));
  
  rsbml_build_dom_s_base(r_event_assignment, (SBase_t *)event_assignment);
  
  if (EventAssignment_isSetVariable(event_assignment))
    SET_SLOT(r_event_assignment, install("variable"), 
      mkString(EventAssignment_getVariable(event_assignment)));
  if (EventAssignment_isSetMath(event_assignment))
    SET_MATH(EventAssignment, event_assignment, Math, math);
  
  UNPROTECT(1);
  
  return r_event_assignment;
}

static SEXP
rsbml_build_dom_delay(const Delay_t *delay)
{
  SEXP r_delay;
  
  PROTECT(r_delay = NEW_OBJECT(MAKE_CLASS("Delay")));
  
  rsbml_build_dom_s_base(r_delay, (SBase_t *)delay);
  
  SET_MATH(Delay, delay, Math, math);
  
  UNPROTECT(1);
  
  return r_delay;
}
static SEXP
rsbml_build_dom_trigger(const Trigger_t *trigger)
{
  SEXP r_trigger;
  
  PROTECT(r_trigger = NEW_OBJECT(MAKE_CLASS("Trigger")));
  
  rsbml_build_dom_s_base(r_trigger, (SBase_t *)trigger);
  
  SET_MATH(Trigger, trigger, Math, math);
  
  UNPROTECT(1);
  
  return r_trigger;
}

static SEXP
rsbml_build_dom_event(Event_t *event)
{
  SEXP r_event;
  
  PROTECT(r_event = NEW_OBJECT(MAKE_CLASS("Event")));
  
  rsbml_build_dom_s_base(r_event, (SBase_t *)event);
  
  if (Event_isSetId(event))
    SET_SLOT(r_event, install("id"), mkString(Event_getId(event)));
  if (Event_isSetName(event))
    SET_SLOT(r_event, install("name"), mkString(Event_getName(event)));
  if (Event_isSetDelay(event))
    SET_SLOT(r_event, install("eventDelay"), rsbml_build_dom_delay(Event_getDelay(event)));
  if (Event_isSetTrigger(event))
    SET_SLOT(r_event, install("trigger"), rsbml_build_dom_trigger(Event_getTrigger(event)));
#if LIBSBML_VERSION >= 30300
  // TODO: handle the useValueFromTrigger field
#endif
  if (Event_isSetTimeUnits(event))
    SET_SLOT(r_event, install("timeUnits"), mkString(Event_getTimeUnits(event)));
  
  SET_SLOT(r_event, install("eventAssignments"), 
    LIST_OF(event, Event, event_assignment, EventAssignment, NULL));

  UNPROTECT(1);
  
  return r_event;
}

#ifdef USE_LAYOUT

static SEXP
rsbml_build_dom_dimensions(Dimensions_t *dimensions)
{
  SEXP r_dimensions;
  
  PROTECT(r_dimensions = NEW_OBJECT(MAKE_CLASS("Dimensions")));
  
  rsbml_build_dom_s_base(r_dimensions, (SBase_t *)dimensions);
  
  SET_SLOT(r_dimensions, install("width"), ScalarReal(Dimensions_getWidth(dimensions)));
  SET_SLOT(r_dimensions, install("height"), ScalarReal(Dimensions_getHeight(dimensions)));
  SET_SLOT(r_dimensions, install("depth"), ScalarReal(Dimensions_getDepth(dimensions)));
  
  UNPROTECT(1);
  
  return r_dimensions;
}

static SEXP
rsbml_build_dom_point(Point_t *point)
{
  SEXP r_point;
  
  PROTECT(r_point = NEW_OBJECT(MAKE_CLASS("Point")));
  
  rsbml_build_dom_s_base(r_point, (SBase_t *)point);

  SET_SLOT(r_point, install("x"), ScalarReal(Point_getXOffset(point)));
  SET_SLOT(r_point, install("y"), ScalarReal(Point_getYOffset(point)));
  SET_SLOT(r_point, install("z"), ScalarReal(Point_getZOffset(point)));
  
  UNPROTECT(1);
  
  return r_point;
}

static SEXP
rsbml_build_dom_bounding_box(BoundingBox_t *bounding_box)
{
  SEXP r_bounding_box;
  
  PROTECT(r_bounding_box = NEW_OBJECT(MAKE_CLASS("BoundingBox")));
  
  rsbml_build_dom_s_base(r_bounding_box, (SBase_t *)bounding_box);
  
  if (BoundingBox_isSetId(bounding_box))
    SET_SLOT(r_bounding_box, install("id"), mkString(BoundingBox_getId(bounding_box)));
  SET_SLOT(r_bounding_box, install("position"), 
    rsbml_build_dom_point(BoundingBox_getPosition(bounding_box)));
  SET_SLOT(r_bounding_box, install("dimensions"), 
    rsbml_build_dom_dimensions(BoundingBox_getDimensions(bounding_box)));
  
  UNPROTECT(1);
  
  return r_bounding_box;
}

static void
rsbml_build_dom_base_graphical_object(SEXP r_graphical_object, GraphicalObject_t *graphical_object)
{
  rsbml_build_dom_s_base(r_graphical_object, (SBase_t *)graphical_object);
  
  SET_SLOT(r_graphical_object, install("id"), mkString(GraphicalObject_getId(graphical_object)));
  SET_SLOT(r_graphical_object, install("boundingBox"), 
    rsbml_build_dom_bounding_box(GraphicalObject_getBoundingBox(graphical_object)));
}

static SEXP
rsbml_build_dom_compartment_glyph(CompartmentGlyph_t *compartment_glyph)
{
  SEXP r_compartment_glyph;
    
  PROTECT(r_compartment_glyph = NEW_OBJECT(MAKE_CLASS("CompartmentGlyph")));
  
  rsbml_build_dom_base_graphical_object(r_compartment_glyph, (GraphicalObject_t *)compartment_glyph);
  
  SET_SLOT(r_compartment_glyph, install("compartment"), 
    mkString(CompartmentGlyph_getCompartmentId(compartment_glyph)));
  
  UNPROTECT(1);
  
  return r_compartment_glyph;
}

static SEXP
rsbml_build_dom_species_glyph(SpeciesGlyph_t *species_glyph)
{
  SEXP r_species_glyph;
  
  PROTECT(r_species_glyph = NEW_OBJECT(MAKE_CLASS("SpeciesGlyph")));
  
  rsbml_build_dom_base_graphical_object(r_species_glyph, (GraphicalObject_t *)species_glyph);
  
  SET_SLOT(r_species_glyph, install("species"), mkString(SpeciesGlyph_getSpeciesId(species_glyph)));
  
  UNPROTECT(1);
  
  return r_species_glyph;
}

static SEXP
rsbml_build_dom_line_segment(LineSegment_t *line_segment)
{
  SEXP r_line_segment = R_NilValue;
  
  SBMLTypeCode_t type = SBase_getTypeCode((SBase_t *)line_segment);
  
  if (type == SBML_LAYOUT_CUBICBEZIER) {
    PROTECT(r_line_segment = NEW_OBJECT(MAKE_CLASS("CubicBezier")));
    SET_SLOT(r_line_segment, install("basePoint1"), 
      rsbml_build_dom_point(CubicBezier_getBasePoint1((CubicBezier_t *)line_segment)));
    SET_SLOT(r_line_segment, install("basePoint2"), 
      rsbml_build_dom_point(CubicBezier_getBasePoint2((CubicBezier_t *)line_segment)));
  } else if (type == SBML_LAYOUT_LINESEGMENT)
    PROTECT(r_line_segment = NEW_OBJECT(MAKE_CLASS("LineSegment")));
  else error("Unknown line segment type");
  
  rsbml_build_dom_s_base(r_line_segment, (SBase_t *)line_segment);
  
  SET_SLOT(r_line_segment, install("start"), 
    rsbml_build_dom_point(LineSegment_getStart(line_segment)));
  SET_SLOT(r_line_segment, install("end"), 
    rsbml_build_dom_point(LineSegment_getEnd(line_segment)));
  
  UNPROTECT(1);
  
  return r_line_segment;
}

static SEXP
rsbml_build_dom_curve(Curve_t *curve)
{
  SEXP r_curve;
  
  PROTECT(r_curve = NEW_OBJECT(MAKE_CLASS("Curve")));
  
  rsbml_build_dom_s_base(r_curve, (SBase_t *)curve);
  
  SET_SLOT(r_curve, install("curveSegments"), 
    LIST_OF(curve, Curve, line_segment, CurveSegment, NULL));
  
  UNPROTECT(1);
  
  return r_curve;
}

static SEXP
rsbml_build_dom_species_reference_glyph(SpeciesReferenceGlyph_t *species_reference_glyph)
{
  SEXP r_species_reference_glyph;
  
  PROTECT(r_species_reference_glyph = NEW_OBJECT(MAKE_CLASS("SpeciesReferenceGlyph")));
  
  rsbml_build_dom_base_graphical_object(r_species_reference_glyph, (GraphicalObject_t *)species_reference_glyph);
  
  if (SpeciesReferenceGlyph_isSetSpeciesGlyphId(species_reference_glyph))
    SET_SLOT(r_species_reference_glyph, install("speciesGlyph"), 
      mkString(SpeciesReferenceGlyph_getSpeciesGlyphId(species_reference_glyph)));
  if (SpeciesReferenceGlyph_isSetSpeciesReferenceId(species_reference_glyph))
    SET_SLOT(r_species_reference_glyph, install("speciesReference"), 
      mkString(SpeciesReferenceGlyph_getSpeciesReferenceId(species_reference_glyph)));
  if (SpeciesReferenceGlyph_isSetRole(species_reference_glyph))
    SET_SLOT(r_species_reference_glyph, install("role"), 
      mkString(SpeciesReferenceGlyph_getRoleString(species_reference_glyph)));
  if (SpeciesReferenceGlyph_isSetCurve(species_reference_glyph))  
    SET_SLOT(r_species_reference_glyph, install("curve"), 
      rsbml_build_dom_curve(SpeciesReferenceGlyph_getCurve(species_reference_glyph)));
  
  UNPROTECT(1);
  
  return r_species_reference_glyph;
}

static SEXP
rsbml_build_dom_reaction_glyph(ReactionGlyph_t *reaction_glyph)
{
  SEXP r_reaction_glyph;
  
  PROTECT(r_reaction_glyph = NEW_OBJECT(MAKE_CLASS("ReactionGlyph")));
  
  rsbml_build_dom_base_graphical_object(r_reaction_glyph, (GraphicalObject_t *)reaction_glyph);
  
  SET_SLOT(r_reaction_glyph, install("reaction"), mkString(ReactionGlyph_getReactionId(reaction_glyph)));
  if (ReactionGlyph_isSetCurve(reaction_glyph))
    SET_SLOT(r_reaction_glyph, install("curve"), 
      rsbml_build_dom_curve(ReactionGlyph_getCurve(reaction_glyph)));
  SET_SLOT(r_reaction_glyph, install("speciesReferenceGlyphs"), 
    LIST_OF(reaction_glyph, ReactionGlyph, species_reference_glyph, SpeciesReferenceGlyph, "id"));
  
  UNPROTECT(1);
  
  return r_reaction_glyph;
}

static SEXP
rsbml_build_dom_text_glyph(TextGlyph_t *text_glyph)
{
  SEXP r_text_glyph;
  
  PROTECT(r_text_glyph = NEW_OBJECT(MAKE_CLASS("TextGlyph")));
  
  rsbml_build_dom_base_graphical_object(r_text_glyph, (GraphicalObject_t *)text_glyph);
  
  if (TextGlyph_isSetGraphicalObjectId(text_glyph))
    SET_SLOT(r_text_glyph, install("graphicalObject"), 
      mkString(TextGlyph_getGraphicalObjectId(text_glyph)));
  if (TextGlyph_isSetText(text_glyph))
    SET_SLOT(r_text_glyph, install("text"), mkString(TextGlyph_getText(text_glyph)));
  if (TextGlyph_isSetOriginOfTextId(text_glyph))
    SET_SLOT(r_text_glyph, install("originOfText"), 
      mkString(TextGlyph_getOriginOfTextId(text_glyph)));
  
  UNPROTECT(1);
  
  return r_text_glyph;
}

static SEXP
rsbml_build_dom_graphical_object(GraphicalObject_t *graphical_object)
{
  SEXP r_graphical_object;
  
  PROTECT(r_graphical_object = NEW_OBJECT(MAKE_CLASS("GraphicalObject")));
  
  rsbml_build_dom_base_graphical_object(r_graphical_object, graphical_object);
  
  return r_graphical_object;
}

static SEXP
rsbml_build_dom_layout(Layout_t *layout)
{
  SEXP r_layout;
  
  PROTECT(r_layout = NEW_OBJECT(MAKE_CLASS("Layout")));
  
  rsbml_build_dom_s_base(r_layout, (SBase_t *)layout);
  
  SET_SLOT(r_layout, install("id"), mkString(Layout_getId(layout)));
  SET_SLOT(r_layout, install("dimensions"), rsbml_build_dom_dimensions(Layout_getDimensions(layout)));
  
  SET_SLOT(r_layout, install("compartmentGlyphs"), 
    LIST_OF(layout, Layout, compartment_glyph, CompartmentGlyph, "id"));
  SET_SLOT(r_layout, install("speciesGlyphs"), 
    LIST_OF(layout, Layout, species_glyph, SpeciesGlyph, "id"));
  SET_SLOT(r_layout, install("reactionGlyphs"), 
    LIST_OF(layout, Layout, reaction_glyph, ReactionGlyph, "id"));
  SET_SLOT(r_layout, install("textGlyphs"), 
    LIST_OF(layout, Layout, text_glyph, TextGlyph, "id"));
  SET_SLOT(r_layout, install("additionalGraphicalObjects"), 
    LIST_OF(layout, Layout, graphical_object, AdditionalGraphicalObject, "id"));

  UNPROTECT(1);
  
  return r_layout;
}
#endif /* USE_LAYOUT */

static SEXP
rsbml_build_dom_compartment_type(CompartmentType_t *compartment_type)
{
  SEXP r_compartment_type;
  
  PROTECT(r_compartment_type = NEW_OBJECT(MAKE_CLASS("CompartmentType")));
  
  rsbml_build_dom_s_base(r_compartment_type, (SBase_t *)compartment_type);
  
  SET_SLOT(r_compartment_type, install("id"), mkString(CompartmentType_getId(compartment_type)));
  if (CompartmentType_isSetName(compartment_type))
    SET_SLOT(r_compartment_type, install("name"), mkString(CompartmentType_getName(compartment_type)));
  
  UNPROTECT(1);
  
  return r_compartment_type;
}
static SEXP
rsbml_build_dom_species_type(SpeciesType_t *species_type)
{
  SEXP r_species_type;
  
  PROTECT(r_species_type = NEW_OBJECT(MAKE_CLASS("SpeciesType")));
  
  rsbml_build_dom_s_base(r_species_type, (SBase_t *)species_type);
  
  SET_SLOT(r_species_type, install("id"), mkString(SpeciesType_getId(species_type)));
  if (SpeciesType_isSetName(species_type))
    SET_SLOT(r_species_type, install("name"), mkString(SpeciesType_getName(species_type)));
  
  UNPROTECT(1);
  
  return r_species_type;
}
static SEXP
rsbml_build_dom_initial_assignment(InitialAssignment_t *initial_assignment)
{
  SEXP r_initial_assignment;
  
  PROTECT(r_initial_assignment = NEW_OBJECT(MAKE_CLASS("InitialAssignment")));
  
  rsbml_build_dom_s_base(r_initial_assignment, (SBase_t *)initial_assignment);
  
  SET_SLOT(r_initial_assignment, install("symbol"), mkString(InitialAssignment_getSymbol(initial_assignment)));
  SET_MATH(InitialAssignment, initial_assignment, Math, math);
  
  UNPROTECT(1);
  
  return r_initial_assignment;
}
static SEXP
rsbml_build_dom_constraint(Constraint_t *constraint)
{
  SEXP r_constraint;
  
  PROTECT(r_constraint = NEW_OBJECT(MAKE_CLASS("Constraint")));
  
  rsbml_build_dom_s_base(r_constraint, (SBase_t *)constraint);
  
  SET_SLOT(r_constraint, install("message"), 
    mkString(XMLNode_convertXMLNodeToString(Constraint_getMessage(constraint))));
  SET_MATH(Constraint, constraint, Math, math);
  
  UNPROTECT(1);
  
  return r_constraint;
}

static SEXP
rsbml_build_dom_model_creator(ModelCreator_t *model_creator)
{
  SEXP r_model_creator;
  
  PROTECT(r_model_creator = NEW_OBJECT(MAKE_CLASS("ModelCreator")));
  
  SET_SLOT(r_model_creator, install("familyName"), mkString(ModelCreator_getFamilyName(model_creator)));
  SET_SLOT(r_model_creator, install("givenName"), mkString(ModelCreator_getGivenName(model_creator)));
  SET_SLOT(r_model_creator, install("email"), mkString(ModelCreator_getEmail(model_creator)));
  SET_SLOT(r_model_creator, install("organization"), mkString(ModelCreator_getOrganisation(model_creator)));
  
  UNPROTECT(1);
  
  return r_model_creator;
}

static SEXP
rsbml_build_dom_model_history(ModelHistory_t *model_history)
{
  SEXP r_model_history;
  
  PROTECT(r_model_history = NEW_OBJECT(MAKE_CLASS("ModelHistory")));

  if (ModelHistory_getCreatedDate(model_history))
    SET_SLOT(r_model_history, install("createdDate"), 
             mkString(Date_getDateAsString(ModelHistory_getCreatedDate(model_history))));
  if (ModelHistory_getModifiedDate(model_history))
    SET_SLOT(r_model_history, install("modifiedDate"), 
             mkString(Date_getDateAsString(ModelHistory_getModifiedDate(model_history))));
  SET_SLOT(r_model_history, install("creators"), 
    LIST_OF(model_history, ModelHistory, model_creator, Creator, NULL));
  
  UNPROTECT(1);
  
  return r_model_history;
}

static SEXP
rsbml_build_dom_model(Model_t *model)
{
  SEXP r_model;

  PROTECT(r_model = NEW_OBJECT(MAKE_CLASS("Model")));

  rsbml_build_dom_s_base(r_model, (SBase_t *)model);
  
  if (Model_isSetId(model))
    SET_SLOT(r_model, install("id"), mkString(Model_getId(model)));
  if (Model_isSetName(model))
    SET_SLOT(r_model, install("name"), mkString(Model_getName(model)));

  if (Model_isSetModelHistory(model))
    SET_SLOT(r_model, install("modelHistory"), 
      rsbml_build_dom_model_history(Model_getModelHistory(model)));

  { /* species don't fit into the macro */
    int i, num_species = Model_getNumSpecies(model);
    SEXP r_species, r_names;
    PROTECT(r_species = NEW_LIST(num_species));
    PROTECT(r_names = NEW_CHARACTER(num_species));
    for (i = 0; i < num_species; i++) {
      SEXP r_element = rsbml_build_dom_species(Model_getSpecies(model, i));
      SET_VECTOR_ELT(r_species, i, r_element);
      SET_STRING_ELT(r_names, i, STRING_ELT(GET_SLOT(r_element, install("id")),0));
    }
    SET_NAMES(r_species, r_names);
    SET_SLOT(r_model, install("species"), r_species);
    UNPROTECT(2);
  }

  SET_SLOT(r_model, install("reactions"), LIST_OF(model, Model, reaction, Reaction, "id"));
  SET_SLOT(r_model, install("compartments"), LIST_OF(model, Model, compartment, Compartment, "id"));
  SET_SLOT(r_model, install("unitDefinitions"), LIST_OF(model, Model, unit_definition, UnitDefinition, "id"));
  SET_SLOT(r_model, install("functionDefinitions"), LIST_OF(model, Model, function_definition, FunctionDefinition, "id"));
  SET_SLOT(r_model, install("parameters"), LIST_OF(model, Model, parameter, Parameter, "id"));
  SET_SLOT(r_model, install("rules"), LIST_OF(model, Model, rule, Rule, NULL));
  SET_SLOT(r_model, install("events"), LIST_OF(model, Model, event, Event, "id"));
  SET_SLOT(r_model, install("speciesTypes"), LIST_OF(model, Model, species_type, SpeciesType, "id"));
  SET_SLOT(r_model, install("compartmentTypes"), LIST_OF(model, Model, compartment_type, CompartmentType, "id"));
  SET_SLOT(r_model, install("initialAssignments"), LIST_OF(model, Model, initial_assignment, InitialAssignment, NULL));
  SET_SLOT(r_model, install("constraints"), LIST_OF(model, Model, constraint, Constraint, "id"));
  #ifdef USE_LAYOUT
  SET_SLOT(r_model, install("layouts"), LIST_OF(model, Model, layout, Layout, "id"));
  #endif

  UNPROTECT(1);

  return r_model;
}

static SEXP
rsbml_build_dom(SBMLDocument_t *doc)
{
  SEXP r_dom;
  
  PROTECT(r_dom = NEW_OBJECT(MAKE_CLASS("SBML")));
  
  SET_SLOT(r_dom, install("level"), ScalarInteger(SBMLDocument_getLevel(doc)));
  SET_SLOT(r_dom, install("ver"), ScalarInteger(SBMLDocument_getVersion(doc)));
  SET_SLOT(r_dom, install("model"), rsbml_build_dom_model(SBMLDocument_getModel(doc)));

#if LIBSBML_VERSION >= 50000
#ifdef USE_LAYOUT
  SBase_enablePackage((SBase_t *)doc,
                      "http://projects.eml.org/bcb/sbml/level2", "layout",
                      TRUE);
#endif
#endif
  
  UNPROTECT(1);
  
  return r_dom;
}

SEXP
rsbml_R_build_dom(SEXP r_doc)
{
  SBMLDocument_t *doc = R_ExternalPtrAddr(r_doc);
  if (rsbml_errors(doc))
    error("Cannot build dom from document with errors");
  return rsbml_build_dom(doc);
}
