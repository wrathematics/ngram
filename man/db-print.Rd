\name{ngram print}

\docType{methods}

\alias{print-method}
\alias{print,ngram-method}
\alias{print}

\alias{show-method}
\alias{show,ngram-method}
\alias{show}

\title{ngram printing}

\description{
  Print methods.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "ngram")}}{}
}
}
\usage{
\S4method{print}{ngram}(x, full=FALSE)

\S4method{show}{ngram}(object)
}
\arguments{
  \item{x,object}{An ngram object.}
  \item{full}{logical; determines if the complete set of n-grams
  and their nextwords should be printed.}
}
\seealso{
  \code{\link{ngram}, \link{babble}}
}


