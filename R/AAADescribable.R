setClass("Describable")

setGeneric("describe", function(object, ...) standardGeneric("describe"))

setMethod("show", "Describable", function(object) {
  cat(describe(object), sep = "\n")
  cat("\n")
})
