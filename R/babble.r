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
#' @param ...
#' Additional arguments.
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
#' @name Babble
#' @rdname babble
NULL

#' @rdname babble
#' @export
setGeneric(name="babble", 
  function(ng,  genlen, ...) 
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
