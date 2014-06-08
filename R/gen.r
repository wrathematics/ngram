ng.generate <- function(ng, genlen=150, seed=getseed())
{
  if (genlen >= 2^31)
    stop(paste("genlen=", genlen, " is too large", sep=""))
  
  genlen <- as.integer(genlen)
  
  if (genlen <= 0)
    stop("genlen must be a positive integer")
  
  if (ng@n > genlen)
    warning("n > genlen; selecting a random n-gram instead")
  
  seed <- as.integer(seed)
  
  ret <- .Call("R_ngram_gen", ng@n, ng@ng_ptr, ng@ngsize, genlen, seed)
  
  return( ret )
}



#setMethod("get.ngrams", signature(ng="ngram"),
#  function(ng)
#    ng.extract.ngrams(ng)
#)
