setClass("Dimensions", representation(width = "numeric", 
  height = "numeric", depth = "numeric"), prototype = list(depth = 0), contains = "SBase")

setMethod("describe", "Dimensions", function(object) {
  paste(width(object), height(object), depth(object), sep = "x")
})

setMethod("width", "Dimensions", function(x) x@width)

 setGeneric("height", function(object) standardGeneric("height"))
setMethod("height", "Dimensions", function(object) object@height)

 setGeneric("depth", function(object) standardGeneric("depth"))
setMethod("depth", "Dimensions", function(object) object@depth)

setReplaceMethod("width", "Dimensions", function(x, value) {
  x@width <- value
  x
})

 setGeneric("height<-", function(object, value) standardGeneric("height<-"))
setReplaceMethod("height", "Dimensions", function(object, value) {
  object@height <- value
  object
})

 setGeneric("depth<-", function(object, value) standardGeneric("depth<-"))
setReplaceMethod("depth", "Dimensions", function(object, value) {
  object@depth <- value
  object
})

