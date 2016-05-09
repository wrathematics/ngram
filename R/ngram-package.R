#' ngram: An n-gram Babbler
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
#' @useDynLib ngram,  
#'   ng_extract_ngrams, ng_extract_str, ng_print, ng_process,
#'   R_ngram_gen, R_ngram_get_seed, R_ngram_wordcount,
#'   R_ng_get_phrasetable, R_stringsummary, ng_asweka
#' 
#' @import methods assertthat
#' 
#' @name ngram-package
#' @docType package
#' @author Drew Schmidt \email{wrathematics AT gmail.com}, Christian
#' Heckendorf.
#' @keywords Package
NULL
