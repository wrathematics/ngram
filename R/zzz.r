.onUnload <- function(libpath)
{
  library.dynam.unload("ngram", libpath)

  invisible()
}
