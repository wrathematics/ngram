hash96 <- function(a, b, c)
{
  .Call(R_mix_96, as.integer(a), as.integer(b), as.integer(c), PACKAGE="ngram")
}


#' getseed
#' 
#' A seed generator for use with the ngram package.
#' 
#' @export
getseed <- function()
{
#  if (Sys.info()[[1L]] == "Windows")
#  {
#    date <- as.integer(Sys.Date())
#    time <- as.integer(Sys.time())
#    pid <- as.integer(Sys.getpid())
#    
#    ret <- hash96(time, pid, date)
#    ret <- as.integer(ret)
#  }
#  else
    ret <- .Call(R_ngram_get_seed, PACKAGE="ngram")
  
  return( ret )
}



#' ngram Babbler
#' 
#' A markov chain babbler.
#' 
#' The babbler uses its own internal PRNG (i.e., not R's), so seeds cannot be
#' managed as with R's seeds.  The generator is an implementation of MT19937.
#' 
#' @param ng 
#' An ngram object.
#' @param genlen 
#' Generated length, i.e., the number of words to babble.
#' @param seed 
#' Seed for the random number generator.
#' 
#' @seealso \code{\link{ngram}}
#' 
#' @examples
#' \dontrun{
#' library(ngram)
#' 
#' str <- "A B A C A B B"
#' ng <- ngram(str)
#' babble(ng, genlen=5, seed=1234)
#' }
#' 
#' @include ngram.r
#' @name babble
#' @rdname babble
NULL

#' @rdname babble
#' @export
setGeneric(name="babble", 
  function(ng, genlen=150, seed=getseed()) 
    standardGeneric("babble"), 
  package="ngram"
)

#' @rdname babble
#' @export
setMethod("babble", signature(ng="ngram"),
  function(ng, genlen=150, seed=getseed())
  {
    if (genlen >= 2^31)
      stop(paste("genlen=", genlen, " is too large", sep=""))
    
    genlen <- as.integer(genlen)
    
    if (genlen <= 0)
      stop("genlen must be a positive integer")
    
    if (ng@n > genlen)
      warning("n > genlen; selecting a random n-gram instead")
    
    seed <- as.integer(seed)
    
    ret <- .Call("R_ngram_gen", ng@ngl_ptr, genlen, seed, PACKAGE="ngram")
    
    return( ret )
  }
)

