setClass("RateRule", representation(variable = "character"), 
  contains = "Rule")

setMethod("describe", "RateRule",
          function(object) paste(variable(object), ":=", math(object)))

setMethod("variable", "RateRule", function(object) object@variable)

setReplaceMethod("variable", "RateRule", function(object, value) {
  object@variable <- value
  object
})

