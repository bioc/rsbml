setClassUnion("OptionalStoichiometryMath", c("StoichiometryMath", "NULL"))
setClass("SpeciesReference",
         representation(stoichiometry = "numeric",
                        stoichiometryMath = "OptionalStoichiometryMath"), 
         prototype(stoichiometry = 1), "SimpleSpeciesReference")

setMethod("describe", "SpeciesReference", function(object) {
  stoich <- stoichiometryMath(object)
  if (is.null(stoich)) {
    stoich <- stoichiometry(object)
    if (stoich == 1)
      stoich <- ""
  } else stoich <- describe(stoich)
  if (nchar(stoich))
    stoich <- paste("(", stoich, ")", sep = "")
  paste(stoich, callNextMethod(object), sep = "")
})

 setGeneric("stoichiometry", function(object) standardGeneric("stoichiometry"))
setMethod("stoichiometry", "SpeciesReference", function(object) object@stoichiometry)

 setGeneric("stoichiometryMath", function(object) standardGeneric("stoichiometryMath"))
setMethod("stoichiometryMath", "SpeciesReference", function(object) object@stoichiometryMath)

 setGeneric("stoichiometry<-", function(object, value) standardGeneric("stoichiometry<-"))
setReplaceMethod("stoichiometry", "SpeciesReference", function(object, value) {
  object@stoichiometry <- value
  object
})

 setGeneric("stoichiometryMath<-", function(object, value) standardGeneric("stoichiometryMath<-"))
setReplaceMethod("stoichiometryMath", "SpeciesReference", function(object, value) {
  object@stoichiometryMath <- value
  object
})

