setClass("AssignmentRule", representation(variable = "character", type = "character"), 
  contains = "Rule")

setMethod("describe", "AssignmentRule",
          function(object) paste(variable(object), ":=", math(object)))

setMethod("type", "AssignmentRule", function(x) x@type)

setReplaceMethod("type", "AssignmentRule", function(x, value) {
  if (!(type %in% c("rate", "scalar")))
    stop("Rule type must be either 'rate' or 'scalar', not ", type)
  x@type <- value
  x
})

setMethod("variable", "AssignmentRule", function(object) object@variable)

setReplaceMethod("variable", "AssignmentRule", function(object, value) {
  object@variable <- value
  object
})

