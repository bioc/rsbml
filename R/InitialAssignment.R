setClass("InitialAssignment", representation(symbol = "character", math = "expression"), contains = "SBase")

setMethod("describe", "InitialAssignment",
          function(object) paste(symbol(object), "=", math(object)))

 setGeneric("symbol", function(object) standardGeneric("symbol"))
setMethod("symbol", "InitialAssignment", function(object) object@symbol)

setMethod("math", "InitialAssignment", function(object) object@math)

 setGeneric("symbol<-", function(object, value) standardGeneric("symbol<-"))
setReplaceMethod("symbol", "InitialAssignment", function(object, value) {
  object@symbol <- value
  object
})

setReplaceMethod("math", "InitialAssignment", function(object, value) {
  object@math <- value
  object
})

