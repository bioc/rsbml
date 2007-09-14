\name{Trigger-class}
\docType{class}
\alias{Trigger-class}
\alias{math,Trigger-method}
\alias{math<-,Trigger-method}

\title{SBML Type "Trigger"}
\description{Expresses when an \code{\linkS4class{Event}} should be fired.}
\section{Objects from the Class}{
Objects can be created by calls of the form \code{new("Trigger", ...)}.
}
\section{Slots}{
	 \describe{
    \item{\code{math}:}{Object of class \code{"expression"} that evaluates to
    \code{TRUE} when the event should be fired.}
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
  \item{math}{\code{signature(domain = "Trigger")}: gets the \code{math} slot. }
  \item{math<-}{\code{signature(object = "Trigger")}: sets the \code{math} slot. }
}
\references{\url{http://sbml.org/documents/}}
\author{Michael Lawrence}
\note{ Requires libsbml >= 3.0 }
\seealso{
	\code{\linkS4class{Event}}, the parent of this element.
}
\keyword{classes}
