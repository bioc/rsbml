\name{Model-class}
\docType{class}
\alias{Model-class}
\alias{compartments,Model-method}
\alias{compartments}
\alias{compartments<-,Model-method}
\alias{compartments<-}
\alias{events,Model-method}
\alias{events}
\alias{events<-,Model-method}
\alias{events<-}
\alias{functionDefinitions,Model-method}
\alias{functionDefinitions}
\alias{functionDefinitions<-,Model-method}
\alias{functionDefinitions<-}
\alias{layouts,Model-method}
\alias{layouts}
\alias{layouts<-,Model-method}
\alias{layouts<-}
\alias{parameters,Model-method}
\alias{parameters}
\alias{parameters<-,Model-method}
\alias{parameters<-}
\alias{reactions,Model-method}
\alias{reactions}
\alias{reactions<-,Model-method}
\alias{reactions<-}
\alias{rules,Model-method}
\alias{rules}
\alias{rules<-,Model-method}
\alias{rules<-}
\alias{unitDefinitions,Model-method}
\alias{unitDefinitions}
\alias{unitDefinitions<-,Model-method}
\alias{unitDefinitions<-}
\alias{compartmentTypes}
\alias{compartmentTypes<-}
\alias{constraints}
\alias{constraints<-}
\alias{initialAssignments}
\alias{initialAssignments<-}
\alias{speciesTypes}
\alias{speciesTypes<-}
\alias{id,Model-method}
\alias{id<-,Model-method}
\alias{name,Model-method}
\alias{name<-,Model-method}
\alias{species,Model-method}
\alias{species<-,Model-method}
\alias{speciesTypes,Model-method}
\alias{speciesTypes<-,Model-method}
\alias{compartmentTypes,Model-method}
\alias{compartmentTypes<-,Model-method}
\alias{constraints,Model-method}
\alias{constraints<-,Model-method}
\alias{initialAssignments,Model-method}
\alias{initialAssignments<-,Model-method}
\alias{modelHistory}
\alias{modelHistory,Model-method}
\alias{modelHistory<-}
\alias{modelHistory<-,Model-method}
\alias{stoichiometryMatrix}
\alias{stoichiometryMatrix,Model-method}


\title{SBML type "Model"}
\description{The central SBML element. Contains the \code{\linkS4class{Species}},
\code{\linkS4class{Reaction}}s, \code{\linkS4class{Compartment}}s and other
components of the model. See the SBML specification, at the reference, for
further details.}
\section{Instantiation}{
Objects can be created by calls of the form \code{new("Model", ...)}.
}
\section{Slots}{
	 \describe{
    \item{\code{id}:}{Object of class \code{"character"} uniquely identifying this component. }
    \item{\code{name}:}{Object of class \code{"character"} naming this component. }
    \item{\code{functionDefinitions}:}{Object of class \code{"list"} containing
      \code{\linkS4class{FunctionDefinition}}s.}
    \item{\code{unitDefinitions}:}{Object of class \code{"list"} containing
      \code{\linkS4class{UnitDefinition}}s. }
    \item{\code{compartments}:}{Object of class \code{"list"} containing
      \code{\linkS4class{Compartment}}s. }
    \item{\code{species}:}{Object of class \code{"list"} containing
      \code{\linkS4class{Species}}s. }
    \item{\code{parameters}:}{Object of class \code{"list"} containing
      \code{\linkS4class{Parameter}}s. }
    \item{\code{rules}:}{Object of class \code{"list"} containing
      \code{\linkS4class{Rule}}s. }
    \item{\code{reactions}:}{Object of class \code{"list"} containing
      \code{\linkS4class{Reaction}}s. }
    \item{\code{events}:}{Object of class \code{"list"} containing
    \code{\linkS4class{Event}}s. }
    \item{\code{layouts}:}{Object of class \code{"list"} containing
    \code{\linkS4class{Layout}}s. }
    \item{\code{speciesTypes}:}{Object of class \code{"list"} containing
      \code{\linkS4class{SpeciesType}}s.}
    \item{\code{compartmentTypes}:}{Object of class \code{"list"} containing
      \code{\linkS4class{CompartmentType}}s.}
    \item{\code{constraints}:}{Object of class \code{"list"} containing
      \code{\linkS4class{Constraint}}s.}
    \item{\code{initialAssignments}:}{Object of class \code{"list"} containing
      \code{\linkS4class{InitialAssignment}}s.}
    \item{\code{modelHistory}:}{Object of class
      \code{\linkS4class{ModelHistory}} recording the history of the
      model.}
    \item{\code{metaId}:}{Object of class \code{"character"} that is an XML ID
      "described" by an RDF resource. This links an SBML element to an RDF
      resource. RDF may appear anywhere in an SBML element,
      but is usually placed inside the \code{annotation} element.}
    \item{\code{notes}:}{Object of class \code{"character"} 
      containing user-readable XHTML notes about an element. }
    \item{\code{annotation}:}{Object of class \code{"character"} containing
      additional machine-readable information about an element, usually as RDF,
      such as BioPAX. This is where application-specific data belongs.}
    \item{\code{cvTerms}:}{Object of class \code{"list"} containing
      instances of \code{\linkS4class{CVTerm}} associated with this
      element.}
    \item{\code{sboTerm}:}{Object of class \code{"integer"} identifying
      a term in the Systems Biology Ontology (SBO).}
  }
}
\section{Extends}{
Class \code{"\linkS4class{SBase}"}, directly.
}
\section{Methods}{
  \describe{
    \item{id}{\code{signature(object = "Model")}: gets the \code{id} slot }
    \item{id<-}{\code{signature(object = "Model")}: sets the \code{id} slot }
    \item{name}{\code{signature(object = "Model")}: gets the \code{name} slot }
    \item{name<-}{\code{signature(object = "Model")}: sets the \code{name} slot }
    \item{compartments}{\code{signature(object = "Model")}: gets the \code{compartments} slot }
    \item{compartments<-}{\code{signature(object = "Model")}: sets the \code{compartments} slot }
    \item{events}{\code{signature(object = "Model")}: gets the \code{events} slot }
    \item{events<-}{\code{signature(object = "Model")}: sets the \code{events} slot }
    \item{functionDefinitions}{\code{signature(object = "Model")}: gets the \code{functionDefinitions} slot }
    \item{functionDefinitions<-}{\code{signature(object = "Model")}: sets the \code{functionDefinitions} slot }
    \item{layouts}{\code{signature(object = "Model")}: gets the \code{layouts} slot }
    \item{layouts<-}{\code{signature(object = "Model")}: sets the \code{layouts} slot }
    \item{parameters}{\code{signature(object = "Model")}: gets the \code{parameters} slot }
    \item{parameters<-}{\code{signature(object = "Model")}: sets the \code{parameters} slot }
    \item{species}{\code{signature(object = "Model")}: gets the \code{species} slot }
    \item{species<-}{\code{signature(object = "Model")}: sets the \code{species} slot }
    \item{reactions}{\code{signature(object = "Model")}: gets the \code{reactions} slot }
    \item{reactions<-}{\code{signature(object = "Model")}: sets the \code{reactions} slot }
    \item{rules}{\code{signature(object = "Model")}: gets the \code{rules} slot }
    \item{rules<-}{\code{signature(object = "Model")}: sets the \code{rules} slot }
    \item{unitDefinitions}{\code{signature(object = "Model")}: gets the \code{unitDefinitions} slot }
    \item{unitDefinitions<-}{\code{signature(object = "Model")}: sets the \code{unitDefinitions} slot }
    \item{compartmentTypes}{\code{signature(object = "Model")}: gets the \code{compartmentTypes} slot }
    \item{compartmentTypes<-}{\code{signature(object = "Model")}: sets the \code{compartmentTypes} slot }
    \item{constraints}{\code{signature(object = "Model")}: gets the \code{constraints} slot }
    \item{constraints<-}{\code{signature(object = "Model")}: sets the \code{constraints} slot }
    \item{initialAssignments}{\code{signature(object = "Model")}: gets the \code{initialAssignments} slot }
    \item{initialAssignments<-}{\code{signature(object = "Model")}: sets the \code{initialAssignments} slot }
    \item{speciesTypes}{\code{signature(object = "Model")}: gets the \code{speciesTypes} slot }
    \item{speciesTypes<-}{\code{signature(object = "Model")}: sets the
      \code{speciesTypes}slot }
    \item{modelHistory}{\code{signature(object = "Model")}: gets the \code{modelHistory} slot }
    \item{modelHistory<-}{\code{signature(object = "Model")}: sets the \code{modelHistory} slot }
    \item{stoichiometryMatrix}{\code{signature(object = "Model")}:
    calculates the stoichiometry matrix of the model }
  }
  
}
\references{\url{http://sbml.org/documents/}}
\author{Michael Lawrence}
\keyword{classes}
