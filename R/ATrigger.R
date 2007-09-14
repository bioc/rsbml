setClass("Trigger", representation(math = "expression"), contains = "SBase")

setMethod("math", "Trigger", function(object) object@math)

setReplaceMethod("math", "Trigger", function(object, value) {
  object@math <- value
  object
})

