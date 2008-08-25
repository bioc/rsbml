setClass("CompartmentGlyph", representation(compartment = "character"), contains = "GraphicalObject")

setMethod("describe", "CompartmentGlyph", function(object) {
  paste(describe(compartment(object)), callNextMethod(object))
})

 setGeneric("compartment", function(object) standardGeneric("compartment"))
setMethod("compartment", "CompartmentGlyph", function(object) object@compartment)

 setGeneric("compartment<-", function(object, value) standardGeneric("compartment<-"))
setReplaceMethod("compartment", "CompartmentGlyph", function(object, value) {
  object@compartment <- value
  object
})

