% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/wordcount.r
\name{wordcount}
\alias{wordcount}
\alias{wordcount.character}
\alias{wordcount.ngram}
\title{wordcount}
\usage{
wordcount(x, sep = " ", count_fun = sum)

\method{wordcount}{character}(x, sep = " ", count_fun = sum)

\method{wordcount}{ngram}(x, sep = " ", count_fun = sum)
}
\arguments{
\item{x}{A string or vector of strings, or an ngram object.}

\item{sep}{The characters used to separate words.}

\item{count_fun}{The function to use for aggregation if \code{x} has length greater than 1.
Useful ones include \code{sum} and \code{identity}.}
}
\value{
A count.
}
\description{
\code{wordcount()} counts words.  Currently a "word" is a clustering of
characters separated from another clustering of charactersby at least 1
space.  That is the law.
}
\examples{
library(ngram)

words = c("a", "b", "c")
words
wordcount(words)

str = concatenate(words, collapse="")
str
wordcount(str)

}
\seealso{
\code{\link{preprocess}}
}
\keyword{Summarize}
