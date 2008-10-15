\name{ModelHistory-class}
\docType{class}
\alias{ModelHistory-class}
\alias{createdDate}
\alias{createdDate,ModelHistory-method}
\alias{createdDate<-}
\alias{creators}
\alias{creators<-}
\alias{modifiedDate}
\alias{modifiedDate<-}
\alias{createdDate,ModelHistory-method}
\alias{createdDate<-,ModelHistory,character-method}
\alias{createdDate<-,ModelHistory,POSIXt-method}
\alias{creators,ModelHistory-method}
\alias{creators<-,ModelHistory-method}
\alias{modifiedDate,ModelHistory-method}
\alias{modifiedDate<-,ModelHistory-method}
\alias{modifiedDate<-,ModelHistory,character-method}
\alias{modifiedDate<-,ModelHistory,POSIXt-method}
\alias{OptionalModelHistory-class}

\title{SBML Type "ModelHistory"}
\description{Stores the history of an SBML model, including the
  created/modified dates and the creators.}
\section{Objects from the Class}{
  Objects can be created by calls of the form \code{new("ModelHistory", ...)}. 
}
\section{Slots}{
  \describe{
    \item{\code{createdDate}:}{Object of class \code{"character"}
      representing the date/time of creation, in W3CDTF format: 
      \code{YYYY-MM-DDThh:mm:ssTZD}, e.g. "1997-07-16T19:20:30+01:00".}
    \item{\code{modifiedDate}:}{Object of class \code{"character"}
      representing the date/time of last modification, in W3CDTF format: 
      \code{YYYY-MM-DDThh:mm:ssTZD}, e.g. "1997-07-16T19:20:30+01:00".}
    \item{\code{creators}:}{Object of class \code{"list"} of instances
      of \code{\linkS4class{ModelCreator}}, one for each creator of the model.}
  }
}
\section{Methods}{
  \describe{
    \item{createdDate}{\code{signature(object = "ModelHistory")}:
      get the \code{createdDate} slot.}
    \item{createdDate<-}{\code{signature(object = "ModelHistory", value =
        "character")}: Set the \code{createdDate} slot to a correctly
      formatted string. }
    \item{createdDate<-}{\code{signature(object = "ModelHistory", value =
        "POSIXt")}: Set the \code{createdDate} slot with a
      \code{\link{POSIXt}} instance, obtained e.g. from
      \code{\link{Sys.time}}.}
    \item{creators}{\code{signature(object = "ModelHistory")}: gets the
      \code{creators} slot. }
    \item{creators<-}{\code{signature(object = "ModelHistory")}: sets
      the \code{creators} slot. }
    \item{modifiedDate}{\code{signature(object = "ModelHistory")}:
      get the \code{modifiedDate} slot.}
    \item{modifiedDate<-}{\code{signature(object = "ModelHistory", value =
        "character")}: Set the \code{modifiedDate} slot to a correctly
      formatted string. }
    \item{modifiedDate<-}{\code{signature(object = "ModelHistory", value =
        "POSIXt")}: Set the \code{modifiedDate} slot with a
      \code{\link{POSIXt}} instance, obtained e.g. from
      \code{\link{Sys.time}}.}
  }
}
\references{\url{http://sbml.org/documents/}}
\author{Michael Lawrence}
\keyword{classes}
