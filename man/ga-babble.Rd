\name{Babble}

\docType{methods}

\alias{babble-method}
\alias{babble,ngram-method}
\alias{babble}

\title{ngram Getters}

\description{
  A markov chain babbler.
}
\section{Methods}{
\describe{
\item{\code{signature(ng = "ngram")}}{}
}
}
\usage{
\S4method{babble}{ngram}(ng, genlen=150, seed=getseed())
}
\arguments{
  \item{ng}{An ngram object.}
  \item{genlen}{Generated length, i.e., the number of words to
  babble.}
  \item{seed}{Seed for the random number generator.}
}
\details{
  The babbler uses its own internal PRNG (i.e., not R's), so seeds
  cannot be managed as with R's seeds.  The generator is an 
  implementation of MT19937.
}
\seealso{
  \code{\link{ngram}}
}
\examples{
\dontrun{
library(ngram)

str <- "A B A C A B B"
ng <- ngram(str)
babble(ng, genlen=5, seed=1234)
}
}
