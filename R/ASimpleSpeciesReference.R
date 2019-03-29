setClass("SimpleSpeciesReference", representation(id = "character", species = "character"), 
  contains = "SBase")

setMethod("describe", "SimpleSpeciesReference",
          function(object) species(object))

setMethod("id", "SimpleSpeciesReference", function(object) object@id)
 
setReplaceMethod("id", "SimpleSpeciesReference", function(object, value) {
  object@id <- value
  object
})

setMethod("species", "SimpleSpeciesReference", function(object) object@species)

setReplaceMethod("species", "SimpleSpeciesReference", function(object, value) {
  object@species<- value
  object
})
