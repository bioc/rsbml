\name{Constraint-class}
\docType{class}
\alias{Constraint-class}
\alias{math,Constraint-method}
\alias{math<-,Constraint-method}
\alias{msg,Constraint-method}
\alias{msg<-,Constraint-method}
\alias{msg<-}
\alias{msg}

\title{SBML Type "Constraint"}
\description{	A constraint that must be continuously satisfied throughout the
simulation of a model. Once a constraint is no longer met, the simulation must halt.}
\section{Objects from the Class}{
Objects can be created by calls of the form \code{new("Constraint", ...)}.
}
\section{Slots}{
	 \describe{
     \item{\code{math}:}{Object of class \code{"expression"} that evaluates to \code{FALSE}
     if the constraint is not satisfied, otherwise evaluates to \code{TRUE}. }
    \item{\code{message}:}{Object of class \code{"character"}, formatted in XHTML,
     that is displayed to the user by an application when the constraint is not satisfied.}
    \item{\code{metaId}:}{Object of class \code{"character"} that is an XML ID
      "described" by an RDF resource. This links an SBML element to an RDF
      resource. RDF may appear anywhere in an SBML element,
      but is usually placed inside the \code{annotation} element.}
    \item{\code{notes}:}{Object of class \code{"character"} 
      containing user-readable XHTML notes about an element. }
    \item{\code{annotation}:}{Object of class \code{"character"} containing
      additional machine-readable information about an element, usually as RDF,
      such as BioPAX. This is where application-specific data belongs.}
    \item{\code{cvTerms}:}{Object of class \code{"list"} containing
      instances of \code{\linkS4class{CVTerm}} associated with this
      element.}
    \item{\code{sboTerm}:}{Object of class \code{"integer"} identifying
      a term in the Systems Biology Ontology (SBO).}
  }
}
\section{Extends}{
Class \code{"\linkS4class{SBase}"}, directly.
}
\section{Methods}{
  \describe{
    \item{math}{\code{signature(domain = "Constraint")}: gets the \code{math} slot. }
    \item{math<-}{\code{signature(object = "Constraint")}: sets the \code{math} slot. }
    \item{msg}{\code{signature(domain = "Constraint")}: gets the \code{msg} slot. }
    \item{msg<-}{\code{signature(object = "Constraint")}: sets the \code{msg} slot. }
	 }
}
\references{\url{http://sbml.org/documents/}}
\author{Michael Lawrence}
\note{Requires libsbml >= 3.0}
\keyword{classes}
