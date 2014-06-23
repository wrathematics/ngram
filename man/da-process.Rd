\name{Process}
\alias{Process}

\docType{methods}

\alias{ngram-method}
\alias{ngram,character-method}
%\alias{ngram,book-method}
\alias{ngram}

\title{ngram}

\description{
  This routine processes a string into an \code{ngram} class 
  object.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "character")}}{}
%\item{\code{signature(x = "book")}}{}
}
}
\usage{
\S4method{ngram}{character}(x, n=2)
%\S4method{ngram}{book}(x, n=2)
}
\arguments{
  \item{x}{The input text.}
  \item{n}{The 'n' as in 'n-gram'.}
}
\details{
  The \code{ngram()} function is the main workhorse of this package.
  It takes an input string and converts it into the internal n-gram
  representation.
  
  On evaluation, a copy of the input string is produced and stored
  as an external pointer.  This is necessary because the internal 
  list representation just points to the first char of each word 
  in the input string.  So if you (or R's gc) deletes the input
  string, basically all hell breaks loose.
}
\examples{
\dontrun{
library(ngram)

str <- "A B A C A B B"
ng <- ngram(str, n=2)
ng
}
}
\seealso{
  \code{\link{ngram-class}}
}
\keyword{Data Generation}


