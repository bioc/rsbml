setClass("ReactionGlyph",
         representation(reaction = "character", glyphCurve = "OptionalCurve", 
                        speciesReferenceGlyphs = "list"),
         contains = "GraphicalObject")

 setGeneric("reaction", function(object) standardGeneric("reaction"))
setMethod("reaction", "ReactionGlyph", function(object) object@reaction)

setMethod("glyphCurve", "ReactionGlyph", function(object) object@glyphCurve)

 setGeneric("speciesReferenceGlyphs", function(object) standardGeneric("speciesReferenceGlyphs"))
setMethod("speciesReferenceGlyphs", "ReactionGlyph", function(object) object@speciesReferenceGlyphs)

 setGeneric("reaction<-", function(object, value) standardGeneric("reaction<-"))
setReplaceMethod("reaction", "ReactionGlyph", function(object, value) {
  object@reaction <- value
  object
})

setReplaceMethod("glyphCurve", "ReactionGlyph", function(object, value) {
  if (is.null(value))
    object <- new("ReactionGlyph", reaction = reaction(object), 
      speciesReferenceGlyphs = speciesReferenceGlyphs(object))
  object@glyphCurve <- value
  object
})

 setGeneric("speciesReferenceGlyphs<-", function(object, value) standardGeneric("speciesReferenceGlyphs<-"))
setReplaceMethod("speciesReferenceGlyphs", "ReactionGlyph", function(object, value) {
  if (!all(sapply(value, inherits, "SpeciesReferenceGlyph")))
    stop("All species reference glyphs must be SpeciesReferenceGlyph objects")
  names(value) <- sapply(value, id)
  object@speciesReferenceGlyphs <- value
  object
})

