setClass("SpeciesGlyph", representation(species = "character"), contains = "GraphicalObject")

setMethod("describe", "SpeciesGlyph",
          function(object) paste(species(object), callNextMethod(object)))

setMethod("species", "SpeciesGlyph", function(object) object@species)

setReplaceMethod("species", "SpeciesGlyph", function(object, value) {
  object@species <- value
  object
})

