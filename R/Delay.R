setClass("Delay", representation(math = "expression"), contains = "SBase")

setMethod("math", "Delay", function(object) object@math)

setReplaceMethod("math", "Delay", function(object, value) {
  object@math <- value
  object
})

