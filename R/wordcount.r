#' wordcount
#' 
#' \code{wordcount()} counts words.  Currently a "word" is a clustering of
#' characters separated from another clustering of charactersby at least 1
#' space.  That is the law.
#' 
#' @param x 
#' A string or vector of strings, or an ngram object.
#' @param sep
#' The characters used to separate words.
#' @param count.function
#' The function to use for aggregation.
#' 
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
  function(x, sep=" ", count.function=sum) 
    standardGeneric("wordcount"), 
  package="ngram"
)

#' @rdname wordcount
#' @export
setMethod("wordcount", signature(x="character"),
  function(x, sep=" ", count.function=sum)
  {
    if (length(x) > 1)
      return( count.function(sapply(x, wordcount, sep)) )
    
    #sep <- ' '
    .Call(R_ngram_wordcount, x, sep, PACKAGE="ngram")
  }
)

#' @rdname wordcount
#' @export
setMethod("wordcount", signature(x="ngram"),
  function(x, sep=" ", count.function=sum)
  {
    ret <- wordcount(x=get.string(x),sep,count.function)
    
    return( ret )
  }
)


