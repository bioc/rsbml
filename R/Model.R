setClassUnion("OptionalModelHistory", c("ModelHistory", "NULL"))
setClass("Model",
         representation(id = "character", name = "character",
                        functionDefinitions = "list", unitDefinitions = "list",
                        compartments = "list", species = "list",
                        parameters = "list", rules = "list", reactions = "list",
                        events = "list", layouts = "list",
                        speciesTypes = "list", compartmentTypes = "list",
                        constraints = "list", initialAssignments = "list",
                        modelHistory = "OptionalModelHistory"),
         contains = "SBase")

setMethod("describe", "Model", function(object) {
  descs <- paste("Model of ", id(object), sep = "")
  if (length(name(object)))
    descs <- paste(descs, " (", name(object), ")", sep = "")
  if (!is.null(modelHistory(object)))
    descs <- c(descs, describe(modelHistory(object)))
  descList <- function(name, max = 4) {
    l <- do.call(name, list(object))
    n <- length(l)
    if (n) {
      substring(name, 1, 1) <- toupper(substring(name, 1, 1))
      c("", paste(name, " (", n, "):", sep = ""), describe(l, max))
    } else NULL
  }
  descs <- c(descs,
             descList("compartments"),
             descList("species"),
             descList("reactions"),
             descList("parameters"),
             descList("rules"),
             descList("unitDefinitions"),
             descList("events"),
             descList("initialAssignments"),
             descList("constraints"),
             descList("speciesTypes"),
             descList("compartmentTypes"),
             descList("layouts", NA))
  descs
})

setMethod("id", "Model", function(object) object@id)

 
setMethod("name", "Model", function(object) object@name)

 setGeneric("functionDefinitions", function(object) standardGeneric("functionDefinitions"))
setMethod("functionDefinitions", "Model", function(object) object@functionDefinitions)

 setGeneric("unitDefinitions", function(object) standardGeneric("unitDefinitions"))
setMethod("unitDefinitions", "Model", function(object) object@unitDefinitions)

 setGeneric("compartments", function(object) standardGeneric("compartments"))
setMethod("compartments", "Model", function(object) object@compartments)

setMethod("species", "Model", function(object) object@species)

setMethod("parameters", "Model", function(object) object@parameters)

 setGeneric("rules", function(object) standardGeneric("rules"))
setMethod("rules", "Model", function(object) object@rules)

 setGeneric("reactions", function(object) standardGeneric("reactions"))
setMethod("reactions", "Model", function(object) object@reactions)

 setGeneric("events", function(object) standardGeneric("events"))
setMethod("events", "Model", function(object) object@events)

 setGeneric("layouts", function(object) standardGeneric("layouts"))
setMethod("layouts", "Model", function(object) object@layouts)

 
setReplaceMethod("id", "Model", function(object, value) {
  object@id <- value
  object
})

 
setReplaceMethod("name", "Model", function(object, value) {
  object@name <- value
  object
})

 setGeneric("functionDefinitions<-", function(object, value) standardGeneric("functionDefinitions<-"))
setReplaceMethod("functionDefinitions", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "FunctionDefinition")))
    stop("All functions must be FunctionDefinition objects")
  names(value) <- sapply(value, id)
  object@functionDefinitions <- value
  object
})

 setGeneric("unitDefinitions<-", function(object, value) standardGeneric("unitDefinitions<-"))
setReplaceMethod("unitDefinitions", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "UnitDefinition")))
    stop("All units must be UnitDefinition objects")
  names(value) <- sapply(value, id)
  object@unitDefinitions <- value
  object
})

 setGeneric("compartments<-", function(object, value) standardGeneric("compartments<-"))
setReplaceMethod("compartments", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "Compartment")))
    stop("All compartments must be Compartment objects")
  names(value) <- sapply(value, id)
  object@compartments <- value
  object
})

setReplaceMethod("species", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "Species")))
    stop("All species must be Species objects")
  names(value) <- sapply(value, id)
  object@species <- value
  object
})

setReplaceMethod("parameters", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "Parameter")))
    stop("All parameters must be Parameter objects")
  names(value) <- sapply(value, id)
  object@parameters <- value
  object
})

 setGeneric("rules<-", function(object, value) standardGeneric("rules<-"))
setReplaceMethod("rules", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "Rule")))
    stop("All rules must be Rule objects")
  object@rules <- value
  object
})

 setGeneric("reactions<-", function(object, value) standardGeneric("reactions<-"))
setReplaceMethod("reactions", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "Reaction")))
    stop("All reactions must be Reaction objects")
  names(value) <- sapply(value, id)
  object@reactions <- value
  object
})

 setGeneric("events<-", function(object, value) standardGeneric("events<-"))
setReplaceMethod("events", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "Event")))
    stop("All events must be Event objects")
  names(value) <- sapply(value, id)
  object@events <- value
  object
})

 setGeneric("layouts<-", function(object, value) standardGeneric("layouts<-"))
setReplaceMethod("layouts", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "Layout")))
    stop("All layouts must be Layout objects")
  names(value) <- sapply(value, id)
  object@layouts <- value
  object
})


 setGeneric("compartmentTypes", function(object) standardGeneric("compartmentTypes"))
setMethod("compartmentTypes", "Model", function(object) object@compartmentTypes)

 setGeneric("speciesTypes", function(object) standardGeneric("speciesTypes"))
setMethod("speciesTypes", "Model", function(object) object@speciesTypes)

 setGeneric("compartmentTypes<-", function(object, value) standardGeneric("compartmentTypes<-"))
setReplaceMethod("compartmentTypes", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "CompartmentType")))
    stop("All compartment types must be CompartmentType objects")
  names(value) <- sapply(value, id)
  object@compartmentTypes <- value
  object
})

 setGeneric("speciesTypes<-", function(object, value) standardGeneric("speciesTypes<-"))
setReplaceMethod("speciesTypes", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "SpeciesType")))
    stop("All species types must be SpeciesType objects")
  names(value) <- sapply(value, id)
  object@speciesTypes <- value
  object
})

 setGeneric("constraints", function(object) standardGeneric("constraints"))
setMethod("constraints", "Model", function(object) object@constraints)

 setGeneric("initialAssignments", function(object) standardGeneric("initialAssignments"))
setMethod("initialAssignments", "Model", function(object) object@initialAssignments)

 setGeneric("constraints<-", function(object, value) standardGeneric("constraints<-"))
setReplaceMethod("constraints", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "Constraint")))
    stop("All constraints must be Constraint objects")
  names(value) <- sapply(value, id)
  object@constraints <- value
  object
})

 setGeneric("initialAssignments<-", function(object, value) standardGeneric("initialAssignments<-"))
setReplaceMethod("initialAssignments", "Model", function(object, value) {
  if (!all(sapply(value, inherits, "InitialAssignment")))
    stop("All initial assignments must be InitialAssignment objects")
  object@initialAssignments <- value
  object
})

 setGeneric("modelHistory", function(object) standardGeneric("modelHistory"))
setMethod("modelHistory", "Model", function(object) object@modelHistory)
 setGeneric("modelHistory<-", function(object, value) standardGeneric("modelHistory<-"))
setReplaceMethod("modelHistory", "Model", function(object, value) {
  object@modelHistory <- value
  object
})

setGeneric("stoichiometryMatrix",
           function(object, ...) standardGeneric("stoichiometryMatrix"))

setMethod("stoichiometryMatrix", "Model", function(object) {
  species <- species(object)
  reactions <- reactions(object)
  mat <- matrix(0, length(species), length(reactions),
                dimnames = list(names(species), names(reactions)))
  setStoich <- function(refList, factor) {
    col <- rep(seq_along(reactions), sapply(refList, length))
    refs <- unlist(refList)
    row <- match(sapply(refs, species), names(species))
    ind <- row + (col-1)*length(species)
    mat[ind] <<- mat[ind] + sapply(refs, stoichiometry) * factor
  }
  setStoich(lapply(reactions, reactants), -1)
  setStoich(lapply(reactions, products), 1)
  mat
})
