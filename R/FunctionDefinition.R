setClass("FunctionDefinition", representation(id = "character", name = "character", math = "expression"), 
  contains = "SBase") 

setMethod("describe", "FunctionDefinition",
          function(object) paste(id(object), "<-", math(object)))

setMethod("id", "FunctionDefinition", function(object) object@id)

 
setMethod("name", "FunctionDefinition", function(object) object@name)

setMethod("math", "FunctionDefinition", function(object) object@math)

 
setReplaceMethod("id", "FunctionDefinition", function(object, value) {
  object@id <- value
  object
})

 
setReplaceMethod("name", "FunctionDefinition", function(object, value) {
  object@name <- value
  object
})

setReplaceMethod("math", "FunctionDefinition", function(object, value) {
  object@math <- as.expression(value)
  object
})

