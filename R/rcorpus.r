#' Random Corpus
#' 
#' Generate a corpus of random "words".
#' 
#' @param nwords
#' Number of words to generate.
#' @param alphabet
#' The pool of "letters" that word generation coes from.  By default,
#' it is the lowercase roman alphabet.
#' @param minwordlen,maxwordlen
#' The min/max length of words in the generated corpus.
#' 
#' @return
#' A string.
#' 
#' @examples
#' rcorpus(10)
#' 
#' @importFrom stats runif
#' 
#' @keywords Utility
#' @export
rcorpus <- function(nwords=50, alphabet=letters, minwordlen=1, maxwordlen=6)
{
  assert_that(is.count(nwords))
  assert_that(is.character(alphabet))
  assert_that(is.count(minwordlen))
  assert_that(is.count(maxwordlen))
  
  if (minwordlen > maxwordlen)
    stop("Argument 'maxwordlen' must be at least 'minwordlen'.")
  
  sizes <- as.integer(runif(nwords, minwordlen, maxwordlen+1))
  words <- sapply(sizes, function(size) paste0(sample(alphabet, size=size, replace=TRUE), collapse=""))
  
  paste0(words, collapse=" ")
}
