\name{SBMLProblems-class}
\docType{class}
\alias{SBMLProblems-class}
\alias{.throw,SBMLProblems-method}
\alias{errors,SBMLProblems-method}
\alias{fatals,SBMLProblems-method}
\alias{infos,SBMLProblems-method}
\alias{warns,SBMLProblems-method}
\alias{warns}
\alias{infos}
\alias{errors}
\alias{fatals}

\title{SBMLProblems}
\description{A class representing errors encountered during parsing of SBML.}
\section{Slots}{
  \describe{
    \item{\code{fatals}:}{A list of
      \code{\linkS4class{SBMLFatal}} instances. }
    \item{\code{errors}:}{A list of
      \code{\linkS4class{SBMLError}} instances. }
    \item{\code{warnings}:}{A list of
      \code{\linkS4class{SBMLWarning}} instances. }
    \item{\code{infos}:}{A list of
      \code{\linkS4class{SBMLInfo}} instances. }
  }
}
\section{Methods}{
  \describe{
    \item{.throw}{\code{signature(object = "SBMLProblems")}: Throws each
      \code{\linkS4class{SBMLProblem}} in this object.}
    \item{errors}{\code{signature(object = "SBMLProblems")}: Gets the
      \code{errors} slot. }
    \item{fatals}{\code{signature(object = "SBMLProblems")}: Gets the
      \code{fatals} slot. }
    \item{infos}{\code{signature(object = "SBMLProblems")}: Gets the
      \code{infos} slot. }
    \item{warns}{\code{signature(object = "SBMLProblems")}: Gets the
      \code{warns} slot. }
  }
}
\author{ Michael Lawrence }
\seealso{
  The \code{\link{rsbml_problems}} function for obtaining an instance of this
    class describing any problems encountered during parsing.}
\keyword{classes}
