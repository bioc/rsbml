setClassUnion("OptionalDelay", c("Delay", "NULL"))
setClass("Event",
         representation(id = "character", name = "character",
                        trigger = "Trigger", eventDelay = "OptionalDelay",
                        timeUnits = "character", eventAssignments = "list"),
         contains = "SBase")

setMethod("describe", "Event",
          function(object) {
            assignments <- sapply(eventAssignments(object), describe)
            assignments <- paste(assignments, collapse = ", ")
            desc <- paste("When", describe(trigger(object)), ":", assignments)
            if (!is.null(delay))
              desc <- paste(desc, "after", describe(eventDelay(object)),
                            timeUnits(object))
            desc
          })

setMethod("id", "Event", function(object) object@id)

 
setMethod("name", "Event", function(object) object@name)

 setGeneric("trigger", function(object) standardGeneric("trigger"))
setMethod("trigger", "Event", function(object) object@trigger)

 setGeneric("eventDelay", function(object) standardGeneric("eventDelay"))
setMethod("eventDelay", "Event", function(object) object@eventDelay)

 setGeneric("timeUnits", function(object) standardGeneric("timeUnits"))
setMethod("timeUnits", "Event", function(object) object@timeUnits)

 setGeneric("eventAssignments", function(object) standardGeneric("eventAssignments"))
setMethod("eventAssignments", "Event", function(object) object@eventAssignments)

 
setReplaceMethod("id", "Event", function(object, value) {
  object@id <- value
  object
})

 
setReplaceMethod("name", "Event", function(object, value) {
  object@name <- value
  object
})

 setGeneric("trigger<-", function(object, value) standardGeneric("trigger<-"))
setReplaceMethod("trigger", "Event", function(object, value) {
  object@trigger <- value
  object
})

 setGeneric("eventDelay<-", function(object, value) standardGeneric("eventDelay<-"))
setReplaceMethod("eventDelay", "Event", function(object, value) {
  object@eventDelay <- value
  object
})

 setGeneric("timeUnits<-", function(object, value) standardGeneric("timeUnits<-"))
setReplaceMethod("timeUnits", "Event", function(object, value) {
  object@timeUnits <- value
  object
})

 setGeneric("eventAssignments<-", function(object, value) standardGeneric("eventAssignments<-"))
setReplaceMethod("eventAssignments", "Event", function(object, value) {
  if (!all(sapply(value, inherits, "Parameter")))
    stop("All assignments must be EventAssignment objects")
  object@eventAssignments <- value
  object
})

