#include "rsbml.h"
#include "StringMap.h"

#ifdef LIBSBML3
#define SimpleSpeciesReference_getSpecies(x) SpeciesReference_getSpecies(x)
typedef SpeciesReference_t SimpleSpeciesReference_t;
#endif

SEXP
rsbml_build_graph(SBMLDocument_t *doc)
{
  SEXP r_graph, r_nodes, r_edges, r_edge_name;
  Model_t *model = SBMLDocument_getModel(doc);
  StringMap_t *id_map;
  int num_species, num_reactions;
  long i;
  int *out_count, *out_pos;
  
  PROTECT(r_graph = NEW_OBJECT(MAKE_CLASS("graphNEL")));
  SET_SLOT(r_graph, install("edgemode"), ScalarString(mkChar("directed")));
  
  num_species = Model_getNumSpecies(model);
  num_reactions = Model_getNumReactions(model);
  
  r_nodes = NEW_CHARACTER(num_species + num_reactions);
  SET_SLOT(r_graph, install("nodes"), r_nodes);
  out_count = (int *)S_alloc(num_species + num_reactions, sizeof(int));
  out_pos = (int *)S_alloc(num_species, sizeof(int));
  
  id_map = StringMap_create();
  for (i = 0; i < num_species; i++) {
    const char *id;
    Species_t *species = Model_getSpecies(model, i);
    if (Species_isSetId(species))
      id = Species_getId(species);
    else id = Species_getName(species);
    SET_STRING_ELT(r_nodes, i, mkChar(id));
  }
  for (i = 0; i < num_reactions; i++) {
    Reaction_t *reaction = Model_getReaction(model, i);
    const char *id;
    if (Reaction_isSetId(reaction))
      id = Reaction_getId(reaction);
    else id = Reaction_getName(reaction);
    SET_STRING_ELT(r_nodes, i + num_species, mkChar(id));
  }
  
  for (i = 0; i < GET_LENGTH(r_nodes); i++)
    StringMap_put(id_map, CHAR(STRING_ELT(r_nodes, i)), (void *)i);
  
  r_edges = NEW_LIST(num_species + num_reactions);
  SET_SLOT(r_graph, install("edgeL"), r_edges);
  for (i = 0; i < num_reactions; i++) {
    Reaction_t *reaction = Model_getReaction(model, i);
    int j, num_reactants = Reaction_getNumReactants(reaction);
    int num_modifiers = Reaction_getNumModifiers(reaction);
    const char *id = Reaction_isSetId(reaction) ? Reaction_getId(reaction) : 
      Reaction_getName(reaction); 
    long reaction_index = (long) StringMap_get(id_map, id);
    out_count[reaction_index] = Reaction_getNumProducts(reaction);
    for (j = 0; j < num_reactants; j++) {
      const char *id = SimpleSpeciesReference_getSpecies(
        (SimpleSpeciesReference_t *)Reaction_getReactant(reaction, j));
      long index = (long) StringMap_get(id_map, id);
      out_count[index]++;
    }
    for (j = 0; j < num_modifiers; j++) {
      const char *id = SimpleSpeciesReference_getSpecies(
        (SimpleSpeciesReference_t *)Reaction_getModifier(reaction, j));
      long index = (long) StringMap_get(id_map, id);
      out_count[index]++;
    }
  }
  
  PROTECT(r_edge_name = ScalarString(mkChar("edges")));
  for (i = 0; i < num_species + num_reactions; i++) {
    SEXP r_edge_element;
    PROTECT(r_edge_element = NEW_LIST(1));
    SET_VECTOR_ELT(r_edge_element, 0, NEW_INTEGER(out_count[i]));
    SET_NAMES(r_edge_element, r_edge_name);
    SET_VECTOR_ELT(r_edges, i, r_edge_element);
    UNPROTECT(1);
  }
  UNPROTECT(1);
  
  for (i = 0; i < num_reactions; i++) {
    Reaction_t *reaction = Model_getReaction(model, i);
    int j, num_reactants = Reaction_getNumReactants(reaction);
    int num_modifiers = Reaction_getNumModifiers(reaction);
    int num_products = Reaction_getNumProducts(reaction);
    const char *id = Reaction_isSetId(reaction) ? Reaction_getId(reaction) : 
      Reaction_getName(reaction); 
    long reaction_index = (long) StringMap_get(id_map, id);
    SEXP reaction_out = VECTOR_ELT(VECTOR_ELT(r_edges, reaction_index), 0);
    for (j = 0; j < num_reactants; j++) {
      const char *id = SimpleSpeciesReference_getSpecies(
        (SimpleSpeciesReference_t *)Reaction_getReactant(reaction, j));
      long index = (long) StringMap_get(id_map, id);
      //Rprintf("reactant index: %d edge count: %d\n", index, out_count[index]);
      INTEGER(VECTOR_ELT(VECTOR_ELT(r_edges, index), 0))[out_pos[index]++] = reaction_index + 1;
    }
    for (j = 0; j < num_modifiers; j++) {
      const char *id = SimpleSpeciesReference_getSpecies(
        (SimpleSpeciesReference_t *)Reaction_getModifier(reaction, j));
      long index = (long) StringMap_get(id_map, id);
      //Rprintf("modifier index: %d edge count: %d\n", index, out_count[index]);
      INTEGER(VECTOR_ELT(VECTOR_ELT(r_edges, index), 0))[out_pos[index]++] = reaction_index + 1;
    }
    for (j = 0; j < num_products; j++) {
      const char *id = SimpleSpeciesReference_getSpecies(
        (SimpleSpeciesReference_t *)Reaction_getProduct(reaction, j));
      long index = (long) StringMap_get(id_map, id);
      //Rprintf("product index: %d\n", index);
      INTEGER(reaction_out)[j] = index + 1;
    }
  }
  
  SET_NAMES(r_edges, r_nodes);
  
  UNPROTECT(1);
  return r_graph;
}

SEXP
rsbml_R_build_graph(SEXP r_doc)
{
  SBMLDocument_t *doc = R_ExternalPtrAddr(r_doc);
  if (rsbml_errors(doc))
    error("Cannot build graph from document with errors");
  return rsbml_build_graph(doc);
}
