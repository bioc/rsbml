\name{CompartmentType-class}
\docType{class}
\alias{CompartmentType-class}
\alias{id,CompartmentType-method}
\alias{id<-,CompartmentType-method}
\alias{name,CompartmentType-method}
\alias{name<-,CompartmentType-method}

\title{SBML Type "CompartmentType"}
\description{ Declares a type of \code{\linkS4class{Compartment}}. Compartments
with the same type are logically similar.}
\section{Objects from the Class}{
Objects can be created by calls of the form \code{new("CompartmentType", ...)}.
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
    \item{id}{\code{signature(object = "CompartmentType")}: gets the \code{id} slot }
    \item{id<-}{\code{signature(object = "CompartmentType")}: sets the \code{id} slot }
    \item{name}{\code{signature(object = "CompartmentType")}: gets the \code{name} slot }
    \item{name<-}{\code{signature(object = "CompartmentType")}: sets the \code{name} slot }
	 }
}
\references{\url{http://sbml.org/documents/}}
\author{Michael Lawrence}
\note{ Requires libsbml >= 3.0 }

\seealso{
	\code{\linkS4class{Compartment}}
}
\keyword{classes}
