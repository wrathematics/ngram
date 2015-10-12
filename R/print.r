ng.print <- function(ng, truncated=TRUE)
{
  .Call("ng_print", ng@ngl_ptr, ng@ngsize, as.integer(truncated), PACKAGE="ngram")
  invisible()
}


#' ngram printing
#' 
#' Print methods.
#' 
#' If \code{output=="summary"}, then just a simple representation of the n-gram
#' object will be printed; for example, "An ngram object with 5 2-grams".
#' 
#' If \code{output=="truncated"}, then the n-grams will be printed up to a
#' maximum of 5 total.
#' 
#' If \code{output=="full"} then all n-grams will be printed.
#' 
#' @param x,object 
#' An ngram object.
#' @param output 
#' a character string; determines what exactly is printed.
#' Options are "summary", "truncated", and "full".
#' 
#' @seealso \code{\link{ngram}, \link{babble}}
#' 
#' @include ngram.r
#' @name ngram-print
#' @rdname ngram-print
NULL

#' @rdname ngram-print
#' @export
setMethod("print", signature(x="ngram"),
  function(x, output="summary")
  {
    output <- match.arg(tolower(output), c("summary", "truncated", "full"))
    
    if (output == "summary")
      cat(paste("An ngram object with ", x@ngsize, " ", x@n, "-grams", sep=""), "\n")
    else if (output == "truncated")
      ng.print(x, truncated=TRUE)
    else if (output == "full")
      ng.print(x, truncated=FALSE)
    
    invisible()
  }
)

#' @rdname ngram-print
#' @export
setMethod("show", signature(object="ngram"),
  function(object)
    print(x=object, output="summary")
)

