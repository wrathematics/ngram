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
#' @param count_fun
#' The function to use for aggregation if \code{x} has length greater than 1.
#' Useful ones include \code{sum} and \code{identity}.
#' 
#' @return 
#' A count.
#' 
#' @examples
#' library(ngram)
#' 
#' words = c("a", "b", "c")
#' words
#' wordcount(words)
#' 
#' str = concatenate(words, collapse="")
#' str
#' wordcount(str)
#' 
#' @seealso \code{\link{preprocess}}
#' @keywords Summarize
#' @name wordcount
#' @rdname wordcount
NULL



#' @useDynLib ngram R_ngram_wordcount
#' @rdname wordcount
#' @export
wordcount = function(x, sep=" ", count_fun=sum) UseMethod("wordcount", x)



#' @rdname wordcount
#' @export
wordcount.character = function(x, sep=" ", count_fun=sum)
{
  if (length(x) > 1)
    count_fun(sapply(x, wordcount, sep))
  else
    .Call(R_ngram_wordcount, x, sep, PACKAGE="ngram")
}



#' @rdname wordcount
#' @export
wordcount.ngram = function(x, sep=" ", count_fun=sum)
{
  x_string = get.string(x)
  wordcount.character(x=x_string, sep=sep, count_fun=count_fun)
}
