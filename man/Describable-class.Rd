\name{describe}
\alias{Describable-class}
\alias{show,Describable-method}
\alias{describe}
\alias{describe-methods}
\alias{describe,AlgebraicRule-method}
\alias{describe,AssignmentRule-method}
\alias{describe,BoundingBox-method}
\alias{describe,CVTerm-method}
\alias{describe,Compartment-method}
\alias{describe,CompartmentGlyph-method}
\alias{describe,CompartmentType-method}
\alias{describe,CompartmentVolumeRule-method}
\alias{describe,Constraint-method}
\alias{describe,CubicBezier-method}
\alias{describe,Curve-method}
\alias{describe,Delay-method}
\alias{describe,Dimensions-method}
\alias{describe,Event-method}
\alias{describe,EventAssignment-method}
\alias{describe,FunctionDefinition-method}
\alias{describe,GraphicalObject-method}
\alias{describe,InitialAssignment-method}
\alias{describe,KineticLaw-method}
\alias{describe,Layout-method}
\alias{describe,LineSegment-method}
\alias{describe,Model-method}
\alias{describe,ModelCreator-method}
\alias{describe,ModelHistory-method}
\alias{describe,Parameter-method}
\alias{describe,ParameterRule-method}
\alias{describe,Point-method}
\alias{describe,RateRule-method}
\alias{describe,Reaction-method}
\alias{describe,ReactionGlyph-method}
\alias{describe,SBML-method}
\alias{describe,SimpleSpeciesReference-method}
\alias{describe,Species-method}
\alias{describe,SpeciesConcentrationRule-method}
\alias{describe,SpeciesGlyph-method}
\alias{describe,SpeciesReference-method}
\alias{describe,SpeciesReferenceGlyph-method}
\alias{describe,SpeciesType-method}
\alias{describe,StoichiometryMath-method}
\alias{describe,TextGlyph-method}
\alias{describe,Trigger-method}
\alias{describe,Unit-method}
\alias{describe,UnitDefinition-method}
\alias{describe,list-method}

\title{Describing objects}
\description{Each class in the SBML DOM extends the \code{Describable}
  class and thus has a \code{describe} method, which
  describes an object with a short string. This is used by the
  \code{show} method to output terse textual representations of the DOM.
}
\section{Describable objects}{An object that extends
  \code{Describable} has a method for the \code{\link{describe}}
  generic, and by default \code{Describable} objects are \code{show}n by
  printing the output of \code{describe}. Note that \code{Describable}
  is a virtual tag class, no objects may be
  created from it.}
\section{Describable methods}{
  \describe{
    \item{show}{\code{signature(object = "Describable")}: outputs the
      return value of \code{describe}. }
  }
}
\usage{
  describe(object, ...)
}
\arguments{
  \item{object}{The object to be described.}
  \item{...}{Additional arguments for methods.}
}
\value{A short textual (string) representation of \code{object}.}
\author{Michael Lawrence}
\keyword{classes}
