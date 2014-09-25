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
\S4method{print}{ngram}(x, output="summary")

\S4method{show}{ngram}(object)
}
\arguments{
  \item{x,object}{An ngram object.}
  \item{output}{a character string; determines what exactly is 
  printed.  Options are "summary", "truncated", and "full".}
}
\details{
  If \code{output=="summary"}, then just a simple representation
  of the n-gram object will be printed; for example, "An ngram object with 
  5 2-grams".
  
  If \code{output=="truncated"}, then the n-grams will be printed
  up to a maximum of 5 total. 
  
  If \code{output=="full"} then all n-grams will be printed. 
}
\seealso{
  \code{\link{ngram}, \link{babble}}
}


