\name{SOSExperiment-class}
\docType{class}
\alias{SOSExperiment-class}
\alias{simulate,SOSExperiment-method}
\alias{simulate}

\title{SOS Experiment}
\description{Implementation of \code{\linkS4class{Experiment}} for
  simulating SBML models using the SOS: (S)BML (O)DE (S)olver library.}
\section{Objects from the Class}{
  Objects can be created by calls of the form \code{new("SOSExperiment", ...)}.
}
\section{Slots}{
  \describe{
    \item{\code{protocol}:}{Object of class
      \code{\linkS4class{SOSProtocol}}, where 
      the simulation parameters are specified.}
    \item{\code{design}:}{Object of class
      \code{\linkS4class{SOSDesign}}, 
      specifying model parameters for each run of a batch experiment.}
    \item{\code{subject}:}{Object of class \code{\linkS4class{SOSSubject}},
      containing the \code{\linkS4class{Model}} to be simulated.}
    \item{\code{result}:}{Object of class
      \code{\linkS4class{SOSResult}}
      containing the result of the simulation. }
  }
}
\section{Extends}{
Class \code{\linkS4class{Experiment}}, directly.
}
\section{Methods}{
  \describe{
    \item{simulate}{\code{signature(object = "SOSExperiment")}:
      \code{simulate(object, nsim = 10, seed, ...)}: Simulates
      the SBML document in the \code{subject} slot according to the
      design points in \code{design} and parameters in \code{protocol}
      for \code{nsim} iterations, using \code{seed} as the random
      seed. Returns an instance of \code{SOSExperiment}, which now
      should include a \code{\linkS4class{SOSResult}} for analysis.}
  }
}
\details{
  The general workflow for running a simulation:
  \enumerate{
    \item Create or import an \linkS4class{SBML} DOM.
    \item Customize the model, for example by adding perturbation
      \code{\linkS4class{Event}}s.
    \item Wrap the SBML DOM in a \code{\linkS4class{SOSSubject}},
      e.g. \code{new("SOSSubject", dom)}.
    \item Optionally construct a \code{\linkS4class{SOSDesign}} for
      running the experiment in batch over several sets of model parameter
      settings.
    \item Optionally construct a \code{\linkS4class{SOSProtocol}} for
      specifying the time points and other parameters controlling the
      simulation.
    \item Construct an instance of this class that groups the subject,
      design and protocol.
    \item Run \code{simulate} on the \code{SOSExperiment}, optionally
      specifying the number of iterations and the random seed.
    \item Analyze the returned \code{\linkS4class{SOSResult}}, perhaps
      starting by converting it to a time series with \code{\link{as.ts}} and
      making some plots.
  }
}
\references{ See \url{http://www.tbi.univie.ac.at/~raim/odeSolver/} for
  more information on the SBML ODE Solver library. }
\author{ Michael Lawrence }
\seealso{
  The \code{simulate} method on \code{\linkS4class{SBMLDocument}} is a
  shortcut, but most users will probably find the above approach most
  useful.
}
\keyword{classes}
