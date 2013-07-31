setGeneric("rsbml_graph", function(doc) standardGeneric("rsbml_graph"))

### FIXME: need to push all SBML layout information into renderInfo

setMethod("rsbml_graph", "SBMLDocument", function(doc) {
  rsbml_graph(rsbml_dom(doc))
})

setMethod("rsbml_graph", "SBML", function(doc) {
  rsbml_graph(model(doc))
})

setMethod("rsbml_graph", "Model", function(doc) {
  species <- species(doc)
  reactions <- reactions(doc)
  productEdges <- lapply(reactions, function(r) {
    list(edges = as.character(lapply(products(r), species)),
         weights = as.integer(lapply(products(r), stoichiometry)))
  })
  makeReactantEdges <- function(accessor) {
    reactantNames <- lapply(reactions,
                            function(r)
                            as.character(lapply(reactants(r), species)))
    reactantWeights <- lapply(reactions,
                              function(r)
                              as.integer(lapply(reactants(r), stoichiometry)))
    reactionNames <- split(rep(names(reactions),
                               graph:::listLen(reactantNames)),
                           unlist(reactantNames, use.names = FALSE))
    reactantWeights <- split(unlist(reactantWeights, use.names = FALSE),
                             unlist(reactantNames, use.names = FALSE))
    mapply(list, edges = reactionNames, weights = reactantWeights,
           SIMPLIFY = FALSE)
  }
  reactantEdges <- makeReactantEdges(reactants)
  modifierEdges <- makeReactantEdges(modifiers)
  nodeNames <- c(names(species), names(reactions))
  edgeL <- rep(list(list(edges = character(), weights = numeric())),
               length(nodeNames))
  names(edgeL) <- nodeNames
  reactionEdges <- c(productEdges, reactantEdges, modifierEdges)
  edgeL[names(reactionEdges)] <- reactionEdges
  new("graphNEL", nodes = nodeNames, edgeL = edgeL, edgemode = "directed")
})

setAs("SBMLDocument", "graph", function(from) rsbml_graph(from))
setAs("SBML", "graph", function(from) rsbml_graph(from))
