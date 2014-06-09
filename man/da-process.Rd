\name{Process}
\alias{Process}

\docType{methods}

\alias{ngram-method}
\alias{ngram,character-method}
\alias{ngram,book-method}
\alias{ngram}

\title{ngram}

\description{
  This routine processes a string into an \code{ngram} class 
  object.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "character")}}{}
\item{\code{signature(x = "book")}}{}
}
}
\usage{
\S4method{ngram}{character}(x, n=2)
\S4method{ngram}{book}(x, n=2)
}
\arguments{
  \item{x}{The input text.}
  \item{n}{The 'n' as in 'n-gram'.}
}
\details{
  deets.
}
\value{
  something
}
\seealso{
  \code{\link{ngram}}
}
\keyword{Data Generation}


