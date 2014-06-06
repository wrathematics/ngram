generate <- function(ng, genlen=150, seed=ngram.getseed())
{
  if (genlen >= 2^31)
    stop(paste("genlen=", genlen, " is too large", sep=""))
  
  genlen <- as.integer(genlen)
  
  if (genlen <= 0)
    stop("genlen must be a positive integer")
  
  if (ng@n > genlen)
  {
    warning("n > genlen; selecting a random n-gram instead")
    genlen <- 1L
  }
  else
    genlen <- genlen - ng@n
  
  seed <- as.integer(seed)
  
  .Call("R_ngram_gen", ng@n, ng@ng_ptr, ng@ngsize, genlen, seed)
}
