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
#' str = "A B A C A B B"
#' ngram(str, n=2)
#' 
#' str = "A,B,A,C A B B"
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
#' 
#' @useDynLib ngram R_ng_process
#' @export
ngram = function(str, n=2, sep=" ")
{
  check.is.strings(str)
  check.is.posint(n)
  check.is.string(sep)
  
  
  if (n > 2^31)
    stop(paste("n=", n, " is too large", sep=""))
  
  n = as.integer(n)
  
  nwords = wordcount(str, sep, min)
  if (nwords < n)
    stop(paste("input 'str' has ", "nwords=", nwords, " and ", "n=", n, "; must have nwords >= n", sep=""))
  
  strlen = length(str)

  if (length(sep) > 1)
      sep = paste0(sep,collapse="")

  out = .Call(R_ng_process, str, strlen, n, sep, PACKAGE="ngram")
  
  if (is.integer(out) && out == -1L)
    stop("There was a problem processing the input string!")
  
  new("ngram", str_ptr=out$str_ptr, strlen=strlen, n=n, ngsize=out$ngsize, sl_ptr=out$sl_ptr, ngl_ptr=out$ngl_ptr)
}
