#' getseed
#' 
#' A seed generator for use with the ngram package.
#' 
#' Uses a 96-bit hash of the current process id, time, and a random
#' uniform value from R's random generator.
#' 
#' @seealso \code{\link{babble}}
#' 
#' @useDynLib ngram R_ngram_get_seed
#' @keywords Utility
#' @export
getseed = function()
{
  .Call(R_ngram_get_seed, PACKAGE="ngram")
}
