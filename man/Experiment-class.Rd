\name{Experiment-class}
\docType{class}
\alias{Experiment-class}
\alias{design}
\alias{design<-}
\alias{design,Experiment-method}
\alias{design<-,Experiment-method}
\alias{protocol}
\alias{protocol<-}
\alias{protocol,Experiment-method}
\alias{protocol<-,Experiment-method}
\alias{reactions<-,Experiment-method}
\alias{result,Experiment-method}
\alias{result<-,Experiment-method}
\alias{result}
\alias{result<-}
\alias{subject,Experiment-method}
\alias{subject<-,Experiment-method}
\alias{subject}
\alias{subject<-}
\alias{ExperimentDesign-class}
\alias{ExperimentSubject-class}
\alias{ExperimentResult-class}
\alias{ExperimentProtocol-class}

\title{Experiment}
\description{This class is an abstraction for an experiment, e.g. in a
  simulation. An experiment consists of a
  \code{ExperimentProtocol}, \code{ExperimentDesign},
  \code{ExperimentSubject} and \code{ExperimentResult}.}

\section{Objects from the Class}{A virtual Class: No objects may be created from it.}
\section{Slots}{
  \describe{
    \item{\code{protocol}:}{Object of empty virtual class
      \code{ExperimentProtocol}, how the experiment was
      or is to be performed.} 
    \item{\code{design}:}{Object of empty virtual class
      \code{ExperimentDesign}, the design of the experiment.}
    \item{\code{subject}:}{Object of empty virtual class
      \code{ExperimentSubject}, 
      the object being observed by the experiment. }
    \item{\code{result}:}{Object of empty virtual class
      \code{ExperimentResult}, the result of the experiment.}
  }
}
\section{Methods}{
  \describe{
    \item{design}{\code{signature(object = "Experiment")}: Gets the
      \code{design} slot. }
    \item{design<-}{\code{signature(object = "Experiment")}: Sets the
      \code{design} slot. }
    \item{protocol}{\code{signature(object = "Experiment")}: Gets the
      \code{protocol} slot. }
    \item{protocol<-}{\code{signature(object = "Experiment")}: Sets the
      \code{protocol} slot. }
    \item{result}{\code{signature(object = "Experiment")}: Gets the
      \code{result} slot. }
    \item{result<-}{\code{signature(object = "Experiment")}: Sets the
      \code{result} slot. }
    \item{subject}{\code{signature(object = "Experiment")}: Gets the
      \code{subject} slot. }
    \item{subject<-}{\code{signature(object = "Experiment")}: Sets the
      \code{subject} slot. }
  }
}
\author{ Michael Lawrence }
\seealso{
  \code{\linkS4class{SOSExperiment}}, an implementation that simulates
  SBML modules using the SBML ODE Solver library.
}
\keyword{classes}
