\alias{rsbml_read}
\name{SBML import}
\title{Read in an SBML file (start here)}
\description{Read an SBML file into R.}
\usage{rsbml_read(filename, text, dom = TRUE, strict = FALSE, schema = FALSE)}
\arguments{
  \item{filename}{the name of the SBML file to parse}
  \item{text}{a string of SBML text to parse (instead of file)}
  \item{dom}{whether to convert directly to the S4 DOM (\code{TRUE}, the
    default) or leave as the internal \code{\linkS4class{SBMLDocument}}.}
  \item{strict}{whether to report warnings in addition to
    errors or not (\code{FALSE}, the default).}
  \item{schema}{whether to perform XML schema validation}
}
\value{a \code{\linkS4class{SBML}} object, or a
  \code{\linkS4class{SBMLDocument}} if \code{dom} is \code{FALSE}.}
\examples{
  # Read an SBML file
  file <- system.file("sbml", "GlycolysisLayout.xml", package = "rsbml")
  doc <- rsbml_read(file)
  
  # Read an SBML string
  string <- paste(readLines(file),collapse="\n")
  doc <- rsbml_read(text = string)
}
\author{Michael Lawrence}
\keyword{IO}
