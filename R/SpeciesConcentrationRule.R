setClass("SpeciesConcentrationRule", representation(species = "character"), 
  contains = "AssignmentRule")

setMethod("describe", "SpeciesConcentrationRule",
          function(object) paste("[", species, "] = ", math(object), sep = ""))

setMethod("species", "SpeciesConcentrationRule", function(object) object@species)

setReplaceMethod("species", "SpeciesConcentrationRule", function(object, value) {
  object@species<- value
  object
})
