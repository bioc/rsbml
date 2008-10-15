\name{SOSProtocol-class}
\docType{class}
\alias{SOSProtocol-class}

\title{SOSProtocol}
\description{Holds the parameters controlling the execution
  of the simulation using the SBML ODE Solver library.}
\section{Objects from the Class}{
  Objects can be created by calls of the form \code{new("SOSProtocol",
    ...)}. Each argument in \code{...} should correspond to one of the
  slots described below.
}
\section{Slots}{
  \describe{
    \item{\code{times}:}{A \code{"numeric"} vector indicating the
      time points at which to evaluate the model. Defaults to
      \code{tail(seq(0, by = timeStep, length.out = nsim + 1),
        -1)}. The model is always evaluated at t = 0. This slot is
      ignored when \code{indefinite} (below) is \code{TRUE}.}
    \item{\code{timeStep}:}{A scalar \code{"numeric"} value, giving the
      length in time between model evaluations. This is used when
      calculating the default value of \code{times}, above, but is
      otherwise only relevant when the \code{indefinite} slot, below, is
      \code{TRUE}. Defaults to 1.}
    \item{\code{indefinite}:}{A scalar \code{"logical"}, indicating
      whether the simulation should run indefinitely, i.e. until one of
      the stopping conditions is met. See \code{haltOnEvent} and
      \code{haltOnSteadyState} below. Defaults to \code{FALSE}.}
    \item{\code{atol}:}{Scalar \code{"numeric"}, the absolute
      tolerance in integration error. Defaults to \code{1e-18}.}
    \item{\code{rtol}:}{Scalar \code{"numeric"}, the relative tolerance
      in integration error. Defaults to \code{1e-10}.}
    \item{\code{maxStep}:}{Sclar \code{"numeric"}, the maximum number of
      steps for integration. Not to be confused with \code{timeStep}, etc,
      above, which control the simulation time points. Defaults to
      \code{10000}.}
    \item{\code{odeMethod}:}{Scalar \code{"character"} naming the
      method for solving ODEs. Either \code{"bdf"} (the default) or
      \code{"adams-moulton"}.}
    \item{\code{iterMethod}:}{Scalar \code{"character"}, naming the
      iteration method used by the ODE solver, either \code{"newton"}
      (the default) or \code{"functional"}. }
    \item{\code{maxOrder}:}{Scalar \code{"numeric"} indicating maximum
      order for the ODE solver. Defaults to \code{5}.}
    \item{\code{sensMethod}:}{Scalar \code{"character"} naming the
      method for sensitivity analysis. One of \code{"none"} (the
      default and currently the only valid option),
      \code{"simultaneous"}, \code{"staggered"} or \code{"staggered1"}.}
    \item{\code{haltOnEvent}:}{Scalar \code{"logical"} indicating
      whether the simulation should halt when the model emits an
      \code{\linkS4class{Event}}. This allows the model to stop the
      simulation when some state is reached. Defaults to \code{FALSE}.}
    \item{\code{haltOnSteadyState}:}{Scalar \code{"logical"}, indicating
      whether to halt when a steady state is detected. Defaults to
      \code{FALSE}.}
    \item{\code{useJacobian}:}{Scalar \code{"logical"} indicating
      whether to use Jacobian ASTs (\code{TRUE}, the default) or the
      internal approximation in the CVODES library.}
    \item{\code{storeResults}:}{Scalar \code{"logical"} indicating
      whether to store the entire time course (\code{TRUE}, the default)
      or just the last time point. Just for performance.}
  }
}
\section{Extends}{
Class \code{"\linkS4class{ExperimentProtocol}"}, directly.
}
\section{Methods}{
No methods defined with class "SOSProtocol" in the signature.
}
\references{ See \url{http://www.tbi.univie.ac.at/~raim/odeSolver/} for
  more information on the SBML ODE Solver library. }
\author{ Michael Lawrence }
\details{
  Most users will probably set only the \code{times} slot, either
  directly or through the \code{timeStep} slot and the \code{nsim}
  parameter to \code{\link{simulate}}.
}
\seealso{
  The \code{\linkS4class{SOSExperiment}} class, which contains
  a \code{SOSProtocol} instance, for setting up and running a simulation.
}
\keyword{classes}
