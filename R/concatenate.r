#' Concatenate
#' 
#' A quick utility for concatenating strings together.  This is
#' handy because if you want to generate the n-grams for several different
#' texts, you must first put them into a single string unless the text is
#' composed of sentences that should not be joined.
#' 
#' @param ... 
#' Input text(s).
#' @param collapse 
#' A character to separate the input strings if a vector of
#' strings is supplied; otherwise this does nothing.
#' @param rm.space 
#' logical; determines if spaces should be removed from the
#' final string.
#' 
#' @return
#' A string.
#' 
#' @examples
#' library(ngram)
#' 
#' words <- c("a", "b", "c")
#' wordcount(words)
#' str <- concatenate(words)
#' wordcount(str)
#' 
#' @seealso \code{\link{preprocess}}
#' @keywords Preprocessing
#' @export
concatenate <- function(..., collapse=" ", rm.space=FALSE)
{
  l <- list(...)
  
  str <- paste(sapply(l, paste, collapse=collapse), collapse=collapse)
  
  if (rm.space)
    str <- gsub(x=str, pattern=" ", replacement="")
  
  return( str )
}
