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
#' \code{\#ngrams = nwords - (\#repeats - 1) - (n - 1)}
#' 
#' An \code{ngram} object is an S4 class container that stores some basic
#' summary information (e.g., n), and several external pointers.  For
#' information on how to construct an \code{ngram} object, see
#' \code{\link{ngram}}.
#' 
#' @slot str_ptr
#' A pointer to a copy of the original input string.
#' @slot strlen
#' The length of the string.
#' @slot n
#' The eponymous 'n' as in 'n-gram'.
#' @slot ngl_ptr
#' A pointer to the processed list of n-grams.
#' @slot ngsize
#' The length of the ngram list, or in other words, the number of
#' unique n-grams in the input string.
#' @slot sl_ptr
#' A pointer to the list of words from the input string.
#' 
#' @name ngram-class
#' @seealso \code{\link{ngram}}
#' @keywords Tokenization
setClass("ngram", 
  representation(
    str_ptr = "externalptr",
    strlen = "integer",
    n = "integer",
    ngl_ptr = "externalptr",
    ngsize = "integer",
    sl_ptr = "externalptr"
  )
)
