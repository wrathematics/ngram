ng.process <- function(str, n=2)
{
  if (n > 2^31)
    stop(paste("n=", n, " is too large", sep=""))
  
  n <- as.integer(n)
  
  if (n < 1L)
    stop("argument 'n' must be a positive integer")
  
  nwords <- wordcount(str)
  if (nwords < n)
    stop(paste("input 'str' has ", "nwords=", nwords, " and ", "n=", n, "; must have nwords >= n", sep=""))
  
  strlen <- nchar(str) ## always an integer due to STRSXP restrictions
  
  out <- .Call("ng_process", str, strlen, n, PACKAGE="ngram")
  
  ret <- new("ngram", str_ptr=out$str_ptr, strlen=strlen, n=n, ngsize=out$ngsize, wl_ptr=out$wl_ptr, ng_ptr=out$ng_ptr)
  
  return( ret )
}



setMethod("ngram", signature(x="character"),
  function(x, n=2)
    ng.process(str=x, n=n)
)

