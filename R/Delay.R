setClass("Delay", representation(math = "expression"), contains = "SBase")

setMethod("describe", "Delay", function(object) as.character(math(object)))

setMethod("math", "Delay", function(object) object@math)

setReplaceMethod("math", "Delay", function(object, value) {
  object@math <- value
  object
})

