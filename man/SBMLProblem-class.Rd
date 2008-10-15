\name{SBMLProblem-class}
\docType{class}
\alias{SBMLProblem-class}
\alias{.condition,SBMLProblem-method}
\alias{show,SBMLProblem-method}
\alias{SBMLFatal-class}
\alias{.throw,SBMLFatal-method}
\alias{SBMLError-class}
\alias{.throw,SBMLError-method}
\alias{.throw,SBMLWarning-method}
\alias{.throw,SBMLInfo-method}
\alias{SBMLWarning-class}
\alias{SBMLInfo-class}

\title{SBMLProblem}
\description{Represents an exception thrown during SBML parsing.}
\section{Slots}{
  \describe{
    \item{\code{line}:}{The \code{"numeric"} line number in the SBML
      file where the problem was detected. }
    \item{\code{column}:}{Object of class \code{"numeric"} column number
      in the SBML file where the problem was detected. }
    \item{\code{msg}:}{Object of class \code{"character"}, a
      human-readable description of the problem. }
  }
}
\section{Methods}{
  \describe{
    \item{.condition}{\code{signature(object = "SBMLProblem")}:
      constructs a \code{\link{condition}} object representing the exception. }
  }
}
\details{
  There are trivial subclasses for fatal errors (\code{SBMLFatal}),
  recoverable errors (\code{SBMLError}), warnings (\code{SBMLWarning})
  and informational messages (\code{SBMLInfo}). Errors become R
  \code{error} \code{\link{condition}}s, warnings become R
  \code{\link{warning}} conditions and messages are output via
  \code{\link{message}}.
}
\author{ Michael Lawrence }
\seealso{
  \code{\linkS4class{SBMLProblems}}, a container for instances of this class.
}
\keyword{classes}
