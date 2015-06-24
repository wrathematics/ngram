#' ngram: An n-gram Babbler
#' 
#' This package offers utilities for creating, displaying, and "babbling"
#' n-grams.  The babbler is a simple Markov process.
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
#'   R_mix_96, R_ngram_gen, R_ngram_get_seed, R_ngram_wordcount,
#'   R_ng_get_phrasetable
#' 
#' @import methods
#' 
#' @name ngram-package
#' @docType package
#' @author Drew Schmidt \email{wrathematics AT gmail.com}, Christian
#' Heckendorf.
#' @keywords Package
NULL

