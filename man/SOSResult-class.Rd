\name{SOSResult-class}
\docType{class}
\alias{SOSResult-class}
\alias{as.ts,SOSResult-method}
\alias{compartments,SOSResult-method}
\alias{parameters,SOSResult-method}
\alias{reactions,SOSResult-method}
\alias{species,SOSResult-method}

\title{SOSResult}
\description{A result from simulating an
  \code{\linkS4class{SOSExperiment}}. Contains the time course for each
  of the model variables: the \code{\linkS4class{Species}} quantities,
  \code{\linkS4class{Compartment}} sizes, \code{\linkS4class{Parameter}}
  values, and \code{\linkS4class{Reaction}} rates.
}
\section{Slots}{
  \describe{
    \item{\code{data}:}{A \code{"data.frame"} containing the time course
      data. Each row contains the value at a single time point for a
      single time course. Has the following columns:
      \describe{
        \item{\code{sample}}{A factor, the run number, only exists if there
          were multiple runs, see \code{\linkS4class{SOSDesign}}.}
        \item{\code{type}}{A factor, the SBML element type for the time course,
          e.g. \code{"species"}.}
        \item{\code{id}}{A factor, the \code{id} of the SBML element for
          the time course.}
        \item{\code{time}}{The numeric time value for the time point.}
        \item{\code{value}}{The actual numeric value for the time course
          at that time.}
      }
    }
    \item{\code{sens}:}{A \code{"matrix"} with results from sensitivity
      analysis, not yet supported. }
  }
}
\section{Extends}{
Class \code{"\linkS4class{ExperimentResult}"}, directly.
}
\section{Methods}{
  \describe{
    \item{as.ts}{\code{signature(x = "SOSResult")}: converts this object
      to a time course object of class \code{ts}. This allows analysis of
      the results with existing R infrastructure for time course analysis.}
    \item{compartments}{\code{signature(object = "SOSResult")}: returns
      a subset containing only the \code{\linkS4class{Compartment}} size
      courses.}
    \item{parameters}{\code{signature(object = "SOSResult")}: returns
      a subset containing only the global \code{\linkS4class{Parameter}}
      value courses.}
    \item{reactions}{\code{signature(object = "SOSResult")}: returns
      a subset containing only the \code{\linkS4class{Reaction}} rate courses.}
    \item{species}{\code{signature(object = "SOSResult")}: returns
      a subset containing only the \code{\linkS4class{Species}} quantity
      courses. }
  }
}
\references{ See \url{http://www.tbi.univie.ac.at/~raim/odeSolver/} for
  more information on the SBML ODE Solver library. }
\author{ Michael Lawrence }
\seealso{
  \code{\linkS4class{SOSExperiment}} for running a simulation and
  obtaining an instance of this class.
}
\keyword{classes}
