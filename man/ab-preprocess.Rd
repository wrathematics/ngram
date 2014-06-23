\name{Preprocess}
\alias{Preprocess}

\alias{preprocess}

\title{Preprocessing}

\description{
  A simple text preprocessor for use with the \code{ngram()} function.
}
\usage{
preprocess(x, case=NULL, split.at.punct=FALSE)
}
\arguments{
  \item{x}{Input text.}
  \item{case}{Option to change the case of the text. See Details 
  section for appropriate values.}
  \item{split.at.punct}{logical; determines if spaces should be 
  inserted before and after punctuation (making them individual
  characters for an n-gram model).}
}
\details{
  The input text \code{x} must already be in the correct form for 
  \code{ngram()}, i.e., a single string (character vector of length 1).
  
  The \code{case} argument can take 3 possible values: \code{NULL}, 
  in which case nothing is done, or \code{lower} or \code{upper}, 
  wherein the case of the input text will be made lower/upper case,
  repesctively.
}
\value{
  \code{concat()} returns 
}
\seealso{
  \code{\link{Process}, \link{Utilities}}
}
\examples{
\dontrun{
library(ngram)

x <- "Watch  out    for snakes!  "
preprocess(x)
preprocess(x, case="upper", split.at.punct=TRUE)
}
}
