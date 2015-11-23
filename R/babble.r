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
#' 
#' @examples
#' library(ngram)
#' 
#' str <- "A B A C A B B"
#' ng <- ngram(str)
#' babble(ng, genlen=5, seed=1234)
#' 
#' @include ngram.r
#' @seealso \code{\link{ngram}}, \code{\link{getseed}}
#' @keywords Amusement
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
    assert_that(is.count(genlen))
    assert_that(is.number(seed))
    
    
    if (genlen >= 2^31)
      stop(paste("genlen=", genlen, " is too large", sep=""))
    
    genlen <- as.integer(genlen)
    
    if (ng@n > genlen)
      warning("n > genlen; selecting a random n-gram instead")
    
    seed <- as.integer(seed)
    
    ret <- .Call("R_ngram_gen", ng@ngl_ptr, genlen, seed, PACKAGE="ngram")
    
    return( ret )
  }
)
