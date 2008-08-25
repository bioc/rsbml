setClass("CompartmentVolumeRule", representation(compartment = "character"), 
  contains = "AssignmentRule")

setMethod("describe", "CompartmentVolumeRule",
          function(object)
          paste("|", compartment(object), "| :=", math(object), sep = ""))

setMethod("compartment", "CompartmentVolumeRule", function(object) object@compartment)

setReplaceMethod("compartment", "CompartmentVolumeRule", function(object, value) {
  object@compartment <- value
  object
})
