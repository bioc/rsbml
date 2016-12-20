#validateSId <- function(sid)
#{
#  tmp <- sub("[A-Za-z_][A-Za-z0-9_]*", "", sid)
#  if (nchar(tmp) > 0)
#    stop("SId '", sid, "' is invalid, SIds must contain only alphanumeric characters ",
#      "plus '_' but must not start with a number")
#  return(TRUE)
#}

setMethod("describe", "list", function(object, max = NA) {
  n <- length(object)
  if (is.na(max))
    cutoff <- n
  else cutoff <- floor(max/2)
  descs <- sapply(object[seq_len(min(n, cutoff))], describe)
  if (n > cutoff) {
    descs <- c(descs, "...")
    descs <- c(descs, sapply(object[seq(cutoff + 1, min(n, max))], describe))
  }
  descs
})

asMath <- function(x) {
    if (is.character(x))
        parse(text=x)
    else as.expression(x)
}
