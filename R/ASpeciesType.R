setClass("SpeciesType", representation(id = "character", name = "character"), contains = "SBase")

setMethod("id", "SpeciesType", function(object) object@id)

setMethod("name", "SpeciesType", function(object) object@name)

setReplaceMethod("id", "SpeciesType", function(object, value) {
  object@id <- value
  object
})

setReplaceMethod("name", "SpeciesType", function(object, value) {
  object@name <- value
  object
})

