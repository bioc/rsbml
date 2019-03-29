setClass("LineSegment", representation(start = "Point", end = "Point"), contains = "SBase")

setMethod("describe", "LineSegment",
          function(object) paste(describe(start), "to", describe(end)))

setMethod("start", "LineSegment", function(x, ...) x@start)

setMethod("end", "LineSegment", function(x, ...) x@end)

setReplaceMethod("start", "LineSegment", function(x, value) {
  object@start <- value
  object
})

setReplaceMethod("end", "LineSegment", function(x, value) {
  x@end <- value
  object
})

