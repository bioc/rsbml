#include "rsbml.h"

#define STRING(x) (char *)CHAR(STRING_ELT(x, 0))
#define INTEGER_SCALAR(x) INTEGER(x)[0]
#define REAL_SCALAR(x) REAL(x)[0]
#define LOGICAL_SCALAR(x) LOGICAL(x)[0]

#define rsbml_build_doc_ast_node(x) rmathml_ASTNode(VECTOR_ELT(x, 0))
#define rsbml_build_doc_unit_kind(x) UnitKind_forName(STRING(x))
#define rsbml_build_doc_rule_type(x) RuleType_forName(STRING(x))

#if LIBSBML_VERSION >= 50000
/* Global variables because we're lazy. Otherwise, we would have to
   pass the version/level from the R document (SBML) to every function. */
unsigned int SBML_VERSION;
unsigned int SBML_LEVEL;

static void rsbml_report_operation_status(OperationReturnValues_t status,
                                          const char *attr)
{
  const char *msg;
  if (status == LIBSBML_OPERATION_SUCCESS)
    return;
  switch(status) {
  case LIBSBML_INDEX_EXCEEDS_SIZE:
    msg = "Index out of bounds";
    break;
  case LIBSBML_UNEXPECTED_ATTRIBUTE:
    msg = "Unexpected attribute for the level/version of this element";
    break;
  case LIBSBML_OPERATION_FAILED:
    msg = "Operation failed";
    break;
  case LIBSBML_INVALID_ATTRIBUTE_VALUE:
    msg = "Invalid attribute value";
    break;
  case LIBSBML_INVALID_OBJECT:
    msg = "Invalid object";
    break;
  case LIBSBML_DUPLICATE_OBJECT_ID:
    msg = "An object already exists with this identifier";
    break;
  case LIBSBML_LEVEL_MISMATCH:
    msg = "SBML level of child does not match that of parent";
    break;
  case LIBSBML_VERSION_MISMATCH:
    msg = "SBML version of child does not match that of parent";
    break;
  case LIBSBML_INVALID_XML_OPERATION:
    msg = "Invalid XML operation";
    break;
  case LIBSBML_NAMESPACES_MISMATCH:
    msg = "Namespaces do not match";
    break;
  default:
    msg = "Unhandled failure type";
  }
  error("libsbml operation failed: %s (code: %d) for %s", msg, status, attr);
}
#endif

#define rsbml_build_doc_date(x) Date_createFromString(STRING(x))

static ModelQualifierType_t 
rsbml_build_doc_model_qualifier_type(SEXP r_type)
{
  const char *name = STRING(r_type);
  ModelQualifierType_t type;
  if (!strcmp(name, "is"))
    type = BQM_IS;
  else if (!strcmp(name, "isDescribedBy"))
    type = BQM_IS_DESCRIBED_BY;
  else type = BQM_UNKNOWN;
  return type;
}

static BiolQualifierType_t 
rsbml_build_doc_biological_qualifier_type(SEXP r_type)
{
  const char *name = STRING(r_type);
  BiolQualifierType_t type;
  if (!strcmp(name, "is"))
    type = BQB_IS;
  else if (!strcmp(name, "hasPart"))
    type = BQB_HAS_PART;
  else if (!strcmp(name, "isPartOf"))
    type = BQB_IS_PART_OF;
  else if (!strcmp(name, "isVersionOf"))
    type = BQB_IS_VERSION_OF;
  else if (!strcmp(name, "hasVersion"))
    type = BQB_HAS_VERSION;
  else if (!strcmp(name, "isHomologTo"))
    type = BQB_IS_HOMOLOG_TO;
  else if (!strcmp(name, "isDescribedBy"))
    type = BQB_IS_DESCRIBED_BY;
#if LIBSBML_VERSION >= 30300
  else if (!strcmp(name, "isEncodedBy"))
    type = BQB_IS_ENCODED_BY;
  else if (!strcmp(name, "encodes"))
    type = BQB_ENCODES;
  else if (!strcmp(name, "occursIn"))
    type = BQB_OCCURS_IN;
#endif
  else type = BQB_UNKNOWN;
  return type;
}

/* String -> XMLNode */
static XMLNode_t *rsbml_build_doc_xml_node(SEXP r_node)
{
  return XMLNode_convertStringToXMLNode(STRING(r_node), NULL);
}

#define CLEANUP_MEMORY 1

#define ADD_LIST_NOCHECK(class, var, Child, child, ParamType, func)     \
  ({                                                                    \
    int i;                                                              \
    SEXP list = GET_SLOT(r_ ## var, install(#child));                   \
    for (i = 0; i < GET_LENGTH(list); i++) {                            \
      ParamType ## _t *obj = rsbml_build_doc_ ## func(VECTOR_ELT(list, i)); \
      class ## _add ## Child(var, obj);                                 \
      if (CLEANUP_MEMORY)                                               \
        ParamType ## _free(obj);                                        \
    }                                                                   \
  })

#define SET_XML_ATTR_OBJ_NOCHECK(Class, var, Name, name, ParamType, converter) \
  ({                                                                    \
    SEXP r_ ## name = GET_SLOT(r_ ## var, install(#name));              \
    if (GET_LENGTH(r_ ## name)) {                                       \
      ParamType ## _t *conv = rsbml_build_doc_ ## converter(r_ ## name); \
      Class ## _set ## Name((Class ## _t *)var, conv);     \
      if (CLEANUP_MEMORY)                                               \
        ParamType ## _free(conv);                                       \
    }                                                                   \
  })

#define SET_XML_ATTR_NOCHECK(Class, var, Name, name, converter)         \
  ({                                                                    \
    SEXP r_ ## name = GET_SLOT(r_ ## var, install(#name));              \
    if (GET_LENGTH(r_ ## name)) {                                       \
      Class ## _set ## Name((Class ## _t *)var,                         \
                            converter(r_ ## name));                     \
    }                                                                   \
  })

/* Hopefully, libsbml eventually will always emit a status on set */
#if LIBSBML_VERSION >= 50000
#define ADD_LIST(class, var, Child, child, ParamType, func)             \
  ({                                                                    \
    int i;                                                              \
    SEXP list = GET_SLOT(r_ ## var, install(#child));                   \
    for (i = 0; i < GET_LENGTH(list); i++) {                            \
      ParamType ## _t *obj = rsbml_build_doc_ ## func(VECTOR_ELT(list, i)); \
      int status = class ## _add ## Child(var, obj);                    \
      if (CLEANUP_MEMORY)                                               \
        ParamType ## _free(obj);                                        \
      rsbml_report_operation_status(status, #class "::add" #Child);     \
    }                                                                   \
  })
#define SET_XML_ATTR_OBJ(Class, var, Name, name, ParamType, converter)  \
  ({                                                                    \
    SEXP r_ ## name = GET_SLOT(r_ ## var, install(#name));              \
    if (GET_LENGTH(r_ ## name)) {                                       \
      ParamType ## _t *conv = rsbml_build_doc_ ## converter(r_ ## name); \
      int status = Class ## _set ## Name((Class ## _t *)var, conv);     \
      if (CLEANUP_MEMORY)                                               \
        ParamType ## _free(conv);                                       \
      rsbml_report_operation_status(status, #Class "::set" #Name);      \
    }                                                                   \
  })
#define SET_XML_ATTR(Class, var, Name, name, converter)                 \
  ({                                                                    \
    SEXP r_ ## name = GET_SLOT(r_ ## var, install(#name));              \
    if (GET_LENGTH(r_ ## name)) {                                       \
      int status = Class ## _set ## Name((Class ## _t *)var,            \
                                         converter(r_ ## name));        \
      rsbml_report_operation_status(status, #Class "::set" #Name);      \
    }                                                                   \
  })
#else
#define SET_XML_ATTR_OBJ SET_XML_ATTR_OBJ_NOCHECK
#define SET_XML_ATTR SET_XML_ATTR_NOCHECK
#define ADD_LIST ADD_LIST_NOCHECK
#endif

static CVTerm_t *
rsbml_build_doc_cvterm(SEXP r_cvterm)
{
  CVTerm_t * cvterm;
  
  QualifierType_t type = UNKNOWN_QUALIFIER;
  SEXP r_type = GET_SLOT(r_cvterm, install("qualifierType"));
  if (GET_LENGTH(r_type)) {
    if (!strcmp(STRING(r_type), "model"))
      type = MODEL_QUALIFIER;
    else if (!strcmp(STRING(r_type), "biological"))
      type = BIOLOGICAL_QUALIFIER;
  }
  cvterm = CVTerm_createWithQualifierType(type);
  
  SET_XML_ATTR(CVTerm, cvterm, ModelQualifierType, modelQualifierType, 
    rsbml_build_doc_model_qualifier_type);
  SET_XML_ATTR(CVTerm, cvterm, BiologicalQualifierType, biologicalQualifierType, 
    rsbml_build_doc_biological_qualifier_type);
  SEXP r_resources = GET_SLOT(r_cvterm, install("resources"));
  for (int i = 0; i < GET_LENGTH(r_resources); i++)
    CVTerm_addResource(cvterm, CHAR(STRING_ELT(r_resources, i)));
  
  return cvterm;
}

static void
rsbml_build_doc_s_base(SBase_t *s_base, SEXP r_s_base)
{
  SET_XML_ATTR(SBase, s_base, MetaId, metaId, STRING);
  SET_XML_ATTR(SBase, s_base, AnnotationString, annotation, STRING);
  SET_XML_ATTR(SBase, s_base, NotesString, notes, STRING);
  SET_XML_ATTR(SBase, s_base, SBOTerm, sboTerm, INTEGER_SCALAR);
  ADD_LIST(SBase, s_base, CVTerm, cvTerms, CVTerm, cvterm);
}

static SpeciesType_t *
rsbml_build_doc_species_type(SEXP r_species_type)
{
  SpeciesType_t * species_type;
  
#if LIBSBML_VERSION >= 40000
  species_type = SpeciesType_create(SBML_LEVEL, SBML_VERSION);
#else
  species_type = SpeciesType_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)species_type, r_species_type);
  
  SET_XML_ATTR(SpeciesType, species_type, Id, id, STRING);
  SET_XML_ATTR(SpeciesType, species_type, Name, name, STRING);
  
  return species_type;
}

static Species_t *
rsbml_build_doc_species(SEXP r_species)
{
  Species_t * species;
  
#if LIBSBML_VERSION >= 40000
  species = Species_create(SBML_LEVEL, SBML_VERSION);
#else
  species = Species_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)species, r_species);
  
  SET_XML_ATTR(Species, species, Id, id, STRING);
  SET_XML_ATTR(Species, species, Name, name, STRING);
  SET_XML_ATTR(Species, species, Compartment, compartment, STRING);
  SET_XML_ATTR(Species, species, InitialConcentration, initialConcentration, REAL_SCALAR);
  SET_XML_ATTR(Species, species, InitialAmount, initialAmount, REAL_SCALAR);
  SET_XML_ATTR(Species, species, SubstanceUnits, substanceUnits, STRING);
  SET_XML_ATTR(Species, species, SpatialSizeUnits, spatialSizeUnits, STRING);
  SET_XML_ATTR(Species, species, Units, units, STRING);
  SET_XML_ATTR(Species, species, HasOnlySubstanceUnits, hasOnlySubstanceUnits, LOGICAL_SCALAR);
  SET_XML_ATTR(Species, species, BoundaryCondition, boundaryCondition, LOGICAL_SCALAR);
  SET_XML_ATTR(Species, species, Charge, charge, INTEGER_SCALAR);
  SET_XML_ATTR(Species, species, Constant, constant, LOGICAL_SCALAR);
  
  return species;
}

static FunctionDefinition_t *
rsbml_build_doc_function_definition(SEXP r_function_definition)
{
  FunctionDefinition_t * function_definition;
  
  #if LIBSBML_VERSION >= 40000
  function_definition = FunctionDefinition_create(SBML_LEVEL, SBML_VERSION);
#else
  function_definition = FunctionDefinition_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)function_definition, r_function_definition);
  
  SET_XML_ATTR(FunctionDefinition, function_definition, Id, id, STRING);
  SET_XML_ATTR(FunctionDefinition, function_definition, Name, name, STRING);
  SET_XML_ATTR_OBJ(FunctionDefinition, function_definition, Math, math, ASTNode, ast_node);
  
  return function_definition;
}

static Unit_t *
rsbml_build_doc_unit(SEXP r_unit)
{
  Unit_t * unit;
  
#if LIBSBML_VERSION >= 40000
  unit = Unit_create(SBML_LEVEL, SBML_VERSION);
#else
  unit = Unit_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)unit, r_unit);
  
  SET_XML_ATTR(Unit, unit, Kind, kind, rsbml_build_doc_unit_kind);
  SET_XML_ATTR(Unit, unit, Exponent, exponent, INTEGER_SCALAR);
  SET_XML_ATTR(Unit, unit, Scale, unitScale, INTEGER_SCALAR);
  SET_XML_ATTR(Unit, unit, Multiplier, multiplier, REAL_SCALAR);
  SET_XML_ATTR(Unit, unit, Offset, offset, REAL_SCALAR);
  
  return unit;
}

static UnitDefinition_t *
rsbml_build_doc_unit_definition(SEXP r_unit_definition)
{
  UnitDefinition_t * unit_definition;
  
#if LIBSBML_VERSION >= 40000
  unit_definition = UnitDefinition_create(SBML_LEVEL, SBML_VERSION);
#else
  unit_definition = UnitDefinition_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)unit_definition, r_unit_definition);
  
  SET_XML_ATTR(UnitDefinition, unit_definition, Id, id, STRING);
  SET_XML_ATTR(UnitDefinition, unit_definition, Name, name, STRING);
  ADD_LIST(UnitDefinition, unit_definition, Unit, units, Unit, unit);
  
  return unit_definition;
}

static CompartmentType_t *
rsbml_build_doc_compartment_type(SEXP r_compartment_type)
{
  CompartmentType_t * compartment_type;
  
#if LIBSBML_VERSION >= 40000
  compartment_type = CompartmentType_create(SBML_LEVEL, SBML_VERSION);
#else
  compartment_type = CompartmentType_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)compartment_type, r_compartment_type);
  
  SET_XML_ATTR(CompartmentType, compartment_type, Id, id, STRING);
  SET_XML_ATTR(CompartmentType, compartment_type, Name, name, STRING);
  
  return compartment_type;
}

static Compartment_t *
rsbml_build_doc_compartment(SEXP r_compartment)
{
  Compartment_t * compartment;
  
#if LIBSBML_VERSION >= 40000
  compartment = Compartment_create(SBML_LEVEL, SBML_VERSION);
#else
  compartment = Compartment_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)compartment, r_compartment);
  
  SET_XML_ATTR(Compartment, compartment, Id, id, STRING);
  SET_XML_ATTR(Compartment, compartment, Name, name, STRING);
  SET_XML_ATTR(Compartment, compartment, SpatialDimensions, spatialDimensions, INTEGER_SCALAR);
  SET_XML_ATTR(Compartment, compartment, Size, size, REAL_SCALAR);
  SET_XML_ATTR(Compartment, compartment, Units, units, STRING);
  SET_XML_ATTR(Compartment, compartment, Outside, outside, STRING);
  SET_XML_ATTR(Compartment, compartment, Constant, constant, LOGICAL_SCALAR);
  
  return compartment;
}

static Parameter_t *
rsbml_build_doc_parameter(SEXP r_parameter)
{
  Parameter_t * parameter;
  
#if LIBSBML_VERSION >= 40000
  parameter = Parameter_create(SBML_LEVEL, SBML_VERSION);
#else
  parameter = Parameter_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)parameter, r_parameter);
  
  SET_XML_ATTR(Parameter, parameter, Id, id, STRING);
  SET_XML_ATTR(Parameter, parameter, Name, name, STRING);
  SET_XML_ATTR(Parameter, parameter, Value, value, REAL_SCALAR);
  SET_XML_ATTR(Parameter, parameter, Units, units, STRING);
  SET_XML_ATTR(Parameter, parameter, Constant, constant, LOGICAL_SCALAR);
  
  return parameter;
}

static KineticLaw_t *
rsbml_build_doc_kinetic_law(SEXP r_kinetic_law)
{
  KineticLaw_t * kinetic_law;
  
#if LIBSBML_VERSION >= 40000
  kinetic_law = KineticLaw_create(SBML_LEVEL, SBML_VERSION);
#else
  kinetic_law = KineticLaw_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)kinetic_law, r_kinetic_law);
  
  SET_XML_ATTR_OBJ(KineticLaw, kinetic_law, Math, math, ASTNode, ast_node);
  ADD_LIST(KineticLaw, kinetic_law, Parameter, parameters, Parameter, parameter);
  SET_XML_ATTR(KineticLaw, kinetic_law, TimeUnits, timeUnits, STRING);
  SET_XML_ATTR(KineticLaw, kinetic_law, SubstanceUnits, substanceUnits, STRING);
  
  return kinetic_law;
}

static void
rsbml_build_doc_simple_species_reference(SpeciesReference_t *simple_species_reference,
  SEXP r_simple_species_reference)
{
  rsbml_build_doc_s_base((SBase_t *)simple_species_reference, r_simple_species_reference);
  /* Somehow, an ID gets automatically added to the document (and thus
     to the R DOM), even when the level/version is insufficient. */
#if LIBSBML_VERSION >= 40000
  if ((SBML_LEVEL == 2 && SBML_VERSION >= 2) || SBML_LEVEL > 2)
#endif
    SET_XML_ATTR(SpeciesReference, simple_species_reference, Id, id, STRING);
  SET_XML_ATTR(SpeciesReference, simple_species_reference, Species, species, STRING);
}

static StoichiometryMath_t *
rsbml_build_doc_stoichiometry_math(SEXP r_stoichiometry_math)
{
#if LIBSBML_VERSION >= 40000
  StoichiometryMath_t *stoichiometry_math = StoichiometryMath_create(SBML_LEVEL, SBML_VERSION);
#else
  StoichiometryMath_t *stoichiometry_math = StoichiometryMath_create();
#endif
  SET_XML_ATTR_OBJ(StoichiometryMath, stoichiometry_math, Math, math, ASTNode, ast_node);
  return stoichiometry_math;
}

static SpeciesReference_t *
rsbml_build_doc_species_reference(SEXP r_species_reference)
{
  SpeciesReference_t * species_reference;
  
  
#if LIBSBML_VERSION >= 40000
  species_reference = SpeciesReference_create(SBML_LEVEL, SBML_VERSION);
#else
  species_reference = SpeciesReference_create();
#endif
  
  rsbml_build_doc_simple_species_reference((SpeciesReference_t *)species_reference,
    r_species_reference);
  
  SET_XML_ATTR(SpeciesReference, species_reference, Stoichiometry, stoichiometry, REAL_SCALAR);
 
  {
    SET_XML_ATTR_OBJ(SpeciesReference, species_reference, StoichiometryMath, stoichiometryMath,
      StoichiometryMath, stoichiometry_math);
  }

  return species_reference;
}

static SpeciesReference_t *
rsbml_build_doc_modifier_species_reference(SEXP r_modifier_species_reference)
{
  SpeciesReference_t * modifier_species_reference;
  
  #if LIBSBML_VERSION >= 40000
  modifier_species_reference = SpeciesReference_createModifier(SBML_LEVEL, SBML_VERSION);
#else
  modifier_species_reference = SpeciesReference_createModifier();
#endif
  
  rsbml_build_doc_simple_species_reference(
    (SpeciesReference_t *)modifier_species_reference, r_modifier_species_reference);
  
  return modifier_species_reference;
}

static Reaction_t *
rsbml_build_doc_reaction(SEXP r_reaction)
{
  Reaction_t * reaction;
  
#if LIBSBML_VERSION >= 40000
  reaction = Reaction_create(SBML_LEVEL, SBML_VERSION);
#else
  reaction = Reaction_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)reaction, r_reaction);
  
  SET_XML_ATTR(Reaction, reaction, Id, id, STRING);
  SET_XML_ATTR(Reaction, reaction, Name, name, STRING);
  ADD_LIST(Reaction, reaction, Reactant, reactants, SpeciesReference, species_reference);
  ADD_LIST(Reaction, reaction, Product, products, SpeciesReference, species_reference);
  ADD_LIST(Reaction, reaction, Modifier, modifiers, SpeciesReference, modifier_species_reference);
  SET_XML_ATTR_OBJ(Reaction, reaction, KineticLaw, kineticLaw, KineticLaw, kinetic_law);
  SET_XML_ATTR(Reaction, reaction, Reversible, reversible, LOGICAL_SCALAR);
  SET_XML_ATTR(Reaction, reaction, Fast, fast, LOGICAL_SCALAR);
  
  return reaction;
}

static Rule_t *
rsbml_build_doc_rule(SEXP r_rule)
{
  Rule_t * rule = NULL;
  
  if (inherits(r_rule, "AlgebraicRule"))
#if LIBSBML_VERSION >= 40000
    rule = Rule_createAlgebraic(SBML_LEVEL, SBML_VERSION);
#else
    rule = Rule_createAlgebraic();
#endif
  else if (inherits(r_rule, "RateRule")) {
#if LIBSBML_VERSION >= 40000
    rule = Rule_createRate(SBML_LEVEL, SBML_VERSION);
#else
    rule = Rule_createRate();
#endif
    SET_XML_ATTR(Rule, rule, Variable, variable, STRING);
  } else if (inherits(r_rule, "AssignmentRule")) {
#if LIBSBML_VERSION >= 40000
    rule = Rule_createAssignment(SBML_LEVEL, SBML_VERSION);
#else
    rule = Rule_createAssignment();
#endif
    SET_XML_ATTR(Rule, rule, Variable, variable, STRING);
  } else {
    error("Unknown event type");
  }
  if (inherits(r_rule, "ParameterRule")) {
    SET_XML_ATTR(Rule, rule, Units, units, STRING);
  }
  
  rsbml_build_doc_s_base((SBase_t *)rule, r_rule);
  
  SET_XML_ATTR_OBJ(Rule, rule, Math, math, ASTNode, ast_node);
  
  return rule;
}

static EventAssignment_t *
rsbml_build_doc_event_assignment(SEXP r_event_assignment)
{
  EventAssignment_t * event_assignment;
  
#if LIBSBML_VERSION >= 40000
  event_assignment = EventAssignment_create(SBML_LEVEL, SBML_VERSION);
#else
  event_assignment = EventAssignment_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)event_assignment, r_event_assignment);
  
  SET_XML_ATTR(EventAssignment, event_assignment, Variable, variable, STRING);
  SET_XML_ATTR_OBJ(EventAssignment, event_assignment, Math, math, ASTNode, ast_node);
  
  return event_assignment;
}

static Trigger_t *
rsbml_build_doc_trigger(SEXP r_trigger)
{
  Trigger_t * trigger;
  
#if LIBSBML_VERSION >= 40000
  trigger = Trigger_create(SBML_LEVEL, SBML_VERSION);
#else
  trigger = Trigger_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)trigger, r_trigger);
  
  SET_XML_ATTR_OBJ(Trigger, trigger, Math, math, ASTNode, ast_node);
  
  return trigger;
}
static Delay_t *
rsbml_build_doc_delay(SEXP r_delay)
{
  Delay_t * delay;
  
#if LIBSBML_VERSION >= 40000
  delay = Delay_create(SBML_LEVEL, SBML_VERSION);
#else
  delay = Delay_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)delay, r_delay);
  
  SET_XML_ATTR_OBJ(Delay, delay, Math, math, ASTNode, ast_node);
  
  return delay;
}

static Event_t *
rsbml_build_doc_event(SEXP r_event)
{
  Event_t * event;
  
#if LIBSBML_VERSION >= 40000
  event = Event_create(SBML_LEVEL, SBML_VERSION);
#else
  event = Event_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)event, r_event);
  
  SET_XML_ATTR(Event, event, Id, id, STRING);
  SET_XML_ATTR(Event, event, Name, name, STRING);
  SET_XML_ATTR_OBJ(Event, event, Delay, eventDelay, Delay, delay);
  SET_XML_ATTR_OBJ(Event, event, Trigger, trigger, Trigger, trigger);
  SET_XML_ATTR(Event, event, TimeUnits, timeUnits, STRING);
  ADD_LIST(Event, event, EventAssignment, eventAssignments, EventAssignment, event_assignment);
  
  return event;
}

#ifdef USE_LAYOUT
static Dimensions_t *
rsbml_build_doc_dimensions(SEXP r_dimensions)
{
  Dimensions_t * dimensions;
  
  dimensions = Dimensions_create();
  
  rsbml_build_doc_s_base((SBase_t *)dimensions, r_dimensions);
  
  SET_XML_ATTR_NOCHECK(Dimensions, dimensions, Width, width, REAL_SCALAR);
  SET_XML_ATTR_NOCHECK(Dimensions, dimensions, Height, height, REAL_SCALAR);
  SET_XML_ATTR_NOCHECK(Dimensions, dimensions, Depth, depth, REAL_SCALAR);
  
  return dimensions;
}

static Point_t *
rsbml_build_doc_point(SEXP r_point)
{
  Point_t * point;
  
  point = Point_create();
  
  rsbml_build_doc_s_base((SBase_t *)point, r_point);
  
  SET_XML_ATTR_NOCHECK(Point, point, XOffset, x, REAL_SCALAR);
  SET_XML_ATTR_NOCHECK(Point, point, YOffset, y, REAL_SCALAR);
  SET_XML_ATTR_NOCHECK(Point, point, ZOffset, z, REAL_SCALAR);
  
  return point;
}

static BoundingBox_t *
rsbml_build_doc_bounding_box(SEXP r_bounding_box)
{
  BoundingBox_t * bounding_box;
  
  bounding_box = BoundingBox_create();
  
  rsbml_build_doc_s_base((SBase_t *)bounding_box, r_bounding_box);
  
  SET_XML_ATTR(BoundingBox, bounding_box, Id, id, STRING);
  SET_XML_ATTR_OBJ_NOCHECK(BoundingBox, bounding_box, Position, position, Point,
                           point);
  SET_XML_ATTR_OBJ_NOCHECK(BoundingBox, bounding_box, Dimensions, dimensions,
                           Dimensions, dimensions);
  
  return bounding_box;
}

static void
rsbml_build_doc_base_graphical_object(GraphicalObject_t * graphical_object, SEXP r_graphical_object)
{
  SET_XML_ATTR(GraphicalObject, graphical_object, Id, id, STRING);
  SET_XML_ATTR_OBJ_NOCHECK(GraphicalObject, graphical_object, BoundingBox,
                           boundingBox, BoundingBox, bounding_box);
}

static GraphicalObject_t *
rsbml_build_doc_graphical_object(SEXP r_graphical_object)
{
  GraphicalObject_t * graphical_object;
  
  graphical_object = GraphicalObject_create();
  
  rsbml_build_doc_base_graphical_object(graphical_object, r_graphical_object);
  
  return graphical_object;
}

static CompartmentGlyph_t *
rsbml_build_doc_compartment_glyph(SEXP r_compartment_glyph)
{
  CompartmentGlyph_t * compartment_glyph;
  
  compartment_glyph = CompartmentGlyph_create();
  
  rsbml_build_doc_base_graphical_object((GraphicalObject_t *)compartment_glyph, r_compartment_glyph);
  
  SET_XML_ATTR_NOCHECK(CompartmentGlyph, compartment_glyph, CompartmentId,
                       compartment, STRING);
  
  return compartment_glyph;
}

static SpeciesGlyph_t *
rsbml_build_doc_species_glyph(SEXP r_species_glyph)
{
  SpeciesGlyph_t * species_glyph;
  
  species_glyph = SpeciesGlyph_create();
  
  rsbml_build_doc_base_graphical_object((GraphicalObject_t *)species_glyph, r_species_glyph);
  
  SET_XML_ATTR_NOCHECK(SpeciesGlyph, species_glyph, SpeciesId, species, STRING);
  
  return species_glyph;
}

static LineSegment_t *
rsbml_build_doc_line_segment(SEXP r_line_segment)
{
  LineSegment_t * line_segment;
  
  if (inherits(r_line_segment, "CubicBezier")) {
    line_segment = (LineSegment_t *)CubicBezier_create();
    SET_XML_ATTR_OBJ_NOCHECK(CubicBezier, line_segment, BasePoint1, basePoint1, Point, point);
    SET_XML_ATTR_OBJ_NOCHECK(CubicBezier, line_segment, BasePoint2, basePoint2, Point, point);
  } else {
    line_segment = LineSegment_create();
  }
  
  rsbml_build_doc_s_base((SBase_t *)line_segment, r_line_segment);
  
  SET_XML_ATTR_OBJ_NOCHECK(LineSegment, line_segment, Start, start, Point, point);
  SET_XML_ATTR_OBJ_NOCHECK(LineSegment, line_segment, End, end, Point, point);
  
  return line_segment;
}

static Curve_t *
rsbml_build_doc_curve(SEXP r_curve)
{
  Curve_t * curve;
  
  curve = Curve_create();
  
  rsbml_build_doc_s_base((SBase_t *)curve, r_curve);
  
  ADD_LIST_NOCHECK(Curve, curve, CurveSegment, curveSegments, LineSegment, line_segment);
  
  return curve;
}

static SpeciesReferenceGlyph_t *
rsbml_build_doc_species_reference_glyph(SEXP r_species_reference_glyph)
{
  SpeciesReferenceGlyph_t * species_reference_glyph;
  
  species_reference_glyph = SpeciesReferenceGlyph_create();
  
  rsbml_build_doc_base_graphical_object((GraphicalObject_t *)species_reference_glyph, 
    r_species_reference_glyph);
  
  SET_XML_ATTR_NOCHECK(SpeciesReferenceGlyph, species_reference_glyph, SpeciesGlyphId, speciesGlyph, STRING);
  SET_XML_ATTR_NOCHECK(SpeciesReferenceGlyph, species_reference_glyph, SpeciesReferenceId, speciesReference, STRING);
  SET_XML_ATTR_NOCHECK(SpeciesReferenceGlyph, species_reference_glyph, Role, role, STRING);
  SET_XML_ATTR_OBJ_NOCHECK(SpeciesReferenceGlyph, species_reference_glyph, Curve, glyphCurve, Curve, curve);
  
  return species_reference_glyph;
}

static ReactionGlyph_t *
rsbml_build_doc_reaction_glyph(SEXP r_reaction_glyph)
{
  ReactionGlyph_t * reaction_glyph;
  
  reaction_glyph = ReactionGlyph_create();
  
  rsbml_build_doc_base_graphical_object((GraphicalObject_t *)reaction_glyph, r_reaction_glyph);
  
  SET_XML_ATTR_NOCHECK(ReactionGlyph, reaction_glyph, ReactionId, reaction, STRING);
  SET_XML_ATTR_OBJ_NOCHECK(ReactionGlyph, reaction_glyph, Curve, glyphCurve, Curve, curve);
  ADD_LIST_NOCHECK(ReactionGlyph, reaction_glyph, SpeciesReferenceGlyph, 
    speciesReferenceGlyphs, SpeciesReferenceGlyph, species_reference_glyph);
  
  return reaction_glyph;
}

static TextGlyph_t *
rsbml_build_doc_text_glyph(SEXP r_text_glyph)
{
  TextGlyph_t * text_glyph;
  
  text_glyph = TextGlyph_create();
  
  rsbml_build_doc_base_graphical_object((GraphicalObject_t *)text_glyph, r_text_glyph);
  
  SET_XML_ATTR_NOCHECK(TextGlyph, text_glyph, GraphicalObjectId,
                       graphicalObject, STRING);
  SET_XML_ATTR_NOCHECK(TextGlyph, text_glyph, Text, text, STRING);
  SET_XML_ATTR_NOCHECK(TextGlyph, text_glyph, OriginOfTextId, originOfText,
                       STRING);
  
  return text_glyph;
}

static void
rsbml_build_doc_layout(SEXP r_layout, Model_t *model)
{
  Layout_t * layout;

#if LIBSBML_VERSION >= 50000
  LayoutModelPlugin_t *mplugin =
    (LayoutModelPlugin_t *)(SBase_getPlugin((SBase_t *)model, "layout"));
  layout = LayoutModelPlugin_createLayout(mplugin);
#else
  layout = Layout_create();
  Model_addLayout(model, layout);
  if (CLEANUP_MEMORY)
    Layout_free(layout);
  layout = Model_getLayout(model, Model_getNumLayouts(model) - 1);
#endif

  rsbml_build_doc_s_base((SBase_t *)layout, r_layout);
  
  SET_XML_ATTR(Layout, layout, Id, id, STRING);
#if LIBSBML_VERSION >= 50000
  SET_XML_ATTR_OBJ_NOCHECK(Layout, layout, Dimensions, dimensions, Dimensions,
                           dimensions);
#endif
  ADD_LIST_NOCHECK(Layout, layout, CompartmentGlyph, compartmentGlyphs, CompartmentGlyph, compartment_glyph);
  ADD_LIST_NOCHECK(Layout, layout, SpeciesGlyph, speciesGlyphs, SpeciesGlyph, species_glyph);
  ADD_LIST_NOCHECK(Layout, layout, ReactionGlyph, reactionGlyphs, ReactionGlyph, reaction_glyph);
  ADD_LIST_NOCHECK(Layout, layout, TextGlyph, textGlyphs, TextGlyph, text_glyph);
  ADD_LIST_NOCHECK(Layout, layout, AdditionalGraphicalObject, additionalGraphicalObjects, 
    GraphicalObject, graphical_object);
}
#endif

static InitialAssignment_t *
rsbml_build_doc_initial_assignment(SEXP r_initial_assignment)
{
  InitialAssignment_t * initial_assignment;
  
#if LIBSBML_VERSION >= 40000
  initial_assignment = InitialAssignment_create(SBML_LEVEL, SBML_VERSION);
#else
  initial_assignment = InitialAssignment_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)initial_assignment, r_initial_assignment);
  
  SET_XML_ATTR_OBJ(InitialAssignment, initial_assignment, Math, math, ASTNode, ast_node);
  SET_XML_ATTR(InitialAssignment, initial_assignment, Symbol, symbol, STRING);
  
  return initial_assignment;
}
static Constraint_t *
rsbml_build_doc_constraint(SEXP r_constraint)
{
  Constraint_t * constraint;
  
#if LIBSBML_VERSION >= 40000
  constraint = Constraint_create(SBML_LEVEL, SBML_VERSION);
#else
  constraint = Constraint_create();
#endif
  
  rsbml_build_doc_s_base((SBase_t *)constraint, r_constraint);
  
  SET_XML_ATTR_OBJ(Constraint, constraint, Math, math, ASTNode, ast_node);
  SET_XML_ATTR(Constraint, constraint, Message, message, rsbml_build_doc_xml_node);
  
  return constraint;
}

static ModelCreator_t *
rsbml_build_doc_model_creator(SEXP r_model_creator)
{
  ModelCreator_t * model_creator;
  
#if LIBSBML_VERSION >= 40000 && LIBSBML_VERSION < 50000
  model_creator = ModelCreator_create(SBML_LEVEL, SBML_VERSION);
#else
  model_creator = ModelCreator_create();
#endif
  
  SET_XML_ATTR(ModelCreator, model_creator, FamilyName, familyName, STRING);
  SET_XML_ATTR(ModelCreator, model_creator, GivenName, givenName, STRING);
  SET_XML_ATTR(ModelCreator, model_creator, Email, email, STRING);
  SET_XML_ATTR(ModelCreator, model_creator, Organisation, organization, STRING);
  
  return model_creator;
}

static ModelHistory_t *
rsbml_build_doc_model_history(SEXP r_model_history)
{
  ModelHistory_t * model_history;
  
#if LIBSBML_VERSION >= 40000 && LIBSBML_VERSION < 50000
  model_history = ModelHistory_create(SBML_LEVEL, SBML_VERSION);
#else
  model_history = ModelHistory_create();
#endif
  
  SET_XML_ATTR_OBJ(ModelHistory, model_history, CreatedDate, createdDate, Date,
                   date);
  SET_XML_ATTR_OBJ(ModelHistory, model_history, ModifiedDate, modifiedDate,
                   Date, date);
  ADD_LIST(ModelHistory, model_history, Creator, creators, ModelCreator,
           model_creator);
  
  return model_history;
}

static Model_t *
rsbml_build_doc_model(SEXP r_model, SBMLDocument_t *doc)
{
  
#if LIBSBML_VERSION >= 40000
  Model_t *model = SBMLDocument_createModel(doc);
#else
  Model_t *model = Model_create();
  SBMLDocument_setModel(doc, model);
  if (CLEANUP_MEMORY)
    Model_free(model);
  model = SBMLDocument_getModel(doc);
#endif

  rsbml_build_doc_s_base((SBase_t *)model, r_model);
  
  SET_XML_ATTR(Model, model, Id, id, STRING);
  SET_XML_ATTR(Model, model, Name, name, STRING);

  ADD_LIST(Model, model, Species, species, Species, species);
  ADD_LIST(Model, model, FunctionDefinition, functionDefinitions,
           FunctionDefinition, function_definition);
  ADD_LIST(Model, model, UnitDefinition, unitDefinitions, UnitDefinition,
           unit_definition);
  ADD_LIST(Model, model, Compartment, compartments, Compartment, compartment);
  ADD_LIST(Model, model, Parameter, parameters, Parameter, parameter);
  ADD_LIST(Model, model, Rule, rules, Rule, rule);
  ADD_LIST(Model, model, Reaction, reactions, Reaction, reaction);
  ADD_LIST(Model, model, Event, events, Event, event);
  ADD_LIST(Model, model, SpeciesType, speciesTypes, SpeciesType, species_type);
  ADD_LIST(Model, model, CompartmentType, compartmentTypes, CompartmentType,
           compartment_type);
  ADD_LIST(Model, model, InitialAssignment, initialAssignments,
           InitialAssignment, initial_assignment);
  ADD_LIST(Model, model, Constraint, constraints, Constraint, constraint);

  SET_XML_ATTR_OBJ(Model, model, ModelHistory, modelHistory, ModelHistory,
                   model_history);

#ifdef USE_LAYOUT
#if LIBSBML_VERSION >= 50000
  SBase_enablePackage((SBase_t *)doc,
                      "http://projects.eml.org/bcb/sbml/level2", "layout",
                      TRUE);
#endif
  SEXP list = GET_SLOT(r_model, install("layouts"));
  for (int i = 0; i < GET_LENGTH(list); i++) {
    rsbml_build_doc_layout(VECTOR_ELT(list, i), model);
  }
#endif
    
  return model;
}

static SBMLDocument_t *
rsbml_build_doc(SEXP r_doc)
{
  SBMLDocument_t *doc;
  
  
  SEXP r_level = GET_SLOT(r_doc, install("level"));
  SEXP r_version = GET_SLOT(r_doc, install("ver"));
  unsigned int level = 2, version = 3;
  if (GET_LENGTH(r_level))
    level = INTEGER_SCALAR(r_level);
  if (GET_LENGTH(r_version))
    version = INTEGER_SCALAR(r_version);

#if LIBSBML_VERSION >= 40000
  SBML_VERSION = version;
  SBML_LEVEL = level;
#endif

  doc = SBMLDocument_createWithLevelAndVersion(level, version);

  /* FIXME: if we had copious spare time and wanted to refactor, we
     could use this design for every element: pass the parent object
     down to the rsbml_build_doc_* function, and have it call the
     appropriate create() method on the parent. We would no longer
     need the SBML_LEVEL/VERSION global variables. This would also
     likely simplify memory management. */
  
  rsbml_build_doc_model(GET_SLOT(r_doc, install("model")), doc);
  
  return doc;
}

SEXP
rsbml_R_build_doc(SEXP r_doc)
{
  SBMLDocument_t *doc = rsbml_build_doc(r_doc);
  return rsbml_create_doc_ptr(doc);
}

static void
rsbml_R_free_doc(SEXP r_doc)
{
  SBMLDocument_t *doc = R_ExternalPtrAddr(r_doc);
  SBMLDocument_free(doc);
}

SEXP
rsbml_create_doc_ptr(SBMLDocument_t *doc)
{
  SEXP r_doc, class_vector;
  PROTECT(class_vector = NEW_CHARACTER(1));
  SET_STRING_ELT(class_vector, 0, mkChar("SBMLDocument"));
  r_doc = R_MakeExternalPtr(doc, R_NilValue, R_NilValue);
  R_RegisterCFinalizer(r_doc, (R_CFinalizer_t)rsbml_R_free_doc);
  SET_CLASS(r_doc, class_vector);
  UNPROTECT(1);
  return r_doc;
}
