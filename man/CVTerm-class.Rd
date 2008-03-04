\name{CVTerm-class}
\docType{class}
\alias{CVTerm-class}
\alias{biologicalQualifierType}
\alias{biologicalQualifierType<-}
\alias{modelQualifierType}
\alias{modelQualifierType<-}
\alias{qualifierType}
\alias{qualifierType<-}
\alias{resources}
\alias{resources<-}
\alias{biologicalQualifierType,CVTerm-method}
\alias{biologicalQualifierType<-,CVTerm-method}
\alias{modelQualifierType,CVTerm-method}
\alias{modelQualifierType<-,CVTerm-method}
\alias{qualifierType,CVTerm-method}
\alias{qualifierType<-,CVTerm-method}
\alias{resources,CVTerm-method}
\alias{resources<-,CVTerm-method}

\title{SBML Type "CVTerm"}
\description{ A MIRIAM annotation, consisting of a qualifier ("model",
  "biological" or something else) and a resource (URI). }
\section{Objects from the Class}{
Objects can be created by calls of the form \code{new("CVTerm", ...)}.
}
\section{Slots}{
  \describe{
    \item{\code{qualifierType}:}{Object of class \code{"character"}
      specifying the type of qualifier for this term. Types "model" and
      "biological" have special meaning, but any string may be specified.}
    \item{\code{modelQualifierType}:}{Object of class \code{"character"}
      specifying the type of model qualifier, if \code{qualifierType} is
      set to "model". Types "is" and "isDescribedBy" are formally
      defined in MIRIAM, but any string may be specified.}
    \item{\code{biologicalQualifierType}:}{Object of class
      \code{"character"} specifying the type of biological qualifier, if
      \code{qualifierType} is set to "biological". Types "is", "hasPart",
      "isPartOf", "isVersionOf", "hasVersion", "isHomologTo",
      and "isDescribedBy" are formally defined in MIRIAM, though any
      string may be specified.}
    \item{\code{resources}:}{Object of class \code{"character"}
      specifying a URI that identifies some resource related an SBML
      element by the qualifier.}
  }
}
\section{Methods}{
  \describe{
    \item{biologicalQualifierType}{\code{signature(object = "CVTerm")}:
      gets the \code{biologicalQualifierType} slot.
    }
    \item{biologicalQualifierType<-}{\code{signature(object =
        "CVTerm")}: 
      sets the \code{biologicalQualifierType} slot.
    }
    \item{modelQualifierType}{\code{signature(object = "CVTerm")}:
      gets the \code{modelQualifierType} slot.
    }
    \item{modelQualifierType<-}{\code{signature(object = "CVTerm")}:
      sets the \code{modelQualifierType} slot.
    }
    \item{qualifierType}{\code{signature(object = "CVTerm")}:
      gets the \code{qualifierType} slot.
    }
    \item{qualifierType<-}{\code{signature(object = "CVTerm")}:
      sets the \code{qualifierType} slot.
    }
    \item{resources}{\code{signature(object = "CVTerm")}:
      gets the \code{resources} slot.
    }
    \item{resources<-}{\code{signature(object = "CVTerm")}:
      sets the \code{resources} slot.
    }
  }
}
\references{\url{http://sbml.org/documents/}}
\author{ Michael Lawrence }
\keyword{classes}
