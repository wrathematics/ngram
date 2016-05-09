#' Weka-like n-gram Tokenization
#' 
#' An n-gram tokenizer with identical output to the \code{NGramTokenizer}
#' function from the RWeka package.
#' 
#' @details
#' TODO
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
#' ngram_asweka(str, min=2, max=4)
#' 
#' @seealso \code{\link{ngram}}
#' @keywords Tokenization
#' @name Tokenize-AsWeka
#' @rdname tokenize-asweka
#' @export
ngram_asweka <- function(x, min=2, max=2, sep=" ")
{
  assert_that(is.character(str))
  assert_that(is.count(min))
  assert_that(is.count(max))
  assert_that(is.character(sep))
  
  .Call(ng_asweka, x, length(x), as.integer(min), as.integer(max), sep)
}
