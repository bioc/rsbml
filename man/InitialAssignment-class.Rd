\name{InitialAssignment-class}
\docType{class}
\alias{symbol}
\alias{symbol<-}
\alias{InitialAssignment-class}
\alias{math,InitialAssignment-method}
\alias{math<-,InitialAssignment-method}
\alias{symbol,InitialAssignment-method}
\alias{symbol<-,InitialAssignment-method}

\title{SBML Type "InitialAssignment"}
\description{Calculates the value of a symbol when the model is initialized.}
\section{Objects from the Class}{
Objects can be created by calls of the form \code{new("InitialAssignment", ...)}.
}
\section{Slots}{
	 \describe{
    \item{\code{symbol}:}{Object of class \code{"character"} to which the
      value is assigned.}
    \item{\code{math}:}{Object of class \code{"expression"} that evaluates
      to the assigned value.}
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
  \describe{
    \item{math}{\code{signature(object = "InitialAssignment")}: gets the \code{math} slot. }
    \item{math<-}{\code{signature(object = "InitialAssignment")}: sets the \code{math} slot. }
    \item{symbol}{\code{signature(object = "InitialAssignment")}: gets the \code{symbol} slot. }
    \item{symbol<-}{\code{signature(object = "InitialAssignment")}: sets the \code{symbol} slot. }
	 }
}
\references{\url{http://sbml.org/documents/}}
\author{Michael Lawrence}
\note{Requires libsbml >= 3.0}
\seealso{
	\code{\linkS4class{AssignmentRule}}, which can set a value at any time but cannot set constants.
}
\keyword{classes}
