concat <- function(str)
{
  if (length(str) > 1)
    return( paste(sapply(str, concat), collapse="") )
  
  gsub(x=str, pattern=" ", replacement="")
}



setMethod("wordcount", signature(x="character"),
  function(x)
  {
    if (length(x) > 1)
      return( sum(sapply(x, wordcount)) )
    
    sep <- ' '
    .Call("R_ngram_wordcount", x, sep, nchar(sep))
  }
)



setMethod("wordcount", signature(x="ngram"),
  function(x)
  {
    ret <- wordcount(x=get.string(x))
    
    return( ret )
  }
)

