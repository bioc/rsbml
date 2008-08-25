setGeneric("rsbml_graph", function(doc) standardGeneric("rsbml_graph"))
setMethod("rsbml_graph", "SBMLDocument", function(doc) {
### FIXME: need to push all SBML layout information into renderInfo
### FIXME: probably best to rewrite this stuff in R
  .Call("rsbml_R_build_graph", doc, PACKAGE="rsbml")
})
setAs("SBMLDocument", "graph", function(from) rsbml_graph(from))
setMethod("rsbml_graph", "SBML", function(doc) rsbml_graph(rsbml_doc(doc)))
setAs("SBML", "graph", function(from) rsbml_graph(from))
