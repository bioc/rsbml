### FIXME: may need a 'verbose' argument here that prints info messages
rsbml_read <- 
function(filename, text, dom = TRUE, strict = FALSE, schema = FALSE,
         consistency = TRUE)
{
  if (!missing(filename)) {
    filename <- path.expand(filename)
    obj <- .Call("rsbml_R_read_doc", as.character(filename), 
      as.logical(schema), PACKAGE="rsbml")
  }
  else if (!missing(text))
    obj <- .Call("rsbml_R_read_doc_from_string", as.character(text), 
      as.logical(schema), PACKAGE="rsbml")
  else stop("You must supply either 'filename' or 'text'")
  rsbml_check(obj, strict, consistency)
  if (dom)
    rsbml_dom(obj)
  else obj
}

setGeneric("rsbml_dom", function(doc) standardGeneric("rsbml_dom"))
setMethod("rsbml_dom", "SBMLDocument", function(doc)
  .Call("rsbml_R_build_dom", doc, PACKAGE="rsbml"))
setAs("SBMLDocument", "SBML", function(from) rsbml_dom(from))

setGeneric("rsbml_doc", function(model) standardGeneric("rsbml_doc"))
setMethod("rsbml_doc", "SBML", function(model) 
  .Call("rsbml_R_build_doc", model, PACKAGE="rsbml"))
setAs("SBML", "SBMLDocument", function(from) rsbml_doc(from))

setGeneric("rsbml_xml", function(x) standardGeneric("rsbml_xml"))
setMethod("rsbml_xml", "SBMLDocument", function(x)
{
 if (.Platform$OS.type == "windows")
 {
   warning("This function is not supported on Windows.")
   return(invisible(NULL))
 }
 .Call("rsbml_R_write_doc_to_string", x, PACKAGE="rsbml")
})
setMethod("rsbml_xml", "SBML", function(x) {
  doc <- rsbml_doc(x)
  rsbml_xml(doc)
})
as.character.SBMLDocument <- as.character.SBML <- function(x, ...) rsbml_xml(x)

setGeneric("rsbml_write", function(object, filename) standardGeneric("rsbml_write"))
setMethod("rsbml_write", "SBMLDocument", function(object, filename) 
  invisible(.Call("rsbml_R_write_doc", object, as.character(filename), PACKAGE="rsbml")))
setMethod("rsbml_write", "SBML", function(object, filename) {
  doc <- rsbml_doc(object)
  rsbml_write(doc, filename)
})

### FIXME: this is total amateur hour. We should just have an S4
### wrapper around SBMLDocument and define a validity function on it,
### like we have for 'SBML'. But whatever.
setGeneric("rsbml_check",
function(object, strict = FALSE, consistency = TRUE)
           standardGeneric("rsbml_check"))
setMethod("rsbml_check", "SBMLDocument",
          function(object, strict, consistency)
{
  problems <- rsbml_problems(object, consistency)
  if (length(fatals(problems)) || length(errors(problems)) ||
      (strict && length(warns(problems))))
    {
      .throw(problems, strict)
      FALSE
    } else TRUE
})

setMethod("rsbml_check", "SBML", function(object, strict, consistency) {
  rsbml_check(rsbml_doc(object), strict, consistency)
})

setGeneric("rsbml_problems", function(object, consistency = TRUE, ...)
  standardGeneric("rsbml_problems"))
setMethod("rsbml_problems", "SBMLDocument",
          function(object, consistency = TRUE) {
            if (consistency) {
              .Call("rsbml_R_check_doc", object, PACKAGE="rsbml")
            }
            probs <- .Call("rsbml_R_problems", object, PACKAGE="rsbml")
### FIXME: these objects should be constructed C side
            classes <- c("SBMLInfo", "SBMLWarning", "SBMLError", "SBMLFatal")
            makeProblems <- function(ind)
              lapply(probs[[ind]],
                     function(prob) do.call(new, c(classes[ind], prob)))
            formalProbs <- lapply(seq_along(probs), makeProblems)
            names(formalProbs) <- names(probs)
            do.call(new, c("SBMLProblems", formalProbs))
          })
