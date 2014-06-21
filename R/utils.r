concat <- function(..., collapse="", rm.space=FALSE)
{
  l <- list(...)
  
  str <- paste(sapply(l, paste, collapse=collapse), collapse=collapse)
  
  if (rm.space)
    str <- gsub(x=str, pattern=" ", replacement="")
  
  return( str )
}



preprocess <- function(x, case=NULL, split.at.punct=FALSE)
{
  if (!is.null(case))
  {
    case <- match.arg(tolower(case), c("lower", "upper"))
    if (case == "lower")
      x <- tolower(x)
    else if (case == "upper") 
      x <- toupper(x)
  }
  
  if (split.at.punct)
    x <- gsub(x=x, pattern="([[:punct:]])", replacement=" \\1 ")
  
  # fix spacing
  x <- gsub(pattern="(\\t| +)", replacement=" ", x=x)
  # remove trailing whitespace
  x <- sub(pattern=" +$", replacement="", x=x)
  
  return( x )
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

