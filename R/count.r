wordcount <- function(str, sep=' ')
{
  .Call("R_ngram_wordcount", str, sep)
}
