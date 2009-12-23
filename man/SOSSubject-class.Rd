\name{SOSSubject-class}
\docType{class}
\alias{SOSSubject-class}

\title{SOSSubject}
\description{This just marks an \code{\linkS4class{SBML}} object as being a
  valid subject for simulation using the SBML ODE Solver library.}
\section{Objects from the Class}{
  Normally created from a \code{SBML} with: \code{new("SOSSubject", model)}.
}
\section{Extends}{
  Class \code{"\linkS4class{ExperimentSubject}"}, directly.
  Class \code{"\linkS4class{SBML}"}, directly.
  Class \code{"\linkS4class{SBase}"}, by class "SBML", distance 2.
  Class \code{"\linkS4class{Describable}"}, by class "SBML", distance 3.
}
\references{ See \url{http://www.tbi.univie.ac.at/~raim/odeSolver/} for
  more information on the SBML ODE Solver library.}
\author{ Michael Lawrence }
\seealso{
  \code{\linkS4class{SOSExperiment}} for running a simulation on a
  \code{SOSSubject}.
}
\keyword{classes}
