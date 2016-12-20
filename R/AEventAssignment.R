setClass("EventAssignment", representation(variable = "character", math = "expression"), 
  contains = "SBase")

setMethod("describe", "EventAssignment",
          function(object) paste(variable(object), "=", math(object)))

 setGeneric("variable", function(object) standardGeneric("variable"))
setMethod("variable", "EventAssignment", function(object) object@variable)

setMethod("math", "EventAssignment", function(object) object@math)

 setGeneric("variable<-", function(object, value) standardGeneric("variable<-"))
setReplaceMethod("variable", "EventAssignment", function(object, value) {
  object@variable <- value
  object
})

setReplaceMethod("math", "EventAssignment", function(object, value) {
  object@math <- asMath(value)
  object
})

