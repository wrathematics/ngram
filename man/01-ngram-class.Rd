\name{ngram-class}
\docType{class}
\alias{ngram}
\alias{ngram-class}
\title{Class ngram}
\description{The ngram Class}
\section{Creating Objects}{
  \code{ new('ddmatrix', Data = ..., dim = ..., ldim = ..., 
  bldim = ..., ICTXT = ...)}
}
\section{Slots}{
\describe{
\item{\code{str_ptr}:}{An external pointer to a copy of the input
  string.}
\item{\code{strlen}:}{The number of chars of the input string.}
\item{\code{n}:}{The canonical 'n' in 'n-gram'.}
\item{\code{ng_ptr}:}{External pointer to the array of n-grams.}
\item{\code{ngsize}:}{Number of n-grams}
\item{\code{wl_ptr}:}{External pointer to the list of words.}
}
}
\section{Details}{
  Deets.
}
\seealso{
  \code{\link{SlotAccessors}}
}
\keyword{Class}
