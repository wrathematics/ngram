hash96 <- function(a, b, c)
{
  .Call(R_mix_96, as.integer(a), as.integer(b), as.integer(c), PACKAGE="ngram")
}


#' getseed
#' 
#' A seed generator for use with the ngram package.
#' 
#' Uses a 96-bit hash of the current process id, time, and a random
#' uniform value from R's random generator.
#' 
#' @seealso \code{\link{babble}}
#' 
#' @keywords Utility
#' @export
getseed <- function()
{
  .Call(R_ngram_get_seed, PACKAGE="ngram")
}
