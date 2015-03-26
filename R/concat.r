#' concat
#' 
#' \code{concat()} is a utility for concatenating strings together.  This is
#' handy because if you want to generate the n-grams for several different
#' texts, you must first put them into a single string.
#' 
#' @param ... 
#' Input text(s).
#' @param collapse 
#' A character to separate the input strings if a vector of
#' strings is supplied; otherwisethis does nothing.
#' @param rm.space 
#' logical; determines if spaces should be removed from the
#' final string.
#' 
#' @return
#' A string.
#' 
#' @seealso \code{\link{Preprocess}}
#' 
#' @examples
#' \dontrun{
#' library(ngram)
#' 
#' words <- c("a", "b", "c")
#' wordcount(words)
#' str <- concat(words)
#' wordcount(str)
#' }
#' 
#' @export
concat <- function(..., collapse="", rm.space=FALSE)
{
  l <- list(...)
  
  str <- paste(sapply(l, paste, collapse=collapse), collapse=collapse)
  
  if (rm.space)
    str <- gsub(x=str, pattern=" ", replacement="")
  
  return( str )
}

