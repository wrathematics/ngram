\name{Utilities}
\alias{Utilities}

\docType{methods}

\alias{concat}

\alias{wordcount-method}
\alias{wordcount,character-method}
%\alias{wordcount,book-method}
\alias{wordcount,ngram-method}
\alias{wordcount}

\title{n-gram Utilities}

\description{
  Some utility methods.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "character")}}{}
%\item{\code{signature(x = "book")}}{}
\item{\code{signature(x = "ngram")}}{}
}
}
\usage{
concat(..., collapse="", rm.space=FALSE)

\S4method{wordcount}{character}(x)
\S4method{wordcount}{ngram}(x)
}
\arguments{
  \item{...}{Input text(s).}
  \item{x}{A string or vector of strings.}
  \item{collapse}{A character to separate the input strings if a 
  vector of strings is supplied; otherwisethis does nothing.}
  \item{rm.space}{logical; determines if spaces should be removed
  from the final string.}
}
\details{
  \code{concat()} is a utility for concatenating strings together.
  This is handy because if you want to generate the n-grams for
  several different texts, you must first put them into a single
  string.
  
  \code{wordcount()} counts words.  Currently a "word" is a 
  clustering of characters separated from another clustering of 
  charactersby at least 1 space.  That is the law.
}
\value{
  \code{concat()} returns 
}
\seealso{
  \code{\link{Preprocess}}
}
\examples{
\dontrun{
library(ngram)

words <- c("a", "b", "c")
wordcount(words)
str <- concat(words)
wordcount(str)
}
}
