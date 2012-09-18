setClass("SBase", representation(metaId = "character", notes = "character", 
  annotation = "character", cvTerms = "list", sboTerm = "integer"), contains=c("VIRTUAL", "Describable"))

setGeneric("metaId", function(object) standardGeneric("metaId"))
setMethod("metaId", "SBase", function(object) object@metaId)

setGeneric("notes", function(object) standardGeneric("notes"))
setMethod("notes", "SBase", function(object) object@notes)

setMethod("annotation", "SBase", function(object) object@annotation)

setGeneric("cvTerms", function(object) standardGeneric("cvTerms"))
setMethod("cvTerms", "SBase", function(object) object@cvTerms)

setGeneric("sboTerm", function(object) standardGeneric("sboTerm"))
setMethod("sboTerm", "SBase", function(object) object@sboTerm)

setGeneric("metaId<-",
           function(object, value) standardGeneric("metaId<-"))
setReplaceMethod("metaId", "SBase", function(object, value) {
    object@metaId <- value
    object
})

setGeneric("notes<-",
           function(object, value) standardGeneric("notes<-"))
setReplaceMethod("notes", "SBase", function(object, value) {
    object@notes <- value
    object
})

setReplaceMethod("annotation", "SBase", function(object, value) {
    object@annotation <- value
    object
})

setGeneric("cvTerms<-",
           function(object, value) standardGeneric("cvTerms<-"))
setReplaceMethod("cvTerms", "SBase", function(object, value) {
    if (!all(sapply(value, inherits, "CVTerm")))
      stop("All cvTerms must be CVTerm objects")
    object@cvTerms <- value
    object
})

setGeneric("sboTerm<-",
           function(object, value) standardGeneric("sboTerm<-"))
setReplaceMethod("sboTerm", "SBase", function(object, value) {
    object@sboTerm <- value
    object
})
