ng.process <- function(str, n=2)
{
  n <- as.integer(n)
  if (n < 1L)
    stop("argument 'n' must be a positive integer")
  
  strlen <- as.integer(nchar(str))
  
  out <- .Call("ng_process", str, strlen, n)
  
  if (is.integer(out))
    stop(paste("No ", n, "-grams found in the given string.", sep=""))
  
  ret <- new("ngram", str_ptr=out$str_ptr, strlen=strlen, n=n, ngsize=out$ngsize, wl_ptr=out$wl_ptr, ng_ptr=out$ng_ptr)
  
  return( ret )
}



ng.print <- function(ng)
{
  .Call("ng_print", ng@ng_ptr, ng@ngsize)
  
  invisible()
}



ng.extract.ngrams <- function(ng)
{
  .Call("ng_extract_ngrams", ng@ng_ptr, ng@ngsize)
}



ng.extract.str <- function(ng)
{
  .Call("ng_extract_str", ng@str_ptr, ng@strlen)
}
