\name{SpeciesType-class}
\docType{class}
\alias{SpeciesType-class}
\alias{id,SpeciesType-method}
\alias{id<-,SpeciesType-method}
\alias{name,SpeciesType-method}
\alias{name<-,SpeciesType-method}

\title{SBML Type "SpeciesType"}
\description{A \code{\linkS4class{Species}} represents a pool of a chemical
in a particular \code{linkS4class{Compartment}}. This element specifies a
type of species, that is, the chemical independent of location.}
\section{Objects from the Class}{
Objects can be created by calls of the form \code{new("SpeciesType", ...)}.
}
\section{Slots}{
	 \describe{
    \item{\code{id}:}{Object of class \code{"character"} uniquely identifying this component. }
    \item{\code{name}:}{Object of class \code{"character"} naming this component. }
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
    \item{id}{\code{signature(object = "SpeciesType")}: gets the \code{id} slot }
    \item{id<-}{\code{signature(object = "SpeciesType")}: sets the \code{id} slot }
    \item{name}{\code{signature(object = "SpeciesType")}: gets the \code{name} slot }
    \item{name<-}{\code{signature(object = "SpeciesType")}: sets the \code{name} slot }
	 }
}
\references{\url{http://sbml.org/documents/}}
\author{Michael Lawrence}
\note{ Requires libsbml >= 3.0 }
\seealso{
	\code{\linkS4class{Species}}
}
\keyword{classes}
