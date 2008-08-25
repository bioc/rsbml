\name{SBMLDocument-class}
\docType{class}
\alias{SBMLDocument-class}
\alias{coerce,SBMLDocument,graph-method}
\alias{coerce,SBMLDocument,SBML-method}
\alias{rsbml_check,SBMLDocument-method}
\alias{rsbml_check}
\alias{rsbml_dom,SBMLDocument-method}
\alias{rsbml_dom}
\alias{rsbml_graph,SBMLDocument-method}
\alias{rsbml_graph}
\alias{rsbml_problems,SBMLDocument-method}
\alias{rsbml_problems}
\alias{rsbml_write,SBMLDocument-method}
\alias{rsbml_xml,SBMLDocument-method}
\alias{as.character.SBMLDocument}

\title{"SBMLDocument" from libsbml}
\description{Low-level libsbml document structure.}
\section{Instantiation}{A virtual Class: No objects may be created from it.}
\section{Extends}{
Class \code{"\linkS4class{oldClass}"}, directly.
}
\section{Methods}{
  \describe{
    \item{rsbml\_check}{\code{signature(object = "SBMLDocument")}:
      \code{rsbml_check(object, quiet = FALSE, verbose = FALSE)}:
      semantically validates the document. If \code{quiet} is
      \code{TRUE}, emits warnings describing errors and fatal failures
      encountered when the document was parsed. If \code{verbose} is
      also \code{TRUE}, reports less critical warnings about problems in
      the model, such as internal inconsistencies.}
    \item{rsbml\_dom}{\code{signature(doc = "SBMLDocument")}: Constructs an S4 
      object model from a libsbml document. }
    \item{rsbml\_graph}{\code{signature(doc = "SBMLDocument")}: Converts a 
      libsbml document to a \code{\link[graph:graph-class]{graph}}. }
    \item{rsbml\_problems}{\code{signature(object = "SBMLDocument")}: 
      reports problems encountered during parsing and/or validation.}
    \item{rsbml\_write}{\code{signature(object = "SBMLDocument")}: writes this 
      document to a file as SBML. }
    \item{rsbml\_xml}{\code{signature(object = "SBMLDocument")}: converts this 
      document to a string as SBML. }
	 }
}
\examples{
  # Read a document into an R DOM
  dom <- rsbml_read(system.file("sbml", "GlycolysisLayout.xml", package
= "rsbml"))
  
  # Convert to a graph
  graph <- rsbml_graph(doc)
  
  # Write it out to a file
  \dontrun{rsbml_write(doc, "my.xml")}
  
  # Or convert it to a string of XML
  rsbml_xml(doc)

  # Read into external libsbml data structure
  doc <- rsbml_read(system.file("sbml", "GlycolysisLayout.xml", package
= "rsbml"), dom = FALSE)
  
  # Convert it explicitly to an S4 DOM
  dom <- rsbml_dom(doc)
}
\references{\url{http://sbml.org/documents/}}
\author{Michael Lawrence}
\keyword{classes}
