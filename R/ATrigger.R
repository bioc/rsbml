setClass("Trigger", representation(math = "expression"), contains = "SBase")

setMethod("describe", "Trigger", function(object) as.character(math(object)))

setMethod("math", "Trigger", function(object) object@math)

setReplaceMethod("math", "Trigger", function(object, value) {
  object@math <- value
  object
})

