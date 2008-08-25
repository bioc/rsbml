setClassUnion("OptionalCurve", c("Curve", "NULL"))
setClass("SpeciesReferenceGlyph",
         representation(speciesGlyph = "character",
                        speciesReference = "character", role = "character",
                        glyphCurve = "OptionalCurve"), 
         prototype(role = "undefined"), "GraphicalObject")

setMethod("describe", "SpeciesReferenceGlyph",
          function(object) {
            desc <- speciesReference(object)
            if (length(role(object)))
              desc <- paste(desc, "as", role(object))
            if (!is.null(glyphCurve))
              desc <- paste(desc, "via", describe(glyphCurve(object)))
            paste(desc, callNextMethod(object))
          })

 setGeneric("speciesGlyph", function(object) standardGeneric("speciesGlyph"))
setMethod("speciesGlyph", "SpeciesReferenceGlyph", function(object) object@speciesGlyph)

 setGeneric("speciesReference", function(object) standardGeneric("speciesReference"))
setMethod("speciesReference", "SpeciesReferenceGlyph", function(object) object@speciesReference)

 setGeneric("role", function(object) standardGeneric("role"))
setMethod("role", "SpeciesReferenceGlyph", function(object) object@role)

setGeneric("glyphCurve", function(object) standardGeneric("glyphCurve"))
setMethod("glyphCurve", "SpeciesReferenceGlyph", 
  function(object) object@glyphCurve)

 setGeneric("speciesGlyph<-", function(object, value) standardGeneric("speciesGlyph<-"))
setReplaceMethod("speciesGlyph", "SpeciesReferenceGlyph", function(object, value) {
  object@speciesGlyph <- value
  object
})

 setGeneric("speciesReference<-", function(object, value) standardGeneric("speciesReference<-"))
setReplaceMethod("speciesReference", "SpeciesReferenceGlyph", function(object, value) {
  object@speciesReference <- value
  object
})

.validRoles <- c("substrate", "product", "sidesubstrate", "sideproduct", "modifier",
  "activator", "inhibitor", "undefined")
  
 setGeneric("role<-", function(object, value) standardGeneric("role<-"))
setReplaceMethod("role", "SpeciesReferenceGlyph", function(object, value) {
  if (!(role %in% .validRoles))
    stop("Role must be one of ", paste(.validRoles, collapse=","), ".")
  object@role <- value
  object
})

 setGeneric("glyphCurve<-", function(object, value) standardGeneric("glyphCurve<-"))
setReplaceMethod("glyphCurve", "SpeciesReferenceGlyph", function(object, value) {
  if (is.null(value))
    object <- new("SpeciesReferenceGlyph", speciesGlyph = speciesGlyph(object),
      speciesReference = speciesReference(object), role = role(object))
  object@glyphCurve <- value
  object
})


