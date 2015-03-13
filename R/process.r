#' Process
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
#' @param x 
#' The input text.
#' @param n 
#' The 'n' as in 'n-gram'.
#' 
#' @seealso \code{\link{ngram-class}}
#' 
#' @keywords Data Generation
#' 
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
#' @name Process
#' @rdname ngram
#' @export
ngram <- function(x, n=2)
{
  if (n > 2^31)
    stop(paste("n=", n, " is too large", sep=""))
  
  n <- as.integer(n)
  
  if (n < 1L)
    stop("argument 'n' must be a positive integer")
  
  nwords <- wordcount(x)
  if (nwords < n)
    stop(paste("input 'x' has ", "nwords=", nwords, " and ", "n=", n, "; must have nwords >= n", sep=""))
  
  strlen <- nchar(x) ## always an integer due to STRSXP restrictions
  
  out <- .Call(ng_process, x, strlen, n, PACKAGE="ngram")
  
  if (is.integer(out) && ret == -1L)
    stop("There was a problem processing the input string!")
  
  ret <- new("ngram", str_ptr=out$str_ptr, strlen=strlen, n=n, ngsize=out$ngsize, wl_ptr=out$wl_ptr, ngl_ptr=out$ngl_ptr)
  
  return( ret )
}

