setClass("ModelHistory", representation(createdDate = "character", 
  modifiedDate = "character", creators = "list"))

 setGeneric("createdDate", function(object) standardGeneric("createdDate"))
setMethod("createdDate", "ModelHistory", function(object) object@createdDate)

 setGeneric("modifiedDate", function(object) standardGeneric("modifiedDate"))
setMethod("modifiedDate", "ModelHistory", function(object) object@modifiedDate)

 setGeneric("creators", function(object) standardGeneric("creators"))
setMethod("creators", "ModelHistory", function(object) object@creators)

 setGeneric("createdDate<-", function(object, value) standardGeneric("createdDate<-"))
setReplaceMethod("createdDate", "ModelHistory", function(object, value) {
  object@createdDate <- value
  object
})

 setGeneric("modifiedDate<-", function(object, value) standardGeneric("modifiedDate<-"))
setReplaceMethod("modifiedDate", "ModelHistory", function(object, value) {
  object@modifiedDate <- value
  object
})

 setGeneric("creators<-", function(object, value) standardGeneric("creators<-"))
setReplaceMethod("creators", "ModelHistory", function(object, value) {
  if (!all(sapply(value, inherits, "ModelCreator")))
    stop("All creators must be ModelCreator objects")
  object@creators <- value
  object
})

