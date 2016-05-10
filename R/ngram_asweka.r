#' Weka-like n-gram Tokenization
#' 
#' An n-gram tokenizer with identical output to the \code{NGramTokenizer}
#' function from the RWeka package.
#' 
#' @details
#' This n-gram tokenizer behaves similarly in both input and return to 
#' the tokenizer in RWeka.  Unlike the tokenizer \code{ngram()}, the
#' return is not a special class of external pointers; it is a vector,
#' and therefore can be serialized via \code{save()} or \code{saveRDS()}.
#' 
#' @param str 
#' The input text.
#' @param min,max
#' The minimum and maximum 'n' as in 'n-gram'.
#' @param sep
#' A set of separator characters for the "words".  See details for
#' information about how this works; it works a little differently
#' from \code{sep} arguments in R functions.
#' 
#' @return
#' A vector of n-grams listed in decreasing blocks of n, in order within a
#' block.  The output matches that of RWeka's n-gram tokenizer.
#' 
#' @examples
#' library(ngram)
#' 
#' str <- "A B A C A B B"
#' ngram_asweka(str, min=2, max=4)
#' 
#' @seealso \code{\link{ngram}}
#' @keywords Tokenization
#' @name Tokenize-AsWeka
#' @rdname tokenize-asweka
#' @export
ngram_asweka <- function(str, min=2, max=2, sep=" ")
{
  assert_that(is.character(str))
  assert_that(length(str) > 0)
  assert_that(is.count(min))
  assert_that(is.count(max))
  assert_that(is.character(sep))
  
  .Call(ng_asweka, str, as.integer(min), as.integer(max), sep)
}
