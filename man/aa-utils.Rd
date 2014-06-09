\name{Utilities}

\docType{methods}

\alias{concat}

\alias{wordcount-method}
\alias{wordcount,character-method}
\alias{wordcount,ngram-method}
\alias{wordcount}

\title{n-gram Utilities}

\description{
  Some utility methods.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "character")}}{}
\item{\code{signature(x = "ngram")}}{}
}
}
\usage{
  concat(str)
\S4method{wordcount}{character}(x)
\S4method{wordcount}{ngram}(x)
}
\arguments{
  \item{x}{The input text.}
  \item{str}{A string or vector of strings.}
}
\details{
  deets.
}
\value{
  \code{concat()} returns 
}
\seealso{
  \code{\link{ngram-class}}
}
\examples{
\dontrun{
library(ngram)

str <- "a b c"
concat(str)
wordcount(str)
}
}

