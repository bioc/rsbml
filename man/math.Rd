\name{math}
\alias{acot}
\alias{acoth}
\alias{acsc}
\alias{acsch}
\alias{asec}
\alias{asech}
\alias{cot}
\alias{coth}
\alias{csc}
\alias{csch}
\alias{sec}
\alias{sech}

\title{ MathML Utilities }
\description{
  Each of these functions implements a trigonometry function found in the
  MathML specification but not found in base R. These are all simple
  wrappers around existing R trig functions.
}
\usage{
acot(x)
acoth(x)
acsc(x)
acsch(x)
asec(x)
asech(x)
cot(x)
coth(x)
csc(x)
csch(x)
sec(x)
sech(x)
}
\arguments{
  \item{x}{The \code{numeric} value(s) for the trigonometry operation}
}
\value{
  A \code{numeric} vector, the same length as \code{x}.
}
\author{ Michael Lawrence }
\keyword{math}