\name{Delay-class}
\docType{class}
\alias{Delay-class}
\alias{math,Delay-method}
\alias{math<-,Delay-method}

\title{SBML Type "Delay"}
\description{	The length of time between the \code{\linkS4class{Trigger}}ing of an 
\code{\linkS4class{Event}} and the execution of its \code{\linkS4class{EventAssignment}}s.}
\section{Objects from the Class}{
Objects can be created by calls of the form \code{new("Delay", ...)}.
}
\section{Slots}{
	 \describe{
    \item{\code{math}:}{Object of class \code{"expression"} that evaluates to
    a quantity of time.}
    \item{\code{metaId}:}{Object of class \code{"character"} that is an XML ID
      "described" by an RDF resource. This links an SBML element to an RDF
      resource. RDF may appear anywhere in an SBML element,
      but is usually placed inside the \code{annotation} element.}
    \item{\code{notes}:}{Object of class \code{"character"} 
      containing user-readable XHTML notes about an element. }
    \item{\code{annotation}:}{Object of class \code{"character"} containing
      additional machine-readable information about an element, usually as RDF,
      such as BioPAX. This is where application-specific data belongs.}
  }
}
\section{Extends}{
Class \code{"\linkS4class{SBase}"}, directly.
}
\section{Methods}{
  \item{math}{\code{signature(domain = "Delay")}: gets the \code{math} slot. }
  \item{math<-}{\code{signature(object = "Delay")}: sets the \code{math} slot. }
}
\references{\url{http://sbml.org/documents/}}
\author{Michael Lawrence}
\note{ Requires libsbml >= 3.0 }
\seealso{\code{\linkS4class{Event}}}
\keyword{classes}
