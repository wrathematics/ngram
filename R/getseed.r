hash96 <- function(a, b, c)
{
  .Call("R_mix_96", as.integer(a), as.integer(b), as.integer(c), PACKAGE="ngram")
}

getseed <- function()
{
#  if (Sys.info()[[1L]] == "Windows")
#  {
#    date <- as.integer(Sys.Date())
#    time <- as.integer(Sys.time())
#    pid <- as.integer(Sys.getpid())
#    
#    ret <- hash96(time, pid, date)
#    ret <- as.integer(ret)
#  }
#  else
    ret <- .Call("R_ngram_get_seed", PACKAGE="ngram")
  
  return( ret )
}
