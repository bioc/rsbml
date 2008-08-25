setClass("CompartmentType", representation(id = "character", name = "character"), contains = "SBase")

setMethod("describe", "CompartmentType",
          function(object) {
            desc <- id(object)
            if (length(name(object)))
              paste(desc, " (", name(object), ")", sep = "")
            desc
          })

setMethod("id", "CompartmentType", function(object) object@id)

setGeneric("name", function(object) standardGeneric("name"))
setMethod("name", "CompartmentType", function(object) object@name)

setReplaceMethod("id", "CompartmentType", function(object, value) {
  object@id <- value
  object
})

setGeneric("name<-", function(object, value) standardGeneric("name<-"))
setReplaceMethod("name", "CompartmentType", function(object, value) {
  object@name <- value
  object
})

