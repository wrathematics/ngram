#' ngram: Fast n-Gram Tokenization
#' 
#' An n-gram is a sequence of n "words" taken from a
#' body of text.  This package offers utilities for creating, 
#' displaying, summarizing, and "babbling" n-grams.  The 
#' tokenization and "babbling" are handled by very efficient C
#' code, which can even be build as its own standalone library.
#' The babbler is a simple Markov chain.
#' 
#' The ngram package is distributed under the permissive 2-clause BSD license.
#' If you find the code here useful, please let us know and/or cite the
#' package, whatever is appropriate.
#' 
#' The package has its own PRNG; we use an implementation of MT1997 for all
#' non-deterministic choices.
#' 
#' @import methods
#' 
#' @name ngram-package
#' @docType package
#' @keywords Package
NULL
