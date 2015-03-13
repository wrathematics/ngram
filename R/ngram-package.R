

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
#' @name ngram-package
#' @docType package
#' @author Drew Schmidt \email{wrathematics AT gmail.com}, Christian
#' Heckendorf.
#' @keywords Package
NULL





#' Class ngram
#' 
#' An n-gram is an ordered sequence of n "words" taken from a body of "text".
#' The terms "words" and "text" can easily be interpreted literally, or with a
#' more loose interpretation.
#' 
#' For example, consider the sequence "A B A C A B B".  If we examine the
#' 2-grams (or bigrams) of this sequence, they are
#' 
#' A B, B A, A C, C A, A B, B B
#' 
#' or without repetition:
#' 
#' A B, B A, A C, C A, B B
#' 
#' That is, we take the input string and group the "words" 2 at a time (because
#' \code{n=2}).  Notice that the number of n-grams and the number of words are
#' not obviously related; counting repetition, the number of n-grams is equal
#' to
#' 
#' \code{nwords - n + 1}
#' 
#' Bounds ignoring repetition are highly dependent on the input.  A correct but
#' useless bound is
#' 
#' \code{\# ngrams = nwords - (\# repeats - 1) - (n - 1)}
#' 
#' An \code{ngram} object is an S4 class container that stores some basic
#' summary information (e.g., n), and several external pointers.  For
#' information on how to construct an \code{ngram} object, see
#' \code{\link{ngram}}.
#' 
#' 
#' @name ngram-class
#' @docType class
#' @section Creating Objects: \code{ new('ngram', str_ptr = ..., strlen = ...,
#' n = ..., ng_ptr = ..., ngsize = ..., wl_ptr = ...)}
#' @seealso \code{\link{Process}}
#' @keywords Class
NULL





#' n-gram Utilities
#' 
#' Some utility methods.
#' 
#' \code{concat()} is a utility for concatenating strings together.  This is
#' handy because if you want to generate the n-grams for several different
#' texts, you must first put them into a single string.
#' 
#' \code{wordcount()} counts words.  Currently a "word" is a clustering of
#' characters separated from another clustering of charactersby at least 1
#' space.  That is the law.
#' 
#' @name Utilities
#' @aliases Utilities concat wordcount-method wordcount,character-method
#' wordcount,ngram-method wordcount
#' @docType methods
#' @param ... Input text(s).
#' @param x A string or vector of strings.
#' @param collapse A character to separate the input strings if a vector of
#' strings is supplied; otherwisethis does nothing.
#' @param rm.space logical; determines if spaces should be removed from the
#' final string.
#' @return \code{concat()} returns
#' @section Methods: \describe{ \item{list("signature(x = \"character\")")}{}
#' %\item{\code{signature(x = "book")}}{} \item{list("signature(x =
#' \"ngram\")")}{} }
#' @seealso \code{\link{Preprocess}}
#' @examples
#' 
#' \dontrun{
#' library(ngram)
#' 
#' words <- c("a", "b", "c")
#' wordcount(words)
#' str <- concat(words)
#' wordcount(str)
#' }
#' 
NULL





#' Preprocessing
#' 
#' A simple text preprocessor for use with the \code{ngram()} function.
#' 
#' The input text \code{x} must already be in the correct form for
#' \code{ngram()}, i.e., a single string (character vector of length 1).
#' 
#' The \code{case} argument can take 3 possible values: \code{NULL}, in which
#' case nothing is done, or \code{lower} or \code{upper}, wherein the case of
#' the input text will be made lower/upper case, repesctively.
#' 
#' @aliases Preprocess preprocess
#' @param x Input text.
#' @param case Option to change the case of the text. See Details section for
#' appropriate values.
#' @param split.at.punct logical; determines if spaces should be inserted
#' before and after punctuation (making them individual characters for an
#' n-gram model).
#' @return \code{concat()} returns
#' @seealso \code{\link{Process}, \link{Utilities}}
#' @examples
#' 
#' \dontrun{
#' library(ngram)
#' 
#' x <- "Watch  out    for snakes!  "
#' preprocess(x)
#' preprocess(x, case="upper", split.at.punct=TRUE)
#' }
#' 
NULL





#' ngram
#' 
#' This routine processes a string into an \code{ngram} class object.
#' 
#' The \code{ngram()} function is the main workhorse of this package.  It takes
#' an input string and converts it into the internal n-gram representation.
#' 
#' On evaluation, a copy of the input string is produced and stored as an
#' external pointer.  This is necessary because the internal list
#' representation just points to the first char of each word in the input
#' string.  So if you (or R's gc) deletes the input string, basically all hell
#' breaks loose.
#' 
#' @name Process
#' @aliases Process ngram-method ngram,character-method ngram
#' @docType methods
#' @param x The input text.
#' @param n The 'n' as in 'n-gram'.
#' @section Methods: \describe{ \item{list("signature(x = \"character\")")}{}
#' %\item{\code{signature(x = "book")}}{} }
#' @seealso \code{\link{ngram-class}}
#' @keywords Data Generation
#' @examples
#' 
#' \dontrun{
#' library(ngram)
#' 
#' str <- "A B A C A B B"
#' ng <- ngram(str, n=2)
#' ng
#' }
#' 
NULL





#' ngram printing
#' 
#' Print methods.
#' 
#' If \code{output=="summary"}, then just a simple representation of the n-gram
#' object will be printed; for example, "An ngram object with 5 2-grams".
#' 
#' If \code{output=="truncated"}, then the n-grams will be printed up to a
#' maximum of 5 total.
#' 
#' If \code{output=="full"} then all n-grams will be printed.
#' 
#' @name ngram print
#' @aliases print-method print,ngram-method print show-method show,ngram-method
#' show
#' @docType methods
#' @param x,object An ngram object.
#' @param output a character string; determines what exactly is printed.
#' Options are "summary", "truncated", and "full".
#' @section Methods: \describe{ \item{list("signature(x = \"ngram\")")}{} }
#' @seealso \code{\link{ngram}, \link{babble}}
NULL





#' ngram Getters
#' 
#' Some simple "getters" for \code{ngram} objects. Necessary since the internal
#' representation is not a native R object.
#' 
#' \code{get.ngrams()} returns an R vector of all n-grams.
#' 
#' \code{get.nextwords()} does nothing at the moment; it will be implemented in
#' future releases.
#' 
#' \code{getnstring()} recovers the input string as an R string.
#' 
#' @name ngram Getters
#' @aliases get.ngrams-method get.ngrams,ngram-method get.ngrams
#' get.string-method get.string,ngram-method get.string get.nextwords-method
#' get.nextwords,ngram-method get.nextwords
#' @docType methods
#' @param ng An ngram object.
#' @section Methods: \describe{ \item{list("signature(ng = \"ngram\")")}{} }
#' @seealso \code{\link{ngram}}
#' @examples
#' 
#' \dontrun{
#' library(ngram)
#' 
#' str <- "A B A C A B B"
#' ng <- ngram(str)
#' get.ngrams(ng)
#' }
#' 
NULL





#' ngram Getters
#' 
#' A markov chain babbler.
#' 
#' The babbler uses its own internal PRNG (i.e., not R's), so seeds cannot be
#' managed as with R's seeds.  The generator is an implementation of MT19937.
#' 
#' @name Babble
#' @aliases babble-method babble,ngram-method babble
#' @docType methods
#' @param ng An ngram object.
#' @param genlen Generated length, i.e., the number of words to babble.
#' @param seed Seed for the random number generator.
#' @section Methods: \describe{ \item{list("signature(ng = \"ngram\")")}{} }
#' @seealso \code{\link{ngram}}
#' @examples
#' 
#' \dontrun{
#' library(ngram)
#' 
#' str <- "A B A C A B B"
#' ng <- ngram(str)
#' babble(ng, genlen=5, seed=1234)
#' }
#' 
NULL



