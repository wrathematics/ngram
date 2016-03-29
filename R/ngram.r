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
#' @seealso \code{\link{Tokenize}}
#' @keywords Tokenization
setClass("ngram", 
  representation(
    str_ptr="externalptr",
    strlen="integer",
    n="integer",
    ngl_ptr="externalptr",
    ngsize="integer",
    sl_ptr="externalptr"
  )
)



#' n-gram Tokenization
#' 
#' The \code{ngram()} function is the main workhorse of this package.  It takes
#' an input string and converts it into the internal n-gram representation.
#' 
#' @details
#' On evaluation, a copy of the input string is produced and stored as an
#' external pointer.  This is necessary because the internal list
#' representation just points to the first char of each word in the input
#' string.  So if you (or R's gc) deletes the input string, basically all hell
#' breaks loose.
#' 
#' The \code{sep} parameter splits at any of the characters in 
#' the string.  So \code{sep=", "} splits at a comma or a space.
#' 
#' @param str 
#' The input text.
#' @param n 
#' The 'n' as in 'n-gram'.
#' @param sep
#' A set of separator characters for the "words".  See details for
#' information about how this works; it works a little differently
#' from \code{sep} arguments in R functions.
#' 
#' @return
#' An \code{ngram} class object.
#' 
#' @examples
#' library(ngram)
#' 
#' str <- "A B A C A B B"
#' ngram(str, n=2)
#' 
#' str <- "A,B,A,C A B B"
#' ### Split at a space
#' print(ngram(str), output="full")
#' ### Split at a comma
#' print(ngram(str, sep=","), output="full")
#' ### Split at a space or a comma
#' print(ngram(str, sep=", "), output="full")
#' 
#' @aliases tokenize
#' @seealso \code{\link{ngram-class}}, \code{\link{getters}}, 
#' \code{\link{phrasetable}}, \code{\link{babble}}
#' @keywords Tokenization
#' @name Tokenize
#' @rdname tokenize
NULL



#' @rdname tokenize
#' @export
setGeneric(name="ngram", 
  function(str, n=2, sep=" ") 
    standardGeneric("ngram"), 
  package="ngram"
)



#' @rdname tokenize
#' @export
setMethod("ngram", signature(str="character"),
  function(str, n=2, sep=" ")
  {
    assert_that(is.character(str))
    assert_that(is.count(n))
    assert_that(is.character(sep))
    
    
    if (n > 2^31)
      stop(paste("n=", n, " is too large", sep=""))
    
    n <- as.integer(n)
    
    nwords <- wordcount(str,sep,min)
    if (nwords < n)
      stop(paste("input 'str' has ", "nwords=", nwords, " and ", "n=", n, "; must have nwords >= n", sep=""))
    
    #strlen <- nchar(str) ## always an integer due to STRSXP restrictions
    strlen <- length(str)

    if(length(sep) > 1)
        sep <- paste0(sep,collapse="")

    out <- .Call(ng_process, str, strlen, n, sep, PACKAGE="ngram")
    
    if (is.integer(out) && out == -1L)
      stop("There was a problem processing the input string!")
    
    ret <- new("ngram", str_ptr=out$str_ptr, strlen=strlen, n=n, ngsize=out$ngsize, sl_ptr=out$sl_ptr, ngl_ptr=out$ngl_ptr)
    
    return( ret )
  }
)
