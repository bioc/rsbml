setClass("SBML", representation(level = "integer", ver = "integer", model = "Model"), 
  contains = "SBase", prototype = list(level = as.integer(2), ver = as.integer(1)),
  validity = function(object) {
    doc <- rsbml_doc(object)
    valid <- rsbml_perform_check(doc)
    if (!valid)
      as(rsbml_problems(doc), "character")
    else NULL
  })

setMethod("describe", "SBML",
          function(object) {
            desc <- paste("SBML Document (level = ", level(object),
                          ", version = ", ver(object), ")", sep = "")
            c(desc, describe(model(object)))
          })

setGeneric("level", function(object) standardGeneric("level"))
setMethod("level", "SBML", function(object) object@level)

setGeneric("ver", function(object) standardGeneric("ver"))
setMethod("ver", "SBML", function(object) object@ver)

setGeneric("level<-", function(object, value) standardGeneric("level<-"))
setReplaceMethod("level", "SBML", function(object, value) {
    object@level <- as.integer(value)
    object
})

setGeneric("ver<-", function(object, value) standardGeneric("ver<-"))
setReplaceMethod("ver", "SBML", function(object, value) {
    object@ver <- as.integer(value)
    object
})

setGeneric("model", function(object) standardGeneric("model"))
setMethod("model", "SBML", function(object) object@model)

 setGeneric("model<-", function(object, value) standardGeneric("model<-"))
setReplaceMethod("model", "SBML", function(object, value) {
  object@model <- value
  object
})

