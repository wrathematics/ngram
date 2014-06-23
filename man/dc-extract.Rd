\name{ngram Getters}

\docType{methods}

\alias{get.ngrams-method}
\alias{get.ngrams,ngram-method}
\alias{get.ngrams}

\alias{get.string-method}
\alias{get.string,ngram-method}
\alias{get.string}

\alias{get.nextwords-method}
\alias{get.nextwords,ngram-method}
\alias{get.nextwords}

\title{ngram Getters}

\description{
  Some simple "getters" for \code{ngram} objects. Necessary since
  the internal representation is not a native R object.
}
\section{Methods}{
\describe{
\item{\code{signature(ng = "ngram")}}{}
}
}
\usage{
\S4method{get.ngrams}{ngram}(ng)

\S4method{get.string}{ngram}(ng)

\S4method{get.nextwords}{ngram}(ng)
}
\arguments{
  \item{ng}{An ngram object.}
}
\details{
  \code{get.ngrams()} returns an R vector of all n-grams.
  
  \code{get.nextwords()} does nothing at the moment; it will be
  implemented in future releases.
  
  \code{getnstring()} recovers the input string as an R string.
}
\examples{
\dontrun{
library(ngram)

str <- "A B A C A B B"
ng <- ngram(str)
get.ngrams(ng)
}
}
\seealso{
  \code{\link{ngram}}
}


