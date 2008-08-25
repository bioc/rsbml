setClass("Constraint", representation(math = "expression", message = "character"), contains = "SBase")

setMethod("describe", "Constraint",
          function(object)
          paste(math(object), " (", msg(object), ")", sep = ""))

setMethod("math", "Constraint", function(object) object@math)

setGeneric("msg", function(object) standardGeneric("msg"))
setMethod("msg", "Constraint", function(object) object@message)

setReplaceMethod("math", "Constraint", function(object, value) {
  object@math <- value
  object
})

setGeneric("msg<-", function(object, value) standardGeneric("msg<-"))
setReplaceMethod("msg", "Constraint", function(object, value) {
  object@message <- value
  object
})

