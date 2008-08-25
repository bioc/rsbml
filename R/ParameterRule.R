setClass("ParameterRule", representation(name = "character", units = "character"),
  contains = "AssignmentRule")

setMethod("describe", "ParameterRule",
          function(object) paste(name(object), ":=", math(object),
                                 units(object)))

setMethod("name", "ParameterRule", function(object) object@name)

setMethod("units", "ParameterRule", function(x) x@units)

 
setReplaceMethod("name", "ParameterRule", function(object, value) {
  object@name <- value
  object
})

setReplaceMethod("units", "ParameterRule", function(x, value) {
  x@units <- value
  x
})
