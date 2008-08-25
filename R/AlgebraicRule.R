setClass("AlgebraicRule", contains = "Rule")

setMethod("describe", "AlgebraicRule",
          function(object) as.character(math(object)))
