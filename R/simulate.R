### Simulate an SBML model
### SEE: http://www.biouml.org/biomodels.shtml for competitors
### - BioUML (Java)
### - ByoDyn (Python)
### - SBMLOdeSolver (C) - let's just use this like SBMLodeSolveR

.simulate.SBML <- function(object, nsim = 10, seed,
                           times = tail(seq(0, by = timeStep,
                             length.out = nsim + 1), -1),
                           design = new("SOSDesign"),
                           timeStep = 1, indefinite = FALSE,
                           atol = 1e-18, rtol = 1e-10, 
                           maxStep = 10000,
                           odeMethod = c("bdf", "adams-moulton"), maxOrder = 5,
                           iterMethod = c("newton", "functional"),
                           sensMethod = c("none", "simultaneous", "staggered",
                             "staggered1"),
                           useJacobian = TRUE, haltOnEvent = FALSE,
                           haltOnSteadyState = FALSE, storeResults = TRUE)
{
  formParams <- formals(sys.function())
  odeMethod <- odeMethod[1]
  odeMethod <- match(match.arg(odeMethod), eval(formParams$odeMethod)) - 1
  iterMethod <- iterMethod[1]
  iterMethod <- match(match.arg(iterMethod), eval(formParams$iterMethod)) - 1
  sensMethod <- sensMethod[1]
  sensMethod <- match(match.arg(sensMethod), eval(formParams$sensMethod)) - 2
  sensitivity <- sensMethod >= 0
  ids <- colnames(design)
  if (!is(design, "SOSDesign"))
    rids <- character(ncol(design))
  rids <- reactions(design)
  rids[is.na(rids)] <- ""
  res <- .Call("rsbml_R_SBML_odeSolver", object, as.numeric(times),
               as.numeric(atol), as.numeric(rtol), as.numeric(timeStep),
               as.integer(indefinite), as.integer(maxStep),
               as.integer(odeMethod), as.integer(maxOrder),
               as.integer(iterMethod), as.integer(sensMethod),
               as.integer(sensitivity), as.integer(useJacobian),
               as.integer(haltOnEvent), as.integer(haltOnSteadyState),
               as.integer(storeResults), as.character(ids), as.character(rids),
               as.matrix(t(design)))
  ## simplify the result a bit up front
  if (!ncol(design)) {
    res <- list(res)
  }
  res <- lapply(res, function(r) do.call("rbind", r))
  ## our result will be a data.frame with columns:
  ## entity types and entity names
  model <- model(rsbml_dom(object))
  comp <- compartments(model)
  comp <- names(comp)[!sapply(comp, constant)]
  parm <- parameters(model)
  parm <- names(parm)[!sapply(parm, constant)]
  ids <- list(names(species(model)), comp, parm, names(reactions(model)))
  types <- c("species", "compartments", "parameters", "reactions")
  types <- rep(types, sapply(ids, length))
  ids <- unlist(ids)
  ## times
  ncols <- rapply(res, ncol)
  if (indefinite)
    times <- lapply(ncols, function(nc) seq(0, nc, by = timeStep))
  else times <- lapply(ncols, function(nc) head(c(0, times), nc))
  times <- rep(unlist(times), each = length(ids))
  ## value
  result <- data.frame(type = types, id = ids, time = unlist(times),
                       value = unlist(res))
  ## design parameter names and values
  ## if design provided, we have a list with an element for each trial
  if (ncol(design)) {
    sample <- rep(seq_len(ncol(design)), ncols*length(ids))
    if (!is.null(rownames(design)))
      sample <- rownames(design)[sample]
    result <- cbind(sample = sample, result)
  }
### TODO: sensitivities
  ## bundle everyhing in an SOSExperiment
  mc <- match.call()
  slots <- as.list(mc)[names(mc) %in% slotNames("SOSProtocol")]
  protocol <- do.call("new", c(list("SOSProtocol"), slots))
  result <- new("SOSResult", data = result)
  new("SOSExperiment", subject = new("SOSSubject", model), design = design,
      protocol = protocol, result = result)
}

## Abstract, self-contained data structure for an experiment

setClass("ExperimentProtocol")
setClass("ExperimentDesign")
setClass("ExperimentSubject")
setClass("ExperimentResult")

setClass("Experiment",
         representation(protocol = "ExperimentProtocol",
                        design = "ExperimentDesign",
                        subject = "ExperimentSubject",
                        result = "ExperimentResult"),
         contains = "VIRTUAL")

setGeneric("protocol", function(object, ...) standardGeneric("protocol"))
setMethod("protocol", "Experiment", function(object) object@protocol)

setGeneric("protocol<-", function(object, value) standardGeneric("protocol<-"))
setReplaceMethod("protocol", "Experiment", function(object, value) {
  object@protocol <- value
  object
})

setGeneric("design", function(object, ...) standardGeneric("design"))
setMethod("design", "Experiment", function(object) object@design)

setGeneric("design<-", function(object, value) standardGeneric("design<-"))
setReplaceMethod("design", "Experiment", function(object, value) {
  object@design <- value
  object
})

setGeneric("subject", function(object, ...) standardGeneric("subject"))
setMethod("subject", "Experiment", function(object) object@subject)

setGeneric("subject<-", function(object, value) standardGeneric("subject<-"))
setReplaceMethod("subject", "Experiment", function(object, value) {
  object@subject <- value
  object
})

setGeneric("result", function(object, ...) standardGeneric("result"))
setMethod("result", "Experiment", function(object) object@result)

setGeneric("result<-", function(object, value) standardGeneric("result<-"))
setReplaceMethod("result", "Experiment", function(object, value) {
  object@result <- value
  object
})

## (S)BML(O)DE(S)olver experiment implementation for SBML models

setClass("SOSProtocol",
         representation(times = "numeric", timeStep = "numeric",
                        indefinite = "logical",
                        atol = "numeric", rtol = "numeric",
                        maxStep = "numeric", odeMethod = "character",
                        iterMethod = "character", maxOrder = "numeric",
                        sensMethod = "character", haltOnEvent = "logical",
                        haltOnSteadyState = "logical", useJacobian = "logical",
                        storeResults = "logical"),
         tail(formals(.simulate.SBML), -5),
         "ExperimentProtocol")

setClass("SOSDesign",
         representation(reactions = "character"),
         contains = c("matrix", "ExperimentDesign"))

setMethod("reactions", "SOSDesign", function(object) object@reactions)
setReplaceMethod("reactions", "Experiment", function(object, value) {
  object@reactions <- value
  object
})

setClass("SOSSubject", contains = c("ExperimentSubject", "Model"))

setClass("SOSResult", representation(data = "data.frame", sens = "matrix"),
         contains = "ExperimentResult")

## subset by:
##   entity type: species(), compartment(), parameters(), reactions()
##   entity name, design point: [name, dp]

setMethod("species", "SOSResult", function(object)
          object[object@data$type == "species",])
setMethod("compartments", "SOSResult", function(object)
          object[object@data$type == "compartments",])
setMethod("parameters", "SOSResult", function(object)
          object[object@data$type == "parameters",])
setMethod("reactions", "SOSResult", function(object)
          object[object@data$type == "reactions",])

## shapes:
##   time series (time variable, variable for each entityXdp)
##   experimental (variable for each timeXdp)
## 

setGeneric("as.ts", function(x, ...) standardGeneric("as.ts"))

setMethod("as.ts", "SOSResult",
          function(x)
          {
            data <- x@data
            tdata <- do.call("cbind", split(data$value, data$id))
            ts(tdata, 0, max(data$time))
          })

setClass("SOSExperiment",
         representation(protocol = "SOSProtocol",
                        design = "SOSDesign",
                        subject = "SOSSubject",
                        result = "SOSResult"),
         contains = "Experiment")

setGeneric("simulate",
           function(object, nsim = 1, seed = NULL, ...)
           standardGeneric("simulate"))

setMethod("simulate", "SOSExperiment",
          function(object, nsim = 10, seed, ...)
          {
            ## break everything down and pass to SBMLDocument method
            proto <- protocol(object)
            protoParms <- lapply(slotNames(proto), function(s) slot(proto, s))
            names(protoParms) <- slotNames(proto)
            doc <- rsbml_doc(subject(object))
            args <- c(list(doc, nsim, design = design(object)),
                      protoParms)
            exp <- do.call("simulate", args)
            ## store result in our experiment (preserves rest of object)
            result(object) <- result(exp)
            object
          })

setMethod("simulate", "SBMLDocument", .simulate.SBML)

setMethod("simulate", "SBML",
          function(object, nsim, seed, ...)
          simulate(rsbml_doc(object), nsim, seed, ...))

setMethod("simulate", "Model",
          function(object, nsim, seed, ...)
          simulate(new("SBML", model = object), nsim, seed, ...))

### Attempt at simulating in R
### Provide a wrapper around lsoda conforming to stats::simulate
### FIXME: may need to move to Rsundials for algebraic support
if (FALSE)
setMethod("simulate", "Model",
          function(object, nsim, seed, times = seq_len(nsim), ...)
          {
            ## extract pieces of the model
            s <- species(object)
            bs <- sapply(s, boundaryCondition)
            cs <- sapply(s, constant)
            r <- reactions(object)
            p <- parameters(object)
            comp <- compartments(object)
            
            ## construct the model environment
### TODO: need to consider InitialAssignments here
            modelEnv <- new.env(parent = empty.env())
            assignParameter <- function(parameter, env) {
              assign(id(parameter), value(parameter), env)
            }
            assignSpecies <- function(species, env) {
              val <- initialAmount(species)
              if (!length(val)) {
                conc <- initialConcentration(species)
                val <- conc*size(comp[[compartment(species)]])
                attr(val, "conc") <- conc
                val
              }
              if (!length(val))
                val <- NA
              assign(id(species), val, env)
            }
            lapply(p, assignParameter, modelEnv)
            lapply(s, assignSpecies, modelEnv)

            ## setup kineticLaws
            makeLawEnv <- function(law) {
              lawEnv <- new.env(parent = modelEnv)
              lapply(parameters(law), assignParameter, lawEnv)
              lawEnv
            }
            laws <- sapply(r, kineticLaw)
            hasLaw <- sapply(laws, is.null)
            lawEnvs <- vector("list", length(r))
            lawEnvs[hasLaw] <- sapply(laws[hasLaw], makeLawEnv)
            lawMaths <- vector("list", length(r))
            lawMaths[hasLaw] <- sapply(laws[hasLaw], math)
            
            v <- rep(NA, length(r))
            
            fderiv <- function(t, X, p) {
              ## 'y' contains levels for non-constant, non-boundary species
              ## 'aux' includes everything else:
              ##  boundary species, compartment sizes, reaction rates, parameters
### TODO: process AssignmentRules (boundaries, sizes, parameters)
### TODO: RateRules will need their targets in X
### TODO: handle events
### TODO: need to multiply species concentrations by compartment size
### TODO: we do not handle 'fast' reactions yet
              v[hasLaw] <- mapply(lawMaths[hasLaw], lawEnvs[hasLaw], eval)
              y <- stoich%*%v
              list(y, aux)
            }
            lsoda(X0, times, fderiv, list(), ...)
          })
