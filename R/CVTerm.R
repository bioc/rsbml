setClass("CVTerm",
         representation(qualifierType = "character",
                        modelQualifierType = "character",
                        biologicalQualifierType = "character",
                        resources = "character"),
         contains = "Describable")

setMethod("describe", "CVTerm", function(object) {
  qtype <- qualifierType(object)
  if (qualifierType == "model")
    type <- modelQualifierType(object)
  else if (qualifierType == "biological")
    type <- biologicalQualifierType(object)
  paste(qtype, ":", type, ":", resources(object), sep = "")
})

 setGeneric("qualifierType", function(object) standardGeneric("qualifierType"))
setMethod("qualifierType", "CVTerm", function(object) object@qualifierType)

 setGeneric("modelQualifierType", function(object) standardGeneric("modelQualifierType"))
setMethod("modelQualifierType", "CVTerm", function(object) object@modelQualifierType)

 setGeneric("biologicalQualifierType", function(object) standardGeneric("biologicalQualifierType"))
setMethod("biologicalQualifierType", "CVTerm", function(object) object@biologicalQualifierType)

 setGeneric("resources", function(object) standardGeneric("resources"))
setMethod("resources", "CVTerm", function(object) object@resources)

.qualifierTypes <- c("model", "biological", "unknown")
 setGeneric("qualifierType<-", function(object, value) standardGeneric("qualifierType<-"))
setReplaceMethod("qualifierType", "CVTerm", function(object, value) {
  if (!(value %in% .qualifierTypes))
    stop("Invalid qualifier type ", value, ". Qualifier type must be one of ", .qualifierTypes)
  object@qualifierType <- value
  object
})

.modelQualifierTypes <- c("is", "isDescribedBy", "unknown")
 setGeneric("modelQualifierType<-", function(object, value) standardGeneric("modelQualifierType<-"))
setReplaceMethod("modelQualifierType", "CVTerm", function(object, value) {
  if (!(value %in% .modelQualifierTypes))
    stop("Invalid model qualifier type ", value, ". Model qualifier type must be one of ", .modelQualifierTypes)
  object@modelQualifierType <- value
  object
})

.biologicalQualifierTypes <- c("is", "hasPart", "isPartOf", "isVersionOf", 
  "hasVersion", "isHomologTo", "isDescribedBy", "unknown")
 setGeneric("biologicalQualifierType<-", function(object, value) standardGeneric("biologicalQualifierType<-"))
setReplaceMethod("biologicalQualifierType", "CVTerm", function(object, value) {
  if (!(value %in% .biologicalQualifierTypes))
    stop("Invalid biological qualifier type ", value, ". Biological qualifier type must be one of ", .biologicalQualifierTypes)
  object@biologicalQualifierType <- value
  object
})

 setGeneric("resources<-", function(object, value) standardGeneric("resources<-"))
setReplaceMethod("resources", "CVTerm", function(object, value) {
  object@resources <- value
  object
})

