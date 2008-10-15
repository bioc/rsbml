\name{SOSDesign-class}
\docType{class}
\alias{SOSDesign-class}
\alias{reactions,SOSDesign-method}
\alias{reactions<-,SOSDesign-method}

\title{SOSDesign}
\description{Specifies the reaction names and their parameter settings
  for each run in a batch experiment. It extends \code{matrix}; each column
  corresponds to a parameter in the model and each row should hold the
  parameter settings for one run of the experiment.}
\section{Objects from the Class}{
  Objects can be created by calls of the form \code{new("SOSDesign", data,
    nrow, ncol, byrow, dimnames, ...)}. This is the same as initializing a
  \code{\link{matrix}}.
}
\section{Slots}{
  \describe{
    \item{\code{.Data}:}{Object of class \code{"matrix"}, holding the
      parameter settings. }
    \item{\code{reactions}:}{Object of class \code{"character"} of
      length the number of columns, holding the reaction IDs for
      parameters local to a reaction (i.e. \code{\linkS4class{KineticLaw}}
      \code{\linkS4class{Parameter}}s). For global parameters, the
      corresponding value should be the empty string.}
  }
}
\section{Extends}{
Class \code{"\linkS4class{matrix}"}, from data part.
Class \code{"\linkS4class{ExperimentDesign}"}, directly.
Class \code{"\linkS4class{array}"}, by class "matrix", distance 2.
Class \code{"\linkS4class{structure}"}, by class "matrix", distance 3.
Class \code{"\linkS4class{vector}"}, by class "matrix", distance 4, with explicit coerce.
}
\section{Methods}{
  \describe{
    \item{reactions}{\code{signature(object = "SOSDesign")}: gets the
      \code{reactions} slot. }
    \item{reactions<-}{\code{signature(object = "SOSDesign")}: sets the
      \code{reactions} slot.}
  }
}
\references{ See \url{http://www.tbi.univie.ac.at/~raim/odeSolver/} for
  more information on the SBML ODE Solver library. }
\author{ Michael Lawrence }
\details{
  It is often desirable to explore the state space of a model by
  adjusting its initial parameter settings. One could do this by
  modifying the model itself for each experiment, but this class aims to
  provide a more convenient and systematic means of running experiments
  in batch, over a range of parameter settings. The results of the
  experiment will then contain the output from each run, which may then
  be compared.
  
  The design is specified as a matrix, and each column in the matrix
  should correspond to a parameter defined in an SBML 
  model. The column names should identify the parameters. These are not
  to be confused with the simulation parameters 
  specified in \code{\linkS4class{SOSProtocol}}, which control how the
  simulation is executed. These should be and are designed to be kept
  constant across the runs.

  There are two different types of parameters: global and local
  (reaction) parameters. Global parameters may correspond to a
  \code{\linkS4class{Species}} quantity,
  \code{\linkS4class{Compartment}} size, or model-level
  \code{\linkS4class{Parameter}} value. These should be identified in
  the column names by the \code{id} of the corresponding SBML
  element. The element in the \code{reactions} slot for one of these
  parameters should be the empty string.

  The second type of parameter specifies the value of a
  \code{Parameter} element within the \code{\linkS4class{KineticLaw}} of a
  reaction. These should be named by the \code{id} of the
  \code{Parameter}. They also should be namespaced by the
  containing \code{Reaction} \code{id}, which is stored in the
  corresponding element of the \code{reactions} slot. 
}

\seealso{
  \code{\linkS4class{SOSExperiment}}, the container of this class, for
  configuring and running a simulation.
}
\keyword{classes}
