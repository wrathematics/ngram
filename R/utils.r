concat <- function(str)
{
  if (length(str) > 1)
    return( paste(sapply(str, concat), collapse="") )
  
  gsub(x=str, pattern=" ", replacement="")
}



wordcount <- function(str)
{
  if (length(str) > 1)
    return( sum(sapply(str, wordcount)) )
  
  # FIXME sep is broken
  sep <- ' '
  .Call("R_ngram_wordcount", str, sep)
}
