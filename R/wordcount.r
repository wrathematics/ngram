#' wordcount
#' 
#' \code{wordcount()} counts words.  Currently a "word" is a clustering of
#' characters separated from another clustering of charactersby at least 1
#' space.  That is the law.
#' 
#' @param x 
#' A string or vector of strings, or an ngram object.
#' 
#' @return 
#' A count.
#' 
#' 
#' @examples
#' library(ngram)
#' 
#' words <- c("a", "b", "c")
#' words
#' wordcount(words)
#' 
#' str <- concatenate(words, collapse="")
#' str
#' wordcount(str)
#' 
#' @include ngram.r
#' @seealso \code{\link{preprocess}}
#' @keywords Summarize
#' @name wordcount
#' @rdname wordcount
NULL

#' @rdname wordcount
#' @export
setGeneric(name="wordcount", 
  function(x) 
    standardGeneric("wordcount"), 
  package="ngram"
)

#' @rdname wordcount
#' @export
setMethod("wordcount", signature(x="character"),
  function(x)
  {
    if (length(x) > 1)
      return( sum(sapply(x, wordcount)) )
    
    sep <- ' '
    .Call(R_ngram_wordcount, x, sep, nchar(sep), PACKAGE="ngram")
  }
)

#' @rdname wordcount
#' @export
setMethod("wordcount", signature(x="ngram"),
  function(x)
  {
    ret <- wordcount(x=get.string(x))
    
    return( ret )
  }
)


