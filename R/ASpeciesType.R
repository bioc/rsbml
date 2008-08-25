setClass("SpeciesType", representation(id = "character", name = "character"), contains = "SBase")

setMethod("describe", "SpeciesType",
          function(object) {
            desc <- id(object)
            if (length(name(object)))
              paste(desc, " (", name(object), ")", sep = "")
            desc
          })

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

