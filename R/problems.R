setClass("SBMLProblems",
         representation(fatals = "list", errors = "list", warnings = "list",
                        infos = "list"))

setGeneric("fatals", function(object, ...) standardGeneric("fatals"))
setMethod("fatals", "SBMLProblems", function(object) object@fatals)

setGeneric("errors", function(object, ...) standardGeneric("errors"))
setMethod("errors", "SBMLProblems", function(object) object@errors)

setGeneric("warns", function(object, ...) standardGeneric("warns"))
setMethod("warns", "SBMLProblems", function(object) object@warnings)

setGeneric("infos", function(object, ...) standardGeneric("infos"))
setMethod("infos", "SBMLProblems", function(object) object@infos)


setGeneric(".throw", function(object, ...)
           standardGeneric(".throw"))

setMethod(".throw", "SBMLProblems",
          function(object, strict = FALSE) {
            if (strict) {
              sapply(warns(object), .throw)
            }
            sapply(errors(object), .throw)
            sapply(fatals(object), .throw)
          })

setClass("SBMLProblem",
         representation(line = "numeric", column = "numeric",
                        msg = "character"),
         contains = "VIRTUAL")

setGeneric(".condition", function(object, ...) standardGeneric(".condition"))
setMethod(".condition", "SBMLProblem", function(object, type) {
  class <- c(class(object), type, "condition")
  structure(list(message = object@msg, call = NULL,
                 line = object@line, column = object@column), 
            class = class)
})

setMethod("show", "SBMLProblem",
          function(object) {
            cat("[", class(object), "] (", object@line, ", ", object@column,
                ") ", object@msg, sep="")
          })


setClass("SBMLFatal", contains = "SBMLProblem")
setMethod(".throw", "SBMLFatal",
          function(object) stop(.condition(object, "error")))

setClass("SBMLError", contains = "SBMLProblem")
setMethod(".throw", "SBMLError",
          function(object) stop(.condition(object, "error")))

setClass("SBMLWarning", contains = "SBMLProblem")
setMethod(".throw", "SBMLWarning",
          function(object) warning(.condition(object, "warning")))

setClass("SBMLInfo", contains = "SBMLProblem")
setMethod(".throw", "SBMLInfo",
          function(object) message(.condition(object, "message")))
