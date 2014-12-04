ng.print <- function(ng, truncated=TRUE)
{
  .Call("ng_print", ng@ngl_ptr, ng@ngsize, as.integer(truncated), PACKAGE="ngram")
  
  invisible()
}



setMethod("print", signature(x="ngram"),
  function(x, output="summary")
  {
    output <- match.arg(tolower(output), c("summary", "truncated", "full"))
    
    if (output == "summary")
      print(paste("An ngram object with ", x@ngsize, " ", x@n, "-grams", sep=""))
    else if (output == "truncated")
      ng.print(x, truncated=TRUE)
    else if (output == "full")
      ng.print(x, truncated=FALSE)
    
    invisible()
  }
)



setMethod("show", signature(object="ngram"),
  function(object)
    print(x=object, output="summary")
)

