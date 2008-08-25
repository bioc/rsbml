setClass("ModelCreator",
         representation(familyName = "character", givenName = "character",
                        email = "character", organization = "character"),
         contains = "Describable")

setMethod("describe", "ModelCreator",
          function(object) paste(givenName(object), " ", familyName(object),
                                 "(", email(object), ") at",
                                 organization(object), sep = ""))

 setGeneric("familyName", function(object) standardGeneric("familyName"))
setMethod("familyName", "ModelCreator", function(object) object@familyName)

 setGeneric("givenName", function(object) standardGeneric("givenName"))
setMethod("givenName", "ModelCreator", function(object) object@givenName)

 setGeneric("email", function(object) standardGeneric("email"))
setMethod("email", "ModelCreator", function(object) object@email)

 setGeneric("organization", function(object) standardGeneric("organization"))
setMethod("organization", "ModelCreator", function(object) object@organization)

 setGeneric("familyName<-", function(object, value) standardGeneric("familyName<-"))
setReplaceMethod("familyName", "ModelCreator", function(object, value) {
  object@familyName <- value
  object
})

 setGeneric("givenName<-", function(object, value) standardGeneric("givenName<-"))
setReplaceMethod("givenName", "ModelCreator", function(object, value) {
  object@givenName <- value
  object
})

 setGeneric("email<-", function(object, value) standardGeneric("email<-"))
setReplaceMethod("email", "ModelCreator", function(object, value) {
  object@email <- value
  object
})

 setGeneric("organization<-", function(object, value) standardGeneric("organization<-"))
setReplaceMethod("organization", "ModelCreator", function(object, value) {
  object@organization <- value
  object
})

