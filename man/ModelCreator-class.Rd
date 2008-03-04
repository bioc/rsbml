\name{ModelCreator-class}
\docType{class}
\alias{ModelCreator-class}
\alias{email}
\alias{email,ModelCreator-method}
\alias{email<-}
\alias{email<-,ModelCreator-method}
\alias{familyName}
\alias{familyName,ModelCreator-method}
\alias{familyName<-}
\alias{familyName<-,ModelCreator-method}
\alias{givenName}
\alias{givenName,ModelCreator-method}
\alias{givenName<-}
\alias{givenName<-,ModelCreator-method}
\alias{organization}
\alias{organization,ModelCreator-method}
\alias{organization<-}
\alias{organization<-,ModelCreator-method}

\title{SBML Type "ModelCreator"}
\description{Information, such as name, email and organization, about a
  creator of an SBML model.}
\section{Objects from the Class}{
  Objects can be created by calls of the form \code{new("ModelCreator", ...)}.
}
\section{Slots}{
  \describe{
    \item{\code{familyName}:}{Object of class \code{"character"} specifying
      the family name of the creator. }
    \item{\code{givenName}:}{Object of class \code{"character"} specifying
      the given name of the creator. }
    \item{\code{email}:}{Object of class \code{"character"} specifying
      the email address of the creator. }
    \item{\code{organization}:}{Object of class \code{"character"}
      specifying the name of the organization to which the creator belongs. }
  }
}
\section{Methods}{
  \describe{
    \item{email}{\code{signature(object = "ModelCreator")}: gets the \code{email} slot. }
    \item{email<-}{\code{signature(object = "ModelCreator")}: sets the \code{email<-} slot. }
    \item{familyName}{\code{signature(object = "ModelCreator")}: gets the \code{familyName} slot. }
    \item{familyName<-}{\code{signature(object = "ModelCreator")}: sets the \code{familyName<-} slot. }
    \item{givenName}{\code{signature(object = "ModelCreator")}: gets the \code{givenName} slot. }
    \item{givenName<-}{\code{signature(object = "ModelCreator")}: sets the \code{givenName<-} slot. }
    \item{organization}{\code{signature(object = "ModelCreator")}: gets the \code{organization} slot. }
    \item{organization<-}{\code{signature(object = "ModelCreator")}: sets the \code{organization<-} slot. }
  }
}
\references{\url{http://sbml.org/documents/}}
\author{Michael Lawrence}
\keyword{classes}
