setClass("StoichiometryMath", representation(math = "expression"), contains = "SBase")

setMethod("describe", "StoichiometryMath",
          function(object) as.character(object@math))

setMethod("math", "StoichiometryMath", function(object) object@math)

setReplaceMethod("math", "StoichiometryMath", function(object, value) {
  object@math <- asMath(value)
  object
})

