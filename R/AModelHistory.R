setClass("ModelHistory",
         representation(createdDate = "character", modifiedDate = "character",
                        creators = "list"),
         contains = "Describable")

setMethod("describe", "ModelHistory",
          function(object) {
            creatorDescs <- paste(sapply(creators(object), describe),
                                  collapse = ", ")
            c(paste("Created:", createdDate(object),
                    "Last modified:", modifiedDate(object)),
              paste("Creators:", creatorDescs))
          })

 setGeneric("createdDate", function(object) standardGeneric("createdDate"))
setMethod("createdDate", "ModelHistory", function(object) object@createdDate)

 setGeneric("modifiedDate", function(object) standardGeneric("modifiedDate"))
setMethod("modifiedDate", "ModelHistory", function(object) object@modifiedDate)

 setGeneric("creators", function(object) standardGeneric("creators"))
setMethod("creators", "ModelHistory", function(object) object@creators)

 setGeneric("createdDate<-", function(object, value) standardGeneric("createdDate<-"))
setReplaceMethod("createdDate", c("ModelHistory", "character"),
                 function(object, value) {
                   object@createdDate <- value
                   object
                 })
setReplaceMethod("createdDate", c("ModelHistory", "POSIXt"),
                 function(object, value)
                 {
                   createdDate(object) <- format(value, "%Y-%m-%dT%H:%M:%S%z")
                   object
                 })

 setGeneric("modifiedDate<-", function(object, value) standardGeneric("modifiedDate<-"))
setReplaceMethod("modifiedDate", c("ModelHistory", "character"),
                 function(object, value) {
                   object@modifiedDate <- value
                   object
                 })
setReplaceMethod("modifiedDate", c("ModelHistory", "POSIXt"),
                 function(object, value)
                 {
                   modifiedDate(object) <- format(value, "%Y-%m-%dT%H:%M:%S%z")
                   object
                 })

 setGeneric("creators<-", function(object, value) standardGeneric("creators<-"))
setReplaceMethod("creators", "ModelHistory", function(object, value) {
  if (!all(sapply(value, inherits, "ModelCreator")))
    stop("All creators must be ModelCreator objects")
  object@creators <- value
  object
})

