setClass("Constraint", representation(math = "expression", message = "character"), contains = "SBase")

setMethod("math", "Constraint", function(object) object@math)

 setGeneric("message", function(..., domain = NULL, appendLF = TRUE) standardGeneric("message"))
setMethod("message", "Constraint", function(..., domain = NULL, appendLF = TRUE) 
  list(...)[[1]]@message)

setReplaceMethod("math", "Constraint", function(object, value) {
  object@math <- value
  object
})

 setGeneric("message<-", function(object, value) standardGeneric("message<-"))
setReplaceMethod("message", "Constraint", function(object, value) {
  object@message <- value
  object
})

