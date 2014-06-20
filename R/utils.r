concat <- function(str, collapse="", rm.space=FALSE)
{
  if (length(str) > 1)
    str <- paste(sapply(str, concat), collapse=collapse)
  
  if (rm.space)
    str <- gsub(x=str, pattern=" ", replacement="")
  
  return( str )
}



setMethod("wordcount", signature(x="character"),
  function(x)
  {
    if (length(x) > 1)
      return( sum(sapply(x, wordcount)) )
    
    sep <- ' '
    .Call("R_ngram_wordcount", x, sep, nchar(sep), PACKAGE="ngram")
  }
)



setMethod("wordcount", signature(x="ngram"),
  function(x)
  {
    ret <- wordcount(x=get.string(x))
    
    return( ret )
  }
)

